
// C语言实现双链表,能存储任意数据

#ifndef _DOUBLE_LINK_H_
#define _DOUBLE_LINK_H_

// 创建0:succeed,-1:failed
extern int create_dlink();
// 销毁0:succeed,-1:failed
extern int destroy_dlink();

// 判断是否为空1:empty,0:not empty
extern int dlink_is_empty();
// 返回大小
extern int dlink_size();

// 获取第index位置元素,成功返回节点指针，否则返回NULL
extern void* dlink_get(int index);
// 获取第1个元素,成功返回节点指针，否则返回NULL
extern void* dlink_get_first();
// 获取最后一个元素,成功返回节点指针，否则返回NULL
extern void* dlink_get_last();

// 将value插入到index位置,0:succeed,-1:failed
extern int dlink_insert(int index, void *pval);
// 将value插入到表头位置,0:succeed,-1:failed
extern int dlink_insert_first(void *pval);
// 将value插入到末尾位置,0:succeed,-1:failed
extern int dlink_append_last(void *pval);

// 删除表中index节点的位置,0:succeed,-1:failed
extern int dlink_delete(int index);
// 删除第一个节点,0:succeed,-1:failed
extern int dlink_delete_first();
// 删除最后一个节点,0:succeed,-1:failed
extern int dlink_delete_last();

#endif // _DOUBLE_LINK_H_