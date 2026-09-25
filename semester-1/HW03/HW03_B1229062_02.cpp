#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class String {
public:
    // 計算字元頻率的函式
    void Frequency(const string& input) {
        unordered_map<char, int> freqMap;

        // 遍歷字串，計算每個字元的出現次數
        for (char ch : input) {
            freqMap[ch]++;
        }

        // 輸出每個不重複字元及其頻率
        cout << "字元頻率(若有空格表示為 _ )：" << endl;
        for (const auto& entry : freqMap) {
            if (entry.first == ' ') {
                cout << "_: " << entry.second << endl;  // 空格用 "_" 表示
            } else {
                cout << entry.first << ": " << entry.second << endl;
            }
        }
    }
};

int main() {
    String s;
    string testStr;

    cout << "請輸入測試字串: ";
    getline(cin, testStr);  // 支援空格的輸入

    s.Frequency(testStr);  // 呼叫 Frequency 函式
    return 0;
}

