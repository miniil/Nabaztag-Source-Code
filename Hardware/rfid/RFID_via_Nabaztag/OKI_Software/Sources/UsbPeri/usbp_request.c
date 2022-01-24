/*******************************************************************************
    usbp_request.c
    JOB60842�T���v���v���O���� 
    �W���f�o�C�X���N�G�X�g����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "usbp.h"
#include "usbp_api.h"

static void usbp_func_Get_Descriptor_String(Device_Request *device_request_pointer, uchar *buf);

/* local macro functions */
/*
	set_buf_EP0TX()
	Control Read�]���p�o�b�t�@�Ƀf�[�^���Z�b�g����}�N���֐�
	���M�f�[�^���z�X�g����̗v����葽���ꍇ�ɁC�v�����ɍ���
	���ăo�b�t�@�ɃZ�b�g����f�[�^���g�����P�[�g����B
*/
#define	set_buf_EP0TX(_dst,_src,_length,_limit)	\
		{						\
			ushort len = 0;\
			len = _length;			\
			if (len > _limit) len = _limit;		\
			while (len--) *_dst++ = *_src++;		\
		}


/*--------------------------------------
      �G���h�|�C���g�]�������̊m�F      
--------------------------------------*/
	/* Get_Status��recipient�ɃG���h�|�C���g���w�肳�ꂽ�Ƃ�
	  USB�R���t�B�O���[�V�������W�X�^���̓]��������
	  �f�o�C�X���N�G�X�gwIndex���̓]����������v���Ă��邩�m�F����
      �������AEP0�͓]�������̃`�F�b�N�͍s��Ȃ� */
	#define CHK_DIR_WINDEX_AND_CONTROL(ep)\
		(((ep) == EP0) || ((CHK_EPn_HOST_TO_DEVICE(ep)) == \
		(((uchar)device_request_pointer->wIndex) & (DEVICE_to_HOST))))

	/* Set_Interface�ő��M�pFIFO�N���A���s�����߂�
	  USB�R���t�B�O���[�V�������W�X�^���̓]��������
	  Device to Host���m�F���� */
	#define CHK_DIR_DEVICE_TO_HOST(ep)\
		((CHK_EPn_HOST_TO_DEVICE(ep)) == DEVICE_to_HOST)


