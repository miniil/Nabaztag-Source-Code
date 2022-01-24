/*******************************************************************************
    usbp_descript.c
    JOB60842�T���v���v���O���� 
    �f�B�X�N���v�^�̒�`

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/

#include "typedef.h"
#include "usbp_common.h"
#include "usbp_class.h"
#include "usbp.h"

/*	=======================================================
	1.	Descriptor�̏������ŗp����}�N��
	=======================================================
*/
/*
	Set_L_H()
	---------
	Low byte, High Byte�̏��ɓƗ�����2byte���`����
	�A���C�����g�ɉ���Ȃ����[�h�̏��������s��
*/
#define	Set_L_H(_val)	(((_val) & 0xff), (((_val) >> 8) & 0xff))

/*
	WordSet()
	---------
	Endian�̉e�������[�h�^���������s��
	�K�i���Descriptor�̒�`��LittleEndian�`��
	����������BigEndian�}�V���ł́A�o�C�g���𔽓]������
*/

#ifdef BIG_ENDIAN
	#define	WordSet(_val)	((((_val) & 0xff) << 8) | (((_val) >> 8) & 0xff))
#else
	#define	WordSet(_val)	(_val)
#endif /* BIG_ENDIAN */


/*	=======================================================
	3.	Descriptor��`�t�@�C���idscrptXX.inc�j�̎捞��
		����� Vendor ID & Product ID �̒�`

		Vendor ID�́A0x70A = Oki Electric Industry Co., Ltd
		Product ID�́A0x4012

		�����́AML60841�̕]������������
		�g�p�ł�����̂ł��B���ۂ̃��[�U�V�X�e���ɂ�
		���ẮA���q�l���擾���ꂽVendorID����т��q�l
		���Ǘ������ProductID��p����K�v������܂��B
	=======================================================
*/

#define	VID		0x70A		/* Vendor ID */

#if defined(BULK_IN_OUT_AND_INT)

	#define	PID	0x4012		/* Product ID *//* 0x4012 */
	#include "dscrpt14.inc"	
/*
	dscrpt14.inc(1)	bulk In/Out + Interrupt
*/
#else

#error never come here

#endif

/* End of file */
