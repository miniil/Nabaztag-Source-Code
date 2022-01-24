/*******************************************************************************
    okijob.c
    JOB60842�T���v���v���O����
    �z�X�gJOB�N���X�h���C�o���[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#define DEBUG

#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "usbh.h"

#define OKIJOB_MAX		1	/* �ڑ��\��JOB�{�[�h�� */

#ifndef DMA_ENABLE
  #define DMA_ENABLE	1
#endif
/* DMA_ENABLE==0 �f�[�^�]����DMA���g�p���Ȃ� */
/* DMA_ENABLE==1 �f�[�^�]����DMA���g�p����   */

/******************************************************************************/
/* �h���C�o�ŗL��� */
struct okijob {
	struct usbh_device_info	*dev;	/*�f�o�C�X�f�[�^*/
	short used;
	short number;
};

/* �F�������f�o�C�X�̃f�o�C�X�f�[�^�e�[�u�� */
static struct okijob okijob_table[OKIJOB_MAX];


/*******************************************************************************
    Routine Name    �Fusb_okijob_connect
    Form            �Fstatic void *usb_okijob_connect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �FJOB���ւ̃|�C���^
    Description     �FOKI JOB�ڑ�����
*******************************************************************************/
static void *usb_okijob_connect(PDEVINFO dev)
{
	struct usb_interface_descriptor *interface;
	struct usb_endpoint_descriptor *endpoint;
	int number;
    int ret;

	if(!dev) return NULL;
	if(!dev->descriptor) return NULL;

	if(dev->descriptor->idVendor != 0x04D7 && dev->descriptor->idVendor != 0x070A) return NULL;
	if(dev->descriptor->idProduct != 0x1BD9 && dev->descriptor->idProduct != 0x4012) return NULL;
	if(!dev->descriptor->configuration) return NULL;

	interface = dev->descriptor->configuration->interface;
	if(interface->bInterfaceClass != 0xFF) return NULL;
	if(interface->bInterfaceSubClass != 0xFF) return NULL;
	if(interface->bInterfaceProtocol != 0xFF) return NULL;

	endpoint = interface->endpoint;
	if(endpoint->bEndpointAddress != 0x01) return NULL;
	if(endpoint->bmAttributes  != 0x02) return NULL;

	endpoint = endpoint->next;
	if(endpoint->bEndpointAddress != 0x82) return NULL;
	if(endpoint->bmAttributes != 0x02) return NULL;

	endpoint = endpoint->next;
	if(endpoint->bEndpointAddress != 0x83) return NULL;
	if(endpoint->bmAttributes != 0x03) return NULL;

	ret = usbh_set_configuration(dev, 1);
	if(ret<0){
		return NULL;
	}

	endpoint = interface->endpoint;
	dev->pipe[1] = usbh_create_pipe(dev, endpoint->bmAttributes, 
		endpoint->bEndpointAddress, endpoint->wMaxPacketSize, endpoint->bInterval);
	if(!dev->pipe[1]) return NULL;
 
	endpoint = endpoint->next;
	dev->pipe[2] = usbh_create_pipe(dev, endpoint->bmAttributes, 
		endpoint->bEndpointAddress, endpoint->wMaxPacketSize, endpoint->bInterval);
	if(!dev->pipe[2]) return NULL;

	endpoint = endpoint->next;
	dev->pipe[3] = usbh_create_pipe(dev, endpoint->bmAttributes, 
		endpoint->bEndpointAddress, endpoint->wMaxPacketSize, endpoint->bInterval);
	if(!dev->pipe[3]) return NULL;

	number = 0;
	while(okijob_table[number].dev){
		number++;
		if(number >= OKIJOB_MAX)
			return NULL;
	}

	okijob_table[number].dev = dev;

	dbg_printf("OKI JOB\n");

	return &okijob_table[number];
}


/*******************************************************************************
    Routine Name    �Fusb_okijob_disconnect
    Form            �Fstatic void usb_okijob_disconnect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F
    Description     �FOKI JOB�ؒf����
*******************************************************************************/
static void usb_okijob_disconnect(PDEVINFO dev)
{
	struct okijob *okijob = (struct okijob *)dev->driver_data;

	okijob->dev = NULL;
	dev->driver_data = NULL;
	dev->driver = NULL;
}


