#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string itobit(const int& num) {
    bitset<32> bs(num);
    return bs.to_string();
}

int btoi(const string& b) {
    bitset<32> bs(b);
    return bs.to_ulong();
}

int flipBitToWin(const int& num) {
    string n = itobit(num);

    bool seenFirstZero = false;
    int runningSum = 0;

    int max_val = 1;
    int prev = 0;
    int prev2 = 0;

    for (int i = 0; i < n.length(); ++i) {
        if (n[i] == '0' and not seenFirstZero) {
            seenFirstZero = true;
            prev2 = runningSum;
        } else if (n[i] == '0') {
            max_val = max(max_val, runningSum + 1 - prev);
            prev = prev2;
            prev2 = runningSum;
        } else {
            runningSum++;
        }

        if (i == n.length() - 1) {
            max_val = max(max_val, runningSum + 1 - prev);
        }
    }
    return max_val;
}

int main() {
    const string n = "101100111110101";
    cout << flipBitToWin(btoi(n)) << endl;
    return 0;
}

/*
#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string itobit(const int& num)
{
        bitset<32> bs(num);
        return bs.to_string();
}

int btoi(const string& b)
{
        bitset<32> bs(b);
        return bs.to_ulong();
}

int flipBitToWin(const int& num)
{
        vector<int> runningSums;
        int zeroCount = 0;
        int runningSum = 0;

        string n = itobit(num);


        for(int i = 0; i < n.length(); ++i)
        {
                if(n[i] == '0')
                {
                        zeroCount++;
                        runningSums.push_back(runningSum);
                }
                else
                {
                        runningSum++;
                }

                if(i == n.length()-1)
                {
                        runningSums.push_back(runningSum);
                }
        }

        int max_val = INT_MIN;

        for(int i = 0; i < zeroCount; ++i)
        {
                if(i == 0 and i != zeroCount-1)
                {
                        max_val = runningSums[i+1]+1;
                }
                else
                {
                        max_val = max(max_val,
runningSums[i+1]-runningSums[i-1]+1);
                }
        }

        return max_val;
}


int main()
{
        const string n = "11011101111";
        cout << flipBitToWin(btoi(n)) << endl;
        return 0;
}
*/