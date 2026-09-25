#include <iostream>
#include <string>
using namespace std;

class String {
public:
    static string CharDelete(const string& input, char c) {
        string result = "";
        for (char ch : input) {
            if (ch != c) {
                result += ch;
            }
        }
        return result;
    }
};

int main() {
    string input;
    char c;

    cout << "輸入字串: ";
    getline(cin, input);
    cout << "輸入要刪除的字元: ";
    cin >> c;

    string output = String::CharDelete(input, c);
    cout << "刪除後的字串: " << output << endl;

    return 0;
}

