
// bitmap��һ��ʮ�����õĽṹ����ν��Bit-map������һ��bitλ�����ĳ��Ԫ�ض�Ӧ��Value��
// ��Key���Ǹ�Ԫ�ء����ڲ�����BitΪ��λ���洢���ݣ�����ڴ洢�ռ䷽�棬���Դ���ʡ��
// ���˵����ô�໹û����ʲô��Bit-map����ô��������һ����������ӣ���������Ҫ��0-7��
// ��5��Ԫ��(4,7,2,5,3)�������������ЩԪ��û���ظ�������ô���ǾͿ��Բ���Bit-map��
// �������ﵽ�����Ŀ�ġ�Ҫ��ʾ8���������Ǿ�ֻ��Ҫ8��Bit��1Bytes�����������ǿ���1Byte
// �Ŀռ䣬����Щ�ռ������Bitλ����Ϊ0
// Ȼ�������5��Ԫ�أ����ȵ�һ��Ԫ����4����ô�Ͱ�4��Ӧ��λ��Ϊ1�������������� 
// p+(i/8)|(0x01<<(i%8)) ��Ȼ������Ĳ����漰��Big-ending��Little-ending�����������Ĭ��
// ΪBig-ending��,��Ϊ�Ǵ��㿪ʼ�ģ�����Ҫ�ѵ���λ��Ϊһ
// Ȼ���ٴ����ڶ���Ԫ��7�����ڰ�λ��Ϊ1,�������ٴ���������Ԫ�أ�һֱ������������е�Ԫ��
// ����Ӧ��λ��Ϊ1
// Ȼ���������ڱ���һ��Bit����,����λ��һ��λ�ı�����(2,3,4,5,7)�����ʹﵽ�������Ŀ��

#ifndef _MYBITMAP_SORT_H_
#define _MYBITMAP_SORT_H_

/**
 * ��ʼ��bitmap
 * nSize:bitmap�Ĵ�С����bitλ�ĸ���
 * start:��ʼֵ
 * ����ֵ: -1��ʾʧ�ܣ�0��ʾ�ɹ�
*/
int bitmap_init(int nSize, int start);

/**
 * ��index��Ӧ��λ��Ϊ1
 * index:Ҫ���õ�ֵ
 * ����ֵ: -1��ʾʧ�ܣ�0��ʾ�ɹ�
*/
int bitmap_set(int index);

/**
 * ��ȡbitmap��iλ��ֵ
 * ����ֵ��-1��ʾʧ�ܣ����򷵻ض�Ӧλ��ֵ
*/
int bitmap_get(int i);

/**
 * ����indexλ��Ӧ��ֵ
*/
int bitmap_data(int index);

// �ͷ�
void bitmap_free();

#endif // _MYBITMAP_SORT_H_