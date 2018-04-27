
#include <stdio.h>
#include <stdlib.h>

#define LH 1
#define EH 0
#define RH -1

typedef int ElemType;
typedef struct BSTNode
{
	ElemType data;
	int bf;		// Æ½ºâÒò×Ó
	struct BSTNode *lchild;
	struct BSTNode *rchild;
}*PBSTree;

void R_Rotate(PBSTree* tree)
{
	PBSTree lc = (*tree)->lchild;
	(*tree)->lchild = lc->rchild;
	lc->rchild = *tree;
	*tree = lc;
}

void L_Rotate(PBSTree* tree)
{
	PBSTree rc = (*tree)->rchild;
	(*tree)->rchild = rc->lchild;
	rc->lchild = *tree;
	*tree = rc;
}

void LeftBalance(PBSTree* T)
{
	PBSTree lc, rd;
	lc = (*T)->lchild;
	switch(lc->bf)
	{
	case LH:
		(*T)->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		rd = lc->rchild;
		switch(rd->bf)
		{
		case LH:
			(*T)->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			(*T)->bf = lc->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			lc->bf = LH;
			break;
		}
		rd->bf = EH;
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
		break;
	}
}

void RightBalance(PBSTree* T)  
{  
	PBSTree lc,rd;  
	lc= (*T)->rchild;  
	switch (lc->bf)  
	{  
	case RH:  
		(*T)->bf = lc->bf = EH;  
		L_Rotate(T);  
		break;  
	case LH:  
		rd = lc->lchild;  
		switch(rd->bf)  
		{  
		case LH:  
			(*T)->bf = EH;  
			lc->bf = RH;  
			break;  
		case EH:  
			(*T)->bf = lc->bf = EH;  
			break;  
		case RH:  
			(*T)->bf = EH;  
			lc->bf = LH;  
			break;  
		}  
		rd->bf = EH;  
		R_Rotate(&(*T)->rchild);  
		L_Rotate(T);  
		break;  
	}  
}  

int InsertAVL(PBSTree* T, ElemType e, bool *taller)
{
	if((*T) == NULL)
	{
		(*T) = (PBSTree)malloc(sizeof(BSTNode));
		(*T)->bf = EH;
		(*T)->data = e;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
	}
	else if(e == (*T)->data)
	{
		*taller = false;
		return 0;
	}
	else if(e < (*T)->data)
	{
		if(!InsertAVL(&(*T)->lchild, e, taller))
			return 0;
		if(*taller)
		{
			switch((*T)->bf)
			{
			case LH:
				LeftBalance(T);
				*taller = false;
				break;
			case EH:
				(*T)->bf = LH;
				*taller = true;
				break;
			case RH:
				(*T)->bf = EH;
				*taller = false;
				break;
			}
		}
	}
	else
	{
		if(!InsertAVL(&(*T)->rchild, e, taller))
			return 0;
		if(*taller)
		{
			switch((*T)->bf)
			{
			case LH:
				(*T)->bf = EH;
				*taller = false;
				break;
			case EH:
				(*T)->bf = RH;
				*taller = true;
				break;
			case RH:
				RightBalance(T);
				*taller = false;
				break;
			}
		}
	}

	return 1;
}

bool FindNode(PBSTree root, ElemType e, PBSTree* pos)
{
	PBSTree pt = root;
	*pos = NULL;
	while(pt)
	{
		if(pt->data == e)
		{
			*pos = pt;
			return  true;
		}
		else if(e < pt->data)
			pt = pt->lchild;
		else
			pt = pt->rchild;
	}
	return false;
}

void InorderTra(PBSTree root)
{
	if(root)
	{
		InorderTra(root->lchild);
		printf("%d ", root->data);
		InorderTra(root->rchild);
	}
}


int main()
{
	int i, arr[] = {1, 23, 45, 34, 98, 9, 4, 35, 23};
	PBSTree root = NULL, pos;
	bool taller;
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		InsertAVL(&root, arr[i], &taller);

	InorderTra(root);
	if(FindNode(root, 103, &pos))
		printf("\n%d\n", pos->data);
	else
		printf("\nNot find this Node\n");

	getchar();
	return 0;
}
