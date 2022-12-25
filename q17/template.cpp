#include <bits/stdc++.h>
using namespace std;

void placeBar(vector<char> airMov, int &maxHeight, set<pair<int, int>> &grid, unsigned long long &iteration){
    bool canMoveDown = true;
    // place ####
    vector<pair<int, int>> piece = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0}
    };

    // apply transformations
    for(int i = 0; i < piece.size(); i++){
        piece[i].first += 2;
        piece[i].second += maxHeight + 3;
    }

    while(canMoveDown){
        int j = iteration % airMov.size();

        // check if piece will move left or right
        if(airMov[j] == '<' && piece[0].first != 0 && grid.find({piece[0].first - 1, piece[0].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first--;
            }
        }
        else if(airMov[j] == '>' && piece[3].first != 6 && grid.find({piece[3].first + 1, piece[3].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first++;
            }
        }

        // see if it can move down
        // check at position piece[1].second - 1, piece[4].second - 1 and piece[3].second - 1

        if( grid.find({piece[0].first, piece[0].second - 1}) != grid.end() || 
            grid.find({piece[1].first, piece[1].second - 1}) != grid.end() || 
            grid.find({piece[2].first, piece[2].second - 1}) != grid.end() || 
            grid.find({piece[3].first, piece[3].second - 1}) != grid.end() || 
            piece[1].second == 0){
            canMoveDown = false;
        }

        if(canMoveDown){
            for(int i = 0; i < piece.size(); i++){
                piece[i].second--;
            }
        }
        else{
            // place piece
            for(int i = 0; i < piece.size(); i++){
                grid.insert({piece[i].first, piece[i].second});
            }
            maxHeight = max(maxHeight, piece[0].second + 1);
        }
        iteration++;
    }
}
void placePlus(vector<char> airMov, int &maxHeight, set<pair<int, int>> &grid, unsigned long long &iteration){
    bool canMoveDown = true;
    // place .#.
    // place ###
    // place .#.

    vector<pair<int, int>> piece = {
        // top nub
                {1, 2},
        // middle bar
        {0, 1}, {1, 1}, {2, 1}, 
        // bottom nub
                {1, 0}
    };

    // apply transformations
    for(int i = 0; i < piece.size(); i++){
        piece[i].first += 2;
        piece[i].second += maxHeight + 3;
    }

    while(canMoveDown){
        int j = iteration % airMov.size();
        // place .#.
        // place ###
        // place .#.

        // check if piece will move left or right
        if(airMov[j] == '<' && piece[1].first != 0 && grid.find({piece[1].first - 1, piece[1].second}) == grid.end()
                            && piece[0].first != 0 && grid.find({piece[0].first - 1, piece[0].second}) == grid.end()
                            && piece[4].first != 0 && grid.find({piece[4].first - 1, piece[4].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first--;
            }
        }
        else if(airMov[j] == '>' && piece[0].first != 6 && grid.find({piece[0].first + 1, piece[0].second}) == grid.end()
                                 && piece[3].first != 6 && grid.find({piece[3].first + 1, piece[3].second}) == grid.end()
                                 && piece[4].first != 6 && grid.find({piece[4].first + 1, piece[4].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first++;
            }
        }

        // see if it can move down
        // check at position piece[1].second - 1, piece[4].second - 1 and piece[3].second - 1

        if( grid.find({piece[1].first, piece[1].second - 1}) != grid.end() || 
            grid.find({piece[4].first, piece[4].second - 1}) != grid.end() || 
            grid.find({piece[3].first, piece[3].second - 1}) != grid.end() || 
            piece[1].second - 1 == 0){
            canMoveDown = false;
        }

        if(canMoveDown){
            for(int i = 0; i < piece.size(); i++){
                piece[i].second--;
            }
        }
        else{
            // place piece
            for(int i = 0; i < piece.size(); i++){
                grid.insert({piece[i].first, piece[i].second});
            }
            maxHeight = max(maxHeight, piece[0].second + 1);
        }
        iteration++;
    }
}
void placeBackwardsL(vector<char> airMov, int &maxHeight, set<pair<int, int>> &grid, unsigned long long &iteration){
    bool canMoveDown = true;
    // place ..#
    // place ..#
    // place ###

    vector<pair<int, int>> piece = {
        // top
                        {2, 2},
        // middle
                        {2, 1}, 
        // bottom
        {0, 0}, {1, 0}, {2, 0}
    };

    // apply transformations
    for(int i = 0; i < piece.size(); i++){
        piece[i].first += 2;
        piece[i].second += maxHeight + 3;
    }

    while(canMoveDown){
        int j = iteration % airMov.size();

        // check if piece will move left or right
        if(airMov[j] == '<' && piece[2].first != 0 && grid.find({piece[2].first - 1, piece[2].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first--;
            }
        }
        else if(airMov[j] == '>' && piece[0].first != 6 && grid.find({piece[0].first + 1, piece[0].second}) == grid.end()
                                 && piece[1].first != 6 && grid.find({piece[1].first + 1, piece[1].second}) == grid.end()
                                 && piece[4].first != 6 && grid.find({piece[4].first + 1, piece[4].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first++;
            }
        }

        // see if it can move down
        // check at position piece[1].second - 1, piece[4].second - 1 and piece[3].second - 1
        if( grid.find({piece[2].first, piece[2].second - 1}) != grid.end() || 
            grid.find({piece[3].first, piece[3].second - 1}) != grid.end() || 
            grid.find({piece[4].first, piece[4].second - 1}) != grid.end() || 
            piece[2].second - 1 == 0){
            canMoveDown = false;
        }

        if(canMoveDown){
            for(int i = 0; i < piece.size(); i++){
                piece[i].second--;
            }
        }
        else{
            // place piece
            for(int i = 0; i < piece.size(); i++){
                grid.insert({piece[i].first, piece[i].second});
            }
            maxHeight = max(maxHeight, piece[0].second + 1);
        }
        iteration++;
    }
}
void placeStick(vector<char> airMov, int &maxHeight, set<pair<int, int>> &grid, unsigned long long &iteration){
    bool canMoveDown = true;
    // place #
    // place #
    // place #
    // place #

    vector<pair<int, int>> piece = {
        // top
        {0, 3},
        // top middle
        {0, 2},
        // bottom middle
        {0, 1},
        // bot
        {0, 0}
    };

    // apply transformations
    for(int i = 0; i < piece.size(); i++){
        piece[i].first += 2;
        piece[i].second += maxHeight + 3;
    }

    while(canMoveDown){
        int j = iteration % airMov.size();

        // check if piece will move left or right
        if(airMov[j] == '<' && piece[0].first != 0 && grid.find({piece[0].first - 1, piece[0].second}) == grid.end() 
                            && piece[1].first != 0 && grid.find({piece[1].first - 1, piece[1].second}) == grid.end()
                            && piece[2].first != 0 && grid.find({piece[2].first - 1, piece[2].second}) == grid.end()
                            && piece[3].first != 0 && grid.find({piece[3].first - 1, piece[3].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first--;
            }
        }
        else if(airMov[j] == '>' && piece[0].first != 6 && grid.find({piece[0].first + 1, piece[0].second}) == grid.end()
                                 && piece[1].first != 6 && grid.find({piece[1].first + 1, piece[1].second}) == grid.end()
                                 && piece[2].first != 6 && grid.find({piece[2].first + 1, piece[2].second}) == grid.end()
                                 && piece[3].first != 6 && grid.find({piece[3].first + 1, piece[3].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first++;
            }
        }

        // see if it can move down
        // check at position piece[1].second - 1, piece[4].second - 1 and piece[3].second - 1
        if( grid.find({piece[3].first, piece[3].second - 1}) != grid.end() || 
            piece[3].second - 1 == 0){
            canMoveDown = false;
        }

        if(canMoveDown){
            for(int i = 0; i < piece.size(); i++){
                piece[i].second--;
            }
        }
        else{
            // place piece
            for(int i = 0; i < piece.size(); i++){
                grid.insert({piece[i].first, piece[i].second});
            }
            maxHeight = max(maxHeight, piece[0].second + 1);
        }
        iteration++;
    }
}
void placeCube(vector<char> airMov, int &maxHeight, set<pair<int, int>> &grid, unsigned long long &iteration){
    bool canMoveDown = true;
    // place ##
    // place ##

    vector<pair<int, int>> piece = {
        // top
        {0, 1}, {1, 1},
        // bottom
        {0, 0}, {1, 0}
    };

    // apply transformations
    for(int i = 0; i < piece.size(); i++){
        piece[i].first += 2;
        piece[i].second += maxHeight + 3;
    }

    while(canMoveDown){
        int j = iteration % airMov.size();

        // check if piece will move left or right
        if(airMov[j] == '<' && piece[0].first != 0 && grid.find({piece[0].first - 1, piece[0].second}) == grid.end()
                            && piece[2].first != 0 && grid.find({piece[2].first - 1, piece[2].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first--;
            }
        }
        else if(airMov[j] == '>' && piece[1].first != 6 && grid.find({piece[1].first + 1, piece[1].second}) == grid.end()
                                 && piece[3].first != 6 && grid.find({piece[3].first + 1, piece[3].second}) == grid.end()){
            for(int i = 0; i<piece.size(); i++){
                piece[i].first++;
            }
        }

        // see if it can move down
        // check at position piece[1].second - 1, piece[4].second - 1 and piece[3].second - 1
        if( grid.find({piece[2].first, piece[2].second - 1}) != grid.end() || 
            grid.find({piece[3].first, piece[3].second - 1}) != grid.end() || 
            piece[2].second - 1 == 0){
            canMoveDown = false;
        }

        if(canMoveDown){
            for(int i = 0; i < piece.size(); i++){
                piece[i].second--;
            }
        }
        else{
            // place piece
            for(int i = 0; i < piece.size(); i++){
                grid.insert({piece[i].first, piece[i].second});
            }
            maxHeight = max(maxHeight, piece[0].second + 1);
        }
        iteration++;
    }
}

int main(){

    ifstream fin("input.txt");

    // change type here
    vector<char> airMov;
    int count;
    string line = "";

    while(getline(fin, line)){
        for(int i = 0; i < line.length(); i++){
            airMov.emplace_back(line[i]);
        }
    }

    int maxHeight = 0;
    int width = 7;

    set<pair<int, int>> grid;
    unsigned long long iterationWind = 0;
    unsigned long long blockCount = 0;

    unsigned long long blocksToAdd = ULONG_LONG_MAX;

    // hashmap of patterns
    unordered_map<string, pair<int, int>> patterns;

    while(blockCount < blocksToAdd){
        placeBar(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placePlus(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeBackwardsL(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeStick(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeCube(airMov, maxHeight, grid, iterationWind);
        blockCount++;

        string section1 = "";

        // save grid chunk (80 for robustness)
        for(int i = maxHeight-77; i < maxHeight; i++){
            for(int j = 0; j < width; j++){
                if(grid.find({j, i}) != grid.end()){
                    section1 += "#";
                }
                else{
                    section1 += ".";
                }
            }
        }

        // look up 
        if(patterns.find(section1) != patterns.end()){
            std::cout << "Found pattern! " << std::endl;
            std::cout << "current height: " << maxHeight << std::endl;
            std::cout << "pattern starts at height: " << patterns[section1].first << std::endl;
            std::cout << "pattern height: " << maxHeight - patterns[section1].first << std::endl;

            std::cout << "current block count: " << blockCount << std::endl;
            std::cout << "pattern started at block count: " << patterns[section1].second << std::endl;
            std::cout << "repeats every " << blockCount - patterns[section1].second << " blocks" << std::endl;

            // calculate by hand! no big int lol
            break;
        }

        patterns[section1] = {maxHeight, blockCount};
    }

    // my exact calculations
    // 10^12 blocks - 685 blocks = height where pattern starts
    // every 1705 blocks, the pattern repeats
    // repeats 586,510,263 times R 900 blocks
    // 586510263 cycles * 2649 pattern height = 1553665686687
    // 900 blocks still needed for my case = 1385 height
    // + initial height = 1083 height

    // 1083 + 1385 + 1553665686687 = 1553665689155 high!


    // just so happens that the pattern repeats every n*5 blocks so I can copy paste this
    int prevHeight = maxHeight;
    blocksToAdd = 900 + blockCount; // may be different for your output
    while(blockCount < blocksToAdd){
        placeBar(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placePlus(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeBackwardsL(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeStick(airMov, maxHeight, grid, iterationWind);
        blockCount++;
        if(blockCount >= blocksToAdd) break;

        placeCube(airMov, maxHeight, grid, iterationWind);
        blockCount++;
    }

     std::cout << "Additional Height: " << maxHeight - prevHeight << std::endl;

    return 0;
}