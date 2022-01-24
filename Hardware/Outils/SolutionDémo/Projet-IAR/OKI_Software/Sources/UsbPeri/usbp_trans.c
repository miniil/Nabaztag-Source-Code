/*******************************************************************************
    usbp_trans.c
    JOB60842�T���v���v���O���� 
    �f�[�^����M����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#define USBPMAIN
#include"config.h"
#include"usbp.h"
#include"usbp_class.h"

#if defined(PERI_TEST)
#include "usbp_test.h"
#endif /*defined(PERI_TEST)*/

/***********************************************************
 DMA �]���@�\��L���ɂ���B
***********************************************************/
#if 0
#define USBP_DMA_ENABLE
#define DMA_ENABLE_TX 1
#define DMA_ENABLE_RX 0
#endif
/***********************************************************
 DMA�`���l���͂P�`�����l���̂ݗL���ł��B
 ���̂��߁A���M����M�̃G���h�|�C���g�̂ǂ��炩�����
 DMA�Ɏw�肵�Ă��������B
***********************************************************/

void usbp_Execute_Request(Device_Request *device_request);

static void read_fifo(ulong *fifo, uchar *buf, uint cnt);
static void write_fifo(ulong *fifo, uchar *buf, uint cnt);

#if defined(USBP_DMA_ENABLE)
static void dma_write_fifo(ulong *fifo, uchar *buf, uint cnt);
static void dma_read_fifo(ulong *fifo, uchar *buf, uint cnt);
#endif /* defined(USBP_DMA_ENABLE) */


/*******************************************************************************
	Routine Name:	usbp_Decode_Request
	Form:			void usbp_Decode_Request(void)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	USB Device Requests (8byte) ��M �f�R�[�h���� 
******************************************************************************/

