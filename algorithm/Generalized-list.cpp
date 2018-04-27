
// 广义表的实现
#include <iostream>
#include <string>

using namespace std;

enum elemTag{ATOM, LIST};

class GList;

class GLnode
{
private:
	elemTag Tag;		// 标志是原子还是子表，0:原子 1:子表
	union
	{
		char data;		// 原子节点值域
		struct			// 表节点指针域
		{
			GLnode *hp;	// 表头节点
			GLnode *tp;	// 表尾节点
		}ptr;
	};

	friend class GList;
};

class GList
{
public:
	// 分割字符串
	string Decompose(string &str)
	{
		// 将非空串str分割成2部分,hstr为第一个','之前的子串,str为后面的
		int n = str.length();
		int i, k;
		string ch, hstr;
		for(i = 0, k = -1; i < n && (ch != "," || k != 0); i++)
		{
			// 搜索最外层的第一个括号
			ch = str.substr(i, 1);		// 从第i个位置起读1个字符
			if(ch == "(")
				k++;
			else if(ch == ")")
				k--;
		}

		if(i < n)
		{
			hstr = str.substr(1, i - 2);
			str = "(" + str.substr(i, n - i);
		}
		else
		{
			hstr = str.substr(1, n - 2);
			str = "";
		}

		return hstr;
	}

	/*---------------------------------------------------- 
    /从广义表书写形式串S创建采用头尾链表存储表示的广义表T 
    /建立广义表头尾结点存储结构的递归定义： 
    /基本项：当S为空串时，置空广义表 
    /        当S为单字符串时，建立原子结点的子表 
    /递归项：假设sub为脱去S最外层括号的子串，记为"s1,s2,s3,..,sn" 
    /        每个si为非空字符串，对每个si建立一个表结点 
    /--------------------------------------------------------*/  
	void Create_GList(GLnode *&GL, string S)
	{
		string hsub = "";
		if(S == "")
			GL = NULL;
		else
		{
			GL = new GLnode;
			if(S.length() == 1)
			{
				GL->Tag = ATOM;
				GL->data = S[0];
			}
			else
			{
				GL->Tag = LIST;
				hsub = Decompose(S);	// 从S中分离出表头串
				Create_GList(GL->ptr.hp, hsub);
				if(S.empty())
					GL->ptr.tp = NULL;
				else
					Create_GList(GL->ptr.tp, S);
			}
		}
	}

	/*----------------------------------------- 
    /当广义表为空表时，深度为1，当广义表为原子时 
    /深度为0，当广义表为广义表时，深度的求法为 
    /GList_Depth(GL)=1+max{GList_Depth(lsi)} 
    /-----------------------------------------*/ 
	int GList_Depth(GLnode *GL)
	{	 
		if(!GL)
			return 1;
		if(GL->Tag == ATOM)
			return 0;

		int dep, nmax;
		GLnode *p;
		for(nmax = 0, p = GL; p; p = p->ptr.tp)
		{
			dep = GList_Depth(p->ptr.hp);
			if(dep > nmax)
				nmax = dep;
		}

		return 1 + nmax;
	}

	 // T复制GL
	void Copy_GList(GLnode *GL,GLnode *&T)
	{  
		//当表为空时，复制空表，否则先复制表头在复制表尾  
		if(!GL)  
			T=NULL;  
		else  
		{  
			T=new GLnode;  
			T->Tag=GL->Tag;  
			if(GL->Tag==ATOM)  
				T->data=GL->data;  
			else  
			{  
				Copy_GList(GL->ptr.hp,T->ptr.hp);  
				Copy_GList(GL->ptr.tp,T->ptr.tp);  
			}  
		}  
	}  

	 /*----------------------------------------------- 
    /遍历广义表，如果是空表就输出"()"，如果遇到Tag=0 
    /的结点，则直接输出该结点的值，如果tag=1，说明 
    /是一个子表，首先输出左括号，然后递归调用输出数据 
    /元素，并当表尾不空的时候输出逗号，最后输出右括号 
    /-----------------------------------------------*/  
    void Traverse_GList(GLnode *L)  
    {  
        if(!L)  
            cout<<"()";  
        else  
        {  
            if(L->Tag==ATOM)  
                cout<<L->data;  
            else  
            {  
                GLnode *p=NULL;  
                cout<<'(';  
                p=L;  
                while(p)  
                {  
                    Traverse_GList(p->ptr.hp);  
                    p=p->ptr.tp;  
                    if(p)  
                        cout<<',';  
                }  
                cout<<')';  
            }  
        }
    }  

	 // 取表头
	void GetHead(GLnode *GL)
	{  
		//取广义表第一个元素  
		cout<<"广义表：";  
		Traverse_GList(GL);  
		cout<<endl;  
		if(!GL || GL->Tag==0 )  
			cout<<"原子和空表不能取表头"<<endl;  
		else  
		{  
			GLnode *h=GL->ptr.hp;  
			if(h->Tag==ATOM)  
				cout<<"表头为："<<h->data<<endl;  
			else  
			{  
				cout<<"表头为：";  
				Traverse_GList(h);  
				cout<<endl;  
			}  
		}  
	}

