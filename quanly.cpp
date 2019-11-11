#include <iostream>
#include<stdio.h>
#include <cstring>]
#include<string.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include<time.h>
#include <ctime>
#include<algorithm>
#include<string>
using namespace std; 

short boxx = 1, boxy = 12, boxs = 103, boxw = 40; //Vi tri bat dau x, y cua box, box size, so tu hien thi trong khung (di chuyen len xuong)
int i;												//tuong tu nhu con tro first-last
bool updated = false; //Kiem tra xem co thay doi du lieu hay khong
struct tai_san
{
	string ten_tai_san, nguoi_thue, dien_thoai, tinh_trang;
	int so_ngay_thue;
	string ngay_thue;
	tai_san *link;
};
struct list
{
	tai_san *first,*last;
};
void Init(list &l)
{
	l.first=l.last=NULL;
}
void gotoxy(short x,short y) { //Ham di chuyen con tro den vi tri nao do trong Console
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

tai_san *getnode(string ten,string hoten,string sdt,string tt,int so_ngay,string ngay_thue)
{
	tai_san *a;
	a=new tai_san;
	if(a==NULL)
		return NULL;
	a->ten_tai_san=ten;
	a->nguoi_thue=hoten;
	a->dien_thoai=sdt;
	a->tinh_trang=tt;
	a->so_ngay_thue=so_ngay;
	a->ngay_thue=ngay_thue;
	a->link=NULL;
	return a;
}
int sn(int thang, int nam)
{
	switch(thang)
	{
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			return 31;
		break;
		case 4:case 6:case 9:case 11:
			return 30;
		case 2:
			if(nam%4||!nam%100&&nam%400)
				return 29;
			else
				return 28;
	}
}
void tach_ngay(string a,int &ngay,int &thang,int &nam)
{
	int i=0;
	while(a[i]!='/')
	{
		ngay=ngay*10+(int)a[i]-48;
		i++;
	}
	i++;
	while(a[i]!='/')
	{
		thang=thang*10+(int)a[i]-48;
		i++;
	}
	i++;
	while((int)a[i]>47&&(int)a[i]<58)
	{
		nam=nam*10+(int)a[i]-48;
		i++;
	}
}
bool qua_han(string a,int b)
{
	time_t hientai = time(0);
	struct tm *now=localtime(&hientai);
	now->tm_year+=1900;
	now->tm_mon+=1;
	int ngay=0,thang=0,nam=0,i=0;
	tach_ngay(a,ngay,thang,nam);
	ngay+=b;
	while(ngay>sn(thang,nam))
	{
		ngay-=sn(thang,nam);
		thang++;
		if(thang>12)
		{
			thang=1;
			nam++;
		}
	}
	if(nam<now->tm_year)
	{
		return true;
	}
	if(nam==now->tm_year)
	{
		if(thang<now->tm_mon)
			return true;
		if(thang==now->tm_mon)
		{
			if(ngay<now->tm_mday)
				return true;
		}	
	}
	return false;
}

void menu1() {
	gotoxy(4,1);
	cout << "Esc: Thoat";
	gotoxy(4,2);
	cout << "Tab: Them tai san";
	gotoxy(4,3);
	cout << "1: Hien thi tai san";
	gotoxy(4,4);
	cout << "2: Cho thue tai san";
	gotoxy(4,5);
	cout << "3: Tra tai san";
	gotoxy(4,6);
	cout << "4: Xoa tai san";
	gotoxy(4,7);
	cout << "5: Cap nhat tai san";
	gotoxy(4,8);
	cout << "Chon chuc nang  ";
}

void tai_san_box(int dem) { //Ham ve khung hien thi danh sach
	boxw=dem;
	gotoxy(boxx, boxy); cout << char(201);
	for( i = 1; i < boxs-4 ; i++) 
	{
		if(i==22||i==46||i==62||i==76||i==86)
			cout<<char(201);
		cout << char(205);
	}
	cout << char(187);
	gotoxy(boxx, boxy + 1); cout << char(186) << " Ten tai san";
	gotoxy(23, boxy + 1);cout << char(186) << " Nguoi thue";
	gotoxy(48, boxy + 1); cout << char(186) << " Dien thoai";
	gotoxy(65, boxy + 1); cout << char(186) << " Tinh trang";
	gotoxy(80, boxy + 1); cout << char(186) << " So ngay";
	gotoxy(91, boxy + 1); cout << char(186) << " Ngay thue";
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	gotoxy(boxx, boxy + 2); cout << char(204);
	for( i = 1; i < boxs -4; i++) {
		cout << char(205);
		if(i==21||i==45||i==61||i==75||i==85)
			cout<<char(206);
	}
	cout << char(185);
	int n;
	for(int i = boxy + 3; i < boxy + 3 + boxw; i++) {
			n=186;
			gotoxy(boxx, i);
			cout << char(n);
			gotoxy(boxx + boxs + 1, i);
			cout << char(n);
			gotoxy(23, i);
			cout << char(n);
			gotoxy(48, i);
			cout << char(n);
			gotoxy(65, i);
			cout << char(n);
			gotoxy(80, i);
			cout << char(n);
			gotoxy(91, i);
			cout << char(n);
	}
	gotoxy(boxx, boxy + boxw + 3); cout << char(200);
	for( i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188);
}

void tai_san_chua_thue_box(int dem) { 
	boxw=dem;
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < 22 ; i++) 
	{
		if(i==22)
			cout<<char(201);
		cout << char(205);
	}
	cout << char(187);
	gotoxy(boxx, boxy + 1); cout << char(186) << " Ten tai san";
	gotoxy(23, boxy + 1); cout << char(186);
	gotoxy(boxx, boxy + 2); cout << char(204);
	for( i = 1; i < 22 ; i++) {
		cout << char(205);
		if(i==21||i==45||i==61||i==75||i==85)
			cout<<char(206);
	}
	int n;
	for( i = boxy + 3; i < boxy + 3 + boxw; i++) {
			n=186;
			gotoxy(boxx, i);
			cout << char(n);
			gotoxy(23, i);
			cout << char(n);
	}
	gotoxy(boxx, boxy + boxw + 3); cout << char(200);
	for( i = 1; i < 22; i++) 
		cout << char(205);
	cout << char(188);
}
void menu3() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
}
void menu2() {
	gotoxy(4,3);
	cout << "N: Khong them tai san";
	gotoxy(4,2);
	cout << "Y: Xac nhan them tai san";
}
void menu4() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
	gotoxy(4,3);
	cout << "1: Hien thi toan bo tai san";
	gotoxy(4,4);
	cout << "2: Hien thi tai san dang duoc thue";
	gotoxy(4,5);
	cout << "3: Hien thi tai san da qua han";
	gotoxy(4,6);
	cout << "4: Hien thi tai san chua co nguoi thue";
	gotoxy(4,8);
	cout << "Chon chuc nang  ";
}
void menu5() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
	gotoxy(4,3);
	cout << "Nhap tai san can thue: ";
	gotoxy(4,6);
	cout << "Danh sach tai san co the thue: ";
}
void menu6() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
	gotoxy(4,3);
	cout << "Nhap tai san can tra: ";
	gotoxy(4,6);
	cout << "Danh sach tai san dang duoc thue: ";
}
void menu7() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
	gotoxy(4,3);
	cout << "Nhap ten tai san can xoa: ";
	gotoxy(4,6);
	cout << "Danh sach tai san: ";
}
void menu8() {
	gotoxy(4,2);
	cout << "Esc: Quay lai";
	gotoxy(4,3);
	cout << "Nhap ten tai san can cap nhat: ";
	gotoxy(4,6);
	cout << "Danh sach tai san: ";
}
void addtaisanbox() {// them tu vao khung
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	gotoxy(boxx, boxy + 1); cout << char(186) << "       Ten tai san:";
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	gotoxy(boxx, boxy + 2); cout << char(186) << "       Nguoi thue:";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	gotoxy(boxx, boxy + 3); cout << char(186) << "       Dien thoai:";
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	gotoxy(boxx, boxy + 4); cout << char(186) << "       Tinh trang:";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	gotoxy(boxx, boxy + 5); cout << char(186) << "       So ngay thue:";
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	gotoxy(boxx, boxy + 6); cout << char(186) << "       Ngay thue(dd/MM/YYYY):";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	gotoxy(boxx, boxy + 7); cout << char(200);
	for( i = 1; i < boxs + 1; i++) cout << char(205);
		cout << char(188);
}

