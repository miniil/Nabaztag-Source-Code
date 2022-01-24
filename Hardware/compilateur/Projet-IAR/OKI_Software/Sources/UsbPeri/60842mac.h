/*******************************************************************************
    60842mac.h
    JOB60842�T���v���v���O����
    ML60842���W�X�^����}�N����`
    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _ML60842MAC_H_
#define	_ML60842MAC_H_



/****************************************************************************
                    ML60842�p���W�X�^�A�N�Z�X�̃}�N��                        
****************************************************************************/

#include "ml60842.h"


#define write_reg32(_reg_, data) *(volatile unsigned long *)_reg_ = (unsigned long)data
#define read_reg32(_reg_) *(volatile unsigned long *)_reg_


#define EP0STALL_CLR_DATA	0x00		/* EP0 �X�g�[���r�b�g�N���A�f�[�^ */
#define EPnSTALL_CLR_DATA	0x00		/* EPn(n=1~5) �X�g�[���r�b�g�N���A�f�[�^ */

/*--------------------------------
      DMA�ݒ�                     
--------------------------------*/

/* �f�o�C�X�R���g���[����DMA�ݒ� */
	/* DMA�]���̑ΏۂƂȂ�EP�̎w�� */
	/* �����ɂ�F_DMA_EP?�̃}�N����`���g�p */
	#define SET_DMA_CONT0_EP(ep)\
		if(ep==EP1) {\
			write_reg32(DMA0CON, ((read_reg32(DMA0CON) & 0x05)| F_DMA_EP1) );\
		}\
		else if (ep==EP2) {\
			write_reg32(DMA0CON, ((read_reg32(DMA0CON) & 0x05)| F_DMA_EP2) );\
		}\
		else if (ep==EP4) {\
			write_reg32(DMA0CON, ((read_reg32(DMA0CON) & 0x05)| F_DMA_EP4) );\
		}\
		else if (ep==EP5) {\
			write_reg32(DMA0CON, ((read_reg32(DMA0CON) & 0x05)| F_DMA_EP5) );\
		}\
		
	#define SET_DMA_CONT1_EP(ep)\
		if(ep==EP1) {\
			write_reg32(DMA1CON, ((read_reg32(DMA1CON) & 0x05)| F_DMA_EP1) );\
		}\
		else if (ep==EP2) {\
			write_reg32(DMA1CON, ((read_reg32(DMA1CON) & 0x05)| F_DMA_EP2) );\
		}\
		else if (ep==EP4) {\
			write_reg32(DMA1CON, ((read_reg32(DMA1CON) & 0x05)| F_DMA_EP4) );\
		}\
		else if (ep==EP5) {\
			write_reg32(DMA1CON, ((read_reg32(DMA1CON) & 0x05)| F_DMA_EP5) );\
		}\
		

	/* DMA�o�C�g�J�E���g�}���@�\ */
	#define SET_DMA_CONT0_BYTE_CNT()\
		write_reg32(DMA0CON, ((read_reg32(DMA0CON))| B_BYTE_COUNT))
	#define SET_DMA_CONT1_BYTE_CNT()\
		write_reg32(DMA1CON, ((read_reg32(DMA1CON))| B_BYTE_COUNT))
	#define DIS_DMA_CONT0_BYTE_CNT()\
		write_reg32(DMA0CON, ((read_reg32(DMA0CON))& ~B_BYTE_COUNT))
	#define DIS_DMA_CONT1_BYTE_CNT()\
		write_reg32(DMA1CON, ((read_reg32(DMA1CON))& ~B_BYTE_COUNT))

	/* DMA�C�l�[�u�� */
	#define SET_DMA_CONT0_ENABLE()\
		write_reg32(DMA0CON, ((read_reg32(DMA0CON))| B_DMA_ENABLE))
	#define SET_DMA_CONT1_ENABLE()\
		write_reg32(DMA1CON, ((read_reg32(DMA1CON))| B_DMA_ENABLE))
	#define DIS_DMA_CONT0_ENABLE()\
		write_reg32(DMA0CON, ((read_reg32(DMA0CON))& ~B_DMA_ENABLE))
	#define DIS_DMA_CONT1_ENABLE()\
		write_reg32(DMA1CON, ((read_reg32(DMA1CON))& ~B_DMA_ENABLE))

