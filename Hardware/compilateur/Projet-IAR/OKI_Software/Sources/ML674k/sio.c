/*******************************************************************************
    sio.c
    JOB60842�T���v���v���O����
    ML674000 SIO ���䃋�[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>

#include "config.h"
#include "fifo.h"


#define SIO_WRITE_IGNORE_OVERFLOW
#define SIO_READ_IGNORE_OVERFLOW

/*--------------------------------------------------------------------------*/
/*�萔��`*/
#define CR (0x0d)
#define LF (0x0a)

#define	GPCTL_SIO	(0x0002ul)
#define D	(256 - SYSCLK * 1000000 / SIO_BAUDRATE / 16)	/* �{�[���[�g�ݒ� */


/*--------------------------------------------------------------------------*/
/*�O���[�o���ϐ���`*/
int sio_error_state = 0;
static int sio_send_active = 0;

static FIFO sio_read_fifo;
static FIFO sio_write_fifo;


/*--------------------------------------------------------------------------*/
/*�v���g�^�C�v�錾*/
static void sio_irq(void);
static int sio_write_fifo_pop(void);
static int sio_read_fifo_push(void);


/*******************************************************************************
    Routine Name    �Fsio_init
    Form            �Fint sio_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FSIO�̏�����
*******************************************************************************/
int sio_init(void)
{
	static char sio_read_buf[SIO_READBUFSIZE];
	static char sio_write_buf[SIO_WRITEBUFSIZE];
	ULONG ret;

	/* �|�[�g�C�l�[�u�� */
	ret = (ULONG)readw_reg(GPCTL);
	ret |= GPCTL_SIO;
	writew_reg(GPCTL, (USHORT)ret);

	/* FIFO�o�b�t�@�̏����� */
	fifo_init(&sio_read_fifo, sio_read_buf, SIO_READBUFSIZE);
	fifo_init(&sio_write_fifo, sio_write_buf, SIO_WRITEBUFSIZE);

	/* �{�[���[�g�̐ݒ� */
	writew_reg(SIOBT, D);

	/* SIO�R���g���[��
		bit2(TSTB)	= 0b;	// 0:2�X�g�b�v�r�b�g	1:1�X�g�b�v
		bit4(PEN)	= 0b;	// 0:��p���e�B		1:����
		bit4(PEN)	= 0b;	// 0:�p���e�B����		1:�L��
		bit1(LN)	= 0b;	// 0:�f�[�^��8�r�b�g	1:7�r�b�g
	*/
	writew_reg(SIOCON, 0x0000);
	
	/* �G���[�t���O�̃N���A */
	sio_send_active = 0;
	sio_error_state = 0;

	/* SIO�X�e�[�^�X�N���A */
	writew_reg(SIOSTA, 0x0037);

	/* SIO�^�C�}�[�C�l�[�u�� */
	writew_reg(SIOBCN, 0x0010);

	/* �_�~�[���[�h */
	ret = read_reg(SIOBUF);

	/* ���荞�݃n���h���[�ݒ� */
	IRQ_Install(SIOIRQ, IRQ_LV_SIO, sio_irq);

	return 0;
}


/*******************************************************************************
    Routine Name    �Fsio_irq
    Form            �Fstatic void sio_irq(void);
    Parameters      �F
    Return value    �F
    Description     �FSIO�̊��荞�ݏ���
*******************************************************************************/
static void sio_irq(void)
{
	ULONG ret;

	ret = (ULONG)readw_reg(SIOSTA);
		
	if((ret & (SIOSTA_PERR | SIOSTA_OERR | SIOSTA_FERR)) != 0ul)
	{	/*�G���[*/
		sio_error_state = 1;

		writew_reg(SIOSTA, (USHORT)ret);

		/* SIO�^�C�}�[�f�B�Z�[�u�� */
		writew_reg(SIOBCN, 0x0000);
	
	}
	
	else if((ret & SIOSTA_RVIRQ) != 0ul)
	{	/*��M�����f�[�^�L��*/
		writew_reg(SIOSTA, SIOSTA_RVIRQ);
		sio_read_fifo_push();
	}

	else if((ret & SIOSTA_TRIRQ) != 0ul)
	{	/*�]���o�b�t�@�G���v�e�B*/
		writew_reg(SIOSTA, SIOSTA_TRIRQ);

		if(fifo_status(&sio_write_fifo)>0)
		{
			sio_write_fifo_pop();
		}
		else
		{
			sio_send_active = 0;
		}
	}
	
	else
	{	/*�G���[*/
		sio_error_state = 1;

		/* SIO�^�C�}�[�f�B�Z�[�u�� */
		writew_reg(SIOBCN, 0x0000);
	}
}