bool kiem_tra_ngay(string a)
{
	int ngay=0,thang=0,nam=0;
	switch(thang)
	{
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			if(ngay<1&&ngay>31)
				return false;
		break;
		case 2:
			if(ngay<=0)
				return false;
			if(nam%4==0&&nam%100!=0||nam%400==0)
			{
				if(ngay>29)
					return false;
			}
			else if(ngay>28)
				return false;
		break;
		case 4:case 6:case 9:case 11:
			if(ngay>30&&ngay<1)
				return false;
		break;
		default:
			return false;		
	}
	return true;
}
void add_last(list &l,tai_san *newnode)
{
	if(l.first==NULL)
		l.first=l.last=newnode;
	else
	{
		l.last->link=newnode;
		l.last=newnode;
	}
}
void add_tai_san(list &l,int &dem1) {// them tu
	system("cls");
	char a1;
	int keyhit=0,k=1,a=23;
	short dem;
	tai_san *b;
	b=new tai_san;
	string text,f[10];
	gotoxy(boxx + 1, boxy +1);
	cout<<"Nhap ten tai san: ";
	menu2();
//	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<dem1;
	gotoxy(boxx + a, boxy + k++);
	getline(std::cin,text);		
	f[0]=text;
	f[1]="";
	f[2]="";
	f[3]="";
	f[4]="0";
	f[5]="";
	cout<<"Xac nhan them: ";
	while(keyhit!=110&&keyhit!=121)
		keyhit=getch();
	if(keyhit==121)
	{
		add_last(l,getnode(f[0],f[1],f[2],f[3],(int)f[4][0]-48,f[5]));
		dem1++;
	}
	updated=true;
	return;
	
}

