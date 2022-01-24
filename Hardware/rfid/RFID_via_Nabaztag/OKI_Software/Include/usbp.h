/*******************************************************************************
	usbp.h
	JOB60842�T���v���v���O����
	�y���t�F�����h���C�o�w�b�_

	Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
	  All rights reserved.

	�X�V����
	Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _USBP_H_
#define	_USBP_H_

#include "typedef.h"
#include "usbp_common.h"

/*****************************************************************************
    Standard Request Codes  ( bRequest )    
*******************************************/
#define	GET_STATUS			0
#define	CLEAR_FEATURE		1
#define	SET_FEATURE			3
#define	SET_ADDRESS			5
#define	GET_DESCRIPTOR		6
#define	SET_DESCRIPTOR		7
#define	GET_CONFIGURATION	8
#define	SET_CONFIGURATION	9
#define	GET_INTERFACE		10
#define	SET_INTERFACE		11
#define	SYNCH_FRAME			12

/*****************************************************************************
    Descriptor Types    
***********************/
#define	DEVICE				1
#define	CONFIGURATION		2
#define	STRING				3
#define	INTERFACE			4
#define	ENDPOINT			5
#if defined(OTG_ENABLE)
#define OTG					9
#endif /* OTG_ENABLE */
/*****************************************************************************
    Feature Selector    
***********************/
#define	DEVICE_REMOTE_WAKEUP	1
#define	ENDPOINT_STALL			0

/* On The Go */
#if defined(OTG_ENABLE)
/* Set Feature Feature Selector */
#define	B_HNP_ENABLE			3
#define	A_HNP_SUPPORT			4
#define	A_ALT_HNP_ENABLE		5
/* OTG Descriptor */
#define	USBP_HNP_SUPPORT				2
#define	USBP_SRP_SUPPORT				1
#endif /* OTG_ENABLE */


/*****************************************************************************
    Transfer Types    
***********************/
#define	CONTROL				0				/* bit 0-1 : 00 */
#define	ISOCHRONOUS			1				/* bit 0-1 : 01 */
#define	BULK				2				/* bit 0-1 : 10 */
#define	INTERRUPT			3				/* bit 0-1 : 11 */

#define	M_EP_NUM			0x0F

/* Device Requests */
typedef	uchar	bmRequestType;
typedef	uchar	bRequest;
typedef	ushort	wValue;
typedef	ushort	wIndex;
typedef	ushort	wLength;

/* Descriptor's common */
typedef	uchar	bLength;
typedef	uchar	bDescriptorType;

/* Device Descriptor */
typedef	ushort	bcdUSB;
typedef	uchar	bDeviceClass;
typedef	uchar	bDeviceSubClass;
typedef	uchar	bDeviceProtocol;
typedef	uchar	bMaxPacketSize0;
typedef	ushort	idVendor;
typedef	ushort	idProduct;
typedef	ushort	bcdDevice;
typedef	uchar	iManufacturer;
typedef	uchar	iProduct;
typedef	uchar	iSerialNumber;
typedef	uchar	bNumConfigurations;

/* Configuration Descriptor */
typedef	ushort	wTotalLength;
typedef	uchar	bNumInterfaces;
typedef	uchar	bConfigurationValue;
typedef	uchar	iConfiguration;
typedef	uchar	bmAttributes;
typedef	uchar	MaxPower;

/* Interface Descriptor */
typedef	uchar	bInterfaceNumber;
typedef	uchar	bAlternateSetting;
typedef	uchar	bNumEndpoints;
typedef	uchar	bInterfaceClass;
typedef	uchar	bInterfaceSubClass;
typedef	uchar	bInterfaceProtocol;
typedef	uchar	iInterface;

#if defined(HID_CLASS) || defined(AUDIO_DEVICE_CLASS)

/* HID Descriptor */
typedef	ushort	bcdHID;			/* HID�N���X�d�l�����[�X�ԍ�  */
typedef	uchar	bCountryCode;		/* �n�[�h�E�F�A�̑Ώۍ��R�[�h */
typedef	uchar	bNumDescriptors;	/* ����HID�f�B�X�N���v�^�̐�  */
typedef	uchar	wItemLengthL;		/* �f�B�X�N���v�^��LOW  */
typedef	uchar	wItemLengthH;		/* �f�B�X�N���v�^��HIGH  */

#endif /* HID_CLASS */

/* Endpoint Descriptor */
typedef	uchar	bEndpointAddress;
/* typedef	uchar	bmAttributes; *//* defined at Config.. */
typedef	ushort	wMaxPacketSize;
typedef	uchar	bInterval;

/* String Descriptor */


