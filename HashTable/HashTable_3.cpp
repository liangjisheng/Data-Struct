
// ���������������ؼ��ֶ�����pȡ������ֱ����Ϊ�洢��ַ������pһ��ȡС�ڵ��ڹ�ϣ����
// size������������ؼ��ֲ��������������Ǹ��ַ����������Ƚ�������ת����Ȼ���ڶ�pȡ��
// ѡ�������p���Ա����ͻ
// ������ֱ��Ѱַ������һ����ϣ����

// ���ŵ�ַ������򵥿�ݣ������������㣬����Ҳ���ڲ���ȱ�㡣����̽�ⷨ�����γɡ��Ѿۡ�
// ����������ܶ��¼������һ�飬����һ���γɡ��Ѿۡ�����¼��Խ��Խ�ࡣ���⣬���ŵ�ַ
// ������һ��ȱ�㣬ɾ�������Ե�ʮ�ָ��ӣ����ǲ���ֱ��ɾ���ؼ������ڵļ�¼�������ڲ���
// ɾ��λ�ú����Ԫ��ʱ�����ܻ�����Ҳ������������Ϊɾ��λ�����Ѿ����˿յ�ַ�����ҵ�
// ����ʱ����ֹ���ҡ�
// ����ַ�����÷��������й�ϣ��ַ��ͬ�Ľ�㹹��һ���������������ͷ�����ڹ�ϣ����
// ����ַ���������ھ��������ɾ���������
// ��ȿ��ŵ�ַ��������ַ���������ŵ㣺������֡��Ѿۡ����󣬹�ϣ��ַ��ͬ�Ĺؼ��ֲ���
// ������ͻ;����Ҫ�ؽ���ϣ���ڿ��ŵ�ַ���У������ϣ��������ؼ����˾���Ҫ�����ϣ��
// Ȼ���ؽ���ϣ����������ַ�����Ϊ��㶼�Ƕ�̬����ģ����Բ�����ֹ�ϣ���������
// ���ֵ��������ȿ��ŵ�ַ�����ؼ���ɾ�������㣬ֻ��Ҫ�ҵ�ָ����㣬ɾ���ý�㼴��

