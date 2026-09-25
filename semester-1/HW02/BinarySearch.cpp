#include <iostream>
#include <ctime>
#include <algorithm> // 用於 std::sort

using namespace std;

// BinarySearch 函數，根據圖片中的 Program 1.10
int BinarySearch(int *a, const int x, const int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (x < a[middle]) right = middle - 1;
        else if (x > a[middle]) left = middle + 1;
        else return middle;
    }
    return -1;  // 沒找到
}

int main() {
    clock_t start_time, end_time;
    float total_time;

    // 設定實驗範圍，n 的範圍為 [0, 100]
    int max_n = 100;
    
    // 創建陣列以儲存測試結果
    float search_times[max_n + 1];

    for (int n = 0; n <= max_n; n += 10) {
        // 動態分配空間給陣列
        int *arr = new int[n];

        // 初始化陣列為遞增順序
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        // 對陣列進行排序（這裡實際上已經是排序過的，可以省略）
        // std::sort(arr, arr + n); // 若要測試排序時間，可以解除註解

        // 設定要搜尋的數字，確保它在陣列內
        int target = (n > 0) ? n / 2 : 0; // 若 n = 0，則 target 設為 0

        // 開始計算搜尋時間
        start_time = clock();
        for (int i = 0; i < 100000; i++) { // 測試的迭代次數
            BinarySearch(arr, target, n);
        }
        end_time = clock();

        // 計算搜尋總時間並轉換為秒
        total_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
        search_times[n] = total_time / 100000; // 計算平均時間

        // 輸出每個 n 值的搜尋時間
        cout << "n = " << n << ", 平均搜尋時間: " << search_times[n] << " 秒" << endl;

        // 清理動態記憶體
        delete[] arr;
    }

    system("pause");
    return 0;
}

