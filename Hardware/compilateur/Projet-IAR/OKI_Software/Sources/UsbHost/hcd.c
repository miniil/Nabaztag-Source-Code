/*******************************************************************************
    hcd.c
    JOB60842�T���v���v���O����
    �z�X�g�R���g���[���h���C�o�v���O����

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
/* #define DEBUG */
/* #define DEBUG_LINK */
#define DEBUG_CC
/* #define DEBUG_RAMAC_ERR */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "usbh.h"
#include "hcd.h"
#include "usbctrl.h"
#include "hcdmem.h"

#include "otg.h"

/****************************************************************************/
/* �萔 */
#define RevisonNumber	0x00000010
#define TD_BUFFER_MAX	4096	/* �ʏ��4096 */

/* �O���[�o���ϐ� */
struct hcd_info hcd_info;


/*******************************************************************************
    Routine Name    �Fhcd_init
    Form            �Fint hcd_init(void);
    Parameters      �F
    Return value    �F���s����
    Description     �F�z�X�g�R���g���[���h���C�o�̏�����
*******************************************************************************/
int hcd_init(void)
{
	ulong rev;
	ulong fminterval;
	ulong mask;
    int otg_state;


	dbg_printf(" HCD: Controler Address = %08lX\n", (ulong)HostCtl_addr);

	/*�R���g���[���m�F*/
	rev = readl_reg(HcRevision);
	if(rev != RevisonNumber){
		con_printf("Bad Revision Register : %08lX", (ulong)rev);
		return -1;
	}

	/*����RAM�A�h���X�ݒ�*/
	writel_reg(RamAdr, IntRAMAddr);

	/*���L�������̈揉����*/
	hcd_malloc_init(IntRAMAddr, IntRAMSize, 16, COMRAM);	/* ����RAM */

	/*HCD����ϐ��̈揉����*/
	memset (&hcd_info, 0, sizeof(struct hcd_info));

	/*���L�������̈�m��*/
	hcd_info.hcca = (struct hcca *) hcd_malloc(sizeof(struct hcca), COMRAM);
	if (!hcd_info.hcca){
		return -1;
	}
	memset ((long *)hcd_info.hcca, 0, sizeof(struct hcca));
	writel_reg(HcHCCA, (ulong)hcd_info.hcca);

	/*�R���g���[�����W�X�^������*/
	writel_reg(HcControlHeadED, 0);
	writel_reg(HcBulkHeadED, 0);

	fminterval = 0x2edf;
	writel_reg(HcPeriodicStart,(fminterval * 9) / 10);
	fminterval |= ((((fminterval - MAXIMUM_OVERHEAD) * 6) / 7) << 16);
	writel_reg(HcFmInterval, fminterval);
	writel_reg(HcLSThreshold, 0x628);

	INIT_LIST_ENTRY(&hcd_info.ed_control);
	INIT_LIST_ENTRY(&hcd_info.ed_bulk);
	INIT_LIST_ENTRY(&hcd_info.ed_pause0);
	INIT_LIST_ENTRY(&hcd_info.ed_pause1);

	/*�R���g���[���̐���J�n*/
	hcd_info.hc_control = OHCI_CTRL_PLE | OHCI_USB_OPER;

	writel_reg(HcControl, hcd_info.hc_control);

	/*���[�g�n�u�̏����ݒ�*/
    /* A-Device��WAIT */
    otg_state = usbctrl_otg_get_state();
    if( (otg_state & 0x000000f0) == OTG_A ){
        mdelay((int)((readl_reg(HcRhDescriptorA) >> 23) & 0x000001fe));
    }

	/*���荞�݂̏�����*/
	mask = OHCI_INTR_MIE | OHCI_INTR_UE | OHCI_INTR_WDH | OHCI_INTR_RHSC | OHCI_INTR_SO;
	writel_reg(HcInterruptEnable, mask);
	writel_reg(HostCtl, 0x0);

	/*���[�g�n�u�C�l�[�u��*/
	writel_reg(HcRhStatus, RH_HS_LPSC);

	return 0;
}


/*******************************************************************************
    Routine Name    �Fhcd_rh_events
    Form            �Fint hcd_rh_events(void);
    Parameters      �F
    Return value    �F���s����
    Description     �F���[�g�n�u�C�x���g����
*******************************************************************************/
int hcd_rh_events(void)
{

	if(hcd_info.rh_status & HcdRH_DISCONNECT){
		hcd_info.rh_status &= ~HcdRH_DISCONNECT;

		dbg_printf(" HCD: disconnected the device.\n");
		usbh_disconnect((PDEVINFO *)&hcd_info.rh_device);
        hcd_info.rh_device = NULL;

		return HcdRH_DISCONNECT;
	}

	else if(hcd_info.rh_status & HcdRH_CONNECT){
        mdelay(40);
		hcd_info.rh_status &= ~HcdRH_CONNECT;

		dbg_printf(" HCD: connected a new device.\n");
		hcd_info.rh_device = usbh_connect((unsigned char)((hcd_info.rh_status & HcdRH_SPEED) ? 1 : 0));

		return HcdRH_CONNECT;
	}

	return 0;
}


#ifdef DEBUG_LINK
/*******************************************************************************
    Routine Name    �Fhcd_print_data
    Form            �Fvoid hcd_print_data(ulong start , ulong end);
    Parameters      �Fstart         �\���擪�A�h���X
                      end           �\���I���A�h���X
    Return value    �F
    Description     �FTD�Ƀ����N���ꂽ�f�[�^�̈�̕\��
*******************************************************************************/
void hcd_print_data(ulong start , ulong end)
{
	uchar *pt;
	int cnt;

	if (start){
		con_printf(" DATA start : %08lX\n", (ulong)start);
		pt = (uchar *)start;
		con_printf(" ");
	}
	else{
		con_printf(" DATA end : %08lX\n", (ulong)end);
		pt = (uchar *)(end-7);
		con_printf("  ...");
	}	

  	for(cnt=8 ; cnt>0; cnt--){
 		con_printf(" %02X", *pt++);
	}

	if(start && start+7 > end)
		con_printf(" ...");

	con_printf("\n");
}


/*******************************************************************************
    Routine Name    �Fhcd_print_td
    Form            �Fvoid hcd_print_td(PHCD_TD td);
    Parameters      �Ftd            TD�ւ̃|�C���^
    Return value    �F
    Description     �FTD�̕\��
*******************************************************************************/
void hcd_print_td(PHCD_TD td)
{
	con_printf(" HcTD : %08lX\n", (ulong)td);
	con_printf("  .Control = %08lX\n", (ulong)td->HcTD.Control );
	con_printf("  .CBP     = %08lX\n", (ulong)td->HcTD.CBP);
	con_printf("  .NextTD  = %08lX\n", (ulong)td->HcTD.NextTD);
	con_printf("  .BE      = %08lX\n", (ulong)td->HcTD.BE);
	con_printf("  .index   = %ld\n",   (ulong)td->index);

	if(td->HcTD.BE || td->HcTD.CBP)
		hcd_print_data((ulong)td->HcTD.CBP, (ulong)td->HcTD.BE);

	if(td->HcTD.NextTD)
		hcd_print_td((PHCD_TD)td->HcTD.NextTD);
}


