#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, char> dirsLu = {
    // y, x
    {{0, 1}, 'R'},
    {{1, 0}, 'D'},
    {{0, -1}, 'L'},
    {{-1, 0}, 'U'}
};

vector<pair<int, int>> dirs = {
    // y, x
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

vector<vector<char>> copyGrid;

pair<int, int> rotate( pair<int, int> dir, char turn) {
    // look up dirs
    int index = 0;
    for(int i = 0; i < dirs.size(); i++) {
        if(dirs[i] == dir) {
            index = i;
            break;
        }
    }

    if(turn == 'R'){
        return dirs[(index+1) % 4];
    }
    else if(turn == 'L') {
        int newIndex = (index-1) % 4;
        if(newIndex < 0) newIndex += 4;
        return dirs[newIndex];
    }
    else{
        exit(-1);
    }
}

pair<pair<int, int>, pair<int, int>> nextPosition(vector<vector<char>> grid, pair<int, int> currPos, pair<int, int> dir) {
    int m = grid.size();
    int n = grid[0].size();

    copyGrid[currPos.first][currPos.second] = dirsLu[dir];
    pair<int, int> nextPosition = make_pair(currPos.first + dir.first, currPos.second + dir.second);
    nextPosition.first = nextPosition.first % m;
    nextPosition.second = nextPosition.second % n;

    if(nextPosition.first < 0) nextPosition.first += m;
    if(nextPosition.second < 0) nextPosition.second += n;

    // // pt 1
    // while(grid[nextPosition.first][nextPosition.second] == ' '){
        // nextPosition.first = nextPosition.first + dir.first;
        // nextPosition.second = nextPosition.second + dir.second;

        // nextPosition.first = nextPosition.first % m;
        // nextPosition.second = nextPosition.second % n;

        // if(nextPosition.first < 0) nextPosition.first += m;
        // if(nextPosition.second < 0) nextPosition.second += n;
    // }

    if(grid[nextPosition.first][nextPosition.second] == ' '){
        int rowSectionOffset = currPos.first % 50;
        int colSectionOffset = currPos.second % 50;

        int rowSection = currPos.first / 50;
        int colSection = currPos.second / 50;

        char direction = dirsLu[dir];

        pair<int, int> newPosition;
        pair<int, int> newDir;

        if (rowSection == 0 && colSection == 1 && direction == 'U') {
            newPosition = {150 + colSectionOffset, 0};
            newDir = {0, 1};
        } else if (rowSection == 3 && colSection == 0 && direction == 'L') {
            newPosition = {0, 50 + rowSectionOffset};
            newDir = {1, 0};
        } else if (rowSection == 0 && colSection == 1 && direction == 'L') {
            newPosition = {149 - rowSectionOffset, 0};
            newDir = {0, 1};
        } else if (rowSection == 2 && colSection == 0 && direction == 'L') {
            newPosition = {49 - rowSectionOffset, 50};
            newDir = {0, 1};
        } else if (rowSection == 1 && colSection == 1 && direction == 'L') {
            newPosition = {100, rowSectionOffset};
            newDir = {1, 0};
        } else if (rowSection == 2 && colSection == 0 && direction == 'U') {
            newPosition = {50 + colSectionOffset, 50};
            newDir = {0, 1};
        } else if (rowSection == 0 && colSection == 2 && direction == 'U') {
            newPosition = {199, colSectionOffset};
            newDir = {-1, 0};
        } else if (rowSection == 3 && colSection == 0 && direction == 'D') {
            newPosition = {0, 100 + colSectionOffset};
            newDir = {1, 0};
        } else if (rowSection == 0 && colSection == 2 && direction == 'R') {
            newPosition = {149 - rowSectionOffset, 99};
            newDir = {0, -1};
        } else if (rowSection == 2 && colSection == 1 && direction == 'R') {
            newPosition = {49 - rowSectionOffset, 149};
            newDir = {0, -1};
        } else if (rowSection == 0 && colSection == 2 && direction == 'D') {
            newPosition = {50 + colSectionOffset, 99};
            newDir = {0, -1};
        } else if (rowSection == 1 && colSection == 1 && direction == 'R') {
            newPosition = {49, 100 + rowSectionOffset};
            newDir = {-1, 0};
        } else if (rowSection == 2 && colSection == 1 && direction == 'D') {
            newPosition = {150 + colSectionOffset, 49};
            newDir = {0, -1};
        } else if (rowSection == 3 && colSection == 0 && direction == 'R') {
            newPosition = {149, 50 + rowSectionOffset};
            newDir = {-1, 0};
        } else {
            throw std::invalid_argument("Invalid input");
        }

        return {newPosition, newDir};
    }

    // not looping back to 0
    return {nextPosition, dir};
}


int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<vector<char>> grid;
    string str = "";
    long long sum = 0;
    long long max = -1;

    stringstream ss;
    string line = "";

    while(getline(fin, line)){
        vector<char> tmp;
        
        for(int i = 0; i < line.length(); i++){
            tmp.push_back(line[i]);
        }

        grid.push_back(tmp);
    }
    fin.close();

    int maxWidth = grid[0].size();
    for(int i = 0; i < grid.size(); i++){
        if(maxWidth < grid[i].size()) maxWidth = grid[i].size();
    }
    for(int i = 0; i < grid.size(); i++){
        while(grid[i].size() < maxWidth){
            grid[i].push_back(' ');
        }
    }

    copyGrid = grid;

    // start at the leftmost open tile of the top row of tiles
    // start facing right
    // if the instructions goes beyond the map, wrap around
    pair<int, int> pos= make_pair(0, 0);
    for(int i=0; i < grid[0].size(); i++) {
        if(grid[0][i] == '.') {
            pos.second = i;
            pos.first = 0;
            break;
        }
    }

    // string movement = "10R5L5R10L4R5L5";
    string movement = "36R27L7R50R50L10L1R4R47L15L12R49R18R49R43R8L46R15R21L15R24L48L13L44R35L33L34L22R31L33L38L15L1R43R49R46L36R3L38L35L50L8L6L38L11R15R2L33R27R32R48L19L15R44L13R23L46R14R40R36R16L43R39R37R36R13L34R4R20R44L4L20L39L49R41L11L28R27R4R1R10R26L41R35L39L48L42R44R17R40L49R12R35R41L29L2L7R26R7R46R8R10R1R30R34L20L32R19R32L47L10R5R29L37R27R4L8R20R41R47R25R2L49R34R26R38R10L5R8L10R30R48R28L12R36R27R10L34L4L35L13R4R17L6R18R23L20R28R16R49R20L46L21L49R23R46R3R8R38R11L40R44R45R5R30L39R21R30R10R43L29L28R19R40R30R44L9R27L32R43R43R42L10R50R44R5L33R26L43R32L16L34R13R26L44L13L41L46L36L47L17L15L26R43L41R1R3R28R27L47L4L47L22L32L32L49L5R50L35R19L29R2R27R23R47L6R1L49L43L17R2R14L40L14L27L39L17L7R43R24L8R32L46L1R17L35L28R14L26R12L40R39R4R44R2R14R2L30R23R33L6L38L14L49L18R5L47L49L41L19L21L14L28R29R37R35R15R38R47R2L1R17L2R30L45R42R35L41R3L47L6L35L36L26L42R18L28L9R25R47R41R33R49R15L39R45L47R18R31R28L8R31R8L11L9L39L43R38L18R13R42L33R9L8R33L31L44L12L8R27R22L25R19R24L23L13R24L29L8R44R21R5R10L14R45R36R36R2R48R33L34L50L35R18L40R22L18L42L33L41R49R27L37L37R50R14R18L2R12R6L11L24R16R41R19L10L18L24R21L45R24L11L20R37L43R34R47L19R16L9L20R37L38L44R26R8R45L40R7L46L5L30L6L48R8R9R1L25L49R1L39R42L23R13L29L33R6R23R33L28L2L25L8R16L25L36L46L45L28R48L37L44L15R47L16L1L8R24L38R44R46R1L2L43L13L36R22L48L36R4R27R40R15R29R7R13R44R11L50R22R21L36L16L14R22R21R21L3R13L48L33L12L30L50L9L7L25L34R8L33L33L10L17L50L26R8L2L17L2L8R5L22L3R23R18L38L35R25R41L49R29R49L2R27L30L4R23L2R8L44L50L27L47L28L46R5R28R21R44L29R25L1R10R38L13L16L42L17L19L40L46L19R21L36R4R8L37R6L42R17R1R8L43R20L19L10R25R23L31R34R45L28L26L6R39L48L33L4R45L40R39R19L16R50R10R44L8L11R24R50R2R36R13L21L39R34R23L43L2R18R21R15R42L43R20L5L41R38R24R5L25R16L7L12R26L16R42R40R50R17L25L14R29L22L18R39L46L4L28L27R46L39R37L47L18L5R19L30L48R50L25L27R27L19R1R10R30L29R17R37L17R27L29R47R7L19L14R41R37L31L14R26R48L23L3R42R39L40R29L13L4R31L22R44L5R45L39L38R16R43L32R21L43R24L35R31L11L11R41R18R16R46L11R22R24R7R24R32R2R42L9L47R3R8R17R32R50L29R23L26L24R25L31R42L4R44L18R37R4L48R11R9L6L35L42L36L44R11R1L12R48R48R48L8R36L14R20R23R26L29L38L32R22L40L26L19L47R11L16L15L34L30R7R11L42L27R33R9R11L19L1L2R32R31L1L40L5L29R49R9L27L19R18R31L49L47R22R50L10R36L15R30L12L9R36L46L27L43L34L50R10L40L41L13R13R4L39R4L49R39L45L24R36R46R24R15L14L4R10L46L18R24L8R16L40L46L4L44R5L10R1L40R17R14R38R37R48R33L8L39L31R1L44R28R3R50R33R10L16L42L24R16R41R47R15L47L5L40R39L33L45R36R45R4L23L46L18L41L8R17R8R33R37L26R21L8L36L42R41R50R19R49L2L24L5L31L12L12R32L9L46R48R31L1L38L44L15L41L41L26L45R33R25R12L40R16R34L38R1R4R26R13L45R11L18L50L25R50R21R8L9L44R6L47R26R2R35R32L25L8R31L47R37L32R34R36R22R27R44R6L36R42L30L30R27R26R23L22R49R41R21L48L13R16L1R43L38R20L10R18R38R24R29L1R26R12R7L8R18R29L35R49R30R6L43L41L21R19L50R4R9L18R11R21L8R4R41L49R6L43L48R2L16R11L1R21L39L43R43R1R9R40R6L5R6L19L11L24R41R32L29R48R41R15L44L29R47R28L14L30R42R7L6L15L32R26L10L33L3L8R47L41R38R21R23R24R30L28R45R34R42R12L15R13L13L31R19R20R45L50L40L25L43R43L34L11R15L12L3R31L37R7R36R5L35L24L26R41L22L4R5L6R29R25L33R37L17R35R35R3R6L32L40R28L8R42R9R32L12R13R7R12R48R27R47L32R4L17L13L17R31R14L33L15R21R27L29R34R28L46R11L6R20L15L20R28R21L30R29R19L6L2L41R17R42L13R14L48L24L10L23L34L26L2R13L4L27L42R36L40R15R11R16L8R21L3L14R17L49R7L26L1L6R19L36L45L48R14R2L48R8L49R36R13L47L35L27R23L39L14L6L33R24R7L12L33R48L9L43R9R47L44L33R38L39L23R24R24L2R37L7L47R35R20R42R31L20R5R42R30L36L8R48L11L21L49L8L3L36L23R31L21R29R50R17R27L12R7R32L41R50L10L20R38R29R18L11R16R32L6L41R6L46R40L37R28L45R12L32R2R3R27L42R15L4R45R30R25R35L27L45R44R4L14R48L20R16R26R34L41R22L8L31L28L29R2R22R50R27R17R4R11L10R40R22R3R17R49R15R27R50R37L26L48L19R21R3L28L33R10L25R40L32L5L7L10R12R12R14L22R15L26R40L46R26L13R3L21L7R31L24R17L34L46R4L6L28R50L1R32R5L19L32R29R18L20R29R5R49L21R23R40R24R4R47L10R14R38R30L50R33R26L7R21L7R27L19L46R37R30L22L2R29R8L12R45R32R28R9L16L30L35R10R48L36L42R47L18R22L26L35R22R49L3L5R25R1L1R36L14L44L33L37L26L30L17R23L48L9L32R18L26L12L46R9L36R15R38L6L18R39L43L37L14R5L11L11L16L47R19R13L34L3R11R43R49R17R10L22L29L16R10R50L31L14L30L50L5R42L50L27L36R15R6R49R25L4R25R36L17L22R19R39L33R18L1R12R19L14R35L30R37L18L25R47R48R10L3R6L2L5L50R4L32R42R45L42L1R19L9R50R2L7L41L33L20L37L42R4L48R41L38R7L16L7L38R38L24L5L44R43L49R2L49R44L16R47R31L35R32R30R42R21L10L11R48R49L35R14L3L41R36R22L46L38R3L38L43L48R15R7L27L37R5L10L34L43R23R50R7L34L7L17R7L30L34R1R23R6R9L31L24L43R6L39R7L39R43L30R12L4L21R21R18R5R27L16L11R32R14L31R40R41L33R20R41L38L11L6L17R17L32L39R17L26R2L16L47L15L12L33R49R22R41L49R30L44R50R7R17L30R19L13L31L23L14L5L46R18R29L21R13L39L41L50R38L20R50L48L36L42L3R5L11R36L37L8L49L37L24R24R44R17R14R3L40L44L46L3R18L9L2R28L4L35L16L3R9R34R31R7L19L47L29R45L41R10L5L7R12L19L21L33L19L7R44R1L21L11L22L49R31R15R47R36L34L43R35R33L13L50L15L1R11R17L31L4L9L48L19L40L5R3L47R1R7L48L18L20L23R31R1R46R40L34L32L24L47R14L2R13L49R20L13R2L46L6L6R39R20R23R32L35R23R27R20R40R17L23L12R12R50L26L41R29L43L35L34L50L5R9R23R46R43L26R33R31R2R17L44L50L35L15L37L24R38L3R12L11L26L21R36R17R33R22R36L5L9R11L6L24R12L9L11R31L29R7R5R11R26L34L25L8R50R16L43R18R33R37R3L43L12L14L13R17R19L40L30R41R10L31L13R45L4L37R39L33L43L44R19R26L27L28R31L18R40R43R17R50R49R4R40L11L4R5R21L6L21L2L29R28R28R17L23R43R2R46R15L22L21L11L20L47R35R15L28R24L21R16L33R25R41L43R24L27L40R28L49R17R27L3R36L46L13L23L18R41R28L12L13L18L21R33L18L21R14R39L41L40L11L48L36L41R1R11R40R48R38L20L12R24L21L42L43R3R13R33R14L28L26R50R22L5R45L17L14L23R45R3R16R38L19R47R18R11R40L45L20R42L37R1L30L41L28R15L34R25R6L21L39L41L10R30R4R4R37R30R34L12L16R24L22R2L33R31L8L8L35L48L1R16L34R15R22R42L4R27R11R17L7L20L33L15L9R19R17L8L31R7L28L11L30L47R32L36L34L8L21L16L34R24L4R9R4R36L7L47R3L6R15L29L27L6L5L37L35L23R45L29L20L6L28L46R24L18L9R49R6L10R23R48R31R36R29R50L16R39L26R11L48L37R27L47R48R46L48R26R9R2R50R14R35R36L25L39L41R22R4R35R26L50";
    vector<int> numSteps;
    vector<char> rotates;

    int steps = 0;
    int pathIndex = 0;
    while(pathIndex < movement.size()) {
        char ch = movement[pathIndex];
        if(ch < '0' || ch > '9') {
            numSteps.push_back(steps);
            steps = 0;
            rotates.push_back(ch);
            pathIndex++;
        }

        steps = steps * 10 + (int)(movement[pathIndex] - '0');
        pathIndex++;
    }
    numSteps.push_back(steps);

    // face right
    pair<int, int> d = {0, 1};

    // traverse
    for(int i = 0; i < min(numSteps.size(), rotates.size()); i++) {
        for(int j = 0; j < numSteps[i]; j++){
            pair<pair<int, int>, pair<int, int>> posAndDir = nextPosition(grid, pos, d);
            pair<int, int> newPos = posAndDir.first;
            pair<int, int> newDir = posAndDir.second;

            char ch = grid[newPos.first][newPos.second];

            if(ch == '#'){
                break;
            }
            else if (ch == '.'){
                pos = newPos;
                d = newDir;
            }
            else if (ch == ' '){
                exit(-1);
            }
            else{
                exit(-2);
            }
        }

        d = rotate(d, rotates[i]);
    }


    for(int i = 0; i < numSteps[numSteps.size() - 1]; i++){
        pair<pair<int, int>, pair<int, int>> posAndDir = nextPosition(grid, pos, d);
        pair<int, int> newPos = posAndDir.first;
        pair<int, int> newDir = posAndDir.second;
        
        char ch = grid[newPos.first][newPos.second];
        if(ch == '#'){
            break;
        }
        else if (ch == '.'){
            pos = newPos;
            d = newDir;
        }
        else if (ch == ' '){
            exit(-1);
        }
    }

    // index of direction
    int dirIndex = 0;
    if(d.first == 0 && d.second == 1) dirIndex = 0;
    else if(d.first == 1 && d.second == 0) dirIndex = 1;
    else if(d.first == 0 && d.second == -1) dirIndex = 2;
    else if(d.first == -1 && d.second == 0) dirIndex = 3;


    // // print out the copyGrid
    // for(int i = 0; i < copyGrid.size(); i++){
    //     for(int j = 0; j < copyGrid[i].size(); j++){
    //         cout << copyGrid[i][j];
    //     }
    //     cout << std::endl;
    // }


    std::cout << 1000 * (pos.first+1) + 4 * (pos.second+1) + dirIndex << std::endl;

    return 0;
}