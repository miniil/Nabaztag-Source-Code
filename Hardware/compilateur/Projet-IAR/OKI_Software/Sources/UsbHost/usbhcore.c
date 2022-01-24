/*******************************************************************************
    usbcore.c
    JOB60842�T���v���v���O����
    �z�X�g�R�A�v���O����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#define DEBUG
#define DEBUG_DES

#include <string.h>
#include "config.h"
#include "bitctrl.h"
#include "usbh.h"
#include "hcd.h"
#include "usbctrl.h"
#include "hcdmem.h"
#include "usbhcfg.h"
#include "otg.h"


/* �N���X�h���C�o���X�g�G���g�� */
DEFINE_LIST_ENTRY(usb_driver_list);

/* �f�o�C�X�A�h���X�}�b�v */
struct _usb_devmap {
	unsigned long map[128 / 32];
}usb_devmap;

/* �z�X�g�h���C�o��������� */
int usbhost_init_status = 0;

/*******************************************************************************
    Routine Name    �Fusbhost_init
    Form            �Fint usbhost_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FUSB�z�X�g�h���C�o������
*******************************************************************************/
int usbhost_init(void)
{
	int ret;


    if( usbhost_init_status == 1 ){
        return 0;
    }

	ret = hcd_init();
	if(ret<0) return ret;

	ret = usbhdriver_init();
	if(ret<0) return ret;

	USBH_MALLOC_INIT();	
    usbhost_init_status = 1;

	return 0;
}


/*******************************************************************************
    Routine Name    �Fusbhost_exit
    Form            �Fvoid usbhost_exit(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�z�X�g�h���C�o�I��
*******************************************************************************/
void usbhost_exit(void)
{


    if( usbhost_init_status == 0 ){
        return;
    }

	usbhost_events();
    hcd_rh_disconnect();
	usbhdriver_exit();
	usbhost_events();
	hcd_exit();
    usbhost_init_status = 0;
}


/*******************************************************************************
    Routine Name    �Fusbhost_events
    Form            �Fvoid usbhost_events(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�z�X�g�h���C�o�C�x���g����
*******************************************************************************/
void usbhost_events(void)
{
	usb_hub_events();
	hcd_rh_events();
}


/*******************************************************************************
    Routine Name    �Fusbh_malloc
    Form            �Fvoid *usbh_malloc(unsigned long size);
    Parameters      �Fsize          �擾�T�C�Y
    Return value    �F�擾�����������ւ̃|�C���^
    Description     �F�������擾�i����RAM�j
*******************************************************************************/
void *usbh_malloc(unsigned long size)
{
	return hcd_malloc(size, INTRAM);
}


/*******************************************************************************
    Routine Name    �Fusbh_malloc_ex
    Form            �Fvoid *usbh_malloc_ex(int size);
    Parameters      �Fsize          �擾�T�C�Y
    Return value    �F�擾�����������ւ̃|�C���^
    Description     �F�������擾�i���[�N�������j
*******************************************************************************/
void *usbh_malloc_ex(unsigned long size)
{
	return hcd_malloc(size, EXTRAM);
}


/*******************************************************************************
    Routine Name    �Fusbh_free
    Form            �Fint usbh_free(void *pt);
    Parameters      �Fpt            �J�����郁�����̃|�C���^
    Return value    �F���s����
    Description     �F�������J��
*******************************************************************************/
int usbh_free(void *pt)
{
	return hcd_free(pt);
}


/*******************************************************************************
    Routine Name    �Fusbh_create_pipe
    Form            �Fvoid *usbh_create_pipe(PDEVINFO dev, uchar type,
                            uchar ep_num, ushort maxpacket, uchar interval);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      type          �]�����
                      ep_num        �G���h�|�C���g�ԍ�
                      maxpacket     MAX�p�P�b�g�T�C�Y
                      interval      �]���Ԋu
    Return value    �FED�ւ̃|�C���^
    Description     �F�p�C�v�̍쐬
*******************************************************************************/
void *usbh_create_pipe(PDEVINFO dev, uchar type, uchar ep_num, ushort maxpacket,
                       uchar interval)
{
	return hcd_create_ed((uchar)dev->dev_speed, (uchar)dev->dev_addr, type,
                          ep_num, maxpacket, interval);
}