/*******************************************************************************
    Routine Name    �Fsio_write_fifo_pop
    Form            �Fint sio_write_fifo_pop(void);
    Parameters      �F
    Return value    �F���s���ʁi���0�j
    Description     �FFIFO����SIO�ւ̕�����o��(���荞�ݎ������p)
*******************************************************************************/
int sio_write_fifo_pop(void)
{
	int data;

	data = fifo_pop(&sio_write_fifo);
	
	if(data!=0)
	{
		write_reg(SIOBUF, (UCHAR)data);
	}

	return 0;
}


/*******************************************************************************
    Routine Name    �Fsio_read_fifo_push
    Form            �Fstatic int sio_read_fifo_push(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FSIO����̓ǂݏo��(���荞�ݎ������p)
*******************************************************************************/
static int sio_read_fifo_push(void)
{
	int  ret;
	char data;

	data = (char)read_reg(SIOBUF);

	ret = fifo_push(&sio_read_fifo, data);

#ifndef SIO_READ_IGNORE_OVERFLOW
	if(ret<0)
	{
		sio_error_state = 1;
	}
#endif

	return ret;
}


/*******************************************************************************
    Routine Name    �Fsio_write
    Form            �Fint sio_write(const char *buf);
    Parameters      �Fbuf           ������
    Return value    �F���s����
    Description     �FSIO�֏o�͂��镶�����FIFO�ɏ�������
*******************************************************************************/
int sio_write(const char *buf)
{
	int  ret = 0;
	char data;

	while((*buf!=NULL) && (ret>=0) && (sio_error_state==0))
	{

		if(*buf=='\n')
		{
			data = CR;
			buf++;
		}
		else
		{
			data = *buf;
			buf++;
		}

		ret = fifo_push(&sio_write_fifo, data);
#ifndef SIO_WRITE_IGNORE_OVERFLOW
		if(ret<0)
		{
			sio_error_state = 1;
		}
#endif		
	}

	if((sio_send_active == 0) && (sio_error_state == 0))
	{
		if(fifo_status(&sio_write_fifo) > 0)
		{
			sio_send_active = 1;
			sio_write_fifo_pop();
		}
	}

	return ret;
}


/*******************************************************************************
    Routine Name    �Fsio_getc
    Form            �Fint sio_getc(void);
    Parameters      �F
    Return value    �F���͕���������ꍇ�ɂ́A���̕�����Ԃ�
                      ���͕������Ȃ��ꍇ�ɂ́A0��Ԃ�
    Description     �FSIO��FIFO����1�����ǂݏo��
*******************************************************************************/
int sio_getc(void)
{
	int ret;

	ret = fifo_pop(&sio_read_fifo);
	
	return ret;
}




/*******************************************************************************
    Routine Name    �Fsio_read
    Form            �Fint sio_read(char *buf, int size);
    Parameters      �Fbuf           ���͂��镶����o�b�t�@
                      size          �o�b�t�@�T�C�Y
    Return value    �F���펞�͓��͂��ꂽ��������Ԃ�
                      �G���[����-1��Ԃ�
    Description     �FSIO��FIFO���當����ǂݏo��
*******************************************************************************/
int sio_read(char *buf, int size)
{
	int ret;
	int len;

	if(size>0)
	{
		
		len = 1;
		ret = 0;
	
		while((ret>=0) && (ret!=CR) && (len < size) && (sio_error_state==0))
		{

			ret = fifo_pop(&sio_read_fifo);

			if((ret>=0) && (ret!=CR))
			{
				*buf++ = (char)ret;
				len++;
			}
		}
	}
	else
	{
		len = 0;
	}
	
	*buf = '\0';

	return len;
}


/*******************************************************************************
    Routine Name    �Fsio_printf
    Form            �Fvoid sio_printf(char * fmt, ...);
    Parameters      �Fprintf�Ɠ����t�H�[�}�b�g
    Return value    �F
    Description     �FSIO�֏o��
*******************************************************************************/
void sio_printf(char * fmt, ...)
{
	char    TextLine[LINEBUFSIZE];
	va_list args;

	va_start(args, fmt);
	vsprintf(TextLine, fmt, args);
	sio_write(TextLine);
}

