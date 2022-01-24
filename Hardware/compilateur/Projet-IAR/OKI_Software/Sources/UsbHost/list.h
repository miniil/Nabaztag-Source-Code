/*******************************************************************************
    list.h
    JOB60842�T���v���v���O����
    ���X�g���䃋�[�`�� (�w�b�_�̂�)

    Copyright(C) 2003, Oki Electric Industry Co.,Ltd.
      All rights reserved.

    �X�V����
    Mar.31,2003 rev1.00:�V�K�쐬
*******************************************************************************/
#ifndef _LIST_H_
#define _LIST_H_

typedef struct _LIST_ENTRY {
	struct _LIST_ENTRY *Blink;
	struct _LIST_ENTRY *Flink;
}LIST_ENTRY, *pLIST_ENTRY;

/* ���X�g�ɒǉ����� */
__inline void __list_add(pLIST_ENTRY entry, pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	entry->Blink = Blink;	
	entry->Flink = Flink;
	Blink->Flink = entry;
	Flink->Blink = entry;	
}

/* ���X�g����폜���� */
__inline void __list_del(pLIST_ENTRY Blink, pLIST_ENTRY Flink)
{
	Flink->Blink = Blink;
	Blink->Flink = Flink;
}

/* ���X�g�G���g����` */
#define DEFINE_LIST_ENTRY(entry) \
LIST_ENTRY entry = {&(entry), &(entry)}

/* ���X�g���������(��)�ɂ��� */
#define INIT_LIST_ENTRY(ptr) do { \
	(ptr)->Flink = (ptr); (ptr)->Blink = (ptr); \
} while (0)

/* �G���g����������\���̂̐擪�̃A�h���X���擾���� */
#define list_struct_entry(entry, type, member) \
	((type *)((char *)(entry)-(unsigned long)(&((type *)0)->member)))


/* �G���g�������X�g�ɐ擪�ɒǉ����� */
__inline void list_add_top(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head, head->Flink);
}

/* �G���g�������X�g�̍Ō�ɒǉ����� */
__inline void list_add(pLIST_ENTRY entry, pLIST_ENTRY head)
{
	__list_add(entry, head->Blink, head);
}

/* �G���g�������X�g����폜���� */
__inline void list_del(pLIST_ENTRY entry)
{
	__list_del(entry->Blink, entry->Flink);
}

/* ���X�g���󂩃`�F�b�N���� */
__inline int list_empty(pLIST_ENTRY head)
{
	return (head->Flink == head);
}

#endif /* _LIST_H_ */