/*******************************************************************************
    Routine Name    �Fhcd_print_ed
    Form            �Fvoid hcd_print_ed(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �FED�̕\��
*******************************************************************************/
void hcd_print_ed(PHCD_ED ed)
{
	if(!ed) return;

	con_printf(" --------------------- \n");
	con_printf(" HcED : %08lX\n", (ulong)ed);
	con_printf("  .Control = %08lX\n", (ulong)ed->HcED.Control );
	con_printf("  .TailP   = %08lX\n", (ulong)ed->HcED.TailP);
	con_printf("  .HeadP   = %08lX\n", (ulong)ed->HcED.HeadP);
	con_printf("  .NextED  = %08lX\n", (ulong)ed->HcED.NextED);

	if(ed->HcED.HeadP & 0xFFFFFFF0)
		hcd_print_td((PHCD_TD)(ed->HcED.HeadP & 0xFFFFFFF0));

	if(ed == (PHCD_ED)ed->HcED.NextED){
		con_printf(" HCD: The list of ED being linked is abnormal.\n");
		return;
	}

	if(ed->HcED.NextED)
		hcd_print_ed((PHCD_ED)ed->HcED.NextED);
}
#endif


#ifdef DEBUG_CC
/*******************************************************************************
    Routine Name    �Fhcd_cc_string
    Form            �Fstatic char *hcd_cc_string(int cc);
    Parameters      �Fcc            �R���f�B�V�����R�[�h
    Return value    �F
    Description     �F�R���f�B�V�����R�[�h�̃��b�Z�[�W�ϊ�
*******************************************************************************/
static char *hcd_cc_string(ulong cc)
{
	char *cc_s;

	switch(cc){
        case CC_NOERROR        : cc_s = "NOERROR";				break;
        case CC_CRC            : cc_s = "CRC";					break;
        case CC_BITSTUFFING    : cc_s = "BITSTUFFING";			break;
        case CC_TOGGLEMISMATCH : cc_s = "DATATOGGLEMISMATCH ";	break;
        case CC_STALL          : cc_s = "STALL"; 				break;
        case CC_NOTRESPONDING  : cc_s = "DEVICENOTRESPONDING";	break;
        case CC_PIDCHECKFAILURE: cc_s = "PIDCHECKFAILURE";		break;
        case CC_UNEXPECTEDPID  : cc_s = "UNEXPECTEDPID";		break;
        case CC_DATAOVERRUN    : cc_s = "DATAOVERRUN";			break;
        case CC_DATAUNDERRUN   : cc_s = "DATAUNDERRUN";			break;
        case CC_BUFFEROVERRUN  : cc_s = "BUFFEROVERRUN";		break;
        case CC_BUFFERUNDERRUN : cc_s = "BUFFERUNDERRUN ";		break;
        case CC_NOTACCESSED    : cc_s = "NOTACCESSED";			break;
        default                : cc_s = "UNKNOWN CODE";         break;
	}

	return cc_s;
}
#else
__inline char *hcd_cc_string(int cc){ return NULL; }
#endif


/*******************************************************************************
    Routine Name    �Fhcd_int_interval
    Form            �Fstatic int hcd_int_interval(int raw_interval);
    Parameters      �Fraw_interval      ���l������C���^�[�o������
    Return value    �F���l�����ꂽ�C���^�[�o������
    Description     �F�C���^�[�o�����Ԃ̐��l��
*******************************************************************************/
static int hcd_int_interval(int raw_interval)
{
	int int_interval;

	if(raw_interval < 2)		int_interval = 1;
	else if(raw_interval < 4)	int_interval = 2;
	else if(raw_interval < 8)	int_interval = 4;
	else if(raw_interval < 16)	int_interval = 8;
	else if(raw_interval < 32)	int_interval = 16;
	else						int_interval = 32;

	return int_interval;
}


/*******************************************************************************
    Routine Name    �Fhcd_int_table_entry
    Form            �Fstatic int hcd_int_table_entry(int int_interval);
    Parameters      �Fint_interval      �C���^�[�o������
    Return value    �F���l�����ꂽ�e�[�u���G���g���l
    Description     �F�C���^���v�g�]���e�[�u���G���g���̐��l�� 
*******************************************************************************/
static int hcd_int_table_entry(int int_interval)
{
	int entry;
	PHCD_ED saved_int_table[32];

    memset( saved_int_table, 0, sizeof(PHCD_ED)*32 );

	for(entry = 0; entry< 32; entry++){
		if(!hcd_info.hcca->int_table[entry])
			break;
		saved_int_table[entry] = (PHCD_ED)hcd_info.hcca->int_table[entry];
	}

	while(entry>=32){
		for(entry = 0; entry< 32; entry++){
			if(!saved_int_table[entry]->HcED.NextED)
				break;
			else if(saved_int_table[entry]->type == USB_ISO)
				break;
			saved_int_table[entry] = (PHCD_ED)saved_int_table[entry]->HcED.NextED;
		}
	} 

	entry = entry % int_interval;
	
	return entry;
}


/*******************************************************************************
    Routine Name    �Fhcd_link_int_table
    Form            �Fstatic void hcd_link_int_table(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �F�C���^���v�g�]���G���h�|�C���g�̃e�[�u�������N
*******************************************************************************/
static void hcd_link_int_table(PHCD_ED ed)
{
	int loop, interval, entry;
	PHCD_ED ed_next, ed_pre;

    memset( &ed_next, 0, sizeof(PHCD_ED) );
    memset( &ed_pre, 0, sizeof(PHCD_ED) );

	interval = hcd_int_interval((int)ed->interval);

	entry = hcd_int_table_entry(interval);

	for(loop = entry ; loop < 32 ; loop += interval){
		ed_next = (PHCD_ED)hcd_info.hcca->int_table[loop];
		if(!ed_next){
			hcd_info.hcca->int_table[loop] = (ulong)ed;
		}
		else if(ed_next->type != USB_INT){
			hcd_info.hcca->int_table[loop] = (ulong)ed;
			ed->HcED.NextED = (ulong)ed_next;
		}
		else{
			while(!ed_next){
				ed_pre = ed_next;
				ed_next = (PHCD_ED)ed_next->HcED.NextED;
 				if(ed_next->type != USB_INT) break;
			}

			ed->HcED.NextED = (ulong)ed_next;
			ed_pre->HcED.NextED = (ulong)ed;	
		}
	}

}


/*******************************************************************************
    Routine Name    �Fhcd_unlink_int_table
    Form            �Fstatic void hcd_unlink_int_table(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �F�C���^���v�g�]���G���h�|�C���g�̃e�[�u���폜
*******************************************************************************/
static void hcd_unlink_int_table(PHCD_ED ed)
{
	int loop, interval;
	PHCD_ED ed_next, ed_pre;

	interval = hcd_int_interval((int)ed->interval);

	loop = 0;
	while(loop < 32){
		if(!hcd_info.hcca->int_table[loop]){
			loop++;
			continue;
		}

		ed_pre = (PHCD_ED)hcd_info.hcca->int_table[loop];
		if(ed_pre == ed){
			hcd_info.hcca->int_table[loop] = ed->HcED.NextED;
			loop += interval;
		}
		else{
			ed_next = (PHCD_ED)ed_pre->HcED.NextED;
			while(1){
				if(!ed_next){
					loop++;
					break;
				}
				else if(ed_next == ed){
					ed_pre->HcED.NextED = ed->HcED.NextED;
					loop += interval;
					break;
				}

				ed_pre = ed_next;
				ed_next = (PHCD_ED)ed_pre->HcED.NextED;
			}
		}
	}
}


