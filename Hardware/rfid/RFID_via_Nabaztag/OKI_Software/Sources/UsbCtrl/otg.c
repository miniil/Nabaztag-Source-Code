/*******************************************************************************
    otg.c
    JOB60842�T���v���v���O���� OTG ����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev.1.00:�V�K�쐬
*******************************************************************************/
#define DEBUG

#include "typedef.h"
#include "config.h"
#include "usbctrl.h"
#include "otg.h"

/* �^�C�} */
#ifndef TIMER_ON
  #define TIMER_ON(ms)		do{ otg_tmr_ch = auto_timera_set(1000, (ms)); } while(0)
#endif
#ifndef TIMER_OFF
  #define TIMER_OFF()		timera_stop(otg_tmr_ch)
#endif

/* �^�C�}���Ԑݒ� */
#define TA_WAIT_VRISE		100		/* Max.100(ms) */
#define TA_WAIT_BCON		200		/* Min.200(ms) */
#define TA_AIDL_BDIS		250		/* Min.150(ms) */
#define TB_ASE0_BRST		60		/* Min.3.125(ms) */ /* ���Z�b�g���Ԋ܂� */

#define TB_SRP_FAIL			5000	/* Min.5000(ms) Max.30000(ms) */

/* �E�F�C�g���Ԑݒ� */
#define TW_PULLUP           7       /* �����l 85ns    2ms�����オ�莞�ԑO�K�v */
#define TW_PULLDOWN         2       /* �����l 1.58��s DatalinePulling 5�`10ms */
#define TW_VBUS_CHAGE		22		/* �����l 12.2ms  �K�i�l �`22ms(Derived)  */
#define TW_VBUS_DISCHAGE	50		/* �����l 34.8ms  �K�i�l 100ms�ȉ�        */


/*�O���[�o���ϐ�*/
int usbctrl_otg_state = OTG_DISABLE;/* ���݂�OTG�X�e�[�g��ێ����� */
BIT32 usbctrl_otg_status = 0;		/* OTG�X�e�[�g����t���O��ێ����� */
static int otg_tmr_ch = 0;			/* OTG����Ŏg�p���Ă���^�C�}�ԍ� */
int usbctrl_otg_message = 0; 		/* OTG���b�Z�[�W�ԍ� */

/*�v���g�^�C�v�錾*/
static void usbctrl_otg_sess_chk(int); 

/******************************************************************************/
/*OTG�X�e�[�g����t���O��`*/

#define id					usbctrl_otg_status.bit.b00

#define a_bus_req			usbctrl_otg_status.bit.b02
#define a_suspend_req		usbctrl_otg_status.bit.b03
#define a_bus_drop			usbctrl_otg_status.bit.b04
#define a_srp_det			usbctrl_otg_status.bit.b05
#define a_set_b_hnp_en		usbctrl_otg_status.bit.b06
#define a_host_release		usbctrl_otg_status.bit.b07

#define a_vbus_vld			usbctrl_otg_status.bit.b08
#define a_sess_vld			usbctrl_otg_status.bit.b09
#define b_conn				usbctrl_otg_status.bit.b10
#define b_bus_suspend		usbctrl_otg_status.bit.b11
#define b_bus_resume		usbctrl_otg_status.bit.b12
#define a_wait_vrise_tmout	usbctrl_otg_status.bit.b13
#define a_wait_bcon_tmout	usbctrl_otg_status.bit.b14
#define a_aidl_bdis_tmout	usbctrl_otg_status.bit.b15

#define b_bus_req			usbctrl_otg_status.bit.b16
#define b_hnp_en			usbctrl_otg_status.bit.b20
#define a_hnp_support		usbctrl_otg_status.bit.b21
#define a_alt_hnp_support	usbctrl_otg_status.bit.b22
#define b_srp_fail_tmout	usbctrl_otg_status.bit.b23

#define b_sess_vld			usbctrl_otg_status.bit.b24
#define b_sess_end			usbctrl_otg_status.bit.b25
#define a_conn				usbctrl_otg_status.bit.b26
#define a_bus_suspend		usbctrl_otg_status.bit.b27
#define a_bus_resume		usbctrl_otg_status.bit.b28
#define b_se0_srp			usbctrl_otg_status.bit.b29
#define b_srp_done			usbctrl_otg_status.bit.b30
#define b_ase0_brst_tmout	usbctrl_otg_status.bit.b31


