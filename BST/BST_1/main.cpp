#include"iostream"
#include"fstream"
#include"string"
#include"cstdlib"
using namespace std;
#include"BST.CPP"

int main(int argc,char *argv[])
{
	ifstream userFile("UsersFile");
	if(!userFile.is_open()){
		cerr<<"Cannot open UserFile"<<endl;
		exit(-1);
	}
	//构造用户记录BST
	BST<UserInfo> userTree;
	UserInfo user;
	while(1){
		userFile>>user;
		if(userFile.eof())break;
		userTree.insert(user);
	}
	//登录验证
	cout<<"Enter Q Q to stop proceessing."<<endl;
	while(1){
		cout<<"User id & password:";
		cin>>user;
		if(user.myId=="Q")break;
		if(userTree.search(user))
			cout<<"Valid user"<<endl;
		else
			cout<<"Not a valid user"<<endl;
	}
	return 0;
}