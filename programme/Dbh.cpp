#include<bits/stdc++.h>
#include<ctime>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<cstdio>
#include<time.h>
#include "Dbh.h"
//#include <Eigen/Dense>
//#include <Eigen/Core>
#define MAXN 260
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void Dbh::clearp(HANDLE hConsole){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   SMALL_RECT scrollRect;
   COORD scrollTarget;
   CHAR_INFO fill;
   if (!GetConsoleScreenBufferInfo(hConsole, &csbi))return;
   scrollRect.Left=0;
   scrollRect.Top=0;
   scrollRect.Right=csbi.dwSize.X;
   scrollRect.Bottom=csbi.dwSize.Y;
   scrollTarget.X=0;
   scrollTarget.Y=(SHORT)(0-csbi.dwSize.Y);
   fill.Char.UnicodeChar=TEXT(' ');
   fill.Attributes=csbi.wAttributes;
   ScrollConsoleScreenBuffer(hConsole,&scrollRect,NULL,scrollTarget,&fill);
   csbi.dwCursorPosition.X=0;
   csbi.dwCursorPosition.Y=0;
   SetConsoleCursorPosition(hConsole,csbi.dwCursorPosition);
}
int Dbh::contact_button(int cx,int sx,int fy,WORD wttu,WORD wttd){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	cur=0;
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
		//Sleep(1);
		if(sig==false){
			short x =cx,y=fy;
			printf("\x1b[%hd;%hdH", y+1, x+1);
			for(int i=cx;i<=sx;i++)cout<<' ';
		}
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
        if(pos.X>=cx&&pos.X<=sx&&pos.Y==fy){
        	HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD getWrittenCount = 0;
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, wttu, sx-cx, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)){ 
				if(cur==1)cur=0;
				else if(cur==0)cur=1;
				//HANDLE hStdoutw;hStdoutw=GetStdHandle(STD_OUTPUT_HANDLE);clearp(hStdoutw);
				//break;
			}
		}
		else{
			HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD getWrittenCount = 0;
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, wttd, sx-cx, writtenPos, &getWrittenCount);
		} 
	} }
