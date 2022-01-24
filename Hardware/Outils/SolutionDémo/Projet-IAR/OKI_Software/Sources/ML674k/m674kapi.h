/*******************************************************************************
    m674kapi.h
    JOB60842�T���v���v���O����
    ML674000 ���ʃw�b�_

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef	_M674KAPI_H
#define	_M674KAPI_H

/*----------------------------------------------------------------------------
  �V�X�e���ݒ�萔��`
----------------------------------------------------------------------------*/
/* JOB60842�ݒ�l (�Œ�l) */
#define CPURAMBase		0x10000000l			/*����RAM*/
#define CPURAMSize		(1024*8)			/*8KBytes*/

#define ExtRAM1Base		0x00C00000l			/*�O��������1*/
#define ExtRAM1Size		(1024*512)			/*512KBytes*/

#define ExtRAM2Base		0xD0000000l			/*�O��������2*/
#define ExtRAM2Size		(1024*512)			/*512Bytes*/

#define ExtRAM3Base		0xC0000000l			/*�O��������3*/
#define ExtRAM3Size		(1024*2048)			/*2MBytes*/

#define ExtFlashBase	0x00800000l			/*����Flash������*/
#define ExtFlashSize	(1024*512)			/*512KByte*/

#define SYSCLK			32					/*����N���b�N���g��(MHz)*/

/* ���荞�݃��x���w�� */
#ifndef IRQ_LV_UART
#define IRQ_LV_UART		0					/*���荞�݃��x�� UART*/
#endif

#ifndef IRQ_LV_SIO
#define IRQ_LV_SIO		0					/*���荞�݃��x�� SIO*/
#endif

#ifndef IRQ_LV_TIMERA
#define IRQ_LV_TIMERA	0					/*���荞�݃��x�� �ėp�^�C�}�[*/
#endif

#ifndef IRQ_LV_EIR0
#define IRQ_LV_EIR0		0					/*���荞�݃��x�� �O��0*/
#endif

#ifndef IRQ_LV_EIR1
#define IRQ_LV_EIR1		0					/*���荞�݃��x�� �O��1*/
#endif

#ifndef IRQ_LV_EIR2
#define IRQ_LV_EIR2		0					/*���荞�݃��x�� �O��2*/
#endif

#ifndef IRQ_LV_EIR3
#define IRQ_LV_EIR3		0					/*���荞�݃��x�� �O��3*/
#endif

#ifndef LINEBUFSIZE
#define LINEBUFSIZE		128					/*print���̍ő啶����*/
#endif

/*----------------------------------------------------------------------------
  �萔��`
----------------------------------------------------------------------------*/
#ifndef NULL
#define	NULL		0
#endif

/* IRQ���x�����䃌�W�X�^ �t�B�[���h */
#define IRQLEVELMAX	7
#define IRN_MASK	0x1Ful
#define ILR_MASK	0x7ul
#define ILR0		0x00000001ul
#define ILR1		0x00000010ul
#define ILR4		0x00010000ul
#define ILR6		0x01000000ul
#define ILR8		0x00000001ul
#define ILR9		0x00000010ul
#define ILR10		0x00000100ul
#define ILR11		0x00001000ul
#define ILR12		0x00010000ul
#define ILR13		0x00100000ul
#define ILR14		0x01000000ul
#define ILR15		0x10000000ul
#define ILR16		0x00000001ul
#define ILR18		0x00000010ul
#define ILR20		0x00000100ul
#define ILR22		0x00001000ul
#define ILR24		0x00010000ul
#define ILR26		0x00100000ul
#define ILR28		0x01000000ul
#define ILR30		0x10000000ul

/* DMA�]�� */
#define TRM_DREQ	0x00ul	/* DMA�]�� DREQ���� */
#define TRM_AUTO	0x01ul	/* DMA�]�� �I�[�g���N�G�X�g */

#define TSIZ_8		0x00ul	/* DMA�]�� �f�[�^�T�C�Y 8�r�b�g */
#define TSIZ_16		0x02ul	/* DMA�]�� �f�[�^�T�C�Y 16�r�b�g */
#define TSIZ_32		0x04ul	/* DMA�]�� �f�[�^�T�C�Y 32�r�b�g */

#define SDP_CONT	0x00ul	/* DMA�]�� �\�[�X�A�h���X �Œ� */
#define SDP_INC		0x08ul	/* DMA�]�� �\�[�X�A�h���X �C���N�������g */

