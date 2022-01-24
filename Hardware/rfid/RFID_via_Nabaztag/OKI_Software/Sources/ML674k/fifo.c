/*******************************************************************************
    fifo.c
    JOB60842�T���v���v���O����
    ML674000 FIFO�o�b�t�@���䃋�[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#include "fifo.h"


/*******************************************************************************
    Routine Name    �Ffifo_init
    Form            �Fint fifo_init(FIFO *fifo, char *buf, int size);
    Parameters      �Ffifo          ����������FIFO�o�b�t�@�ւ̃|�C���^
                      buf           �f�[�^�o�b�t�@�ւ̃|�C���^
                      size          �f�[�^�o�b�t�@�T�C�Y
    Return value    �F���s����(���0)
    Description     �FFIFO�̏�����
*******************************************************************************/
int fifo_init(FIFO *fifo, char *buf, int size)
{
	int i;

	fifo->data = buf;
	fifo->size = size;	
	fifo->start = 0;
	fifo->next = 0;

	for(i=0; i<size; i++)
	{
		fifo->data[i] = 0;
	}

	return 0;
}


/*******************************************************************************
    Routine Name    �Ffifo_pop
    Form            �Fint fifo_pop(FIFO *fifo);
    Parameters      �Ffifo          �ǂݏo��FIFO�o�b�t�@�ւ̃|�C���^
    Return value    �F���͕���������ꍇ�ɂ́A���̕�����Ԃ�
                      ���͕������Ȃ��ꍇ�ɂ́A0��Ԃ�
    Description     �FFIFO�o�b�t�@����1�����ǂݏo��
*******************************************************************************/
int fifo_pop(FIFO *fifo)
{
	int ret;

	if(fifo->start != fifo->next)
	{
		ret = fifo->data[fifo->start];
		fifo->start++;
		if(fifo->start >= fifo->size)
		{
			fifo->start = 0;
		}
	}
	else
	{
		ret = 0;
	}

	return ret;
}


/*******************************************************************************
    Routine Name    �Ffifo_push
    Form            �Fint fifo_push(FIFO *fifo, char data);
    Parameters      �Ffifo          ��������FIFO�o�b�t�@�ւ̃|�C���^
                      data          �������ރf�[�^
    Return value    �F���s����
    Description     �FFIFO�o�b�t�@�ւ̈ꕶ����������
*******************************************************************************/
int fifo_push(FIFO *fifo, char data)
{
	int ret;
	int next;

	next = fifo->next + 1;

	if(next >= fifo->size)
	{
		next = 0;
	}

	if(next != fifo->start)
	{
		fifo->data[fifo->next] = data;
		fifo->next = next;
		ret = 0;
	}
	else
	{
		ret = -1;
	}

	return ret;
}


/*******************************************************************************
    Routine Name    �Ffifo_status
    Form            �Fint fifo_status(FIFO *fifo);
    Parameters      �Ffifo          FIFO�o�b�t�@�ւ̃|�C���^
    Return value    �F���s����
    Description     �FFIFO�o�b�t�@�ւɗ��܂��Ă��镶����
*******************************************************************************/
int fifo_status(FIFO *fifo)
{
	int ret;

	if(fifo->next >= fifo->start)
	{
		ret = fifo->next - fifo->start;
	}
	else
	{
		ret = fifo->size + fifo->next - fifo->start; 
	}

	return ret;
}


/* end of file */
