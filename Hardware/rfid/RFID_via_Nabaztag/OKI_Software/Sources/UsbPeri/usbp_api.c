/*******************************************************************************
    usbp_api.c
    JOB60842�T���v���v���O���� 
    API�֐�

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "usbp.h"


/*
 ---------------------------------------------------------------------------
   �_�~�[�R�[���o�b�N�֐�                                                   
 ---------------------------------------------------------------------------
 */
static void dummy_cbf(uchar *buf, uint transferred_size);
static void dummy_cbf_reset(void);
void dummy_cbf_for_set_interface(uchar interface, uchar alternate);


/*******************************************************************************
	Routine Name:	usbp_init
	Form:			int usbp_init(void)
	Parameters:		�Ȃ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�y���t�F�����h���C�o�̏��������s��
******************************************************************************/
int usbp_init(Device_Desc	*device_desc)
{
#if defined(PERI_TEST)
	PULLUP_OFF();
#endif /*defined(PERI_TEST)*/
	/*------------------------------------------------------------
	   Control Write Transfer �p�G���h�|�C���g�\����              
	------------------------------------------------------------*/
	epV[EP0RX].transferred_size	= 0;
	epV[EP0RX].demand_size	= 0;
	epV[EP0RX].buf		= (uchar *)cont_buf;
	epV[EP0RX].callback	= dummy_cbf;
	epV[EP0RX].demand_null	= 0;

	/*------------------------------------------------------------
	   �G���h�|�C���g�P�p�\����                                   
	------------------------------------------------------------*/
	epV[EP1].transferred_size	= 0;
	epV[EP1].demand_size	= 0;
	epV[EP1].buf		= (uchar *)NULL;
	epV[EP1].callback	= dummy_cbf;
	epV[EP1].demand_null	= 0;

	/*------------------------------------------------------------
	   �G���h�|�C���g�Q�p�\����                                   
	------------------------------------------------------------*/
	epV[EP2].transferred_size	= 0;
	epV[EP2].demand_size	= 0;
	epV[EP2].buf		= (uchar *)NULL;
	epV[EP2].callback	= dummy_cbf;
	epV[EP2].demand_null	= 0;

	/*------------------------------------------------------------
	   �G���h�|�C���g�R�p�\���� (Interrupt�]����p)               
	------------------------------------------------------------*/
	epV[EP3].transferred_size	= 0;
	epV[EP3].demand_size	= 0;
	epV[EP3].buf		= (uchar *)NULL;
	epV[EP3].callback	= dummy_cbf;
	epV[EP3].demand_null	= 0;

	/*------------------------------------------------------------
	   �G���h�|�C���g�S�p�\����                                   
	------------------------------------------------------------*/
	epV[EP4].transferred_size	= 0;
	epV[EP4].demand_size	= 0;
	epV[EP4].buf		= (uchar *)NULL;
	epV[EP4].callback	= dummy_cbf;
	epV[EP4].demand_null	= 0;

	/*------------------------------------------------------------
	   �G���h�|�C���g�T�p�\����                                   
	------------------------------------------------------------*/
	epV[EP5].transferred_size	= 0;
	epV[EP5].demand_size	= 0;
	epV[EP5].buf		= (uchar *)NULL;
	epV[EP5].callback	= dummy_cbf;
	epV[EP5].demand_null	= 0;

	/*------------------------------------------------------------
	   Control Read Transfer �p�G���h�|�C���g�\����               
	------------------------------------------------------------*/
	epV[EP0TX].transferred_size= 0;
	epV[EP0TX].demand_size	= 0;
	epV[EP0TX].buf		= (uchar *)cont_buf;
	epV[EP0TX].callback	= dummy_cbf;
	epV[EP0TX].demand_null	= 0;

	/*------------------------------------------------------------
	   Endpoint0�̐ݒ�                                            
	------------------------------------------------------------*/
	/* �����l�s���STALL�r�b�g�̃N���A */
	CLR_STALL_EP0();

	/*------------------------------------------------------------
	   �e��X�e�[�^�X�ϐ��̏�����                                 
	------------------------------------------------------------*/
	usb_status.configuration = NULL;
	usb_status.reset_assert_callback    = dummy_cbf_reset;
	usb_status.reset_deassert_callback  = dummy_cbf_reset;
	usb_status.set_interface_callback   = dummy_cbf_for_set_interface;
	usb_status.remote_wakeup = 0;
	usb_status.address       = 0;
	usb_status.dvcstate      = DEFAULT_STATE; /* Device state: DEFAULT */
	usb_status.stall_req     = 0;

	/*------------------------------------------------------------
       USB�f�o�C�X�ȓd�ݒ�                                        
	------------------------------------------------------------*/
	#ifdef ENA_PW_DWN_MODE
		ENA_POWER_DOWN();
	#endif
	
	/*------------------------------------------------------------
       USB�f�o�C�X�f�B�X�N���v�^�̐ݒ�                            
	------------------------------------------------------------*/
	device_descriptor = device_desc;
	
	
	/*------------------------------------------------------------
       �G���h�|�C���g�X�e�[�^�X�̐ݒ�                            
	------------------------------------------------------------*/
	ep_stat[EP0] = SET;
	
	/*------------------------------------------------------------
	   �����ݐ��䏉����                                           
	       �Z�b�g�A�b�v���f�B������                               
	       USB�o�X���Z�b�g������                                  
	       �T�X�y���f�b�h�X�e�[�g������                           
	------------------------------------------------------------*/
	ENA_SETUP_BUSRES_SUSPEND_INT();
	
#if defined(PERI_TEST)
	/* D+ �v���A�b�v */
	PULLUP_ON();
#endif /*defined(PERI_TEST)*/
	
	return(E_OK);
}


