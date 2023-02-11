#pragma once
class Dbh{
	public:
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int cur;	
		bool sig=true;
		int adjustment_button(int cx,int fy,int difnumb,WORD wttu=0xB0,WORD wttd=0x0B,int r_ox=173,int g_ox=17,int b_ox=255,char lsig='<',char rsig='>',int width=4);
		int slider_bar(int cx,int fy,int difnumb,WORD wttu=0xB0,WORD wttd=0x0B,int r_ox=145,int g_ox=215,int b_ox=37);
		int input_box(int cx,int fy,int areat,int r_ox=173,int g_ox=202,int b_ox=255);
		int color_box(int cx,int fy,int r,int g,int b);
		int text_box(int cx,int fy,int txtin,int length);
		int contact_button(int cx,int sx,int fy);
		void clearp(HANDLE hConsole=GetStdHandle(STD_INPUT_HANDLE));
}; 
 