int dem_dang_thue(list l)
{
	int i=0;
	tai_san *p=l.first;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang==s)
			i++;
		p=p->link;
	}
	return i;
}
int dem_chua_thue(list l)
{
	int i=0;
	tai_san *p=l.first;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang!=s)
			i++;
		p=p->link;
	}
	return i;
}
int dem_qua_han(list l)
{
	int i=0;
	tai_san *p=l.first;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang==s&&qua_han(p->ngay_thue,p->so_ngay_thue))
			i++;
		p=p->link;
	}
	return i;
}
void print(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	while(p!=NULL)
	{
		gotoxy(boxx+1, boxy +1+i++); cout <<" "<<p->ten_tai_san;
		if(p->nguoi_thue!=""||p->dien_thoai!=""||p->tinh_trang!=""||p->so_ngay_thue!=0||p->ngay_thue!="")
		{
			gotoxy(24, boxy +i ); cout <<" "<<p->nguoi_thue;
			gotoxy(48+1, boxy +i); cout <<" "<<p->dien_thoai;
			gotoxy(65+1, boxy +i); cout <<" "<<p->tinh_trang;
			gotoxy(80+1, boxy +i); cout <<" "<<p->so_ngay_thue;
			gotoxy(91+1, boxy +i); cout <<" "<<p->ngay_thue;
		}
		cout<<endl;
		p=p->link;	
	}
}

void print_dang_thue(list l)
{
	tai_san *p;
	p=l.first;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang==s)
		{
			gotoxy(boxx+1, boxy +1+i++); cout <<" "<<p->ten_tai_san;
			gotoxy(24, boxy +i ); cout <<" "<<p->nguoi_thue;
			gotoxy(48+1, boxy +i); cout <<" "<<p->dien_thoai;
			gotoxy(65+1, boxy +i); cout <<" "<<p->tinh_trang;
			gotoxy(80+1, boxy +i); cout <<" "<<p->so_ngay_thue;
			gotoxy(91+1, boxy +i); cout <<" "<<p->ngay_thue<<endl;
		}
		p=p->link;
	}
	
}

