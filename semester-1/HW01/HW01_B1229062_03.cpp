//1.先下標頭檔 
#include <iostream>
#include <cstring> 
using namespace std;

//用new 
//2.輸入要幾個名字
int main(){
	int x; //儲存輸入了幾個名字 
	cout <<"輸入英文名字(包含姓氏+名字)數量(x):";
	cin >>x;
	cin.ignore(); //忽略換行的符號
	
//3.用new動態分配名字陣列，要記得假設名字長度限制 ，避免記憶體浪費 
    char** names=new char*[x];
    for (int i=0;i<x;i++){
    	names[i]=new char[50]; //設定每個名字最多50個字 
	}
	
//4.在輸入的名字後，讀取計算出名字第一個空格(姓氏和名字之間的)前的(姓氏的)最長字數
    int maxFirstSpacePos; //宣告變數 
	maxFirstSpacePos=0; //還沒找到空格的位置，初始化為0
	
    for(int i=0;i<x;i++){
    	cout <<"請輸入第"<< (i+1) <<"個英文名字:";
		cin.getline(names[i],50); //用getline讀整行名字
	char*spacePos=strchr(names[i],' '); //用strchr找空格 
		if(spacePos!=NULL){ //如果找到空格 
		   int firstSpacePos=spacePos-names[i]; //計算空格的位置 
		   if(firstSpacePos > maxFirstSpacePos){ //更新以計算過的最大空格量，後續對齊要用 
		   	 maxFirstSpacePos=firstSpacePos;
		   }	
		} 
	} 
	
//5.輸出對齊後的英文名字
    cout <<"對齊後的英文名字如下:"<< endl;
    for (int i=0;i<x;i++){
    	char*spacePos=strchr(names[i],' '); //尋找空格
		 
    	if(spacePos!=NULL){ //如果找到空格 
    		int firstSpacePos=spacePos-names[i]; //計算空格位置 
    		int padding=maxFirstSpacePos-firstSpacePos; //計算要對齊的話要加多少空格在姓氏前面
			
			for(int j=0;j<padding;j++){
				cout <<' ';  //輸出英文名字前，先填補姓氏前空格，對齊好空格，再印出名字 
			}
			cout <<names[i]<<endl;	 
		}
	}

//6.釋放動態分配的記憶體 
    for(int i=0;i<x;i++){
    	delete[]names[i]; //釋放每個字串的記憶體 
	} 
	delete[] names; //釋放整個字串陣列記憶體 
	
	return 0;
} 

