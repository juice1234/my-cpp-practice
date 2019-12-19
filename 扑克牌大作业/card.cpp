#include<iostream>
#include<iomanip>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
using namespace std;
struct card{
	int num;
	int position;
	int color;
};//�����ƵĴ�С����ɫ���Լ����λ��
card pok[104];
card player[4][26];
int showmap();
void savegame();
void loadgame();
int opt=1,in01,in02,spe,choice01,choice02,choice03;
int showmenu();
//ϴ�ƣ�ͨ�����衮position��0~103��ͬ��ֵ���ٰ���position��˳�����򣬾͵õ������������
int shuffle(){
	for(int a=0;a<4;a++){
		for(int b=0;b<26;b++){
			opt=1;
			int i=a*26+b;
			int r[104],opt=1;
			while(opt){
				opt=0;
			    r[i]=rand()%104;
			    for(int n=0;n<i;n++)
				    if(r[n]==r[i]) opt=1;//��ֹÿ���Ƶ������ֵ�ظ�
			}
			pok[i].position=r[i];
		}
	}
	cout<<"shuffle complete"<<endl;
	choice01=0;choice02=0;
	system("pause");
	system("cls");
	return showmenu();
}
int deal(){
	for(int i=0;i<104;i++){
		player[pok[i].position%4][pok[i].position/4]=pok[i];//����position��˳��ֵ��player
	}
	for(int n=0;n<4;n++){
		for(int j=0;j<26;j++){
			int flag=1;
			for(int i=0;i<25-j;i++){
				if(player[n][i].num>player[n][i+1].num){
					card temp=player[n][i];
					player[n][i]=player[n][i+1];
					player[n][i+1]=temp;
					flag=0;
				}
				if(flag) continue;
			}
		}
	}
	showmap();
	return showmenu();
}
int print01(int i,int n){
	SetConsoleOutputCP(936);
	switch(player[n][i].color){
	case 0:cout<<setw(3)<<(char)3;break;
	case 1:cout<<setw(3)<<(char)4;break;
	case 2:cout<<setw(3)<<(char)5;break;
	case 3:cout<<setw(3)<<(char)6;break;
	case 4:cout<<setw(3)<<" ";break;
	}
	return 0;
}
int print02(int i,int n){
	if(player[n][i].num!=1&&player[n][i].num!=11&&player[n][i].num!=12&&player[n][i].num!=13&&player[n][i].num!=0)
		cout<<setw(3)<<player[n][i].num;
	if(player[n][i].num==1) cout<<setw(3)<<"A";
	if(player[n][i].num==11) cout<<setw(3)<<"J";
	if(player[n][i].num==12) cout<<setw(3)<<"Q";
	if(player[n][i].num==13) cout<<setw(3)<<"K";
	if(player[n][i].num==0) cout<<setw(3)<<" ";
	return 0;
}
int showmap(){
	system("cls");
	cout<<setw(4)<<" ";
	for(int i1=0;i1<26;i1++) print01(i1,3);
	cout<<endl<<endl;
	cout<<setw(4)<<" ";
	system("color 07");
	for(int i2=0;i2<26;i2++) print02(i2,3);
	cout<<endl<<setw(25)<<" "<<"player 4"<<endl;
	for(int i3=0;i3<26;i3++){
		print01(i3,2);
		cout<<" ";
		print02(i3,2);
		if(i3==12){cout<<" "<<"player 3"<<setw(39)<<" "<<"player 1";}
		else cout<<setw(56)<<" ";
		print01(i3,0);
	    cout<<" ";
		print02(i3,0);
		cout<<endl;
	}
	cout<<endl<<setw(4)<<" ";
    for(int i7=0;i7<26;i7++) print01(i7,1);
	cout<<endl<<setw(4)<<" ";
	for(int i8=0;i8<26;i8++) print02(i8,1);
	cout<<endl<<setw(25)<<" "<<"player 2"<<endl;;
	return 0;
}
//ÿ�γ��ƺ󣬽�����λ��֮�������ǰ�ƣ�������ÿո��
int adjust(int a,int b){
	if(a==25){
		player[b][25].num=0;
		player[b][25].color=4;
		return 0;
	}
	else{
		player[b][a]=player[b][a+1];
		return adjust(a+1,b);
	}
}
//���ڼ��player[r][i]�������Ƿ񹹳�ը�������ǣ������Ѱ��
int bn_check(int r,int i){
	if(i==27||choice03==0) return i;
	int j=0;
	for(int a=0;a<26;a++){
		if(player[r][a].num==player[r][i].num&&player[r][a].num!=0) j++;}
	if(j==3&&player[r][i].num!=13) return bn_check(r,i+1);
	else return i;
}
//��ӡ��ʱ�����������
int begin(int i,int r){
	showmap();
	cout<<"player "<<r+1<<":";
	cout<<setw(10)<<" ";
	print01(i,r);
	cout<<endl<<setw(19)<<" ";
	print02(i,r);
	cout<<endl<<"0) menu"<<endl;
	cout<<"1) pause"<<endl;
	adjust(i,r);
	in01=i,in02=r;
	if(_kbhit()){
		int command;
		cin>>command;
		if(command==0){
			system("cls");
			opt=0;
			showmenu();
		}
		else if(command==1) system("pause");
		else return 0;
	}
	Sleep(spe*500);
	return 0;
}
//����Ƿ�ȫ��ը��
int allbom(int j){
	int c=1,a=0;
	for(a=0;a<26;a++){
		if(player[j][a].num==0) break;}
	while(a%3==0){
		for(int b=0;b<a/3;b++){
			if(player[j][3*b].num!=player[j][3*b+1].num||player[j][3*b+1].num!=player[j][3*b+2].num) c=0;}
		return c;
	}
	return 0;
}
//��ը��ʱ�Ĳ���
int bm_check(int &b,int j){
	if(b!=0||choice03==0) return 0;
	if(allbom(j)){b=player[j][0].num;return 1;}
	for(int i=0;i<24;i++){
		int b0=0,b1=0;
		if(player[j][i].num==player[j][i+1].num==player[j][i+2].num&&player[j][i].num!=0) b0=player[j][i].num;
		if(b0!=0&&i!=0) b1=0;else b1=i+3;
		if(b0!=0&&(player[0][2].num==0||player[1][2].num==0||player[2][2].num==0||player[3][2].num==0||player[j][b1].num>5)){b=b0;return 1;}
	}
	return 0;
}
//�ж���һ������Ƿ��и����ը��
int doubm(int &b,int j,int m){
	if(b==0||choice03==0) return 0;
	for(int i=0;i<24;i++){
		int b0=0;
		if(player[j][i].num==player[j][i+1].num==player[j][i+2].num) b0=player[j][i].num;
		if(b0>b&&(player[j][4].num==0||player[m][1].num==0)){b=b0;return 1;}
	}
    return 0;
}
//��ӡ��ը��ʱ���ƾ�
int bm_begin(int j,int b){
	for(int i=0;i<26;i++){
		if(player[j][i].num==b&&player[j][i+3].num!=b){showmap();cout<<"player "<<j+1<<":";cout<<setw(10)<<" ";
		print01(i,j);cout<<" ";print01(i+1,j);cout<<" ";print01(i+2,j);cout<<endl<<setw(19)<<" ";
		print02(i,j);cout<<" ";print02(i+1,j);cout<<" ";print02(i+2,j);
		adjust(i+2,j);adjust(i+1,j);adjust(i,j);return 0;}
	}
	Sleep(spe*500);
	return 0;
}
//�ж��Ƿ���Ҫͬ��ɫ���ܳ���
int c_check(int b,int i,int r){
	if(choice01==0) return 1;
	else if(player[r][i].color==b) return 1;
	else return 0;
}
//�ж��Ƿ���Ҫ�������ڲ��ܳ���
int n_check(int a,int i,int r){
	if(choice02==0) return 1;
	else if(player[r][i].num==a+1) return 1;
	else return 0;
}
//�ж���һ����ҳ���
int play(int r,int a,int b){
	int con=0,j,bom=0,bomer=4,m,nb;
	opt=1;
	while(opt){
		if(r==3) j=0;
		else j=r+1;
		for(int i=0;i<26;i++){
            m=bn_check(j,i);
			if(m==27){con++;break;}
			if(c_check(b,m,j)&&n_check(a,m,j)&&player[j][m].num>a&&bom==0){
				r=j;
				a=player[r][m].num;
				b=player[r][m].color;
				begin(m,j);
				con=0;
				bom=0;
				break;
			}
			else if(bm_check(bom,j)){bm_begin(j,bom);con=0;r=j;bomer=j;break;}
			else if(doubm(bom,j,bomer)){bm_begin(j,bom);con=0;r=j;bomer=j;break;}
			else con++;
		}
		for(int n=0;n<4;n++){
		    if(player[n][0].num==0){
			    cout<<endl<<"player "<<n+1<<" wins"<<endl;
				system("pause");
			    opt=0;
			    break;
			}
		}
		if(con/26==3&&con%26==0){
			if(r==3) j=0;
		    else j=r+1;
			if(j==3) j=0;
		    else j=j+1;
			con=0;
			bom=0;
			r=j;
			nb=bn_check(j,0);
			if(player[j][nb].num==0&&bm_check(bom,j)){bm_begin(j,bom);bomer=j;continue;}
			a=player[r][nb].num;
			b=player[r][nb].color;
			begin(nb,j);
		}
		if(con%26==0&&con/26!=3&&con!=0) r=j;
		if(con%26!=0) con=0;
	}
	showmenu();
	return 0;
}
//��Ϸ����
void help(){
	while(1){
	   system("cls");
	   cout<<"ϴ�������������棬��������Ƶ����С�����֮ǰ����ϴ�ƣ����Բ�ֻϴһ�Σ�������֮ǰ���뷢�ơ�"<<endl;
       cout<<"���������ʼ�Զ����ƺ����ѡ��һ�ҿ�ʼ����"<<endl;
	   cout<<"��˳ʱ�뷽����Ҹ��ƣ������Ʊ�����ǰһ��ͬ��ɫ�ұ���һ�������"<<endl;
	   cout<<"�з��ϵ����ѡ��һ�ţ����û�з���Ҫ���Ƶ���������ƣ�����һ�Ҽ������ơ��������û��������Ҹ�����һ�ֽ����ɵ�ǰ��Ҽ������ơ�"<<endl;
	   cout<<"press 0 to return"<<endl;
	   char command;
	   command=getch();
	   if(command=='0'){
		  system("cls");
		  showmenu();
		  return;
	   }
	}
}
//�����Ӻ���
int sz(){
	cout<<"���ѡ��һλ��ҿ�ʼ���ƣ����������ʼ������"<<endl;
	system("pause");
	int r;
	do{
		system("cls");
		cout<<"press any key to stop"<<endl;
		r=rand()%4+1;
		cout<<r<<endl;
		system("color 0c");
		if(_kbhit()){ system("pause");break;}
	}while(1);
	system("color 07");
	int nb;
	if(choice03==0) nb=0;
	else nb=bn_check(r-1,0);
	begin(nb,r-1);play(r-1,player[r-1][nb].num,player[r-1][nb].color);
	return 0;
}
//������ҳ����ٶ�
int speed(){
	system("cls");
	cout<<"choose the speed of players"<<endl;
	cout<<"1) fast"<<endl<<"2) common"<<endl<<"3) slow"<<endl;
	do{
	char command;
	command=getch();
	if(command=='1'||command=='2'||command=='3'){ spe=(int)command-48;break;}
	else cout<<"input again"<<endl;}while(1);
	return sz();
}
//ѡ����ƹ���
int rules(){
	system("cls");
	if(choice01!=0||choice02!=0){play(in02,player[in02][in01].num,player[in02][in01].color);return 0;}
	cout<<"choose the rules for the game first(you can choose more than one)"<<endl;
	cout<<"1) ���Ž��Ʊ���ͬ��ɫ"<<endl;
	cout<<"2) �����������ڲ��ܽ���"<<endl;
	cout<<"3) �����ƿ���ը(ֻ�������Ʋ���ը)"<<endl;
	char command;
	while(command!='0'||(choice01==0&&choice02==0&&choice03==0)){
	    cout<<"input your choices:";
	    command=getch();
		if(command!='1'&&command!='2'&&command!='3'&&command!='0'){cout<<"input again"<<endl;cin.clear();cin.sync();continue;}
		if(command=='0'&&choice01==0&&choice02==0&&choice03==0){cout<<"input again"<<endl;continue;}
		if(command=='1') choice01=1;
		if(command=='2') choice02=1;
		if(command=='3') choice03=1;
		cout<<"you have chosen:"<<command<<endl;
		cout<<"if you confirm,press 0"<<endl;
	}
	speed();
	return 0;
}
//��ӡ�˵�����������ѡ��ͬ����
int showmenu(){
	cout<<"0) exit"<<endl;
	cout<<"1) shuffle"<<endl;
	cout<<"2) deal"<<endl;
	cout<<"3) begin"<<endl;
	cout<<"4) savegame"<<endl;
	cout<<"5) loadgame"<<endl;
	cout<<"6) help"<<endl;
	int con=0;
	do{
	char command;
	command=getch();//���벻����
	switch(command){
	case '0':return 0;
	case '1':shuffle();break;
	case '2':deal();break;
	case '3':{rules();break;}
	case '4':{savegame();break;}
	case '5':{loadgame();break;}
	case '6':help();break;
	default:{cin.clear();cin.sync();cout<<"input again"<<endl;system("pause");con=1;break;}//������Ч���ж�
	}
	}while(con);
	return 0;
}
int main(){
	for(int a=0;a<4;a++){
		for(int b=0;b<26;b++){
			int i=a*26+b;
			pok[i].num=b/2+1;
			pok[i].color=a;
		}
	}//��ʼ��pok[]��δ���
	showmenu();
	return 0;
}
void savegame(){
	ofstream f("saved_game.txt");
	if( f.is_open())
	{
		for(int i=0;i<4;i++){
			for(int j=0;j<26;j++){
		        f << player[i][j].num << '\t' << endl;
				f << player[i][j].color << '\t' << endl;
			}
		}
		f<<in01<<'\0'<<in02<<'\0'<<choice01<<'\0'<<choice02<<'\0'<<choice03<<'\0'<<spe;
		f.close();
		cout << "Saved OK!" << endl;
	}
	else
		cout << "Can not open file!" << endl;
	system("pause");
	return;
}
void loadgame(){
	ifstream f("saved_game.txt");
	if( f.is_open())
	{
		for(int i=0;i<4;i++){
			for(int j=0;j<26;j++){
		       f >> player[i][j].num>>player[i][j].color;
		if( f.fail() )
		{ cout<< "Wrong!" <<endl; goto Exit; }
		}
		}
		f>>in01>>in02>>choice01>>choice02>>choice03>>spe;
		f.close();
		play(in02,player[in02][in01].num,player[in02][in01].color);
		return;
	}
	else
		cout << "Can not open file!" << endl;
Exit:
	f.close();
	system("pause");
	return;
}