void print_qua_han(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang==s&&qua_han(p->ngay_thue,p->so_ngay_thue))
		{
			gotoxy(boxx+1, boxy +1+i++); cout <<" "<<p->ten_tai_san;
			gotoxy(24, boxy +i ); cout <<" "<<p->nguoi_thue;
			gotoxy(48+1, boxy +i); cout <<" "<<p->dien_thoai;
			gotoxy(65+1, boxy +i); cout <<" "<<p->tinh_trang;
			gotoxy(80+1, boxy +i); cout <<" "<<p->so_ngay_thue;
			gotoxy(91+1, boxy +i); cout <<" "<<p->ngay_thue<<endl;
		}
		p=p->link;
	}
	
}
void print_da_tra(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang!=s)
		{
			gotoxy(boxx+1, boxy +1+i++); cout <<" "<<p->ten_tai_san;
			gotoxy(24, boxy +i ); cout <<" "<<p->nguoi_thue;
			gotoxy(48+1, boxy +i); cout <<" "<<p->dien_thoai;
			gotoxy(65+1, boxy +i); cout <<" "<<p->tinh_trang;
			gotoxy(80+1, boxy +i); cout <<" "<<p->so_ngay_thue;
			gotoxy(91+1, boxy +i); cout <<" "<<p->ngay_thue<<endl;
		}
		p=p->link;
	}
	
}
void print_ten_tai_san(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		gotoxy(boxx+1, boxy +1+i++); 
		cout <<" "<<p->ten_tai_san<<endl;	
		p=p->link;
	}
	
}
void print_ten_tai_san_chua_thue(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang!=s)
		{
			gotoxy(boxx+1, boxy +1+i++); 
			cout <<" "<<p->ten_tai_san<<endl;
		}
		p=p->link;
	}
	
}
void print_ten_tai_san_dang_duoc_thue(list l)
{
	tai_san *p;
	p=l.first;
	cout<<endl;
	int i=2;
	string s="Dang thue";
	while(p!=NULL)
	{
		if(p->tinh_trang==s)
		{
			gotoxy(boxx+1, boxy +1+i++); 
			cout <<" "<<p->ten_tai_san<<endl;
		}
		p=p->link;
	}
	
}
void hien_thi_toan_bo(list l,int dem1)
{
	menu3();
	tai_san_box(dem1);
	print(l);
	return;
}

void hien_thi_dang_thue(list l,int dem1)
{
	system("cls");
	menu3();
	tai_san_box(dem_dang_thue(l));
	print_dang_thue(l);
}
void hien_thi_qua_han(list l,int dem1)
{
	system("cls");
	menu3();
	tai_san_box(dem_qua_han(l));
	print_qua_han(l);
}

