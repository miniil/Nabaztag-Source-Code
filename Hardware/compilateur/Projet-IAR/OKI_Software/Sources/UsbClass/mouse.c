/*******************************************************************************
    mouse.c
    JOB60842�T���v���v���O����
    �z�X�g�}�E�X�N���X�h���C�o���[�`�� (EASY��)

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#define DEBUG

#include <string.h>
#include "config.h"
#include "bitctrl.h"
#include "usbh.h"

#define USB_MOUSE_MAX	1

struct usb_mouse {
	int number;
	PDEVINFO dev;
	signed char *data;
	int dx, dy, dz;
	ulong buttons;
    ulong detect_flag;
	URB urb;
} *usb_mouse_table[USB_MOUSE_MAX];


#define buttons(s, idx, btn) (((s) & (1 << (idx))) ? set_bit((idx), (btn)) : \
												   clear_bit((idx), (btn)))


/*******************************************************************************
    Routine Name    �Fmouse_status
    Form            �Fint mouse_status(int *mouse_status);
    Parameters      �Fmouse_status      �}�E�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �FUSB�}�E�X ��Ԏ擾
*******************************************************************************/
int mouse_status(int *mouse_status)
{

    /* �}�E�X�ڑ���Ԕ��� */
    if( (usb_mouse_table[0] == NULL) || (usb_mouse_table[0]->detect_flag == 0) ){
        return NG;
    }

    /* �}�E�X��Ԏ擾 */
    mouse_status[0] = usb_mouse_table[0]->dx;
    mouse_status[1] = usb_mouse_table[0]->dy;
    mouse_status[2] = usb_mouse_table[0]->dz;
    mouse_status[3] = (usb_mouse_table[0]->buttons & 0x00000001);
    mouse_status[4] = ((usb_mouse_table[0]->buttons >> 0x1) & 0x00000001);
    mouse_status[5] = ((usb_mouse_table[0]->buttons >> 0x2) & 0x00000001);

    usb_mouse_table[0]->detect_flag = 0;

    return OK;
}


/*******************************************************************************
    Routine Name    �Fusb_mouse_event
    Form            �Fstatic void usb_mouse_event(struct usb_mouse *mouse);
    Parameters      �Fmouse         �}�E�X���ւ̃|�C���^
    Return value    �F
    Description     �FUSB�}�E�X �f�[�^����
*******************************************************************************/
static void usb_mouse_event(struct usb_mouse *mouse)
{

	mouse->dx += mouse->data[1];					/* X */
	mouse->dy += mouse->data[2];					/* Y */
	mouse->dz += mouse->data[3];					/* Z */
	buttons(mouse->data[0], 0, &mouse->buttons);	/* LEFT */
	buttons(mouse->data[0], 1, &mouse->buttons);	/* RIGHT */
	buttons(mouse->data[0], 2, &mouse->buttons);	/* MIDDLE */

}


/*******************************************************************************
    Routine Name    �Fusb_mouse_callback
    Form            �Fstatic void usb_mouse_callback(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �FUSB�}�E�X �R�[���o�b�N
*******************************************************************************/
static void usb_mouse_callback(PURB urb)
{
	struct usb_mouse *mouse;

	if (urb->status<0){
		/* �G���[������͖������ɂȂ�B�K�v�Ȃ�΃G���[�������������� */
		return;
	}

	mouse = (struct usb_mouse *)(urb->dev->driver_data);

	usb_mouse_table[0]->detect_flag = 1;
	usb_mouse_event(mouse);

	usbh_transfer_request(urb);
}


/*******************************************************************************
    Routine Name    �Fusbh_set_idle
    Form            �Fint usbh_set_idle(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F���s����
    Description     �F�N���X���N�G�X�g Set Idle
*******************************************************************************/
int usbh_set_idle(PDEVINFO dev)
{
	return usbh_control_transfer(dev, 0, USB_SET_IDLE, 
		USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0, 0, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusb_mouse_connect
    Form            �Fstatic void *usb_mouse_connect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F�}�E�X���ւ̃|�C���^
    Description     �FUSB�}�E�X �ڑ�����
