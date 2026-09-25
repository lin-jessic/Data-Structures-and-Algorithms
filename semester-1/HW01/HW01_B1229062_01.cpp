//1.設好必要標頭檔 
#include <iostream> //提供標準的cin和cout功能
#include <cstring>  //用來處理C-Style字串
using namespace std; //在程式中使用 using namespace std;，你就不需要在每次有std::cout(用於輸出)、std::cin(用於輸入)、std::string都加上 std::，這樣可以讓代碼更簡潔

//6.用bubble sort 根據ASCII排序字串，每個字串第一個字元的ASCII值從大排到小
    void bubbleSort(char**arr,int x){  //void 表示這個函數沒有返回值，char**arr指向一個字串數組，每個char指向一個字串，int x表示字串數量=二維陣列行數 
    	for(int i=0;i<x-1;i++){ //外層循環，每遍循環 會將當前為排序部分的最大元素往後放，須執行x-1次，最後最大元素會被放到開頭 
    		for(int j=0;j<x-i-1;j++){ //內層循環，用來比較並交換字串 
    			if (arr[j][0]<arr[j+1][0]){ //比較當前字串第一個字與下一個字串第一個字的ASCII值 
    			   char*tmp=arr[j];
    			   arr[j]=arr[j+1];
    			   arr[j+1]=tmp;
    		    }
			}
		}
    } 

//2.變數宣告，和使用者輸入
int main (){
    int x,y; 
    cout <<"請輸入字串數量(x):";
    cin >>x;
    cout <<"請輸入字串最大長度(y):";
    cin >>y;
    cin.ignore(); //清空輸入緩衝區 

//3.用new動態分配二維陣列
    char**matrix_new=new char *[x]; //x行
    for (int i=0;i<x;i++){
        matrix_new[i]=new char[y+1]; //字串分配長度含'/0'，'/0'是作為結束符
    }
    
//4.要求使用者輸入的字串放入matrix
    for (int i=0;i<x;i++){
    	cout<<"請輸入第"<<i+1<<"個字串(最多"<<y<<"個字元):";
		cin.getline(matrix_new[i],y+1);
    }

//5.輸出字串逐一放入動態二維陣列中
     cout <<"Part1_逐一放入原字串:"<<endl;
	for(int i=0;i<x;i++) {
	   cout <<matrix_new[i] <<endl;
    } 
    
//7.輸出排序的結果
    bubbleSort(matrix_new, x); //使用bubble sort完成條件:字串第一個字元依大小排序 
    cout <<"Part2_經排序後的字串為:"<<endl;
	for(int i=0;i<x;i++) {
	   cout <<matrix_new[i] <<endl;
    }

//8.手動釋放動態陣列記憶體，二維陣列需逐行釋放，再釋放行指標
    for(int i=0;i<x;i++) {
	   delete[] matrix_new[i]; //釋放每一行 
    }
    delete[] matrix_new; //釋放行指標 
    
    return 0;
}