void hien_thi_chua_thue(list l,int dem1)
{
	system("cls");
	menu3();
	tai_san_box(dem1);
	print_da_tra(l);
}
tai_san* kiem_tra_tai_san(list l,string a)
{
	tai_san *p;
	string a1="Dang thue";
	p=l.first;
	
	
	while(p!=NULL)
	{
		char a2[1000]="",a3[1000]="";
		for(int i=0;i<a.length();i++)
		{
			a2[i]=a[i];
			a3[i]=p->ten_tai_san[i];
		}
		if(stricmp(a2,a3)==0&&a1!=p->tinh_trang&&a.size()==p->ten_tai_san.size())
			return p;
		p=p->link;
	}
	return NULL;
}
tai_san* kiem_tra_tai_san_can_tra(list l,string a)
{
	tai_san *p;
	string a1="Dang thue";
	p=l.first;
	
	
	while(p!=NULL)
	{
		char a2[1000]="",a3[1000]="";
		for(int i=0;i<a.length();i++)
		{
			a2[i]=a[i];
			a3[i]=p->ten_tai_san[i];
		}
		if(stricmp(a2,a3)==0&&a1==p->tinh_trang&&a.size()==p->ten_tai_san.size())
			return p;
		p=p->link;
	}
	return NULL;
}
tai_san* kiem_tra_tai_san_can_xoa(list l,string a)
{
	tai_san *p;
	p=l.first;
	
	
	while(p!=NULL)
	{
		char a2[1000]="",a3[1000]="";
		for(int i=0;i<a.length();i++)
		{
			a2[i]=a[i];
			a3[i]=p->ten_tai_san[i];
		}
		if(stricmp(a2,a3)==0&&a.size()==p->ten_tai_san.size())
			return p;
		p=p->link;
	}
	return NULL;
}
void cho_thue_tai_san(list &l,int &keyhit,int dem1)
{
	tai_san *p;
	int keyhit1 = 0,i=0,i1;
	string a,bb[10];
	while(keyhit1!=27)
	{
		system("cls");
		menu5();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san_chua_thue(l);
		gotoxy(35,8);
		fflush(stdin);
		do 
		{
			system("cls");
			menu5();
			keyhit1=0;
			tai_san_chua_thue_box(dem1);
			print_ten_tai_san_chua_thue(l);
			if(i!=0)
			{
				gotoxy(4,4);
				cout<<"Nhap sai ten tai san, khong ton tai hoac tai san da duoc thue. Moi nhap lai.";
			}
			gotoxy(35,3);
			fflush(stdin);
			getline(cin,a);
			p=kiem_tra_tai_san(l,a);
			i++;
		}while(p==NULL);
		system("cls");
		menu5();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san_chua_thue(l);
		gotoxy(35,3);
		cout<<a<<endl;
		cout<<"    Xac nhan thue(y: dong y,n: huy): ";
		i=0;
		while(i!=121&&i!=110)
			i=getch();
		if(i==110)
		{
			keyhit=0;
			return;
		}
		else
		{
			int aa;
			do
			{
				system("cls");
				addtaisanbox();
				fflush(stdin);
				gotoxy(25,13);
				cout<<p->ten_tai_san;
				gotoxy(25,14);fflush(stdin);
				getline(cin,bb[0]);
				gotoxy(25,15);fflush(stdin);
				getline(cin,bb[1]);
				gotoxy(25,16);fflush(stdin);
				cout<<"Dang thue";
				gotoxy(25,17);fflush(stdin);
				cin>>i1;
				gotoxy(35,18);fflush(stdin);
				getline(cin,bb[3]);
				gotoxy(8,21);
				cout<<"y: Xac nhan thong tin\n\tn: Nhap lai\n\tEsc: Thoat\n\tNhap lua chon: ";
				aa=0;
				while(aa!=110&&aa!=121&&aa!=27)
					aa=getch();
				if(aa==27)
				{
					keyhit1=27;
					return;
				}
			}while(aa!=121);
			p->nguoi_thue=bb[0];
			p->dien_thoai=bb[1];
			p->tinh_trang="Dang thue";
			p->so_ngay_thue=i1;
			p->ngay_thue=bb[3];
			
			cout<<"\nThem thanh cong.\nBam phim bat ki de quay ve Menu chinh.";
			aa=getch();
			keyhit1=27;
			updated=true;
		}
		
	}
	return;
}
void cho_tra_tai_san(list &l,int &keyhit,int dem1)
{
	tai_san *p;
	int keyhit1 = 0,i=0,i1;
	string a,bb[10];
	while(keyhit1!=27)
	{
		system("cls");
		menu6();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san_dang_duoc_thue(l);
		gotoxy(35,8);
		fflush(stdin);
		do 
		{
			system("cls");
			menu6();
			keyhit1=0;
			tai_san_chua_thue_box(dem1);
			print_ten_tai_san_dang_duoc_thue(l);
			if(i!=0)
			{
				gotoxy(4,4);
				cout<<"Nhap sai ten tai san, khong ton tai hoac tai san chua duoc thue. Moi nhap lai.";
			}
			gotoxy(35,3);
			fflush(stdin);
			getline(cin,a);
			p=kiem_tra_tai_san_can_tra(l,a);
			i++;
		}while(p==NULL);
		system("cls");
		menu5();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san_dang_duoc_thue(l);
		gotoxy(35,3);
		cout<<a<<endl;
		cout<<"    Xac nhan tra(y: dong y,n: huy): ";
		i=0;
		while(i!=121&&i!=110)
			i=getch();
		if(i==110)
		{
			keyhit=0;
			return;
		}
		else
		{
			int aa;
			do
			{
				system("cls");
				addtaisanbox();
				fflush(stdin);
				gotoxy(25,13);
				cout<<p->ten_tai_san;
				gotoxy(25,14);fflush(stdin);
				cout<<p->nguoi_thue;
				gotoxy(25,15);fflush(stdin);
				cout<<p->dien_thoai;
				gotoxy(25,16);fflush(stdin);
				cout<<p->tinh_trang;
				gotoxy(25,17);fflush(stdin);
				cout<<p->so_ngay_thue;
				gotoxy(35,18);fflush(stdin);
				cout<<p->ngay_thue;
				gotoxy(8,21);
				cout<<"y: Xac nhan tra\n\tEsc: Thoat\n\tNhap lua chon: ";
				aa=0;
				while(aa!=121&&aa!=27)
					aa=getch();
				if(aa==27)
				{
					keyhit1=27;
					return;
				}
			}while(aa!=121);
			p->tinh_trang="Da tra";
			
			cout<<"\nTra thanh cong.\nBam phim bat ki de quay ve Menu chinh.";
			aa=getch();
			keyhit1=27;
			updated=true;
		}
		
	}
	return;
}

