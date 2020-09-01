#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

struct hanoiTower {
    static int towerCount;

    stack<int> tower;

    int towerName;
    int disk_count;

    hanoiTower(const int& nd) : towerName(towerCount + 1), disk_count(0) {
        if (towerCount != 0) {
            throw runtime_error(
                "Can't create more than one hanoiTower with disks");
        } else {
            towerCount++;
            for (int i = nd; i > 0; --i) {
                tower.push(i);
                disk_count++;
            }
        }
    }

    hanoiTower() : towerName(towerCount + 1) {
        towerCount++;
        if (towerCount > 3) {
            throw runtime_error("Can't create more than 3 hanoiTowers");
        }
    }

    bool addDisk(const int& disk) {
        if (tower.size() == 0 or tower.top() > disk) {
            tower.push(disk);
            disk_count++;
            return true;
        } else {
            cout << "Trying to add " << disk << " to tower#" << towerName
                 << " top: " << tower.top()
                 << "\nfail to add a smaller disk on top of a bigger disk\n";
            return false;
        }
    }

    int getTopDisk() {
        if (tower.size() == 0) {
            cout << "Trying to get disk from tower#" << towerName << " size "
                 << 0 << "\nfail to get disk from an empty tower\n";
            return -1;
        }

        int topDisk = tower.top();
        tower.pop();
        disk_count--;
        return topDisk;
    }

    int size() const { return disk_count; }
};

struct towersOfHanoi {
    const int n_disks;

    hanoiTower t1;
    hanoiTower t2;
    hanoiTower t3;

    unordered_map<int, hanoiTower*> towers;

    towersOfHanoi(const int& n) : n_disks(n), t1(n), t2{}, t3{} {
        towers[1] = &t1;
        towers[2] = &t2;
        towers[3] = &t3;
    }

    int size() const { return n_disks; }

    void shift(const int& i1, const int& i2) {
        towers[i2]->addDisk(towers[i1]->getTopDisk());
    }

    void visualize() {
        stack<int> s1 = t1.tower;
        stack<int> s2 = t2.tower;
        stack<int> s3 = t3.tower;
        vector<int> buffer;
        cout << "===========\n";

        cout << '|';
        while (s1.size() != 0) {
            buffer.insert(buffer.begin(), s1.top());
            s1.pop();
        }
        for (int i = 0; i < buffer.size(); ++i) {
            cout << buffer[i] << '-';
        }
        cout << '\n';

        buffer = vector<int>();
        cout << '|';
        while (s2.size() != 0) {
            buffer.insert(buffer.begin(), s2.top());
            s2.pop();
        }
        for (int i = 0; i < buffer.size(); ++i) {
            cout << buffer[i] << '-';
        }
        cout << '\n';

        buffer = vector<int>();
        cout << '|';
        while (s3.size() != 0) {
            buffer.insert(buffer.begin(), s3.top());
            s3.pop();
        }
        for (int i = 0; i < buffer.size(); ++i) {
            cout << buffer[i] << '-';
        }
        cout << '\n';
    }
};

int hanoiTower::towerCount = 0;

void hanoiSolver_helper(towersOfHanoi& toh,
                        const int& ori,
                        const int& tar,
                        const int& n,
                        int& count,
                        const bool& visual) {
    int buffer_tower = 6 - ori - tar;

    if (n == 1) {
        toh.shift(ori, tar);
        if (visual) {
            toh.visualize();
        }
        count++;
    } else {
        hanoiSolver_helper(toh, ori, buffer_tower, n - 1, count, visual);
        hanoiSolver_helper(toh, ori, tar, 1, count, visual);
        hanoiSolver_helper(toh, buffer_tower, tar, n - 1, count, visual);
    }
}

void hanoiSolver(towersOfHanoi& toh, const bool& visual) {
    int count = 0;
    hanoiSolver_helper(toh, 1, 3, toh.size(), count, visual);
    cout << "num of step: " << count << endl;
}

int main() try {
    towersOfHanoi toh(2);

    const bool visualize = false;

    hanoiSolver(toh, visualize);
    return 0;
} catch (runtime_error& er) {
    cout << er.what() << endl;
}