/*******************************************************************************
    Routine Name    �Fhcd_delete_td
    Form            �Fstatic void hcd_delete_td(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �FTD�̍폜
*******************************************************************************/
static void hcd_delete_td(PHCD_ED ed)
{
	PURB urb;
	PHCD_TD td_next, td_prev;
	ulong HeadP = ed->HcED.HeadP;
	ulong TailP = ed->HcED.TailP;

	td_next = (PHCD_TD)(HeadP & 0xFFFFFFF0);
	while((ulong)td_next != TailP){
	 	urb = td_next->urb;
		if(urb){
			list_del(&td_next->list);
			if(urb->status>=0)
				urb->status = URB_ABORT;
		}
		td_prev	= td_next;
		td_next = (PHCD_TD)td_prev->HcTD.NextTD;
		hcd_free(td_prev);
	}
	
	ed->HcED.HeadP = (HeadP & 0xF) | TailP;
}


/*******************************************************************************
    Routine Name    �Fhcd_add_td
    Form            �Fstatic int hcd_add_td(PHCD_ED ed, ulong control,
                                 void *buffer, int length, PURB urb, int index)
    Parameters      �Fed            ED�ւ̃|�C���^
                      control       �]���f�B�X�N���v�^����R�[�h
                      buffer        �]���f�[�^�̃|�C���^
                      length        �]���T�C�Y
                      urb           URB�ւ̃|�C���^
                      index         �]���f�B�X�N���v�^��INDEX
    Return value    �F
    Description     �FTD�̒ǉ�
*******************************************************************************/
static int hcd_add_td(PHCD_ED ed, ulong control, void *buffer, int length,
	 PURB urb, int index)
{
	PHCD_TD td_tail;
	PHCD_TD td_next;

	td_tail = (PHCD_TD)ed->HcED.TailP;
	if(!td_tail){
		return -1;
	}
	
	td_next = (PHCD_TD)(td_tail->HcTD.NextTD);
	while(td_next){
		td_tail = td_next;
		td_next = (PHCD_TD)(td_tail ->HcTD.NextTD);
	}

	td_next = (PHCD_TD)hcd_malloc(sizeof(HCD_TD), COMRAM);	/* new TD */
	if (!td_next){
		return -1;
	}
	memset((long *)td_next, 0, sizeof(HCD_TD));

	td_tail->HcTD.Control = control;
	td_tail->HcTD.CBP = (!buffer || !length) ? 0: buffer;
	td_tail->HcTD.NextTD = (ulong)td_next;
	td_tail->HcTD.BE = (!buffer || !length ) ? 0: (char *)buffer + length - 1;
	td_tail->urb = urb;
	td_tail->index = index;

	ed->HcED.TailP = (ulong)td_next;

	list_add(&td_tail->list, &urb->td_list);

	return 0;
}


/*******************************************************************************
    Routine Name    �Fhcd_unlink_ed
    Form            �Fstatic void hcd_unlink_ed(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �FED�������N���X�g�����菜��
*******************************************************************************/
static void hcd_unlink_ed(PHCD_ED ed)
{
	PHCD_ED ed_pre;

	if(ed->type == USB_CTRL){

		if(ed->ed_list.Blink == &hcd_info.ed_control){
			/* �Y��ED�������N���X�g�̐擪�ɂ���ꍇ */
			writel_reg(HcControlHeadED, ed->HcED.NextED);
		}
		else{
			/* �Y��ED�������N���X�g�̐擪�ɂȂ��ꍇ */
			ed_pre = list_struct_entry(ed->ed_list.Blink, HCD_ED, ed_list);
			ed_pre->HcED.NextED = ed->HcED.NextED;
		}

		list_del(&ed->ed_list);

		if(list_empty(&hcd_info.ed_bulk)){
			/* �����N���X�g����̏ꍇ�A�f�B�Z�[�u���ɂ��� */
			hcd_info.hc_control &= ~OHCI_CTRL_CLE;
			writel_reg(HcControl, hcd_info.hc_control);
		}

#ifdef DEBUG_LINK
	con_printf(" hcd_unlink_ed (control): done.\n");
	hcd_print_ed((PHCD_ED)readl_reg(HcControlHeadED));
#endif

	}
	else if(ed->type == USB_BULK){

		if(ed->ed_list.Blink == &hcd_info.ed_bulk){
			/* �Y��ED�������N���X�g�̐擪�ɂ���ꍇ */
			writel_reg(HcBulkHeadED, ed->HcED.NextED);
		}
		else{
			/* �Y��ED�������N���X�g�̐擪�ɂȂ��ꍇ */
			ed_pre = list_struct_entry(ed->ed_list.Blink, HCD_ED, ed_list);
			ed_pre->HcED.NextED = ed->HcED.NextED;
		}

		list_del(&ed->ed_list);

		if(list_empty(&hcd_info.ed_bulk)){
			/* �����N���X�g����̏ꍇ�A�f�B�Z�[�u���ɂ��� */
			hcd_info.hc_control &= ~OHCI_CTRL_BLE;
			writel_reg(HcControl, hcd_info.hc_control);
		}

#ifdef DEBUG_LINK
	con_printf(" hcd_unlink_ed (bulk): done.\n");
	hcd_print_ed((PHCD_ED)readl_reg(HcBulkHeadED));
#endif

	}
	else if(ed->type == USB_INT){
		hcd_unlink_int_table(ed);
	}

	ed->HcED.NextED = NULL;
    ed->flag = ED_UNLINK;
}


/*******************************************************************************
    Routine Name    �Fhcd_pause_ed
    Form            �Fstatic void hcd_pause_ed(PHCD_ED ed);
    Parameters      �Fed            ED�ւ̃|�C���^
    Return value    �F
    Description     �FED�̒�~
*******************************************************************************/
static void hcd_pause_ed(PHCD_ED ed)
{
	if(ed->HcED.Control & HcED_SKIP){

		if((ed->HcED.HeadP & 0xFFFFFFF0) != ed->HcED.TailP)
			hcd_delete_td(ed);

		hcd_unlink_ed(ed);
	}

	else if((ed->HcED.HeadP & 0xFFFFFFF0) == ed->HcED.TailP){

		ed->HcED.Control |= HcED_SKIP;

		hcd_unlink_ed(ed);
	}

	else{
        ed->flag = ED_PAUSE;

		ed->HcED.Control |= HcED_SKIP;

		list_add(&ed->ed_list, &hcd_info.ed_pause0);

		writel_reg(HcInterruptEnable, OHCI_INTR_SF);
	}
}


