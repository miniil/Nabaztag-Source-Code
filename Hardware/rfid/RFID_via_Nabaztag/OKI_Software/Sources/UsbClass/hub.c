/*******************************************************************************
    hub.c
    JOB60842�T���v���v���O����
    �z�X�g�n�u�N���X�h���C�o���[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
/* #define DEBUG */

#include <string.h>
#include "config.h"
#include "list.h"
#include "usbh.h"
#include "usbctrl.h"
#include "hub.h"

DEFINE_LIST_ENTRY(hub_event_list);

#define HUB_MAX 5
static struct usb_hub hub_table[HUB_MAX];
int hub_status = USB_HUB_IDLE;

/*******************************************************************************
    Routine Name    �Fusb_get_hub_descriptor
    Form            �Fstatic int usb_get_hub_descriptor(PDEVINFO dev,
                                 void *data, ushort size);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      data          �n�u�f�B�X�N���v�^�ւ̃|�C���^
                      size          �n�u�f�B�X�N���v�^�T�C�Y
    Return value    �F���s����
    Description     �F�n�u�f�B�X�N���v�^�擾
*******************************************************************************/
static int usb_get_hub_descriptor(PDEVINFO dev, void *data, ushort size)
{
	return usbh_control_transfer(dev, 0, USB_GET_DESCRIPTOR,
		USB_DIR_IN | USB_RT_HUB, USB_DT_HUB << 8, 0, size,  data);
}


