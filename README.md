<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/wzwyz/Components_part/blob/main/pics/DBHico.png">
  <source media="(prefers-color-scheme: light)" srcset="https://github.com/wzwyz/Components_part/blob/main/pics/DBHico.png">
  <img alt="Shows an illustrated sun in light mode and a moon with stars in dark mode." src="https://github.com/wzwyz/Components_part/blob/main/pics/DBHico.png.png">
</picture>

# Components_part
![c++](https://github.com/wzwyz/Components_part/actions/workflows/c-cpp.yml/badge.svg)
![c++](https://github.com/wzwyz/Components_part/actions/workflows/cmake.yml/badge.svg)
### Easier graphic operating controls for GCC 
It’s written on Devcpp 4.9.2 and can supports all versions below 5.1.1.
## **Here are the available functions in the lib:**
The function supported always formed by subjects below:
```
Dbh::describe_function(int cx,int fy,int difnumb,WORD wttu,WORD wttd,int r_ox,int g_ox,int b_ox,char lsig,char rsig,int width)
```

- `cx` and `fy` represent to the position of the controls on the consoles;
- `difnumb` represents to the very first value of the controls;
- `wttu` and `wttd` represent to the different type of a button when it was clicked or not, and must go as `0x**`;
- `r_ox`, `g_ox` and `b_ox` represent to the color of the controls if there is a need, and the value of it must smaller than 255 while bigger than 0;
- `lsig` and `rsig` represent to the signals between the controls and not every control have one.The value of it must be UTF-8 or mistake will occurred;
- `width` represents to the width of the controls.`cx` and `fy` represent to the position of the controls on the consoles;

## **And the original function is listed as follow:**
```
int adjustment_button(int cx,int fy,int difnumb,WORD wttu=0xB0,WORD wttd=0x0B,int r_ox=173,int g_ox=17,int b_ox=255,char lsig='<',char rsig='>',int width=4);
int slider_bar(int cx,int fy,int difnumb,WORD wttu=0xB0,WORD wttd=0x0B,int r_ox=145,int g_ox=215,int b_ox=37);
int input_box(int cx,int fy,int areat,int r_ox=173,int g_ox=202,int b_ox=255);
int color_box(int cx,int fy,int r,int g,int b);
int text_box(int cx,int fy,int txtin,int length);
int contact_button(int cx,int sx,int fy,WORD wttu=0xB0,WORD wttd=0x0B);
int write_box(int cx,int fy,string txton,int length,WORD wttu=0xB0,WORD wttd=0x0B);
void clearp(HANDLE hConsole=GetStdHandle(STD_INPUT_HANDLE)); 
 ```
 ## **How to add it to GCC compiler linker：**
 1. add libdbh.a `\Dev-Cpp\MinGW64\lib`
 2. add Dbh.h `\Dev-Cpp\MinGW64\include`
 3. add `-lDbh` in the window of DEV-CPP ` Tools->Compiler option->General->add the following command when calling the linker`

## **How to add it to GCC compiler linker：**
add the heading as:
```
#include "Dbh.h"
#include<conio.h>
#include<cstdio>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
```
And use openMP to combine controls as