void usbp_Decode_Request(void)
{
	/*------------------------------------------------------------
	   EP0����M�����݋֎~                                        
	       �R���g���[���f�[�^�]�����ɁC�V���ȃZ�b�g�A�b�v���͂�   
	       �܂����ꍇ�C�����݋��ɂȂ��Ă���\�������邽��     
	------------------------------------------------------------*/
	DIS_EP0TXRX_PKTRDY_INT();

	/*------------------------------------------------------------
	   �f�o�C�X���N�G�X�g(8Byte)��ǂݍ���                        
	------------------------------------------------------------*/
	device_request.bmRequestType = GET_bmRequestType();
	device_request.bRequest      = GET_bRequest();
	device_request.wValue        = GET_wValue();
	device_request.wIndex        = GET_wIndex();
	device_request.wLength       = GET_wLength();

	/*------------------------------------------------------------
	   ���N�G�X�g����ǂݍ��񂾂̂� setup_rdy �̃��Z�b�g        
	------------------------------------------------------------*/
	CLR_SETUPRDY();

	/*------------------------------------------------------------
	   ����M�J�E���^������                                       
	------------------------------------------------------------*/
	epV[EP0RX].transferred_size = 0;	/* ��M�f�[�^���� */
	epV[EP0RX].demand_size  = 0;		/* ��M�v���f�[�^�� */
	epV[EP0TX].transferred_size = 0;	/* ���M�f�[�^���� */
	epV[EP0TX].demand_size  = 0;		/* ���M�v���f�[�^�� */

	if (device_request.wLength == 0x00)
	{	/* Control No-Data Transfer */
		/*------------------------------------------------------------
		   �z�X�g�E�f�o�C�X�ԂŃf�[�^�̑���M�Ȃ�                     
		------------------------------------------------------------*/
		usbp_Execute_Request(&device_request);			/* Device Request ���� */

		if((device_request.bmRequestType & DEVICE_to_HOST) != DEVICE_to_HOST)
		{
			SET_PKTRDY(EP0TX);			/* EP0���M�p�P�b�g���f�B�Z�b�g */
			ENA_EP0TX_PKTRDY_INT();		/* EP0���M�p�P�b�g���f�B�����݋��� */
		}
		else
		{
			/*	�]��������DEVICE_to_HOST�Ńf�[�^�X�e�[�W�����̏ꍇ�ɑΉ� */
			/* EP0�̃��b�N�������� */
			CLR_PKTRDY(EP0RX);			/* ��M�p�P�b�g���f�B���Z�b�g */
		}

	} 

	else if (device_request.bmRequestType & DEVICE_to_HOST)
	{	/* Control Read Transfer */
		/*------------------------------------------------------------
		   �z�X�g�Ƀf�[�^�𑗂�ꍇ�̓f�[�^���쐬���āC���M�p�P�b�g   
		   ���f�B�����݋���                                           
		------------------------------------------------------------*/
		usbp_Execute_Request(&device_request);		/* Device Request ���� */

		ENA_EP0TX_PKTRDY_INT();			/* EP0���M�p�P�b�g���f�B�����݋��� */

		/*------------------------------------------------------------
		   �f�[�^�]�����ɃX�e�[�^�X�X�e�[�W�Ɉڍs�����Ƃ��̂��߂Ɏ�   
		   �M�p�P�b�g���f�B�r�b�g���N���A                             
		  ----------------------------------------------------------  
		   �X�e�[�^�X�X�e�[�W�ŃR�}���h���s���s�����N�G�X�g�̏ꍇ�C   
		   �����Ŏ�M�p�P�b�g���f�B�̃N���A���s�����Ƃ͔��Ɋ댯��   
	       ���D�����ŃN���A���邱�Ƃɂ���ăX�e�[�^�X�X�e�[�W�I���m   
		   �F�̂��߂�OUT�g�[�N���ɑ΂��āC��������ACK��ԓ����܂��D   
		    (�{���X�e�[�^�X�X�e�[�W���I�����Ă��Ȃ��ꍇ��NAK��ԓ�)   
		  ----------------------------------------------------------  
		   �X�e�[�^�X�X�e�[�W�ŃR�}���h���s�𔺂����N�G�X�g�������   
		   ���́C�|�[�����O�Ȃǂɂ��EP0�X�e�[�^�X���W�X�^��D4:3��    
		   �Ď����C�X�e�[�^�X�X�e�[�W�Ɉڍs�m�F��C�p�P�b�g���f�B��   
		   �N���A����K�v������܂��D                                 
		------------------------------------------------------------*/
		CLR_PKTRDY(EP0RX);

	} 

	else	/* HOST to DEVICE */
	{	/* Control Write Transfer */
		/*------------------------------------------------------------
		   �z�X�g����f�[�^����M���邽�߂Ɏ�M�p�P�b�g���f�B������   
		   ����                                                       
		------------------------------------------------------------*/
		ENA_EP0RX_PKTRDY_INT();
	}
#if defined(USBP_DEBUG_PRINT)
#if defined(PERI_TEST)
			reg_print(INTENBL);
#endif /*defined(PERI_TEST)*/
#endif
}