void cap_nhat_tai_san(list &l,int &keyhit,int dem1)
{
	tai_san *p;
	int keyhit1 = 0,i=0,i1;
	string a,bb[10];
	while(keyhit1!=27)
	{
		system("cls");
		menu8();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		hien_thi_toan_bo(l,dem1);
		gotoxy(35,8);
		fflush(stdin);
		do 
		{
			system("cls");
			menu8();
			keyhit1=0;
			tai_san_chua_thue_box(dem1);
			hien_thi_toan_bo(l,dem1);
			if(i!=0)
			{
				gotoxy(4,4);
				cout<<"Nhap sai ten tai san hoac khong ton tai. Moi nhap lai.";
			}
			gotoxy(35,3);
			fflush(stdin);
			getline(cin,a);
			p=kiem_tra_tai_san(l,a);
			i++;
		}while(p==NULL);
		system("cls");
		menu8();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		hien_thi_toan_bo(l,dem1);
		gotoxy(35,3);
		cout<<a<<endl;
		cout<<"    Xac nhan cap nhat thong tin nguoi thue(y: dong y,n: huy): ";
		i=0;
		while(i!=121&&i!=110)
			i=getch();
		if(i==110)
		{
			keyhit=0;
			return;
		}
		else
		{
			int aa;
			do
			{
				system("cls");
				addtaisanbox();
				fflush(stdin);
				gotoxy(25,13);
				cout<<p->ten_tai_san;
				gotoxy(25,14);fflush(stdin);
				cout<<p->nguoi_thue;
				gotoxy(25,16);fflush(stdin);
				cout<<p->tinh_trang;
				gotoxy(25,15);fflush(stdin);
				getline(cin,bb[1]);
				gotoxy(25,17);fflush(stdin);
				cin>>i1;
				gotoxy(35,18);fflush(stdin);
				getline(cin,bb[3]);
				gotoxy(8,21);
				cout<<"y: Xac nhan thong tin\n\tn: Nhap lai\n\tEsc: Thoat\n\tNhap lua chon: ";
				aa=0;
				while(aa!=110&&aa!=121&&aa!=27)
					aa=getch();
				if(aa==27)
				{
					keyhit1=27;
					return;
				}
			}while(aa!=121);
			p->dien_thoai=bb[1];
			p->so_ngay_thue=i1;
			p->ngay_thue=bb[3];
			cout<<"\nThem thanh cong.\nBam phim bat ki de quay ve Menu chinh.";
			aa=getch();
			keyhit1=27;
			updated=true;
		}
	}
	return;
}

