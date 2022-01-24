/*******************************************************************************
    timera.c
    JOB60842�T���v���v���O����
    ML674000 �^�C�}�[���䃋�[�`�� (For �ėp�^�C�}�[)

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "config.h"

/*--------------------------------------------------------------------------*/
static struct _timer{
	int (*vector)(int);
	int count;
	int used;
} timer[MAXTMCH+1];


/*--------------------------------------------------------------------------*/
static void error(void);


/*******************************************************************************
    Routine Name    �Ftimera_irq
    Form            �Fstatic void timera_irq(int ch);
    Parameters      �Fch            �^�C�}�`���l���ԍ�
    Return value    �F
    Description     �F�^�C�}�[���荞�ݏ���
            �e�^�C�}�̊��荞��timer?_irq()����������
            ?�̓^�C�}�[�ԍ�(0�`MAXTMCH)�ɂȂ�
            �O���[�o���ϐ� timer[ch].count �͊��荞�݂����������񐔂�����
            �O���[�o���ϐ� timer[ch].count ���C���N�������g����
            ���荞�ݎ��̏�����ǉ�����ꍇ�́Atimera_set()�ɂď������[�`����
            �ǉ�����
*******************************************************************************/
static void timera_irq(int ch)
{
	ULONG status;

	status = (ULONG)readw_reg(GET_TIMER_ADDR(TIMESTAT0,ch));
	if((status & 0x0001ul) != 0ul)
	{
		writew_reg(GET_TIMER_ADDR(TIMESTAT0,ch), 0x0001);
		timer[ch].count++;
		if(timer[ch].vector != NULL)
		{
			timer[ch].vector(ch);
		}
	}
}

static void timer0_irq(void)
{
	timera_irq(CH0);
}

static void timer1_irq(void)
{
	timera_irq(CH1);
}

static void timer2_irq(void)
{
	timera_irq(CH2);
}

static void timer3_irq(void)
{
	timera_irq(CH3);
}

static void timer4_irq(void)
{
	timera_irq(CH4);
}

static void timer5_irq(void)
{
	timera_irq(CH5);
}




/*******************************************************************************
    Routine Name    �Ftimera_init
    Form            �Fint timera_init(void);
    Parameters      �F
    Return value    �F���s���ʁi���0�j
    Description     �F�^�C�}�[�̏�����
*******************************************************************************/
int timera_init(void)
{
	int i;
	
	for(i=0; i<=MAXTMCH; i++)
	{
		timer[i].used = 0;
		timer[i].vector = 0;
	}

	writew_reg(TIMECNTL0, 0);
	writew_reg(TIMECNTL1, 0);
	writew_reg(TIMECNTL2, 0);
	writew_reg(TIMECNTL3, 0);
	writew_reg(TIMECNTL4, 0);
	writew_reg(TIMECNTL5, 0);

	IRQ_Install(TMRIRQ0, IRQ_LV_TIMERA, timer0_irq);
	IRQ_Install(TMRIRQ1, IRQ_LV_TIMERA, timer1_irq);
	IRQ_Install(TMRIRQ2, IRQ_LV_TIMERA, timer2_irq);
	IRQ_Install(TMRIRQ3, IRQ_LV_TIMERA, timer3_irq);
	IRQ_Install(TMRIRQ4, IRQ_LV_TIMERA, timer4_irq);
	IRQ_Install(TMRIRQ5, IRQ_LV_TIMERA, timer5_irq);

	return 0;
}


/*******************************************************************************
    Routine Name    �Ftimera_set
    Form            �Fint timera_set(int ch, int us, int (*vector)(int));
    Parameters      �Fch                �g�p����^�C�}�[�ԍ� (0�`MAXTMCH)
                      us                ���荞�ݎ��� (�ʂr)
                      (*vector)(int)    ���荞�ݔ������������[�`��
    Return value    �F���s���ʁi���0�j
    Description     �F�^�C�}�[�ݒ聕�J�E���g�J�n
*******************************************************************************/
int timera_set(int ch, int us, int (*vector)(int))
{
	int   ret;
	int   divd;
	int   count;
	ULONG base;
	ULONG ctrl;

	if((ch>=0) && (ch<=MAXTMCH) && (timer[ch].used == 0) && (us >= 0))
	{
		count = us * SYSCLK;
		base = (ULONG)count;

		for(divd=0; (divd <= MAXTMDIVD) && (base >= MAXTMCOUNT); divd++)
		{
			base = base >> 1;
		}

		if((divd<=MAXTMDIVD) && (base<MAXTMCOUNT))
		{
			base = (MAXTMCOUNT - 1ul) - base;
			ctrl = (ULONG)divd << TIMECNTL_CLKSEL;
			ctrl |= TIMECNTL_EN;
	
			timer[ch].vector = vector;
			timer[ch].count = 0;
			timer[ch].used = 1;

			writew_reg(GET_TIMER_ADDR(TIMEBASE0,ch), (USHORT)base);
			writew_reg(GET_TIMER_ADDR(TIMESTAT0,ch), 0x0001);
			writew_reg(GET_TIMER_ADDR(TIMECNTL0,ch), (USHORT)ctrl);

			ret = 0;
		}
		else
		{
			ret = -1;
			error();	/* Debug!! */
		}
	}
	else
	{
		ret = -1;
		error();	/* Debug!! */
	}
	
	return ret;
}


