#include <iostream>
#include <chrono>
#include <algorithm> // 用於 std::swap
using namespace std;

// 選擇排序函式
// 時間複雜度最壞情況: O(n^2)
void SelectionSort(int* arr, const int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        // 每次都需要比較 n - i 次，最壞情況 O(n^2)
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 最壞情況下可能需要交換，但這是 O(n) 次
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    const int repetitions = 1000; // 每次測量重複次數，以獲得平均值
    int max_n = 3000;

    // 依次測量不同的 n 值，包括 n = 0
    for (int n = 0; n <= max_n; n += 500) {
        int* arr = new int[n];
        
        // 準備最壞情況數據：降序排列數組，O(n^2) 最壞情況
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }

        // 計時開始
        auto start = chrono::high_resolution_clock::now();
        
        // 重複選擇排序多次以獲得平均執行時間
        for (int i = 0; i < repetitions; i++) {
            SelectionSort(arr, n); // O(n^2)
        }
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, micro> elapsed = end - start;

        // 計算平均時間
        double average_time = elapsed.count() / repetitions;

        // 輸出結果，顯示 n 值及其對應時間
        cout << "n = " << n << ", 最壞時間 = " << average_time << " 微秒" << endl;

        delete[] arr;
    }
    
    return 0;
}