/*******************************************************************************
	Routine Name:	usbp_tx_data
	Form:			int usbp_tx_data(uchar *buf, uchar ep, uint size, long time)
	Parameters:		uchar *buf	���M�f�[�^���i�[���ꂽ�o�b�t�@�ւ̃|�C���^          
					uchar ep	���M�p Endpoint                                     
					uint size	���M�f�[�^��                                        
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�f�[�^�o�b�t�@�̃|�C���^���G���h�|�C���g���M�����n���h���ɁA
					�ݒ肵�āA���M�p�P�b�g���f�B���荞�݂�������B
******************************************************************************/
int usbp_tx_data(uchar *buf, uchar ep, uint size)
{
/* 2003_02_04 */
/* �f�[�^�]�������ƃG���h�|�C���g�ԍ����m�F����B*/
	if((ep > EP0RX) && (ep <= EP0TX))
	{
		if(ep != EP0TX)
		{
			if(CHK_EPn_HOST_TO_DEVICE(ep) != DEVICE_to_HOST)
			{
				return(E_NG);
			}
		} 
	}
	else
	{
		return(E_NG);
	}
/* 2003_02_04 */
	if (epV[ep].demand_size != 0) return(E_NG);
	epV[ep].buf = buf; /* ���M�p�o�b�t�@�|�C���^�ݒ� */
	epV[ep].demand_size = size; /* ���M�f�[�^���ݒ� */
	epV[ep].transferred_size = 0; /* ���M�f�[�^���������� */
	ENA_PKTRDY_INT(ep); /* ���M�p�P�b�g���f�B�����݋��� */
	return(E_OK);
}


/*******************************************************************************
	Routine Name:	usbp_rx_data
	Form:			int usbp_rx_data(uchar *buf, uchar ep, uint size, long time)
	Parameters:		uchar *buf	��M�f�[�^���i�[����o�b�t�@�ւ̃|�C���^          
					uchar ep	��M�p Endpoint                                     
					uint size	��M�f�[�^��                                        
	Return value:	�Ȃ�
	Description:	�f�[�^�o�b�t�@�̃|�C���^���G���h�|�C���g��M�����n���h���ɁA
					�ݒ肵�āA��M�p�P�b�g���f�B���荞�݂�������B
******************************************************************************/
int usbp_rx_data(uchar *buf, uchar ep, uint size)
{
/* 2003_02_04 */
/* �f�[�^�]�������ƃG���h�|�C���g�ԍ����m�F����B*/
	if(ep < EP0TX)
	{
		if(ep != EP0RX)
		{
			if(CHK_EPn_HOST_TO_DEVICE(ep) == DEVICE_to_HOST)
			{
				return(E_NG);
			}
		} 
	}
	else
	{
		return(E_NG);
	}
/* 2003_02_04 */
	epV[ep].buf = buf; /* ��M�p�o�b�t�@�|�C���^�ݒ� */
	epV[ep].demand_size = size; /* ���M�f�[�^���ݒ� */
	epV[ep].transferred_size = 0; /* ��M�f�[�^���������� */
	ENA_PKTRDY_INT(ep); /* ���M�p�P�b�g���f�B�����݋��� */
	return(E_OK);
}