int Dbh::text_box(int cx,int fy,int txtin,int length){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=length;i++)cout<<"¨€";
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=length-1-floor(log10(txtin));i++)cout<<" ";
	cout<<txtin;
}
int Dbh::write_box(int cx,int fy,string txton,int length,WORD wttu,WORD wttd){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x+1);
	for(int i=1;i<=length;i++)cout<<"¨€";
	printf("\x1b[%hd;%hdH", y + 1, x+1);
	const char *der=txton.substr(0, length-2).c_str();
	const char *derd=txton.c_str();
	if(txton.size()>length-1){
		printf("%s...",der);
		Dbh dbh;
		#pragma omp parallel for
		for(int i=1;i<=2;i++){
			if(i==1)dbh.contact_button(cx,cx+length+2,fy,wttu,wttd);
			else{
				int old=dbh.cur;
				while(1){
					Sleep(2);
					if(dbh.cur!=old){
						if(dbh.cur==1){
							printf("\x1b[%hd;%hdH", y + 1, x+1);printf("%s",derd);
						}
						else {
							const char *dert=txton.substr(0, length-2).c_str();
							printf("\x1b[%hd;%hdH", y + 1, x+1);printf("%s...",dert);
							//printf("\x1b[%hd;%hdH", y + 1, x+length);
							for(int i=1;i<=txton.size()-length+2;i++)cout<<" "; 
						}
						old=dbh.cur;
					}
					
				}
			}
		}
	}
	else {
		for(int i=1;i<=length-txton.size();i++)cout<<' ';
		printf("%s",derd);
	}
}
int Dbh::color_box(int cx,int fy,int r,int g,int b){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	wprintf(L"\x1b[38;2;%d;%d;%dm",r,g,b);
	cur=1000000*r+1000*g+b;
	cout<<"¨ˆ¨ˆ";
}
int Dbh::input_box(int cx,int fy,int areat,int r_ox,int g_ox,int b_ox){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	wprintf(L"\x1b[38;2;%d;%d;%dm",r_ox,g_ox,b_ox);
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=areat;i++)cout<<"¨€";
	printf("\x1b[%hd;%hdH", y + 1, x);
	cin>>cur; 
	return cur;
}
int Dbh::adjustment_button(int cx,int fy,int difnumb,WORD wttu,WORD wttd,int r_ox,int g_ox,int b_ox,char lsig,char rsig,int width){
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	wprintf(L"\x1b[38;2;%d;%d;%dm",r_ox,g_ox,b_ox);
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x+1);
	cout<<lsig;text_box(cx+2,fy,difnumb,width);
	//for(int i=1;i<=width-2;i++)cout<<" ";
	cout<<rsig;
	cur=difnumb;
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
		if(sig==false){
			printf("\x1b[%hd;%hdH", y + 1, x+1);
			for(int i=1;i<=width+2;i++)cout<<' ';
			return 0;
		}
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
        HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD getWrittenCount = 0;
		COORD writtenPos0={cx,fy};
		FillConsoleOutputAttribute(outputHandle, wttu, 1, writtenPos0, &getWrittenCount);
		COORD writtenPos1={cx+width+1,fy};
		FillConsoleOutputAttribute(outputHandle, wttu, 1, writtenPos1, &getWrittenCount);
		COORD writtenPos2={cx+1,fy};
		FillConsoleOutputAttribute(outputHandle, wttu,width, writtenPos2, &getWrittenCount);
		if(pos.X>=cx&&pos.X<=cx+1&&pos.Y==fy){
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, wttd, 1, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				cur--;text_box(cx+2,fy,cur,width);
			}
		}
		else if(pos.X>=cx+width&&pos.X<=cx+width+1&&pos.Y==fy){
			COORD writtenPos={cx+width+1,fy};
			FillConsoleOutputAttribute(outputHandle, wttd, 1, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				cur++;text_box(cx+2,fy,cur,width);
			}
		}
		else if(pos.X>=cx+1&&pos.X<=cx+width+1&&pos.Y==fy){
			COORD writtenPos={cx+1,fy};
			//WORD wtt=0xB0; 
			FillConsoleOutputAttribute(outputHandle, wttd, width, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				cur=input_box(cx+2,fy,width);text_box(cx+2,fy,cur,width);
			}
		}
	} }
int Dbh::slider_bar(int cx,int fy,int difnumb,WORD wttu,WORD wttd,int r_ox,int g_ox,int b_ox){
    if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
	cur=difnumb;
	wprintf(L"\x1b[38;2;%d;%d;%dm", r_ox, g_ox, b_ox);
	printf("\033[45;0f"); 
	short x = cx, y = fy;
	printf("\x1b[%hd;%hdH",y,x);
	printf("\033(0lqqqqqqqqqqwqqqqqk");
	printf("\x1b[%hd;%hdH",y+1,x);
	printf("x\033(B          \033(0x     \033(0x");
	printf("\x1b[%hd;%hdH",y+2,x);
	printf("\033(0mqqqqqqqqqqvqqqqqj");
	printf("\033(B\033[0m");
	text_box(cx+12,fy,cur,5);
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
    HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD getWrittenCount = 0;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
		if(pos.X>=cx&&pos.X<=cx+9&&pos.Y==fy){
			COORD writtenPos0={cx,fy};
			FillConsoleOutputAttribute(outputHandle, wttd, 10, writtenPos0, &getWrittenCount);
			COORD writtenPos1={cx+cur-1,fy};
			FillConsoleOutputAttribute(outputHandle, wttu, 1, writtenPos1, &getWrittenCount);
			//if(KEY_DOWN(37)||KEY_DOWN(40))cur--;
			//if(KEY_DOWN(38)||KEY_DOWN(39))cur++;
        	if(KEY_DOWN(VK_LBUTTON)) { 
				COORD writtenPos2={cx+cur-1,fy};
				FillConsoleOutputAttribute(outputHandle, wttd, 1, writtenPos2, &getWrittenCount);
				COORD writtenPos={pos.X,fy};
				FillConsoleOutputAttribute(outputHandle, wttu, 1, writtenPos, &getWrittenCount);
				cur=(pos.X-cx+1);
				text_box(cx+12,fy,cur,5);
			}
		}
	} }

