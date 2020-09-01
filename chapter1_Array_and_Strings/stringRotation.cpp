/*
String Rotation:
assume you have a method isSubstring which checks if one word
is a substring of another. Given two string s1 and s2 write code to
check if s2 is a rotation s1 using only 1 call to isSubstring
*/

#include <iostream>
#include <string>

using namespace std;

bool isSubstring(const string& a, const string& b) {
    // implemented

    return true;
}

bool isRotation(const string& s1, const string& s2) {
    string db;
    db.reserve(s1.length() + s2.length());
    db += s1;
    db += s1;
    if (isSubstring(db, s2)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    cout << "Enter 2 strings two check if they are rotation of each other:"
         << endl;
    cout << ">> ";
    string s1, s2;
    cin >> s1 >> s2;
    // assume s1 and s2 is checked to be substring of each other
    if (isRotation(s1, s2)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}