/*******************************************************************************
	Routine Name:	usbp_set_trans_callback
	Form:			ER usbp_set_trans_callback(uchar ep, void (*func)(uchar, uint))
	Parameters:		uchar ep				Endpoint�̎w��
					void (*func)(uchar)	callback�֐��ւ̃|�C���^
	Return value:	���E_OK
	Description:	�f�[�^��M�I�����A�܂��̓f�[�^���M�����̂��߂̃R�[���o�b�N�֐�
					��ݒ肷��B
******************************************************************************/
int usbp_set_trans_callback(uchar ep, void (*func)(uchar *buf, ulong transferred_size))
{
/* 2003_02_04 */
/* ep���͈͊O�ł������ꍇ */
	if(ep > EP0TX)
	{
		return(E_OK);
	}
	epV[ep].callback = func;
	return(E_OK);
}


/*******************************************************************************
	Routine Name:	usbp_busreset_assert_callback
	Form:			int usbp_busreset_assert_callback(void *func(void))
	Parameters:		void (*func)(void)	callback�֐��ւ̃|�C���^
	Return value:	���펞�@E_OK
	Description:	USB�o�X���Z�b�g�A�T�[�g�v���̂��߂̃R�[���o�b�N�֐�
					��ݒ肷��B
******************************************************************************/
int usbp_busreset_assert_callback(void (*func)(void))
{
	usb_status.reset_assert_callback = func;
	return E_OK;
}



/*******************************************************************************
	Routine Name:	usbp_busreset_deassert_callback
	Form:			int usbp_busreset_deassert_callback(void *func(void))
	Parameters:		void (*func)(void)	callback�֐��ւ̃|�C���^
	Return value:	���펞�@E_OK
	Description:	USB�o�X���Z�b�g�f�A�T�[�g�v���̂��߂̃R�[���o�b�N�֐�
					��ݒ肷��B
******************************************************************************/
int usbp_busreset_deassert_callback(void (*func)(void))
{
	usb_status.reset_deassert_callback = func;
	return E_OK;

}

/*******************************************************************************
	Routine Name:	usbp_int_enable
	Form:			ER usbp_int_enable(uchar ep)
	Parameters:		uchar ep	Endpoint�ԍ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�p�P�b�g���f�B���荞�݂�������B
******************************************************************************/
int usbp_int_enable(uchar ep)
{
	/* �p�P�b�g���f�B�����݋��� */
	if (ep == EP1 || ep == EP2 || ep == EP3 || ep == EP4 || ep == EP5)
	{
		ENA_PKTRDY_INT(ep);/* ���M�p�P�b�g���f�B�����݋��� */
		return(E_OK);
	}
	else
	{
		return(E_NG);
	}
}

/*******************************************************************************
	Routine Name:	usbp_int_disable
	Form:			ER usbp_int_disable(uchar ep)
	Parameters:		uchar ep	Endpoint�ԍ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�p�P�b�g���f�B���荞�݂��֎~����B
******************************************************************************/
int usbp_int_disable(uchar ep)
{
	/* �p�P�b�g���f�B�����݋��� */
	if (ep == EP1 || ep == EP2 || ep == EP3 || ep == EP4 || ep == EP5)
	{
		DIS_PKTRDY_INT(ep);/* ���M�p�P�b�g���f�B�����݋��� */
		return(E_OK);
	}
	else
	{
		return(E_NG);
	}
}

/*******************************************************************************
	Routine Name:	usbp_remote_wakeup
	Form:			ER usbp_remote_wakeup(void)
	Parameters:		�Ȃ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�o�X��Ƀ����[�g�E�F�C�N�A�b�v�M�����o�͂���B
******************************************************************************/
int usbp_remote_wakeup(void)
{
	int  status = E_NG;

	if (usb_status.remote_wakeup == SET)
	{
		SET_WAKEUP();
		status = E_OK;
	}

	return(status);
}