void menu_hien_thi(list &l,int &keyhit,int dem1)
{
	int keyhit1 = 0;
	while(keyhit1!=27)
	{
		system("cls");
		menu4();
		fflush(stdin);
		keyhit1=0;
		while(keyhit1!=27&&keyhit1!=49&&keyhit1!=50&&keyhit1!=51&&keyhit1!=52)
			keyhit1=getch();
		if(keyhit1==27)
		{
			keyhit=0;
			return;
		}
		else if(keyhit1==49)
		{
			keyhit1=0; 
			system("cls");
			hien_thi_toan_bo(l,dem1);
			while(keyhit1!=27)
				keyhit1=getch();
			if(keyhit1==27)
			{
				keyhit1=0;
				continue;
			}			
		}
		else if(keyhit1==50)
		{
			keyhit1=0; 
			hien_thi_dang_thue(l,dem_dang_thue(l));
			while(keyhit1!=27)
				keyhit1=getch();
			if(keyhit1==27)
			{
				keyhit1=0;
				continue;
			}		
		}
		else if(keyhit1==51)
		{
			keyhit1=0; 
			hien_thi_qua_han(l,dem_qua_han(l));
			while(keyhit1!=27)
				keyhit1=getch();
			if(keyhit1==27)
			{
				keyhit1=0;
				continue;
			}				
		}
		else if(keyhit1==52)
		{
			keyhit1=0; 
			hien_thi_chua_thue(l,dem_chua_thue(l));
			while(keyhit1!=27)
					keyhit1=getch();
			if(keyhit1==27)
			{
				keyhit1=0;
				continue;
			}	
		}
	}
	return;
}
int removeHead (list &l){
	if (l.first == NULL) 
			return 0;
	tai_san* p=l.first;
	l.first = p->link;
	if (l.first == NULL)  l.last=NULL; //N?u danh sách r?ng
	delete p;
	return 1;
}

int  removeAfter (list &l, tai_san	* q ){
	if (q !=NULL && q->link !=NULL)	{
		tai_san*   p = q->link;
		q->link = p->link;
		if  (p==l.last)	 l.last = q;
		delete p;
		return 1;
	}
	else return 0;
}

void xoa(list &l,string a)
{	
	tai_san *p=l.first;
	tai_san *q=NULL;
	while  (p != NULL) 
	{ 
		if  (p->ten_tai_san == a) break; 
		q = p;    
		p = p->link; 
	} 
	if (p == NULL)  {return ;}
	else if (q == NULL) 
		removeHead(l);
		else 
			removeAfter(l,q);
} 
void xoa_tai_san(list &l,int &keyhit,int &dem1)
{
	tai_san *p;
	int keyhit1 = 0,i=0,i1;
	string a,bb[10];
	while(keyhit1!=27)
	{
		system("cls");
		menu7();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san(l);
		gotoxy(35,8);
		fflush(stdin);
		do 
		{
			system("cls");
			menu7();
			keyhit1=0;
			tai_san_chua_thue_box(dem1);
			print_ten_tai_san(l);
			if(i!=0)
			{
				gotoxy(4,4);
				cout<<"Nhap sai ten tai san hoac khong ton tai. Moi nhap lai.";
			}
			gotoxy(35,3);
			fflush(stdin);
			getline(cin,a);
			p=kiem_tra_tai_san_can_xoa(l,a);
			i++;
		}while(p==NULL);
		system("cls");
		menu7();
		keyhit1=0;
		tai_san_chua_thue_box(dem1);
		print_ten_tai_san(l);
		gotoxy(35,3);
		cout<<a<<endl;
		cout<<"    Xac nhan xoa(y: dong y,n: huy): ";
		i=0;
		while(i!=121&&i!=110)
			i=getch();
		if(i==110)
		{
			keyhit=0;
			return;
		}
		else
		{
			int aa;
			xoa(l,p->ten_tai_san);
			dem1--;
			cout<<"\n\tTra thanh cong.\n\tBam phim bat ki de quay ve Menu chinh.";
			aa=getch();
			keyhit1=27;
			updated=true;
		}
		
	}
	return;
}

