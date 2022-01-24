/*******************************************************************************
    hcdmem.c
    JOB60842�T���v���v���O����
    �z�X�g�R���g���[�����������䃋�[�`��

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
/* #define DEBUG */
#define DEBUG_INFO

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "typedef.h"
#include "hcdmem.h"

#define max(a,b)	( ( (a) > (b) ) ? (a) : (b) )

/*--------------------------------------------------------------------------*/
typedef struct _memory {
	struct _memory *Next;
	unsigned long Address;
	unsigned long Area;
	unsigned long Size;
} MMDL, *PMMDL;

typedef struct _buffer{
	PMMDL MMDLs;
	unsigned long Address;
	unsigned long PhyAddress;
	unsigned long Size;
	unsigned long Boundary;
} MBDL, *PMBDL;

/*--------------------------------------------------------------------------*/
#ifndef BufferBanks
#define BufferBanks		3
#endif

static MBDL BufferTable[BufferBanks] = {
	{ NULL, 0, 0, 0 ,0},
	{ NULL, 0, 0, 0 ,0},
	{ NULL, 0, 0, 0 ,0}
};

/*--------------------------------------------------------------------------*/
#define SetBoundary(Addr, Boundary) (((Addr) % (Boundary) == 0 ) ? (Addr) : \
									(((Addr) / (Boundary) + 1) * (Boundary)))


/*******************************************************************************
    Routine Name    �Fhcd_malloc_init
    Form            �Fint hcd_malloc_init(unsigned long Address, unsigned long Size,
                                          unsigned long Boundary, int Bank);
    Parameters      �FAddress           �o�b�t�@�������擪�A�h���X
                      Size              �o�b�t�@�������T�C�Y
                      Boundary          �o�E���_���w��
                      Bank              �o���N�ԍ�
    Return value    �F���s����
    Description     �F�o�b�t�@�������̏�����
*******************************************************************************/
int hcd_malloc_init(unsigned long Address, unsigned long Size,
                    unsigned long Boundary, int Bank)
{
	if(Bank>=0 && Bank<BufferBanks){
		BufferTable[Bank].MMDLs = NULL;
		BufferTable[Bank].Address = Address;
		BufferTable[Bank].Size = Size;
		BufferTable[Bank].Boundary = Boundary;

		#ifdef _WINDOWS
		BufferTable[Bank].PhyAddress = HcdBufferPhysicalAddress((char *)Address);
		#else
		BufferTable[Bank].PhyAddress = Address;
		#endif

	}else{
		dbg_printf(" hcd_malloc: Bad number of Bank.\n");
		return -1;
	}

	return 0;
}


/*******************************************************************************
    Routine Name    �Fhcd_malloc_check
    Form            �Fint hcd_malloc_check(void * Address);
    Parameters      �FAddress           �o�b�t�@�������擪�A�h���X
    Return value    �F�o���N�ԍ�
    Description     �F�g�p����o�b�t�@�������̃o���N���`�F�b�N����
*******************************************************************************/
int hcd_malloc_check(void * Address)
{
	int Bank;

	for(Bank = 0; Bank < BufferBanks; Bank++){
		if(((unsigned long)Address	< (unsigned long)BufferTable[Bank].Address 
										+ BufferTable[Bank].Size)
		&& ((unsigned long)Address	>= (unsigned long)BufferTable[Bank].Address)){
			return Bank;
		}
	}

	return -1;
}