/*******************************************************************************
    Routine Name    �Fhcd_delete_ed
    Form            �Fvoid hcd_delete_ed(PHCD_ED ed);
    Parameters      �Fed            �폜����ED�ւ̃|�C���^
    Return value    �F
    Description     �FED�̍폜
*******************************************************************************/
void hcd_delete_ed(PHCD_ED ed)
{
	int timeout = 0;

	dbg_printf(" hcd_delete_ed:\n");

	/* ED�̒�~ */
	if(ed->flag == ED_LINK)
		hcd_pause_ed(ed);

	/* ED�̒�~�҂� */
	while(ed->flag == ED_LINK || ed->flag == ED_PAUSE){
		mdelay(1);
		if(timeout++ > 100){
			con_printf(" HCD: hcd_delete_ed timeout!!\n");
			return;
		}
	}

	hcd_free((long *)ed->HcED.TailP);
	hcd_free(ed);
}


/*******************************************************************************
    Routine Name    �Fhcd_update_ed
    Form            �Fint hcd_update_ed(PHCD_ED ed, uchar dev_addr, ushort maxpacket);
    Parameters      �Fed            �X�V����ED�ւ̃|�C���^
    Return value    �F
    Description     �FED�̍X�V
*******************************************************************************/
int hcd_update_ed(PHCD_ED ed, uchar dev_addr, ushort maxpacket)
{
	ulong control;

	dbg_printf(" hcd_update_ed:\n");

	if(ed->HcED.Control & HcED_SKIP){
		control = ed->HcED.Control & (HcED_FA | HcED_EN | HcED_SPEED | HcED_SKIP);
		ed->HcED.Control = control | ((ulong)maxpacket << 16) | dev_addr;
		return 0;
	}

	return -1;
}


/*******************************************************************************
    Routine Name    �Fhcd_create_ed
    Form            �FPHCD_ED hcd_create_ed(uchar speed, uchar dev_addr,
                              uchar type, uchar ep_num, ushort maxpacket,
                              uchar interval);
    Parameters      �Fspeed         �f�o�C�X�X�s�[�h
                      dev_addr      �f�o�C�X�A�h���X
                      type          �]���^�C�v
                      ep_num        �G���h�|�C���g�ԍ�
                      maxpacket     MAX�p�P�b�g�T�C�Y
                      interval      �]���Ԋu
    Return value    �FED�ւ̃|�C���^
    Description     �FED�̍쐬
*******************************************************************************/
PHCD_ED hcd_create_ed(uchar speed, uchar dev_addr, uchar type, uchar ep_num, 
	ushort maxpacket, uchar interval)
{
	PHCD_ED ed;
	PHCD_TD td;
	ulong dir;

	dbg_printf(" hcd_create_ed:\n");

	ed = (PHCD_ED)hcd_malloc(sizeof(HCD_ED), COMRAM);
	if (!ed){
		return NULL;
	}

	td = (PHCD_TD)hcd_malloc(sizeof(HCD_TD), COMRAM);	/* dumy TD */
	if (!td){
		hcd_free(ed);
		return NULL;
	}
	memset((long *)td, 0, sizeof(HCD_TD));
	
	dir = (type == USB_CTRL) ? (ulong)0:
		((ep_num & USB_DIR_IN) ? (ulong)HcED_DIR_IN : (ulong)HcED_DIR_OUT);
	ed->HcED.Control = ((ulong)maxpacket << 16) | ((ulong)speed << 13 ) | ((ulong)ep_num << 7) 
					 | dir | ((ulong)dev_addr & 0x7Fl) | HcED_SKIP;
	ed->HcED.TailP = (ulong)td;
	ed->HcED.HeadP = (ulong)td;
	ed->HcED.NextED = NULL;
    ed->type = type;
    ed->interval = interval;
    ed->flag = ED_IDLE;

	return ed;
}


