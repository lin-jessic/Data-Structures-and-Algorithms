#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;


// 1.Heap Sort
template <class T>
void Adjust(T* a, int root, int n) {
	// 以 a[root] 根的子樹進行向下調整 ，要做出 Max heap 的結構 
    T e = a[root]; //做暫存根節點的值 
    int j; //定義一個指標 j 
    // for 迴圈:每次往下找子節點 
    for (j = 2 * root; j <= n; j *= 2) {
    	 // 如果有右子節點，且右子節點比較大，指標 j 指向右子節點 
        if (j < n && a[j] < a[j + 1]) j++;
        
        // 如果目前節點>=子節點(父節點已經比子節點大)，則不需調整 
        if (e >= a[j]) break; 
        
        a[j / 2] = a[j]; // 大的子節點上移
    }
    a[j / 2] = e; // 把原本的值放回調整後的根
}
template <class T>
void HeapSort(T* a, int n) {
	 // 第一個 for 迴圈:從最後一個內部節點開始，依序建立出 Max heap 
    for (int i = n / 2; i >= 1; i--)
        Adjust(a, i, n); // 由下往上調整堆積 (建立堆疊 O(n) ) 
     // 第二個 for 迴圈:依次取出最大值(根節點)和最後一個節點交換再取出，並持續調整 
    for (int i = n; i > 1; i--) { 
        swap(a[1], a[i]); // 把根節點(最大值)移到最後一個節點 
        Adjust(a, 1, i - 1); // 調整剩下的堆積，一樣要做成 Max heap(每次調整 O(log n) )
    }
}
//這裡使用陣列從 index = 1 開始，保留 a[0] 不使用。
// 這是為了方便使用設定(以下關係)：
// (1)左子節點：2 * i
// (2)右子節點：2 * i + 1
// (3)父節點：   i / 2
// 若從 a[0] 開始就需調整公式: 
// 補充:若從 a[0] 開始，以上公式就要變成：
// 左子節點 = 2 * i + 1，右子節點 = 2 * i + 2，父節點 = (i - 1) / 2

// 2.Merge Sort
template <class T>
void Merge(T* initList, T* mergedList, int left, int mid, int right) {
	// 將兩個已經排序好的子陣列 [left  mid]、[mid+1  right] 合併成一個陣列 
	//分別定義指向左半邊起始位置、右半邊起始位置、mergeList 的填入位置的指標 
    int i1 = left, i2 = mid + 1, iResult = left; 
    
    // 當左右兩邊都有剩下的元素，進行比較 
    while (i1 <= mid && i2 <= right) {
        if (initList[i1] <= initList[i2]) // 如果左半邊元素較小，先放進 mergedList 
            mergedList[iResult++] = initList[i1++];
        else //如果是右半邊元素較小，先放進 mergedList 
            mergedList[iResult++] = initList[i2++];
    }
    
     // 將左邊剩下的全部搬到結果陣列中 
    while (i1 <= mid)
        mergedList[iResult++] = initList[i1++];
    // 將右邊剩下的資料全部搬到結果陣列
    while (i2 <= right)
        mergedList[iResult++] = initList[i2++];
}

template <class T>
void MergePass(T* initList, T* resultList, int n, int s) {
	// 將相鄰的區間長度為 s 的兩組資料合併成長度為 2s 的區塊
    int i;
     // 每次跳過 2s 的區塊：合併 [i ~ i+s-1] 和 [i+s ~ i+2s-1]
    for (i = 0; i <= n - 2 * s; i += 2 * s)
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);

    // 剩下不足兩個區塊時，合併剩下最後一組 
	if (i + s - 1 < n)
        Merge(initList, resultList, i, i + s - 1, n - 1);
    else
        // 如果只剩一段，不需要合併，直接複製到結果陣列
        for (int j = i; j < n; j++)
            resultList[j] = initList[j];
}

template <class T>
void MergeSort(T* a, int n) {
	// 建立暫存陣列 ，用來交替存放合併結果 
    T* tempList = new T[n];
    
    // for 迴圈:不斷兩兩結合 
    for (int s = 1; s < n; s *= 2) {
    	 // 每輪 s = 1, 2, 4, 8 ... 表示合併區塊的長度
        MergePass(a, tempList, n, s); // 第一輪:a -> temp ，(O(n))
        s *= 2;
        MergePass(tempList, a, n, s); // 第二輪:temp -> a ，(O(n))
        // 每兩輪交換 input/output 角色，保持原地排序
    }
    delete[] tempList;
}

// 3.Quick Sort  
 //（用三數中位數選 pivot）
