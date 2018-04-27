
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 常规串的模式匹配,从目标串的pos位置处开始查找模式第一次出现的位置
// 返回值用索引表示
int pattern_match_General(const string& strDest, const string& strPattern, int pos = 0);

// KMP算法进行模式匹配,从目标串的pos位置处开始查找模式第一次出现的位置
// 返回值用索引表示
int pattern_match_KMP_first(const string& strDest, const string& strPattern, int* next, int pos = 0);

void pattern_match_KMP_All(const string& strDest, const string& strPattern, int* next, int pos = 0);

int pattern_match_KMP_1_first(const string& strDest, const string& strPattern, int* next, int pos = 0 );

void pattern_match_KMP_1_All(const string& strDest, const string& strPattern, int* next, int pos = 0 );

int pattern_match_KMP_2_first(const string& strDest, const string& strPattern, int* next, int pos = 0 );

void pattern_match_KMP_2_All(const string& strDest, const string& strPattern, int* next, int pos = 0 );


void compute_next(const string& strPattern, int* next)
{
	cout << __FUNCTION__ << ": ";
	// next[0] = 0;
	int nextvalue = 0;
	cout << next[0] << ' ';
	int i = 1, j = 0;

	while(i < (int)strPattern.length())
	{
		char ch = strPattern[i];
		char ch1 = strPattern[j];
		if(j == 0 || strPattern[i] == strPattern[j])
		{
			if(strPattern[i] == strPattern[j])
				next[i] = ++j;
			else
				next[i] = j;
			
			cout << next[i] << ' ';
			i++;
		}
		else
			j = next[j];
	}

	//for(int i = 1; i < strPattern.length(); i++)
	//{
	//	// store previous fail position k to index;
	//	index = next[i - 1];

	//	char ch, ch1;
	//	while(index >= 0 && strPattern[i] != strPattern[index + 1])
	//	{
	//		ch = strPattern[i];
	//		ch1 = strPattern[index + 1];
	//		index = next[index];
	//		ch1 = strPattern[index + 1];
	//	}

	//	if(strPattern[i] == strPattern[index + 1])
	//		next[i] = index + 1;
	//	else
	//		next[i] = 1;

	//	cout << next[i] << ' ';
	//}
	//cout << endl;
}

void compute_next_1(const string& strPattern, int* next)
{
	cout << __FUNCTION__ << ": ";
	cout << next[0] << ' ';
	int i = 1, j = 0;

	for(; i < strPattern.length(); i++)
	{
		char chi = strPattern[i];
		char chj = strPattern[j];
		if(strPattern[i] == strPattern[j])
		{
			j++;	// ++之前,j == next[i - 1]
			next[i] = j;
		}
		else
		{
			while(j > 0 && strPattern[i] != strPattern[j])
				j = next[j - 1];
			if(strPattern[i] == strPattern[j])
				next[i] = ++j;
			else	// j == 0 
				next[i] = 0;
		}

		cout << next[i] << ' ';
	}
}

int compNext(const char *check, int *next, int sizeCheck) 
{
	cout << __FUNCTION__ << ": ";

	int j = 1;
	int i = 0;
	while (j < sizeCheck)
	{
		char chi = check[i];
		char chj = check[j];
		if (check[i] == check[j])
			next[j++] = ++i;
		else 
		{
			if (i == 0) 
				next[j++] = 0;
			else 
				i = next[i];
		}
	}

	for (i = 0; i < sizeCheck; i++)
		printf("%d ", next[i]);

	return 0;
}

void makeNext(const char* P,int* next)
{
	cout << __FUNCTION__ << ": ";

	int q,k;//q:模版字符串下标；k:最大前后缀长度
	int m = strlen(P);//模版字符串长度
	next[0] = 0;//模版字符串的第一个字符的最大前后缀长度为0
	for (q = 1,k = 0; q < m; ++q)//for循环，从第二个字符开始，依次计算每一个字符对应的next值
	{
		char chk = P[k];
		char chq = P[q];
		while(k > 0 && P[q] != P[k])//递归的求出P[0]···P[q]的最大的相同的前后缀长度k
			k = next[k];          //不理解没关系看下面的分析，这个while循环是整段代码的精髓所在，确实不好理解  
		if (P[q] == P[k])//如果相等，那么最大相同前后缀长度加1
		    k++;
		next[q] = k;
	}

	for(int i = 0; i < m; i++)
		cout << next[i] << ' ';
}




