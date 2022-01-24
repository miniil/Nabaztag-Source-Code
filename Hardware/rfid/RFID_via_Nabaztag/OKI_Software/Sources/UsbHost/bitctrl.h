/*******************************************************************************
    bitctrl.h
    JOB60842�T���v���v���O����
    �r�b�g���䃋�[�`�� (�w�b�_�̂�)

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef BITCTRL_H
#define BITCTRL_H

/*�r�b�g0�T�[�`*/
unsigned char __inline find_zero_bit(void *map, unsigned char max, unsigned char start)
{
	unsigned long *ptr = (unsigned long *)map;
	while(start<max){
		if(((*ptr >> start) & 1) == 0) break;
		start++;
		if(start%(32) == 0) ptr += 1;
	}
	return start;
}

/*�r�b�g�Z�b�g*/
void __inline set_bit(int nr, void *addr)
{
	int bit = nr % (32);
	unsigned long * ptr = (unsigned long *)addr + (nr / (32)); 
	unsigned long data = *ptr | ((unsigned long)1l << bit);
	*ptr = data;
}

/*�r�b�g�N���A*/
void __inline clear_bit(int nr, volatile void *addr)
{
	int bit = nr % (32);
	unsigned long * ptr = (unsigned long *)addr + (unsigned long)(nr / (32)); 
	*ptr &= ~((unsigned long)1l << bit);
}

/*�r�b�g�̃`�F�b�N*/
int __inline test_bit(int nr, volatile void * addr)
{
	int bit = nr % (32);
	unsigned long * ptr = (unsigned long *)addr + (nr / (32));
	int data = (int)((*ptr >> bit) & 1ul);  
	return data;
}

/*�r�b�g�̔��]*/
void __inline change_bit(int nr, volatile void * addr)
{
	int bit = nr % (32);
	unsigned long * ptr = (unsigned long *)addr + (nr / (32)); 
	unsigned long data;
	data = (( *ptr >> bit ) & 1l) ? *ptr & ~((unsigned long)1l << bit) : *ptr | ((unsigned long)1l << bit);
	*ptr = data;
}

/*�r�b�g�̃`�F�b�N �� �r�b�g�̃N���A*/
int __inline test_and_clear_bit(int nr, volatile void * addr)
{
	int ret;
	ret = test_bit(nr, addr);
	if(ret)
		clear_bit(nr, addr);
	return ret;
}

#endif	/* BITCTRL_H */
