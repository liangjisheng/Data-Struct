
// C����ʵ��˫����,�ܴ洢��������

#ifndef _DOUBLE_LINK_H_
#define _DOUBLE_LINK_H_

// ����0:succeed,-1:failed
extern int create_dlink();
// ����0:succeed,-1:failed
extern int destroy_dlink();

// �ж��Ƿ�Ϊ��1:empty,0:not empty
extern int dlink_is_empty();
// ���ش�С
extern int dlink_size();

// ��ȡ��indexλ��Ԫ��,�ɹ����ؽڵ�ָ�룬���򷵻�NULL
extern void* dlink_get(int index);
// ��ȡ��1��Ԫ��,�ɹ����ؽڵ�ָ�룬���򷵻�NULL
extern void* dlink_get_first();
// ��ȡ���һ��Ԫ��,�ɹ����ؽڵ�ָ�룬���򷵻�NULL
extern void* dlink_get_last();

// ��value���뵽indexλ��,0:succeed,-1:failed
extern int dlink_insert(int index, void *pval);
// ��value���뵽��ͷλ��,0:succeed,-1:failed
extern int dlink_insert_first(void *pval);
// ��value���뵽ĩβλ��,0:succeed,-1:failed
extern int dlink_append_last(void *pval);

// ɾ������index�ڵ��λ��,0:succeed,-1:failed
extern int dlink_delete(int index);
// ɾ����һ���ڵ�,0:succeed,-1:failed
extern int dlink_delete_first();
// ɾ�����һ���ڵ�,0:succeed,-1:failed
extern int dlink_delete_last();

#endif // _DOUBLE_LINK_H_