/*******************************************************************************
    Routine Name    �Fusbctrl_otg_init
    Form            �Fint usbctrl_otg_init(void);
    Parameters      �F
    Return value    �F
    Description     �FOTG�X�e�[�g�}�V���̏�����
*******************************************************************************/
int usbctrl_otg_init(void)
{
	/*OTG����X�^�[�g*/
	usbctrl_otg_state = OTG_START;
	usbctrl_otg_status.word = 0;

	usbctrl_vbus_thress(VBUS_NC);
	usbctrl_vbus_set(VBUS_OFF);
	usbctrl_mode_set(USB_IDLE);

	id = usbctrl_id_check();
	usbctrl_otg_sess_chk(usbctrl_vbus_status());
	usbctrl_otg_control();

	return E_OK;
}


/*******************************************************************************
    Routine Name    �Fusbctrl_otg_request
    Form            �Fint usbctrl_otg_request(int req);
    Parameters      �Freq           ���N�G�X�g
    Return value    �F���s����
    Description     �FOTG ���N�G�X�g
*******************************************************************************/
int usbctrl_otg_request(int req)
{

	switch(req){
		case BUS_REQ:
			if(id)
			{
				b_bus_req = TRUE;
				b_srp_done = FALSE;
			}
			else
			{
				a_bus_req = TRUE;
				a_suspend_req = FALSE;
				a_bus_drop = FALSE;
			}
			break;
			
		case DROP_REQ:
			if(id)
			{
				b_bus_req = FALSE;
			}
			else
			{
				a_bus_req = FALSE;
				a_bus_drop = TRUE;
			}
			break;

		case SUSPEND_REQ:
			if(id)
			{
				b_bus_req = FALSE;
			}
			else
			{
				a_bus_req = FALSE;
				a_suspend_req = TRUE;
				a_bus_drop = FALSE;
			}
			break;

		case HNP_ENABLE_SET:
			if(!id)
			{
				a_set_b_hnp_en = TRUE;
				a_host_release = TRUE;	
			}
			break;
			
		case HNP_NOT_SUPPORTED:
			if(!id)
			{
				usbctrl_otg_message = 0x10;
				a_host_release = TRUE;	
			}
			break;

		case B_HNP_ENABLE_SET:
			if(id)
			{
				b_hnp_en = TRUE;
				a_hnp_support = TRUE;
			}

		case A_HNP_SUPPORT_SET:
			if(id)
			{
				a_hnp_support = TRUE;
			}
			break;

		case A_ALT_HNP_SUPPORT_SET:
			if(id)
			{
				a_alt_hnp_support = TRUE;
			}
			break;
			
		case B_CONFIGRATION:
			if(id && !b_hnp_en)
			{
				usbctrl_otg_message = 0x12;
			}
			break;
			
		case B_UNCONFIGRATION:
			if(id)
			{
				b_hnp_en = FALSE;
				a_hnp_support = FALSE;
				a_alt_hnp_support = FALSE;
				a_bus_suspend = FALSE;
			}
			break;

		case CONNECT:
			if(id)
			{
				a_conn = TRUE;
			}
			else
			{
				b_conn = TRUE;
			}
			break;

		case DISCONNECT:
			if(id)
			{
				a_conn = FALSE;
			}
			else
			{
				b_conn = FALSE;
			}
			break;

		case BUS_SUSPENDED:
			if(id)
			{
				a_bus_suspend = TRUE;
			}
			else
			{
				b_bus_suspend = TRUE;
			}
			break;

		default:
			return E_NG;
	}

	usbctrl_otg_control();

	return E_OK;
}


