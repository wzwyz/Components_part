#include<bits/stdc++.h>
#include<ctime>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<cstdio>
#include<time.h>
//#include <Eigen/Dense>
//#include <Eigen/Core>
#define MAXN 260
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void clearp(HANDLE hConsole)
{
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
bool bumutu(int cx,int sx,int fy){
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
        if(pos.X>=cx&&pos.X<=sx&&pos.Y==fy){
        	HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD getWrittenCount = 0;
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, 0xB0, sx-cx, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				return true;
				//HANDLE hStdoutw;hStdoutw=GetStdHandle(STD_OUTPUT_HANDLE);clearp(hStdoutw);
				//break;
			}
		}
		else{
			HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD getWrittenCount = 0;
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, sx-cx, writtenPos, &getWrittenCount);
		} 
	} 
	return false;
}
int textbox3(int cx,int fy,int txtin,int length){
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=length;i++)cout<<"█";
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=length-1-floor(log10(txtin));i++)cout<<" ";
	//if(txtin!=100)cout<<" ";
	cout<<txtin;
}
int colorbox(int cx,int fy,int r,int g,int b){
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	wprintf(L"\x1b[38;2;%d;%d;%dm",r,g,b);
	cout<<"▓▓";
}
int yzinbox(int cx,int areat,int fy){
	wprintf(L"\x1b[38;2;%d;%d;%dm",173,202,255);
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	for(int i=1;i<=areat;i++)cout<<"█";
	//short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	int a;
	cin>>a; 
	return a;
}
int udinbox(int cx,int fy,int difnumb){
	wprintf(L"\x1b[38;2;%d;%d;%dm",173,17,255);
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x);
	cout<<"↑  ↓"<<endl;
	//for(int i=1;i<=areat;i++)cout<<"█";
	textbox3(cx,fy+1,difnumb,4);int cur=difnumb;
	//short x =cx,y=fy;
	while(1){
		if(bumutu(cx,cx+1,fy)){
			cur++;textbox3(cx,fy+1,cur,4);
		};
		if(bumutu(cx+3,cx+4,fy)){
			cur--;textbox3(cx,fy+1,cur,4);
		};
		if(bumutu(cx,cx+4,fy+1)){
			cur=yzinbox(cx,4,fy+1);
			textbox3(cx,fy+1,cur,4);
		};
	}
}
int updoUI(int cx,int fy,int difnumb){
	//printf("\033[45;37;1m"); // 使用 DEC 特殊图形字符集

	// 绘制区域
	// 为了对齐，第十一行必须打空格，但是在 437 代码页下是不用的
	//short x = cx, y = fy;
	//printf("\x1b[%hd;%hdH",y+1,x+1);
	//cout<<"          ";
	wprintf(L"\x1b[38;2;%d;%d;%dm",173,17,255);
	short x =cx,y=fy;
	printf("\x1b[%hd;%hdH", y + 1, x+1);
	cout<<"↑  ↓"<<endl;
	//short x =cx,y=fy;
	//printf("\x1b[%hd;%hdH", y + 2, x+1);
	//for(int i=1;i<=areat;i++)cout<<"█";
	textbox3(cx+1,fy+1,difnumb,4);int cur=difnumb;
	//printf("\033(0lqqqqqqqqqqqk \n");
	//printf("x\033(B           \033(0x \n");
	//printf("\033(0mqqqqqqqqqqqj ");

	//printf("\033(B\033[0m\n"); // 返回 ASCII 字符集
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
        HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD getWrittenCount = 0;
		COORD writtenPos0={cx,fy};
		FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos0, &getWrittenCount);
		COORD writtenPos1={cx+3,fy};
		FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos1, &getWrittenCount);
		COORD writtenPos2={cx,fy+1};
		FillConsoleOutputAttribute(outputHandle, 0x0B, 4, writtenPos2, &getWrittenCount);
		if(pos.X>=cx&&pos.X<=cx+1&&pos.Y==fy){
        	
			
			//HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			//DWORD getWrittenCount = 0;
			COORD writtenPos={cx,fy};
			FillConsoleOutputAttribute(outputHandle, 0xB0, 1, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				//return pos.X;
				//HANDLE hStdoutw;hStdoutw=GetStdHandle(STD_OUTPUT_HANDLE);clearp(hStdoutw);
				//break;
				cur++;textbox3(cx+1,fy+1,cur,4);
				
			}
		}
		else if(pos.X>=cx+3&&pos.X<=cx+4&&pos.Y==fy){
			COORD writtenPos={cx+3,fy};
			FillConsoleOutputAttribute(outputHandle, 0xB0, 1, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				cur--;textbox3(cx+1,fy+1,cur,4);
			}
		}
		else if(pos.X>=cx&&pos.X<=cx+4&&pos.Y==fy+1){
			COORD writtenPos={cx,fy+1};
			FillConsoleOutputAttribute(outputHandle, 0xB0, 4, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				cur=yzinbox(cx+1,4,fy+1);textbox3(cx+1,fy+1,cur,4);
			}
		}
	} 
	return 0;
}
int sd;
int tyumutu(int cx,int fy){
	//printf("\033[45;37;1m"); // 使用 DEC 特殊图形字符集

	// 绘制区域
	// 为了对齐，第十一行必须打空格，但是在 437 代码页下是不用的
	//short x = cx, y = fy;
	//printf("\x1b[%hd;%hdH",y+1,x+1);
	//cout<<"          ";
	textbox3(cx+15,fy,0,5);
	//printf("\033(0lqqqqqqqqqqqk \n");
	//printf("x\033(B           \033(0x \n");
	//printf("\033(0mqqqqqqqqqqqj ");

	//printf("\033(B\033[0m\n"); // 返回 ASCII 字符集
	HANDLE hInput = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;
    GetConsoleMode( hInput, &mode );
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode( hInput, mode|ENABLE_MOUSE_INPUT );
    INPUT_RECORD record;
    DWORD n;
	for( COORD pos={}; ReadConsoleInput(hInput,&record,1,&n) && n==1; ){
        if(record.EventType!=MOUSE_EVENT)continue;
		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
        pos = pos_new;
		if(pos.X>=cx&&pos.X<=cx+9&&pos.Y==fy){
        	HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD getWrittenCount = 0;
			COORD writtenPos0={cx,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos0, &getWrittenCount);
			COORD writtenPos1={cx+1,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos1, &getWrittenCount);
			COORD writtenPos2={cx+2,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos2, &getWrittenCount);
			COORD writtenPos3={cx+3,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos3, &getWrittenCount);
			COORD writtenPos4={cx+4,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos4, &getWrittenCount);
			COORD writtenPos5={cx+5,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos5, &getWrittenCount);
			COORD writtenPos6={cx+6,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos6, &getWrittenCount);
			COORD writtenPos7={cx+7,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos7, &getWrittenCount);
			COORD writtenPos8={cx+8,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos8, &getWrittenCount);
			COORD writtenPos9={cx+9,fy};
			FillConsoleOutputAttribute(outputHandle, 0x0B, 1, writtenPos9, &getWrittenCount);
			//HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
			//DWORD getWrittenCount = 0;
			COORD writtenPos={pos.X,fy};
			FillConsoleOutputAttribute(outputHandle, 0xB0, 1, writtenPos, &getWrittenCount);
        	if(KEY_DOWN(VK_LBUTTON)) { 
				//return pos.X;
				//HANDLE hStdoutw;hStdoutw=GetStdHandle(STD_OUTPUT_HANDLE);clearp(hStdoutw);
				//break;
				textbox3(cx+15,fy,(pos.X-cx+1)*10,5);
				
			}
		}
	} 
	return 0;
}
int main(){
	//_______________________________________________________________RGB句柄 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
    dwMode |= 0x0004;
    if (!SetConsoleMode(hOut, dwMode))return GetLastError();
    int r,g,b;
    
	//cout<<"\033c"; 
	//_______________________________________________________________键鼠交互句柄 
    //_______________________________________________________________键鼠交互句柄
	wprintf(L"\x1b[38;2;%d;%d;%dm+------+.      +------+       +------+       +------+      .+------+", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|`.    | `.    |\\     |\\      |      |      /|     /|    .' |    .'|", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|  `+--+---+   | +----+-+     +------+     +-+----+ |   +---+--+'  |", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|   |  |   |   | |    | |     |      |     | |    | |   |   |  |   |", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm+---+--+.  |   +-+----+ |     +------+     | +----+-+   |  .+--+---+", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm `. |    `.|    \\|     \\|     |      |     |/     |/    |.'    | .'", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm   `+------+     +------+     +------+     +------+     +------+'", 255, 255,18);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm                             Simpler_3D",106,90,205);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm   .+------+     +------+     +------+     +------+     +------+.",  0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm .' |    .'|    /|     /|     |      |     |\\     |\\    |`.    | `.",  0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm+---+--+'  |   +-+----+ |     +------+     | +----+-+   |  `+--+---+",  0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|   |  |   |   | |    | |     |      |     | |    | |   |   |  |   |",  0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|  ,+--+---+   | +----+-+     +------+     +-+----+ |   +---+--+   |",  0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm|.'    | .'    |/     |/      |      |      \\|     \\|    `. |   `. |", 0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dm+------+'      +------+       +------+       +------+      `+------+", 0,250,170);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dmWhat do you want to do?",255,255,255);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dmyou can click ",255,255,255);
	wprintf(L"\x1b[38;2;%d;%d;%dmadd ",30,255,254);
	wprintf(L"\x1b[38;2;%d;%d;%dmto launch your models in the dock",255,255,255);cout<<endl;
	wprintf(L"\x1b[38;2;%d;%d;%dmor you can click",255,255,255);
	wprintf(L"\x1b[38;2;%d;%d;%dm launch ",30,255,254);
	wprintf(L"\x1b[38;2;%d;%d;%dmto luanch the done ones",255,255,255);
	cout<<endl;wprintf(L"\x1b[38;2;%d;%d;%dm",30,255,254);
	cout<<"  ██████████";
	//if(bumutu(14,18,17))cout<<"fuck!";
	while(1){
		updoUI(2,4,12);
		//tyumutu(2,18);
		//textbox3(20,2,yzinbox(2,10,2),12);
		//tyumutu(2,2);
	}
	return 0;
}
