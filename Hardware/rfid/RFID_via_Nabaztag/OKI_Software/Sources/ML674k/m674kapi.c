/*******************************************************************************
    m674kapi.c
    JOB60842�T���v���v���O����
    ML674000 ���ʃ��[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include <stdio.h>
#include "config.h"


/*----------------------------------------------------------------------------*/
/*�O���[�o���ϐ���`*/
#define IRQ_NUM (32)
static struct _IRQ_Table{ 
	void (*Vector)(void);
}IRQ_Table[IRQ_NUM];				/*IRQ���荞�݃x�N�^�[�e�[�u��*/

/*----------------------------------------------------------------------------*/
/*�v���g�^�C�v�錾*/
static int peri_init(void);			/*����I/O�̏�����*/
static int IRQ_init(void);			/*IRQ���荞�݃R���g���[��������*/


/*----------------------------------------------------------------------------*/
/*�萔*/
#define BWC_VALUE	(0x000000A8)	/* �o�X���ݒ� */
#define ROMAC_VALUE	(0x00000003)	/* �O��ROM�ݒ� */
#define RAMAC_VALUE	(0x00000001)	/* �O��RAM�ݒ� */
#define IO0AC_VALUE	(0x00000001)	/* �O��IO�o���N0�ݒ� */

									/* �ėp�|�[�g�̐ݒ� */
#define GPCTL_VALUE (0x0004u |      /* �O���o�X�A�h���X */           \
                     0x0008u | 		/* DMA0�C�l�[�u�� */				\
					 0x0010u | 		/* DMA1�C�l�[�u�� */				\
					 0x0040u | 		/* �O���E�F�C�g�M���C�l�[�u�� */	\
					 0x0080u )		/* XWR�M���C�l�[�u�� */

#define DBWC_VALUE	(0x00000002)	/* DRAM�o�X���ݒ� 16bit */
#define DRMC_VALUE	(0x00000080)	/* DRAM�R���g���[���ݒ� */ 
#define DRPC_VALUE	(0x00000000)	/* DRAM�����p�����[�^�ݒ� */ 
#define SDMD_VALUE	(0x00000081)	/* SDRAM���[�h�ݒ� CL=2 */
#define RDWC_VALUE	(0x00000003)	/* SDRAM�p���[�_�E���R���g���[�� */
#define RFSH0_VALUE	(0x00000000)	/* SDRAM���t���b�V���T�C�N��0 x2 */
#define RFSH1_VALUE	(500)			/* SDRAM���t���b�V���T�C�N��1 64KHz @32MHx*/

#define DCMD_PALL	(0x00000004)	/* SDRAM�S�o���N�v���`���[�W */
#define DCMD_REF	(0x00000004)	/* SDRAM CBR���t���b�V�� */
#define DCMD_SELF	(0x00000006)	/* SDRAM�Z���t���t���b�V���J�n */
#define DCMD_SREX	(0x00000007)	/* SDRAM�Z���t���t���b�V����~ */


/*******************************************************************************
    Routine Name    �Fcpu_init
    Form            �Fint cpu_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FCPU�̏�����
*******************************************************************************/
int cpu_init(void)
{
	int ret;

	ret = peri_init();

	if(ret>=0)
	{
		ret = IRQ_init();
	}
	
	if(ret>=0)
	{
		ret = timera_init();
	}

	if(ret>=0)
	{
		ret = sio_init();
	}
	
#ifdef USE_SDRAM
	if(ret>=0)
	{
		sdram_init();
	}
#endif

	return ret;
}


/*******************************************************************************
    Routine Name    �Fperi_init
    Form            �Fstatic int peri_init(void);
    Parameters      �F
    Return value    �F���s����(���0��Ԃ�)
    Description     �F����I/O�̏�����
*******************************************************************************/
static int peri_init(void)
{
	/* �o�X���ݒ� */
	writel_reg(BWC, BWC_VALUE);
	
	/* �O��ROM�ݒ� */
	writel_reg(ROMAC, ROMAC_VALUE);

	/* �O��SRAM�ݒ� */
	writel_reg(RAMAC, RAMAC_VALUE);

	/* �O��IO�o���N0�ݒ� */
	writel_reg(IO0AC, IO0AC_VALUE);

	/* �ėp�|�[�g�̐ݒ� */
	writew_reg(GPCTL, GPCTL_VALUE);

	return 0;
}


