#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");
    string line;
    set<pair<int,int>> walls;
    set<tuple<int,int,int,int>> blizzards;
    int x = 0, y = 0;
    while(getline(fin, line)){
        for(char c : line){
            if(c == '#') walls.    insert({x-1, y-1});
            if(c == '>') blizzards.insert({x-1, y-1,  1,  0});
            if(c == '<') blizzards.insert({x-1, y-1, -1,  0});
            if(c == '^') blizzards.insert({x-1, y-1,  0, -1});
            if(c == 'v') blizzards.insert({x-1, y-1,  0,  1});
            x++;
        }
        y++;
        x=0;
    }
    
    int X = max_element(walls.begin(), walls.end())->first;
    int Y = max_element(walls.begin(), walls.end())->second;
    cout << "maze size: " << X << "x" << Y << ", " << walls.size() << " walls, " << blizzards.size() << " blizzards" << endl;

    // contain the player
    for(int i = -1; i < 3; i++) walls.insert({i, -2});
    for(int i = X-3; i < X+2; i++) walls.insert({i, Y+1});

    pair<int,int> start = {0, -1};
    pair<int,int> exit = {X-1, Y};
    vector<pair<int,int>>moves = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
        {0, 0}
    };
    
    int t = 0;
    set<pair<int,int>> q = {start};
    vector<pair<int,int>> goals = {exit, start, exit};

    while(!goals.empty()){
        t++;
        set<pair<int,int>> currBlizz;
        for(auto blizz : blizzards){
            int startingLocationX = get<0>(blizz);
            int startingLocationY = get<1>(blizz);
            int dx = get<2>(blizz);
            int dy = get<3>(blizz);

            int blizzX = (px + t * dx) % X;
            int blizzY = (py + t * dy) % Y;

            if(blizzX < 0) blizzX += X;
            if(blizzY < 0) blizzY += Y;

            currBlizz.insert({blizzX, blizzY});
        }

        // add moves for all moves in q
        set<pair<int,int>> n;
        for(auto move : moves){
            int dx = move.first;
            int dy = move.second;

            for(auto qMoves : q){
                n.insert({qMoves.first + dx, qMoves.second + dy});
            }
        }

        // q = n - currBlizz - walls
        // remove all moves that well be blocked by blizzards or walls
        q=n;
        for(auto blizz : currBlizz) {
            int bx = blizz.first;
            int by = blizz.second;
            q.erase({bx, by});
        }

        for(auto wall : walls) {
            int wx = wall.first;
            int wy = wall.second;
            q.erase({wx, wy});
        }
        
        // cout << t << " " << q.size() << " " << goals[0].first << " " << goals[0].second << endl;
        if(q.find(goals[0]) != q.end()){
            cout << "goal " << goals[0].first << " " << goals[0].second << " reached after " << t << " steps" << endl;
            
            // reset the queue
            q.clear();
            n.clear();

            // new destination
            q = {goals[0]};
            goals.erase(goals.begin());
        }
    }
}
