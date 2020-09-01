/*
Is Unique: Implement an Algorithm to determine if a string
has all unique characters. What if you cannot use additional
data structures?
*/
#include <iostream>
#include <string>
using namespace std;

bool isUnique(const string& s) {
    // there are total of 128 char
    const int max_ch = 128;

    // if the string is longer than 128
    // there must be at least 1 repeated entry
    if (s.length() > max_ch) {
        return false;
    }

    // use an array of boolean to make char_map as
    // small as possible, since we only need each
    // slot of it to hold 2 values.
    bool char_map[max_ch] = {0};

    for (auto& ch : s) {
        if (char_map[(int)ch]) {
            return false;
        }

        char_map[(int)ch] = true;
    }
    return true;
}

int main() {
    string my_str;

    cout << "Enter your string: ";

    getline(cin, my_str);

    if (isUnique(my_str)) {
        cout << "Your string is composed of only unique characters!" << endl;
    } else {
        cout << "Your string contains repeated characters!" << endl;
    }

    return 0;
}