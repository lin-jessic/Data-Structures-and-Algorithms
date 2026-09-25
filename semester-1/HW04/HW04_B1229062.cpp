#include <iostream>  //cin、cout 
#include <cstdlib>   //隨機數
#include <ctime>     //時間函數庫，生成隨機數種子
using namespace std;

//1.定義表示多項式項的結構
struct Term {
    int coef; //係數
    int exp;  //次方
    Term* next; //指向下一個項的pointer（linked list的node）
};

//2.加入項到linked list中，並按照次方降冪排序
void insertTerm(Term*& head, int coef, int exp) {
    Term* newTerm = new Term{coef, exp, nullptr}; //創建新的node
    if (!head || head->exp < exp) { //如果串列為null或新項的次方大於頭項次方
        newTerm->next = head; //新項的下一個node設為當前頭node
        head = newTerm; //更新頭node為新項
    } else {
        Term* current = head; //從頭node開始遍歷
        while (current->next && current->next->exp >= exp) { //找到適合的位置插入
            current = current->next;
        }
        newTerm->next = current->next; //將新項插入到linked list中
        current->next = newTerm;
    }
}

//3.列印多項式（依次輸出每個項）
void printPolynomial(Term* head) {
    bool first = true; //判斷是否為第一項
    while (head) { //遍歷每個node
        if (first) { //第一項輸出不加 "+" 符號
            cout << head->coef << "x^" << head->exp;
            first = false; //第一項輸出後設為 false
        } else { //然後其他項還要根據係數決定是否加 "+"
            if (head->coef < 0) {
                cout << head->coef << "x^" << head->exp;
            } else {
                cout << "+" << head->coef << "x^" << head->exp;
            }
        }
        head = head->next; //移動到下一個項
    }
    cout << endl; //換行
}

//4.將單項結果加入結果多項式 c 中
void addPolynomials(Term*& c, int coef, int exp) {
    Term* current = c; //從頭node開始
    while (current) {  //遍歷 c，檢查是否存在相同次方的項
        if (current->exp == exp) { //如果次方相同
            current->coef += coef; //就要累加係數
            return;
        }
        current = current->next; //繼續檢查下一個node
    }
    insertTerm(c, coef, exp); //如果沒有相同次方，插入新項
}

//5.兩個多項式相乘
Term* multiplyPolynomials(Term* poly1, Term* poly2) {
    Term* c = nullptr; //用於存放結果的多項式 c（初始化為空）
    for (Term* p1 = poly1; p1; p1 = p1->next) { //遍歷第一個多項式的每一項
        for (Term* p2 = poly2; p2; p2 = p2->next) { //遍歷第二個多項式的每一項
            int newCoef = p1->coef * p2->coef; //計算新係數
            int newExp = p1->exp + p2->exp;   //計算新次方
            addPolynomials(c, newCoef, newExp); //將結果加入結果多項式 c 中
        }
    }
    return c;
}

//6.隨機生成多項式，但係數固定為 1，次方範圍為 0 到 100
Term* generateRandomPolynomial(int terms) {
    Term* poly = nullptr; //初始化多項式為null
    for (int i = 0; i < terms; i++) { //生成指定數量的項次 
        int coef = 1; //固定係數為 1
        int exp = rand() % 101; //隨機生成次方範圍為 0 到 100
        insertTerm(poly, coef, exp); //插入新項到多項式
    }
    return poly;
}

//7.主程式 
int main() {
    srand(time(0)); //初始化隨機數，保證每次生成的隨機數字不會完全一樣，且執行結果也會不同

    int m, n;
    cout << "輸入第一個多項式的項數 m: ";
    cin >> m; 
    cout << "輸入第二個多項式的項數 n: ";
    cin >> n; 

    Term *poly1 = nullptr, *poly2 = nullptr; //初始化兩個多項式為null 

    //(1)第一個多項式輸入
    if (m <= 10) { // 如果項數小於等於 10，要手動輸入
        cout << "請手動輸入第一個多項式 (係數 次方):" << endl;
        for (int i = 0; i < m; i++) {
            int coef, exp;
            cin >> coef >> exp; //輸入係數和次方
            insertTerm(poly1, coef, exp); //將輸入插入到第一個多項式
        }
    } else { //如果項數大於 10，跳到隨機生成程式 
        poly1 = generateRandomPolynomial(m);
    }

    //(2)第二個多項式輸入
    if (n <= 10) { // 如果項數小於等於 10，手動輸入
        cout << "請手動輸入第二個多項式 (係數 次方):" << endl;
        for (int i = 0; i < n; i++) {
            int coef, exp;
            cin >> coef >> exp; //輸入係數和次方
            insertTerm(poly2, coef, exp); //將輸入插入到第二個多項式
        }
    } else { //如果項數大於 10，跳到隨機生成程式 
        poly2 = generateRandomPolynomial(n);
    }

    //輸出第一個多項式
    cout << "第一個多項式 (降冪): ";
    printPolynomial(poly1);

    //輸出第二個多項式
    cout << "第二個多項式 (降冪): ";
    printPolynomial(poly2);

    //8.排除輸入輸出時間，開始計算多項式相乘時間
    const int repeat = 100000; //重複執行次數，用於計算平均時間
    clock_t start = clock(); //記錄開始時間
    for (int i = 0; i < repeat; i++) {
        Term* temp = multiplyPolynomials(poly1, poly2); //執行多項式相乘
    }
    clock_t end = clock(); //記錄結束時間

    //計算平均時間
    double duration = double(end - start) / CLOCKS_PER_SEC / repeat;

    //9.計算相乘的結果
    Term* result = multiplyPolynomials(poly1, poly2);

    //輸出相乘結果
    cout << "相乘結果 (降冪): ";
    printPolynomial(result);

    // 顯示計算時間
    cout << "平均計算時間 (排除輸入輸出): " << duration << " 秒" << endl;

    return 0; // 結束程式
}

