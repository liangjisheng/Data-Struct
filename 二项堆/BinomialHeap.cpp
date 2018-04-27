
#include <iostream>
#include "BinomialHeap.h"
using namespace std;

#define DEBUG 0

// ��7�� = 1+2+4
int a[] = {12,  7, 25, 15, 28, 
           33, 41};
// ��13�� = 1+4+8
int b[] = {18, 35, 20, 42,  9, 
           31, 23,  6, 48, 11, 
           24, 52, 13 };

// ��֤"����ѵĲ������"
void testInsert()
{
    int i;
    int alen=sizeof(a)/sizeof(a[0]);
    BinomialHeap<int>* ha=new BinomialHeap<int>();

    cout << "== �����(ha)���������: ";
    for(i=0; i<alen; i++)
    {
        cout << a[i] <<" ";
        ha->insert(a[i]);
    }
    cout << endl;
    cout << "== �����(ha)����ϸ��Ϣ: " << endl;
    ha->print();
}

// ��֤"����ѵĺϲ�����"
void testUnion()
{
    int i;
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
    BinomialHeap<int>* ha=new BinomialHeap<int>();
    BinomialHeap<int>* hb=new BinomialHeap<int>();

    cout << "== �����(ha)���������: ";
    for(i=0; i<alen; i++)
    {
        cout << a[i] <<" ";
        ha->insert(a[i]);
    }
    cout << endl;
    cout << "== �����(ha)����ϸ��Ϣ: " << endl;
    ha->print();


    cout << "== �����(hb)���������: ";
    for(i=0; i<blen; i++)
    {
        cout << b[i] <<" ";
        hb->insert(b[i]);
    }
    cout << endl;
    cout << "== �����(hb)����ϸ��Ϣ: " << endl;
    hb->print();


    // ��"�����hb"�ϲ���"�����ha"�С�
    ha->combine(hb);
    cout << "== �ϲ�ha��hb�����ϸ��Ϣ: " << endl;
    ha->print();
}

// ��֤"����ѵ�ɾ������"
void testDelete()
{
    int i;
    int blen=sizeof(b)/sizeof(b[0]);
    BinomialHeap<int>* hb=new BinomialHeap<int>();

    cout << "== �����(hb)���������: ";
    for(i=0; i<blen; i++)
    {
        cout << b[i] <<" ";
        hb->insert(b[i]);
    }
    cout << endl;
    cout << "== �����(hb)����ϸ��Ϣ: " << endl;
    hb->print();


    // ��"�����hb"�ϲ���"�����ha"�С�
    hb->remove(20);
    cout << "== ɾ���ڵ�20�����ϸ��Ϣ: " << endl;
    hb->print();
}

// ��֤"����ѵĸ���(����)����"
void testDecrease()
{
    int i;
    int blen=sizeof(b)/sizeof(b[0]);
    BinomialHeap<int>* hb=new BinomialHeap<int>();

    cout << "== �����(hb)���������: ";
    for(i=0; i<blen; i++)
    {
        cout << b[i] <<" ";
        hb->insert(b[i]);
    }
    cout << endl;
    cout << "== �����(hb)����ϸ��Ϣ: " << endl;
    hb->print();


    // ���ڵ�20����Ϊ2
    hb->update(20, 2);
    cout << "== ���½ڵ�20->2�����ϸ��Ϣ: " << endl;
    hb->print();
}

// ��֤"����ѵĸ���(����)����"
void testIncrease()
{
    int i;
    int blen=sizeof(b)/sizeof(b[0]);
    BinomialHeap<int>* hb=new BinomialHeap<int>();

    cout << "== �����(hb)���������: ";
    for(i=0; i<blen; i++)
    {
        cout << b[i] <<" ";
        hb->insert(b[i]);
    }
    cout << endl;
    cout << "== �����(hb)����ϸ��Ϣ: " << endl;
    hb->print();


    // ���ڵ�6����Ϊ60
    hb->update(6, 60);
    cout << "== ���½ڵ�6->60�����ϸ��Ϣ: " << endl;
    hb->print();
}

int main()
{
    // 1. ��֤"����ѵĲ������"
    testInsert();
    // 2. ��֤"����ѵĺϲ�����"
    //testUnion();
    // 3. ��֤"����ѵ�ɾ������"
    //testDelete();
    // 4. ��֤"����ѵĸ���(����)����"
    //testDecrease();
    // 5. ��֤"����ѵĸ���(����)����"
    //testIncrease();
    
	system("pause");
    return 0;
}