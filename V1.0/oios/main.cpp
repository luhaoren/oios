#include <bits/stdc++.h>
#include <windows.h>
using  namespace std;
void setColor(int num=0){
    HANDLE consolehwnd;//�������
    consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
    SetConsoleTextAttribute(consolehwnd,num);//����������ɫ
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
		string fileName;//�ļ��� 
		bool isDir;//�Ƿ�ΪĿ¼ 
		bool isDel;//�Ƿ�ɾ�� 
		int fa;//����Ŀ¼ 
		string dateTime;//����ʱ��	
		int grade;//Ȩ��:0��ͨ�û�1����Ա2ϵͳ����Ա 
		//�����ļ� 
		vector<string>text;
		//�����ļ��� 
		vector<int>son;//��Ŀ¼�µ��ļ� 
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
file fs[100010];//�ļ�ϵͳ
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
			//ɾ���ļ� 
			string s;
			cin>>s;
			for(auto it:fs[nowMenu].son){
				if(fs[it].fileName==s) fs[it].clear();
			}
		}
		if(order=="md"){
			//�����ļ��� 
			string s;
			cin>>s;
			fs[++fileNum](s,true,nowMenu);
			fs[nowMenu].son.push_back(fileNum);
		}
		if(order=="cd"){ 
			//�л��ļ��� 
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
			//ɾ���ļ��� 
			string s;
			cin>>s;
			for(auto it:fs[nowMenu].son){
				if(fs[it].fileName==s) clearFile(it);
			}			
		}
	}
	return 0;
}