/*******************************************************************************
    Routine Name    �Fauto_timera_set
    Form            �Fint auto_timera_set(int us, int (*vector)(int));
    Parameters      �Fus                ���荞�ݎ��� (�ʂr)
                      (*vector)(int)    ���荞�ݔ������������[�`��
    Return value    �F�g�p�����^�C�}�[�ԍ�(0�`MAXTMCH)
    Description     �F�^�C�}�[�ݒ聕�J�E���g�J�n
*******************************************************************************/
int auto_timera_set(int us, int (*vector)(int))
{
	int ch = MAXTMCH;
	int ret;

	while((timer[ch].used != 0) && (ch >= 0))
	{
		ch--;
	}

	if(ch>=0)
	{
		ret = timera_set(ch, us, vector);
		if(ret<0)
		{
			ch = -1;
			error();	/*Debug!!!*/
		}
	}
	else
	{
		ch = -1;
		error();	/*Debug!!!*/
	}
	
	return ch;
}


/*******************************************************************************
    Routine Name    �Ftimera_over
    Form            �Fint timera_over(int ch, int count);
    Parameters      �Fch                �g�p����^�C�}�[�ԍ� (0�`MAXTMCH)
                      count             ��r��
    Return value    �F���荞�ݔ����񐔂���r�񐔖����̏ꍇ0��Ԃ�
                      ��r�񐔈ȏ�̏ꍇ1��Ԃ�
    Description     �F�^�C�}�[���荞�݉񐔃`�F�b�N
*******************************************************************************/
int timera_over(int ch, int count)
{
	int status;


	
	if((ch>=0) && (ch<=MAXTMCH) && (timer[ch].used==1) && (count>=0))
	{
		if(timer[ch].count < count)
		{
			status = 0;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = -1;
		error();	/*Debug!!!*/
	}

	return status;
}


/*******************************************************************************
    Routine Name    �Ftimera_stop
    Form            �Fint timera_stop(int ch);
    Parameters      �Fch                �g�p����^�C�}�[�ԍ� (0�`MAXTMCH)
    Return value    �F���s���ʁi���0�j
    Description     �F�^�C�}�[��~
*******************************************************************************/
int timera_stop(int ch)
{
	int ret = 0;
	
	if((ch>=0) && (ch<=MAXTMCH) && (timer[ch].used==1))
	{
		writew_reg(GET_TIMER_ADDR(TIMECNTL0,ch), 0x0000);
		writew_reg(GET_TIMER_ADDR(TIMESTAT0,ch), 0x0001);

		timer[ch].vector = 0;
		timer[ch].used = 0;
	}
	else
	{
		ret = -1;
		error();	/*Debug!!!*/
	}

	return ret;
}


/*******************************************************************************
    Routine Name    �Fmdelay
    Form            �Fvoid mdelay(int ms);
    Parameters      �Fms                �f�B���C����(���b)
    Return value    �F
    Description     �F���b�P�ʂ̃f�B���C
*******************************************************************************/
void mdelay(int ms)
{
	int ch;

	ch = auto_timera_set(TM1MS, NULL);

	while(!timera_over(ch, ms))
	{
		/* */
	}

	timera_stop(ch);
}


/*******************************************************************************
    Routine Name    �Fudelay
    Form            �Fvoid udelay(int us);
    Parameters      �Fus                �f�B���C����(�ʕb)
    Return value    �F
    Description     �F�ʕb�P�ʂ̃f�B���C
*******************************************************************************/
void udelay(int us)
{
	int ch;


	ch = auto_timera_set(us, timera_stop);

	while(!timera_over(ch, 1))
	{
		/* */
	}
}


/****************************************************************************/
static void error(void)
{
	dbg_printf("Error!! Setting of timer...\n");

#ifndef NOT_FAIL_STOP
	for(;;)	/*Dead loop!!*/
	{
		/* */
	}
	/*
	** �{�\�[�X�ł̓^�C�}�̐ݒ�̌�肪����Ƃ��̃��[�`�����Ŗ������[�v���
	** �ƂȂ�܂�
	*/
#endif
}


/*****************************************************************************
// ���荞�ݏ������[�`���L�q��

	���荞�ݏ������[�`���͕K�� void FUNCTION(int); �Œ�`����
	���̗�ł̓^�C�}�[���荞�݂�1ms���Ɣ��������A10�b�ɂȂ�����UART���u���[�N
	��Ԃɂ��A�^�C�}�[���~����
	
	�E�E�E���C�����[�`����
	timera_set(3, 1000, set_uart_break);

	�E�E�E
	void set_uart_break(int ch)
	{
		if(timera_over(ch, 10000)
		{
			uart_break_state = 1;
			timera_stop(ch);
		}
	}

*****************************************************************************/

