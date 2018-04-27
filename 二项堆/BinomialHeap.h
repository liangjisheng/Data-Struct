
#ifndef _BINOMIAL_TREE_HPP_
#define _BINOMIAL_TREE_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

template <class T>
class BinomialNode {
    public:
        T key;                      // �ؼ���(��ֵ)
        int degree;                 // ����
        BinomialNode<T> *child;     // ����
        BinomialNode<T> *parent;    // ���ڵ�
        BinomialNode<T> *next;      // �ֵܽڵ�

        BinomialNode(T value):key(value), degree(0), 
            child(NULL),parent(NULL),next(NULL) {}
};

template <class T>
class BinomialHeap {
    private:
        BinomialNode<T> *mRoot;    // �����

    public:
        BinomialHeap();
        ~BinomialHeap();

        // �½�key��Ӧ�Ľڵ㣬��������뵽�������
        void insert(T key);
        // ��������м�ֵoldkey����Ϊnewkey
        void update(T oldkey, T newkey);
        // ɾ����ֵΪkey�Ľڵ�
        void remove(T key);
        // �Ƴ�������е���С�ڵ�
        void extractMinimum();

         // ��other�Ķ���Ѻϲ�����ǰ�������
        void combine(BinomialHeap<T>* other);

         // ��ȡ������е���С�ڵ�ļ�ֵ
        T minimum();
        // ��������Ƿ������ֵkey
        bool contains(T key);
        // ��ӡ�����
        void print();
    private:

        // �ϲ���������ѣ���child�ϲ���root��
        void link(BinomialNode<T>* child, BinomialNode<T>* root);
        // ��h1, h2�еĸ���ϲ���һ���������������������غϲ���ĸ��ڵ�
        BinomialNode<T>* merge(BinomialNode<T>* h1, BinomialNode<T>* h2);
         // �ϲ�����ѣ���h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
        BinomialNode<T>* combine(BinomialNode<T>* h1, BinomialNode<T>* h2);
        // ��ת�����root�������ط�ת��ĸ��ڵ�
        BinomialNode<T>* reverse(BinomialNode<T>* root);
        // �Ƴ������root�е���С�ڵ㣬������ɾ���ڵ��Ķ�����
        BinomialNode<T>* extractMinimum(BinomialNode<T>* root);
        // ɾ���ڵ㣺ɾ����ֵΪkey�Ľڵ㣬������ɾ���ڵ��Ķ�����
        BinomialNode<T>* remove(BinomialNode<T> *root, T key);
        // �ڶ�����root�в��Ҽ�ֵΪkey�Ľڵ�
        BinomialNode<T>* search(BinomialNode<T>* root, T key);

        // ���ӹؼ��ֵ�ֵ����������еĽڵ�node�ļ�ֵ����Ϊkey��
        void increaseKey(BinomialNode<T>* node, T key);
        // ���ٹؼ��ֵ�ֵ����������еĽڵ�node�ļ�ֵ��СΪkey
        void decreaseKey(BinomialNode<T>* node, T key);
        // ���¹ؼ��ֵ�ֵ�����¶���ѵĽڵ�node�ļ�ֵΪkey
        void updateKey(BinomialNode<T>* node, T key);

        // ��ȡ������е���С���ڵ�
        void minimum(BinomialNode<T>* root, BinomialNode<T> *&prev_y, BinomialNode<T> *&y);
        // ��ӡ�����
        void print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction);
};

/* 
 * ���캯��
 */
template <class T>
BinomialHeap<T>::BinomialHeap():mRoot(NULL)
{
}

/* 
 * ��������
 */
template <class T>
BinomialHeap<T>::~BinomialHeap() 
{
}

/*
 * ��ȡ������е���С���ڵ�
 *
 * ����˵����
 *     root    -- �����
 *     prev_y  -- [�������]��С���ڵ�y��ǰһ�����ڵ�
 *     y       -- [�������]��С���ڵ�
 */
