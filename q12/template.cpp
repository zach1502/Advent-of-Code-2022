#include <bits/stdc++.h>
using namespace std;

struct position{
    int x;
    int y;
};

int main(){
    ifstream fin("input.txt");

    // change type here
    vector<vector<char>> v;
    string str = "";
    long long sum = 0;
    long long max = -1;

    position start;
    position end;


    string line = "";
    while(getline(fin, line)){
        vector<char> vect;
        for(int i = 0; i < line.length(); i++){
            vect.push_back(line[i]);
        }

        v.push_back(vect);
    }

    std::cout << sum << std::endl;

    return 0;
}