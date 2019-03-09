#include <iostream>
#include <map>
#include <string>
using namespace std;

void init_map(map<char, int>& m, const string& s)
{
    for(int i = 'a'; i <= 'z'; ++i)
    {
        m[char(i)] = 0;
    }
    for(auto ch : s)
    {
        m[ch] ++;
    }
}

void reset_map(map<char, int>& m)
{
    for(auto& item : m)
    {
        item.second = 0;
    }
}

void shortInLong(const string& l, const string& s)
{
    auto lenl = l.length();
    auto lens = s.length();
    // check for invalid input
    if(lenl < lens)
    {
        cout << "bad input" << endl;
        return;
    }
    
    // prepare containers
    map<char, int> inS;
    map<char, int> inL;
    
    init_map(inS, s);
    init_map(inL, "");
    
    
    for(auto i = 0; i < lenl-lens+1; ++i)
    {
        int counter = 0;
        string ans;
        for(auto j = i; j < i+lens; ++j)
        {
            if(inS[l[j]] != 0)
            {
                inL[l[j]]++;
                counter++;
                ans += l[j];
            }
            else
            {
                reset_map(inL);
                i += counter;
                counter = 0;
                ans = "";
                break;
            }
            
            if(inL[l[j]] > inS[l[j]])
            {
                reset_map(inL);
                counter = 0;
                ans = "";
                break;
            }
            
            if(counter == lens)
            {
                cout << ans << " at " << i << endl;
                reset_map(inL);
                counter = 0;
                ans = "";
            }
        }
    }
}

int main(){
    string L = "cbabadcbbabbcbabaabccbabc";
    string s = "abbc";
    shortInLong(L, s);
    return 0;
}

/*
 However, since im shifting the window one position by one postion
 I didn't need to check the whole windowed substring for letter frequence
 instead, i could have decrement the one element that left the window
 and increment the 1 element newly included in the window.
 */
