/*******************************************************************************
    usbp_bulk.c
    JOB60842�T���v���v���O���� 
    USB�y���t�F�����o���N���[�v�o�b�O�h���C�o���[�`���Q


    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "config.h"
#include "usbp.h"
#include "usbp_class.h"
#include "usbp_api.h"


/*----------------------------------------------------------------------------*/
/*�O���[�o���ϐ���`*/
#ifdef USB_BUFFER_ADDRESS
  #define BULKBUF_SIZE	(USB_BUFFER_SIZE/4)
  uchar	*buf1 = (uchar *)USB_BUFFER_ADDRESS;
  uchar	*buf2 = (uchar *)USB_BUFFER_ADDRESS+USB_BUFFER_SIZE/4;
  uchar	*buf3 = (uchar *)USB_BUFFER_ADDRESS+USB_BUFFER_SIZE/2;
  uchar	*buf4 = (uchar *)USB_BUFFER_ADDRESS+((USB_BUFFER_SIZE/4)*3);
#else
  #define BULKBUF_SIZE	(1024)
  uchar	buf1[BULKBUF_SIZE];		/* �f�[�^����M�o�b�t�@ */
  uchar	buf2[BULKBUF_SIZE];		/* �f�[�^����M�o�b�t�@ */
  uchar	buf3[BULKBUF_SIZE];		/* �f�[�^����M�o�b�t�@ */
  uchar	buf4[BULKBUF_SIZE];		/* �f�[�^����M�o�b�t�@ */
#endif

uchar 	*buf_rx;				/* �f�[�^��M�o�b�t�@�|�C���^ */
uchar 	*buf_tx;				/* �f�[�^���M�o�b�t�@�|�C���^ */
uchar 	*buf_rx2;				/* �f�[�^��M�o�b�t�@�|�C���^ */
uchar 	*buf_tx2;				/* �f�[�^���M�o�b�t�@�|�C���^ */
uint 	send_cnt;
uint 	recv_cnt;
uint 	send_cnt2;
uint 	recv_cnt2;

#define INT_BUFFER_SIZE 16
uchar	buf_int[INT_BUFFER_SIZE] = {0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF};

uchar 	ready_nullpkt_xfer = 0;	/* Null�p�P�b�g���M�����������t���O */

/*----------------------------------------------------------------------------*/
/*�v���g�^�C�v�錾*/
static void bulk_rx(uchar *buf, ulong size);
static void bulk_tx(uchar *buf, ulong size);
static void bulk_rx2(uchar *buf, ulong size);
static void bulk_tx2(uchar *buf, ulong size);
static void interrup_tx(uchar *buf, ulong size);

