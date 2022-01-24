/*******************************************************************************
    usbh_class.h
    JOB60842�T���v���v���O����
    USB�z�X�g �N���X�h���C�o�w�b�_

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _USBH_CLASS_H_
#define _USBH_CLASS_H_

/* �v���g�^�C�v�錾 */
/* mouse */
int mouse_status( int* );

/* JOB */
void *okijob_open( void );
int okijob_close( void* );
int okijob_bulk( void*, unsigned char, void*, unsigned long );
int okijob_number(void*);

#endif /* _USBH_CLASS_H_ */
