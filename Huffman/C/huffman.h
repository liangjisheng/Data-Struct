
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


// 前序遍历huffman树
void preorder_huffman(HuffmanTree tree);
// 中序遍历
void inorder_huffman(HuffmanTree tree);
// 后序遍历
void postorder_huffman(HuffmanTree tree);

// 创建Huffman树
HuffmanNode* create_huffman(Type arr[], int size);

// 销毁Huffman树
void destroy_huffman(HuffmanTree tree);

// 打印Huffamn树
void print_huffman(HuffmanTree tree);

#endif // _HUFFMAN_TREE_H_