*******************************************************************************/
static void *usb_mouse_connect(PDEVINFO dev)
{
	struct usb_interface_descriptor *interface;
	struct usb_endpoint_descriptor *endpoint;
	int i;
	struct usb_mouse *mouse;
    int ret;

	if(!dev) return NULL;
	if(!dev->descriptor) return NULL;
 	if(!dev->descriptor->configuration) return NULL;
	if(dev->descriptor->bNumConfigurations != 1) return NULL;

	interface = dev->descriptor->configuration->interface;
	if(interface->bInterfaceClass != 3) return NULL;
	if(interface->bInterfaceSubClass != 1) return NULL;
	if(interface->bInterfaceProtocol != 2) return NULL;
	if(interface->bNumEndpoints != 1) return NULL;

	endpoint = interface->endpoint;
	if( (endpoint->bEndpointAddress & 0x80) == 0 ) return NULL;
	if(endpoint->bmAttributes != 3) return NULL;
	if(endpoint->wMaxPacketSize > 8) return NULL;

	ret = usbh_set_configuration(dev, 1);
	if(ret<0){
		return NULL;
	}

	dev->pipe[1] = usbh_create_pipe(dev, endpoint->bmAttributes, endpoint->bEndpointAddress, 
		endpoint->wMaxPacketSize, endpoint->bInterval);
	if(!dev->pipe[1]) return NULL;

	for(i=0; i<USB_MOUSE_MAX; i++){
		if(!usb_mouse_table[i]) break;
	}
	if(i == USB_MOUSE_MAX) return NULL;

	mouse = (struct usb_mouse *)malloc(sizeof(struct usb_mouse));
	if(!mouse) return NULL;
	memset(mouse, 0, sizeof(struct usb_mouse));
  	usb_mouse_table[i] = mouse;
	mouse->number = i;
	mouse->dev = dev;
	dev->driver_data = mouse;
	
	mouse->data = (signed char *)usbh_malloc(8);
	if (!mouse->data){
		free(mouse);
	  	usb_mouse_table[mouse->number] = NULL;
		return NULL;
	}

	dbg_printf("USB mouse\n");

	usbh_set_interrupt_urb(&mouse->urb, dev, 1, mouse->data, endpoint->wMaxPacketSize, usb_mouse_callback);
	if(usbh_transfer_request(&mouse->urb)){
		usbh_free(mouse->data);
		return NULL;
	}

	return mouse;
}


/*******************************************************************************
    Routine Name    �Fusb_mouse_disconnect
    Form            �Fstatic void usb_mouse_disconnect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F
    Description     �FUSB�}�E�X �ؒf����
*******************************************************************************/
static void usb_mouse_disconnect(PDEVINFO dev)
{
	struct usb_mouse *mouse = (struct usb_mouse *)dev->driver_data;

	usbh_transfer_cancel(&mouse->urb);
	usbh_free(mouse->data);
	free(mouse);
	usb_mouse_table[mouse->number] = NULL;
	dev->driver_data = NULL;
	dev->driver = NULL;
}


/****************************************************************************/
/* USB�}�E�X�h���C�o��� */
static struct usbh_driver usb_mouse_driver = {
	"mouse",
	usb_mouse_connect,
	usb_mouse_disconnect,
};


/*******************************************************************************
    Routine Name    �Fusb_mouse_init
    Form            �Fint usb_mouse_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FUSB�}�E�X�h���C�o��������
*******************************************************************************/
int usb_mouse_init(void)
{
	int i;

	for(i=0; i<USB_MOUSE_MAX; i++){
		usb_mouse_table[i] = NULL;
	}
	usbh_driver_install(&usb_mouse_driver);
	return OK;
}


/*******************************************************************************
    Routine Name    �Fusb_mouse_exit
    Form            �Fvoid usb_mouse_exit(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�}�E�X�h���C�o�I������
*******************************************************************************/
void usb_mouse_exit(void)
{
	int i;

	for(i=0; i<USB_MOUSE_MAX; i++){
		if(usb_mouse_table[i]){
			if(usb_mouse_table[i]->dev){
				usbh_disconnect(&usb_mouse_table[i]->dev);
			}
		}
	}
	usbh_driver_uninstall(&usb_mouse_driver);
}

/* End of file */