/*--------------------------------
      ���M�f�[�^�o�C�g��          
--------------------------------*/
	/* ���M�f�[�^�o�C�g���ݒ� */
	#define SET_EPn_TXCNT(ep, size)\
		write_reg32((uint)(epC[ep].epntxcnt), size)

	/* ���M�f�[�^�o�C�g���擾(2�o�C�g) */
	#define GET_EPn_TXCNT(ep)\
		read_reg32((uint)(epC[ep].epntxcnt))

/*----------------------------
      �p�P�b�g���f�B�ݒ�      
----------------------------*/
	/* EPn(n=0,1,2,3,4,5)�̎�M�p�P�b�g���f�B���Z�b�g
		ep = EP0RX,EP1,EP2,EP3,EP4,EP5 */
	#define CLR_PKTRDY(ep)\
		write_reg32((uint)epC[ep].epnstat, (read_reg32((uint)epC[ep].epnstat) |\
			B_RECV_PKTRDY))

	/* EPn(n=0,1,2,3,4,5)�̑��M�p�P�b�g���f�B�Z�b�g
		ep = EP0TX,EP1,EP2,EP3,EP4,EP5 */
	#define SET_PKTRDY(ep)\
		write_reg32((uint)epC[ep].epnstat, (read_reg32((uint)epC[ep].epnstat) |\
			B_TRNS_PKTRDY))

	/* ���M�p�P�b�g���f�B�r�b�g�擾 */
	#define GET_PKTRDY(ep)\
		(read_reg32((uint)epC[ep].epnstat) & B_TRNS_PKTRDY)
/*----------------------
      ���荞�݋֎~      
----------------------*/
	/* EP0��M�p�P�b�g���f�B���荞�݋֎~ */
	#define DIS_EP0RX_PKTRDY_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) & (~epC[EP0RX].b_pktrdy_int)))

	/* EP0���M�p�P�b�g���f�B���荞�݋֎~ */
	#define DIS_EP0TX_PKTRDY_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) & (~epC[EP0TX].b_pktrdy_int)))

	/* EP0����M�p�P�b�g���f�B���荞�݋֎~ */
	#define DIS_EP0TXRX_PKTRDY_INT()\
	write_reg32(INTENBL, (read_reg32(INTENBL) & (~(epC[EP0TX].b_pktrdy_int | \
								epC[EP0RX].b_pktrdy_int))))

	/* EPn(n=1,2,3,4,5)�p�P�b�g���f�B���荞�݋֎~
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define DIS_PKTRDY_INT(ep)\
	write_reg32(INTENBL, (read_reg32(INTENBL) & (~(epC[ep].b_pktrdy_int))))

	/* SOF���荞�݋֎~ */
	#define DIS_SOF_INT()\
	write_reg32(INTENBL, (read_reg32(INTENBL) & (~B_SOF_INT)))

	/* �T�X�y���f�b�h���荞�݋֎~ */
	#define DIS_SUSPENDED_INT()\
	write_reg32(INTENBL, ((ulong)(read_reg32(INTENBL)) & (~B_SUSPENDED_STATE_INT)))

/*----------------------
      ���荞�݋���      
----------------------*/
	/* EP0��M�p�P�b�g���f�B���荞�݋��� */
	#define ENA_EP0RX_PKTRDY_INT()\
	write_reg32(INTENBL, (read_reg32(INTENBL) | epC[EP0RX].b_pktrdy_int))

	/* EP0���M�p�P�b�g���f�B���荞�݋��� */
	#define ENA_EP0TX_PKTRDY_INT()\
	write_reg32(INTENBL, (read_reg32(INTENBL) | epC[EP0TX].b_pktrdy_int))

	/* EPn(n=1,2,3,4,5)�p�P�b�g���f�B���荞�݋���
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define ENA_PKTRDY_INT(ep)\
		write_reg32(INTENBL, (read_reg32(INTENBL) | epC[ep].b_pktrdy_int))

	/* SOF���荞�݋��� */
	#define ENA_SOF_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) | B_SOF_INT))

	/* USB�o�X���Z�b�g�E�A�T�[�g���荞�݋��� */
	#define ENA_BUS_RESET_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) | B_BUS_RESET_INT))

	/* USB�o�X���Z�b�g�E�f�A�T�[�g���荞�݋��� */
	#define ENA_BUS_RESET_DES_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) | B_BUS_RESET_DES_INT))

	/* �T�X�y���f�b�h���荞�݋��� */
	#define ENA_SUSPENDED_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) | B_SUSPENDED_STATE_INT))

	/* �f�o�C�X�A�E�F�C�N�X�e�[�g�����݋��� */
	#define ENA_AWAKE_INT()\
		write_reg32(INTENBL, (read_reg32(INTENBL) | B_AWAKE_INT))

	/* �Z�b�g�A�b�v���f�B,�o�X���Z�b�g,�T�X�y���f�b�h,
		�o�X���Z�b�g�f�A�T�[�g,�A�E�F�C�N���荞�݋���(���������p) */
	#define ENA_SETUP_BUSRES_SUSPEND_INT()\
		write_reg32(INTENBL, (((B_SETUP_RDY_INT | \
		B_BUS_RESET_INT | B_SUSPENDED_STATE_INT | \
		B_BUS_RESET_DES_INT | B_AWAKE_INT))))