/*******************************************************************************
    Routine Name    �Fusbh_update_pipe0
    Form            �Fint usbh_update_pipe0(PDEVINFO dev, ushort maxpacket)
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      maxpacket     MAX�p�P�b�g�T�C�Y
    Return value    �F���s����
    Description     �F�p�C�v�̍X�V�i�G���h�|�C���g0�̂݁j
*******************************************************************************/
int usbh_update_pipe0(PDEVINFO dev, ushort maxpacket)
{
	return hcd_update_ed((PHCD_ED)dev->pipe[0], (uchar)dev->dev_addr, maxpacket);
}


/*******************************************************************************
    Routine Name    �Fusbh_delete_pipe
    Form            �Fvoid usbh_delete_pipe(PDEVINFO dev, uchar ep_num)
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      ep_num        �G���h�|�C���g�ԍ�
    Return value    �F���s����
    Description     �F�p�C�v�̍폜
*******************************************************************************/
void usbh_delete_pipe(PDEVINFO dev, uchar ep_num)
{
	hcd_delete_ed((PHCD_ED)dev->pipe[ep_num]);
	dev->pipe[ep_num] = NULL;
}


/*******************************************************************************
    Routine Name    �Fusbh_control_transfer
    Form            �Fint usbh_control_transfer(PDEVINFO dev, uchar pipe,
                          uchar bRequest, uchar bmRequestType, ushort wValue,
                          ushort wIndex, ushort wLength, void *data);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      pipe          �G���h�|�C���g�ԍ�
                      bRequest      bRequest�l
                      bmRequestType bmRequestType�l
                      wValue        wValue�l
                      wIndex        wIndex�l
                      wLength       wLength�l
                      data          �]���f�[�^�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�R���g���[���]���v��
*******************************************************************************/
int usbh_control_transfer(PDEVINFO dev, uchar pipe,	uchar bRequest,
	uchar bmRequestType, ushort wValue, ushort wIndex, ushort wLength,
	void *data)
{
	URB urb;
	struct usb_setup setup;
	int ret;

	urb.buffer		 = (char *)data;
	urb.length		 = (ulong)wLength;
	urb.timeout 	 = 1000;
	urb.setup		 = &setup;
	urb.dev			 = dev;
	urb.ed			 = dev->pipe[pipe];

	setup.bmRequestType = bmRequestType;
	setup.bRequest   	= bRequest;
	setup.wValue		= wValue;
	setup.wIndex		= wIndex;
	setup.wLength		= wLength;

	urb.callback	 = NULL;

	ret = hcd_transfer_request(&urb);

	return ret;
}


/*******************************************************************************
    Routine Name    �Fusbh_bulk_transfer
    Form            �Fint usbh_bulk_transfer(PDEVINFO dev, uchar pipe,
                          void *buf, ulong size, uchar dma_enable);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      pipe          �G���h�|�C���g�ԍ�
                      buf           �]���f�[�^�ւ̃|�C���^
                      size          �]���f�[�^�T�C�Y
                      dma_enable    DMA�g�p�L��
    Return value    �F���s����
    Description     �F�o���N�]���v��
*******************************************************************************/
int usbh_bulk_transfer(PDEVINFO dev, uchar pipe, void *buf, ulong size, uchar dma_enable)
{
	URB urb;
	int ret;

	urb.buffer		 = (char *)buf;
	urb.length		 = size;
	urb.timeout 	 = 1000;
	urb.setup		 = NULL;
	urb.dev			 = dev;
	urb.ed			 = dev->pipe[pipe];
    urb.dma_enable   = dma_enable;

	urb.callback	 = NULL;

	ret = hcd_transfer_request(&urb);

	return ret;
}


/*******************************************************************************
    Routine Name    �Fusbh_transfer_request
    Form            �Fint usbh_transfer_request(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�]���v�� (�R���g���|���A�o���N�A�C���^�[���v�g)
*******************************************************************************/
int usbh_transfer_request(PURB urb)
{
	int ret;

	ret = hcd_transfer_request(urb);
	if(ret == URB_PENDING) ret = 0;

	return ret;
}


/*******************************************************************************
    Routine Name    �Fusbh_transfer_cancel
    Form            �Fvoid usbh_transfer_cancel(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�]���v���̃L�����Z��
*******************************************************************************/
void usbh_transfer_cancel(PURB urb)
{
	hcd_transfer_cancel(urb);
}


