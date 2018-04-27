/**
 * C++: б��
 *
 * @author skywang
 * @date 2014/03/31
 */

#ifndef _SKEW_HEAP_HPP_
#define _SKEW_HEAP_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

template <class T>
class SkewNode{
    public:
        T key;                // �ؼ���(��ֵ)
        SkewNode *left;        // ����
        SkewNode *right;    // �Һ���

        SkewNode(T value, SkewNode *l, SkewNode *r):
            key(value), left(l),right(r) {}
};

template <class T>
class SkewHeap {
    private:
        SkewNode<T> *mRoot;    // �����

    public:
        SkewHeap();
        ~SkewHeap();

        // ǰ�����"б��"
        void preOrder();
        // �������"б��"
        void inOrder();
        // �������"б��"
        void postOrder();

         // ��other��б�Ѻϲ���this�С�
        void merge(SkewHeap<T>* other);
        // �����(keyΪ�ڵ��ֵ)���뵽б����
        void insert(T key);
        // ɾ�����(keyΪ�ڵ��ֵ)
        void remove();

        // ����б��
        void destroy();

        // ��ӡб��
        void print();
    private:

        // ǰ�����"б��"
        void preOrder(SkewNode<T>* heap) const;
        // �������"б��"
        void inOrder(SkewNode<T>* heap) const;
        // �������"б��"
        void postOrder(SkewNode<T>* heap) const;

        // �����ڵ�x�ͽڵ�y
        void swapNode(SkewNode<T> *&x, SkewNode<T> *&y);
        // �ϲ�"б��x"��"б��y"
        SkewNode<T>* merge(SkewNode<T>* &x, SkewNode<T>* &y);

        // ����б��
        void destroy(SkewNode<T>* &heap);

        // ��ӡб��
        void print(SkewNode<T>* heap, T key, int direction);
};

/* 
 * ���캯��
 */
template <class T>
SkewHeap<T>::SkewHeap():mRoot(NULL)
{
}

/* 
 * ��������
 */
template <class T>
SkewHeap<T>::~SkewHeap() 
{
    destroy(mRoot);
}

/*
 * ǰ�����"б��"
 */
template <class T>
void SkewHeap<T>::preOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        cout<< heap->key << " " ;
        preOrder(heap->left);
        preOrder(heap->right);
    }
}

template <class T>
void SkewHeap<T>::preOrder() 
{
    preOrder(mRoot);
}

/*
 * �������"б��"
 */
template <class T>
void SkewHeap<T>::inOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        inOrder(heap->left);
        cout<< heap->key << " " ;
        inOrder(heap->right);
    }
}

template <class T>
void SkewHeap<T>::inOrder() 
{
    inOrder(mRoot);
}

/*
 * �������"б��"
 */
template <class T>
void SkewHeap<T>::postOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        postOrder(heap->left);
        postOrder(heap->right);
        cout<< heap->key << " " ;
    }
}

template <class T>
void SkewHeap<T>::postOrder() 
{
    postOrder(mRoot);
}

/*
 * ���������ڵ������
 */
template <class T>
void SkewHeap<T>::swapNode(SkewNode<T> *&x, SkewNode<T> *&y)
{
    SkewNode<T> *tmp = x;
    x = y;
    y = tmp;
}


/*
 * �ϲ�"б��x"��"б��y"
 */
template <class T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &x, SkewNode<T>* &y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;

    // �ϲ�x��yʱ����x��Ϊ�ϲ�������ĸ���
    // ����Ĳ����Ǳ�֤: x��key < y��key
    if(x->key > y->key)
        swapNode(x, y);

    // ��x���Һ��Ӻ�y�ϲ���
    // �ϲ���ֱ�ӽ���x�����Һ��ӣ�������Ҫ�������һ���������ǵ�npl��
    SkewNode<T> *tmp = merge(x->right, y);
    x->right = x->left;
    x->left  = tmp;

    return x;
}

/*
 * ��other��б�Ѻϲ���this�С�
 */
template <class T>
void SkewHeap<T>::merge(SkewHeap<T>* other)
{
    mRoot = merge(mRoot, other->mRoot);
}

/* 
 * �½���ֵΪkey�Ľ�㲢������뵽б����
 *
 * ����˵����
 *     heap б�ѵĸ����
 *     key ����Ľ��ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
template <class T>
void SkewHeap<T>::insert(T key)
{
    SkewNode<T> *node;    // �½����

    // �½��ڵ�
    node = new SkewNode<T>(key, NULL, NULL);
    if (node==NULL)
    {
        cout << "ERROR: create node failed!" << endl;
        return ;
    }

    mRoot = merge(mRoot, node);
}

/* 
 * ɾ�����
 */
template <class T>
void SkewHeap<T>::remove()
{
    if (mRoot == NULL)
        return NULL;

    SkewNode<T> *l = mRoot->left;
    SkewNode<T> *r = mRoot->right;

    // ɾ�����ڵ�
    delete mRoot;
    // ���������ϲ��������
    mRoot = merge(l, r); 
}

/* 
 * ����б��
 */
template <class T>
void SkewHeap<T>::destroy(SkewNode<T>* &heap)
{
    if (heap==NULL)
        return ;

    if (heap->left != NULL)
        destroy(heap->left);
    if (heap->right != NULL)
        destroy(heap->right);

    delete heap;
}

template <class T>
void SkewHeap<T>::destroy()
{
    destroy(mRoot);
}

/*
 * ��ӡ"б��"
 *
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
template <class T>
void SkewHeap<T>::print(SkewNode<T>* heap, T key, int direction)
{
    if(heap != NULL)
    {
        if(direction==0)    // heap�Ǹ��ڵ�
            cout << setw(2) << heap->key << " is root" << endl;
        else                // heap�Ƿ�֧�ڵ�
            cout << setw(2) << heap->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(heap->left, heap->key, -1);
        print(heap->right,heap->key,  1);
    }
}

template <class T>
void SkewHeap<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}
#endif