/*******************************************************************************
    Routine Name    �Fsdram_init
    Form            �Fstatic int sdram_init(void);
    Parameters      �F
    Return value    �F���s����(���0��Ԃ�)
    Description     �FDRAM�R���g���[���̏�����
*******************************************************************************/
int sdram_init(void)
{
	int i;

	/* DRAM�R���g���[���̐ݒ� */
	writel_reg(DBWC, DBWC_VALUE);
	writel_reg(DRPC, DRPC_VALUE);

	writel_reg(DCMD, DCMD_PALL);

	for(i = 0; i < 8; i++)
	{
		writel_reg(DCMD, DCMD_REF);
	}

	writel_reg(DRMC, DRMC_VALUE);
	writel_reg(SDMD, SDMD_VALUE);
	writel_reg(RFSH0, RFSH0_VALUE);
	writel_reg(RFSH1, RFSH1_VALUE);
	writel_reg(RDWC, RDWC_VALUE);
	writel_reg(DCMD, DCMD_SREX);

	return 0;
}


/*******************************************************************************
    Routine Name    �FIRQ_init
    Form            �Fstatic int IRQ_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FIRQ���荞�݃R���g���[��������
*******************************************************************************/
static int IRQ_init(void)
{
	int i;
	
	writel_reg(ILC0, 0x00000000);
	writel_reg(ILC1, 0x00000000);
	writel_reg(ILC, 0x00000000);
	
	write_reg(CILCL, 0xFE);

	for(i=0 ; i<IRQ_NUM; i++)
	{
		IRQ_Table[i].Vector = NULL;
	}

	return 0;
}


/*******************************************************************************
    Routine Name    �FIRQ_Handler
    Form            �Fvoid __irq IRQ_Handler(void);
    Parameters      �F
    Return value    �F
    Description     �FIRQ���荞�݃n���h���[
*******************************************************************************/
void __irq IRQ_Handler(void)
{
	int   level;
	int   request;

	request = readl_reg(IRN) & IRN_MASK;
	level = readl_reg(CILE) & ILR_MASK;
	
	if(IRQ_Table[request].Vector != NULL)
	{
		IRQ_Table[request].Vector();
	}
	else
	{
		/* �f�o�b�O�̃����[�h���ُ̈튄�荞�ݑ΍� */
		IRQ_Install(request, 0, NULL);
	}
	
	if(level>0)
	{
		writel_reg(CIL, (0xFFul<<level) & 0xFEul);
	}

}


