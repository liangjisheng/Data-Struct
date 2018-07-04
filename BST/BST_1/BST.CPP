#include"iostream"
#include"cstdlib"
using namespace std;
//BST二叉查找树
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

//定义节点结构
class UserInfo{
public:
	friend istream& operator>>(istream& in,UserInfo& user);
	bool operator==(const UserInfo& user);
	bool operator<(const UserInfo& user);
	bool operator>(const UserInfo& user);
	string myId,myPassword;
};
typedef UserInfo* BinNodePointer;

istream& operator>>(istream& in,UserInfo& user)
{
	in>>user.myId>>user.myPassword;
	return in;
}

bool UserInfo::operator ==(const UserInfo& user)
{return myId==user.myId&&myPassword==user.myPassword;}

bool UserInfo::operator <(const UserInfo& user)
{return myId<user.myId;}

bool UserInfo::operator >(const UserInfo& user)
{return myId>user.myId;}

//类模板定义
template<typename DataType>
class BST{
public:
	BST();
	bool empty()const;
	bool search(const DataType& item)const;
	void insert(const DataType& item);
	void Inorder(ostream& out,BinNodePointer p);
	bool searchDigui(BinNodePointer p,const DataType& item)const;
	void insertDigui(BinNodePointer p,const DataType& item);
	void Delete(const DataType& item);
	void search2(const DataType& item,bool& found,
				BinNodePointer& p,BinNodePointer& parent);
private:
	BinNodePointer root;
};

template<typename DataType>
inline BST<DataType>::BST()
{root=0;}

template<typename DataType>
bool BST<DataType>::empty()const
{return root==0;}

template<typename DataType>
bool BST<DataType>::search(const DataType& item)const
{
	BinNodePointer p=root;
	bool found=false;
	while(1){
		if(found||p==0)break;
		if(item.myId < p->myId)
			p=p->left;
		else if(item.myId > p->myId)
			p=p->right;
		else 
			found=true;
	}
	return found;
}

template<typename DataType>
void BST<DataType>::insert(const DataType& item)
{
	BinNodePointer p=root,praent;
	bool found=false;
	while(1){
		if(found||p==0)break;
		parent=p;
		if(item.myId < p->myId)
			p=p->left;
		else if(item.myId > p->myId)
			p=p->right;
		else
			found=true;
	}
	if(found==true)
		cerr<<"item already in the tree!"<<endl;
	else{
		p=&item;
		if(parent==0)
			root=p;
		else if(item.myId < parent->myId)
			parent->left=p;
		else
			parent->right=p;
	}
}

template<typename DataType>
void BST<DataType>::Inorder(ostream& out,BinNodePointer p)
{
	p=root;
	if(p!=0){
		Inorder(out,p->left);
		out<<p->data<<" ";
		Inorder(out,p->right);
	}
}

template<typename DataType>
bool BST<DataType>::searchDigui(BinNodePointer p,const DataType& item)const
{
	bool found=false;
	if(root==0)return false;
	if(item->data<p->data)
		return search2(p->left,item);
	else if(item->data>p->data)
		return search2(p->right,item);
	else 
		return true;
}

template<typename DataType>
void BST<DataType>::insertDigui(BinNodePointer p,const DataType& item)
{
	if(p==0)
		p=&item;
	if(item->data<p->data)
		insert2(p->left,item);
	else if(item->data>p->data)
		insert2(p->right,item);
	else 
		cerr<<"Item already in the tree!"<<endl;
}

template<typename DataType>
void BST<DataType>::Delete(const DataType& item)
{
	bool found;
	BinNodePointer x,parent;
	search2(item,found,x,parent);
	if(!found){
		cout<<"Item not in the BST"<<endl;
		exit(0);
	}
	//处理左右子树都不空
	if(x->left!=0&&x->right!=0){
		BinNodePointer xSucc=x->right;
		parent=x;
		while(xSucc->left!=0){//寻找中序后继
			parent=xSucc;
			xSucc=xSucc->left;
		}
		x->data=xSucc->data;
		x=xSucc;
	}
	BinNodePointer subtree=x->left;
	if(subtree==0)
		subtree=x->right;
	if(parent==0)
		root=parent;
	else if(parent->left==x)
		parent->left=subtree;
	else 
		parent->right=subtree;
	delete x;
}

template<typename DateType>
void BST<DateType>::search2(const DataType& item,bool& found,
							BinNodePointer& p,BinNodePointer& parent)
{
	p=root;
	parent=0;
	found=false;
	while(1){
		if(found||p==0)return ;
		if(item->data<p->data)
			parent=p,p=p->left;
		else if(item->data>p->data)
			parent=p,p=p->right;
		else 
			found=true;
	}
}

/*template<typename DataType>
bool BST<DataType>::UserInfo::operator ==(const UserInfo& user)
{return myId==user.myId&&myPassword==user.myPassword;}

template<typename DataType>
istream& BST<DataType>::UserInfo::operator>>(istream& in,UserInfo& user)
{
	in>>user.myId>>user.myPassword;
	return in;
}

template<typename DataType>
bool BST<DataType>::UserInfo::operator <(const UserInfo& user)
{return myId<user.myId;}

template<typename DataType>
bool BST<DataType>::UserInfo::operator >(const UserInfo& user)
{return myId>user.myId;}*/
#endif