/*----------------------------
      ���荞�ݗv���N���A      
----------------------------*/
	/* �Z�b�g�A�b�v���f�B���Z�b�g */
	#define CLR_SETUPRDY()\
		write_reg32(EP0RXCNTSTAT, B_EP0_SETUP_RDY)

	/* SOF�����݃X�e�[�^�X���Z�b�g */
	#define CLR_B_SOF_STATE()\
		write_reg32(INTSTAT, B_SOF_INT)

	/* USB�o�X���Z�b�g�E�A�T�[�g�����݃X�e�[�^�X���Z�b�g */
	#define CLR_BUS_RESET_STATE()\
		write_reg32(INTSTAT, B_BUS_RESET_INT)

	/* USB�o�X���Z�b�g�E�f�A�T�[�g���荞�݃X�e�[�^�X���Z�b�g */
	#define CLR_BUS_RESET_DES_STATE()\
		write_reg32(INTSTAT, B_BUS_RESET_DES_INT)

	/* �f�o�C�X�T�X�y���f�b�h�X�e�[�g�����݃X�e�[�^�X���Z�b�g */
	#define CLR_SUSPENDED_STATE()\
		write_reg32(INTSTAT, B_SUSPENDED_STATE_INT)

	/* �f�o�C�X�A�F�[�N�X�e�[�g�����݃X�e�[�^�X���Z�b�g */
	#define CLR_AWAKE_STATE()\
		write_reg32(INTSTAT, B_AWAKE_INT)

/*------------------------------
      ���荞�ݗv���`�F�b�N      
------------------------------*/
	#define GET_INT_PTN()\
		(read_reg32(INTSTAT))

	/* �Z�b�g�A�b�v���f�B */
	#define SETUP_RDY_INT()\
		(read_reg32(INTSTAT) & B_SETUP_RDY_INT)

	/* EP1�p�P�b�g���f�B */
	#define EP1_PKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP1PKTRDY_INT)

	/* EP2�p�P�b�g���f�B */
	#define EP2_PKTRDY_INT()\
		(read_reg32(INTSTAT) &  B_EP2PKTRDY_INT)

	/* EP3�p�P�b�g���f�B */
	#define EP3_PKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP3PKTRDY_INT)

	/* EP4�p�P�b�g���f�B */
	#define EP4_PKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP4PKTRDY_INT)

	/* EP5�p�P�b�g���f�B */
	#define EP5_PKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP5PKTRDY_INT)

	/* EP0��M�p�P�b�g���f�B */
	#define EP0_RXPKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP0RXPKTRDY_INT)

	/* EP0���M�p�P�b�g���f�B */
	#define EP0_TXPKTRDY_INT()\
		(read_reg32(INTSTAT) & B_EP0TXPKTRDY_INT)

	/* SOF */
	#define SOF_INT()\
		(read_reg32(INTSTAT) & B_SOF_INT)

	/* USB�o�X���Z�b�g�A�T�[�g */
	#define USB_BUSRESET_ASS_INT()\
		(read_reg32(INTSTAT) & B_BUS_RESET_INT)

	/* USB�o�X���Z�b�g�f�A�T�[�g */
	#define USB_BUSRESET_DES_INT()\
		(read_reg32(INTSTAT) & B_BUS_RESET_DES_INT)

	/* �T�X�y���f�b�h */
	#define SUSPENDED_INT()\
		(read_reg32(INTSTAT) & B_SUSPENDED_STATE_INT)

	/* �A�E�F�C�N�X�e�[�g */
	#define AWAKE_INT()\
		(read_reg32(INTSTAT) &  B_AWAKE_INT)

