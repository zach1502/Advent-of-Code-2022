#include <bits/stdc++.h>
using namespace std;

struct position {
    int x;
    int y;

    position(){
        this->x = 0;
        this->y = 0;
    }

    position(int x, int y){
        this->x = x;
        this->y = y;
    }

    string str() const {
        return to_string(this->x) + " " + to_string(this->y);
    }
};

position moveTail(position H, position T){
    int dr = H.x - T.x;
    int dc = H.y - T.y;

    if (abs(dr) <= 1 && abs(dc) <= 1) return T;

    if (abs(dr) >= 2){
        T.x = (T.x < H.x) ? H.x-1 : H.x+1;
    }
    if (abs(dc) >= 2){
        T.y = (T.y < H.y) ? H.y-1 : H.y+1;
    }

    return T;
}

int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<vector<bool>> v;
    long long sum = 0;

    position H = position(0, 0);
    position* T = new position[9];
    for(int i = 0; i < 9; i++){
        T[i] = position(0, 0);
    }

    map<string, int> row = {
        {"L", 0},
        {"U", -1},
        {"R", 0},
        {"D", 1}
    };
    map<string, int> col = {
        {"L", -1},
        {"U", 0},
        {"R", 1},
        {"D", 0}
    };

    set<string> part1;
    set<string> part2;

    part1.insert(T[0].str());
    part2.insert(T[8].str());

    string line = "";
    while(getline(fin, line)){
        // delimit line by spaces
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ' ')){
            tokens.push_back(token);
        }
        ss.clear();

        // DIR Number
        string dir = tokens[0];
        int num = atoi(tokens[1].c_str());

        for(int i = 0; i < num; i++){
            H.x = H.x + row[dir];
            H.y = H.y + col[dir];
            T[0] = moveTail(H, T[0]);

            for(int i = 1; i < 9; i++){
                T[i] = moveTail(T[i-1], T[i]);
            }

            part1.insert(T[0].str());
            part2.insert(T[8].str());
        }
    }

    std::cout << "Part 1: " << part1.size() << std::endl;
    std::cout << "Part 2: " << part2.size() << std::endl;
    
    return 0;
}