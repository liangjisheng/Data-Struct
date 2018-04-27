
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

typedef int Type;

typedef struct _HuffmanNode
{
	Type key;
	struct _HuffmanNode *left;
	struct _HuffmanNode *right;
	struct _HuffmanNode *parent;
}HuffmanNode, *HuffmanTree;


// ǰ�����huffman��
void preorder_huffman(HuffmanTree tree);
// �������
void inorder_huffman(HuffmanTree tree);
// �������
void postorder_huffman(HuffmanTree tree);

// ����Huffman��
HuffmanNode* create_huffman(Type arr[], int size);

// ����Huffman��
void destroy_huffman(HuffmanTree tree);

// ��ӡHuffamn��
void print_huffman(HuffmanTree tree);

#endif // _HUFFMAN_TREE_H_