/*******************************************************************************
    Routine Name    �Fusb_clear_hub_feature
    Form            �Fstatic int usb_clear_hub_feature(PDEVINFO dev, ushort feature);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      feature       �@�\�Z���N�^
    Return value    �F���s����
    Description     �F�n�u�@�\�N���A
*******************************************************************************/
static int usb_clear_hub_feature(PDEVINFO dev, ushort feature)
{
	return usbh_control_transfer(dev, 0, USB_CLEAR_FEATURE,
		USB_RT_HUB, feature, 0, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusb_clear_port_feature
    Form            �Fstatic int usb_clear_port_feature(PDEVINFO dev, ushort port,
                                 ushort feature);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      port          �|�[�g�ԍ�
                      feature       �@�\�Z���N�^
    Return value    �F���s����
    Description     �F�|�[�g�@�\�N���A
*******************************************************************************/
static int usb_clear_port_feature(PDEVINFO dev, ushort port, ushort feature)
{
	return usbh_control_transfer(dev, 0, USB_CLEAR_FEATURE,
		USB_RT_PORT, feature, port, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusbh_set_port_feature
    Form            �Fstatic int usbh_set_port_feature(PDEVINFO dev, ushort port,
                                 ushort feature);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      port          �|�[�g�ԍ�
                      feature       �@�\�Z���N�^
    Return value    �F���s����
    Description     �F�|�[�g�@�\�ݒ�
*******************************************************************************/
static int usbh_set_port_feature(PDEVINFO dev, ushort port, ushort feature)
{
	return usbh_control_transfer(dev, 0, USB_SET_FEATURE, 
		USB_RT_PORT, feature, port, 0, NULL);
}


/*******************************************************************************
    Routine Name    �Fusb_get_hub_status
    Form            �Fstatic int usb_get_hub_status(PDEVINFO dev, void *data);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      data          �n�u�X�e�[�^�X�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�n�u�X�e�[�^�X�擾
*******************************************************************************/
static int usb_get_hub_status(PDEVINFO dev, void *data)
{
	return usbh_control_transfer(dev, 0, USB_GET_STATUS,
		USB_DIR_IN | USB_RT_HUB, 0, 0, sizeof(struct usb_hub_status), data);
}


/*******************************************************************************
    Routine Name    �Fusb_get_port_status
    Form            �Fstatic int usb_get_port_status(PDEVINFO dev, ushort port,
                                 void *data);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
                      port          �|�[�g�ԍ�
                      data          �|�[�g�X�e�[�^�X�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�|�[�g�X�e�[�^�X�擾
*******************************************************************************/
static int usb_get_port_status(PDEVINFO dev, ushort port, void *data)
{
	return usbh_control_transfer(dev, 0, USB_GET_STATUS, 
		USB_DIR_IN | USB_RT_PORT, 0, port, sizeof(struct usb_hub_status), data);
}


#ifdef DEBUG
/*******************************************************************************
    Routine Name    �Fusb_show_hub_descriptor
    Form            �Fvoid usb_show_hub_descriptor(struct usb_hub_descriptor *desc);
    Parameters      �Fdesc          �n�u�f�B�X�N���v�^�ւ̃|�C���^
    Return value    �F���s����
    Description     �FUSB�n�u �N���X�f�B�X�N���v�^�̕\��
*******************************************************************************/
void usb_show_hub_descriptor(struct usb_hub_descriptor *desc)
{
	int i;
	ushort wHubCharacteristics = (ushort)((((ushort)desc->wHubCharacteristics_h) << 16 )
                                         | ((ushort)desc->wHubCharacteristics_l));

	con_printf("Hub Class Descriptor:\n");
	con_printf(" bLength             = %d\n",		desc->bLength);
	con_printf(" bDescriptorType     = %02X\n",		desc->bDescriptorType);
	con_printf(" bNbrPorts           = %02X\n",		desc->bNbrPorts);
	con_printf(" wHubCharacteristic  = %04X\n",		wHubCharacteristics);
	switch (wHubCharacteristics & 0x03) {
		case 0x00:	con_printf("  Ganged power switching\n"); break;
		case 0x01:	con_printf("  Individual port power switching\n"); break;
        default: break;
	}
	switch (wHubCharacteristics & 0x04) {
		case 0x00:	con_printf("  Hub is not part of a compound device.\n"); break;
		case 0x04:	con_printf("  Hub part of a compound device.\n"); break;
        default: break;
	}
	switch (wHubCharacteristics & 0x18) {
		case 0x00:	con_printf("  Global Over-current Protection\n"); break;
		case 0x08:	con_printf("  Individual Port Over-current Protection\n");	break;
		default:	con_printf("  No Over-current Protection\n");	break;
	}
	con_printf(" bPwrOn2PwrGood      = %dms\n",		desc->bPwrOn2PwrGood *2);
	con_printf(" bHubContrCurrent    = %dmA\n", 		desc->bHubContrCurrent);
	con_printf(" DeviceRemovale      = ");
	for(i=0; i<desc->bNbrPorts; i++){
		con_printf("%c ", desc->bitmap[((i + 1) / 8)] & (1 << ((i + 1) % 8)) ? 'N' : 'Y');
	}
	con_printf("\n");
	con_printf(" PoerPwreCtrlMask    = ");
	for(i=0; i<desc->bNbrPorts; i++){
		con_printf("%c ", desc->bitmap[desc->bNbrPorts/8+((i + 1)/8)] & (1 << ((i + 1) % 8)) ? 'N' : 'Y');
	}
	con_printf("\n");
}
#endif


/*******************************************************************************
    Routine Name    �Fusb_hub_power_on
    Form            �Fstatic void usb_hub_power_on(struct usb_hub *hub);
    Parameters      �Fhub           �n�u���ւ̃|�C���^
    Return value    �F
    Description     �FUSB�n�u �S�|�[�g�d���I��
*******************************************************************************/
static void usb_hub_power_on(struct usb_hub *hub)
{
	ushort port;
    int    ret;

	dbg_printf(" hub: enabling power on all ports\n");
	for (port = 0; port < hub->ports; port++){
		ret = usbh_set_port_feature(hub->dev, port + (ushort)1, PORT_POWER);
		if(ret<0)
			dbg_printf(" hub: Error!\n");
	}

	mdelay(hub->descriptor->bPwrOn2PwrGood * 2);
}


/*******************************************************************************
    Routine Name    �Fusb_hub_callback
    Form            �Fstatic void usb_hub_callback(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �FUSB�n�u �R�[���o�b�N
*******************************************************************************/
static void usb_hub_callback(PURB urb)
{
	struct usb_hub *hub= (struct usb_hub *)urb->dev->driver_data;

	if (urb->status<0){
		/* �G���[������͖������ɂȂ�B�K�v�Ȃ�΃G���[�������������� */
		return;
	}
	
	list_add(&hub->list, &hub_event_list);
}


/*******************************************************************************
    Routine Name    �Fusb_hub_events
    Form            �Fvoid usb_hub_events(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�n�u �C�x���g����
*******************************************************************************/
void usb_hub_events(void)
{
	pLIST_ENTRY tmp;
	struct usb_hub *hub;
	PDEVINFO dev;
	ushort port;
    int ret;
	struct usb_port_status portsts;
	ushort portstatus, portchange;
	struct usb_hub_status hubsts;
	ushort hubstatus, hubchange;

	while (1) {

		if (list_empty(&hub_event_list))
            return;

		tmp = hub_event_list.Flink;

		hub = list_struct_entry(tmp, struct usb_hub, list);
		dev = hub->dev;

		list_del(tmp);
		INIT_LIST_ENTRY(tmp);

		ret = usb_get_hub_status(dev, &hubsts);
		if (ret < 0) {
			dbg_printf(" hub: Error! get_hub_status\n");
		}
		else {
			hubstatus = hubsts.wHubStatus;
			hubchange = hubsts.wHubChange;
			if (hubchange & HUB_CHANGE_LOCAL_POWER) {
				dbg_printf(" hub: HUB_CHANGE_LOCAL_POWER\n");
				usb_clear_hub_feature(dev, C_HUB_LOCAL_POWER);
			}
			if (hubchange & HUB_CHANGE_OVERCURRENT) {
				dbg_printf("hub: HUB_CHANGE_OVERCURRENT\n");
				usb_clear_hub_feature(dev, C_HUB_OVER_CURRENT);
				usbh_disconnect(&dev);
			}
		}

		for (port = 1; port <= hub->ports; port++) {

			ret = usb_get_port_status(dev, port, &portsts);
			if (ret < 0) {
				dbg_printf(" hub: Error! get_port_status (port=%d)\n", port);
				continue;
			}

			portstatus = portsts.wPortStatus;
			portchange = portsts.wPortChange;

			if (portchange & HUB_C_PORT_RESET) {
				dbg_printf(" hub: C_PORT_RESET (%d)\n", port);
				usb_clear_port_feature(dev, port, C_PORT_RESET);
				if(portstatus & HUB_PORT_CONNECTION){
					if(!hub->children[port-1]){
						hub->children[port-1] = usbh_connect((unsigned char)(portstatus & HUB_PORT_LOW_SPEED ? 1: 0));
						if(!hub->children[port-1]){
							usb_clear_port_feature(dev, port, PORT_POWER);
						}
					}
				}
                hub_status = USB_HUB_IDLE;
			}

			if(portchange & HUB_C_PORT_CONNECTION){
				dbg_printf(" hub: C_PORT_CONNECTION (%d)\n", port);
                if( hub_status == USB_HUB_IDLE ){
                    hub_status = USB_HUB_CONNECT;
				    usb_clear_port_feature(dev, port, C_PORT_CONNECTION);
				    usbh_set_port_feature(dev, port, PORT_RESET);
				    if( ((portstatus & HUB_PORT_CONNECTION) == 0) && (hub->children[port-1]) ){
					    usbh_disconnect(&hub->children[port-1]);
                        hub->children[port-1] = NULL;
                        hub_status = USB_HUB_IDLE;
				    }
				    mdelay(200);
                }
                else{
                    break;
                }
			}

			if(portchange & HUB_C_PORT_ENABLE){
				dbg_printf(" hub: C_PORT_ENABLE (%d)\n", port);
				usb_clear_port_feature(dev, port, C_PORT_ENABLE);
			}

			if (portchange & HUB_C_PORT_SUSPEND) {
				dbg_printf(" hub: C_PORT_SUSPEND (%d)\n", port);
				usb_clear_port_feature(dev, port, C_PORT_SUSPEND);
			}
			
			if (portchange & HUB_C_PORT_OVER_CURRENT) {
				dbg_printf(" hub: C_OVER_CURRENT (%d)\n", port);
				usb_clear_port_feature(dev, port, C_PORT_OVER_CURRENT);
				usb_hub_power_on(hub);
			}

		}

		usbh_transfer_request(&hub->urb);
	}/* while(1) */
}


/*******************************************************************************
    Routine Name    �Fusb_hub_connect
    Form            �Fstatic void *usb_hub_connect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F�n�u���ւ̃|�C���^
    Description     �FUSB�n�u �ڑ�����
*******************************************************************************/
static void *usb_hub_connect(PDEVINFO dev)
{
	struct usb_interface_descriptor *interface;
	struct usb_endpoint_descriptor *endpoint;
	int ret;
	struct usb_hub_status hubstatus;
	int number;


	if(!dev) return NULL;
	if(!dev->descriptor) return NULL;
	if(!dev->descriptor->configuration) return NULL;

	interface = dev->descriptor->configuration->interface;

	if (interface->bInterfaceClass != USB_CLASS_HUB) return NULL;
	if ((interface->bInterfaceSubClass != 0) &&
		(interface->bInterfaceSubClass != 1)) return NULL;
	if (interface->bNumEndpoints != 1) return NULL;

	ret = usbh_set_configuration(dev, 1);
	if(ret<0){
		return NULL;
	}

	endpoint = interface->endpoint;
	if ( (endpoint->bEndpointAddress & USB_DIR_IN) == 0 ) return NULL;
	if ((endpoint->bmAttributes & 3) != 3) return NULL;

	dev->pipe[1] = usbh_create_pipe(dev, endpoint->bmAttributes, endpoint->bEndpointAddress, 
		endpoint->wMaxPacketSize, endpoint->bInterval);
	if(!dev->pipe[1]) return NULL;

	number = 0;
	while(hub_table[number].dev){
		number++;
		if(number >= HUB_MAX)
			return NULL;
	}

	hub_table[number].dev = dev;
	dev->driver_data = &hub_table[number];

	hub_table[number].buffer = (char *)usbh_malloc(MAXCHILDREN / 8);
	if (!hub_table[number].buffer) {
        hub_table[number].dev = NULL;
		return NULL;
	}
	memset((void *)hub_table[number].buffer, 0, MAXCHILDREN / 8);

	hub_table[number].descriptor = (struct usb_hub_descriptor *)malloc(sizeof(struct usb_hub_descriptor));
	if (!hub_table[number].descriptor) {
		usbh_free(hub_table[number].buffer);
		hub_table[number].dev = NULL;
		return NULL;
	}

	ret = usb_get_hub_descriptor(dev, hub_table[number].descriptor, sizeof(struct usb_hub_descriptor));
	if (ret < 0) {
		free(hub_table[number].descriptor);
		usbh_free(hub_table[number].buffer);
		hub_table[number].dev = NULL;
		return NULL;
	}
	hub_table[number].ports = hub_table[number].descriptor->bNbrPorts;
	
#ifdef DEBUG
	usb_show_hub_descriptor(hub_table[number].descriptor);
#endif
	
	ret = usb_get_hub_status(dev, &hubstatus);
	if (ret < 0) {
		dbg_printf(" hub: Error! get_hub_status\n");
        free(hub_table[number].descriptor);
		usbh_free(hub_table[number].buffer);
		hub_table[number].dev = NULL;
		return NULL;
	}
	dbg_printf(" hub: wHubStatus = %04X\n", hubstatus.wHubStatus );
	dbg_printf(" hub: wHubChange = %04X\n", hubstatus.wHubChange );

	dbg_printf("USB Hub\n");

	usbh_set_interrupt_urb(&hub_table[number].urb, dev, 1, hub_table[number].buffer, endpoint->wMaxPacketSize, usb_hub_callback);
	if(usbh_transfer_request(&hub_table[number].urb)){
        free(hub_table[number].descriptor);
		usbh_free(hub_table[number].buffer);
		hub_table[number].dev = NULL;
		return NULL;
	}

	usb_hub_power_on(&hub_table[number]);
	return &hub_table[number];
}


/*******************************************************************************
    Routine Name    �Fusb_hub_disconnect
    Form            �Fstatic void usb_hub_disconnect(PDEVINFO dev);
    Parameters      �Fdev           �f�o�C�X���ւ̃|�C���^
    Return value    �F
    Description     �FUSB�n�u �ؒf����
*******************************************************************************/
static void usb_hub_disconnect(PDEVINFO dev)
{
	struct usb_hub *hub= (struct usb_hub *)dev->driver_data;
	int i;

	for(i = 0; i<MAXCHILDREN; i++){
		if(hub->children[i]){
			usbh_disconnect(&hub->children[i]);
		}
	}

	usbh_transfer_cancel(&hub->urb);
	usbh_free(hub->buffer);
	free(hub->descriptor); 
	hub->dev = NULL;
	dev->driver_data = NULL;
	dev->driver = NULL;
}


/****************************************************************************/
/* USB�n�u�N���X �h���C�o��� */
static struct usbh_driver usb_hub_driver = {
	"hub",
	usb_hub_connect,
	usb_hub_disconnect,
};


/*******************************************************************************
    Routine Name    �Fusb_hub_init
    Form            �Fint usb_hub_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FUSB�n�u �h���C�o��������
*******************************************************************************/
int usb_hub_init(void)
{
    int i;

    /* HUB�e�[�u�������� */
	for(i=0; i<HUB_MAX; i++){
        memset(&hub_table[i], 0, sizeof(struct usb_hub));
	}

	usbh_driver_install(&usb_hub_driver);
	return OK;
}


/*******************************************************************************
    Routine Name    �Fusb_hub_exit
    Form            �Fvoid usb_hub_exit(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�n�u �h���C�o�I������
*******************************************************************************/
void usb_hub_exit(void)
{
    int i;


	/*hub_table�̍폜*/
	for(i=0; i<HUB_MAX; i++){
		if(hub_table[i].dev){
			usbh_disconnect(&hub_table[i].dev);
		}
	}

	usbh_driver_uninstall(&usb_hub_driver);
}

/* End of file */