/*****************************************************************************
    USB Device Requests     
*****************************************************************************/
typedef struct Device_Request {
	bmRequestType		bmRequestType;		/*  */
	bRequest			bRequest;			/*  */
	wValue				wValue;				/*  */
	wIndex				wIndex;				/*  */
	wLength				wLength;			/*  */
} Device_Request;

/* bmRequestType D7     Data xfer direction */
#define	REQUEST_XFER		0x80
#define	HOST_to_DEVICE		0x00
#define	DEVICE_to_HOST		0x80

/* bmRequestType D6..5  Type */
#define	REQUEST_TYPE		0x60
#define	STANDARD_TYPE		0x00
#define	CLASS_TYPE			0x20
#define	VENDOR_TYPE			0x40

/* bmRequestType D4..0  Recipient */
#define	REQUEST_RECIPIENT	0x1F
#define	DEVICE_RECIPIENT	0x00
#define	INTERFACE_RECIPIENT	0x01
#define	ENDPOINT_RECIPIENT	0x02

/*****************************************************************************
    Standard USB Descriptor Definitions    
******************************************************************************/
typedef const struct String_Descriptor {
	bLength			bLength;
	bDescriptorType		bDescriptorType;
	ushort			*string;
} String_Desc;

typedef const struct Endpoint_Descriptor {
	bLength			bLength;
	bDescriptorType		bDescriptorType;
	bEndpointAddress	bEndpointAddress;
	bmAttributes		bmAttributes;
	wMaxPacketSize		wMaxPacketSize;
	bInterval		bInterval;
#ifdef AUDIO_DEVICE_CLASS			/* S000623 */
	uchar			append_1;
	uchar			append_2;
	uchar			*Class_Spec_Desc;
#endif /* AUDIO_DEVICE_CLASS */
} Endpoint_Desc;

#if defined( HID_CLASS)

/* �A���C�����g������Ȃ��̂ŁAwItemLength�̓o�C�g�P�ʂɕ������� */
typedef const struct HID_Descriptor {
	bLength				bLength;	/* �f�B�X�N���v�^��*/
	bDescriptorType		bDesciptorType;	/* �f�B�X�N���v�^�^�C�v			*/
	bcdHID				bcdHID;		/* HID�N���X�d�l�����[�X�ԍ�	*/
	bCountryCode		bCountryCode;	/* �n�[�h�E�F�A�̑Ώۍ��R�[�h	*/
	bNumDescriptors		bNumDescriptors;/* ����HID�f�B�X�N���v�^�̐�	*/
	bDescriptorType		bDescriptorType;/* �f�B�X�N���v�^�^�C�v			*/
	wItemLengthL		wItemLengthL;	/* �f�B�X�N���v�^��LOW			*/
	wItemLengthH		wItemLengthH;	/* �f�B�X�N���v�^��HIGH			*/
} HID_Desc;

#endif /* HID_CLASS */

typedef const struct Interface_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bInterfaceNumber	bInterfaceNumber;
	bAlternateSetting	bAlternateSetting;
	bNumEndpoints		bNumEndpoints;
	bInterfaceClass		bInterfaceClass;
	bInterfaceSubClass	bInterfaceSubClass;
	bInterfaceProtocol	bInterfaceProtocol;
	iInterface			iInterface;
	Endpoint_Desc		*p_EP_desc;	/* Endpoint Descriptor���w���|�C���^ */
#ifdef HID_CLASS
	HID_Desc		*p_HID_desc;	/* HID Descriptor���w���|�C���^ */
	const uchar		*p_HID_report_desc;	/*�K�{�̂P���|�[�g�f�B�X�N���v�^�ւ̃|�C���^*/
#endif /* HID_CLASS */
#ifdef AUDIO_DEVICE_CLASS
	uchar			num_audio_desc;
	const 			void **Audio_interface_desc;
#endif /* AUDIO_DEVICE_CLASS */
#ifdef CDC
	uchar			num_functional_desc;
	const 			void **CDC_functional_desc;
#endif /* CDC */
} Interface_Desc;

/*
 * OTG Descriptor
 */
#if defined(OTG_ENABLE)
typedef const struct OTG_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bmAttributes		bmAttributes;
}	OTG_Desc;
#endif /* OTG_ENABLE */

/*
 * ����bInterfaceNumber�ňႤbAlternateSetting������ Descriptor��
 * �ݒ�ł��邽�� Configuration �� Interface �����̍\���̂Œ����
 */