/******************************************************************************/
/* �f�o�C�X�h���C�o�[�C���f�b�N�X*/
static struct usbh_driver usb_okijob_driver = {
	"okijob",
	usb_okijob_connect,
	usb_okijob_disconnect,
};


/*******************************************************************************
    Routine Name    �Fusb_okijob_init
    Form            �Fint usb_okijob_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FOKI JOB������
*******************************************************************************/
int usb_okijob_init(void)
{
	short i;

	/*okijov_table�̏�����*/
	for(i=0; i<OKIJOB_MAX; i++){
		okijob_table[i].dev = NULL;
		okijob_table[i].used = 0;
		okijob_table[i].number = i;
	}

	usbh_driver_install(&usb_okijob_driver);
	return OK;
}


/*******************************************************************************
    Routine Name    �Fusb_okijob_exit
    Form            �Fvoid usb_okijob_exit(void);
    Parameters      �F
    Return value    �F
    Description     �FOKI JOB�I��
*******************************************************************************/
void usb_okijob_exit(void)
{
	int i;

	/*okijov_table�̍폜*/
	for(i=0; i<OKIJOB_MAX; i++){
		if(okijob_table[i].dev){
			usbh_disconnect(&okijob_table[i].dev);
		}
	}

	usbh_driver_uninstall(&usb_okijob_driver);
}


/*******************************************************************************
    Routine Name    �Fokijob_open
    Form            �Fvoid *okijob_open(void);
    Parameters      �F
    Return value    �FJOB�n���h���ւ̃|�C���^
    Description     �FOKI JOB�n���h���擾
*******************************************************************************/
void *okijob_open(void)
{
	int number;

	for(number = 0; number < OKIJOB_MAX; number++){

	 	if(!okijob_table[number].dev) continue;	/*�f�o�C�X�����݂��邩�H*/

		if(okijob_table[number].used) continue;	/*�f�o�C�X���g�p����Ă��Ȃ����H*/

		okijob_table[number].used = 1;

		return &okijob_table[number];

	}

	return NULL;
}


/*******************************************************************************
    Routine Name    �Fokijob_close
    Form            �Fint okijob_close(void * pt);
    Parameters      �Fpt            JOB�n���h���ւ̃|�C���^
    Return value    �F���s����
    Description     �FOKI JOB�n���h���擾
*******************************************************************************/
int okijob_close(void * pt)
{
	struct okijob * okijob = (struct okijob *)pt;

	if(!pt) return NG;

	okijob->used = 0;

	return OK;
}


/*******************************************************************************
    Routine Name    �Fokijob_number
    Form            �Fint okijob_number(void * pt);
    Parameters      �Fpt            JOB�n���h���ւ̃|�C���^
    Return value    �FJOB�ԍ�
    Description     �FOKI JOB�ԍ��擾
*******************************************************************************/
int okijob_number(void * pt)
{
	struct okijob * okijob = (struct okijob *)pt;
	return okijob->number;
}


/*******************************************************************************
    Routine Name    �Fokijob_bulk
    Form            �Fint okijob_bulk(void * pt, unsigned char pipe,
                                 void * data, ulong len);
    Parameters      �Fpt            JOB�n���h���ւ̃|�C���^
                      pipe          �p�C�v�ԍ�
                      data          �]���f�[�^�ւ̃|�C���^
                      len           �]���f�[�^�T�C�Y
    Return value    �F���s����
    Description     �FOKI JOB�ԍ��擾
*******************************************************************************/
int okijob_bulk(void * pt, unsigned char pipe, void * data, unsigned long len)
{
	struct okijob *okijob = (struct okijob *)pt;
	struct usbh_device_info *dev = (struct usbh_device_info *)okijob->dev;
	int ret;

	if (!okijob || !okijob->dev || !okijob->used)
		return NG;

	ret = usbh_bulk_transfer(dev, pipe, data, len, DMA_ENABLE);

	if (ret < 0) {
		dbg_printf(" okijob: bulk failed dev=%d ep=%d len=%u ret=%d\n",
			(uchar)dev->dev_addr, pipe, len, ret);
		return ret;
	}

	return ret;
}

/* End of File */