/*------------------------------------
      �����[�g�E�F�C�N�A�b�v�ݒ�      
------------------------------------*/
	/* �����[�g�E�F�C�N�A�b�v�r�b�g�̃`�F�b�N */
	#define CHK_WAKEUP()\
		(read_reg32(INTSTAT) & B_AWAKE_INT)

	/* �����[�g�E�F�C�N�A�b�v�r�b�g�̃Z�b�g */
	#define SET_WAKEUP()\
		write_reg32(SYSCON,(ulong)((read_reg32(SYSCON)| B_REMOTE_WAKEUP)& ~B_SOFT_RESET))

/*----------------------
      �X�g�[���ݒ�      
----------------------*/
	/* EP0�̃X�g�[���r�b�g�̃Z�b�g */
	#define SET_STALL_EP0()\
		write_reg32((uint)(epC[EP0].epncontrol), B_STALL)

	/* EPn(n=1,2,3,4,5)�̃X�g�[���r�b�g�̃Z�b�g
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define SET_STALL_EPn(ep) \
		write_reg32( ((uint)epC[ep].epncontrol) ,\
		( ((read_reg32((uint)epC[ep].epncontrol)) & 0x08) | B_STALL))

	/* EP0�̃X�g�[���r�b�g�̃N���A */
	#define CLR_STALL_EP0()\
		write_reg32((uint)epC[EP0].epncontrol,EP0STALL_CLR_DATA)

	/* EPn(n=1,2,3,4,5)�̃X�g�[���r�b�g�̃N���A
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define CLR_STALL_EPn(ep)\
		write_reg32((uint)epC[ep].epncontrol,(ushort)((read_reg32((uint)(epC[ep].epncontrol)))& (ushort)EPnSTALL_CLR_DATA ))

	/* EPn(n=0,1,2,3,4,5)�X�g�[���r�b�g�̗L���m�F
		ep = EP0,EP1,EP2,EP3,EP4,EP5 */
	#define CHK_STALL_EPn(ep)\
		(read_reg32((uint)epC[ep].epncontrol) & B_STALL)

/*--------------------------
      �g�O���r�b�g�ݒ�      
--------------------------*/
	/* EPn(n=0,1,2,3,4,5)�̃g�O���r�b�g�̃��Z�b�g
		ep = EP0,EP1,EP2,EP3,EP4,EP5 */
	#define CLR_TOGL_EPn(ep)\
		write_reg32((uint)epC[ep].epncontrol,\
		((read_reg32((uint)epC[ep].epncontrol) & 0x03) | B_DATA_SEQUENCE))


/*----------------------------------
      �R���t�B�O���[�V�����ݒ�      
----------------------------------*/
	/* EPn(n=1,2,3,4,5)�̃R���t�B�O���[�V�����r�b�g�Z�b�g
		ep = EP1,EP2,EP3,EP4,EP5 */
		#define SET_CONFIGBIT_EPn(ep)\
			write_reg32((uint)epC[ep].epnconfig, \
				(read_reg32((uint)epC[ep].epnconfig)| ((uchar)B_CONFIG) ))

	/* Set Interface���CEPn(n=1,2,3,4,5)�̃R���t�B�O���[�V�����r�b�g�Z�b�g
		�]�������̐ݒ� & CONFIGURATION BIT ON & STALL �r�b�g���������s�� */
	#define SETINIT_CONFIGBIT_EPn(ep)\
			write_reg32((uint)epC[ep].epnconfig, \
			((read_reg32((uint)epC[ep].epnconfig) & 0xFFFFFF00) |\
			(((p_e_desc->bEndpointAddress & DEVICE_to_HOST)|\
			B_CONFIG | (p_e_desc->bmAttributes & 0x03))\
			)));\
			CLR_STALL_EPn(ep);

	/* EPn(n=1,2,3,4,5)�̃R���t�B�O���[�V�����r�b�g���Z�b�g
		ep = EP1,EP2,EP3,EP4,EP5 */
		#define CLR_CONFIGBIT_EPn(ep)\
			write_reg32((uint)epC[ep].epnconfig, (read_reg32((uint)epC[ep].epncontrol))\
			 & ((uint)(~B_CONFIG)));

	/* ���ׂĂ�EPn(n=1,2,3,4,5)�̃R���t�B�O���[�V�����r�b�g���Z�b�g
		ep = EP1,EP2,EP3,EP4,EP5 */