typedef struct Configuration_Interface {
	bInterfaceNumber	bInterfaceNumber;/* p_IF_desc���w��Descriptor��bInterfaceNumber */
	bAlternateSetting	bAlternateSetting;/* p_IF_desc���w��Descriptor��AlternateSetting�� */
	bAlternateSetting	currentAlternateSetting;/* ���ݐݒ肳��Ă���AlternateSetting */
	Interface_Desc		*p_IF_desc;	/* Interface Descriptor���w���|�C���^ */
#if defined(OTG_ENABLE)
	OTG_Desc			*p_OTG_desc;
#endif
#ifdef HID_CLASS
	HID_Desc			*p_HID_desc;	/* HID Descriptor���w���|�C���^ */
	const uchar			*p_HID_report_desc;/* �K�{�̂P���|�[�g�f�B�X�N���v�^�ւ̃|�C���^ */
#endif /* HID_CLASS */
} Config_if;

typedef const struct Configuration_Descriptor {
	bLength					bLength;
	bDescriptorType			bDescriptorType;
	wTotalLength			wTotalLength;
	bNumInterfaces			bNumInterfaces;
	bConfigurationValue		bConfigurationValue;
	iConfiguration			iConfiguration;
	bmAttributes			bmAttributes;
	MaxPower				MaxPower;
	Config_if				*p_CFG_if;	/* ����p�\���̂��w���|�C���^ */
} Config_Desc;

typedef const struct Device_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bcdUSB				bcdUSB;
	bDeviceClass		bDeviceClass;
	bDeviceSubClass		bDeviceSubClass;
	bDeviceProtocol		bDeviceProtocol;
	bMaxPacketSize0		bMaxPacketSize0;
	idVendor			idVendor;
	idProduct			idProduct;
	bcdDevice			bcdDevice;
	iManufacturer		iManufacturer;
	iProduct			iProduct;
	iSerialNumber		iSerialNumber;
	bNumConfigurations	bNumConfigurations;
	Config_Desc			*p_CFG_desc;	/* Configuration Descriptor���w���|�C���^ */
} Device_Desc;



/*****************************************************************************
*	�G���h�|�C���g�p�\����
******************************************************************************/
/*
Endpoint ����p�\����
*/
typedef const struct EP_List_C {
	uchar	*recv_byte_cnt;				/* ��M�o�C�g�J�E���g���W�X�^ */
	uchar	*epnconfig;				/* �R���t�B�O���[�V�������W�X�^ */
	uchar	*epncontrol;			/* ���䃌�W�X�^ */
	uchar	*epnstat;				/* �X�e�[�^�X���W�X�^ */
	uchar	*epnpayload;			/* �y�C���[�h���W�X�^ */
	uchar	*epntxcnt;				/* ���M�f�[�^�o�C�g�����W�X�^ */
	uint	*fifo_R;				/* ��MFIFO�A�h���X */
	uint	*fifo_W;				/* ���MFIFO�A�h���X */
	ushort	b_pktrdy_int;			/* �p�P�b�g���f�B������ �r�b�g */
	ushort	dummyA;			/*  */
} EP_LIST_C;


typedef struct EP_List_V {
	uint		transferred_size;	/* ����M�f�[�^���� */
	uint		demand_size;		/* ����M�f�[�^�� */
	uchar		*buf;				/* �f�[�^�p�o�b�t�@ */
	void	(*callback)(uchar *buf, uint transferred_size);	/* CallBack�֐� */
	uchar		demand_null;		/* �y�C���[�h�T�C�Y�̔{���̃f�[�^���M��NULL���o�����B*/
	uchar		dummyA;		/* */
	uchar		dummyB;		/* */
	uchar		dummyC;		/* */
} EP_LIST_V;

/* 
	USB Device �X�e�[�^�X
*/
typedef struct USB_Status {
	Config_Desc	*configuration;
	void	(*reset_assert_callback)(void);	/* Reset CallBack�֐� */
	void	(*reset_deassert_callback)(void);	/* Reset CallBack�֐� */
	void	(*set_interface_callback)(uchar conf, uchar ifnum);	
					/* SetInterface CallBack�֐� */
	uchar		remote_wakeup;
	uchar		address;
	uchar		dvcstate;		/* ���݂̃f�o�C�X�E�X�e�[�g */	
	uchar		stall_req;		/* STALL�v����� */
} USB_STATUS;

	#define REQ_STALL			0x80		/* STALL�v���r�b�g */
	#define DEFAULT_STATE		0
	#define ADDRESS_STATE		1
	#define CONFIGURED_STATE	2


/******************************************************************************/
/* Function Prototype */

void usbp_class_func(void);
void usbp_vendor_func(void);

