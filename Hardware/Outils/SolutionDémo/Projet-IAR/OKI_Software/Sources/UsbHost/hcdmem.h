/*******************************************************************************
    hcdmem.h
    JOB60842�T���v���v���O����
    USB�z�X�g �R���g���[������������w�b�_

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _HCDMEM_H_
#define _HCDMEM_H_

#define COMRAM	0
#define INTRAM	0
#define EXTRAM	2

int hcd_malloc_init(unsigned long, unsigned long, unsigned long, int);
void *hcd_malloc(unsigned long, int);
int hcd_free(void *);
void hcd_malloc_info(int);
int hcd_malloc_check(void *);
int hcd_malloc_rest(int);

#endif /* _HCDMEM_H_ */