/*******************************************************************************
    Routine Name    �Fusbh_set_address
    Form            �Fint usbh_set_address(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�W�����N�G�X�g SET ADDRESS
*******************************************************************************/
int usbh_set_address(PDEVINFO dev)
{
	return usbh_control_transfer(dev, 0, USB_SET_ADDRESS, USB_DIR_OUT, 
		(uchar)dev->dev_addr, 0, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusbh_get_descriptor
    Form            �Fint usbh_get_descriptor(PDEVINFO dev, uchar type,
                          uchar index, ushort size, void *buf);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      type          �f�B�X�N���v�^���
                      index         �f�B�X�N���v�^INDEX
                      size          �擾�T�C�Y
                      buf           �f�B�X�N���v�^�擾�o�b�t�@�|�C���^
    Return value    �F���s����
    Description     �F�W�����N�G�X�g GET DESCRIPTOR
*******************************************************************************/
int usbh_get_descriptor(PDEVINFO dev, uchar type, uchar index, ushort size, void *buf)
{
	return usbh_control_transfer(dev, 0, USB_GET_DESCRIPTOR, USB_DIR_IN, 
		((type<<8)|index), 0, size, buf);
}


/*******************************************************************************
    Routine Name    �Fusbh_get_configuration
    Form            �Fint usbh_get_configuration(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�W�����N�G�X�g GET CONFIGURATION
*******************************************************************************/
int usbh_get_configuration(PDEVINFO dev)
{
	int ret;
	uchar buf;

	ret = usbh_control_transfer(dev, 0, USB_GET_CONFIGURATION, USB_DIR_IN,
		0, 0, 1, &buf);
	return (int)buf; 
}


/*******************************************************************************
    Routine Name    �Fusbh_set_configuration
    Form            �Fint usbh_set_configuration(PDEVINFO dev, ushort index);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      index         �R���t�B�O���[�V�����l
    Return value    �F���s����
    Description     �F�W�����N�G�X�g SET CONFIGURATION
*******************************************************************************/
int usbh_set_configuration(PDEVINFO dev, ushort index)
{
	return usbh_control_transfer(dev, 0, USB_SET_CONFIGURATION, USB_DIR_OUT,
		index, 0, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusbh_set_feature_dev
    Form            �Fint usbh_set_feature_dev(PDEVINFO dev, ushort feature);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      feature       �@�\�Z���N�^�l
    Return value    �F���s����
    Description     �F�W�����N�G�X�g SET FEATURE
*******************************************************************************/
int usbh_set_feature_dev(PDEVINFO dev, ushort feature)
{
	return usbh_control_transfer(dev, 0, USB_SET_FEATURE, USB_DIR_OUT,
		feature, 0, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusbh_get_descriptor_device
    Form            �Fint usbh_get_descriptor_device(PDEVINFO dev, uchar **pbuf);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      pbuf          �f�o�C�X�f�B�X�N���v�^�ւ̃|�C���^�|�C���^
    Return value    �F���s����
    Description     �F�f�o�C�X�f�B�X�N���v�^�̎擾
*******************************************************************************/
int usbh_get_descriptor_device(PDEVINFO dev, uchar **pbuf)
{
	int ret;

	*pbuf= (uchar *)malloc(sizeof(struct usb_device_descriptor));
	if(!*pbuf) return -1;

	ret = usbh_get_descriptor(dev, USB_DT_DEVICE, 0, 18, *pbuf);
	if(ret<18) return -1;

	return ret;
}


/*******************************************************************************
    Routine Name    �Fusbh_get_descriptor_configuration
    Form            �Fint usbh_get_descriptor_configuration(PDEVINFO dev, uchar **pbuf);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      pbuf          �R���t�B�O�f�B�X�N���v�^�ւ̃|�C���^�|�C���^
    Return value    �F���s����
    Description     �F�R���t�B�M�����[�V�����f�B�X�N���v�^�̎擾
*******************************************************************************/
int usbh_get_descriptor_configuration(PDEVINFO dev, uchar **pbuf)
{
	int ret;
	ushort size;
	ulong temp[2];	/* 8Byte buffer */

	ret = usbh_get_descriptor(dev, USB_DT_CONFIGURATION, 0, 8, temp);
	if(ret<0) return ret;

	size = ((struct usb_configuration_descriptor *)&temp)->wTotalLength;
	*pbuf= (uchar *)malloc(size);
	if(!*pbuf) return -1;

	ret = usbh_get_descriptor(dev, USB_DT_CONFIGURATION, 0, size, *pbuf);
	if(ret<size) return -1;

	return ret;
}


/*******************************************************************************
    Routine Name    �Fusbh_otg_setting
    Form            �Fint usbh_otg_setting(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �FOTG�f�o�C�X�̐ݒ�
*******************************************************************************/
int usbh_otg_setting(PDEVINFO dev)
{
	uchar bmAttributes;
	int ret = 0;


	bmAttributes = dev->descriptor->otg->bmAttributes;

    /* OTG���T�|�[�g? */
	if( (dev->descriptor->otg == NULL) || (hcd_info.rh_device != NULL) ||
        ((bmAttributes & HNP_SUPPORT) == NULL) ){
        return 0;
    }

	ret = usbh_set_feature_dev(dev, OTG_B_HNP_ENABLE);
	if(ret<0){
        return -1;
    }

	return 1;
}


/*******************************************************************************
    Routine Name    �Ferror
    Form            �Fvoid error(int code, int status);
    Parameters      �Fcode          �G���[�R�[�h
                      status        �G���[�X�e�[�^�X
    Return value    �F
    Description     �F�G���[�\��
*******************************************************************************/
void error(int code, int status)
{
	static int usbh_error_code;
	static int usbh_error_status;
	char *err;

	switch(code){
		case 00: err = "out of memory";					break;
		case 10: err = "create pipe0";					break;
		case 11: err = "GET_DESCRIPTOR(pre)";			break;
		case 12: err = "No new device address";			break;
		case 13: err = "SET_ADDRESS";					break;
		case 14: err = "update pipe0(address)";			break;
		case 20: err = "GET_DESCRIPTOR";				break;
		case 21: err = "update pipe0(maxpacket)";		break;
		case 22: err = "GET_DESCRIPTOR(device)";		break;
		case 30: err = "SET_CONFIGRATION";				break;
		case 31: err = "GET_CONFIGRATION";				break;
		case 32: err = "Not configuration value=1";		break;
		case 40: err = "GET_DESCRIPTOR(all)";			break;
		case 41: err = "GET_DESCRIPTOR(device)";		break;
		case 42: err = "GET_DESCRIPTOR(configration)";	break;
		case 50: err = "No class driver.";				break;
		default: err = "Unknown error code.";			break;
	}

	dbg_printf(" USBH: Error!! %s (%d, %d)\n", err, code, status);

	usbh_error_code = code;
	usbh_error_status = status;
}


/*******************************************************************************
    Routine Name    �Fusbh_release_descriptor_all
    Form            �Fvoid usbh_release_descriptor_all(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F
    Description     �F�擾�����S�Ẵf�B�X�N���v�^�̊J��
*******************************************************************************/
void usbh_release_descriptor_all(PDEVINFO dev)
{
	struct usb_configuration_descriptor *configuration;
	struct usb_interface_descriptor *interface; 
	struct usb_endpoint_descriptor *endpoint;
	void * temp;

	if(!dev) return;

	if(!dev->descriptor) return;

	if(dev->descriptor->otg){
		free(dev->descriptor->otg);
	}

	configuration = dev->descriptor->configuration;
	
	while(configuration){
		
		interface = configuration->interface;
		while(interface){

			if(interface->expansion){
				free(interface->expansion);
			}

			endpoint = interface->endpoint;
			while(endpoint){
				temp = endpoint;
				endpoint = endpoint->next;
				free(temp);
			}

			temp = interface;
			interface = interface->next;
			free(temp);
		}				

		temp = configuration;
		configuration = configuration->next;
		free(temp);
	}

	free(dev->descriptor);
	dev->descriptor = NULL;
}


/*******************************************************************************
    Routine Name    �Fusbh_get_descriptor_all
    Form            �Fint usbh_get_descriptor_all(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�S�Ẵf�B�X�N���v�^�̎擾
*******************************************************************************/
int usbh_get_descriptor_all(PDEVINFO dev)
{
	uchar bLength, bDescriptorType;
	struct usb_configuration_descriptor **pconfiguration;
	struct usb_interface_descriptor **pinterface; 
	struct usb_endpoint_descriptor **pendpoint;
	struct usb_otg_descriptor *otg;
	uchar *expansion;
	uchar *ptr, *buf;
	int ret, status;

	if(!dev->descriptor){
		ret = usbh_get_descriptor_device(dev, (uchar **)&dev->descriptor);
		if(ret<dev->descriptor->bLength){
			error(41, 0);
			return NG;
		}
		dev->descriptor->configuration = NULL;
		dev->descriptor->otg = NULL;
	}

	pconfiguration = &dev->descriptor->configuration;
	pinterface = NULL;
	pendpoint = NULL;

	ret = usbh_get_descriptor_configuration(dev, &buf);
	if(ret<0){
		error(42, 0);
		return NG;
	}

	ptr = (uchar *)buf;
	status = 0;

	while(ptr < buf + ret){

		bLength = *ptr;

		if(!bLength) break;

		bDescriptorType = *(ptr+1);

		if(bDescriptorType == USB_DT_CONFIGURATION){

			if(!pconfiguration) break;

			if(*pconfiguration)	pconfiguration = &((*pconfiguration)->next);

			*pconfiguration = (struct usb_configuration_descriptor *)
				malloc(sizeof(struct usb_configuration_descriptor));
			if(!*pconfiguration) break;

			(*pconfiguration)->next = NULL;
			pinterface = &((*pconfiguration)->interface);
			*pinterface = NULL;
			pendpoint = NULL;

			memcpy((ulong *)*pconfiguration, (uchar *)ptr, bLength);
		}

		else if(bDescriptorType == USB_DT_INTERFACE){

			if(!pinterface) break;

			if(*pinterface) pinterface = &((*pinterface)->next);

			*pinterface =(struct usb_interface_descriptor *)
				malloc(sizeof(struct usb_interface_descriptor));
			if(!*pinterface) break;

			(*pinterface)->expansion = NULL;
			(*pinterface)->next = NULL;
			pendpoint = &((*pinterface)->endpoint);
			*pendpoint = NULL;

			memcpy((ulong *)*pinterface, (uchar *)ptr, *ptr);
		}

		else if(bDescriptorType == USB_DT_ENDPOINT){

			if(!pendpoint) break;
			
			if(*pendpoint) pendpoint = &((*pendpoint)->next);

			*pendpoint =(struct usb_endpoint_descriptor *)
				malloc(sizeof(struct usb_endpoint_descriptor));
			if(!*pendpoint) break;

			(*pendpoint)->next = NULL;

			memcpy((ulong *)*pendpoint, (uchar *)ptr, *ptr);
		}

		else if(bDescriptorType == USB_DT_OTG){

			if(dev->descriptor->otg) break;

			otg = (struct usb_otg_descriptor *)
				malloc(sizeof(struct usb_otg_descriptor));
			if(!otg) break;

			dev->descriptor->otg = otg;

			memcpy((void *)otg, (uchar *)ptr, bLength);
		}

		else{
			if(!pinterface) break;
	
			if(!*pinterface) break;

			if((*pinterface)->expansion) break;

			expansion = (uchar *)malloc(bLength);
			if(!expansion) break;

			(*pinterface)->expansion = expansion;

			memcpy((void *)expansion, (uchar *)ptr, *ptr);
		}

		ptr += bLength;
	}

	if(ptr != buf + ret){
		usbh_release_descriptor_all(dev);
		error(40, 0);
		return NG;
	}

	free(buf);
	return OK;
}


#ifdef DEBUG_DES
/*******************************************************************************
    Routine Name    �Fusbh_show_descriptor_device
    Form            �Fvoid usbh_show_descriptor_device(struct usb_device_descriptor *desc);
    Parameters      �Fdesc          �f�o�C�X�f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F
    Description     �F�f�o�C�X�f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_descriptor_device(struct usb_device_descriptor *desc)
{
	dbg_printf("Device:\n");
	dbg_printf(" Length              = %d\n",		desc->bLength);
	dbg_printf(" DescriptorType      = %02X\n",		desc->bDescriptorType);
	dbg_printf(" USB version         = %x.%02X\n", 	desc->bcdUSB >>8, desc->bcdUSB & 0xff);
	dbg_printf(" VID:PID             = %04X:%04X\n",desc->idVendor, desc->idProduct);
	dbg_printf(" MaxPacketSize0      = %02X\n",		desc->bMaxPacketSize0);
	dbg_printf(" NumConfigurations   = %02X\n",		desc->bNumConfigurations);
	dbg_printf(" Device version      = %x.%02X\n", 	desc->bcdDevice >> 8, desc->bcdDevice & 0xff);
	dbg_printf(" Device Class        = %02X:%02X:%02X\n",
		desc->bDeviceClass, desc->bDeviceSubClass,desc->bDeviceProtocol);
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_otg_descriptor
    Form            �Fvoid usbh_show_otg_descriptor(uchar desc[]);
    Parameters      �Fdesc[]        OTG�f�B�X�N���v�^
    Return value    �F
    Description     �FOTG�f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_otg_descriptor(uchar desc[])
{
	con_printf("On-The-Go:\n");
	con_printf(" bLength             = %d\n",		desc[0]);
	con_printf(" bDescriptorType     = %02X\n", 	desc[1]);
	con_printf(" bmAttribute         = %02X",		desc[2]);
	con_printf(" %s", desc[2]&HNP_SUPPORT ? "HNP": "");
	con_printf(" %s", desc[2]&SRP_SUPPORT ? "SRP": "");
	con_printf(" support\n");
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_descriptor_configuration
    Form            �Fvoid usbh_show_descriptor_configuration(struct usb_configuration_descriptor *desc);
    Parameters      �Fdesc          �R���t�B�O�f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F
    Description     �F�R���t�B�O���[�V�����f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_descriptor_configuration(struct usb_configuration_descriptor *desc)
{
	con_printf("Configuration(%d):\n",desc->bConfigurationValue);
	con_printf(" bLength             = %d\n",		desc->bLength);
	con_printf(" bDescriptorType     = %02X\n",		desc->bDescriptorType);
	con_printf(" wTotalLength        = %04X\n",		desc->wTotalLength);
	con_printf(" bNumInterfaces      = %02X\n",		desc->bNumInterfaces);
	con_printf(" bConfigurationValue = %02X\n",		desc->bConfigurationValue);
	con_printf(" iConfiguration      = %02X\n",		desc->iConfiguration);
	con_printf(" bmAttributes        = %02X\n",		desc->bmAttributes);
	con_printf(" bMaxPower            = %dmA\n",	desc->bMaxPower * 2);
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_interface_descriptor
    Form            �Fvoid usbh_show_interface_descriptor(struct usb_interface_descriptor *desc);
    Parameters      �Fdesc          �C���^�t�F�[�X�f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F
    Description     �F�C���^�t�F�[�X�f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_interface_descriptor(struct usb_interface_descriptor *desc)
{
	con_printf(" Alternate Setting(%d-%d):\n", desc->bInterfaceNumber, desc->bAlternateSetting);
	con_printf("  bLength            = %d\n",		desc->bLength);
	con_printf("  bDescriptorType    = %02X\n",		desc->bDescriptorType);
	con_printf("  bInterfaceNumber   = %02X\n",		desc->bInterfaceNumber);
	con_printf("  bAlternateSetting  = %02X\n",		desc->bAlternateSetting);
	con_printf("  bNumEndpoints      = %02X\n",		desc->bNumEndpoints);
	con_printf("  bInterface Class   = %02X:%02X:%02X\n",
		desc->bInterfaceClass, desc->bInterfaceSubClass, desc->bInterfaceProtocol);
	con_printf("  iInterface         = %02X\n", 	desc->iInterface);
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_endpoint_descriptor
    Form            �Fvoid usbh_show_endpoint_descriptor(struct usb_endpoint_descriptor *desc);
    Parameters      �Fdesc          �G���h�|�C���g�f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F
    Description     �F�G���h�|�C���g�f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_endpoint_descriptor(struct usb_endpoint_descriptor *desc)
{
	con_printf("  Endpoint(%d):\n", desc->bEndpointAddress & 0x0F);
	con_printf("   bLength           = %d\n",		desc->bLength);
	con_printf("   bDescriptorType   = %02X\n", 	desc->bDescriptorType);
	con_printf("   bEndpointAddress  = %02X\n", 	desc->bEndpointAddress);
	con_printf("   bmAttributes      = %02X\n", 	desc->bmAttributes);
	con_printf("   wMaxPacketSize    = %04X\n", 	desc->wMaxPacketSize);
	con_printf("   bInterval         = %02X\n", 	desc->bInterval);
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_expansion_descriptor
    Form            �Fvoid usbh_show_expansion_descriptor(uchar desc[]);
    Parameters      �Fdesc[]        �g���f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F
    Description     �F�g���f�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_expansion_descriptor(uchar desc[])
{
	int i;

	con_printf(" Expansion:\n");
	con_printf("  bLength            = %d\n",		desc[0]);
	con_printf("  bDescriptorType    = %02X\n", 	desc[1]);
	con_printf("  bData              =");
	for(i=2; i<desc[0]; i++){
		con_printf(" %02X", desc[i]);
	}
	con_printf("\n");
    mdelay(2);
}


/*******************************************************************************
    Routine Name    �Fusbh_show_descriptor_all
    Form            �Fvoid usbh_show_descriptor_all(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F
    Description     �F�擾�����S�Ẵf�B�X�N���v�^�̕\��
*******************************************************************************/
void usbh_show_descriptor_all(PDEVINFO dev)
{
	struct usb_configuration_descriptor *configuration;
	struct usb_interface_descriptor *interface; 
	struct usb_endpoint_descriptor *endpoint;

	usbh_show_descriptor_device(dev->descriptor);

	configuration = dev->descriptor->configuration;

	if(dev->descriptor->otg){
		usbh_show_otg_descriptor((uchar *)dev->descriptor->otg);
	}

	while(configuration){
		usbh_show_descriptor_configuration(configuration);
		
		interface = configuration->interface;

		while(interface){
			usbh_show_interface_descriptor(interface);

			if(interface->expansion){
				usbh_show_expansion_descriptor((uchar *)interface->expansion);
			}

			endpoint = interface->endpoint;
			while(endpoint){
				usbh_show_endpoint_descriptor(endpoint);
				endpoint = endpoint->next;
			}

			interface = interface->next;
		}				

		configuration = configuration->next;
	}

}
#endif


/*******************************************************************************
    Routine Name    �Fusbh_driver_install
    Form            �Fvoid usbh_driver_install(struct usbh_driver *driver);
    Parameters      �Fdriver            �N���X�h���C�o���ւ̃|�C���^
    Return value    �F
    Description     �F�N���X�h���C�o�̒ǉ�
*******************************************************************************/
void usbh_driver_install(struct usbh_driver *driver)
{
	dbg_printf(" USBH: install driver(%s)\n", driver->name);
	list_add(&driver->driver_list, &usb_driver_list);
}


/*******************************************************************************
    Routine Name    �Fusbh_driver_uninstall
    Form            �Fvoid usbh_driver_uninstall(struct usbh_driver *driver);
    Parameters      �Fdriver            �N���X�h���C�o���ւ̃|�C���^
    Return value    �F
    Description     �F�N���X�h���C�o�̍폜
*******************************************************************************/
void usbh_driver_uninstall(struct usbh_driver *driver)
{
	dbg_printf(" USBH: uninstall driver(%s)\n", driver->name);
	list_del(&driver->driver_list);
}


/*******************************************************************************
    Routine Name    �Fusbh_find_driver
    Form            �Fstatic int usbh_find_driver(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�Ή�����N���X�h���C�o�̌����ƋN��
*******************************************************************************/
static int usbh_find_driver(PDEVINFO dev)
{
	LIST_ENTRY *next = usb_driver_list.Flink;
	struct usbh_driver *driver;
	void *data;
 	
	if (list_empty(&usb_driver_list))
		return NULL;

	while(next != &usb_driver_list) {
		driver = list_struct_entry(next, struct usbh_driver, driver_list);
			
		data = driver->connect(dev);
		if(data){
			dbg_printf(" USBH: found driver(%s)\n", driver->name);
			dev->driver = driver;
			dev->driver_data = data;
			return 0;
		}
		
		next = next->Flink;
	}
	
	return -1;
}


/*******************************************************************************
    Routine Name    �Fusbh_enumeration
    Form            �Fstatic int usbh_enumeration(PDEVINFO dev)
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�G�j�������[�V����
*******************************************************************************/
static int usbh_enumeration(PDEVINFO dev)
{
	int ret, err;
    int hnp_enable = 0;
	uchar temp[8];


	/* �f�t�H���g�p�C�v�쐬 */
	dev->pipe[0] = usbh_create_pipe(dev, USB_CTRL, 0, 8, 0);
	if(!dev->pipe[0]){
		error(10, 0);
		return -1;
	}

	/* �f�o�C�X�f�B�X�N���v�^�̎擾(�擪8�o�C�g�̂�) */
	for(err = 0; err < 3; err++){
		ret = usbh_get_descriptor(dev, USB_DT_DEVICE, 0, 8, temp);
		if(ret==8) break;
		mdelay(20);
	}
	if(ret!=8){
		error(11, ret);
		return -1;
	}

	/* �f�o�C�X�A�h���X���� */
	dev->dev_addr = find_zero_bit(&usb_devmap, 128, 1);
	if (dev->dev_addr < 128) {
		set_bit((uchar)dev->dev_addr , &usb_devmap);
	}else{
		error(12, 0);
		return -1;
	}

	/* �f�o�C�X�A�h���X�̐ݒ� */
	ret = usbh_set_address(dev);
	if(ret<0){
		error(13, ret);
		return -1;
	}

	mdelay(10);
	
	/* �f�t�H���g�p�C�v���p�C�v�O�ɂ��� */
	ret = usbh_update_pipe0(dev, 8);
	if(ret<0){
		error(14, ret);
		return -1;
	}

	/* �f�o�C�X�f�B�X�N���v�^�̎擾(�擪8�o�C�g�̂�) */
	ret = usbh_get_descriptor(dev, USB_DT_DEVICE, 0, 8, temp);
	if(ret<8){
		error(20, ret);
		return -1;
	}

	/* �p�C�v�O�̍ő�p�P�b�g�T�C�Y�̍X�V */
	ret = usbh_update_pipe0(dev, temp[7]);
	if(ret<0){
		error(21, ret);
		return -1;
	}

	/* �f�o�C�X�f�B�X�N���v�^�̎擾 */
	ret = usbh_get_descriptor_device(dev, (uchar **)&dev->descriptor);
	if(ret<dev->descriptor->bLength){
		dev->descriptor = NULL;
		error(22, ret);
		return -1;
	}
	dev->descriptor->configuration = NULL;
	dev->descriptor->otg = NULL;

	/* �S�Ẵf�B�X�N���v�^���擾���� */
	ret = usbh_get_descriptor_all(dev);
	if(ret<0){
		return -1;
	}

#ifdef DEBUG_DES
	usbh_show_descriptor_all(dev);
#endif

    /* OTG�f�o�C�X�̐ݒ� */
	hnp_enable = usbh_otg_setting(dev);
	if( hnp_enable < 0 ){
		return -1;
	}

	/* �N���X�h���C�o�̌��� */
	ret = usbh_find_driver(dev);

    /* OTG�h���C�o�֒ʒm */
    if( hnp_enable == 0 ){
        usbctrl_otg_request( HNP_NOT_SUPPORTED );
    }
    else{
        usbctrl_otg_request( HNP_ENABLE_SET );
    }

	if(ret<0){
		error(50, ret);
		return -1;
	}

	return 0;
}


/*******************************************************************************
    Routine Name    �Fusbh_connect
    Form            �FPDEVINFO usbh_connect(unsigned char speed)
    Parameters      �Fspeed         �f�o�C�X�X�s�[�h
    Return value    �F�f�o�C�X���ւ̃|�C���^
    Description     �F�f�o�C�X�ڑ�������
*******************************************************************************/
PDEVINFO usbh_connect(unsigned char speed)
{
	int ret;

	PDEVINFO dev;

	dbg_printf(" USBH: connect a new device\n");

	/* �f�o�C�X���\���̗̈�擾 */
	dev = (PDEVINFO)malloc(sizeof(DEVINFO));
	if(!dev){
		error(00, 0);
		return NULL;
	}

	/* �f�o�C�X���\���̏����� */
	memset((long *)dev, 0, sizeof(DEVINFO));
	dev->dev_speed = speed;		/* �f�o�C�X�X�s�[�h */

	/* �G�j���~���[�V���� */
	ret = usbh_enumeration(dev);
	if(ret<0){
		con_printf(" USBH: Error!! failed enumeration\n");
		usbh_release_descriptor_all(dev);
		if(dev->pipe[0]){
			usbh_delete_pipe(dev, 0);
		}
	}

	return dev;
}


/*******************************************************************************
    Routine Name    �Fusbh_disconnect
    Form            �Fint usbh_disconnect(PDEVINFO *pdev)
    Parameters      �Fpdev          �f�o�C�X���ւ̃|�C���^�|�C���^
    Return value    �F���s����
    Description     �F�f�o�C�X�ؒf������
*******************************************************************************/
int usbh_disconnect(PDEVINFO *pdev)
{
	unsigned char i;
	PDEVINFO dev;

	dbg_printf(" USBH: disconnect a device\n");

	if(!pdev) return -1;
	dev = *pdev;

	if(!dev) return -1;

	/* �N���X�h���C�o�̐ؒf���� */
	if(dev->driver)
		dev->driver->disconnect(dev);

	/* �擾�����f�B�X�N���v�^�̈�J�� */
	usbh_release_descriptor_all(dev);

	clear_bit((uchar)dev->dev_addr , &usb_devmap);

	/* �擾�����p�C�v�̊J�� */
	for(i=0; i<MAX_PIPE; i++){
		if(dev->pipe[i]){
			usbh_delete_pipe(dev, i);
		}
	}

	/* �f�o�C�X���\���̗̈�J�� */
	free(dev);

	return 0;
}

/* end of file */