/*******************************************************************************
	Routine Name:	usbp_bulk_init
	Form:			void usbp_bulk_init(uchar interface, uchar alternate)
	Parameters:		uchar	interface Interface�ԍ�
					uchar	alternate Alternate�ԍ�
	Return value:	����
	Description:	�G���h�|�C���g�̐ݒ�󋵂ɂ��R�[���o�b�N�֐��̐ݒ���s���B

******************************************************************************/
void usbp_bulk_init(uchar interface, uchar alternate)
{
	if(interface != 0)
		return;
	if(alternate != 0)
		return;
	/*------------------------------------------------------------
	   BULK�p�G���h�|�C���g�Ɋւ��鏉��������                     
	------------------------------------------------------------*/
	buf_rx = buf1;	/* ��M�p�o�b�t�@�|�C���^�ݒ� */
	buf_tx = buf2;	/* ���M�p�o�b�t�@�|�C���^�ݒ� */
	buf_rx2 = buf3;	/* ��M�p�o�b�t�@�|�C���^�ݒ� */
	buf_tx2 = buf4;	/* ���M�p�o�b�t�@�|�C���^�ݒ� */

	send_cnt = 0;
	recv_cnt = 0;
	send_cnt2 = 0;
	recv_cnt2 = 0;

	/* BULK OUT �G���h�|�C���g�ݒ� */
	usbp_set_trans_callback(EP_RX, bulk_rx);	/* �R�[���o�b�N�֐��ݒ� */
	usbp_rx_data(buf_rx, EP_RX, 64);		/* ��M���� */

	/* BULK IN �G���h�|�C���g�ݒ� */
	usbp_set_trans_callback(EP_TX, bulk_tx);	/* �R�[���o�b�N�֐��ݒ� */


	/* BULK OUT �G���h�|�C���g�ݒ� */
	usbp_set_trans_callback(EP_RX2, bulk_rx2);	/* �R�[���o�b�N�֐��ݒ� */
	usbp_rx_data(buf_rx2, EP_RX2, 64);		/* ��M���� */

	/* BULK IN �G���h�|�C���g�ݒ� */
	usbp_set_trans_callback(EP_TX2, bulk_tx2);	/* �R�[���o�b�N�֐��ݒ� */
	

	/* Interrupt IN �G���h�|�C���g�ݒ� */
	usbp_set_trans_callback(EP_INT, interrup_tx);	/* �R�[���o�b�N�֐��ݒ� */
	usbp_tx_data(buf_int, EP_INT, EPINT_PLD);		/* ���M���� */
#if defined(USBP_DEBUG_PRINT)
	sio_printf("BULK ENDPOINT INITIALIZED.\n");
#endif
}


/*******************************************************************************
	Routine Name:	bulk_rx
	Form:			static void bulk_rx(uchar *buf, ulong size)
	Parameters:		unsigned char *buf - �o�b�t�@�|�C���^
					unsigned long size - �T�C�Y
	Return value:	����
	Description:	BULK OUT Endpoint�p�R�[���o�b�N�֐�

******************************************************************************/
static void bulk_rx(uchar *buf, ulong size)
{
	/*
	** ��M�f�[�^������C���M�҂��f�[�^�������ꍇ
	*/
	if (size > 0)
	{
		uchar *tmp;
		recv_cnt +=  size;

		if(recv_cnt > 0 && (send_cnt == 0))
		{
			send_cnt = recv_cnt;
			tmp = buf_tx;
			buf_tx = buf_rx;
			buf_rx = tmp;
			usbp_tx_data(buf_tx, EP_TX, send_cnt);
			usbp_rx_data(buf_rx, EP_RX, 64);
			recv_cnt = 0;
#if defined(USBP_DEBUG_PRINT)
			sio_printf("RX = %08X\n",send_cnt);
#endif
			return;
		}
		else
		{
			/*
			** ��M�f�[�^���o�b�t�@�T�C�Y�𒴂��Ȃ��l��
			*/
			if ((uint)(buf-buf_rx)+size+64 > BULKBUF_SIZE)
			{
				usbp_rx_data(buf_rx, EP_RX, 64);
				/* �ȑO�Ɏ�M�����f�[�^�͏������܂� */
			}
			else
			{
				usbp_rx_data((buf + size), EP_RX, 64);
			}
		}
	}
}


/*******************************************************************************
	Routine Name:	bulk_tx
	Form:			static void bulk_tx(uchar *buf, ulong size)
	Parameters:		unsigned char *buf - �o�b�t�@�|�C���^
					unsigned long size - �T�C�Y
	Return value:	����
	Description:	BULK IN Endpoint�p�R�[���o�b�N�֐�

******************************************************************************/
static void bulk_tx(uchar *buf, ulong size)
{
	uchar *tmp;

	send_cnt = 0;	/* ���M�f�[�^���N���A */

	if(recv_cnt > 0)
	{
		send_cnt = recv_cnt;

		tmp = buf_tx;
		buf_tx = buf_rx;
		buf_rx = tmp;

		usbp_tx_data(buf_tx, EP_TX, send_cnt);
		usbp_rx_data(buf_rx, EP_RX, 64);

		recv_cnt = 0;
#if defined(USBP_DEBUG_PRINT)
			sio_printf("TX = %08X\n",send_cnt);
#endif
	}

}