/*******************************************************************************
    Routine Name    �FIRQ_Install
    Form            �Fint IRQ_Install(int number, int level, void (*vector)(void));
    Parameters      �Fnumber            ���荞�ݔԍ�
                      level             ���荞�݃��x��
                      (*vector)(void)   ���荞�݃x�N�^
    Return value    �F���s����
    Description     �FIRQ���荞�݂̐ݒ�
*******************************************************************************/
int IRQ_Install(int number, int level, void (*vector)(void))
{
	int   ret;
	ULONG reg;
	ULONG bit;
	ULONG mask;
	ULONG work;

	switch(number)
	{
	case STMIRQ:
		reg = ILC0; 
		bit = ILR0; 
		break;
	case WDTIRQ:
	case WDTITVIRQ:
		reg = ILC0; 
		bit = ILR1; 
		break;
	case GPIOAIRQ:
	case GPIOBIRQ:
		reg = ILC0; 
		bit = ILR4; 
		break;
	case SOFTIRQ:
		reg = ILC1; 
		bit = ILR8; 
		break;
	case UARTIRQ:
		reg = ILC1; 
		bit = ILR9; 
		break;
	case SIOIRQ:
		reg = ILC1; 
		bit = ILR10; 
		break;
	case ADIRQ:
		reg = ILC1; 
		bit = ILR11; 
		break;
	case PWM0IRQ:
		reg = ILC1; 
		bit = ILR12; 
		break;
	case PWM1IRQ:
		reg = ILC1; 
		bit = ILR13; 
		break;
	case TMRIRQ0:
	case TMRIRQ1:
		reg = ILC;  
		bit = ILR16; 
		break;
	case TMRIRQ2:
	case TMRIRQ3:
		reg = ILC;  
		bit = ILR18; 
		break;
	case TMRIRQ4:
	case TMRIRQ5:
		reg = ILC;  
		bit = ILR20; 
		break;
	case DMAIRQ0:
	case DMAIRQ1:
		reg = ILC;  
		bit = ILR24; 
		break;
	case EIRQ0:
	case EIRQ1:
		reg = ILC;  
		bit = ILR28; 
		break;
	case EIRQ2:
	case EIRQ3:
		reg = ILC;  
		bit = ILR30; 
		break;
	default:
		reg = 0;
		bit = 0;
	}

	if((level>=0) && (level<=IRQLEVELMAX) && (reg>0ul))
	{
		IRQ_Table[number].Vector = vector;
		
		work = readl_reg(reg);
		mask = bit * ILR_MASK;
		work = work & ~mask ;
		mask = bit * (ULONG)level;
		work = work | mask;
		writel_reg(reg, work);
		ret = 0;
	}
	else
	{
		ret = -1;
	}

	return ret;
}	


/*******************************************************************************
    Routine Name    �Fdmemcpy
    Form            �Fint dmemcpy(void *dest, void *src, int size);
    Parameters      �Fdest              �f�X�e�B�l�[�V�����A�h���X
                      src               �\�[�X�A�h���X
                      size              �R�s�[�T�C�Y
    Return value    �F���s����
    Description     �FDMA���g�p�����������Ԃ̃f�[�^�R�s�[
*******************************************************************************/
int dmemcpy(void *dest, void *src, int size)
{
	int   ret;
	ULONG status;

	/*DMA��~*/
	write_reg(DMACMSK1, 1);

	/*�X�e�[�^�X�N���A*/
	writel_reg(DMACCINT1, 0);

	/*�]�����[�h*/
	writel_reg(DMACTMOD1, TRM_AUTO	/*�I�[�g���N�G�X�g*/
						| TSIZ_16  	/*�]���T�C�Y16b*/
						| SDP_INC	/*�\�[�X�A�h���X�C���N�������g*/
						| DDP_INC	/*�f�B�X�e�l�[�V�����A�h���X�C���N�������g*/
						| BRQ_BURST	/*�o�[�X�g*/
						| IMK_ENA	/*���荞�݃}�X�N�ݒ�*/
	);

	/*�\�[�X�A�h���X*/
	writel_reg(DMACSAD1, (ULONG)src);

	/*�f�B�X�e�l�[�V�����A�h���X*/
	writel_reg(DMACDAD1, (ULONG)dest);

	if((ULONG)size <= (DMACSIZ_MAX * sizeof(short)))
	{

		/*�]����*/
		writel_reg(DMACSIZ1, ((ULONG)size /sizeof(short)));

		/*DMA�J�n*/
		writel_reg(DMACMSK1, 0);

		/*�X�e�[�^�X�`�F�b�N*/
		do
		{
			status = readl_reg(DMASTA);
		}while((status & DMASTA_STA1) != 0ul);

		/*DMA��~*/
		write_reg(DMACMSK1, 1);

		status = readl_reg(DMAINT);
		if((status & DMAINT_ISTX1) == 0ul)
		{
			ret = 0;
		}
		else
		{
			dbg_printf(" DMA: src=%08X dest=%08X count=%08X status=%08X\n",
				readl_reg(DMACSAD1), readl_reg(DMACDAD1), readl_reg(DMACSIZ1), status);
			dbg_printf(" DMA: erorr!!\n");
			ret = -1;
		}
	}
	else
	{
		ret = -1;
	}

	return ret;
}


