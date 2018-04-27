
// ������ʵ��
#include <iostream>
#include <string>

using namespace std;

enum elemTag{ATOM, LIST};

class GList;

class GLnode
{
private:
	elemTag Tag;		// ��־��ԭ�ӻ����ӱ�0:ԭ�� 1:�ӱ�
	union
	{
		char data;		// ԭ�ӽڵ�ֵ��
		struct			// ��ڵ�ָ����
		{
			GLnode *hp;	// ��ͷ�ڵ�
			GLnode *tp;	// ��β�ڵ�
		}ptr;
	};

	friend class GList;
};

class GList
{
public:
	// �ָ��ַ���
	string Decompose(string &str)
	{
		// ���ǿմ�str�ָ��2����,hstrΪ��һ��','֮ǰ���Ӵ�,strΪ�����
		int n = str.length();
		int i, k;
		string ch, hstr;
		for(i = 0, k = -1; i < n && (ch != "," || k != 0); i++)
		{
			// ���������ĵ�һ������
			ch = str.substr(i, 1);		// �ӵ�i��λ�����1���ַ�
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
    /�ӹ������д��ʽ��S��������ͷβ����洢��ʾ�Ĺ����T 
    /���������ͷβ���洢�ṹ�ĵݹ鶨�壺 
    /�������SΪ�մ�ʱ���ÿչ���� 
    /        ��SΪ���ַ���ʱ������ԭ�ӽ����ӱ� 
    /�ݹ������subΪ��ȥS��������ŵ��Ӵ�����Ϊ"s1,s2,s3,..,sn" 
    /        ÿ��siΪ�ǿ��ַ�������ÿ��si����һ������ 
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
				hsub = Decompose(S);	// ��S�з������ͷ��
				Create_GList(GL->ptr.hp, hsub);
				if(S.empty())
					GL->ptr.tp = NULL;
				else
					Create_GList(GL->ptr.tp, S);
			}
		}
	}

	/*----------------------------------------- 
    /�������Ϊ�ձ�ʱ�����Ϊ1���������Ϊԭ��ʱ 
    /���Ϊ0���������Ϊ�����ʱ����ȵ���Ϊ 
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

	 // T����GL
	void Copy_GList(GLnode *GL,GLnode *&T)
	{  
		//����Ϊ��ʱ�����ƿձ������ȸ��Ʊ�ͷ�ڸ��Ʊ�β  
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
    /�������������ǿձ�����"()"���������Tag=0 
    /�Ľ�㣬��ֱ������ý���ֵ�����tag=1��˵�� 
    /��һ���ӱ�������������ţ�Ȼ��ݹ����������� 
    /Ԫ�أ�������β���յ�ʱ��������ţ������������� 
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

	 // ȡ��ͷ
	void GetHead(GLnode *GL)
	{  
		//ȡ������һ��Ԫ��  
		cout<<"�����";  
		Traverse_GList(GL);  
		cout<<endl;  
		if(!GL || GL->Tag==0 )  
			cout<<"ԭ�ӺͿձ���ȡ��ͷ"<<endl;  
		else  
		{  
			GLnode *h=GL->ptr.hp;  
			if(h->Tag==ATOM)  
				cout<<"��ͷΪ��"<<h->data<<endl;  
			else  
			{  
				cout<<"��ͷΪ��";  
				Traverse_GList(h);  
				cout<<endl;  
			}  
		}  
	}

	 // ȡ��β
	void GetTail(GLnode *GL)
	{  
		//������βָ���ǳ��˵�һ��Ԫ�غ�����ʣ���Ԫ����ɵı�  
		cout<<"�����";  
		Traverse_GList(GL);  
		cout<<endl;  

		if(!GL || GL->Tag==0)  
			cout<<"ԭ�ӺͿձ���ȡ��β"<<endl;  
		else  
		{  
			GLnode *t;  
			t=GL->ptr.tp;  
			cout<<"��βΪ��";  
			Traverse_GList(t);  
			cout<<endl;  
		}  
	}

	 //�����ĳ���(�ǵݹ�)
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

	// �����ĳ���(�ݹ�)
	int Length_GList_2(GLnode *GL)
	{  
		if(!GL)  
			return 0;  
		return 1+Length_GList_2(GL->ptr.tp);  
	}

	// �滻������е�ĳ���ַ�
	void Replace_GList(GLnode *p,char x,char y,GLnode *&q)
	{  
		//�������p��Ԫ��x�滻��y�������¹����q  
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
				Replace_GList(p->ptr.hp,x,y,h);//�ݹ鴦���ͷ�õ�h  
				Replace_GList(p->ptr.tp,x,y,t);//�ݹ鴦���β�õ�t  
				q=new GLnode;  
				q->Tag=LIST;  
				q->ptr.hp=h;  
				q->ptr.tp=t;  
			}  
		}  
	}

	// �ж�����������Ƿ���ͬ
	int Is_Same(GLnode *p,GLnode *q)
	{  
		int flag=1;//1��ʾ��ȣ�0��ʾ�����  
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

	// �������������
	void Concat_Glist(GLnode *&GL,GLnode *LG)
	{  
		GLnode *p=GL;  
		GLnode *q=p->ptr.tp;  
		while(q->ptr.tp)  
			q=q->ptr.tp;  
		q->ptr.tp=LG;  
		//GL=p;  
	}

	// �������ԭ�ӽڵ����Ŀ
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
	// cout << "��������s: ";		// ((a,b),(c,d))
	// cin >> s;
	list.Create_GList(GL, s);
	cout<<"�����S�����Ϊ��"<<list.GList_Depth(GL)<<endl;
	cout<<"�����S�ĳ���Ϊ��"<<list.Length_GList_1(GL)<<endl;
	cout<<"�����S�ĳ���Ϊ��"<<list.Length_GList_2(GL)<<endl;
	cout << endl;

	cout << "ԭ�ӽڵ����:" << list.CountAtom(GL) << endl;
	cout << endl;

	list.GetHead(GL);  
	list.GetTail(GL);
	cout << endl;

	GLnode *T;  
	cout<<"���ƹ����"<<endl;  
	list.Copy_GList(GL,T);  
	cout<<"�������ƺ�Ĺ����T"<<endl;  
	list.Traverse_GList(T);  
	cout<<endl;
	cout<<endl;

	string F = "((a,b),(c,e))";
	// cout<<"��������F��";  
	//cin>>F;  
	GList list1;   
	GLnode *LG;  
	list1.Create_GList(LG,F);
	if(list.Is_Same(GL,LG))
		cout<<"�����S��F���"<<endl;  
	else  
		cout<<"�����S��F�����"<<endl;  

	cout<<"�����F�ĳ���Ϊ��"<<list1.Length_GList_2(LG)<<endl;
	cout << endl;

	char x = 'a';	// ���滻���ַ�
	char y = 's';	// �滻�ַ�
	//cout<<"������Ҫ�滻���ַ�: ";  
	//cin>>x;  
	//cout<<endl;  
	//cout<<"������Ҫ�滻���ĸ��ַ���";  
	//cin>>y;  
	GLnode *k;  
	list1.Replace_GList(LG,x,y,k);  
	cout<<"�滻��Ĺ����Ϊ��";  
	list1.Traverse_GList(k);  
	cout<<endl;
	cout<<endl;

	cout<<"���ӹ����S�뱻�滻�ַ���Ĺ����F�ı�Ϊ��";  
	list.Concat_Glist(GL,k);  
	list.Traverse_GList(GL);  
	cout<<endl;
	cout<<endl;

	system("pause");
	return 0;
}
