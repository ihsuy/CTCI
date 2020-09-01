#include <iostream>
#include <string>

using namespace std;

void swap(string& s, const int& i, const int& j) {
    auto temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void print_strPermuation(string& s, const int& b, const int& e) {
    if (b == e) {
        cout << s << endl;
    }

    for (auto i = b; i <= e; ++i) {
        swap(s, b, i);
        print_strPermuation(s, b + 1, e);
        swap(s, i, b);
    }
}

int main() {
    string mystr = "ABCD";
    print_strPermuation(mystr, 0, mystr.length() - 1);
    return 0;
}