/*******************************************************************************
    Routine Name    �Fusbctrl_otg_srp
    Form            �Fint usbctrl_otg_srp(void);
    Parameters      �F
    Return value    �F���s����
    Description     �FOTG SRP (VBUS Pulsing)
*******************************************************************************/
int usbctrl_otg_srp(void)
{
	if(usbctrl_state == STATE_OTG_SRP){
    	writel_reg(OTGIntMask, B_IDSELCHGINT);

        /* Data Line Pulsing */
        usbctrl_resistance_set(PULLUP);
        mdelay(TW_PULLUP);

        usbctrl_resistance_set(PULLDOWN);
        mdelay(TW_PULLDOWN);

        /* VBUS Pulsing */
	    usbctrl_vbus_set(VBUS_CHARGE);
	    mdelay(TW_VBUS_CHAGE);

	    usbctrl_vbus_set(VBUS_DISCHARGE);
	    mdelay(TW_VBUS_DISCHAGE);

	    usbctrl_vbus_set(VBUS_OFF);
	    writel_reg(OTGIntMask, B_IDSELCHGINT|B_AVBUSVLDCHGINT);

		b_srp_done = TRUE;
		usbctrl_otg_control();

		return E_OK;
	}

	return E_NG;
}


/*******************************************************************************
    Routine Name    �Fusbctrl_otg_sess_chk
    Form            �Fstatic void usbctrl_otg_sess_chk(int vbus);
    Parameters      �Fvbus          VBUS�d�����
    Return value    �F
    Description     �FOTG �Z�b�V���� �`�F�b�N
*******************************************************************************/
static void usbctrl_otg_sess_chk(int vbus)
{

	if( id ){
		if(vbus == 0){
			b_sess_vld = FALSE;
			b_sess_end = TRUE;
		}
		else{
			b_sess_vld = TRUE;
			b_sess_end = FALSE;
		}
		a_sess_vld = FALSE;
		a_vbus_vld = FALSE;
	}
	else{
		if(vbus == 0){
			a_sess_vld = FALSE;
			a_vbus_vld = FALSE;
		}
		else if(vbus == 1){
			a_sess_vld = TRUE;
			a_vbus_vld = FALSE;
		}
		else if(vbus == 2){
			a_sess_vld = TRUE;
			a_vbus_vld = TRUE;
		}
		b_sess_vld = FALSE;
		b_sess_end = FALSE;
	}

	return;
}

/*******************************************************************************
    Routine Name    �Fusbctrl_otg_get_state
    Form            �Fint usbctrl_otg_get_state(void);
    Parameters      �F
    Return value    �F
    Description     �FOTG�X�e�[�g�ԍ���Ԃ��B
*******************************************************************************/
int usbctrl_otg_get_state(void)
{
	return usbctrl_otg_state;
}

/*******************************************************************************
    Routine Name    �Fusbctrl_otg_message_get
    Form            �Fint usbctrl_otg_message_get(void);
    Parameters      �F
    Return value    �F
    Description     �F���b�Z�[�W�ԍ���Ԃ��B���b�Z�[�W���Ȃ��Ƃ���0��Ԃ��B
                      �R�[������ƃ��b�Z�[�W�ԍ��̓N���A�����B
*******************************************************************************/
int usbctrl_otg_message_get(void)
{
	int message;
	
	message = usbctrl_otg_message;
	usbctrl_otg_message = 0;
	
	return message;
}


/*******************************************************************************
    Routine Name    �Fusbctrl_vbus_changed
    Form            �Fint usbctrl_vbus_changed(void);
    Parameters      �F
    Return value    �F
    Description     �FSVBUS�[�q���荞�݂����������Ƃ��Ɋ��荞�݃n���h������Ăяo��
*******************************************************************************/
void usbctrl_vbus_changed(void)
{
	if(usbctrl_otg_state == OTG_A_IDLE){
		a_srp_det = TRUE;	
	}
	
	usbctrl_otg_sess_chk(usbctrl_vbus_status());

	usbctrl_otg_control();
}

/*******************************************************************************
    Routine Name    �Fusbctrl_id_changed
    Form            �Fint usbctrl_vbus_changed(void);
    Parameters      �F
    Return value    �F
    Description     �FID�[�q���荞�݂����������Ƃ��Ɋ��荞�݃n���h������Ăяo��
*******************************************************************************/
void usbctrl_id_changed(void)
{
	id = usbctrl_id_check();

	usbctrl_otg_sess_chk(usbctrl_vbus_status());

	usbctrl_otg_control();
}