/*******************************************************************************
	Routine Name:	bulk_rx2
	Form:			static void bulk_rx2(uchar *buf, ulong size)
	Parameters:		unsigned char *buf - �o�b�t�@�|�C���^
					unsigned long size - �T�C�Y
	Return value:	����
	Description:	BULK OUT Endpoint�p�R�[���o�b�N�֐�

******************************************************************************/
static void bulk_rx2(uchar *buf, ulong size)
{
	/*
	** ��M�f�[�^������C���M�҂��f�[�^�������ꍇ
	*/
	if (size > 0)
	{
		uchar *tmp;
		recv_cnt2 +=  size;

		if(recv_cnt2 > 0 && (send_cnt2 == 0))
		{
			send_cnt2 = recv_cnt2;
			tmp = buf_tx2;
			buf_tx2 = buf_rx2;
			buf_rx2 = tmp;
			usbp_tx_data(buf_tx2, EP_TX2, send_cnt2);
			usbp_rx_data(buf_rx2, EP_RX2, 64);
			recv_cnt2 = 0;
#if defined(USBP_DEBUG_PRINT)
			sio_printf("Data Transfer Request.(@RX Call Back2)\t");
			sio_printf("send_cnt = %08X\n",send_cnt2);
#endif
			return;
		}
		else
		{
			/*
			** ��M�f�[�^���o�b�t�@�T�C�Y�𒴂��Ȃ��l��
			*/
			if ((uint)(buf-buf_rx2)+size+64 > BULKBUF_SIZE)
			{
				usbp_rx_data(buf_rx2, EP_RX2, 64);
				/* �ȑO�Ɏ�M�����f�[�^�͏������܂� */
			}
			else
			{
				usbp_rx_data((buf + size), EP_RX2, 64);
			}
		}
	}
}


/*******************************************************************************
	Routine Name:	bulk_tx2
	Form:			static void bulk_tx2(uchar *buf, ulong size)
	Parameters:		unsigned char *buf - �o�b�t�@�|�C���^
					unsigned long size - �T�C�Y
	Return value:	����
	Description:	BULK IN Endpoint�p�R�[���o�b�N�֐�

******************************************************************************/
static void bulk_tx2(uchar *buf, ulong size)
{
	uchar *tmp;

	send_cnt2 = 0;	/* ���M�f�[�^���N���A */

	if(recv_cnt2 > 0)
	{
		send_cnt2 = recv_cnt2;

		tmp = buf_tx2;
		buf_tx2 = buf_rx2;
		buf_rx2 = tmp;

		usbp_tx_data(buf_tx2, EP_TX2, send_cnt2);
		usbp_rx_data(buf_rx2, EP_RX2, 64);

		recv_cnt2 = 0;
#if defined(USBP_DEBUG_PRINT)
			sio_printf("Data Transfer Request.(@TX Call Back2)\t");
			sio_printf("send_cnt = %08X\n",send_cnt2);
#endif
	}

}

/*******************************************************************************
	Routine Name:	interrup_tx
	Form:			static void interrup_tx(uchar *buf, ulong size)
	Parameters:		unsigned char *buf - �o�b�t�@�|�C���^
					unsigned long size - �T�C�Y
	Return value:	����
	Description:	BULK IN Endpoint�p�R�[���o�b�N�֐�

******************************************************************************/

static void interrup_tx(uchar *buf, ulong size)
{
	int i;
	uchar tmp = buf_int[0];

	for(i=0; i<(INT_BUFFER_SIZE-1); i++)
	{
		buf_int[i] = buf_int[i+1];
	}
	buf_int[i] = tmp;
	usbp_tx_data(buf_int, EP_INT, EPINT_PLD);		/* ���M���� */
#if defined(USBP_DEBUG_PRINT)
			sio_printf("EP_INT\n");
#endif
}


/* End of file */