int main()
{
	string strDest = "abcdbcabcabcacf";
	string strPattern = "abc";
	int *next = new int[strPattern.length()];
	memset(next, 0, sizeof(int) * strPattern.length());

	//compute_next(strPattern, next);
	//memset(next, 0, sizeof(int) * strPattern.length());
	//cout << endl;

	makeNext(strPattern.c_str(), next);
	memset(next, 0, sizeof(int) * strPattern.length());
	cout << endl;

	int pos = pattern_match_KMP_first(strDest, strPattern, next);
	cout << strPattern << " in " << strDest << ' ' << pos + 1 << endl;

	pattern_match_KMP_All(strDest, strPattern, next);
	cout << endl << endl;

	pos = pattern_match_KMP_1_first(strDest, strPattern, next);
	cout << strPattern << " in " << strDest << ' ' << pos + 1 << endl;

	pattern_match_KMP_1_All(strDest, strPattern, next);
	cout << endl << endl;

	pos = pattern_match_KMP_2_first(strDest, strPattern, next);
	cout << strPattern << " in " << strDest << ' ' << pos + 1 << endl;

	pattern_match_KMP_2_All(strDest, strPattern, next);
	cout << endl << endl;

	//compute_next_1(strPattern, next);
	//memset(next, 0, sizeof(int) * strPattern.length());
	//cout << endl;

	//compNext(strPattern.c_str(), next, strPattern.length());
	//memset(next, 0, sizeof(int) * strPattern.length());
	//cout << endl;

	// int pos = pattern_match_General(strDest, strPattern);
	// cout << pos + 1 << endl;


	delete [] next;
	next = NULL;
	system("pause");
	return 0;
}


int pattern_match_General(const string& strDest, const string& strPattern, int pos /* = 0 */)
{
	int i = pos;
	int j = 0;
	while(i < strDest.length() && j < strPattern.length())
	{
		char chDest = strDest[i];
		char chPattern = strPattern[j];
		if(strDest[i] == strPattern[j])	
		{
			i++;
			j++;	
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if(j == strPattern.length())
		return i - j;
	else
		return 0;
}


int pattern_match_KMP_first(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */)
{
	int i = pos, j = 0;
	while(i < strDest.length() && j < strPattern.length())
	{
		char chi = strDest[i];
		char chj = strPattern[j];
		if(strDest[i] == strPattern[j] || j == 0)
		{
			if(strDest[i] == strPattern[j])
			{
				i++;
				j++;
			}
			else
				i++;
		}
		else
			j = next[j];
	}

	if(j >= strPattern.length())
		return i - j;
	else
		return 0;
}

void pattern_match_KMP_All(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */)
{
	int i = pos, j = 0;
	while(i < strDest.length())
	{
		char chi = strDest[i];
		char chj = strPattern[j];
		if(strDest[i] == strPattern[j] || j == 0)
		{
			if(strDest[i] == strPattern[j])
			{
				i++;
				j++;
			}
			else
				i++;
		}
		else
			j = next[j];

		if(j >= strPattern.length())
		{
			cout << i - j << ' ';
			j = 0;
		}
	}
}

int pattern_match_KMP_1_first(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */)
{
	int i = pos, j = 0;
	while(i < strDest.length() && j < strPattern.length())
	{
		char chi = strDest[i];
		char chj = strPattern[j];
		// j = next[j]; 从模式串的第next[j]与目标串下一个字符开始比较
		for(j = next[j]; j < strPattern.length() && strDest[i] == strPattern[j]; i++, j++)
		{
			char chi = strDest[i];
			char chj = strPattern[j];
		}

		if(j == 0)
			i++;
		else if(j == strPattern.length())
			return i - j;
	}

	return -1;
}

void pattern_match_KMP_1_All(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */)
{
	int i = pos, j = 0;
	while(i < strDest.length())
	{
		char chi = strDest[i];
		char chj = strPattern[j];
		// j = next[j]; 从模式串的第next[j]与目标串下一个字符开始比较
		for(j = next[j]; j < strPattern.length() && strDest[i] == strPattern[j]; i++, j++)
		{
			char chi = strDest[i];
			char chj = strPattern[j];
		}

		if(j == 0)
			i++;
		else if(j == strPattern.length())
		{
			cout << i - j << ' ';
			j = 0;
		}
	}
}

int pattern_match_KMP_2_first(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */ )
{
	int j = 0;
	for(int i = 0; i < strDest.length(); i++)
	{
		while(j > 0 && strDest[i] != strPattern[j])
			j = next[j];
		if(strDest[i] == strPattern[j])
			j++;		
		if(j == strPattern.length())
			return  i + 1 - j;
	}

	return -1;
}

void pattern_match_KMP_2_All(const string& strDest, const string& strPattern, int* next, int pos /* = 0 */ )
{
	int j = 0;
	for(int i = 0; i < strDest.length(); i++)
	{
		while(j > 0 && strDest[i] != strPattern[j])
			j = next[j];
		if(strDest[i] == strPattern[j])
			j++;		
		if(j == strPattern.length())
		{
			cout << i + 1 - j<< ' ';
			j = 0;
		}
	}
}