/*******************************************************************************
	Routine Name:	usbp_func_Clear_Feature
	Form:			void usbp_func_Clear_Feature(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		Device_Request *device_request_pointer:�f�o�C�X���N�G�X�g�̃|�C���^
					uchar *buf:�o�b�t�@�ւ̃|�C���^
	Return value:	�Ȃ�
	Description:	wValue�Ŏw�肳�ꂽFeature���N���A���� 
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Clear Feature                                                            
 ---------------------------------------------------------------------------
   wValue�Ŏw�肳�ꂽFeature���N���A����                                    
                                                                            
     +--------------------+-----------------------------------------------+ 
      wValue                ����                                            
     +--------------------+-----------------------------------------------+ 
      DEVICE_REMOTE_WAKEUP  Remote Wakeup �̏�Ԃ�ێ����Ă���ϐ������Z�b  
                            �g����                                          
     +--------------------+-----------------------------------------------+ 
      ENDPOINT_STALL        wIndex �Ŏw�肳�ꂽ Endpoint Control Register   
                            �� STALL bit ���N���A����                       
     +--------------------+-----------------------------------------------+ 
                                                                            
   (��)bmRequestType�� 00000001B (Interface) �̏ꍇ�͏���������`�̂��ߖ��� 
       ���ł�                                                               
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂ŃA�h���X�E�X�e�[�g�Ɠ����������s��  
   �A�h���X�E�X�e�[�g  :�C���^�t�F�[�X�܂��̓G���h�|�C���g0�ȊO��           
                        �Q�Ƃ����ꍇ�̓��N�G�X�g�E�G���[��Ԃ�              
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Clear_Feature(Device_Request *device_request_pointer, uchar *buf)
{
	bmRequestType recipient = device_request_pointer->bmRequestType & (uchar)REQUEST_RECIPIENT;
	uchar ep = (uchar)(device_request_pointer->wIndex & M_EP_NUM);
	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if(device_request_pointer->wLength != 0	)	/* S990701 USB Rev.1.1�Ή� */
	{	/* --- �G���[���� ---
			1.wLength=0�łȂ�
		*/
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
		case CONFIGURED_STATE:
			if((recipient == DEVICE_RECIPIENT) &&/* Device */
			   (device_request_pointer->wValue == DEVICE_REMOTE_WAKEUP))
			{
				usb_status.remote_wakeup = RESET;
			}
			else if(recipient == INTERFACE_RECIPIENT)
			{														/* Interface */
				/* ����������`�̂��ߖ����� */

				SET_STALL_EP0();			/* STALL bit ON */
			}
			else if((recipient == ENDPOINT_RECIPIENT) &&	/* Endpoint */
					(device_request_pointer->wValue == ENDPOINT_STALL) &&
					(ep < EP_MAX) && (ep_stat[ep] == SET) &&
					CHK_DIR_WINDEX_AND_CONTROL(ep))
			{	/* EP���͈͓� */
				if((usb_status.dvcstate == CONFIGURED_STATE) ||
						/* USB Rev.1.1�Ή� */
					 (ep == EP0))
				{/* ���݂̃f�o�C�X�E�X�e�[�g�ɂ����āA�Q�ƃG���h�|�C���g�͗L�� */
					CLR_EPn_FIFO(ep);		/* FIFO �N���A */
					CLR_STALL_EPn(ep);		/* STALL bit OFF */
					CLR_TOGL_EPn(ep);		/* �g�O���r�b�g���Z�b�g */
				}
				else
				{	/* �A�h���X�E�X�e�[�g�܂��̓f�t�H���g�E�X�e�[�g��
					�G���h�|�C���g0�ȊO���Q�Ƃ��郊�N�G�X�g�ɑ΂��Ă̓G���[��Ԃ�*/
					SET_STALL_EP0();			/* STALL bit ON */

				}
			}
			else
			{
				SET_STALL_EP0();			/* STALL bit ON */
				
			}
			break;
		default:
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Clear_Feature ********************************************************/


/*******************************************************************************
	Routine Name:	usbp_func_Get_Configuration
	Form:			void usbp_func_Get_Configuration(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	���ݐݒ肳��Ă��� Configuration Descriptor �� bConfigurationValue ���  
					���D�ݒ肳��Ă��Ȃ��ꍇ�� 0 ��Ԃ��D
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Get Configuration                                                        
 ---------------------------------------------------------------------------
   ���ݐݒ肳��Ă��� Configuration Descriptor �� bConfigurationValue ���  
   ���D�ݒ肳��Ă��Ȃ��ꍇ�� 0 ��Ԃ��D                                    
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂ŃA�h���X�E�X�e�[�g�Ɠ����������s��  
   �A�h���X�E�X�e�[�g  : 0 ��Ԃ�                                           
   �\���ς݃X�e�[�g    :���ݐݒ肳��Ă���\���� bConfiguration�l��Ԃ�     
 ---------------------------------------------------------------------------
 */
void usbp_func_Get_Configuration(Device_Request *device_request_pointer, uchar *buf)
{
	bmRequestType recipient = device_request_pointer->bmRequestType & (uchar)REQUEST_RECIPIENT;
	Config_Desc *p_c_desc = usb_status.configuration;
	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((recipient != DEVICE_RECIPIENT) ||
	    (device_request_pointer->wValue != 0) ||			/* S990701 USB Rev.1.1�Ή� */
		(device_request_pointer->wIndex != 0) ||
		(device_request_pointer->wLength != 1)	||
		(device_request_pointer->bmRequestType & DEVICE_to_HOST) != DEVICE_to_HOST)
	{	/* --- �G���[���� ---
			0.recipient=DEVICE�łȂ�
			1.wValue=0�łȂ�
			2.wIndex=0�łȂ�
			3.wLength=1�łȂ�
		*/
		
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
			*buf = 0;	/* �A�h���X�E�X�e�[�g����"0"��Ԃ� */
			
			break;
		case CONFIGURED_STATE:
			*buf = p_c_desc->bConfigurationValue;
			
			break;
		default:
			SET_STALL_EP0();			/* STALL bit ON */
			
			return;
	}
	epV[EP0TX].demand_size = 1; /* ���M�f�[�^���ݒ� */

}
/**** Get_Configuration ****************************************************/


/*******************************************************************************
	Routine Name:	usbp_func_Get_Descriptor
	Form:			void usbp_func_Get_Descriptor(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	wValue�� High Byte(Descriptor Index)�Ŏw�肳�ꂽ Descriptor �̐ݒ��Ԃ�
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Get Descriptor                                                           
 ---------------------------------------------------------------------------
   wValue�� High Byte(Descriptor Index)�Ŏw�肳�ꂽ Descriptor �̐ݒ��Ԃ� 
                                                                            
     +--------------+-----------------------------------------------------+ 
      wValue          ����                                                  
     +--------------+-----------------------------------------------------+ 
      DEVICE          Device Descriptor ��Ԃ�                              
     +--------------+-----------------------------------------------------+ 
      CONFIGURATION   Configuration + Interface + Endpoint Descriptor ���  
                      ��                                                    
     +--------------+-----------------------------------------------------+ 
      STRING          String Descriptor ��Ԃ�                              
     +--------------------------------------------------------------------+ 
                                                                            
   �f�t�H���g�E�X�e�[�g:���N�G�X�g�ɉ������������s��                        
   �A�h���X�E�X�e�[�g  :���N�G�X�g�ɉ������������s��                        
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Get_Descriptor(Device_Request *device_request_pointer, uchar *buf)
{
	uchar *p_desc;
	uchar *buf_p = buf;
	uchar DescriptorType;
	uint tmp = (device_request_pointer->wValue >> 8);
	uchar DescriptorIndex = (uchar)(device_request_pointer->wValue);

	uint num;

	ushort i, j, k, l;
	Device_Desc *p_d_desc;
	Config_Desc *p_c_desc;
	Config_if *p_cfg_if;
	Interface_Desc *p_i_desc;
	Endpoint_Desc *p_e_desc;
#if defined(OTG_ENABLE)
	OTG_Desc *p_otg_desc;
#endif
	bmRequestType recipient = device_request_pointer->bmRequestType & (uchar)REQUEST_RECIPIENT;

	DescriptorType = (uchar)tmp;


	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if(((device_request_pointer->bmRequestType & DEVICE_to_HOST) != DEVICE_to_HOST)
	|| (recipient != DEVICE_RECIPIENT) )	
	{	/* --- �G���[���� ---
			1.bmRequest�̕�����0x80�łȂ�
		*/
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch (DescriptorType)
	{
	case DEVICE:
		p_desc = (uchar *)device_descriptor;

		set_buf_EP0TX(buf_p			/* dest */
			,p_desc				/* src */
			,device_descriptor->bLength	/* length */
			,device_request_pointer->wLength);		/* length requested */

		if((device_descriptor->bLength) > (device_request_pointer->wLength))
		{
			num =  (device_request_pointer->wLength);
			
		}
		else
		{
			num =  (device_descriptor->bLength);
			
		}



		epV[EP0TX].demand_size = num;

		break;

	case CONFIGURATION:
		{
			p_d_desc = device_descriptor;
			p_c_desc = p_d_desc->p_CFG_desc;

			if (DescriptorIndex >= device_descriptor->bNumConfigurations)
			{
				SET_STALL_EP0();			/* STALL bit ON */
			}
			else
			{
				/* �Y��Configuratioin Descriptor�܂ňړ� */
				p_c_desc += DescriptorIndex;

				/* InterfaceDescriptor�ւ̃u���b�W */
				p_cfg_if = p_c_desc->p_CFG_if;

				/* Configuration Descriptor�̓��e���o�b�t�@�Ɋi�[ */
				p_desc = (uchar *)p_c_desc;
				for(i=0; i<p_c_desc->bLength; i++)
				{
					*buf_p++ = *p_desc++;
				}

				/* Configuration�������Ă���Interface�����[�v */
				for(i=0; i<p_c_desc->bNumInterfaces; i++)
				{
					p_i_desc = p_cfg_if->p_IF_desc;

					/* Interface Descriptor������AlternateSetting�����[�v */
					for(j=0; j<p_cfg_if->bAlternateSetting; j++)
					{
						p_e_desc = p_i_desc->p_EP_desc;

						/* Interface Descriptor�̓��e���o�b�t�@�Ɋi�[ */
						p_desc = (uchar *)p_i_desc;
						for(k=0; k<p_i_desc->bLength; k++)
						{
							*buf_p++ = *p_desc++;
						}

						/* Interface�������Ă���Endpoint�����[�v */
						for(k=0; k<p_i_desc->bNumEndpoints; k++)
						{
							/* Endpoint Descriptor�̓��e���o�b�t�@�Ɋi�[ */
							p_desc = (uchar *)p_e_desc;
							for(l=0; l<p_e_desc->bLength; l++)
							{
								*buf_p++ = *p_desc++;
							}
							p_e_desc++;
							
						}
						p_i_desc++;
					}
					p_cfg_if++;
				}
/* 
	OTG �f�B�X�N���v�^�́A�Ō�Ƀf�[�^���o���Ƃ��Ď�������B
*/
#if defined(OTG_ENABLE)
				p_cfg_if = p_c_desc->p_CFG_if;
				p_otg_desc = p_cfg_if->p_OTG_desc;
				p_desc = (uchar *)p_otg_desc;
				for(i=0; i< p_otg_desc->bLength; i++)
				{
					*buf_p++ = *p_desc++;
				}
#endif
				/* ���M�f�[�^���z�X�g����̗v����葽���ꍇ�ɁC�v�����ɍ��킹�� */

				if (p_c_desc->wTotalLength > device_request_pointer->wLength)
				{
					epV[EP0TX].demand_size = device_request_pointer->wLength; /* ���M�f�[�^���ݒ� */

				}
				else
				{
					epV[EP0TX].demand_size = p_c_desc->wTotalLength; /* ���M�f�[�^���ݒ� */

				}
			}
		}
		break;
    case STRING:
        {
			usbp_func_Get_Descriptor_String(device_request_pointer, buf);
        }
		break;

	default:
	
		SET_STALL_EP0();			/* STALL bit ON */
		break;
	}
}
/**** Get_Descriptor *******************************************************/