template <class T>
void BinomialHeap<T>::minimum(BinomialNode<T>* root,
        BinomialNode<T> *&prev_y, BinomialNode<T> *&y)
{
    BinomialNode<T> *x, *prev_x;    // x�����������ĵ�ǰ�ڵ�

    if (root==NULL)
        return ;
 
    prev_x  = root;
    x       = root->next;
    prev_y = NULL;
    y      = root;
    // �ҵ���С�ڵ�
    while (x != NULL) {
        if (x->key < y->key) {
            y = x;
            prev_y = prev_x;
        }
        prev_x = x;
        x = x->next;
    }
}

/*
 * ��ȡ������е���С�ڵ�ļ�ֵ
 */
template <class T>
T BinomialHeap<T>::minimum()
{
    BinomialNode<T> *prev_y, *y;

    minimum(mRoot, prev_y, y);
 
   return y->key;
}

 
/*
 * �ϲ���������ѣ���child�ϲ���root��
 */
template <class T>
void BinomialHeap<T>::link(BinomialNode<T>* child, BinomialNode<T>* root)
{
    child->parent = root;
    child->next   = root->child;
    root->child = child;
    root->degree++;
}

/*
 * ��h1, h2�еĸ���ϲ���һ���������������������غϲ���ĸ��ڵ�
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::merge(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T>* root = NULL; //heapΪָ���¶Ѹ����
    BinomialNode<T>** pos = &root;

    while (h1 && h2)
    {
        if (h1->degree < h2->degree)
        {
            *pos = h1;
            h1 = h1->next;
        } 
        else 
        {
            *pos = h2;
            h2 = h2->next;
        }
        pos = &(*pos)->next;
    }
    if (h1)
        *pos = h1;
    else
        *pos = h2;

    return root;
}

/*
 * �ϲ�����ѣ���h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::combine(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T> *root;
    BinomialNode<T> *prev_x, *x, *next_x;

    // ��h1, h2�еĸ���ϲ���һ������������������root
    root = merge(h1, h2);
    if (root == NULL)
        return NULL;
 
    prev_x = NULL;
    x      = root;
    next_x = x->next;
 
    while (next_x != NULL)
    {
        if (   (x->degree != next_x->degree) 
            || ((next_x->next != NULL) && (next_x->degree == next_x->next->degree))) 
        {
            // Case 1: x->degree != next_x->degree
            // Case 2: x->degree == next_x->degree == next_x->next->degree
            prev_x = x;
            x = next_x;
        } 
        else if (x->key <= next_x->key) 
        {
            // Case 3: x->degree == next_x->degree != next_x->next->degree
            //      && x->key    <= next_x->key
            x->next = next_x->next;
            link(next_x, x);
        } 
        else 
        {
            // Case 4: x->degree == next_x->degree != next_x->next->degree
            //      && x->key    >  next_x->key
            if (prev_x == NULL) 
            {
                root = next_x;
            } 
            else 
            {
                prev_x->next = next_x;
            }
            link(x, next_x);
            x = next_x;
        }
        next_x = x->next;
    }

    return root;
}

/*
 * �������other�ϲ�����ǰ����
 */
template <class T>
void BinomialHeap<T>::combine(BinomialHeap<T> *other)
{
    if (other!=NULL && other->mRoot!=NULL)
        mRoot = combine(mRoot, other->mRoot);
}

/*
 * �½�key��Ӧ�Ľڵ㣬��������뵽������С�
 */
template <class T>
void BinomialHeap<T>::insert(T key)
{
    BinomialNode<T>* node;

    // ��ֹ������ͬ�ļ�ֵ
    if (contains(key))
    {
        cout << "Insert Error: the key (" << key << ") is existed already!" << endl;
        return ;
    }

    node = new BinomialNode<T>(key);
    if (node==NULL)
        return ;

    mRoot = combine(mRoot, node);
}