/*******************************************************************************
    Routine Name    �Fusbctrl_se0_det
    Form            �Fint usbctrl_se0_det(void);
    Parameters      �F
    Return value    �F
    Description     �FSE0��Ԃ����o�����Ƃ��Ɋ��荞�݃n���h������Ăяo��
*******************************************************************************/
void usbctrl_se0_det(void)
{
	if(usbctrl_otg_state == OTG_B_SRP_PRE){
		b_se0_srp = TRUE;
		usbctrl_otg_control();
	}
}


/*******************************************************************************
    Routine Name    �Fa_wait_vrise_tmr
    Form            �Fint a_wait_vrise_tmr(int ch);
    Parameters      �Fint ch    �^�C�}�`���l��
    Return value    �F
    Description     �F�^�C�}�R�[���o�b�N�֐�
                      �ua_wait_vrise�v��ԂŁATA_WAIT_VRISE �ȏ�o�߂����Ƃ��A
                      a_wait_vrise_tmout���Z�b�g����
*******************************************************************************/
static int a_wait_vrise_tmr(int ch)
{
	if(timera_over(ch, TA_WAIT_VRISE)){
		if(usbctrl_otg_state == OTG_A_WAIT_VRISE){
			a_wait_vrise_tmout = TRUE;
			usbctrl_otg_control();
		}
	}
	return 0;
}

/*******************************************************************************
    Routine Name    �Fa_wait_bcon_tmr
    Form            �Fint a_wait_bcon_tmr(int ch);
    Parameters      �Fint ch    �^�C�}�`���l��
    Return value    �F
    Description     �F�^�C�}�R�[���o�b�N�֐�
                      �ua_wait_bcon�v��ԂŁATA_WAIT_BCON �ȏ�o�߂����Ƃ��A
                      a_wait_bcon_tmout���Z�b�g����
*******************************************************************************/
static int a_wait_bcon_tmr(int ch)
{
	if(timera_over(ch, TA_WAIT_BCON)){
		if(usbctrl_otg_state == OTG_A_WAIT_BCON){
			a_wait_bcon_tmout = TRUE;
			usbctrl_otg_control();
		}
	}
	return 0;
}

/*******************************************************************************
    Routine Name    �Fa_aidl_bdis_tmr
    Form            �Fint a_aidl_bdis_tmr(int ch);
    Parameters      �Fint ch    �^�C�}�`���l��
    Return value    �F
    Description     �F�^�C�}�R�[���o�b�N�֐�
                      �ua_suspend�v��ԂŁATA_AIDL_BDIS �ȏ�o�߂����Ƃ��A
                      a_aidl_bdis_tmout���Z�b�g����
*******************************************************************************/
static int a_aidl_bdis_tmr(int ch)
{
	if(timera_over(ch, TA_AIDL_BDIS)){
		if(usbctrl_otg_state == OTG_A_SUSPEND){
			a_aidl_bdis_tmout = TRUE;
			usbctrl_otg_control();
		}
	}
	return 0;
}

/*******************************************************************************
    Routine Name    �Fb_ase0_brst_tmr
    Form            �Fint b_ase0_brst_tmr(int ch);
    Parameters      �Fint ch    �^�C�}�`���l��
    Return value    �F
    Description     �F�^�C�}�R�[���o�b�N�֐�
                      �ub_wait_acon�v��ԂŁATB_ASE0_BRST �ȏ�o�߂����Ƃ��A
                      b_ase0_brst_tmout���Z�b�g����
*******************************************************************************/
static int b_ase0_brst_tmr(int ch)
{
	if(timera_over(ch, TB_ASE0_BRST)){
		if(usbctrl_otg_state == OTG_B_WAIT_ACON){
			b_ase0_brst_tmout = TRUE;

			usbctrl_otg_control();
		}
	}
	return 0;
}

