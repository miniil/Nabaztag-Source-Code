/*******************************************************************************
    usbp_main.c
    JOB60842�T���v���v���O���� 
    �y���t�F�������C���v���O����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/

#include "usbp.h"
#include "usbp_class.h"
#include "usbp_api.h"
#include "config.h"
#include "ml674000.h"
#include "m674kapi.h"


#if defined(PERI_TEST)
#include "usbp_test.h"
int loop_continue = 1;
#endif /*defined(PERI_TEST)*/

/*******************************************************************************
	Routine Name:	usbperi_init
	Form:			int usbperi_init(void)
	Parameters:		�Ȃ�
	Return value:	���펞�@E_OK
					�ُ펞�@E_NG
	Description:	�y���t�F�����h���C�o�̏��������s��
******************************************************************************/
int usbperi_init(void)
{
	int ret = E_OK;
	ret |= usbp_init(&device_descriptor1);
	ret |= usbp_set_callback_set_interface(usbp_bulk_init);
	return ret;
}

#if defined(PERI_TEST_MAIN)
/*******************************************************************************
	Routine Name:	main
	Form:			int main(void)
	Parameters:		�Ȃ�
	Return value:	��ɂO
	Description:	�e�X�g�p���C���֐�
******************************************************************************/
int main(void)
{
	uint loop;
	cpu_init();
	
    /* ���g���G���f�B�A���ݒ� */
    write_reg32(Endian, 0x00000000);

	/*���荞�݂̏�����*/
	write_reg32(SttTrnsCnt, read_reg32(SttTrnsCnt));
	write_reg32(OTGIntMask, 0x00000000);
	write_reg32(INTENBL, 0);
	write_reg32(HostCtl, B_DMAIRQ_MASK|B_OHCIIRQ_MASK);

	/*�y���t�F�����@�\�ɐ؊���*/
	write_reg32(HostPeriSel, B_PERI_SEL);
	/*�r�W�[�����҂�*/
	loop=0;
	while(read_reg32(HostPeriSel) & B_OPERATION){
		loop++;
	}
	write_reg32(RstClkCtl, 0x00000000);
	/*�y���t�F���������Z�b�g*/
	write_reg32(RstClkCtl, B_PRST);
	/*�r�W�[�����҂�*/
	loop=0;
	while(read_reg32(HostPeriSel) & B_OPERATION){
		loop++;
	}
    write_reg32(OTGCtl, (read_reg32(OTGCtl) & ~(B_PDCTLDP | B_PDCTLDM | B_PUCTLDP)) | B_ABSESSVLDENB );

	IRQ_Install(EIRQ3, IRQ_LV_EXUSB, usbp_interrupt);
	usbperi_init();
	
	usbp_main();
	return 0;
}
#endif /*defined(PERI_TEST)*/
/*******************************************************************************
    Routine Name    �Fusbp_main
    Form            �Fvoid usbp_main(void);
    Parameters      �F�Ȃ�
    Return value    �F�Ȃ�
    Description     �FUSB�y���t�F�������C������
*******************************************************************************/
void usbp_main(void)
{
#if defined(PERI_TEST)
#if defined(USBP_DEBUG_PRINT)
	sio_printf("USBP_DEBUG_PRINT_ENABLE\n");
#endif
	for(;;)
	{
		if(loop_continue == 0)
		{
			break;
		}
	}
#endif
    return;
}

/* End of file */
