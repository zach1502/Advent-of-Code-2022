#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.txt");
    string line;
    set<vector<int>> P;

    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> p;
        int x;
        while (ss >> x) {
            p.push_back(x);
            if (ss.peek() == ',') ss.ignore();
        }
        P.insert(p);
    }

    int sa = 0;
    for (auto p : P) {
        for (int axis = 0; axis < 3; ++axis) {
            for (int d = -1; d <= 1; d += 2) {
                vector<int> q = p;
                q[axis] += d;
                if (P.count(q) == 0) ++sa;
            }
        }
    }
    cout << sa << endl;

    // bounds 
    vector<int> P_min(3, INT_MAX);
    vector<int> P_max(3, INT_MIN);
    for (auto p : P) {
        for (int axis = 0; axis < 3; ++axis) {
            P_min[axis] = min(P_min[axis], p[axis]);
            P_max[axis] = max(P_max[axis], p[axis]);
        }
    }

    for (int axis = 0; axis < 3; ++axis) {
        --P_min[axis];
        ++P_max[axis];
    }

    vector<vector<int>> stack = {P_min};
    set<vector<int>> visited;
    sa = 0;
    while (!stack.empty()) {
        auto p = stack.back();
        stack.pop_back();

        if (visited.count(p)) continue;
        visited.insert(p);
        
        for (int axis = 0; axis < 3; ++axis) {
            for (int d = -1; d <= 1; d += 2) {
                vector<int> q = p;
                q[axis] += d;

                if (P.count(q)) ++sa;
                if (P.count(q) == 0 && visited.count(q) == 0) {
                    bool ok = true;

                    for (int axis = 0; axis < 3; ++axis) {
                        if (q[axis] < P_min[axis] || q[axis] > P_max[axis]) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) stack.push_back(q);
                }
            }
        }
    }

    cout << sa << endl;
}