/*******************************************************************************
	Routine Name:	usbp_cfg_status
	Form:			ER usbp_cfg_status(Config_Desc **desc)
	Parameters:		Config_Desc **desc�@���\����Configuration Descriptor�ւ�
					�|�C���^���i�[���邽�߂̃|�C���^
	Return value:	���펞	���݂�Configuration Descriptor��bConfigration Value
					�G���[	-1
	Description:	�f�o�C�X�̍\�������擾����B
******************************************************************************/
signed char usbp_cfg_status(Config_Desc **desc)
{
	signed char status = -1;
	*desc = usb_status.configuration;
	if (*desc != NULL)
		status = (signed char)((*desc)->bConfigurationValue);
	return status;
}

/*******************************************************************************
	Routine Name:	usbp_alt_status
	Form:			ER usbp_alt_status(uchar interface)
	Parameters:		uchar interface�@�C���^�[�t�F�[�X�ԍ�
	Return value:	���펞	�w�肵���C���^�[�t�F�[�X�i���o�[��AlternateSetting�l
					�G���[	-1
	Description:	�w�肵���C���^�[�t�F�[�X�i���o�[��AlternateSetting�l���擾����B
******************************************************************************/
signed char usbp_alt_status(bInterfaceNumber interface)
{
	char i;
	signed char status = -1;

	if (usb_status.configuration != NULL)
	{
		Config_if *p_cfg_if = usb_status.configuration->p_CFG_if;

		for (i=0; i<(usb_status.configuration)->bNumInterfaces; i++)
		{
			if (p_cfg_if->bInterfaceNumber == interface)
			{
				status = (signed char)(p_cfg_if->currentAlternateSetting);
				break;
			}

			p_cfg_if++;
		}
	}
	return status;
}


/*******************************************************************************
	Routine Name:	usbp_exit
	Form:			ER usbp_exit(void)
	Parameters:		�Ȃ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	USBP�h���C�o���I������B
******************************************************************************/
int usbp_exit(void)
{
	/* ���荞�݂��֎~���āA�h���C�o����𒆎~����B*/
	/*------------------------------------------------------------
	   �����ݐ��䏉����                                           
	       �Z�b�g�A�b�v���f�B�����݂̂݋�����B
			�n�[�h�E�F�A�̏������                               
	------------------------------------------------------------*/
	write_reg32(INTENBL, (read_reg32(INTENBL) & (B_SETUP_RDY_INT)));
	/*------------------------------------------------------------
	   �e��X�e�[�^�X�ϐ��̏�����                                 
	------------------------------------------------------------*/
	usb_status.configuration = NULL;
	usb_status.reset_assert_callback    = dummy_cbf_reset;
	usb_status.reset_deassert_callback  = dummy_cbf_reset;
	usb_status.set_interface_callback   = dummy_cbf_for_set_interface;
	usb_status.remote_wakeup = 0;
	usb_status.address       = 0;
	usb_status.dvcstate      = DEFAULT_STATE; /* Device state: DEFAULT */
	usb_status.stall_req     = 0;
	PULLUP_OFF();
	return E_OK;
}

/*******************************************************************************
	Routine Name:	usbp_set_callback_set_interface
	Form:			ER usbp_set_callback_set_interface(void (*func)( uchar, uchar ))
	Parameters:		void (*func)( uchar, uchar )	callback�֐��ւ̃|�C���^
	Return value:	���E_OK
	Description:	SetInterface�ɂ����Interface�ݒ肪�s�Ȃ�ꂽ���Ƃ�
					�A�v���P�[�V�����ɒʒm���邽�߂̊֐���ݒ肷��B
******************************************************************************/
int usbp_set_callback_set_interface (void (*func)( uchar, uchar ))
{
	usb_status.set_interface_callback = func;
	return E_OK;
}


/*
 ---------------------------------------------------------------------------
   �_�~�[�R�[���o�b�N�֐�                                                   
 ---------------------------------------------------------------------------
 */
static void dummy_cbf(uchar *buf, uint transferred_size){
	;
}

static void dummy_cbf_reset(void)
{
	;
}

void dummy_cbf_for_set_interface(uchar interface, uchar alternate)
{
	;
}