/*******************************************************************************
    Routine Name    �Fhcd_transfer_wait
    Form            �Fstatic void hcd_transfer_wait(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�]���̏I���҂�
*******************************************************************************/
static void hcd_transfer_wait(PURB urb)
{
	int timeout = 0;

	dbg_printf(" hcd_transfer_wait:\n");

	while(urb->status == URB_PENDING){
		mdelay(1);
		if(timeout++ > urb->timeout){
			PHCD_ED ed = (PHCD_ED)urb->ed;
			con_printf(" HCD: hcd_transfer_wait timeout!!\n");
			hcd_pause_ed(ed);
			urb->status = URB_TIMEOUT;
			return;
		}
	}

	/* URB�Ƀ����N���ꂽTD���S�ď������ꂽ���`�F�b�N */
	if(!list_empty(&urb->td_list))
		urb->status = URB_SYSERR;
#ifdef DEBUG_RAMAC_ERR
    	hcd_info.hc_control |= OHCI_CTRL_PLE;
	    writel_reg(HcControl, hcd_info.hc_control);
#endif
	dbg_printf(" hcd_transfer_wait: done.\n");

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_control_transfer_start
    Form            �Fstatic void hcd_control_transfer_start(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�R���g���[���]���̊J�n
*******************************************************************************/
static void hcd_control_transfer_start(PURB urb)
{
	ulong control;
	PHCD_ED ed = (PHCD_ED)urb->ed;
	PHCD_ED ed_list_tail;
	int ret;

	dbg_printf(" hcd_control_transfer_start:\n");

	/* URB�̃X�e�[�^�X�������� */
	urb->result = 0;
	urb->status = URB_PENDING;
	INIT_LIST_ENTRY(&urb->td_list);

	writel_reg(HostCtl, B_OHCIIRQ_MASK);		/* �R���g���[�����荞�݋֎~ */

	/* TD�̍쐬 �Z�b�g�A�b�v�X�e�[�W�p */
	control = HcTD_CC | HcTD_DP_SETUP | HcTD_T_DATA0 | HcTD_DI;
	ret = hcd_add_td(ed, control, urb->setup, 8, urb, TD_SETUP);
	if(ret<0){
		urb->status = URB_ADDTDERR;
		return;
	}

	/* TD�̍쐬 �f�[�^�X�e�[�W�p */
	if (urb->length> 0) {
		if(urb->setup->bmRequestType & USB_DIR_IN)
			control = HcTD_CC | HcTD_R | HcTD_DP_IN  | HcTD_T_DATA1 | HcTD_DI;
		else
			control = HcTD_CC | HcTD_R | HcTD_DP_OUT | HcTD_T_DATA1 | HcTD_DI;
		ret = hcd_add_td(ed, control, urb->buffer, (int)urb->length, urb, TD_DATA);
		if(ret<0){
			urb->status = URB_ADDTDERR;
			return;
		}
	}

	/* TD�̍쐬 �X�e�[�^�X�X�e�[�W�p */
	if(urb->setup->bmRequestType & USB_DIR_IN)
		control = HcTD_CC | HcTD_DP_OUT | HcTD_T_DATA1;
	else
		control = HcTD_CC | HcTD_DP_IN  | HcTD_T_DATA1;
	ret = hcd_add_td(ed, control, NULL, 0, urb, TD_STATUS);
	if(ret<0){
		urb->status = URB_ADDTDERR;
		return;
	}

	/* �R���g���[���]��ED���X�g�փ����N */
	if(ed->flag == ED_IDLE || ed->flag == ED_UNLINK){
		if(list_empty(&hcd_info.ed_control)){
			writel_reg(HcControlHeadED, (ulong)ed);
		}
		else{
			ed_list_tail = (PHCD_ED)readl_reg(HcControlHeadED);
			while(ed_list_tail->HcED.NextED){
				ed_list_tail = (PHCD_ED)ed_list_tail->HcED.NextED;
			}
			ed_list_tail->HcED.NextED = (ulong)ed;
		}
		ed->HcED.NextED = NULL;
        ed->flag = ED_LINK;

		/* ���X�g�̃Z�[�u */
		list_add(&ed->ed_list, &hcd_info.ed_control);

	}

#ifdef DEBUG_LINK
	con_printf(" hcd_control_transfer_start(check the link of ed): \n");
	hcd_print_ed((PHCD_ED)readl_reg(HcControlHeadED));
#endif

	/* Halt�r�b�g�̃N���A */
	if(ed->HcED.HeadP & HcED_HeadP_HALT){
		ed->HcED.HeadP &= (ulong)(~HcED_HeadP_HALT);
	}

	/* ED�̃X�L�b�v��ԉ��� */
	if(ed->HcED.Control & HcED_SKIP){
		ed->HcED.Control &= (ulong)(~HcED_SKIP);
	}

	/* �R���g���[���]���̋��� */
	if( (hcd_info.hc_control & OHCI_CTRL_CLE) == 0 ){
		hcd_info.hc_control |= OHCI_CTRL_CLE;
		writel_reg(HcControl, hcd_info.hc_control);
	}

	writel_reg(HostCtl, 0);	/* �R���g���[�����荞�݃C�l�[�u�� */

	/* �R���g���[���]���̊J�n */
	writel_reg(HcCommandStatus, OHCI_CLF);

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_control_transfer
    Form            �Fstatic void hcd_control_transfer(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�R���g���[���]���̑O�㏈��
*******************************************************************************/
static void hcd_control_transfer(PURB urb)
{
	struct usb_setup *setup, *setup_saved;
	void *buffer, *buffer_saved;

	/* �Z�b�g�A�b�v�f�[�^������RAM��ɂȂ��ꍇ */
	if(hcd_malloc_check(urb->setup)!=INTRAM){
		setup = (struct usb_setup *)hcd_malloc(8, COMRAM);
		if(!setup){
			urb->status = URB_NOMEM;
			return;
		}
		memcpy((void *)setup, (void *)(urb->setup), 8);
		setup_saved = urb->setup;
		urb->setup = setup;
	}
	else{ 
		setup = NULL;
        setup_saved = NULL;
	}

	/* �f�[�^�o�b�t�@������RAM��ɂȂ��ꍇ */
	if(urb->setup->wLength > 0 && (hcd_malloc_check(urb->buffer)!=INTRAM)){
		buffer = hcd_malloc(urb->length, COMRAM);
		if (!buffer){
			urb->status = URB_NOMEM;
			return;
		}
		buffer_saved = urb->buffer;
		if( (urb->setup->bmRequestType & USB_DIR_IN) == 0 )
			memcpy((long *)buffer, (long *)buffer_saved, urb->length);
		urb->buffer = buffer;
	}
	else{
		buffer = NULL;
        buffer_saved = NULL;
	}

	hcd_control_transfer_start(urb);

	if(urb->timeout || setup || buffer)
		hcd_transfer_wait(urb);

	if(setup){
		urb->setup = setup_saved;
		hcd_free(setup);
	}

	if(buffer){
		urb->buffer = buffer_saved;
		if(urb->setup->bmRequestType & USB_DIR_IN)
			memcpy((long *)buffer_saved, (long *)buffer, urb->length);
		hcd_free(buffer);
	}

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_bulk_transfer_start
    Form            �Fstatic void hcd_bulk_transfer_start(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�o���N�]���̊J�n
*******************************************************************************/
static void hcd_bulk_transfer_start(PURB urb)
{
	PHCD_ED ed = (PHCD_ED)urb->ed;
	PHCD_ED ed_list_tail;
	char *buffer = (char *)urb->buffer;
	ulong length = urb->length;
	uchar cnt = 0;
	int ret;

	dbg_printf(" hcd_bulk_transfer_start:\n");

	/* URB�̃X�e�[�^�X�������� */
	urb->result = 0;
	urb->status = URB_PENDING;
	INIT_LIST_ENTRY(&urb->td_list);

	writel_reg(HostCtl, B_OHCIIRQ_MASK);		/* �R���g���[�����荞�݋֎~ */

	/* TD�̍쐬 */
	while(length > TD_BUFFER_MAX) {
		ret = hcd_add_td(ed, HcTD_CC | HcTD_DI, buffer, TD_BUFFER_MAX, urb, cnt);
		if(ret<0){
			urb->status = URB_ADDTDERR;
			return;
		}
		buffer += TD_BUFFER_MAX;
		length -= TD_BUFFER_MAX;
		cnt++;
	}

	ret = hcd_add_td(ed, HcTD_CC, buffer, (int)length, urb, cnt);
	if(ret<0){
		urb->status = URB_ADDTDERR;
		return;
	}

	/* �o���N�]��ED���X�g�փ����N */
	if(ed->flag == ED_IDLE || ed->flag == ED_UNLINK){
		if(list_empty(&hcd_info.ed_bulk)){
			writel_reg(HcBulkHeadED, (ulong)ed);
		}
		else{
			ed_list_tail = (PHCD_ED)readl_reg(HcBulkHeadED);
			while(ed_list_tail->HcED.NextED){
				ed_list_tail = (PHCD_ED)ed_list_tail->HcED.NextED;
			}
			ed_list_tail->HcED.NextED = (ulong)ed;
		}
		ed->HcED.NextED = NULL;
        ed->flag = ED_LINK;

		/* ���X�g�̃Z�[�u */
		list_add(&ed->ed_list, &hcd_info.ed_bulk);
	}

#ifdef DEBUG_LINK
	con_printf(" hcd_bulk_transfer_start(check the link of ed): \n");
	hcd_print_ed((PHCD_ED)readl_reg(HcBulkHeadED));
#endif

	/* Halt�r�b�g�̃N���A */
	if(ed->HcED.HeadP & HcED_HeadP_HALT){
		ed->HcED.HeadP &= (ulong)(~HcED_HeadP_HALT);
	}
	
	/* ED�̃X�L�b�v��ԉ��� */
	if(ed->HcED.Control & HcED_SKIP){
		ed->HcED.Control &= (ulong)(~HcED_SKIP);
	}

	/* �o���N�]���̋��� */
	if( (hcd_info.hc_control & OHCI_CTRL_BLE) == 0 ){
		hcd_info.hc_control |= OHCI_CTRL_BLE;
		writel_reg(HcControl, hcd_info.hc_control);
	}

	writel_reg(HostCtl, 0);	/* �R���g���[�����荞�݃C�l�[�u�� */

	/* �o���N�]���̊J�n */
	writel_reg(HcCommandStatus, OHCI_BLF);

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_bulk_transfer_loop
    Form            �Fstatic void hcd_bulk_transfer_loop(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�o���N�]���������[�v
*******************************************************************************/
#define BULK_BUF_MAX 1024
static void hcd_bulk_transfer_loop(PURB urb)
{
	URB urb_new;
	char *buffer, *buffer_new;
	ulong length;

	memcpy(&urb_new, urb, sizeof(URB));

	length = (ulong)((ulong)hcd_malloc_rest(COMRAM)-256);
	length = (ulong)(min(BULK_BUF_MAX, (length - length % 64)));
	length = (ulong)(min(urb->length, length));

	buffer_new = (char *)hcd_malloc(length, COMRAM);
	if(!buffer_new){
		urb->status = URB_NOMEM;
		return;
	}

	urb_new.buffer = buffer_new;
	buffer = (char *)urb->buffer;
	urb->result = 0;

	while(urb->result < urb->length){

		urb_new.length = (urb->length - urb->result > length) ? length: urb->length - urb->result;

		if((((PHCD_ED)urb->ed)->HcED.Control & HcED_DIR) == HcED_DIR_OUT)
			memcpy((void *)urb_new.buffer, (void *)buffer, urb_new.length);

		hcd_bulk_transfer_start(&urb_new);

		hcd_transfer_wait(&urb_new);

		if((((PHCD_ED)urb->ed)->HcED.Control & HcED_DIR) == HcED_DIR_IN)
			memcpy((void *)buffer, (void *)urb_new.buffer, urb_new.result);

		if(urb_new.status < 0) break;
		urb->result += urb_new.result;
		buffer += urb_new.result;
	}

	hcd_free(buffer_new);

	if(urb_new.status < 0){
		urb->status = urb_new.status;
		if(urb_new.status == URB_XFERERR){
			urb->result = urb_new.result;
		}
	}
	else{
		urb->status = (int)urb->result;
	}
	
	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_bulk_transfer
    Form            �Fvoid hcd_bulk_transfer(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�o���N�]���̊J�n �O����
*******************************************************************************/
void hcd_bulk_transfer(PURB urb)
{
	if(hcd_malloc_check(urb->buffer)!=INTRAM && !urb->dma_enable){
		/* �f�[�^�o�b�t�@������RAM��ɂȂ��ADMA���T�|�[�g���Ȃ��ꍇ */
		hcd_bulk_transfer_loop(urb);
	}
	else{
		/* �f�[�^�o�b�t�@������RAM��ɂ���ꍇ�A�܂���DMA���T�|�[�g����ꍇ */
		hcd_bulk_transfer_start(urb);
		if(urb->timeout)
			hcd_transfer_wait(urb);
	}

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_interrupt_transfer
    Form            �Fstatic void hcd_interrupt_transfer(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F
    Description     �F�C���^���v�g�]���̊J�n
*******************************************************************************/
static void hcd_interrupt_transfer(PURB urb)
{
	PHCD_ED ed = (PHCD_ED)urb->ed;
	uchar cnt = 0;
	int ret;

	dbg_printf(" hcd_interrupt_transfer:\n");

	/* URB�̃X�e�[�^�X�������� */
	urb->result = 0;
	urb->status = URB_PENDING;
	INIT_LIST_ENTRY(&urb->td_list);

	/* TD�̍쐬 */
	ret = hcd_add_td(ed, HcTD_CC, urb->buffer, (int)urb->length, urb, cnt);
	if(ret<0){
		urb->status = URB_ADDTDERR;
		return;
	}

	/* �C���^���v�g�e�[�u���փ����N */
	if(ed->HcED.Control & HcED_SKIP){
        ed->flag = ED_LINK;
		hcd_link_int_table(ed);
		ed->HcED.Control &= (ulong)(~HcED_SKIP);
	}

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_transfer_cancel
    Form            �Fint hcd_transfer_cancel(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�]���v���̃L�����Z��
*******************************************************************************/
int hcd_transfer_cancel(PURB urb)
{
	dbg_printf(" hcd_transfer_cancel:\n");

	/* �R���g���[���̏�Ԋm�F */
	if (hcd_info.disabled) {
		urb->status = URB_ABORT;
		return urb->status;
	}

	if(((PHCD_ED)urb->ed)->flag == ED_LINK){
		hcd_pause_ed((PHCD_ED)urb->ed);
	}

	return urb->status;
}


/*******************************************************************************
    Routine Name    �Fhcd_transfer_request
    Form            �Fint hcd_transfer_request(PURB urb);
    Parameters      �Furb           URB�ւ̃|�C���^
    Return value    �F���s����
    Description     �F�]���v��
*******************************************************************************/
int hcd_transfer_request(PURB urb)
{
	dbg_printf(" hcd_transfer_request:\n");

	/* �R���g���[���̏�Ԋm�F */
	if (hcd_info.disabled) {
		urb->status = URB_ABORT;
		return urb->status;
	}

	/* ED�̃^�C�v�ʂɏ������[�`���̌Ăяo�� */
	switch(((PHCD_ED)urb->ed)->type){
		case USB_CTRL:
#ifdef DEBUG_RAMAC_ERR
    	hcd_info.hc_control &= ~OHCI_CTRL_PLE;
	    writel_reg(HcControl, hcd_info.hc_control);
#endif
		hcd_control_transfer(urb);
    	break;

		case USB_BULK:
		hcd_bulk_transfer(urb);
		break;
		
		case USB_INT:
		hcd_interrupt_transfer(urb);
		break;

		default:
		urb->status = URB_ABORT;
	}

	return urb->status;
}


/*******************************************************************************
    Routine Name    �Fhcd_get_done_list
    Form            �Fstatic PHCD_TD hcd_get_done_list(void);
    Parameters      �F
    Return value    �F�]���I��TD���X�g�擪�A�h���X
    Description     �F�]���I��TD���X�g�̎擾
*******************************************************************************/
static PHCD_TD hcd_get_done_list(void)
{
	PHCD_TD td_done, td_next, td_temp;

	td_done = NULL;
	td_next = (PHCD_TD)((hcd_info.hcca->donehead) & 0xfffffff0);
	hcd_info.hcca->donehead = 0;

	while (td_next) {
		dbg_printf(" HCD: Done TD = %08lX\n", (ulong)td_next);

		/* td_next �Ɍ�����l��ǂݍ��ނƖ������[�v�Ɋׂ�̂�h�� */
		if( hcd_malloc_check((long *)td_next) != COMRAM){
			con_printf(" HCD: DoneHead is bad address!!\n");
			break;
		}

		td_temp = td_done;
		td_done = td_next;
		td_next = (PHCD_TD)(td_next->HcTD.NextTD & 0xFFFFFFF0);
		td_done->HcTD.NextTD = (ulong)td_temp;
	}

	return td_done;
}


/*******************************************************************************
    Routine Name    �Fhcd_transfer_count
    Form            �Fstatic ushort hcd_transfer_count(PHCD_TD td, void *buffer);
    Parameters      �Ftd            TD�ւ̃|�C���^
                      buffer        �f�[�^�o�b�t�@�ւ̃|�C���^
    Return value    �F�]���o�C�g��
    Description     �F�]�������o�C�g���̌v�Z
*******************************************************************************/
static ulong hcd_transfer_count(PHCD_TD td, void *buffer)
{
	ulong result;

	if (td->HcTD.CBP == 0 && td->HcTD.BE != 0){
		result = (ulong)td->HcTD.BE - (ulong)buffer + 1;
	}
	else{
		result = (ulong)td->HcTD.CBP - (ulong)buffer;
	}

	return result;
}


/*******************************************************************************
    Routine Name    �Fhcd_control_transfer_done
    Form            �Fstatic PHCD_TD hcd_control_transfer_done(PHCD_TD td);
    Parameters      �Ftd            TD�ւ̃|�C���^
    Return value    �F��TD�ւ̃|�C���^
    Description     �F�R���g���[���]���̏I������
*******************************************************************************/
static PHCD_TD hcd_control_transfer_done(PHCD_TD td)
{
	PURB urb = td->urb;
	PHCD_ED ed = (PHCD_ED)urb->ed;
	PHCD_TD td_next;
	ulong cc;

	if(td->index == TD_DATA){
		urb->result = hcd_transfer_count(td, urb->buffer);
	}
	else if(td->index == TD_STATUS){
		urb->status = (int)urb->result;
		hcd_pause_ed(ed);
	}

	cc = (td->HcTD.Control >> 28);
	if(cc){
		con_printf(" HCD: USB-error/status: %02X(%s): %08lX\n", cc, hcd_cc_string(cc), (ulong)td);
		urb->result = cc;
		urb->status = URB_XFERERR;
		if( ((ed->HcED.HeadP & HcED_HeadP_HALT) != 0) && ((ed->HcED.HeadP & 0xFFFFFFF0) != 0) ){
			hcd_delete_td((PHCD_ED)ed);
			hcd_pause_ed(ed);
		}
	}

	td_next = (PHCD_TD)td->HcTD.NextTD;
	list_del(&td->list);
	hcd_free(td);

	return td_next;
}


/*******************************************************************************
    Routine Name    �Fhcd_bulk_transfer_done
    Form            �Fstatic PHCD_TD hcd_bulk_transfer_done(PHCD_TD td);
    Parameters      �Ftd            TD�ւ̃|�C���^
    Return value    �F��TD�ւ̃|�C���^
    Description     �F�o���N�]���̏I������
*******************************************************************************/
static PHCD_TD hcd_bulk_transfer_done(PHCD_TD td)
{
	PURB urb = td->urb;
	PHCD_ED ed = (PHCD_ED)urb->ed;
	PHCD_TD td_next;
	ulong cc;

	urb->result = hcd_transfer_count(td, urb->buffer);

	cc = (td->HcTD.Control >> 28);
	if(cc){
		con_printf(" HCD: USB-error/status: %02X(%s): %08lX\n", cc, hcd_cc_string(cc), (ulong)td);
		urb->result = cc;
		urb->status = URB_XFERERR;
		if( ((ed->HcED.HeadP & HcED_HeadP_HALT) != 0) && ((ed->HcED.HeadP & 0xFFFFFFF0) != 0) ){
			hcd_delete_td((PHCD_ED)ed);
			hcd_pause_ed(ed);
		}
	}

	if(urb->result >= urb->length){
		urb->status = (int)urb->result;

	  #ifdef BULK_UNLINK
		hcd_pause_ed(ed);
	  #endif
	}

	td_next = (PHCD_TD)td->HcTD.NextTD;
	list_del(&td->list);
	hcd_free(td);

	return td_next;
}


/*******************************************************************************
    Routine Name    �Fhcd_interrupt_transfer_done
    Form            �Fstatic PHCD_TD hcd_interrupt_transfer_done(PHCD_TD td);
    Parameters      �Ftd            TD�ւ̃|�C���^
    Return value    �F��TD�ւ̃|�C���^
    Description     �F�C���^���v�g�]���̏I������
*******************************************************************************/
static PHCD_TD hcd_interrupt_transfer_done(PHCD_TD td)
{
	PURB urb = td->urb;
	PHCD_ED ed = (PHCD_ED)urb->ed;
	PHCD_TD td_next;
	ulong cc;

	urb->result = hcd_transfer_count(td, urb->buffer);

	cc = ((td->HcTD.Control >> 28) & 0xf);
	if(cc == CC_DATAUNDERRUN){
		cc = CC_NOERROR;
		ed->HcED.HeadP &= (ulong)(~HcED_HeadP_HALT);
	}
	else if(cc){
		con_printf(" HCD: USB-error/status: %02X(%s): %08lX\n", cc, hcd_cc_string(cc), (ulong)td);
		urb->result = cc;
		urb->status = URB_XFERERR;
		if( ((ed->HcED.HeadP & HcED_HeadP_HALT) != 0) && ((ed->HcED.HeadP & 0xFFFFFFF0) != 0) ){
			hcd_delete_td((PHCD_ED)ed);
			hcd_pause_ed(ed);
		}
	}

	if(cc == CC_NOERROR){
		urb->status = (int)urb->result;
		if(urb->callback)
			urb->callback(urb);
	}

	td_next = (PHCD_TD)td->HcTD.NextTD;
	list_del(&td->list);
	hcd_free(td);

	return td_next;
}


/*******************************************************************************
    Routine Name    �Fhcd_writeback_done
    Form            �Fstatic void hcd_writeback_done(void);
    Parameters      �F
    Return value    �F
    Description     �F�z�X�g�R���g���[�����荞�� �]���I������
*******************************************************************************/
static void hcd_writeback_done(void)
{
	PURB	urb;
	PHCD_TD td_list, td_next;
	PHCD_ED ed;

	td_list = hcd_get_done_list();

	while (td_list) {

		urb = td_list->urb;
		ed = (PHCD_ED)urb->ed;
		if(ed->type == USB_CTRL){
			td_next = hcd_control_transfer_done(td_list);
		}
		else if(ed->type == USB_BULK){
			td_next = hcd_bulk_transfer_done(td_list);
		}
		else if(ed->type == USB_INT){
			td_next = hcd_interrupt_transfer_done(td_list);
		}
        else{
            dbg_printf( "Illegal Type! %x\n", ed->type );
            return;
        }

		td_list = td_next;
	}
}


/*******************************************************************************
    Routine Name    �Fhcd_rh_irq
    Form            �Fstatic void hcd_rh_irq(void);
    Parameters      �F
    Return value    �F
    Description     �F�z�X�g�R���g���[�����荞�ݏ��� ���[�g�n�u����
*******************************************************************************/
static void hcd_rh_irq(void)
{
	unsigned long hub_status;
	unsigned long port_status;

	hub_status = readl_reg(HcRhStatus);
	
	if(hub_status & RH_HS_OCIC){
		con_printf(" root hub: Overcurrent Indicator Changed.\n");
	 	con_printf(" root hub: please debug this code.\n");
		return;
	}
    else if (hub_status){
	 	con_printf(" root hub: please debug this code.\n");
		return;
	}

	port_status = readl_reg(HcRhPortStatus);

	if(port_status & RH_PS_CSC){
	 	dbg_printf(" root hub: Port Connect Status Changed.\n");
		writel_reg(HcRhPortStatus, RH_PS_CSC|RH_PS_PRS);
	}

	if(port_status & RH_PS_PRSC){
	 	dbg_printf(" root hub: Port Reset Status Changed.\n");
		writel_reg(HcRhPortStatus, RH_PS_PRSC);
		if( ((port_status & RH_PS_PES) != 0) && ((port_status & RH_PS_CCS) != 0) ){
			dbg_printf(" root hub: Port Connect Status = 1\n");
			dbg_printf("           %s speed device connected.\n",
				((port_status & RH_PS_LSDA) ? "low" : "full"));
			hcd_info.rh_status |= HcdRH_CONNECT;
			if(port_status & RH_PS_LSDA)
				hcd_info.rh_status |= HcdRH_SPEED;
			else
				hcd_info.rh_status &= ~HcdRH_SPEED;
		    usbctrl_otg_request(CONNECT);
		}
	}

	if(port_status & RH_PS_PESC){
	 	dbg_printf(" root hub: Port Enable Status Changed.\n");
		writel_reg(HcRhPortStatus, RH_PS_PESC);
		if( ((port_status & RH_PS_PES) == 0) || ((port_status & RH_PS_CCS) == 0) ){
			dbg_printf(" root hub: Port Connect Status = 0\n");
			hcd_info.rh_status |= HcdRH_DISCONNECT;

		    usbctrl_otg_request(DISCONNECT);
		}
	}

	else if(port_status & RH_PS_PSSC){
	 	con_printf(" root hub: Port Suspend Status Changed.\n");
	 	con_printf(" root hub: please debug this code.\n");
		/*writel_reg(HcRhPortStatus0, RH_PS_PSSC);*/
	}

	else if(port_status & RH_PS_OCIC){
	 	con_printf(" root hub: Port Overcurrent Indicator Status Changed.\n");
	 	con_printf(" root hub: please debug this code.\n");
		writel_reg(HcRhPortStatus, RH_PS_PRS);
		/*writel_reg(HcRhPortStatus, RH_PS_OCIC);*/
	}

	return;
}


/*******************************************************************************
    Routine Name    �Fhcd_ed_delete_list
    Form            �Fvoid hcd_ed_delete_list(void);
    Parameters      �F
    Return value    �F
    Description     �F�폜ED���X�g��ED�폜
*******************************************************************************/
void hcd_ed_delete_list(void)
{
	PHCD_ED ed;

	while(!list_empty(&hcd_info.ed_pause1)){
		ed = list_struct_entry(hcd_info.ed_pause1.Flink, HCD_ED, ed_list);
		list_del(&ed->ed_list);
		hcd_pause_ed(ed);
	}

	while(!list_empty(&hcd_info.ed_pause0)){
		ed = list_struct_entry(hcd_info.ed_pause0.Flink, HCD_ED, ed_list);
		list_del(&ed->ed_list);
		list_add(&ed->ed_list, &hcd_info.ed_pause1);
	}
	
	if(!list_empty(&hcd_info.ed_pause1)){
		writel_reg(HcInterruptEnable, OHCI_INTR_SF);
	}
}


/*******************************************************************************
    Routine Name    �Fusbhost_interrupt
    Form            �Fvoid usbhost_interrupt(void);
    Parameters      �F
    Return value    �F
    Description     �FUSB�z�X�g�h���C�o���荞�݃n���h��
*******************************************************************************/
void usbhost_interrupt(void)
{
	ulong status;
	ulong drq_addr;
	ulong drq_dir;

	status = readl_reg(SttTrnsCnt);
    /* DMA���荞�� */
	if(status&B_DMAIRQ){

		drq_addr = readl_reg(HostDataTrnsReq);
		drq_dir  = drq_addr & 1;
		drq_addr = drq_addr & 0xFFFFFFFE;

		dma_start((int)drq_dir, (long *)FifoAcc, (long *)drq_addr, 0x20000);

		writel_reg(SttTrnsCnt, B_DMAIRQ);

	}
    /* OHCI���荞�� */
	else if(status&B_OHCIIRQ){
    	if ((hcd_info.hcca->donehead != 0) && ((hcd_info.hcca->donehead & 0x01) == 0) ) {
	    	status = OHCI_INTR_WDH;
	    } else if ((status = (readl_reg(HcInterruptStatus) & readl_reg(HcInterruptEnable))) == 0) {
		    return;
	    }

	    dbg_printf(" HCD: Interrupt %lX frame: %lX\n", status, (ushort)hcd_info.hcca->framenumber);

	    if (status & OHCI_INTR_UE) {
		    hcd_info.disabled++;
		    writel_reg(HcInterruptDisable, 0xFFFFFFFF);
		    con_printf(" HCD: Unrecoverable Error, controller disabled");
	 	    con_printf(" HCD: please debug this code.\n");
	    }

	    if (status & OHCI_INTR_WDH) {
		    writel_reg(HcInterruptDisable, OHCI_INTR_WDH);
		    writel_reg(HcInterruptStatus, OHCI_INTR_WDH);
		    hcd_writeback_done();
		    writel_reg(HcInterruptEnable, OHCI_INTR_WDH);
	    }

	    if (status & OHCI_INTR_RHSC) {
		    writel_reg(HcInterruptDisable, OHCI_INTR_RHSC);
		    writel_reg(HcInterruptStatus, OHCI_INTR_RHSC);
		    hcd_rh_irq();
		    writel_reg(HcInterruptEnable, OHCI_INTR_RHSC);
	    }

	    if (status & OHCI_INTR_SO) {
		    writel_reg(HcInterruptStatus, OHCI_INTR_SO);
		    con_printf("USB Schedule overrun");
	    }

	    if (status & OHCI_INTR_SF) {
		    writel_reg(HcInterruptDisable, OHCI_INTR_SF);
		    writel_reg(HcInterruptStatus, OHCI_INTR_SF);
		    hcd_ed_delete_list();
	    }
		writel_reg(SttTrnsCnt, B_OHCIIRQ);
	}
}


/*******************************************************************************
    Routine Name    �Fhcd_exit
    Form            �Fvoid hcd_exit(void);
    Parameters      �F
    Return value    �F
    Description     �F�z�X�g�R���g���[���̏I������
*******************************************************************************/
void hcd_exit(void)
{
	hcd_info.disabled = 1;
    writel_reg( HostCtl, (B_DMAIRQ_MASK | B_OHCIIRQ_MASK) );
}


/*******************************************************************************
    Routine Name    �Fhcd_rh_disconnect
    Form            �Fint hcd_rh_disconnect(void);
    Parameters      �F
    Return value    �F���s����
    Description     �F���[�g�n�u�f�o�C�X�̃f�B�X�R�l�N�g����
*******************************************************************************/
int hcd_rh_disconnect(void)
{


    usbh_disconnect( (PDEVINFO *)&hcd_info.rh_device );
    hcd_info.rh_device = NULL;

    return OK;
}


/* end of file */
