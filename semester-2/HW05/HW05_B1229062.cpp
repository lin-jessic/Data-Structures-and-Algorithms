#include <iostream>
#include <vector> 
#include <queue> // Queue (BFS要用) 
#include <fstream> //檔案輸出功能 
#include <cstdlib> // rand() 隨機 
#include <ctime> // time() 隨機種子 

using namespace std;

const int WHITE = 0;  // vertex 尚未被造訪 
const int GRAY = 1;  // vertex 已 discovered，但未 finish  
const int BLACK = 2;  // vertex搜尋已finished

// 定義 edge 會用到的 data structure 
struct Edge {
    int from, to; //從某一點 (起點)到某一點 (終點) 
};

// 定義 vertex 會用到的 data structure
struct Vertex {
    int color, d, f, pi; // color, discovery time/distance, finish time, parent index
};

// 初始化所有儲存 Graph 與搜尋狀態的 data structure
vector<vector<int>> adjList; //adjust list: record每個 vertex 所連接的鄰居vertex 
vector<vector<int>> adjMatrix; //adjst matrix: 檢查 edge是否已存在 
vector<Vertex> dfsV, bfsV; // DFS / BFS 過程中的每個 vertex狀態(包含 color, d, f, pi)
vector<Edge> oriEdges, dfsEdges, bfsEdges;// 儲存不同來源的edge(隨機的、DFS的、BFS的) 
vector<int> dfsOrder, bfsOrder; //儲存尋訪順序 
int timer = 0; //記時間的 (d, f) 

// 輸出 CSV 檔案
void saveCSV(string fileName, const vector<Edge>& edges) {
    ofstream fout(fileName.c_str());
    fout << "Vertex 1,Vertex 2\n";
    for (int i = 0; i < edges.size(); i++) {
        fout << edges[i].from << "," << edges[i].to << "\n";
    }
    fout.close();
}

// 印出鄰接矩陣和鄰接串列
void showAdj(const vector<Edge>& edges, int n, string name) {
    vector<vector<int>> mat(n, vector<int>(n, 0)); //鄰居都先為空  
    vector<vector<int>> list(n);  //矩陣內都先為 0  

    // 建構鄰接矩陣與鄰接串列
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        if (mat[u][v] == 0) { // 避免重複加入
            mat[u][v] = mat[v][u] = 1;
            list[u].push_back(v);
            list[v].push_back(u);
        }
    }

    // 印出鄰接矩陣
    cout << "\n" << name << " 的鄰接矩陣：\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

    // 印出鄰接串列
    cout << "\n" << name << " 的鄰接串列：\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < list[i].size(); j++) {
            cout << list[i][j] << " ";
        }
        cout << "\n";
    }
}

// DFS 遞迴 
void DFSVisit(int u) {
    dfsV[u].color = GRAY;
    dfsV[u].d = ++timer;
    dfsOrder.push_back(u);
    
    for (int i = 0; i < adjList[u].size(); i++) {
        int v = adjList[u][i];
        if (dfsV[v].color == WHITE) {
            dfsV[v].pi = u;
            Edge e; e.from = u; e.to = v;
            dfsEdges.push_back(e);
            DFSVisit(v);
        }
    }
    dfsV[u].color = BLACK;
    dfsV[u].f = ++timer;
}

// DFS 主程式
void DFS(int n) {
    dfsV.clear();
    for (int i = 0; i < n; i++) {
        Vertex v;
        v.color = WHITE; v.d = 0; v.f = 0; v.pi = -1;
        dfsV.push_back(v);
    }
    timer = 0;
    for (int i = 0; i < n; i++) {
        if (dfsV[i].color == WHITE)
            DFSVisit(i);
    }
}

// BFS 主程式
void BFS(int n) {
    bfsV.clear();
    for (int i = 0; i < n; i++) {
        Vertex v;
        v.color = WHITE; v.d = -1; v.f = 0; v.pi = -1;
        bfsV.push_back(v);
    }

    for (int s = 0; s < n; s++) {
        if (bfsV[s].color != WHITE) continue;
        bfsV[s].color = GRAY;
        bfsV[s].d = 0;
        queue<int> Q;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            bfsOrder.push_back(u);
            
            for (int i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i];
                if (bfsV[v].color == WHITE) {
                    bfsV[v].color = GRAY;
                    bfsV[v].d = bfsV[u].d + 1;
                    bfsV[v].pi = u;
                    Edge e; e.from = u; e.to = v;
                    bfsEdges.push_back(e);
                    Q.push(v);
                }
            }
            bfsV[u].color = BLACK;
        }
    }
}

int main() {
    int n, e;
    cout << "請輸入節點數 n: ";
    cin >> n;
    cout << "請輸入邊數 e (最大為 n*(n-1)/2): ";
    cin >> e;

    if (e > n * (n - 1) / 2) {
        cout << "錯誤：邊數過多！\n";
        return 1;
    }

    //建立空的 adjust list、adjust matrix 
	for (int i = 0; i < n; i++) {
        adjList.push_back(vector<int>()); //鄰居都先為空 
        adjMatrix.push_back(vector<int>(n, 0)); //矩陣內都先為 0 
    }

    srand(time(0)); //設亂數種子 
    int count = 0; //定義記錄目前已產生的 edge 
    while (count < e) {
        int a = rand() % n, b = rand() % n; //隨機選擇節點 a、b 
        if (a != b && adjMatrix[a][b] == 0) { //不是 self-loop，且 edge還未存在 
            adjMatrix[a][b] = adjMatrix[b][a] = 1;
            adjList[a].push_back(b);
            adjList[b].push_back(a);

            //記錄這條 edge，要輸出 csv 
			Edge edge;
            edge.from = a;
            edge.to = b;
            oriEdges.push_back(edge);

            count++;
        }
    }

    cout << "\n隨機無向圖的鄰接矩陣：\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n隨機無向圖的鄰接串列：\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        
    // 排序：讓鄰接串列由小到大排好
    for (int j = 0; j + 1 < adjList[i].size(); j++)
        for (int k = j + 1; k < adjList[i].size(); k++)
        if (adjList[i][k] < adjList[i][j])
            swap(adjList[i][j], adjList[i][k]);
		
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] << " ";
        }
        cout << "\n";
    }

    DFS(n);
    BFS(n);

	showAdj(dfsEdges, n, "DFS Tree");
	
	cout << "\nDFS 尋訪順序:";
    for (int i = 0;i < dfsOrder.size(); i++) 
	cout << dfsOrder[i] << " ";
	cout << "\n";
	
    showAdj(bfsEdges, n, "BFS Tree");
	
	cout << "\nBFS 尋訪順序:";
    for (int i = 0;i < bfsOrder.size(); i++) 
	cout << bfsOrder[i] << " ";
	cout << "\n"; 

    saveCSV("graph_edges.csv", oriEdges);
    saveCSV("dfs_tree.csv", dfsEdges);
    saveCSV("bfs_tree.csv", bfsEdges);

    cout << "輸出檔案：\n- graph_edges.csv\n- dfs_tree.csv\n- bfs_tree.csv\n";
    return 0;
}