// ���ŵ�ַ��������ַ������ǧ������ڲ�ͬ���
// ���ؼ��ֹ�ģ�ٵ�ʱ�򣬿��ŵ�ַ��������ַ������ʡ�ռ䣬��Ϊ������ַ�����ܻ���ڹ�ϣ
// ������ִ����յ�ַ����������ڹؼ��ֹ�ģ�������£�����ַ���ͱȿ��ŵ�ַ������ʡ�ռ�
// ���������ָ������Ժ��Բ��ƣ��ؼ��ֶ࣬��ϣ����������Ŀյ�ַ������

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class HashTable
{
private:
	string *elem;		// �����Ƕ�̬���ٴ�ŵ�
	int size;			// ��ϣ��ı�
public:
	HashTable()
	{
		size = 2000;
		elem = new string[size];

		// ������Ǹ�λ���Ƿ��Ѿ�������û�����#��ǵ�ǰλ��Ϊ��
		for (int i = 0; i < size; ++i)
			elem[i] = "#";
	}

	~HashTable() { delete [] elem; }

	int hash(string &index)
	{
		// ��ϣ�������췽����ʹ��forѭ���еĹ��췽��Ϊindex�ַ����ҵ����ڹ�ϣ���еĶ�Ӧλ��  
		int code = 0;
		for (size_t i = 0; i < index.length(); ++i)
			code = (code * 256 + index[i] + 128) % size;
		return code;
	}

	// ����ÿ������hash���������Ĺ�ϣֵ����Ч��
	bool search(string &index, int &pos, int &times)
	{
		pos = hash(index);
		times = 0;	// ��¼��ͻ����
		// �����ϣֵ�ı�Ǵ�Ϊ�յĻ�����ô�Ͳ��ؼ���ô�λ���Ƿ�ռ�õ�����
		// �������ϣֵ�ı�Ǵ���ֵ��index��ȵĻ�����˵���ڴ���index֮ǰ��hash
		// �����Ѿ����������index�ַ�����ȵ��ַ����ˣ����ҽ��������pos����
		// ��ʱ����ʾ���ַ�����hash�����Ѿ����ڡ����Ե��ô���Ϊ�գ�����ռ��
		// ��Ԫ�ز���indexʱ����˵�������˹�ϣ��ͻ�������Ҫ����Ϊindex�ַ���
		// Ѱ��λ��
		while (elem[pos] != "#" && elem[pos] != index)
		{
			++times;
			if (times < size)//pos + 1��ֵ���ܻ����size��ֵ,ʹ������̽�ⷨ�����ϣ��ͻ
				pos = (pos + 1) % size;
			else			// //��ͻ�����ﵽ�˹�ϣ��ĳ��ȣ���ʾ������̽�ⷨ�Ҳ����ܹ�����index��
				return false;
		}

		if (elem[pos] == index)
			return true;	// ��ʾhash�����Ѿ����������index�ַ�����ȵ��ַ���
		else
			return false;	//��ϣ��ͻδ���
	}

	int insert(string &index)
	{
		int pos, times;
		//���ȼ��һ�´�������ַ����Ƿ���hash�����Ѿ�����,�������򷵻�2  
		if (search(index, pos, times))
			return 2;
		// ��ͻ�������ڱ�һ��(���߿�����涨)������£���index�ַ����������,
		// ��Ϊ�����ͻ�������࣬˵������ ���е�Ԫ���Ѿ��ܶ��ˣ�����ӿ��ܵ��±����������
		else if (times < size / 2)
		{
			elem[pos] = index;
			return 1;
		}
		else
		{
			// ��ͻ�������࣬��������Ԫ��Ҳ�����ˣ��޷��������µ�Ԫ�أ�
			// �����Ҫ�ؽ�һ������Ĺ�ϣ��
			recreate();
			return 0;  
		}
	}

	void recreate()
	{
		string *temp_elem;
		temp_elem = new string[size];  
		for(int i = 0;i < size;i++)  
			temp_elem[i] = elem[i];			//����������ʱ�ռ������ԭ����ϣ�����Ѿ���źõ�����
		int copy_size = size;				//Ȼ���¼��ԭ����ϣ��ĳ���  

		size = size * 2;					//�����ϣ��ĳ���,ʹ���Ϊԭ��������  
		delete [] elem;						//ɾ��ԭ������Ĺ�ϣ��Ŀռ䣬��ֹ�ڴ�й©  
		elem = new string[size];			//�����µĿռ�  
		for (int i = 0; i < size; i++)
			elem[i] = "#";					//��Ǻ�ԭ���Ѿ����Ԫ�ص�λ��  

		for (int i = 0; i < copy_size; i++)
			if(temp_elem[i] != "#")
				insert(temp_elem[i]);       //��ԭ���Ѿ��д��Ԫ�ص�λ�����²������  
		delete [] temp_elem;				//ɾ����ʱ����Ŀռ䣬��ֹ�ڴ�й©  
	}

	void Display()
	{
		cout << "pos\tcontent" << endl;
		for (int i = 0; i < size; ++i)
			if (elem[i] != "#")
				cout << i << '\t' << elem[i] << endl;
	}
};


int main()
{
	HashTable hashtable;
	string buffer[] = { "test", "asdf", "qwer", "zxcv", "ghjk", "tyui" };
	int nlen = sizeof(buffer) / sizeof(buffer[0]);
	
	for (int i = 0; i < nlen; ++i)
	{
		int ans = hashtable.insert(buffer[i]);
		if (0 == ans)
			cout << "insert failed" << endl;
		else if (1 == ans)
			cout << "insert success" << endl;
		else if (2 == ans)
			cout << "It already exists" << endl;
	}
	cout << endl;

	hashtable.Display();
	cout << endl;

	int temp_pos, temp_times;	// ��¼�ڹ�ϣ���в����λ�úͳ�ͻ����
	string str1 = "asdf";
	if (hashtable.search(str1, temp_pos, temp_times))
		cout << "search success" << endl;
	else
		cout << "search failed" << endl;

	cout << "pos: " << temp_pos << endl;
	cout << "times: " << temp_times << endl;

	temp_pos = 0;
	temp_times = 0;
	str1 = "aaaa";
	if (hashtable.search(str1, temp_pos, temp_times))
		cout << "search success" << endl;
	else
		cout << "search failed" << endl;

	cout << "pos: " << temp_pos << endl;
	cout << "times: " << temp_times << endl;

	system("pause");
	return 0;
}