#include <bits/stdc++.h>
#include <windows.h>
using  namespace std;
void setColor(int num=0){
    HANDLE consolehwnd;//创建句柄
    consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);//实例化句柄
    SetConsoleTextAttribute(consolehwnd,num);//设置字体颜色
}
string getTime(){
	SYSTEMTIME st;
	GetLocalTime(&st);
	char c[110];
	sprintf(c,"%d-%d-%d %d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	return c; 
}
class file{
	public:
		string fileName;//文件名 
		bool isDir;//是否为目录 
		bool isDel;//是否被删除 
		int fa;//所在目录 
		string dateTime;//创建时间	
		int grade;//权限:0普通用户1管理员2系统管理员 
		//若是文件 
		vector<string>text;
		//若是文件夹 
		vector<int>son;//该目录下的文件 
		void operator()(string filename,bool isdir,int father,int Grade=0){
			dateTime=getTime();
			fileName=filename,isDir=isdir,fa=father,grade=Grade;
			isDel=false;
		}
		void clear(){
			isDel=true;
			fileName=" ",dateTime=" ";
			text.clear();
			fa=-1,isDir=false;
			son.clear();
		}	
		file(){
			isDel=true;
			fileName=" ",dateTime=" ";
			text.clear(),son.clear();
			fa=-1,isDir=false;			
		}	
};
file fs[100010];//文件系统
int nowMenu,fileNum=0;
void init(){
	fs[0]("oios",true,0);
	SetConsoleTitle("OIOS"); 
	nowMenu=0; 
} 
auto handle(){
	char c[1024];
	fgets(c,1024,stdin);
	int l=strlen(c);
	vector<string>orders;
	for(int i=0;i<l;i++){
		string s;
		while(c[i]!=' '&&i<l) s.push_back(c[i++]);
		while(c[i]==' '&&i<l) i++;
		orders.push_back(s);
	}
	return orders;
} 
void clearFile(int i){
	if(!fs[i].son.empty()){
		for(auto it:fs[i].son) clearFile(it);
	}
	fs[i].clear();
}
void pwd(int i){
	if(i!=0) pwd(fs[i].fa);
	cout<<fs[i].fileName<<"/";
}
void help(){
	ifstream in("help.txt");
	while(!in.eof()){
		char c[1024];
		in.getline(c,1024);
		cout<<c<<endl;
	}
} 
int main(){
	init();
	while(true){
		setColor(2);
		pwd(nowMenu);
		setColor(7);
		string order;
		cin>>order;
		if(order=="time") cout<<getTime()<<endl;
		if(order=="ls"){
			if(fs[nowMenu].son.empty()) cout<<"no file!\n";
			for(auto it:fs[nowMenu].son){
				if(!fs[it].isDel) cout<<fs[it].fileName<<" "<<fs[it].dateTime<<endl;
			}
		}
		if(order=="exit") exit(-1);
		if(order=="help") help();
		if(order=="cls") system("cls");
		if(order=="del"){			
			//删除文件 
			string s;
			cin>>s;
			for(auto it:fs[nowMenu].son){
				if(fs[it].fileName==s) fs[it].clear();
			}
		}
		if(order=="md"){
			//创建文件夹 
			string s;
			cin>>s;
			fs[++fileNum](s,true,nowMenu);
			fs[nowMenu].son.push_back(fileNum);
		}
		if(order=="cd"){ 
			//切换文件夹 
			string s;
			cin>>s;			
			if(s=="up") nowMenu=fs[nowMenu].fa;
			else{
				for(auto it:fs[nowMenu].son){
					if(fs[it].fileName==s){
						nowMenu=it;
						break;
					}
				} 
			}
		}
		if(order=="rd"){
			//删除文件夹 
			string s;
			cin>>s;
			for(auto it:fs[nowMenu].son){
				if(fs[it].fileName==s) clearFile(it);
			}			
		}
	}
	return 0;
}