/*******************************************************************************
    Routine Name    �Fhcd_malloc
    Form            �Fvoid *hcd_malloc(unsigned long Size, int Bank);
    Parameters      �FSize          �������T�C�Y
                      Bank          �o���N�ԍ�
    Return value    �F�������u���b�N�擪�A�h���X
    Description     �F�R�������������Ƀo�b�t�@�����������蓖�Ă�
*******************************************************************************/
void *hcd_malloc(unsigned long Size, int Bank)
{
	PMMDL	pLastMMDL;
	PMMDL	pNextMMDL;
	PMMDL	pNewMMDL;
	unsigned long	NextBufferAddress;
	PMBDL	Buffer;
	unsigned long	Area;

	if(Bank>=0 && Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		dbg_printf(" hcd_malloc: Bad number of Bank.\n");
		return NULL;
	}

	if(Buffer->Address == 0){
		dbg_printf("hcd_malloc: No memory for buffer.\n");
		return NULL;
	}

	if(Size==0) return NULL;

    if( Size > (Buffer->Size - sizeof(MMDL)) ){
        return NULL;
    }

	/*�G���A�Ƀ������Ǘ��̈��t������*/
	Area = Size + sizeof(MMDL);
	/*���蓖�ăG���A��4�o�C�g�P�ʂƂ���*/
	switch(Area % 4){
		case 1: Area = Area + 3; break;
		case 2: Area = Area + 2; break;
		case 3: Area = Area + 1; break;
        default:                 break;
	}

	/*�G���A���擾����*/
	if(Buffer->MMDLs == NULL){
		NextBufferAddress = Buffer->Address;
		pLastMMDL = NULL;
		pNextMMDL = NULL;
	}
	else{
		NextBufferAddress = SetBoundary(Buffer->Address, Buffer->Boundary);
		pLastMMDL = NULL;
		pNextMMDL = Buffer->MMDLs;

		while(pNextMMDL != NULL){ /*���X�g�̍Ō�܂Ō���������I���*/
		
			if(NextBufferAddress + Area <= pNextMMDL->Address){
				/*�G���A�����X�g�̓r������擾����*/
				break;
			}

			NextBufferAddress = SetBoundary(pNextMMDL->Address + pNextMMDL->Area, Buffer->Boundary);
			pLastMMDL = pNextMMDL;
			pNextMMDL = pLastMMDL->Next;
		}

	}

	/*�擾�G���A�T�C�Y�̊m�F*/
	if(NextBufferAddress + Area > Buffer->Address + Buffer->Size){
		return NULL;
	}

	/*MMDL�̎擾*/
	pNewMMDL = (PMMDL)(NextBufferAddress + Area - sizeof(MMDL));

	/*�V����MMDL�̐ݒ�*/
	pNewMMDL->Address = NextBufferAddress;
	pNewMMDL->Area = Area;
	pNewMMDL->Size = Size;

	/*�V����MMDL�|�C���^�̃Z�[�u*/
	if(pLastMMDL == NULL){
		Buffer->MMDLs = pNewMMDL;
	}else{
		pLastMMDL->Next = pNewMMDL;
	}

	/*����MMDL�|�C���^�̃Z�[�u*/
	pNewMMDL->Next = pNextMMDL;

	dbg_printf(" hcd_malloc: %08lX (%d,%d)\n", NextBufferAddress, Size, Area);

	return (unsigned char *)NextBufferAddress;
}


/*******************************************************************************
    Routine Name    �Fhcd_free
    Form            �Fint hcd_free(void * pAddress);
    Parameters      �FpAddress          �������u���b�N�擪�A�h���X
    Return value    �F���s����
    Description     �F�R�������������̃o�b�t�@���������J������
*******************************************************************************/
int hcd_free(void * pAddress)
{
	PMMDL	pLastMMDL;
	PMMDL	pNowMMDL;
	PMBDL	Buffer;
	int		Bank;

	dbg_printf(" hcd_free: %08lX\n", pAddress);

	/*�o�b�t�@�̃o���N�擾�ƃ`�F�b�N*/
	Bank = hcd_malloc_check(pAddress);
	if(Bank<0) return 0;

	Buffer = &BufferTable[Bank];

	/*�|�C���^��NULL�̏ꍇ�A�������Ȃ�*/
	if(pAddress == NULL) return 0;

	/*MMDL���Ȃ��ꍇ*/
	if(Buffer->MMDLs == NULL) return 0;

	/*�Y������MMDL��1�ڂ̏ꍇ*/
	pNowMMDL = Buffer->MMDLs;
	if((unsigned char *)pNowMMDL->Address == (unsigned char *)pAddress){
		Buffer->MMDLs = pNowMMDL->Next;
		/*free(pNowMMDL);*/
		return 1;
	}

	/*�Y������MMDL��2�ڈȍ~�̏ꍇ*/
	pLastMMDL = Buffer->MMDLs;
	while(pLastMMDL->Next != NULL){

		pNowMMDL = pLastMMDL->Next;

		if((unsigned char *)pNowMMDL->Address == (unsigned char *)pAddress){
			pLastMMDL->Next = pNowMMDL->Next;
			/*free(pNowMMDL);*/
			return 1;
		}

		pLastMMDL = pNowMMDL;
	}

	/*�Y��MMDL�Ȃ�*/
	return 0;
}


