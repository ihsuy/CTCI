#include <bitset>
#include <iostream>
#include <string>
using namespace std;

string itobit(const int& num) {
    bitset<16> bs(num);
    return bs.to_string();
}

bool getBit(const int& num, const int& loc) {
    /*
    Gets the git value at loc-th position

    create a mask that has 1 on the loc-th location,
    and has 0 on all other positions.
    performing bitwise AND with the original num will
    clear every bit except the loc-th bit whose value will be 1 if
    the original value at this position was 1 and 0 otherwise.

    since the value of a bit string of all zeros is 0,
    we could check result's value to see if its 0 to know the value at location
    loc.
    */
    return (((1 << loc) & num) != 0);
}

int setBit(const int& num, const int& loc) {
    /*
    Set loc-th bit to 1

    Create a mask that has 1 on the loc-th position and 0s elsewhere,
    apply the mask to num with bitwise OR will force num's loc-th position
    to be set to 1, and maintain bit values at all other positions
    */
    return ((1 << loc) | num);
}

int clearBit(const int& num, const int& loc) {
    /*
    Set loc-th bit to 0

    Create a mask that has 0 on the loc-th position and 1s elsewhere
    do bitwise AND operation on mask and num will preserve bit values at
    all locations except the one at loc-th which will be set to 0
    */
    return (~(1 << loc) & num);
}

int clearBitsMSBthroughLOC(const int& num, const int& loc) {
    /*
    Set every bit from the left most bit to the loc-th bit to 0

    for example:
            clearBitsMSBthroughLOC(b"1000111011101111", 8)
            will yield:              0000000011101111

    In order to do this:
    we create a mask like this:
    mask:   0000000011111111
                              AND
    num:    1000111011101111
    result: 0000000011101111

    0000000011111111 can be generated by first shifting 1 << 8
    which creates 000000010000000, and subtract 1 from it
    */
    return (((1 << loc) - 1) & num);
}

int clearBitsLOCthrough0(const int& num, const int& loc) {
    /*
    Clear all bit from the loc-th postion to the right most position(0-th)
    for num: 1000111011101111 and loc = 8
    mask:	 1111111000000000
    will produce the result
    the mask can be created by shifting -1 to the loc+1 the position
    */
    return ((-1 << (loc + 1)) & num);
}

int main() {
    int test_value = 399;
    cout << itobit(test_value) << endl;
    cout << getBit(test_value, 1) << endl;
    cout << itobit(setBit(test_value, 10)) << endl;
    cout << itobit(clearBit(test_value, 0)) << endl;
    cout << itobit(clearBitsMSBthroughLOC(test_value, 15)) << endl;
    cout << itobit(clearBitsLOCthrough0(test_value, 3)) << endl;
    return 0;
}