template <class T>
void QuickSort(T* a, const int left, const int right) {
    if (left < right) {
        int i = left, j = right;

        // 取中間位置
        int mid = left + (right - left) / 2;

        // 找出 a[left]、a[mid]、a[right] 中的中位數，並放到 a[left]
        if (a[mid] < a[left]) swap(a[mid], a[left]);   // 確保 a[left] <= a[mid]
        if (a[right] < a[left]) swap(a[right], a[left]); // 確保 a[left] 是三者中最小或第二小
        if (a[right] < a[mid]) swap(a[right], a[mid]); // 確保 a[mid] 是中位數
        swap(a[mid], a[left]); // 把中位數移到最左邊，作為 pivot

        T pivot = a[left];  // 設定 pivot 為中位數

        // 開始進行分割過程
        while (i < j) {
            // 從右往左找第一個比 pivot 小的值
            while (i < j && a[j] >= pivot) j--;
            // 從左往右找第一個比 pivot 大的值
            while (i < j && a[i] <= pivot) i++;
            // 若找到的 i 和 j 尚未交錯，就交換它們
            if (i < j) swap(a[i], a[j]);
        }

        // 最後把 pivot 放到正確的位置（j 是最後比 pivot 小的位置）
        swap(a[left], a[j]);

        // 對左右兩側繼續遞迴排序
        QuickSort(a, left, j - 1);   // 左半邊
        QuickSort(a, j + 1, right);  // 右半邊
    }
}




// 公用涵式部分 

//1.產生隨機陣列，值在 1 ~ 50000 之間
void generateRandomArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 50000 + 1;
    }
}

//2. 印出陣列的前 limit 筆資料（預設為 10 筆）
void printArray(int* arr, int size, int limit = 10) {
    for (int i = 0; i < min(size, limit); i++) {
        cout << arr[i] << " ";
    }
    if (size > limit) {
        cout << "... (共 " << size << " 個數字)";
    }
    cout << endl;
}

//3.執行指定排序並顯示平均排序時間，若資料量小（<=1000），會重複排序多次並取平均時間
void testSorting(int size, int method) {
      const int repeatCount = (size <= 1000) ? 30 : 1;  // 重複次數
    long long totalDuration = 0; // 總花費時間（單位：奈秒），用來累加多次測試結果

    // 開始進行多次測試
    for (int r = 0; r < repeatCount; r++) {
        int* arr = nullptr; // 宣告指標 arr，用來指向排序用的整數陣列
        // 根據使用者選擇的排序方法建立陣列
        // HeapSort 會從 index 1 開始 (index 0不用) 
        if (method == 1) {
            arr = new int[size + 1]; // 建立陣列（額外多一格） 
            generateRandomArray(arr + 1, size); // 從 index 1 開始填入隨機資料
        } else {
            arr = new int[size];  // 其他排序法正常從 index 0 開始 
            generateRandomArray(arr, size); // 填入隨機資料 
        }

        // 印出初始資料（僅第一次顯示）
        if (r == 0) {
            cout << "\n[排序前] ";
            if (method == 1)
                printArray(arr + 1, size); // HeapSort 從 arr[1] 開始印 
            else
                printArray(arr, size); // 其他從 arr[0] 開始印 
        }

        // 開始計時
        auto start = high_resolution_clock::now();

        // 執行對應的排序方法
        switch (method) {
            case 1: HeapSort(arr, size); break;
            case 2: MergeSort(arr, size); break;
            case 3: QuickSort(arr, 0, size - 1); break;
        }
        
		// 結束計時 
        auto end = high_resolution_clock::now(); 
        // 計算此次排序所花的時間（單位：奈秒）
        auto duration = duration_cast<nanoseconds>(end - start);
        // 加總此次排序時間至 totalDuration
        totalDuration += duration.count();

        // 印出排序結果（僅第一次顯示）
        if (r == 0) {
            cout << "[排序後] ";
            if (method == 1)
                printArray(arr + 1, size);
            else
                printArray(arr, size);
        }

        delete[] arr;  // 釋放記憶體
    }

    // 顯示平均排序時間（總時間除以執行次數）
    cout << "排序 " << size << " 個數字所需平均時間: "
         << totalDuration / repeatCount << " 奈秒（共執行 " << repeatCount << " 次）\n";
}

//主程式 
int main() {
    srand(time(0));  // 設定亂數種子

    int method;
    char repeat;
    char manualInput;

    do {
        // 讓使用者選擇排序方法
        cout << "\n請選擇排序方法：\n";
        cout << "1. Heap Sort\n2. Merge Sort\n3. Quick Sort\n輸入選項 (1/2/3): ";
        cin >> method;

        if (method < 1 || method > 3) {
            cout << "無效的選項！請重新輸入。\n";
            continue;
        }

        // 是否手動輸入資料大小
        cout << "是否要手動輸入排序數量？(y/n): ";
        cin >> manualInput;

        if (manualInput == 'y' || manualInput == 'Y') {
            int size;
            cout << "請輸入要排序的數字數量: ";
            cin >> size;

            if (size <= 0) {
                cout << "數量必須為正整數！\n";
                continue;
            }

            testSorting(size, method);  // 依照輸入的數量進行排序測試
        } else {
            // 若不是手動輸入，則自動測試多組資料量
            int sizes[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};
            for (int size : sizes) {
                cout << "\n-- 測試排序數量：" << size << " --\n";
                testSorting(size, method);
            }
        }

        // 詢問是否繼續測試
        cout << "\n是否要繼續測試？(y/n): ";
        cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');

    cout << "end" << endl;
    return 0;
}

