#include <bits/stdc++.h>
using namespace std;


int main() {
    ifstream infile("input.txt");
    string line;
    vector<string> grid;
    while (getline(infile, line)) {
        grid.push_back(line);
    }

    set<pair<int,int>> elves;
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] == '#') {
                elves.insert({row,col});
            }
        }
    }

    vector<string> dirList = {"N", "E", "S", "W"};

    for (int t = 0; t < INT_MAX; t++) {
        bool hasMoved = false;
        map<pair<int,int>, vector<pair<int,int>>> proposals;

        for (auto pos : elves) {
            int row = pos.first;
            int col = pos.second;
            bool hasNeighbour = false;

            for (int dRow=-1; dRow<=1; dRow++) {
                for (int dCol=-1; dCol<=1; dCol++) {
                    if ((dRow!=0 || dCol!=0) && elves.count({row+dRow, col+dCol})) {
                        hasNeighbour = true;
                    }
                }
            }

            // no neighbour == no move
            if (!hasNeighbour) {
                continue;
            }

            // propose move
            bool moved = false;
            for (auto dir : dirList) {
                if (dir =="N" && !moved && !elves.count({row-1,col}) && !elves.count({row-1,col-1}) && !elves.count({row-1,col+1})) {
                    proposals[{row-1,col}].push_back({row,col});
                    moved = true;
                } else if (dir == "E" && !moved && !elves.count({row+1,col}) && !elves.count({row+1,col-1}) && !elves.count({row+1,col+1})) {
                    proposals[{row+1,col}].push_back({row,col});
                    moved = true;
                } else if (dir == "S" && !moved && !elves.count({row,col-1}) && !elves.count({row-1,col-1}) && !elves.count({row+1,col-1})) {
                    proposals[{row,col-1}].push_back({row,col});
                    moved = true;
                } else if (dir == "W" && !moved && !elves.count({row,col+1}) && !elves.count({row-1,col+1}) && !elves.count({row+1,col+1})) {
                    proposals[{row,col+1}].push_back({row,col});
                    moved = true;
                }
            }
        }

        std::rotate(dirList.begin(), dirList.begin()+1, dirList.end());

        for (auto propose : proposals) {
            pair<int,int> dest = propose.first;
            vector<pair<int,int>> vectorOfSources = propose.second;

            if (vectorOfSources.size() == 1) {
                hasMoved = true;
                elves.erase(vectorOfSources[0]);
                elves.insert(dest);
            }
        }

        // pt 1
        if (t==9) {
            int rowMin = min_element(elves.begin(), elves.end())->first;
            int rowMax = max_element(elves.begin(), elves.end())->first;
            int colMin = min_element(elves.begin(), elves.end(), [](auto a, auto b) { return a.second < b.second; })->second;
            int colMax = max_element(elves.begin(), elves.end(), [](auto a, auto b) { return a.second < b.second; })->second;
            int ans = 0;

            for (int row = rowMin; row <= rowMax; row++) {
                for (int col = colMin; col <= colMax; col++) {
                    if (!elves.count({row,col})) {
                        ans += 1;
                    }
                }
            }
            cout << ans << endl;
        }

        // pt2
        if (!hasMoved) {
            cout << t+1 << endl;
            break;
        }
    }
}

