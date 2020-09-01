#include <bitset>
#include <iostream>

using namespace std;

string binaryToString(const double& n)  // num is from (0,1) both side exclusive
{
    if (n >= 1 or n <= 0) {
        return "ERROR";
    }

    const int width = 32;
    string result;
    result.reserve(width);
    double num = n;

    while (result.length() <= width) {
        if (num == 0) {
            break;
        }

        num *= 2;
        if (num >= 1) {
            result += "1";
            num -= 1;
        } else {
            result += "0";
        }
    }

    int diff = width - result.length();
    if (diff < 0) {
        return "ERROR";
    } else if (diff == 0) {
        return result;
    } else {
        while (result.length() < width) {
            result += "0";
        }
        return result;
    }
}

int main() {
    cout << binaryToString(0.72) << endl;
    return 0;
}