/*******************************************************************************
    Routine Name    �Fdma_start
    Form            �Fint dma_start(int dir, void *device, void *memory, int size);
    Parameters      �Fdir               �]������
                                        1: �f�o�C�X��������
                                        0: ���������f�o�C�X
                      device            �f�o�C�X�A�h���X�iDREQ����j
                      memory            �������A�h���X
                      size              �Z�b�g�T�C�Y
    Return value    �F���s����
    Description     �FDMA���g�p�����������Ԃ̃f�[�^�R�s�[
*******************************************************************************/
int dma_start(int dir, void *device, void *memory, int size)
{
	ULONG dma_dir;


	/*DMA��~*/
	writel_reg(DMACMSK0, 1);

	/*�X�e�[�^�X�N���A*/
	writel_reg(DMACCINT0, 0);

	if(dir==1)
	{
		/* ������ �� �O���f�o�C�X */
		dma_dir = SDP_INC	/*�\�[�X�A�h���X�C���N�������g*/
				| DDP_CONT;	/*�f�B�X�e�l�[�V�����A�h���X�Œ�*/

		/*�\�[�X�A�h���X*/
		writel_reg(DMACSAD0, (ULONG)memory);

		/*�f�B�X�e�l�[�V�����A�h���X*/
		writel_reg(DMACDAD0, (ULONG)device);

	}
	else
	{
		/* �O���f�o�C�X �� ������ */
		dma_dir = SDP_CONT	/*�\�[�X�A�h���X�Œ�*/
				| DDP_INC;	/*�f�B�X�e�l�[�V�����A�h���X�C���N�������g*/

		/*�\�[�X�A�h���X*/
		writel_reg(DMACSAD0, (ULONG)device);

		/*�f�B�X�e�l�[�V�����A�h���X*/
		writel_reg(DMACDAD0, (ULONG)memory);

	}

	/*�]�����[�h*/
	writel_reg(DMACTMOD0, TSIZ_16  	/*�]���T�C�Y16b*/
						| dma_dir	/*�]������*/
						| BRQ_CYCLE	/*�T�C�N���X�`�[��*/
						| IMK_ENA	/*���荞�݃}�X�N�ݒ�*/
	);


	/*�]����*/
	if((ULONG)size > (DMACSIZ_MAX * sizeof(short)))
	{
		writel_reg(DMACSIZ0, DMACSIZ_MAX);
	}
	else
	{
		writel_reg(DMACSIZ0, ((ULONG)size / sizeof(short)));
	}

	/*DMA�J�n*/
	writel_reg(DMACMSK0, 0);

	return 0;
}


/*******************************************************************************
    Routine Name    �Fdma_stop
    Form            �Fint dma_stop(int mode);
    Parameters      �Fmode              ��~���[�h
                                        1: �]�������҂�
                                        0: ������~
    Return value    �F���s����
    Description     �FDMA�]���̒�~
*******************************************************************************/
int dma_stop(int mode)
{
	int   ret = 0;
	ULONG status;

	/* �]�������҂� */
	if( mode == 1 )
	{
		do
		{
			status = readl_reg(DMASTA);
		}while((status & DMASTA_STA0) != 0ul);
	}

	/*DMA��~*/
	write_reg(DMACMSK0, 1);

	/* �]�������҂����A���s���ʊm�F */
	if( mode == 1 )
	{
		status = readl_reg(DMAINT);
		if((status & DMAINT_ISTX0) == 0ul)
		{
			ret = 0;
		}
		else
		{
			dbg_printf(" DMA: src=%08X dest=%08X count=%08X status=%08X\n",
				readl_reg(DMACSAD0), readl_reg(DMACDAD0), readl_reg(DMACSIZ0), status);
			dbg_printf(" DMA: erorr!!\n");
			ret = -1;
		}
	}

	return ret;
}


/* end of file */
