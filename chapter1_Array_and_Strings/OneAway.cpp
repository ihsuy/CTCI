/*
There are 3 types of edits that can be performed on strings:
insert a character remove a character, or replace a character.
Given two strings, write a function to check if they are one
edit away.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool isOneAway(const string& s1, const string& s2) {
    int len1 = s1.length(), len2 = s2.length();

    if (abs(len1 - len2) > 1) {
        return false;
    }

    string s, l;

    if (len1 > len2) {
        s = s2;
        l = s1;
    } else {
        s = s1;
        l = s2;
    }

    bool isEdited = false;

    for (int i = 0, j = 0; i < s.length();) {
        if (s[i] != l[j]) {
            if (isEdited) {
                return false;
            }

            isEdited = true;

            if (len1 != len2) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++, j++;
        }
    }

    return true;
}

int main() {
    string s1, s2;
    cout << "Enter 2 strings two check if their edit distance is 0 or 1\n";
    cout << "String 1: ";
    cin >> s1;
    cout << "String 2: ";
    cin >> s2;
    cout << isOneAway(s1, s2) << endl;
    return 0;
}