void usbp_func_Clear_Feature(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Get_Configuration(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Get_Descriptor(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Get_Interface(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Get_Status(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Set_Address(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Set_Configuration(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Set_Descriptor(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Set_Feature(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Set_Interface(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_Synch_Frame(Device_Request *device_request_pointer, uchar *buf);
void usbp_func_stall(void);


void write_FIFO(char ep);
void read_FIFO(char ep);
void usbp_Decode_Request(void);

void usbp_interrupt(void);
int usbperi_init(void);

/******************************************************************************/

#include "ml60842.h"
#include "60842mac.h"

/******************************************************************************/
/* Variable Definition */

#if defined(USBPMAIN)
#define EXTERN 
#else
#define EXTERN extern
#endif

#if defined(USBPMAIN)
EP_LIST_C	epC[EP_MAX+1]
=
{
	{
		(void *)EP0RXCNTSTAT,
		(void *)EP0PLDCONF,
		(void *)EP0CONT,
		(void *)EP0RXCNTSTAT,
		(void *)EP0PLDCONF,
		(void *)EP0TXCNT,
		(void *)EP0RXFIFO,
		(void *)EP0TXFIFO,
		B_EP0RXPKTRDY_INT,
		NULL
	},
	{
		(void *)EP1RXCNTSTAT,
		(void *)EP1PLDCONF,
		(void *)EP1CONT,
		(void *)EP1RXCNTSTAT,
		(void *)EP1PLDCONF,
		(void *)EP1TXCNT,
		(void *)EP1FIFO,
		(void *)EP1FIFO,
		B_EP1PKTRDY_INT,
		NULL
	},
	{
		(void *)EP2RXCNTSTAT,
		(void *)EP2PLDCONF,
		(void *)EP2CONT,
		(void *)EP2RXCNTSTAT,
		(void *)EP2PLDCONF,
		(void *)EP2TXCNT,
		(void *)EP2FIFO,
		(void *)EP2FIFO,
		B_EP2PKTRDY_INT,
		NULL
	},
	{
		(void *)EP3RXCNTSTAT,
		(void *)EP3PLDCONF,
		(void *)EP3CONT,
		(void *)EP3RXCNTSTAT,
		(void *)EP3PLDCONF,
		(void *)EP3TXCNT,
		(void *)EP3FIFO,
		(void *)EP3FIFO,
		B_EP3PKTRDY_INT,
		NULL
	},
	{
		(void *)EP4RXCNT,
		(void *)EP4CONF,
		(void *)EP4CONT,
		(void *)EP4STAT,
		(void *)EP4PLD,
		(void *)EP4TXCNT,
		(void *)EP4FIFO,
		(void *)EP4FIFO,
		B_EP4PKTRDY_INT,
		NULL
	},
	{
		(void *)EP5RXCNT,
		(void *)EP5CONF,
		(void *)EP5CONT,
		(void *)EP5STAT,
		(void *)EP5PLD,
		(void *)EP5TXCNT,
		(void *)EP5FIFO,
		(void *)EP5FIFO,
		B_EP5PKTRDY_INT,
		NULL
	},
	{
		(void *)EP0RXCNTSTAT,
		(void *)EP0PLDCONF,
		(void *)EP0CONT,
		(void *)EP0RXCNTSTAT,
		(void *)EP0PLDCONF,
		(void *)EP0TXCNT,
		(void *)EP0RXFIFO,
		(void *)EP0TXFIFO,
		B_EP0TXPKTRDY_INT,
		NULL
	},
};	
#else
EXTERN	EP_LIST_C	epC[EP_MAX+1];
#endif

EXTERN	Device_Request		device_request;		/* Device Request */
EXTERN	USB_STATUS			usb_status;			/* Device Current Status */
EXTERN	uchar				ep_stat[EP_MAX];	/* �G���h�|�C���g�L��/������� 0:invalid 1:valid */	


EXTERN	EP_LIST_V	epV[EP_MAX+1];
EXTERN	USB_STATUS	usb_status;
EXTERN uchar cont_buf[256];

EXTERN	Device_Desc			*device_descriptor;	/* Device Descriptor */
/* 4�̃f�B�X�N���v�^��錾���Ă����B�����ύX���邱�ƁB */
extern	Device_Desc			device_descriptor1;	/* Device Descriptor */
#if defined(PERI_TEST)
extern	Device_Desc			device_descriptor2;	/* Device Descriptor */
extern	Device_Desc			device_descriptor3;	/* Device Descriptor */
extern	Device_Desc			device_descriptor4;	/* Device Descriptor */
#endif
extern String_Desc string_desc[];

#endif /*_USBP_H_*/

/* End of file */

