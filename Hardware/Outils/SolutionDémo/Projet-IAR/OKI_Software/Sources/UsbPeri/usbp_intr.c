/*******************************************************************************
    usbp_intr.c
    JOB60842�T���v���v���O���� 
    �����ݏ����֐�
    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "usbp.h"
#include "ml60842.h"
#include "config.h"

/*****************************************************************************
	�O�����荞�ݏ���														 
*****************************************************************************/
/*******************************************************************************
	Routine Name:	usbp_interrupt
	Form:			void usbp_interrupt(void)
	Parameters:		����
	Return value:	����
	Description:	USB �y���t�F�������荞�ݏ���
******************************************************************************/
void usbp_interrupt(void)
{
	ushort status;
	int i;
	do{
		status = (ushort)(read_reg32(INTSTAT));

		if (status & B_SOF_INT)
		{	/* SOF���荞�݃X�e�[�^�X */
			/* SOF�����݃X�e�[�^�X�N���A */
			CLR_B_SOF_STATE();	/* �v���N���A */
		}

		else if (status & B_EP1PKTRDY_INT)
		{	/* EP1�p�P�b�g���f�B */
			if(CHK_EPn_HOST_TO_DEVICE(EP1) == DEVICE_to_HOST)
			{
				write_FIFO(EP1);
			}
			else
			{
				read_FIFO(EP1);
			}
		}

		else if (status & B_EP2PKTRDY_INT)
		{	/* EP2�p�P�b�g���f�B */	
			if(CHK_EPn_HOST_TO_DEVICE(EP2) == DEVICE_to_HOST)
			{
				write_FIFO(EP2);
			}
			else
			{
				read_FIFO(EP2);
			}
		}

		else if (status & B_EP3PKTRDY_INT)
		{	/* EP3�p�P�b�g���f�B */	
			if(CHK_EPn_HOST_TO_DEVICE(EP3) == DEVICE_to_HOST)
			{
				write_FIFO(EP3);
			}
			else
			{
				read_FIFO(EP3);
			}
		}

		else if (status & B_EP4PKTRDY_INT)
		{	/* EP4�p�P�b�g���f�B */	
			if(CHK_EPn_HOST_TO_DEVICE(EP4) == DEVICE_to_HOST)
			{
				write_FIFO(EP4);
			}
			else
			{
				read_FIFO(EP4);
			}
		}

		else if (status & B_EP5PKTRDY_INT)
		{	/* EP5�p�P�b�g���f�B */	
			if(CHK_EPn_HOST_TO_DEVICE(EP5) == DEVICE_to_HOST)
			{
				write_FIFO(EP5);
			}
			else
			{
				read_FIFO(EP5);
			}
		}

		else if (status & B_SETUP_RDY_INT)
		{	/* �Z�b�g�A�b�v���f�B */
			usbp_Decode_Request();
		}

		else if (status & B_EP0RXPKTRDY_INT)
		{	/* EP0��M�p�P�b�g���f�B */
			read_FIFO(EP0RX);
		}

		else if (status & B_EP0TXPKTRDY_INT)
		{	/* EP0���M�p�P�b�g���f�B */
			write_FIFO(EP0TX);
		}

		if (status & B_BUS_RESET_INT)
		{	/* USB�o�X���Z�b�g */
			/* USB�o�X���Z�b�g�X�e�[�^�X�N���A */
			CLR_BUS_RESET_STATE();

			/*------------------------------------------------------------
				�e��X�e�[�^�X�ϐ��̏�����								
			------------------------------------------------------------*/
			usb_status.configuration = NULL;
			usb_status.remote_wakeup = 0;
			usb_status.address = 0;
			usb_status.dvcstate = DEFAULT_STATE;	/* Device state :DEFAULT */
			usb_status.stall_req = 0;
			
			/*------------------------------------------------------------
				EP�ʐM�f�[�^�Ǘ��ϐ��̏�����						
			------------------------------------------------------------*/
			for(i = 0; i <= EP_MAX + 1; i++)
			{
				epV[i].transferred_size = 0;	/* �ʐM�f�[�^���� */
				epV[i].demand_size  = 0;		/* �ʐM�v���f�[�^�� */
			}

			/*------------------------------------------------------------
				USB�o�X���Z�b�g�ʒm											
			------------------------------------------------------------*/
			(*usb_status.reset_assert_callback)();
#if OTG_ENABLE
				/* On The Go �R���g���[���h���C�o�ɒʒm */
#if defined(PERI_TEST)
/*			usbctrl_otg_request(B_UNCONFIGRATION);*/
#else
			usbctrl_otg_request(B_UNCONFIGRATION);
#endif /* defined(PERI_TEST) */
#endif
#if defined(USBP_DEBUG_PRINT)
			sio_printf("USB BUS RESET ASSERT.\n");
#endif
		}

		else if (status & B_BUS_RESET_DES_INT)
		{	/* USB�o�X���Z�b�g�E�f�A�T�[�g */

			/* �o�X���Z�b�g�E�f�A�T�[�g���̏��������� */
			 CLR_BUS_RESET_DES_STATE();	/* �v���N���A */
			(*usb_status.reset_deassert_callback)();
#if defined(USBP_DEBUG_PRINT)
			sio_printf("USB BUS RESET DEASSERT.\n");
#endif
		}

		else if (status & B_SUSPENDED_STATE_INT)
		{	/* �T�X�y���f�b�h�X�e�[�g */
			CLR_SUSPENDED_STATE();	/* �v���N���A */
#if OTG_ENABLE
				/* On The Go �R���g���[���h���C�o�ɒʒm */
#if defined(PERI_TEST)
/*			usbctrl_otg_request(BUS_SUSPENDED);*/
#else
			usbctrl_otg_request(BUS_SUSPENDED);
#endif /* defined(PERI_TEST) */
#endif
#if defined(USBP_DEBUG_PRINT)
			sio_printf("USB BUS SUSPENDED.\n");
#endif
		}

		else if (status & B_AWAKE_INT)
		{	/* �f�o�C�X�A�E�F�C�N�X�e�[�g */
			/* AWAKE���������� */
			CLR_AWAKE_STATE();			/* �v���N���A */
#if defined(USBP_DEBUG_PRINT)
			sio_printf("USB BUS WAKE UP.\n");
#endif
		}

	}while(status);

}

/* End of file */