void searchbox(list &l, tai_san *t,int &dem1) { //Ham khung nhap tu khoa va ket qua tim kiem
	bool changed = false;
	string intext = "";
	int keyhit = 0;
	while(keyhit != 27) {
		system("cls");
		menu1();
		keyhit=getch();
		if(keyhit==27)       
    		break;
		if(keyhit==49)		
		{
			menu_hien_thi( l,keyhit,dem1);
		} 
		if(keyhit==9)		
		{
			add_tai_san(l,dem1);
			keyhit=0;
			continue;
		} 
  		if(keyhit==50)		
  		{
  			tai_san *a=NULL;
			cho_thue_tai_san(l,keyhit,dem_chua_thue(l));
			keyhit=0;
			continue;  	
  		}
  		if(keyhit==51)		
  		{
  			tai_san *a=NULL;
			cho_tra_tai_san(l,keyhit,dem_dang_thue(l));
			keyhit=0;
			continue;  	
  		}
  		if(keyhit==52)		
  		{
  			tai_san *a=NULL;
			xoa_tai_san(l,keyhit,dem1);
			keyhit=0;
			continue;  	
  		}
		if(keyhit==53)		
		{
			cap_nhat_tai_san(l,keyhit,dem1);
			keyhit=0;
			continue;
		} 
    }
}

void tachchuoi(string line, tai_san *&newtaisan)
{
	int i=0;
	string tach="";
	while(line[i]!='-')
	{
		tach+=line[i];
		i++;
	}
	newtaisan->ten_tai_san=tach;
	i++;tach="";
	while(line[i]!='-')
	{
		tach+=line[i];
		i++;
	}
	newtaisan->nguoi_thue=tach;
	i++;tach="";
	while(line[i]!='-')
	{
		tach+=line[i];
		i++;
	}
	newtaisan->dien_thoai=tach;
	i++;tach="";
	while(line[i]!='-')
	{
		tach+=line[i];
		i++;
	}
	newtaisan->tinh_trang=tach;
	i++;tach="";
	long a=0,i1=0;
	while(line[i]!='-')
	{
		int b=(int)line[i]-48;
		a=a*10+b;
		i++;
	}
	newtaisan->so_ngay_thue=a;
	i++;tach="";
	while(line[i]!='-')
	{
		tach+=line[i];
		i++;
	}
	newtaisan->ngay_thue=tach;
}
void import_tai_san(list &l,string line)
{
		if((int)line[0]!=32)
		{
			tai_san *newtaisan ;
			newtaisan= new tai_san();
			tachchuoi(line, newtaisan);
			newtaisan->link = NULL;
			add_last(l, newtaisan);
		}
}
void docfile(list &l,int &dem)
{
	ifstream fi("taisan.txt");
	string line;
	if(fi.is_open())
	{
		while(getline(fi,line))
		{	
			dem++;
			import_tai_san(l,line);
		}	
		fi.close();
	}
}
void ghifile(list &l) { //Ghi file
	ofstream fo("taisan.txt");
	if(fo.is_open()) {
		tai_san *p;
		p=l.first;
		while(p!=NULL)
		{
			fo<<p->ten_tai_san<<"-"<<p->nguoi_thue<<"-"<<p->dien_thoai<<"-"
			<<p->tinh_trang<<"-"<<p->so_ngay_thue<<"-"<<p->ngay_thue<<"--\n";
			p=p->link;
		}
		fo.close();
	}
}

int main()
{
	string ten_tai_san, nguoi_thue, dien_thoai, tinh_trang;
	int so_ngay_thue;
	string ngay_thue;
	tai_san *a=new tai_san;
	int dem=0,aa;
	list l;
	Init(l);
	string s="Dang thue";
	docfile(l,dem);
	menu1();
	searchbox(l,a,dem);
	cout<<endl;
	if(updated)
		ghifile(l);
}