/*
 * ��ת�����root�������ط�ת��ĸ��ڵ�
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::reverse(BinomialNode<T>* root)
{
    BinomialNode<T>* next;
    BinomialNode<T>* tail = NULL;

    if (!root)
        return root;

    root->parent = NULL;
    while (root->next) 
    {
        next          = root->next;
        root->next = tail;
        tail          = root;
        root          = next;
        root->parent  = NULL;
    }
    root->next = tail;

    return root;
}

/*
 * �Ƴ������root�е���С�ڵ㣬������ɾ���ڵ��Ķ�����
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::extractMinimum(BinomialNode<T>* root)
{
    BinomialNode<T> *y, *prev_y;    // y����С�ڵ�

    if (root==NULL)
        return root;
 
    // �ҵ�"��С�ڵ��y"��"����ǰһ�����ڵ�prev_y"
    minimum(root, prev_y, y);
 
    if (prev_y == NULL)    // root�ĸ��ڵ������С���ڵ�
        root = root->next;
    else                // root�ĸ��ڵ㲻����С���ڵ�
        prev_y->next = y->next;
 
    // ��ת��С�ڵ�����ӣ��õ���С��child��
    // ��������ʹ����С�ڵ����ڶ������ĺ����Ƕ����������Ϊһ�ö����Ķ�����(��������С�ڵ�)
    BinomialNode<T>* child = reverse(y->child);
    // ��"ɾ����С�ڵ�Ķ����child"��"root"���кϲ���
    root = combine(root, child);

    // ɾ����С�ڵ�
    delete y;

    return root;
}

template <class T>
void BinomialHeap<T>::extractMinimum()
{
    mRoot = extractMinimum(mRoot);
}

/* 
 * ���ٹؼ��ֵ�ֵ����������еĽڵ�node�ļ�ֵ��СΪkey��
 */
template <class T>
void BinomialHeap<T>::decreaseKey(BinomialNode<T>* node, T key)
{
    if(key>=node->key || contains(key))
    {
        cout << "decrease failed: the new key(" << key <<") is existed already, " 
             << "or is no smaller than current key(" << node->key <<")" << endl;
        return ;
    }
    node->key = key;
 
    BinomialNode<T> *child, *parent;
    child = node;
    parent = node->parent;
    while(parent != NULL && child->key < parent->key)
    {
        swap(parent->key, child->key);
        child = parent;
        parent = child->parent;
    }
}

/* 
 * ���ӹؼ��ֵ�ֵ����������еĽڵ�node�ļ�ֵ����Ϊkey��
 */
template <class T>
void BinomialHeap<T>::increaseKey(BinomialNode<T>* node, T key)
{
    if(key<=node->key || contains(key))
    {
        cout << "decrease failed: the new key(" << key <<") is existed already, " 
             << "or is no greater than current key(" << node->key <<")" << endl;
        return ;
    }

    node->key = key;

    BinomialNode<T> *cur, *child, *least;
    cur = node;
    child = cur->child;
    while (child != NULL) 
    {
        if(cur->key > child->key)
        {
            // ���"��ǰ�ڵ�" < "��������"��
            // ����"���ĺ�����(���� �� ���ӵ��ֵ�)"�У��ҳ���С�Ľڵ㣻
            // Ȼ��"��С�ڵ��ֵ" �� "��ǰ�ڵ��ֵ"���л���
            least = child;
            while(child->next != NULL)
            {
                if (least->key > child->next->key)
                {
                    least = child->next;
                }
                child = child->next;
            }
            // ������С�ڵ�͵�ǰ�ڵ��ֵ
            swap(least->key, cur->key);

            // ��������֮���ٶ�"ԭ��С�ڵ�"���е�����ʹ��������С�ѵ����ʣ����ڵ� <= �ӽڵ�
            cur = least;
            child = cur->child;
        }
        else
        {
            child = child->next;
        }
    }
}

/* 
 * ���¶���ѵĽڵ�node�ļ�ֵΪkey
 */
template <class T>
void BinomialHeap<T>::updateKey(BinomialNode<T>* node, T key)
{
    if (node == NULL)
        return ;

    if(key < node->key)
        decreaseKey(node, key);
    else if(key > node->key)
        increaseKey(node, key);
    else
        cout <<"No need to update!!!" <<endl;
}