#define CLR_CONFIGBIT_ALL_EPn()\
			{\
			write_reg32((uint)epC[EP1].epnconfig, (read_reg32((uint)epC[EP1].epnconfig))\
			 & ((uint)(~B_CONFIG)));\
			write_reg32((uint)epC[EP2].epnconfig, (read_reg32((uint)epC[EP2].epnconfig))\
			 & ((uint)(~B_CONFIG)));\
			write_reg32((uint)epC[EP3].epnconfig, (read_reg32((uint)epC[EP3].epnconfig))\
			 & ((uint)(~B_CONFIG)));\
			write_reg32((uint)epC[EP4].epnconfig, (read_reg32((uint)epC[EP4].epnconfig))\
			 & ((uint)(~B_CONFIG)));\
			write_reg32((uint)epC[EP5].epnconfig, (read_reg32((uint)epC[EP5].epnconfig))\
			 & ((uint)(~B_CONFIG)));\
			 }

/*------------------------------
      �y�C���[�h�T�C�Y�ݒ�      
------------------------------*/
	/* EPn(n=0,1,2,3,4,5)�̃y�C���[�h�T�C�Y�ݒ�
		ep = EP0RX,EP0TX,EP1,EP2,EP3,EP4,EP5 */

	#define SET_PAYLOAD_EPn(ep, size)\
	{\
		if( (ep!=EP4) && (ep!=EP5))\
		{\
			write_reg32((uint)(epC[ep].epnpayload),	\
			((read_reg32((uint)(epC[ep].epnpayload)) & 0xFF) | (((uint)size<<8)&0xFF00)));\
		}\
		else\
		{\
			write_reg32((uint)(epC[ep].epnpayload),	\
			((read_reg32((uint)(epC[ep].epnpayload)) & 0x0000FFFFul)\
			 | (((uint)size<<16) & 0x0FFF0000ul)));\
		}\
	}\
			

	/* EPn(n=0,1,2,3,4,5)�̃y�C���[�h�T�C�Y�擾
		ep = EP0TX,EP0RX,EP1,EP2,EP3 */
	#define GET_PAYLOAD_EPn(ep)\
		((read_reg32((uint)(epC[ep].epnpayload)))>>8 & 0xFF)

	#define GET_PAYLOAD_EP4or5(ep)\
		(ushort)(((read_reg32((uint)(epC[ep].epnpayload))) >> 16) & 0xFFFF)


/*--------------------------
      �]�������`�F�b�N      
--------------------------*/
	/* EPn(n=1,2,3,4,5)�̓]�������`�F�b�N
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define CHK_EPn_HOST_TO_DEVICE(ep)\
		(uchar)(read_reg32((uint)(epC[ep].epnconfig)) & DEVICE_to_HOST)

/*--------------------
      FIFO�N���A      
--------------------*/
	/* EPn(n=1,2,3,4,5)��FIFO���W�X�^�N���A
		ep = EP1,EP2,EP3,EP4,EP5 */
	#define CLR_EPn_FIFO(ep)\
	write_reg32(((uint)epC[ep].epncontrol), B_CLR_FIFO)

/*----------------------
      �A�h���X�ݒ�      
----------------------*/
	/* SET_ADDRESS���N�G�X�g�ɂ��A�h���X��DVCADR���W�X�^�ɐݒ� */
	#define SET_ADDRESS_DATA(address)\
		write_reg32((uint)DVCADR, address)

	/* DVCADR���W�X�^����ݒ肳��Ă���A�h���X�l���擾 */
	#define GET_ADDRESS_DATA()\
		read_reg32((uint)DVCADR)

/*---------------------------------------
      FIFO���W�X�^�̃A�h���X�擾         
---------------------------------------*/
	/* EPn(n=0,1,2,3,4,5)�̃��C�gFIFO���W�X�^�̃A�h���X���擾
		ep = EP0TX,EP1,EP2,EP3,EP4,EP5 */
	#define GET_WFIFO_ADRS_EPn(ep)\
		epC[ep].fifo_W

	/* EPn(n=0,1,2,3,4,5)�̃��[�hFIFO���W�X�^�̃A�h���X���擾
		ep = EP0RX,EP1,EP2,EP3,EP4,EP5 */
	#define GET_RFIFO_ADRS_EPn(ep)\
		epC[ep].fifo_R


