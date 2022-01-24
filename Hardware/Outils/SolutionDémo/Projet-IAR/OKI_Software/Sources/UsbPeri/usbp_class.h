/*******************************************************************************
    usbp_class.h
    JOB60842�T���v���v���O���� 
    �N���X��`
    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _USBP_CLASS_H_
#define	_USBP_CLASS_H_

/* CLASS ��錾 */
#define BULK_IN_OUT_AND_INT


/* �N���X���̐ݒ� */
#if defined(BULK_IN_OUT_AND_INT)
/*----------------------------------------------------------------------------
�萔��`*/
#define	EPA_WITH_DIR	(EP1 | HOST_to_DEVICE)
#define	EPB_WITH_DIR	(EP2 | DEVICE_to_HOST)
#define	EPINT_WITH_DIR	(EP3 | DEVICE_to_HOST)
#define	EPC_WITH_DIR	(EP4 | HOST_to_DEVICE)
#define	EPD_WITH_DIR	(EP5 | DEVICE_to_HOST)
#define	EPA_PLD			64
#define	EPB_PLD			64
#define	EPINT_PLD		16
#define	EPC_PLD			64
#define	EPD_PLD			64
#define	EP_INT_INTERVAL	2
#define	EP_RX			EP1
#define	EP_TX			EP2
#define EP_INT			EP3
#define	EP_RX2			EP4
#define	EP_TX2			EP5

void usbp_bulk_init(uchar interface, uchar alternate);

#else
	#error never come here
#endif




/******************************************************************************/
#endif /*_USBP_CLASS_H_*/

/* End of file */
