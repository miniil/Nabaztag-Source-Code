/*******************************************************************************
    usbp_req_clss.c
    JOB60842�T���v���v���O���� 
    �N���X���N�G�X�g����
    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "usbp.h"
/*******************************************************************************
	Routine Name:	usbp_class_func
	Form:			void usbp_class_func(void)
	Parameters:		����
	Return value:	����
	Description:	�N���X���N�G�X�g�����֐�
******************************************************************************/
void usbp_class_func(void)
{
	SET_STALL_EP0();
}

/* End of file */
