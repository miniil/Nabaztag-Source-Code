/*******************************************************************************
    sio.h
    JOB60842�T���v���v���O����
    ML674000 SIO ����w�b�_

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef SIO_H
#define SIO_H

/*----------------------------------------------------------------------------
  �萔��`
----------------------------------------------------------------------------*/
/*�o�b�t�@�T�C�Y*/
#ifndef SIO_WRITEBUFSIZE
#define SIO_WRITEBUFSIZE 1024
#endif

#ifndef SIO_READBUFSIZE
#define SIO_READBUFSIZE 16
#endif

/*�ʐM���x*/
#ifndef SIO_BAUDRATE
  #ifdef DEBUG_BAUDRATE
  #define SIO_BAUDRATE DEBUG_BAUDRATE
  #else
  #define SIO_BAUDRATE 19200
  #endif
#endif

#define SIOSTA_TRIRQ	0x20ul	/* SIO ���M���f�B */
#define SIOSTA_RVIRQ	0x10ul	/* SIO ��M���f�B */
#define SIOSTA_PERR		0x04ul	/* SIO �p���e�B�G���[ */
#define SIOSTA_OERR		0x02ul	/* SIO �I�[�o�[�����G���[ */
#define SIOSTA_FERR		0x01ul	/* SIO �t���[�~���O�G���[ */

/*----------------------------------------------------------------------------
  �O���[�o���ϐ�
----------------------------------------------------------------------------*/
extern int sio_error_state;

/*----------------------------------------------------------------------------
  �v���g�^�C�v�錾
----------------------------------------------------------------------------*/
int sio_init(void);
int sio_write(const char *);
int sio_read(char *, int);
int sio_getc(void);
void sio_printf(char *, ...);

#endif /* SIO_H */