#ifdef DEBUG_INFO
/*******************************************************************************
    Routine Name    �Fhcd_malloc_info
    Form            �Fvoid hcd_malloc_info(int Bank);
    Parameters      �FBank          �o���N�ԍ�
    Return value    �F
    Description     �F�R�������������Ɋ��蓖�Ă��o�b�t�@��������\������
*******************************************************************************/
void hcd_malloc_info(int Bank)
{
	PMMDL	pLastMMDL;
	unsigned long	LastBufferAddress;
	PMBDL	Buffer;
	unsigned long 	DataSize = 0;
	unsigned long 	Gap1Size = 0;
	unsigned long 	Gap2Size = 0;
	unsigned long 	UsedSize;
	unsigned long 	FreeSize;
	
	if(Bank>=0 && Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		con_printf(" hcd_malloc_info: Bad number of Bank.\n");
        return;
	}

	con_printf("  hcd_malloc_info (Bank=%d)\n", Bank);

	pLastMMDL = Buffer->MMDLs;
	LastBufferAddress = Buffer->Address;

	while(pLastMMDL != NULL){
		if(LastBufferAddress != pLastMMDL->Address){
				con_printf("    %08lX :      : %4d = gap\n", LastBufferAddress,
					(unsigned short)(pLastMMDL->Address - LastBufferAddress));
				Gap2Size += (int)(pLastMMDL->Address - LastBufferAddress);
			}

		con_printf("    %08lX : %4d : %4d = use\n", pLastMMDL->Address, pLastMMDL->Size, pLastMMDL->Area);
		DataSize += pLastMMDL->Size;
		Gap1Size += (pLastMMDL->Area - pLastMMDL->Size);

		LastBufferAddress = pLastMMDL->Address + pLastMMDL->Area;
		pLastMMDL = pLastMMDL->Next;
	}

	UsedSize = Gap1Size + Gap2Size + DataSize;
	FreeSize = Buffer->Size - UsedSize; 

	con_printf("      Total Data Size =%6d\n", DataSize);
	con_printf("      Total Gap1 Size =%6d\n", Gap1Size);
	con_printf("      Total Gap2 Size =%6d\n", Gap2Size);
	con_printf("      Total Used Size =%6d\n", UsedSize);
	con_printf("      Total Free Size =%6d\n", FreeSize);

}
#endif


/*******************************************************************************
    Routine Name    �Fhcd_malloc_rest
    Form            �Fint hcd_malloc_rest(int Bank);
    Parameters      �FBank          �o���N�ԍ�
    Return value    �F�ő僁�����u���b�N�T�C�Y
    Description     �F�ő僁�����u���b�N�T�C�Y����������
*******************************************************************************/
int hcd_malloc_rest(int Bank)
{
	PMMDL	pLastMMDL;
	unsigned long	LastBufferAddress;
	PMBDL	Buffer;
	unsigned long Gap2MaxSize = 0;
	unsigned long FreeMaxSize;
	unsigned long rest;

	if(Bank>=0 && Bank<BufferBanks){
		Buffer = &BufferTable[Bank];
	}else{
		dbg_printf(" hcd_malloc_rest: Bad number of Bank.\n");
        return -1;
	}

	pLastMMDL = Buffer->MMDLs;
	LastBufferAddress = Buffer->Address;

	while(pLastMMDL != NULL){
		if(LastBufferAddress != pLastMMDL->Address){
				Gap2MaxSize = max(Gap2MaxSize, (int)(pLastMMDL->Address - LastBufferAddress));
			}

		LastBufferAddress = pLastMMDL->Address + pLastMMDL->Area;
		pLastMMDL = pLastMMDL->Next;
	}

	FreeMaxSize = Buffer->Size - (int)(LastBufferAddress - Buffer->Address);

	rest = max(Gap2MaxSize, FreeMaxSize)-sizeof(MMDL);

	return (int)rest;
}

/* End of File */
