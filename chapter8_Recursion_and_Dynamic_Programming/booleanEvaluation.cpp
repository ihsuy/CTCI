#include <math.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
inline int two(int n) {
    return 1 << n;
}
inline int test(int n, int b) {
    return (n >> b) & 1;
}
inline void set_bit(int& n, int b) {
    n |= two(b);
}
inline void unset_bit(int& n, int b) {
    n &= ~two(b);
}
inline int last_bit(int n) {
    return n & (-n);
}
inline int ones(int n) {
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*

Boolean Evaluation: Given a boolean expression consisting
of the symbols e (false), 1 (true), & (AND), I (OR), and" (XOR),
and a desired boolean result value result, implement a function to
count the number of ways of parenthesizing the expression such
that it evaluates to result.
countEval("1^0|0|1" false) -> 2
*/

int booleanEvaluation_helper(const string& s,
                             const char& cur_val,
                             const int& front,
                             const bool& desiredValue) {
    if (front == s.length() - 1) {
        return ((s[front] - '0') == desiredValue);
    }

    int result = 0;

    char op = s[front + 1];  // next operator
    char front_val = s[front];
    cout << cur_val + s.substr(front + 1) << '\n';
    cout << "cur_val: " << cur_val << " front: " << front << " op: " << op
         << " dv: " << desiredValue << '\n';

    if (cur_val == '1') {
        if (op == '&') {
            result +=
                booleanEvaluation_helper(s, front_val, front + 2, desiredValue);
        } else if (op == '|' and desiredValue == true) {
            result += booleanEvaluation_helper(s, front_val, front + 2, 0);
            result += booleanEvaluation_helper(s, front_val, front + 2, 1);
        } else if (op == '^') {
            result += booleanEvaluation_helper(s, front_val, front + 2,
                                               not desiredValue);
        }
    } else {
        if (op == '&' and desiredValue == false) {
            result += booleanEvaluation_helper(s, front_val, front + 2, 0);
            result += booleanEvaluation_helper(s, front_val, front + 2, 1);
        } else if (op == '|') {
            result +=
                booleanEvaluation_helper(s, front_val, front + 2, desiredValue);
        } else if (op == '^') {
            result +=
                booleanEvaluation_helper(s, front_val, front + 2, desiredValue);
        }
    }
    cout << "result1: " << result << '\n';
    // get the result for the case when the
    // first operation is calculated first

    bool operand1 = s[front] - '0';
    bool operand2 = s[front + 2] - '0';
    bool temp_result;
    switch (op) {
        case '&':
            temp_result = operand1 & operand2;
            break;
        case '|':
            temp_result = operand1 | operand2;
            break;
        case '^':
            temp_result = operand1 ^ operand2;
            break;
        default:
            throw runtime_error("bad operator: " + string(1, op));
    }

    result +=
        booleanEvaluation_helper(s, temp_result + '0', front + 2, desiredValue);
    cout << "result2: " << result << '\n';
    return result;
}

int main() {
    string s = "1^0|0|1";
    // string s = "0&0&0&1^1|0";
    bool v = false;
    // bool v = true;
    cout << booleanEvaluation_helper(s, s[0], 0, v) << endl;

    return 0;
}