/*--------------------------
      ��M�o�C�g���擾      
--------------------------*/
	/* EPn(n=0,1,2,3,4,5)�̃y�C���[�h�T�C�Y�ݒ�
		ep = EP0RX,EP0TX,EP1,EP2,EP3,EP4,EP5 */

	#define GET_RECV_BYTE(ep)\
		(unsigned char)((read_reg32((uint)(epC[ep].recv_byte_cnt)))>>8 & 0xFF)

	#define GET_RECV_BYTE_EP4or5(ep)\
		(ushort)(((read_reg32((uint)(epC[ep].recv_byte_cnt)))>>16) & 0xFFFF)



/*------------------------
      �v���A�b�v����      
------------------------*/
	#define PULLUP_ON()\
		write_reg32(OTGCtl,(((read_reg32(OTGCtl))| B_PUCTLDP) ))

	/* �v���A�b�vOFF */
	#define PULLUP_OFF()\
		write_reg32(OTGCtl,(((read_reg32(OTGCtl))& (~B_PUCTLDP))))



/*--------------------------------
      �T�X�y���h���̏ȓd�ݒ�      
--------------------------------*/
	/* �T�X�y���h���ɏȓd�ɂ��� */
	#define ENA_POWER_DOWN()\
		write_reg32(SYSCON,(((read_reg32(SYSCON))| B_PWDWN_MODE)& ~B_SOFT_RESET))

	/* �T�X�y���h���ɏȓd�ɂ��Ȃ� */
	#define DIS_POWER_DOWN()\
		write_reg32(SYSCON,(((read_reg32(SYSCON))& ~B_PWDWN_MODE)& ~B_SOFT_RESET))

/*------------------------
      EP���[�h�̐ݒ�      
------------------------*/
	/* 5EP���[�h�ɐݒ肷�� */
	#define SET_5EP_MODE()\
		write_reg32(SYSCON,(((read_reg32(SYSCON)) | (B_EP_MODE)) &~B_SOFT_RESET))

	/* 6EP���[�h�ɐݒ肷�� */
	#define SET_6EP_MODE()\
		write_reg32(SYSCON,(((read_reg32(SYSCON))& (~B_EP_MODE)) &~B_SOFT_RESET))

/*------------------------------------
      �f�o�C�X���N�G�X�g�̎擾      
------------------------------------*/
	#define GET_bmRequestType()		(uchar)(read_reg32(SETUP0W))
	#define GET_bRequest()			(uchar)(read_reg32(SETUP0W) >> 8 & 0x00FF)
	#define GET_wValue()	 		(wValue)(((read_reg32(SETUP0W))>>16) & 0xFFFFul)
	#define GET_wIndex()			(wIndex)(((read_reg32(SETUP2W))))
	#define GET_wLength()			(wLength)(((read_reg32(SETUP2W))>>16) & 0xFFFFul)

/*----------------------------------------------------------
      ���O�t���[����ISO IN�]�������݂��Ă��邩�̊m�F     
----------------------------------------------------------*/

	#define CHK_ISO_IN_RECVED_EP4() \
		((read_reg32(EP4RXCNTSTAT)  & ISO_IN_RCVED_STS) == ISO_IN_RCVED_STS)
	#define CHK_ISO_IN_RECVED_EP5() \
		((read_reg32(EP5RXCNTSTAT)  & ISO_IN_RCVED_STS) == ISO_IN_RCVED_STS)
	#define SET_ISO_MODE_1_EP4() \
		(write_reg32(ISOMODE,( read_reg32(ISOMODE) & ~(0x10))))
	#define SET_ISO_MODE_2_EP4() \
		(write_reg32(ISOMODE,( read_reg32(ISOMODE) | (0x10))))
	#define SET_ISO_MODE_1_EP5() \
		(write_reg32(ISOMODE,( read_reg32(ISOMODE) & ~(0x20))))
	#define SET_ISO_MODE_2_EP5() \
		(write_reg32(ISOMODE,( read_reg32(ISOMODE) | (0x20))))
	#define CHECK_SET_ISO_MODE_EP4() \
		((read_reg32(ISOMODE) & (0x10)) == 0x10)
	#define CHECK_SET_ISO_MODE_EP5() \
		((read_reg32(ISOMODE) & (0x20)) == 0x20)


/******************************************************************************/
#endif /*_ML60842MAC_H_*/

/* End of file */
