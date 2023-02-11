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
int main(){
	Dbh dbh,dbh1;
	dbh1.text_box(27,2,7,4);
	#pragma omp parallel for
	for(int i=1;i<=2;i++){
		if(i==1)dbh.slider_bar(3,2,4);
		else{
			int old;
			while(1){
				if(dbh.cur!=old){
					Sleep(2);
					dbh1.text_box(27,2,dbh.cur,4);
					old=dbh.cur;
				}
			}
		}
	}
}