/*******************************************************************************
	Routine Name:	usbp_Execute_Request
	Form:			void usbp_Execute_Request(void)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	USB Device Requests (8byte) ��M �f�R�[�h���� 
******************************************************************************/
void usbp_Execute_Request(Device_Request *device_request)
{
	bmRequestType type;
	uchar *buf;
	type = (bmRequestType)(device_request->bmRequestType & REQUEST_TYPE);
	buf = epV[EP0RX].buf;

#if defined(USBP_DEBUG_PRINT)
	sio_printf("%02X ",device_request->bmRequestType);
	sio_printf("%02X ",device_request->bRequest);
	sio_printf("%04X ",device_request->wValue);
	sio_printf("%04X ",device_request->wIndex);
	sio_printf("%04X\t",device_request->wLength);
#endif

	switch (type)
	{
	case STANDARD_TYPE:
		switch (device_request->bRequest)
		{
		case CLEAR_FEATURE:
			usbp_func_Clear_Feature(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("CLEAR_FEATURE.\n");
#endif
			break;
		case GET_CONFIGURATION:
			usbp_func_Get_Configuration(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("GET_CONFIGURATION.\n");
#endif
			break;
		case GET_DESCRIPTOR:
			usbp_func_Get_Descriptor(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("GET_DESCRIPTOR.\n");
#endif
			break;
		case GET_INTERFACE:
			usbp_func_Get_Interface(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("GET_INTERFACE.\n");
#endif
			break;
		case GET_STATUS:
			usbp_func_Get_Status(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("GET_STATUS.\n");
#endif
			break;
		case SET_ADDRESS:
			usbp_func_Set_Address(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SET_ADDRESS.\n");
#endif
			break;
		case SET_CONFIGURATION:
			usbp_func_Set_Configuration(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SET_CONFIGURATION.\n");
#endif
			break;
		case SET_DESCRIPTOR:
			usbp_func_Set_Descriptor(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SET_DESCRIPTOR.\n");
#endif
			break;
		case SET_FEATURE:
			usbp_func_Set_Feature(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SET_FEATURE.\n");
#endif
			break;
		case SET_INTERFACE:
			usbp_func_Set_Interface(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SET_INTERFACE.\n");
#if defined(PERI_TEST)
			reg_print(INTENBL);
#endif /*defined(PERI_TEST)*/
#endif
			break;
		case SYNCH_FRAME:
			usbp_func_Synch_Frame(device_request, buf);
#if defined(USBP_DEBUG_PRINT)
			sio_printf("SYNCH_FRAME.\n");
#if defined(PERI_TEST)
			reg_print(INTENBL);
#endif /*defined(PERI_TEST)*/
#endif
			break;
		default:
			/* STALL ����*/
			usbp_func_stall();
#if defined(USBP_DEBUG_PRINT)
			sio_printf("STALL.\n");
#endif
			break;
		}
		break;
	case VENDOR_TYPE:
		/*
		 * bmRequestType �� D6..5 �� Vendor ���w�肷��ꍇ�̏������s���D
		 */
		usbp_vendor_func();
#if defined(USBP_DEBUG_PRINT)
			sio_printf("VENDOR.\n");
#endif
		break;
	case CLASS_TYPE:
		/*
		 * bmRequestType �� D6..5 �� Class ���w�肷��ꍇ�̏������s���D
		 */
		usbp_class_func();
#if defined(USBP_DEBUG_PRINT)
			sio_printf("CLASS.\n");
#endif
		break;
	default:
		/* STALL ���� */
		SET_STALL_EP0();	/* STALL */
		break;
	}
}


/*
 ---------------------------------------------------------------------------
   ��M�f�[�^�ǂݍ��ݏ���                                                   
 ---------------------------------------------------------------------------
 */
/*******************************************************************************
	Routine Name:	read_FIFO
	Form:			void read_FIFO(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO READ �����֐�
******************************************************************************/
void read_FIFO(char ep)
{
	ulong *fifo;
	uchar *buf;
	ushort cnt;
	ushort payload;
	
	if((ep != EP4) && (ep != EP5))
		cnt = GET_RECV_BYTE(ep);					/* ��M�f�[�^�� */
	else
		cnt = GET_RECV_BYTE_EP4or5(ep);					/* ��M�f�[�^�� */

	/*------------------------------------------------------------
	   FIFO����f�[�^�̓Ǎ���                                     
	------------------------------------------------------------*/
	buf  = epV[ep].buf + epV[ep].transferred_size;		/* ��M�o�b�t�@�̃|�C���^�ړ� */
	fifo = GET_RFIFO_ADRS_EPn(ep);
	epV[ep].transferred_size += (uint)cnt;				/* ��M�f�[�^���� */
#if defined(USBP_DMA_ENABLE)
#if DMA_ENABLE_RX 
	if(ep == EP_RX)
	{
		SET_DMA_CONT0_EP(ep);
		SET_DMA_CONT0_ENABLE();
		dma_read_fifo(fifo, buf, (uint)cnt);
		DIS_DMA_CONT0_ENABLE();
	}
	else
#endif
#endif /* defined(USBP_DMA_ENABLE) */
	{
		read_fifo(fifo, buf, (uint)cnt);
		
		/*------------------------------------------------------------
		   ��M�p�P�b�g���f�B���Z�b�g                                 
		------------------------------------------------------------*/
		CLR_PKTRDY(ep);								/* ��M�p�P�b�g���f�B���Z�b�g */
	}
	
	if(ep == EP0RX)
	{
		/*------------------------------------------------------------
		   Control�]���S�f�[�^��M                                    
		------------------------------------------------------------*/
		if (device_request.wLength != 0 &&
			epV[EP0RX].transferred_size == device_request.wLength)
		{
			usbp_Execute_Request(&device_request);		/* Device Request �f�R�[�h���� */
			SET_PKTRDY(EP0TX);				/* ���M�p�P�b�g���f�B�Z�b�g */
			DIS_EP0RX_PKTRDY_INT();			/* EP0 ��M�p�P�b�g���f�B�����݋֎~ */
		}
	}
	else
	{
		if((ep != EP4) && (ep != EP5))
			payload = GET_PAYLOAD_EPn(ep);					/* ��M�y�C���[�h�� */
		else
			payload = GET_PAYLOAD_EP4or5(ep);				/* ��M�y�C���[�h�� */
		if(cnt == payload)
		{
			if(epV[ep].transferred_size >= epV[ep].demand_size)
			{
				/* �]�����I�������B */
				epV[ep].demand_size = 0;
				DIS_PKTRDY_INT(ep);
				(*epV[ep].callback)(buf, epV[ep].transferred_size);	/* ��M���ʒm */
			}
		}
		else
		{
			/* �]�����I�������B �V���[�g�p�P�b�g��M�̂��� */
			epV[ep].demand_size = 0;
			DIS_PKTRDY_INT(ep);
			(*epV[ep].callback)(buf, epV[ep].transferred_size);	/* ��M���ʒm */
		}
	}
}

/*
 ---------------------------------------------------------------------------
   ���M�f�[�^�������ݏ���                                                   
 ---------------------------------------------------------------------------
 */
/*******************************************************************************
	Routine Name:	write_FIFO
	Form:			void write_FIFO(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO WRITE �����֐�
******************************************************************************/
void write_FIFO(char ep)
{
	uint payload;
	uchar *buf;
	ulong *fifo;
	uint txsize;

	/*------------------------------------------------------------
	   ���M�f�[�^��FIFO�ɏ���                       
	------------------------------------------------------------*/
	if (epV[ep].demand_size > epV[ep].transferred_size)
	{
		if( (ep!=EP4) && (ep!=EP5))
			payload	  = GET_PAYLOAD_EPn(ep);
		else
			payload	  = GET_PAYLOAD_EP4or5(ep);
		buf       = epV[ep].buf + epV[ep].transferred_size;
		fifo      = GET_WFIFO_ADRS_EPn(ep);
		
		txsize = epV[ep].demand_size - epV[ep].transferred_size;
		
#if defined(USBP_DMA_ENABLE)
#if DMA_ENABLE_TX
		if(ep == EP_TX)
		{
			SET_DMA_CONT0_EP(ep);
			SET_DMA_CONT0_ENABLE();
			if (txsize > payload)
			{
				/* �y�C���[�h�T�C�Y�`�F�b�N */
				SET_EPn_TXCNT(ep, payload);				/* ���M�f�[�^�o�C�g���ݒ� */
				dma_write_fifo(fifo, buf, payload);	
				epV[ep].transferred_size += payload;
			}
			else
			{
				SET_EPn_TXCNT(ep, txsize);	/* ���M�f�[�^�o�C�g���ݒ� */
				dma_write_fifo(fifo, buf, txsize);
				epV[ep].transferred_size += txsize;
			}
			DIS_DMA_CONT0_ENABLE();
		}
		else
#endif
#endif /* defined(USBP_DMA_ENABLE) */
		{
			if (txsize > payload)
			{
				/* �y�C���[�h�T�C�Y�`�F�b�N */
				SET_EPn_TXCNT(ep, payload);				/* ���M�f�[�^�o�C�g���ݒ� */
				write_fifo(fifo, buf, payload);	
	
				epV[ep].transferred_size += payload;
			}
			else
			{
				SET_EPn_TXCNT(ep, txsize);	/* ���M�f�[�^�o�C�g���ݒ� */
				write_fifo(fifo, buf, txsize);
	
				epV[ep].transferred_size += txsize;
			}
	
			/*------------------------------------------------------------
				���M�p�P�b�g���f�B�Z�b�g                                   
			------------------------------------------------------------*/
			SET_PKTRDY(ep);	/* ���M�p�P�b�g���f�B�Z�b�g */
		}
	}

	else
	{
		if(ep != EP0TX)
		{
			/* �S�f�[�^���M��̑��M�p�P�b�g���f�B�����݋֎~ */
			DIS_PKTRDY_INT(ep);
			epV[ep].demand_size = 0;
			(*epV[ep].callback)(epV[ep].buf, epV[ep].transferred_size);	/* ���M�I���ʒm */
		}
		else
		{
			/*
			 * Set Address Request �̗�O����
			 *	Set Address Request �̃A�h���X�ݒ�͑��M�p�P�b�g���f�B��
			 *	���Z�b�g��(ACK��M��)�ɍs��
			 */
			if (GET_ADDRESS_DATA() != usb_status.address)
			{
				SET_ADDRESS_DATA(usb_status.address);
				if(usb_status.address == 0)			/* USB Rev.1.1�Ή� */
				{
					/* �A�h���X"0"���ݒ肳�ꂽ�ꍇ�̓f�t�H���g��X�e�[�g�ɖ߂� */
					CLR_CONFIGBIT_ALL_EPn();		/* ���ׂẴG���h�|�C���g��config�r�b�g�N���A */
					usb_status.configuration = NULL;
					usb_status.dvcstate = DEFAULT_STATE;	/* Device state :DEFAULT */
				}

				else if(usb_status.dvcstate != CONFIGURED_STATE)
				{
					usb_status.dvcstate = ADDRESS_STATE;	/* Device state :ADDRESS */
				}
			}

			/*
				SetFeature��ENDPOINT_HALT�w�莞�̗�O����
				SetFeature��STALL�ݒ�͑��M�p�P�b�g���f�B�̃Z�b�g��ɍs��
			*/
			if(usb_status.stall_req & REQ_STALL)
			{
				usb_status.stall_req &= ~REQ_STALL;
				SET_STALL_EPn(usb_status.stall_req);
			}

			/* �S�f�[�^���M��̑��M�p�P�b�g���f�B�����݋֎~ */
			DIS_EP0TX_PKTRDY_INT();

			/* EP0�̃��b�N�������� */
			CLR_PKTRDY(EP0RX);				/* ��M�p�P�b�g���f�B���Z�b�g */

			/* ���M�f�[�^�� % Payload = 0 �̏ꍇ��NULL�p�P�b�g�쐬 */
			if (device_request.wLength != 0x00)
			{	/* Control Data Transfer */
				SET_PKTRDY(EP0TX);
			}			
		}
	}
}


/*
 ---------------------------------------------------------------------------
   ��M�f�[�^�ǂݍ��݉��w����                                               
 ---------------------------------------------------------------------------
 */
#if defined(USBP_DMA_ENABLE)
int dma_start(int dir, void *device, void *memory, int size);
int dma_stop(int mode);
/*******************************************************************************
	Routine Name:	dma_read_fifo
	Form:			void dma_read_fifo(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO DMA READ �����֐�
******************************************************************************/
static void dma_read_fifo(ulong *fifo, uchar *buf, uint cnt)
{
	if((cnt % 2) != 0)
	{
		cnt += 1;
	}
	dma_start(0, fifo, buf, (int)cnt);
	dma_stop(1);
}
#endif /* defined(USBP_DMA_ENABLE) */

/*******************************************************************************
	Routine Name:	read_fifo
	Form:			void read_fifo(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO READ �����֐�
******************************************************************************/
static void read_fifo(ulong *fifo, uchar *buf, uint cnt)
{
	ulong *buf_long;
	buf_long = (ulong *)((uint)buf & 0xFFFFFFFC);
	while (cnt > 0)
	{
		/* �f�[�^��FIFO����ǂݍ��� */
		if(cnt == 64)
		{
			*buf_long = *fifo;		/* 32bit */ /*  4 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /*  8 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 12 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 16 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 20 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 24 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 28 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 32 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 36 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 40 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 44 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 48 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 52 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 56 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 60 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 64 */
			buf_long++;
			return;
		}
		if(cnt >= 32)
		{
			*buf_long = *fifo;		/* 32bit */ /*  4 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /*  8 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 12 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 16 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 20 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 24 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 28 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 32 */
			buf_long++;
			cnt = cnt - 32;
		}
		if(cnt >= 16)
		{
			*buf_long = *fifo;		/* 32bit */ /*  4 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /*  8 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 12 */
			buf_long++;
			*buf_long = *fifo;		/* 32bit */ /* 16 */
			buf_long++;
			cnt = cnt - 16;
		}
		if(cnt > 0)
		{
			*buf_long = *fifo;		/* 32bit */
			buf_long++;

			if ( cnt > 3 )
				cnt = cnt - (uint)4;
			else
				cnt = 0;
		}
	}
}


/*
 ---------------------------------------------------------------------------
   ���M�f�[�^�������݉��w����                                               
 ---------------------------------------------------------------------------
 */
#if defined(USBP_DMA_ENABLE)

/*******************************************************************************
	Routine Name:	dma_write_fifo
	Form:			void dma_write_fifo(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO DMA WRITE �����֐�
******************************************************************************/

static void dma_write_fifo(ulong *fifo, uchar *buf, uint cnt)
{
	if((cnt % 2) != 0)
	{
		cnt += 1;
	}
	dma_start(1, fifo, buf, (int)cnt);
	dma_stop(1);

}
#endif /* defined(USBP_DMA_ENABLE) */

/*******************************************************************************
	Routine Name:	write_fifo
	Form:			void write_fifo(void)
	Parameters:		����
	Return value:	����
	Description:	FIFO WRITE �����֐�
******************************************************************************/
static void write_fifo(ulong *fifo, uchar *buf, uint cnt)
{
	ulong *buf_long;
	buf_long = (ulong *)((uint)buf & 0xFFFFFFFC);
	while(cnt > 0)
	{
		/* �f�[�^��FIFO�֏������� */
		if(cnt == 64)
		{
			*fifo = *buf_long;		/* 32bit */ /*  4 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /*  8 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 12 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 16 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 20 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 24 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 28 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 32 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 36 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 40 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 44 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 48 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 52 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 56 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 60 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 64 */
			buf_long++;
			cnt -= 64;
		}
		if(cnt >= 32)
		{
			*fifo = *buf_long;		/* 32bit */ /*  4 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /*  8 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 12 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 16 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 20 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 24 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 28 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 32 */
			buf_long++;
			cnt -= 32;
		}
		if(cnt >= 16)
		{
			*fifo = *buf_long;		/* 32bit */ /*  4 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /*  8 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 12 */
			buf_long++;
			*fifo = *buf_long;		/* 32bit */ /* 16 */
			buf_long++;
			cnt -= 16;
		}
		if(cnt > 0)
		{
			*fifo = *buf_long;		/* 32bit */ /*  4 */
			buf_long++;
			
			if ( cnt > 3 )
				cnt = cnt - (uint)4;
			else
				cnt = 0;
		}
	}
}


/* End of file */