#define DDP_CONT	0x00ul	/* DMA�]�� �f�B�X�e�l�[�V�����A�h���X �Œ� */
#define DDP_INC		0x10ul	/* DMA�]�� �f�B�X�e�l�[�V�����A�h���X �C���N�������g */

#define BRQ_BURST	0x00ul	/* DMA�]�� �o�[�X�g���[�h */
#define BRQ_CYCLE	0x20ul	/* DMA�]�� �T�C�N���X�`�[�����[�h */

#define IMK_DIS		0x00ul	/* DMA�]�� ���荞�݃}�X�N���� */
#define IMK_ENA		0x40ul	/* DMA�]�� ���荞�݃}�X�N�ݒ� */

#define DMACSIZ_MAX	0x10000ul	/* DMA�]�� �ő��]�� */

#define DMASTA_STA0 	0x0000001ul	/* DMA�]�� �X�e�[�^�X CH0 */
#define DMASTA_STA1 	0x0000002ul	/* DMA�]�� �X�e�[�^�X CH1 */

#define DMAINT_ISTX0	0x00010100ul	/* DMA�]�� �I���X�e�[�^�X CH0 */
#define DMAINT_ISTX1	0x00020200ul	/* DMA�]�� �I���X�e�[�^�X CH1 */

/*----------------------------------------------------------------------------
  �O���[�o���ϐ���`
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  ���W�X�^�A�N�Z�X�}�N����`
----------------------------------------------------------------------------*/
typedef	unsigned char				UCHAR;
typedef	unsigned short				USHORT;
typedef	unsigned long				ULONG;
typedef	volatile unsigned char		VUCHAR;
typedef	volatile unsigned short		VUSHORT;
typedef	volatile unsigned long		VULONG;

#define	read_reg(n)		_read_reg(n)			/* 1Byte read  */
#define	write_reg(n,c)	_write_reg((n),(c))		/* 1Byte write */
#define	readw_reg(n)	_readw_reg(n)			/* 2Byte read  */
#define	writew_reg(n,c)	_writew_reg((n),(c))	/* 2Byte write */
#define	readl_reg(n)	_readl_reg(n)			/* 4Byte read  */
#define	writel_reg(n,c)	_writel_reg((n),(c))	/* 4Byte write */


/* 1Byte Read */
__inline UCHAR _read_reg(ULONG addr)
{
	UCHAR data = *(VUCHAR *)(addr);
	return data;
}

/* 2Byte Read */
__inline USHORT _readw_reg(ULONG addr)
{
	USHORT data = *(VUSHORT *)(addr);
	return data;
}

/* 4Byte Read */
__inline ULONG _readl_reg(ULONG addr)
{
	ULONG data = *(VULONG *)(addr);
	return data;
}

/* 1Byte write */
__inline void _write_reg(ULONG addr, UCHAR data)
{
	*(VUCHAR *)(addr) = (UCHAR)(data);
}

/* 2Byte write */
__inline void _writew_reg(ULONG addr, USHORT data)
{
	*(VUSHORT *)(addr) = (USHORT)(data);
}
/* 4Byte write */
__inline void _writel_reg(ULONG addr, ULONG data)
{
	*(VULONG *)(addr) = (ULONG)(data);
}


/*----------------------------------------------------------------------------
  �v���g�^�C�v�錾
----------------------------------------------------------------------------*/
int cpu_init(void);							/*CPU�̏�����*/
int sdram_init(void);						/*DRAM�R���g���[���̏�����*/

int IRQ_Install(int, int, void (*)(void));	/*IRQ���荞�݃x�N�^�[�̐ݒ�*/
void IRQ_Handler(void);						/*IRQ���荞�݃n���h���[*/

int dmemcpy(void *, void *, int);           /*DMAx�������R�s�[*/
int dma_start(int ,void *, void *, int);	/*DMA�X�^�[�g*/
int dma_stop(int);                          /*DMA�X�g�b�v */


/*----------------------------------------------------------------------------
  �R���\�[�����o��
----------------------------------------------------------------------------*/
/* print�� */
#define con_printf  sio_printf
#define con_getc    sio_getc

/* �f�o�b�O�o�� print�� */
#ifdef DEBUG
  #define dbg_printf sio_printf
#else
  __inline void dbg_printf(char * fmt, ...) { ; }	/* ������ */
#endif

#endif	/* _M671KAPI_H */
