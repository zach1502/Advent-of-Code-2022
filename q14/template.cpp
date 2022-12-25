#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    string line = "";
    long long sum = 0;
    long long max = -1;

    vector<pair<int,int>> points;
    set<pair<int, int>> blocked;

    while(getline(fin, line)){
        // 481,122 -> 481,125 -> 476,125 -> 476,129 -> 491,129 -> 491,125 -> 485,125 -> 485,122
        // 475,119 -> 475,113 -> 475,119 -> 477,119 -> 477,113 -> 477,119 -> 479,119 -> 479,114 -> 479,119 -> 481,119 -> 481,115 -> 481,119 -> 483,119 -> 483,113 -> 483,119
        // 489,148 -> 493,148
        // 471,152 -> 475,152

        // split line into tokens
        stringstream ss(line);
        string token = "";
        vector<string> tokens;
        while(getline(ss, token, ' ')){
            tokens.push_back(token);
        }

        for(int i = 0; i < tokens.size(); i+=2){
            // split token into x and y
            stringstream ss2(tokens[i]);
            string token2 = "";
            vector<string> tokens2;
            while(getline(ss2, token2, ',')){
                tokens2.push_back(token2);
            }

            int x = stoi(tokens2[0]);
            int y = stoi(tokens2[1]);

            points.push_back(make_pair(x, y));
        }

        pair<int, int> from = points[0];
        // fill cave with #s
        for(int i = 1; i < points.size(); i++){
            pair<int, int> to = points[i];

            // either x and y are guarenteed to be the same
            // figure out if x or y is the same
            if(from.first == to.first){
                // x is the same
                // y is the variable
                int smallY = min(from.second, to.second);
                int bigY = (smallY == from.second) ? to.second : from.second;

                for(int j = smallY; j <= bigY; j++){
                    blocked.insert(make_pair(from.first, j));
                }

            } else {
                // y is the same
                // x is the variable
                int smallX = min(from.first, to.first);
                int bigX = (smallX == from.first) ? to.first : from.first;
                
                for(int j = smallX; j <= bigX; j++){
                    blocked.insert(make_pair(j, from.second));
                }
            }

            from = to;
        }

        points.clear();
    }

    // print points
    std::cout << "Points:" << std::endl;
    for(int i = 0; i < points.size(); i++){
        std::cout << points[i].first << "," << points[i].second << std::endl;
    }

    // find the largest y in the set
    int floor = 0;
    for(auto it = blocked.begin(); it != blocked.end(); it++){
        if(it->second > floor){
            floor = it->second;
        }
    }

    floor += 2;
    // create a floor from x=0 -> 750
    for(int i = 0; i <= 750; i++){
        blocked.insert(make_pair(i, floor));
    }

    // sand spawns at 500,0
    // sand falls until it hits a wall or another sand
    // sand can flow left or right if it hits a wall. it will try to flow left first.
    // if it cannot flow left or right, it will stop. Add to list of blocked.

    // while 500, 0 is not in blocked 
    bool isDone = false;
    while(blocked.find(make_pair(500, 0)) == blocked.end()){
        // sand falls
        // if sand hits a wall, it will flow left or right
        // if sand hits another sand, it will flow left or right
        int x = 500;
        int y = 0;

        while(true){
            pair<int, int> below = make_pair(x, y+1);

            if(blocked.find(below) == blocked.end()){
                // sand falls
                y++;
            } else {
                // sand hits a wall or another sand
                // sand will flow left or right
                pair<int, int> left = make_pair(x-1, y+1);
                pair<int, int> right = make_pair(x+1, y+1);

                if(blocked.find(left) == blocked.end()){
                    // sand flows left
                    y++;
                    x--;
                } else if(blocked.find(right) == blocked.end()){
                    // sand flows right
                    y++;
                    x++;
                } else {
                    // sand cannot flow left or right
                    // sand stops
                    blocked.insert(make_pair(x, y));
                    sum++;
                    break;
                }
            }

            // below the max y value
            // would cause infinite loop
            if(y > floor){
                isDone = true;
                break;
            }
        }

        if(isDone){
            break;
        }
    }

    std::cout << sum << std::endl;
    // print full cave
    for(int i = 0; i <= floor; i++){
        for(int j = 0; j <= 750; j++){
            if(blocked.find(make_pair(j, i)) == blocked.end()){
                std::cout << ".";
            } else {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }


    return 0;
}