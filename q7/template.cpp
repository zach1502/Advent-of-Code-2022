#include <bits/stdc++.h>
using namespace std;

int recur1(ifstream &f, int &total, vector<int> &sizes){
    int acc = 0;
    string line = "";
    while (getline(f, line) && line != "$ cd .."){
        if (isdigit(line[0])){
            acc += atoi(line.c_str());
            continue;
        }
        if (line[0] == '$' && line[2] == 'c'){
            acc += recur1(f, total, sizes);
            continue;
        }
    }

    if (acc < 100000){
        total += acc;
    }

    sizes.push_back(acc);
    return acc;
}

int main(){
    ifstream f("input.txt");
    int total = 0;
    vector<int> sizes;
    int accum = recur1(f, total, sizes);
    int smallest_to_delete = 0;
    
    if (accum > 40000000) {
        int must_free = accum - 40000000;
        sort(sizes.begin(), sizes.end());
        smallest_to_delete = sizes[lower_bound(sizes.begin(), sizes.end(), must_free) - sizes.begin()];
    }
    cout << "pt 1: " << total << endl;
    cout << "pt 2: " << smallest_to_delete << endl;
}