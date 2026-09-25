# Data Structures and Algorithms

長庚大學資訊工程學系「資料結構與演算法」課程實作整理。

本 Repository 收錄上下學期的 C++ 程式作業與實驗紀錄，內容從基礎搜尋與排序演算法，逐步延伸至多項式資料結構、進階排序、Graph Representation，以及 DFS / BFS Traversal。

除了完成演算法實作之外，部分作業亦透過不同輸入規模進行執行時間量測與圖表分析，比較理論時間複雜度與實際程式執行結果。

**Institution:** 長庚大學 資訊工程學系  
**Language:** C++  
**Topics:** Data Structures / Algorithms / Complexity Analysis / Graph Traversal

---

## Repository Structure

```text
Data-Structures-and-Algorithms/
│
├── semester-1/
│   ├── HW01/
│   ├── HW02/
│   ├── HW03/
│   └── HW04/
│
├── semester-2/
│   ├── HW01/
│   ├── HW02/
│   ├── HW03/
│   ├── HW04/
│   └── HW05/
│
├── README.md
└── .gitignore
```

各資料夾保留課程期間完成的 C++ 原始程式與相關作業文件；部分實驗另包含執行時間分析資料與圖表。

---

## Course Contents

### Search & Basic Sorting

課程前期透過搜尋與排序演算法實作，觀察資料規模增加時的執行時間變化。

包含：

- Binary Search
- Selection Sort
- Execution Time Measurement
- Time Complexity Analysis

其中 Binary Search 透過不同資料量測試平均搜尋時間；Selection Sort 則以不同輸入規模觀察其平方成長的執行時間特性。

---

## Binary Search

Binary Search 在已排序資料中持續將搜尋範圍縮小一半。

```text
Sorted Array
      │
      ▼
Check Middle
   /       \
smaller   larger
  │          │
  ▼          ▼
Left Half  Right Half
```

理論時間複雜度：

```text
O(log n)
```

課程作業中透過不同 `n` 值重複執行搜尋，以量測平均搜尋時間並與理論複雜度進行比較。

---

## Selection Sort

Selection Sort 每一輪從尚未排序的區域中找出最小元素，再與目前位置交換。

```text
Unsorted Array
      │
      ▼
Find Minimum
      │
      ▼
Swap
      │
      ▼
Sorted Region + Unsorted Region
```

時間複雜度：

```text
O(n²)
```

作業中以不同輸入規模量測實際排序時間，觀察資料量增加後的執行時間變化。

---

## Polynomial Representation & Multiplication

其中一項作業以 Linked Structure 表示 Polynomial Term，並實作多項式相乘。

每個 Term 包含：

```text
Coefficient
Exponent
Next
```

概念結構：

```text
[coef, exp] → [coef, exp] → [coef, exp] → ...
```

多項式相乘時，會遍歷兩個 Polynomial 的各個 Term：

```text
Polynomial A
    │
    ├──────────────┐
    ▼              ▼
 Term A1         Term A2
    │              │
    ▼              ▼
Polynomial B × Polynomial B
    │
    ▼
Combine Terms
    │
    ▼
Result Polynomial
```

作業另外比較 Dense 與 Non-Dense Polynomial 在不同輸入規模下的實際執行時間，並分析程式中的 Nested Loop 與結果項目合併所造成的時間成本。

---

## Sorting Algorithms

後續作業進一步實作與比較三種常見排序演算法：

- Heap Sort
- Merge Sort
- Quick Sort

### Complexity

| Algorithm | Best Case | Worst Case |
| --- | --- | --- |
| Heap Sort | O(n log n) | O(n log n) |
| Merge Sort | O(n log n) | O(n log n) |
| Quick Sort | O(n log n) | O(n²) |

---

### Heap Sort

利用 Heap 結構進行排序。

每次 Heap Adjustment 約需：

```text
O(log n)
```

整體進行約 `n` 次，因此時間複雜度為：