/*******************************************************************************
    Routine Name    �Fb_srp_fail_tmr
    Form            �Fint b_srp_fail_tmr(int ch);
    Parameters      �Fint ch    �^�C�}�`���l��
    Return value    �F
    Description     �F�^�C�}�R�[���o�b�N�֐�
                      �ub_idle�v��ԂŁATB_SRP_FAIL �ȏ�o�߂����Ƃ��A
                      b_srp_fail_tmout���Z�b�g����
*******************************************************************************/
static int b_srp_fail_tmr(int ch)
{
	if(timera_over(ch, TB_SRP_FAIL)){
		if(usbctrl_otg_state == OTG_B_IDLE){
			b_srp_fail_tmout = TRUE;

			usbctrl_otg_control();
		}
	}
	return 0;
}

#ifdef DEBUG
/*******************************************************************************
    Routine Name    �Fusbctrl_print_otg_state
    Form            �Fstatic void usbctrl_print_otg_state(void);
    Parameters      �F
    Return value    �F
    Description     �FOTG �X�e�[�g�\��
*******************************************************************************/
static void usbctrl_print_otg_state(void)
{
	switch(usbctrl_otg_state){
        case OTG_DISABLE:
            con_printf(" OTG: disable\n"); break;
		case OTG_START: 
			con_printf(" OTG: start\n"); break;
		case OTG_A_IDLE:
			con_printf(" OTG: a_idle\n"); break;
		case OTG_A_WAIT_VRISE:
			con_printf(" OTG: a_wait_vrise\n"); break;
		case OTG_A_WAIT_BCON:
			con_printf(" OTG: a_wait_bcon\n"); break;
		case OTG_A_HOST:
			con_printf(" OTG: a_host\n"); break;
		case OTG_A_SUSPEND:
			con_printf(" OTG: a_suspend\n"); break;
		case OTG_A_PERIPHERAL:
			con_printf(" OTG: a_peripheral\n"); break;
		case OTG_A_WAIT_VFALL:
			con_printf(" OTG: a_wait_vfall\n"); break;
		case OTG_A_VBUS_ERR:
			con_printf(" OTG: a_vbus_err\n"); break;
		case OTG_B_IDLE:
			con_printf(" OTG: b_idle\n"); break;
		case OTG_B_SRP_PRE:
			con_printf(" OTG: b_srp_pre\n"); break;
		case OTG_B_SRP_INIT:
			con_printf(" OTG: b_srp_init\n"); break;
		case OTG_B_PERIPHERAL:
			con_printf(" OTG: b_peripheral\n"); break;
		case OTG_B_WAIT_ACON:
			con_printf(" OTG: b_wait_acon\n"); break;
		case OTG_B_HOST:
			con_printf(" OTG: b_host\n"); break;
		default:
			con_printf(" OTG: ????? 0x%02X\n", usbctrl_otg_state);
	}

	con_printf("  ");
	if(id)					con_printf(" id");
	if(a_vbus_vld)			con_printf(" a_vbus_vld");
	if(a_sess_vld)			con_printf(" a_sess_vld");
	if(b_sess_vld)			con_printf(" b_sess_vld");
	if(b_sess_end)			con_printf(" b_sess_end");
	if(a_bus_req)			con_printf(" a_bus_req");
	if(b_bus_req)			con_printf(" b_bus_req");
	if(a_suspend_req)		con_printf(" a_suspend_req");
	if(a_conn)				con_printf(" a_conn");
	if(b_conn)				con_printf(" b_conn");
	if(a_bus_suspend)		con_printf(" a_bus_suspend");
	if(b_bus_suspend)		con_printf(" b_bus_suspend");
	if(a_bus_resume)		con_printf(" a_bus_resume");
	if(b_bus_resume)		con_printf(" b_bus_resume");
	if(a_bus_drop)			con_printf(" a_bus_drop");
	if(b_se0_srp)			con_printf(" b_se0_srp");
	if(b_srp_done)			con_printf(" b_srp_done");
	if(a_srp_det)			con_printf(" a_srp_det");
	if(a_set_b_hnp_en)		con_printf(" a_set_b_hnp_en");
	if(b_hnp_en)			con_printf(" b_hnp_en");
	if(a_wait_vrise_tmout)	con_printf(" a_wait_vrise_tmout");
	if(a_wait_bcon_tmout)	con_printf(" a_wait_bcon_tmout");
	if(a_aidl_bdis_tmout)	con_printf(" a_aidl_bdis_tmout");
	if(b_ase0_brst_tmout)	con_printf(" b_ase0_brst_tmout");
	if(a_hnp_support)		con_printf(" a_hnp_support");
	if(a_alt_hnp_support)	con_printf(" a_alt_hnp_support");
	con_printf("\n");

}
#endif

