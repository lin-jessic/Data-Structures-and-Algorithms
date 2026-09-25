#include <iostream>
#include <string>
#include <sstream>  // 用來格式化輸出
using namespace std;

class Quadratic {
private:
    double a, b, c;  // 儲存多項式的係數

public:
    // (a) 預設建構子：建立 0 多項式
    Quadratic() : a(0), b(0), c(0) {}

    // (a) 自訂建構子：用參數初始化 a, b, c
    Quadratic(double a, double b, double c) : a(a), b(b), c(c) {}

    // (b) 運算子重載：相加兩個二次多項式
    Quadratic operator+(const Quadratic& other) const {
        return Quadratic(a + other.a, b + other.b, c + other.c);
    }

    // (c) 運算子重載 >> ：讀入多項式係數
    friend istream& operator>>(istream& in, Quadratic& poly) {
        cout << "(1)請依次輸入 a, b, c 的值：";
        in >> poly.a >> poly.b >> poly.c;  // 改為浮點數輸入
        return in;
    }

    // (c) 運算子重載 << ：格式化輸出多項式
    friend ostream& operator<<(ostream& out, const Quadratic& poly) {
        stringstream ss;  // 用於暫存格式化的多項式字串

        // 組合多項式格式，忽略係數為 0 的項
        bool isFirst = true; // 用來判斷是否是第一項
        if (poly.a != 0) {
            ss << poly.a << "x^2";
            isFirst = false;
        }
        if (poly.b != 0) {
            if (!isFirst) {
                ss << (poly.b > 0 ? " + " : " ");  // 加號或空格
            }
            ss << poly.b << "x";
            isFirst = false;
        }
        if (poly.c != 0) {
            if (!isFirst) {
                ss << (poly.c > 0 ? " + " : " ");  // 加號或空格
            }
            ss << poly.c; // 輸出常數項
        }

        // 如果所有係數都為 0，則輸出 0
        if (poly.a == 0 && poly.b == 0 && poly.c == 0) {
            ss << "0";
        }

        out << ss.str();  // 輸出格式化後的多項式字串
        return out;
    }

    // (d) Eval 函數：計算多項式在 x 位置的值
    double Eval(double x) const {  // 將 x 的類型改為 double
        return a * x * x + b * x + c;
    }
};

int main() {
    Quadratic p1, p2;

    // 顯示多項式標題
    cout << "多項式皆為 ax^2 + bx + c " << endl;  // 在這裡加入標題

    // 讀入兩個多項式
    cout << "(一)第一個多項式：" << endl;
    cin >> p1;
    cout << "(2)第一個多項式： " << p1 << endl;
    cout << "(二)第二個多項式：" << endl;
    cin >> p2;
    cout << "(2)第二個多項式： " << p2 << endl;

    // (b) 相加兩個多項式並輸出結果
    Quadratic sum = p1 + p2;
    cout << "(三)相加後的多項式： " << sum << endl;

    // (d) 測試 Eval 函數
    double x;  // 將 x 的類型改為 double
    cout << "(1)請輸入 x 的值：";
    cin >> x;
    cout << "(四)多項式在 x = " << x << " 時的值為：" << sum.Eval(x) << endl;

    return 0;
}