```text
O(n log n)
```

---

### Merge Sort

將資料持續切分後再逐層合併：

```text
Array
      │
   Split
   /   \
  ▼     ▼
Half   Half
 │       │
 ▼       ▼
Sort    Sort
  \     /
   Merge
     │
     ▼
Sorted Array
```

每層合併約需 `O(n)`，共約 `log n` 層，因此：

```text
O(n log n)
```

Merge Sort 需要額外的暫存空間，因此空間複雜度為：

```text
O(n)
```

---

### Quick Sort

Quick Sort 透過 Pivot 將資料分割成左右子陣列。

```text
          Pivot
         /     \
        ▼       ▼
    Smaller   Larger
       │         │
       └── Recursive ──┘
```

當分割較平均時：

```text
O(n log n)
```

若 Pivot 持續造成極度不平均的分割：

```text
O(n²)
```

課程實驗中亦透過實際執行時間比較 Heap Sort、Merge Sort 與 Quick Sort，觀察理論複雜度與實際效能之間的差異。

---

## Graph Representation

後續作業以 C++ 隨機產生 Undirected Graph，並分別建立：

- Adjacency Matrix
- Adjacency List

若 Vertex `u` 與 `v` 之間存在 Edge，因為是 Undirected Graph：

```text
u ───── v
```

因此：

```text
v ∈ adjacency(u)
u ∈ adjacency(v)
```

程式亦會將 Edge 資料輸出為 CSV，供後續圖形化工具使用。

---

## DFS & BFS

在建立隨機無向圖後，進一步實作：

- Depth-First Search (DFS)
- Breadth-First Search (BFS)

### DFS

DFS 優先沿著目前節點繼續向下一層探索：

```text
Start
  │
  ▼
Node
  │
  ▼
Next Unvisited Node
  │
  ▼
Continue Deeper
```

### BFS

BFS 則使用 Queue 逐層尋訪：

```text
Start
  │
  ▼
Queue
  │
  ├─ Neighbor 1
  ├─ Neighbor 2
  ├─ Neighbor 3
  └─ ...
```

作業會輸出 DFS / BFS 的：

- Traversal Order
- Adjacency Matrix
- Adjacency List
- Edge CSV

並將 CSV 匯入 NodeXL，分別產生原始 Random Graph、DFS Tree 與 BFS Tree，以圖形方式驗證 Traversal 結果。

---

## Selected Topics

| Topic | Implementation / Analysis |
| --- | --- |
| Binary Search | C++ 實作與執行時間量測 |
| Selection Sort | C++ 實作與 O(n²) 效能觀察 |
| Polynomial | Linked Structure、多項式相乘與複雜度分析 |
| Heap Sort | C++ 排序與效能分析 |
| Merge Sort | Divide-and-Conquer 與效能分析 |
| Quick Sort | Pivot Partition 與不同情況之複雜度 |
| Graph | Random Undirected Graph |
| Graph Representation | Adjacency Matrix / Adjacency List |
| DFS | Depth-First Traversal / DFS Tree |
| BFS | Breadth-First Traversal / BFS Tree |

---

## What I Learned

這門課讓我從單純「讓程式得到正確答案」，進一步開始思考資料結構與演算法選擇對程式效能造成的影響。

透過 Binary Search、Selection Sort、Heap Sort、Merge Sort 與 Quick Sort 等實作，我將課堂上的時間複雜度概念與實際執行時間進行比較；在 Polynomial 與 Graph 作業中，則進一步接觸 Linked Structure、Adjacency Matrix、Adjacency List，以及 DFS / BFS 等資料表示與 Traversal 方法。

實際量測與繪製執行時間曲線的過程，也讓我理解理論上的 Big-O 並不等同於每一次實際執行速度，而需要同時考慮資料分布、實作方式與額外空間等因素。

---

> 本 Repository 為大學課程學習成果整理，內容以課程期間實際完成之程式、作業文件與實驗結果為主。