/*******************************************************************************
	Routine Name:	usbp_func_Get_Interface
	Form:			void usbp_func_Get_Interface(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	bInterfaceNumber = wIndex �ƂȂ� Interface Descriptor �̒���             
					���ݐݒ肳��Ă��� bAlternateSetting �l��Ԃ�
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Get Interface                                                            
 ---------------------------------------------------------------------------
   bInterfaceNumber = wIndex �ƂȂ� Interface Descriptor �̒���             
   ���ݐݒ肳��Ă��� bAlternateSetting �l��Ԃ�                            
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂ŃA�h���X�E�X�e�[�g�Ɠ����������s��  
   �A�h���X�E�X�e�[�g  :���N�G�X�g�E�G���[��Ԃ�                            
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Get_Interface(Device_Request *device_request_pointer, uchar *buf)
{
	Config_Desc *p_c_desc = usb_status.configuration;
	Config_if   *p_cfg_if = p_c_desc->p_CFG_if;
	uchar i, status;
	bmRequestType recipient = device_request_pointer->bmRequestType & (uchar)REQUEST_RECIPIENT;

	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wValue != 0) ||					/* S990701 USB Rev.1.1�Ή� */
		(device_request_pointer->wLength != 1) 	||
		 (recipient != INTERFACE_RECIPIENT) ||
		 (device_request_pointer->bmRequestType & DEVICE_to_HOST) != DEVICE_to_HOST )

	{	/* --- �G���[���� ---
			1.wValue=0�łȂ�
			2.wLength=1�łȂ�
		*/
		
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
			SET_STALL_EP0();		/* �\���ς݂łȂ��̂Ń��N�G�X�g�G���[ */
			break;

		case CONFIGURED_STATE:
			status = RESET;

			for (i=0; i<p_c_desc->bNumInterfaces; i++)
			{
				if (p_cfg_if->bInterfaceNumber == device_request_pointer->wIndex)
				{
					*buf = p_cfg_if->currentAlternateSetting;
					status = SET;
					
					break;
				}
				p_cfg_if++;
			}

			/* �w�肳�ꂽInterface Descriptor�����݂������`�F�b�N */
			if (status == SET)
			{

				epV[EP0TX].demand_size = 1; /* ���M�f�[�^���ݒ� */	
			}
			else
			{	/* ���݂��Ȃ��̂Ń��N�G�X�g�E�G���[��Ԃ� */
			
				SET_STALL_EP0();			/* STALL bit ON */
			}

			break;

		default:
		
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Get_Interface ********************************************************/


/*******************************************************************************
	Routine Name:	usbp_func_Get_Status
	Form:			void usbp_func_Get_Status(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	bmRequestType�Ŏw�肳�ꂽ recipiesnt �̃X�e�[�^�X��Ԃ�
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Get Status                                                               
 ---------------------------------------------------------------------------
   bmRequestType�Ŏw�肳�ꂽ recipiesnt �̃X�e�[�^�X��Ԃ�                  
                                                                            
     +----------+---------------------------------------------------------+ 
      DEVICE      Remote Wakeup �̉�/�s�̏�ԁC�d�͋������@��Ԃ�         

     +----------+---------------------------------------------------------+ 
      INTERFACE   0 ��Ԃ�                                                  
     +----------+---------------------------------------------------------+ 
      ENDPOINT    wIndex �Ŏw�肳�ꂽ Endpoint �� STALL ��Ԃ�Ԃ�          
     +----------+---------------------------------------------------------+ 
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂ŃA�h���X�E�X�e�[�g�Ɠ����������s��  
   �A�h���X�E�X�e�[�g  :�C���^�t�F�[�X�܂��̓G���h�|�C���g0�ȊO��           
                        �Q�Ƃ����ꍇ�̓��N�G�X�g�E�G���[��Ԃ�              
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Get_Status(Device_Request *device_request_pointer, uchar *buf)
{
	bmRequestType recipient = (uchar)(device_request_pointer->bmRequestType & REQUEST_RECIPIENT);
	uchar   ep = (uchar)(device_request_pointer->wIndex & M_EP_NUM);
	uchar *buf_p = buf, i;
	Config_Desc *p_c_desc = usb_status.configuration;
	Config_if   *p_cfg_if = p_c_desc->p_CFG_if;

	*buf_p     = 0;
	*(buf_p+1) = 0;

	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wValue != 0) ||			/* S990701 USB Rev.1.1�Ή� */
		(device_request_pointer->wLength != 2)
		|| (device_request_pointer->bmRequestType & DEVICE_to_HOST) != DEVICE_to_HOST)
	{	/* --- �G���[���� ---
			1.wValue=0�łȂ�
			2.wLength=2�łȂ�
			3.bmRequestType�̕�����0x80�łȂ�
		*/
		
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
			if(recipient == DEVICE_RECIPIENT ||
				recipient == INTERFACE_RECIPIENT)
			{
				/* �\���ς݃X�e�[�g�ȊO��DEVICE�
					INTERFACE���w�肳�ꂽ�̂Ń��N�G�X�g�G���[ */
					
				SET_STALL_EP0();
				break;
			}
			if(recipient == ENDPOINT_RECIPIENT && ep != EP0)
			{
				/* EP0�ȊO���w�肳��Ă���̂Ń��N�G�X�g�G���[ */
				SET_STALL_EP0();
				
				break;
			}
		case CONFIGURED_STATE:

			if (recipient == DEVICE_RECIPIENT)
			{													/* Device */
				p_c_desc = usb_status.configuration;

				if(device_request_pointer->wIndex != 0)			/* S990701 USB Rev.1.1�Ή� */
				{	/* --- �G���[���� ---
						1.wIndex=0�łȂ�
					*/
					
					SET_STALL_EP0();
				}

				/* Self Powered */
				if (p_c_desc->bmAttributes & 0x60)
				{
					*buf_p = 1;
				}
				/* Remote Wakeup */
				*buf_p = *buf_p | (usb_status.remote_wakeup << 1);
			}
			else if (recipient == INTERFACE_RECIPIENT)
			{													/* Interface */
				for (i=0; i<p_c_desc->bNumInterfaces; i++)
				{
					/* �w�肳�ꂽ Interface Number ������ Interface Descriptor ��T�� */
					if (p_cfg_if->bInterfaceNumber == device_request_pointer->wIndex)
					{
						break;
					}
					p_cfg_if++;
				}
				if(i >= p_c_desc->bNumInterfaces)
				{
					SET_STALL_EP0();			/* STALL bit ON */	/* Rev.1.1�Ή� */
				}
			}
			else if ((recipient == ENDPOINT_RECIPIENT) ) /* Endpoint */
			{
				if(	ep < EP_MAX && ep_stat[ep] == SET )		/* EP���͈͓� */
				{
					if(	ep == EP0 )
					{	/* �]�������̃`�F�b�N */	/* S990621 */
					/*
					  wIndex�Ŏw�����ꂽEP Control Register�̃X�g�[���r�b�g�̏�Ԃ�Ԃ�
					*/
						if (CHK_STALL_EPn(ep))
						{
							*buf_p = 1;
						}
					}
					else if(CHK_EPn_HOST_TO_DEVICE(ep) 
					== 	((uchar)(device_request_pointer->wIndex) & DEVICE_to_HOST))
					{
						/*
						  wIndex�Ŏw�����ꂽEP Control Register�̃X�g�[���r�b�g�̏�Ԃ�Ԃ�
						*/
						if (CHK_STALL_EPn(ep))
						{
							*buf_p = 1;
						}
					}
					else
					{
						SET_STALL_EP0();			/* STALL bit ON */
					}
				}
				else
				{
						SET_STALL_EP0();			/* STALL bit ON */
						
				}
			}
			else
			{
				SET_STALL_EP0();			/* STALL bit ON */
			}

			epV[EP0TX].demand_size = 2; /* ���M�f�[�^���ݒ� */	
			break;

		default:
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Get_Status ***********************************************************/


/*******************************************************************************
	Routine Name:	usbp_func_Set_Address

	Form:			void usbp_func_Set_Address(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	wValue �Ŏw�肳�ꂽ�A�h���X��ݒ肷��
					�A�h���X�ݒ�� Status Stage �� handshake ��ɍs�����ߕϐ��ɕێ�����
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Set Address                                                              
 ---------------------------------------------------------------------------
   wValue �Ŏw�肳�ꂽ�A�h���X��ݒ肷��                                    
       �A�h���X�ݒ�� Status Stage �� handshake ��ɍs�����ߕϐ��ɕێ�����  
                                                                            
   �f�t�H���g�E�X�e�[�g:���N�G�X�g�ɉ������������s��                        
   �A�h���X�E�X�e�[�g  :���N�G�X�g�ɉ������������s��                        
   �\���ς݃X�e�[�g    :���얢��`�Ȃ̂ŃA�h���X�ύX�������p������??????    
 ---------------------------------------------------------------------------
 */
void usbp_func_Set_Address(Device_Request *device_request_pointer, uchar *buf)
{
	bmRequestType recipient = (uchar)(device_request_pointer->bmRequestType & REQUEST_RECIPIENT);
	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wIndex != 0) ||		/* S990701 USB Rev.1.1�Ή� */
		(device_request_pointer->wLength != 0) ||
		(device_request_pointer->wValue > 127)  ||
		 (recipient != DEVICE_RECIPIENT) )
	{	/* --- �G���[���� ---
			1.wIndex=0�łȂ�
			2.wLength=0�łȂ�
			3.�w��A�h���X�l��127���傫��
		*/
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
		case CONFIGURED_STATE:
			if (device_request_pointer->wValue < 128)
			{
				if((usb_status.dvcstate != CONFIGURED_STATE) ||
					(device_request_pointer->wValue != 0))
				{
					usb_status.address = (uchar)device_request_pointer->wValue;
					
				}
				else
				{/* �\���ς݃X�e�[�g���̃A�h���X�l"0"�̓G���[ */
					SET_STALL_EP0();			/* STALL bit ON */
					
				}
			}
			else
			{
				SET_STALL_EP0();			/* STALL bit ON */
			}
			break;

		default:
		
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Set_Address **********************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Set_Configuration
	Form:			void usbp_func_Set_Configuration(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	wValue �Ŏw�肳�ꂽ bConfigurationValue ������ Configuration Descriptor  
					�̒l��p���Đݒ���s��
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Set Configuration                                                        
 ---------------------------------------------------------------------------
   wValue �Ŏw�肳�ꂽ bConfigurationValue ������ Configuration Descriptor  
   �̒l��p���Đݒ���s��                                                   
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂Ń��N�G�X�g�E�G���[��Ԃ�            
   �A�h���X�E�X�e�[�g  :���N�G�X�g�ɉ������������s��                        
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Set_Configuration(Device_Request *device_request_pointer, uchar *buf)
{
	Config_Desc *p_c_desc = device_descriptor->p_CFG_desc;
	uchar i, status;

	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wIndex != 0) ||				/* S990701 USB Rev.1.1�Ή� */
		(device_request_pointer->wLength != 0) ||
		((device_request_pointer->wValue & 0xff00) != 0) ||
		((device_request_pointer->bmRequestType & DEVICE_to_HOST) == DEVICE_to_HOST))
	{	/* --- �G���[���� ---
			1.wIndex=0�łȂ�
			2.wLength=0�łȂ�
			3.wValue�̏�ʃo�C�g��=0�łȂ�
		*/
		
		SET_STALL_EP0();			/* STALL bit ON */
 		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		
			SET_STALL_EP0();			/* STALL bit ON */
			break;

		case ADDRESS_STATE:
		case CONFIGURED_STATE:
			if (device_request_pointer->wValue == 0)
			{	/* �A�h���X�E�X�e�[�g�Ɉڍs���� */
				/* ���ݒ��Ԃɂ��邽�߂� Configuration Bit OFF */

				CLR_CONFIGBIT_ALL_EPn();		/* ���ׂẴG���h�|�C���g��config�r�b�g�N���A */
				usb_status.configuration = NULL;
				usb_status.dvcstate = ADDRESS_STATE;	/* Device state :ADDRESS */

				/* Endpoint�̗L����Ԃ𖳌��ɕύX */
				for (i=EP1; i<EP_MAX; i++)
					ep_stat[i] = RESET;

				DIS_SOF_INT();							/* SOF�����݂��֎~���� */
#if OTG_ENABLE
				/* On The Go �R���g���[���h���C�o�ɒʒm */
				usbctrl_otg_request(B_UNCONFIGRATION);
#endif

			}
			else
			{
				status = RESET;

				for(i=0; i<device_descriptor->bNumConfigurations; i++)
				{
					if(p_c_desc->bConfigurationValue == device_request_pointer->wValue)
					{
						usb_status.configuration = p_c_desc;
						usb_status.dvcstate = CONFIGURED_STATE;	/* Device state :CONFIGURED */

						/* �Y������ConfigurationDescriptor�̃f�t�H���g�ݒ� */
						device_request_pointer->wValue = 0;
						device_request_pointer->wIndex = 0;
						do {
							usbp_func_Set_Interface(device_request_pointer, buf);  
							device_request_pointer->wIndex++;
						} while (device_request_pointer->wIndex < p_c_desc->bNumInterfaces);
						
						if(CHK_STALL_EPn(EP0))
						{
						/* Set_Interface���s�ɂ��EP0��STALL�����ꍇ�͍\���ς݃X�e�[�g�Ɉڍs���Ȃ� */

							usb_status.configuration = NULL;
							usb_status.dvcstate = ADDRESS_STATE;	/* Device state :ADDRESS */
						}

						status = SET;

						break;
					}

					p_c_desc++;
				}

				/* �w�肳�ꂽConfiguration Descriptor�����݂������`�F�b�N */
				if (status == RESET)
				{
					SET_STALL_EP0();			/* STALL bit ON */
					
				}
#if OTG_ENABLE
				else
				{
					/* On The Go �R���g���[���h���C�o�ɒʒm */
					usbctrl_otg_request(B_CONFIGRATION);
					/* SUSPEND ���荞�݂�L���ɂ���B */
					ENA_SUSPENDED_INT();
				}
#endif
			}
			break;

		default:
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Set_Configuration ****************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Set_Descriptor
	Form:			void usbp_func_Set_Descriptor(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	�z�X�g�� Descriptor �̐ݒ��ǉ��E�ύX����
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Set Descriptor                                                           
 ---------------------------------------------------------------------------
   �z�X�g�� Descriptor �̐ݒ��ǉ��E�ύX����                               
                                                                            
   (��)�I�v�V�����Ȃ̂Ŗ������ł��D                                         
 ---------------------------------------------------------------------------
 */
void usbp_func_Set_Descriptor(Device_Request *device_request_pointer, uchar *buf)
{
	/* �I�v�V�����̂��ߖ����� */
	SET_STALL_EP0();			/* STALL bit ON */
	
}
/**** Set_Descriptor *******************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Set_Feature
	Form:			void usbp_func_Set_Feature(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	wValue �Ŏw�肳�ꂽ Feature ���Z�b�g����
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Set Feature                                                              
 ---------------------------------------------------------------------------
   wValue �Ŏw�肳�ꂽ Feature ���Z�b�g����                                 
                                                                            
     +--------------------+-----------------------------------------------+ 
      wValue                ����                                            
     +--------------------+-----------------------------------------------+ 
      DEVICE_REMOTE_WAKEUP  Remote Wakeup �̏�Ԃ�ێ����Ă���ϐ����Z�b�g  
                            ����                                            
     +--------------------+-----------------------------------------------+ 
      ENDPOINT_STALL        wIndex �Ŏw�肳�ꂽ Endpoint Control Register   
                            �� STALL bit ���Z�b�g����                       
     +--------------------+-----------------------------------------------+ 
                                                                            
   (��)bmRequestType�� 00000001B (Interface) �̏ꍇ�͏���������`�̂��ߖ��� 
       ���ł�                                                               
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂ŃA�h���X�E�X�e�[�g�Ɠ����������s��  
   �A�h���X�E�X�e�[�g  :�C���^�t�F�[�X�܂��̓G���h�|�C���g0�ȊO��           
                        �Q�Ƃ����ꍇ�̓��N�G�X�g�E�G���[��Ԃ�              
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Set_Feature(Device_Request *device_request_pointer, uchar *buf)
{
	bmRequestType recipient = (bmRequestType)(device_request_pointer->bmRequestType & REQUEST_RECIPIENT);
	uchar ep = (uchar)(device_request_pointer->wIndex & M_EP_NUM);

	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wLength != 0) ||
	((device_request_pointer->bmRequestType & DEVICE_to_HOST) == DEVICE_to_HOST))
	{	/* --- �G���[���� ---
			1.wLength=0�łȂ�
		*/
		
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
		case CONFIGURED_STATE:
			if(recipient == DEVICE_RECIPIENT)
			{														/* Device */
				switch((device_request_pointer -> wValue))
				{
					case DEVICE_REMOTE_WAKEUP:
						usb_status.remote_wakeup = SET;
						break;
#if OTG_ENABLE
					case B_HNP_ENABLE:
						/* On The Go �R���g���[���h���C�o�ɒʒm */
						usbctrl_otg_request(B_HNP_ENABLE_SET);
						break;
					case A_HNP_SUPPORT:
						/* On The Go �R���g���[���h���C�o�ɒʒm */
						usbctrl_otg_request(A_HNP_SUPPORT_SET);
						break;
					case A_ALT_HNP_ENABLE:
						/* On The Go �R���g���[���h���C�o�ɒʒm */
						usbctrl_otg_request(A_ALT_HNP_SUPPORT_SET);
						break;
#endif
					default:
						SET_STALL_EP0();			/* STALL bit ON */
						break;
				}
			}
			else if (recipient == INTERFACE_RECIPIENT)
			{														/* Interface */
				/* ����������`�̂��ߖ����� */
				SET_STALL_EP0();			/* STALL bit ON */
				
			}
			else if (recipient == ENDPOINT_RECIPIENT )	/* Endpoint */
			{
				if(	device_request_pointer->wValue == ENDPOINT_STALL)
				{
					if(ep < EP_MAX && ep_stat[ep] == SET)
					{
						if(	CHK_DIR_WINDEX_AND_CONTROL(ep))/* EP���͈͓� */
						{
							if(usb_status.dvcstate == CONFIGURED_STATE || ep == EP0)	
							{	/* ���݂̃f�o�C�X�E�X�e�[�g�ɂ����āA�Q�ƃG���h�|�C���g�͗L�� */
								/* SetFeature�ɑ΂���ACK��HOST�ɕԂ����߁A�����ł�STALL���Ȃ� */
								usb_status.stall_req = (uchar)(REQ_STALL | ep);/* STALL�v�����Z�b�g */
								
							}
							else
							{	/* �A�h���X�E�X�e�[�g�ŃG���h�|�C���g0�ȊO���Q�Ƃ���
								���N�G�X�g�ɑ΂��Ă̓G���[��Ԃ� */
								SET_STALL_EP0();			/* STALL bit ON */
								
							}
						}
						else
						{
							SET_STALL_EP0();			/* STALL bit ON */
							
						}
					}
					else
					{
						SET_STALL_EP0();			/* STALL bit ON */
						
					}
				}
				else
				{
					SET_STALL_EP0();			/* STALL bit ON */
					
				}
			}
			else
			{
				SET_STALL_EP0();			/* STALL bit ON */
				
			}
			break;

		default:
			
			SET_STALL_EP0();			/* STALL bit ON */
			break;
	}
}
/**** Set_Feature **********************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Set_Interface
	Form:			void usbp_func_Set_Interface(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	bInterfaceNumber = wIndex �ƂȂ� Interface Descriptor �̒���             
					bAlternateSetting = wValue �ƂȂ� Descriptor ���ۗL���� Endpoint �̐ݒ�  
					������
******************************************************************************/
/*

 ---------------------------------------------------------------------------
   Set Interface                                                            
 ---------------------------------------------------------------------------
   bInterfaceNumber = wIndex �ƂȂ� Interface Descriptor �̒���             
   bAlternateSetting = wValue �ƂȂ� Descriptor ���ۗL���� Endpoint �̐ݒ�  
   ������                                                                   
                                                                            
   �f�t�H���g�E�X�e�[�g:���얢��`�Ȃ̂Ń��N�G�X�g�E�G���[��Ԃ�            
   �A�h���X�E�X�e�[�g  :���N�G�X�g�E�G���[��Ԃ�                            
   �\���ς݃X�e�[�g    :���N�G�X�g�ɉ������������s��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_Set_Interface(Device_Request *device_request_pointer, uchar *buf)
{
	Config_Desc *p_c_desc = usb_status.configuration;
	Config_if   *p_cfg_if /* = p_c_desc->p_CFG_if */ ;
	uchar i, j, k, status;
	uchar iso_enbl, ep;
	Interface_Desc *p_i_desc, *p_i_desc_configuration = NULL;
	Endpoint_Desc *p_e_desc;

	/* ���N�G�X�g�E�G���[�`�F�b�N */
	if((device_request_pointer->wLength != 0) ||
	 ((device_request_pointer->bmRequestType & DEVICE_to_HOST) == DEVICE_to_HOST))
	{	/* --- �G���[���� ---
			1.wLength=0�łȂ�
		*/
		SET_STALL_EP0();			/* STALL bit ON */
		return;
	}
	p_cfg_if = p_c_desc->p_CFG_if;	/* �\��-IF�u���b�W�����߂� */

	status = RESET;

	switch(usb_status.dvcstate)
	{
		case DEFAULT_STATE:
		case ADDRESS_STATE:
			SET_STALL_EP0();	/* �\���ςłȂ����stall */
			break;

		case CONFIGURED_STATE:
			for (i=0; i<p_c_desc->bNumInterfaces; i++)
			{
				/* �w�肳�ꂽ Interface Number ������ Interface Descriptor ��T�� */
				if (p_cfg_if->bInterfaceNumber == device_request_pointer->wIndex)
				{
					p_i_desc = p_cfg_if->p_IF_desc;
					for (j=0; j<p_cfg_if->bAlternateSetting; j++)
					{
						/* �w�肳�ꂽ AlternateSetting �l������ Descriptor ��T�� */
						if (p_i_desc->bAlternateSetting == device_request_pointer->wValue)
						{
							status = SET;
							p_i_desc_configuration = p_i_desc;
							break;
						}
						p_i_desc++;
					}
					p_i_desc = p_cfg_if->p_IF_desc;
					
					/* Interface Descriptor�����SEP��CONFIGURATION BIT OFF */
					if(status == SET)
					{
						for (j=0; j<p_cfg_if->bAlternateSetting; j++)
						{
							p_e_desc = p_i_desc->p_EP_desc;

							/* Endpoint�̌��� */
							for (k=0; k<p_i_desc->bNumEndpoints; k++)
							{
								ep = (uchar)((p_e_desc->bEndpointAddress) & M_EP_NUM);
								/* CONFIGURATION BIT OFF */
								CLR_CONFIGBIT_EPn(ep);
								/* Endpoint�̐ݒ� */
								ep_stat[k] = RESET;	/* S990723 */
								p_e_desc++;
							}
							p_i_desc++;
						}

						p_e_desc = p_i_desc_configuration->p_EP_desc;
						p_cfg_if->currentAlternateSetting = (uchar)(device_request_pointer->wValue);
						iso_enbl = RESET;	/* ISO�G���h�|�C���g���o�p�ϐ������� */
						for (k=0; k<p_i_desc_configuration->bNumEndpoints; k++)
						{
							ep = (uchar)((p_e_desc->bEndpointAddress) & M_EP_NUM);
							/* �]�������̐ݒ� & CONFIGURATION BIT ON & STALL �r�b�g������ */
							SETINIT_CONFIGBIT_EPn(ep);
							/* �y�C���[�h�T�C�Y�ݒ� */
							SET_PAYLOAD_EPn(ep, p_e_desc->wMaxPacketSize);
							/* �f�[�^�V�[�P���X�g�O���E�r�b�g�̏����� */
							CLR_TOGL_EPn(ep);
							if(CHK_DIR_DEVICE_TO_HOST(ep))
							{ /* �G���h�|�C���g�]��������Device to Host���`�F�b�N */
								/* ���M�pEP��FIFO�N���A */
								CLR_EPn_FIFO(ep);
							}
							ep_stat[ep] = SET;	/* S990723 */
							if((p_e_desc->bmAttributes&0x03) == ISOCHRONOUS)	/* S990720*/
							{
								iso_enbl = SET;			/* ISO�p�G���h�|�C���g���o */
							}			
							p_e_desc++;/* O000427 */
						}

#if (defined(ML60842) || defined(ML60852))
						/* EP���[�h�̐ݒ� */
						if(ep_stat[EP5] == SET)
#if defined(FORCE_5EP_MODE)
							SET_5EP_MODE();				/* 5EP MODE�ݒ� */
#else
							SET_6EP_MODE();				/* 6EP MODE�ݒ� */
#endif
						else
#if defined(FORCE_6EP_MODE)
							SET_6EP_MODE();				/* 6EP MODE�ݒ� */
#else
							SET_5EP_MODE();				/* 5EP MODE�ݒ� */
#endif
#endif /*(defined(ML60842) || defined(ML60852))*/
#if (defined(EP4_ISO_OUT) || defined(EP4_ISO_IN) || defined(EP5_ISO_OUT) || defined(EP5_ISO_IN))	/* S990720 */
						/* �G���h�|�C���g��ISO���w�肳��Ă��邩�m�F��
							�ݒ肳��Ă���ꍇ��SOF�����݂������� */
						if(iso_enbl == SET)
							ENA_SOF_INT();				/* SOF �����݋��� */
						else
							DIS_SOF_INT();				/* SOF �����݋֎~ */
#endif
						(*usb_status.set_interface_callback)((p_cfg_if->bInterfaceNumber),(p_i_desc->bAlternateSetting ));
					}
					break;
				}
				p_cfg_if++;
			}

			/* Endpoint�̐ݒ肪�I���������`�F�b�N */
			if (status == RESET)
			{
				SET_STALL_EP0();			/* STALL bit ON */
				
			}
			break;

		default:
			SET_STALL_EP0();			/* STALL bit ON */
			
			break;
	}
}
/**** Set_Interface ********************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Synch_Frame
	Form:			void usbp_func_Synch_Frame(Device_Request *device_request_pointer, uchar *buf)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	����p�^�[�����J�n�����t���[���ԍ����z�X�g�ɕԂ�
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Synch Frame                                                              
 ---------------------------------------------------------------------------
   ����p�^�[�����J�n�����t���[���ԍ����z�X�g�ɕԂ�                         
 ---------------------------------------------------------------------------
 */
void usbp_func_Synch_Frame(Device_Request *device_request_pointer, uchar *buf)
{
		SET_STALL_EP0();			/* STALL bit ON */
}
/**** Synch_Frame **********************************************************/



/*******************************************************************************
	Routine Name:	usbp_func_Get_Descriptor_String
	Form:			void usbp_func_Get_Descriptor_String(Device_Request *, uchar *)
	Parameters:		Device_Request *device_request
					uchar *buf
	Return value:	�Ȃ�
	Description:	wValue�� High Byte(Descriptor Index)�Ŏw�肳�ꂽ String 
					Descriptor �̐ݒ��Ԃ�
******************************************************************************/
static void usbp_func_Get_Descriptor_String(Device_Request *device_request, uchar *buf)
{
	uint i;
	uchar string_length = 0;
	const uchar *pointer;
    uchar DescriptorIndex = (uchar)(device_request->wValue);
	if( DescriptorIndex == 0x00)
	{
	    *buf++ = string_desc[0].bLength;
	    *buf++ = string_desc[0].bDescriptorType;
		pointer = (const uchar *)(string_desc[0].string);
	    for(i = 0; i < string_desc[0].bLength-2; i++)
	    {
			*buf++ = *pointer;
			pointer++;
		}
		
        /* Data will be truncated when the requested data size is less
           than prepared. */
		if ( string_desc[0].bLength> device_request->wLength)
			epV[EP0TX].demand_size = device_request->wLength; /* ���M�f�[�^���ݒ� */
		else
			epV[EP0TX].demand_size = string_desc[0].bLength; /* ���M�f�[�^���ݒ� */
	}
	else
	{
		if((device_request->wIndex) == 0x0409)
		{
			switch( DescriptorIndex )
			{
				case 0x01:
				case 0x02:
				case 0x03:
				case 0x04:
					string_length = *buf++ = string_desc[DescriptorIndex].bLength;
					*buf++ = string_desc[DescriptorIndex].bDescriptorType;
					pointer = (const uchar *)(string_desc[DescriptorIndex].string);
					for(i = 0; i < string_desc[DescriptorIndex].bLength-2 ; i++)
					{
						*buf++ = *pointer;
						pointer++;
					}
 	        		 break;
	        	default:
					SET_STALL_EP0();            /* STALL bit ON */
	    			break;
			}
			if ( string_length> device_request->wLength)
				epV[EP0TX].demand_size = device_request->wLength; /* ���M�f�[�^���ݒ� */
			else
				epV[EP0TX].demand_size = string_length; /* ���M�f�[�^���ݒ� */
		}
		else
		{
			SET_STALL_EP0();            /* STALL bit ON */
		}
	}
}


/*******************************************************************************
	Routine Name:	usbp_func_stall
	Form:			void usbp_func_stall(void)
	Parameters:		�Ȃ�
	Return value:	�Ȃ�
	Description:	��`�O�̃��N�G�X�g��STALL�������s���ꍇ�ɌĂяo��
******************************************************************************/
/*
 ---------------------------------------------------------------------------
   Stall �����p�̊֐�                                                       
 ---------------------------------------------------------------------------
   ��`�O�̃��N�G�X�g��STALL�������s���ꍇ�ɌĂяo��                        
 ---------------------------------------------------------------------------
 */
void usbp_func_stall(void)
{
		SET_STALL_EP0();			/* STALL bit ON */
}

/* End of file */
