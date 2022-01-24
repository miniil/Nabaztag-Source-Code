/*******************************************************************************
    timer.h
    JOB60842�T���v���v���O���� ML674000
    �^�C�}�[����w�b�_

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef TIMER_H
#define	TIMER_H

/*----------------------------------------------------------------------------
  �萔��`
----------------------------------------------------------------------------*/
#define MAXTMCH			5

#define CH0				0
#define CH1				1
#define CH2				2
#define CH3				3
#define CH4				4
#define CH5				5

#define MAXTMDIVD		5
#define MAXTMCOUNT		0x10000ul
#define TIMECNTL_CLKSEL	5
#define TIMECNTL_EN		0x0018ul
#define TM1MS 			1000

/*----------------------------------------------------------------------------
  �v���g�^�C�v�錾
----------------------------------------------------------------------------*/
int timera_init(void);
int auto_timera_set(int, int (*vector)(int));
int timera_set(int, int, int (*vector)(int));
int timera_over(int, int);
int timera_stop(int);
void mdelay(int);
void udelay(int);

#define GET_TIMER_ADDR(base, ch)	((base) + 0x20ul * (ULONG)(ch))

#endif /* TIMER_H */
