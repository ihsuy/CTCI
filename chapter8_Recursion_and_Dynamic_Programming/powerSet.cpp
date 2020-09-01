#include <iostream>
#include <vector>

void printv(std::vector<int>::const_iterator b,
            std::vector<int>::const_iterator e) {
    std::cout << "{";
    while (b != e) {
        std::cout << *b << ',';
        b++;
        if (b == e) {
            std::cout << '\b';
        }
    }
    std::cout << "}";
}

std::vector<std::vector<int>> powerSet(std::vector<int>& mySet) {
    if (mySet.size() == 0) {
        return std::vector<std::vector<int>>();
    } else if (mySet.size() == 1) {
        return std::vector<std::vector<int>>({mySet, std::vector<int>()});
    } else {
        std::vector<std::vector<int>> result;
        int tail = mySet.back();

        mySet.pop_back();

        std::vector<std::vector<int>> prev_result = powerSet(mySet);

        result = prev_result;

        for (int i = 0; i < prev_result.size(); ++i) {
            prev_result[i].push_back(tail);
        }

        result.insert(result.begin(), prev_result.begin(), prev_result.end());

        return result;
    }
}

void show_powerSet(const std::vector<std::vector<int>>& ps) {
    std::cout << "{";
    for (int i = 0; i < ps.size(); ++i) {
        printv(ps[i].begin(), ps[i].end());
        if (i != ps.size() - 1) {
            std::cout << ',';
        }
    }
    std::cout << "}\n";
}

int main() {
    std::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<std::vector<int>> ps = powerSet(a);

    show_powerSet(ps);

    // auto aite = a.begin();
    // a.insert(aite, b.begin(), b.end());
    // printv(a.begin(), a.end());
    // for(auto item:a)
    // {
    // 	std::cout << item << " ";
    // }
    // std::cout << '\n';

    return 0;
}