/*******************************************************************************
    Routine Name    �Fusbctrl_otg_control
    Form            �Fvoid usbctrl_otg_control(void);
    Parameters      �F
    Return value    �F
    Description     �FOTG �X�e�[�g����
*******************************************************************************/
void usbctrl_otg_control(void)
{

	while(1){

#ifdef DEBUG
		usbctrl_print_otg_state();
#endif
		switch(usbctrl_otg_state)
		{

        case OTG_DISABLE:
            break;

		case OTG_START:
			if(id)
			{
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_otg_state = OTG_B_IDLE;
			}
			else
			{
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_otg_state = OTG_A_IDLE;
			}
			continue;

	/* ----- A-device ----- */
		case OTG_A_IDLE:
			if(id)
			{
				a_bus_req = FALSE;
				a_suspend_req = FALSE;
				a_conn = FALSE;
				a_srp_det = FALSE;
				usbctrl_otg_state = OTG_B_IDLE; 
				continue;
			}
			else if(!a_bus_drop && (a_bus_req || a_srp_det))
			{
				a_srp_det = FALSE;
				a_wait_vrise_tmout = FALSE;
				usbctrl_vbus_thress(VBUS_RISE);
				usbctrl_vbus_set(VBUS_ON);
				TIMER_ON(a_wait_vrise_tmr);
				usbctrl_otg_state = OTG_A_WAIT_VRISE;
				continue;
			}
			break;

		case OTG_A_WAIT_VRISE:
			if(a_vbus_vld)
			{
				TIMER_OFF();	/* a_wait_vrise_tmr */
				a_wait_bcon_tmout = FALSE;
				usbctrl_mode_set(USB_HOST);
				TIMER_ON(a_wait_bcon_tmr);
				usbctrl_otg_state = OTG_A_WAIT_BCON;
				continue;
			}
			else if(id | a_bus_drop | a_wait_vrise_tmout)
			{
				TIMER_OFF();	/* a_wait_vrise_tmr */
				a_wait_vrise_tmout = FALSE;
				a_wait_bcon_tmout = FALSE;
				TIMER_ON(a_wait_bcon_tmr);
				usbctrl_otg_state = OTG_A_WAIT_BCON;
				continue;
			}
			break;

		case OTG_A_WAIT_BCON:
			if(id | a_bus_drop | a_wait_bcon_tmout)
			{
				TIMER_OFF();	/* a_wait_bcon_tmr */
				a_wait_bcon_tmout = FALSE;
				b_conn = FALSE;	/* a_wait_vfall�X�e�[�g�ł�b_conn/�J�ڏ��� */
				usbctrl_mode_set(USB_IDLE);
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_OFF);
				usbctrl_otg_state = OTG_A_WAIT_VFALL;
				continue;
			}
			else if(!a_vbus_vld)
			{
				TIMER_OFF();	/* a_wait_bcon_tmr */
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_DISCHARGE);
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_message = 0x10;
				usbctrl_otg_state = OTG_A_VBUS_ERR;
				continue;
			}
			else if(b_conn)
			{
				TIMER_OFF();	/* a_wait_bcon_tmr */
				a_host_release = FALSE;
				usbctrl_vbus_thress(VBUS_FALL);
				usbctrl_otg_state = OTG_A_HOST;
				continue;
			}
			break;

		case OTG_A_HOST:
			if(!a_vbus_vld)
			{
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_DISCHARGE);
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_message = 0x10;
				usbctrl_otg_state = OTG_A_VBUS_ERR;
				continue;
			}
			else if(id || !b_conn || a_bus_drop)
			{
				a_wait_bcon_tmout = FALSE;
				TIMER_ON(a_wait_bcon_tmr);
				usbctrl_otg_state = OTG_A_WAIT_BCON;
				usbctrl_mode_set(USB_IDLE);
				continue;
			}
			else if((a_suspend_req || !a_bus_req ) && a_host_release)
			{
				a_aidl_bdis_tmout = FALSE;
                writel_reg(HcControl, (readl_reg(HcControl) | OHCI_USB_SUSPEND) );
				TIMER_ON(a_aidl_bdis_tmr);
				usbctrl_otg_state = OTG_A_SUSPEND;
				continue;
			}
			break;

		case OTG_A_SUSPEND:
			if(id | a_bus_drop | a_aidl_bdis_tmout)
			{
				TIMER_OFF();	/* a_aidl_bdis_tmr */
				a_aidl_bdis_tmout = FALSE;
				b_conn = FALSE;	/* a_wait_vfall�X�e�[�g�ł�b_conn/�J�ڏ��� */
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_OFF);
                usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_state = OTG_A_WAIT_VFALL;
				continue;
			}
			else if(!a_vbus_vld)
			{
				TIMER_OFF();	/* a_aidl_bdis_tmr */
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_DISCHARGE);
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_message = 0x10;
				usbctrl_otg_state = OTG_A_VBUS_ERR;
				continue;
			}
			else if(!b_conn && !a_set_b_hnp_en)
			{
				TIMER_OFF();	/* a_aidl_bdis_tmr */
				a_wait_bcon_tmout = FALSE;
                writel_reg(HcControl, ((readl_reg(HcControl) & ~OHCI_USB_SUSPEND) | OHCI_USB_OPER) );
				TIMER_ON(a_wait_bcon_tmr);
				usbctrl_otg_state = OTG_A_WAIT_BCON;
				continue;
			}
			else if(!b_conn && a_set_b_hnp_en)
			{
				TIMER_OFF();	/* a_aidl_bdis_tmr */
				usbctrl_otg_state = OTG_A_PERIPHERAL;
				usbctrl_mode_set(USB_PERIPHERAL);
				continue;
			}
			else if(a_bus_req | b_bus_resume)
			{
				TIMER_OFF();	/* a_aidl_bdis_tmr */
                writel_reg(HcControl, ((readl_reg(HcControl) & ~OHCI_USB_SUSPEND) | OHCI_USB_OPER) );
				usbctrl_otg_state = OTG_A_HOST;
				continue;
			}
			break;

		case OTG_A_PERIPHERAL:
			if(id | a_bus_drop)
			{
				usbctrl_mode_set(USB_IDLE);
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_OFF);
				usbctrl_otg_state = OTG_A_WAIT_VFALL;
				continue;
			}
			else if(!a_vbus_vld)
			{
				usbctrl_vbus_thress(VBUS_SESS);
				usbctrl_vbus_set(VBUS_DISCHARGE);
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_message = 0x10;
				usbctrl_otg_state = OTG_A_VBUS_ERR;
				continue;
			}
			else if(b_bus_suspend)
			{
				b_bus_suspend = FALSE;
				usbctrl_mode_set(USB_HOST);
                TIMER_ON(a_wait_bcon_tmr);
				usbctrl_otg_state = OTG_A_WAIT_BCON;
				continue;
			}
			break;

		case OTG_A_WAIT_VFALL:
			if(id || a_bus_req || (!b_conn && !a_sess_vld))
			{
				a_set_b_hnp_en = FALSE;
				usbctrl_otg_state = OTG_A_IDLE;
				continue;
			}
			break;

		case OTG_A_VBUS_ERR:
			if(id | a_bus_drop)
			{
				b_conn = FALSE;	/* a_wait_vfall�X�e�[�g�ł�b_conn/�J�ڏ��� */
				usbctrl_otg_state = OTG_A_WAIT_VFALL;
				continue;
			}
			else if(!a_sess_vld)
			{
				usbctrl_vbus_set(VBUS_OFF);
			}
			break;

	/* ----- B-device ----- */
		case OTG_B_IDLE:
			if(!id)
			{
				if(b_srp_done == TRUE) {
					TIMER_OFF();	/* b_srp_fail_tmr */
				}
				b_srp_fail_tmout = FALSE;
				b_bus_req = FALSE;
				usbctrl_otg_state = OTG_A_IDLE;
				continue;
			}
			else if(b_sess_vld)
			{
				if(b_srp_done == TRUE) {
					TIMER_OFF();	/* b_srp_fail_tmr */
				}
				b_srp_fail_tmout = FALSE;
				b_srp_done = FALSE;
				usbctrl_mode_set(USB_PERIPHERAL);
				usbctrl_otg_state = OTG_B_PERIPHERAL;
				continue;
			}
			else if(b_bus_req && b_sess_end && !b_srp_done)
			{
				usbctrl_resistance_set(PULLDOWN);
				usbctrl_se0_det_int(ENABLE);
				usbctrl_otg_state = OTG_B_SRP_PRE;
				continue;
			}
			else if(b_srp_fail_tmout)
			{
				TIMER_OFF();	/* b_srp_fail_tmr */
				b_srp_fail_tmout = FALSE;
				b_srp_done = FALSE;
				usbctrl_otg_message = 0x20;
				continue;
			}
			break;

		case OTG_B_SRP_PRE:
			if(!id || b_sess_vld)
			{
				usbctrl_se0_det_int(DISABLE);
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_state = OTG_B_IDLE;
				continue;
			}
			else if(b_se0_srp)
			{
				usbctrl_se0_det_int(DISABLE);
				usbctrl_vbus_thress(VBUS_NC);
				usbctrl_mode_set(USB_OTG_SRP);
				usbctrl_otg_state = OTG_B_SRP_INIT;
				continue;
			}
			break;
			
		case OTG_B_SRP_INIT:
			if(!id || b_srp_done)
			{
				b_se0_srp = FALSE;
				usbctrl_mode_set(USB_IDLE);
				b_srp_fail_tmout = FALSE;
				TIMER_ON(b_srp_fail_tmr);
				usbctrl_otg_state = OTG_B_IDLE;
				usbctrl_vbus_thress(VBUS_SESS);
				continue;
			}
			break;

		case OTG_B_PERIPHERAL:
			if(a_bus_suspend & b_bus_req & b_hnp_en)
			{
				a_bus_suspend = FALSE;
				b_ase0_brst_tmout = FALSE;
				usbctrl_mode_set(USB_HOST);
				TIMER_ON(b_ase0_brst_tmr);
				usbctrl_otg_state = OTG_B_WAIT_ACON;
				continue;
			}
			else if(!id || !b_sess_vld)
			{
				a_conn = FALSE;
				b_hnp_en = FALSE;
				a_hnp_support = FALSE;
				a_alt_hnp_support = FALSE;
				a_bus_suspend = FALSE;
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_state = OTG_B_IDLE;
				continue;
			}
			break;

		case OTG_B_WAIT_ACON:
			if(!id || !b_sess_vld)
			{
				TIMER_OFF();	/* b_ase0_brst_tmr */
				b_hnp_en = FALSE;
				a_hnp_support = FALSE;
				a_alt_hnp_support = FALSE;
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_state = OTG_B_IDLE;
				continue;
			}
			else if(a_bus_resume | b_ase0_brst_tmout)
			{
				TIMER_OFF();	/* b_ase0_brst_tmr */
				b_ase0_brst_tmout = FALSE;
				usbctrl_mode_set(USB_PERIPHERAL);
				usbctrl_otg_state = OTG_B_PERIPHERAL;
				continue;
			}
			else if(a_conn)
			{
				TIMER_OFF();	/* b_ase0_brst_tmr */
				usbctrl_otg_state = OTG_B_HOST;
				continue;
			}
			break;

		case OTG_B_HOST:
			if(!id || !b_sess_vld)
			{
				b_hnp_en = FALSE;
				a_hnp_support = FALSE;
				a_alt_hnp_support = FALSE;
				usbctrl_mode_set(USB_IDLE);
				usbctrl_otg_state = OTG_B_IDLE;
				continue;
			}
			else if(!b_bus_req || !a_conn)
			{
				usbctrl_mode_set(USB_PERIPHERAL);
				usbctrl_otg_state = OTG_B_PERIPHERAL;
				continue;
			}
			break;

		default:
			break;
		}

		break;
	}

}

/* End of File */
