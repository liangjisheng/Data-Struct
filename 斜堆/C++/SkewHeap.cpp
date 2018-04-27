/**
 * C ����: б��
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <iostream>
#include "SkewHeap.h"
using namespace std;

int main()
{
    int i;
    int a[]= {10,40,24,30,36,20,12,16};
    int b[]= {17,13,11,15,19,21,23};
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
    SkewHeap<int>* ha=new SkewHeap<int>();
    SkewHeap<int>* hb=new SkewHeap<int>();

    cout << "== б��(ha)���������: ";
    for(i=0; i<alen; i++)
    {
        cout << a[i] <<" ";
        ha->insert(a[i]);
    }
    cout << "\n== б��(ha)����ϸ��Ϣ: " << endl;
    ha->print();


    cout << "\n== б��(hb)���������: ";
    for(i=0; i<blen; i++)
    {
        cout << b[i] <<" ";
        hb->insert(b[i]);
    }
    cout << "\n== б��(hb)����ϸ��Ϣ: " << endl;
    hb->print();


    // ��"б��hb"�ϲ���"б��ha"�С�
    ha->merge(hb);
    cout << "\n== �ϲ�ha��hb�����ϸ��Ϣ: " << endl;
    ha->print();


    // ����
    ha->destroy();

	system("pause");
    return 0;
}