	 // 取表尾
	void GetTail(GLnode *GL)
	{  
		//广义表表尾指的是除了第一个元素后所有剩余的元素组成的表  
		cout<<"广义表：";  
		Traverse_GList(GL);  
		cout<<endl;  

		if(!GL || GL->Tag==0)  
			cout<<"原子和空表不能取表尾"<<endl;  
		else  
		{  
			GLnode *t;  
			t=GL->ptr.tp;  
			cout<<"表尾为：";  
			Traverse_GList(t);  
			cout<<endl;  
		}  
	}

	 //广义表的长度(非递归)
	int Length_GList_1(GLnode *GL)
	{
		int len = 0;
		if(GL && GL->Tag==LIST)  
		{  
			while(GL)  
			{  
				GL=GL->ptr.tp;  
				len++;  
			}  
			return len;  
		}  
		else  
			return 0;  
	}

	// 广义表的长度(递归)
	int Length_GList_2(GLnode *GL)
	{  
		if(!GL)  
			return 0;  
		return 1+Length_GList_2(GL->ptr.tp);  
	}

	// 替换广义表中的某个字符
	void Replace_GList(GLnode *p,char x,char y,GLnode *&q)
	{  
		//将广义表p中元素x替换成y，构建新广义表q  
		if(!p)  
			q=NULL;  
		else  
		{  
			if(p->Tag==ATOM)  
			{  
				q=new GLnode;  
				q->Tag=ATOM;  
				q->ptr.hp=NULL;  
				if(p->data==x)  
					q->data=y;  
				else  
					q->data=p->data;  
			}  
			else  
			{  
				GLnode *h,*t;  
				Replace_GList(p->ptr.hp,x,y,h);//递归处理表头得到h  
				Replace_GList(p->ptr.tp,x,y,t);//递归处理表尾得到t  
				q=new GLnode;  
				q->Tag=LIST;  
				q->ptr.hp=h;  
				q->ptr.tp=t;  
			}  
		}  
	}

	// 判断连个广义表是否相同
	int Is_Same(GLnode *p,GLnode *q)
	{  
		int flag=1;//1表示相等，0表示不相等  
		if(p && q)  
		{
			if(p->Tag==ATOM && q->Tag==ATOM)  
			{  
				if(p->data!=q->data)  
					flag=0;  
				else  
					flag=1;  
			}  
			else if(p->Tag==LIST &&q->Tag==LIST)
			{
				flag=Is_Same(p->ptr.hp,q->ptr.hp);
				if(flag)
					flag=Is_Same(p->ptr.tp,q->ptr.tp); 
			}
			else  
				flag=0; 
		}  
		else  
		{  
			if(p && !q)  
				flag=0;  
			if(!p && q)  
				flag=0;  
		}  
		return flag;  
	}  

	// 连接两个广义表
	void Concat_Glist(GLnode *&GL,GLnode *LG)
	{  
		GLnode *p=GL;  
		GLnode *q=p->ptr.tp;  
		while(q->ptr.tp)  
			q=q->ptr.tp;  
		q->ptr.tp=LG;  
		//GL=p;  
	}

	// 广义表中原子节点的数目
	int CountAtom(GLnode* GL)
	{
		if(!GL) return 0;
		if(GL->Tag == ATOM) return 1;
		int n1 = CountAtom(GL->ptr.hp);
		int n2 = CountAtom(GL->ptr.tp);
		return n1 + n2;
	}
};


int main()
{
	GList list;
	GLnode *GL = NULL;
	string s = "((a,b),(c,d))";
	// cout << "输入广义表s: ";		// ((a,b),(c,d))
	// cin >> s;
	list.Create_GList(GL, s);
	cout<<"广义表S的深度为："<<list.GList_Depth(GL)<<endl;
	cout<<"广义表S的长度为："<<list.Length_GList_1(GL)<<endl;
	cout<<"广义表S的长度为："<<list.Length_GList_2(GL)<<endl;
	cout << endl;

	cout << "原子节点个数:" << list.CountAtom(GL) << endl;
	cout << endl;

	list.GetHead(GL);  
	list.GetTail(GL);
	cout << endl;

	GLnode *T;  
	cout<<"复制广义表"<<endl;  
	list.Copy_GList(GL,T);  
	cout<<"遍历复制后的广义表T"<<endl;  
	list.Traverse_GList(T);  
	cout<<endl;
	cout<<endl;

	string F = "((a,b),(c,e))";
	// cout<<"输入广义表F：";  
	//cin>>F;  
	GList list1;   
	GLnode *LG;  
	list1.Create_GList(LG,F);
	if(list.Is_Same(GL,LG))
		cout<<"广义表S和F相等"<<endl;  
	else  
		cout<<"广义表S和F不相等"<<endl;  

	cout<<"广义表F的长度为："<<list1.Length_GList_2(LG)<<endl;
	cout << endl;

	char x = 'a';	// 被替换的字符
	char y = 's';	// 替换字符
	//cout<<"输入你要替换的字符: ";  
	//cin>>x;  
	//cout<<endl;  
	//cout<<"输入你要替换成哪个字符：";  
	//cin>>y;  
	GLnode *k;  
	list1.Replace_GList(LG,x,y,k);  
	cout<<"替换后的广义表为：";  
	list1.Traverse_GList(k);  
	cout<<endl;
	cout<<endl;

	cout<<"连接广义表S与被替换字符后的广义表F的表为：";  
	list.Concat_Glist(GL,k);  
	list.Traverse_GList(GL);  
	cout<<endl;
	cout<<endl;

	system("pause");
	return 0;
}
