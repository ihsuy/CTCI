#include <iostream>
using namespace std;

long recursiveMultiply_helper(const long& n1, long& counter) {
    if (counter == 0) {
        return 0;
    }

    return n1 + recursiveMultiply_helper(n1, --counter);
}

long recursiveMultiply(const long& n1, const long& n2) {
    long counter = n2;
    return recursiveMultiply_helper(n1, counter);
}

long bitmanipMultiply(const long& n1, const long& n2) {
    long result = 0;

    for (long temp1 = (n1 << 1), count = 0; (temp1 = temp1 >> 1); ++count) {
        if (temp1 & 1) {
            result += (n2 << count);
        }
    }

    return result;
}

int main() {
    const int n1 = 0;
    const int n2 = 1;
    int n3 = 100;

    // cout << recursiveMultiply(n1, n2) << endl;
    cout << bitmanipMultiply(n1, n2) << endl return 0;
}