/* 
 * ��������м�ֵoldkey����Ϊnewkey
 */
template <class T>
void BinomialHeap<T>::update(T oldkey, T newkey)
{
    BinomialNode<T> *node;

    node = search(mRoot, oldkey);
    if (node != NULL)
        updateKey(node, newkey);
}

/*
 * ���ң��ڶ�����в��Ҽ�ֵΪkey�Ľڵ�
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::search(BinomialNode<T>* root, T key)
{
    BinomialNode<T> *child;
    BinomialNode<T> *parent = root;

    parent = root;
    while (parent != NULL)
    {
        if (parent->key == key)
            return parent;
        else
        {
            if((child = search(parent->child, key)) != NULL)
                return child;
            parent = parent->next;
        }
    }

    return NULL;
}
 
/*
 * ��������Ƿ������ֵkey
 */
template <class T>
bool BinomialHeap<T>::contains(T key)
{
    return search(mRoot, key)!=NULL ? true : false;
}

/* 
 * ɾ���ڵ㣺ɾ����ֵΪkey�Ľڵ�
 */
template <class T>
BinomialNode<T>* BinomialHeap<T>::remove(BinomialNode<T>* root, T key)
{
    BinomialNode<T> *node;
    BinomialNode<T> *parent, *prev, *pos;

    if (root==NULL)
        return root;

    // ���Ҽ�ֵΪkey�Ľڵ�
    if ((node = search(root, key)) == NULL)
        return root;

    // ����ɾ���Ľڵ�������������Ƶ������ڵĶ������ĸ��ڵ�
    parent = node->parent;
    while (parent != NULL)
    {
        // ��������
        swap(node->key, parent->key);
        // ��һ�����ڵ�
        node   = parent;
        parent = node->parent;
    }

    // �ҵ�node��ǰһ�����ڵ�(prev)
    prev = NULL;
    pos  = root;
    while (pos != node) 
    {
        prev = pos;
        pos  = pos->next;
    }
    // �Ƴ�node�ڵ�
    if (prev)
        prev->next = node->next;
    else
        root = node->next;

    root = combine(root, reverse(node->child)); 

    delete node;

    return root;
}

template <class T>
void BinomialHeap<T>::remove(T key)
{
    mRoot = remove(mRoot, key);
}

/*
 * ��ӡ"�����"
 *
 * ����˵����
 *     node       -- ��ǰ�ڵ�
 *     prev       -- ��ǰ�ڵ��ǰһ���ڵ�(���ڵ�or�ֵܽڵ�)
 *     direction  --  1����ʾ��ǰ�ڵ���һ������;
 *                    2����ʾ��ǰ�ڵ���һ���ֵܽڵ㡣
 */
template <class T>
void BinomialHeap<T>::print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction)
{
    while(node != NULL)
    {
        if(direction==1)    // node�Ǹ��ڵ�
            cout << "\t" << setw(2) << node->key << "(" << node->degree << ") is "<< setw(2) << prev->key << "'s child" << endl;
        else                // node�Ƿ�֧�ڵ�
            cout << "\t" << setw(2) << node->key << "(" << node->degree << ") is "<< setw(2) << prev->key << "'s next" << endl;

        if (node->child != NULL)
            print(node->child, node, 1);

        // �ֵܽڵ�
        prev = node;
        node = node->next;
        direction = 2;
    }
}

template <class T>
void BinomialHeap<T>::print()
{
    BinomialNode<T> *p;
    if (mRoot == NULL)
        return ;

    cout << "== �����( ";
    p = mRoot;
    while (p != NULL) 
    {
        cout << "B" << p->degree << " ";
        p = p->next;
    }
    cout << ")����ϸ��Ϣ��" << endl;

    int i=0;
    p = mRoot;
    while (p != NULL) 
    {
        i++;
        cout << i << ". ������B" << p->degree << ":" << endl;
        cout << "\t" << setw(2) << p->key << "(" << p->degree << ") is root" << endl;

        print(p->child, p, 1);
        p = p->next;
    }
    cout << endl;
}
#endif