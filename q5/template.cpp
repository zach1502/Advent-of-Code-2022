#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<int> v;
    string str = "";
    long long sum = 0;
    long long max = -1;

    stringstream ss;
    string line = "";

    //         [H]     [W] [B]            
    //     [D] [B]     [L] [G] [N]        
    // [P] [J] [T]     [M] [R] [D]        
    // [V] [F] [V]     [F] [Z] [B]     [C]
    // [Z] [V] [S]     [G] [H] [C] [Q] [R]
    // [W] [W] [L] [J] [B] [V] [P] [B] [Z]
    // [D] [S] [M] [S] [Z] [W] [J] [T] [G]
    // [T] [L] [Z] [R] [C] [Q] [V] [P] [H]
    //  1   2   3   4   5   6   7   8   9 

    std::vector<std::stack<char>> stacks;
    for(int i = 0; i < 9; i++){
        std::stack<char> s;
        stacks.push_back(s);
    }

    while(getline(fin, line)){
        ss << line;

        string s = line;
        // 0123456789
        // [V] [F] [V]     [F] [Z] [B]     [C]

        if(s[1] == '1') break;

        std::cout << s[1] << s[5] << s[9] << s[13] << s[17] << s[21] << s[25] << s[29] << s[33] << std::endl;
        // check positions
        if(s[1] != ' '){
            stacks[0].push(s[1]);
        }
        if(s[5] != ' '){
            stacks[1].push(s[5]);
        }
        if(s[9] != ' '){
            stacks[2].push(s[9]);
        }
        if(s[13] != ' '){
            stacks[3].push(s[13]);
        }
        if(s[17] != ' '){
            stacks[4].push(s[17]);
        }
        if(s[21] != ' '){
            stacks[5].push(s[21]);
        }
        if(s[25] != ' '){
            stacks[6].push(s[25]);
        }
        if(s[29] != ' '){
            stacks[7].push(s[29]);
        }
        if(s[33] != ' '){
            stacks[8].push(s[33]);
        }

        ss.clear();
    }

    // reverse the order of the stacks
    for(int i = 0; i < 9; i++){
        std::stack<char> s;
        while(!stacks[i].empty()){
            s.push(stacks[i].top());
            stacks[i].pop();
        }
        stacks[i] = s;
    }

    // empty
    getline(fin, line);

    while(getline(fin, line)){
        // line == "move Xx from Yy to Zz"
        // seperate line into x, y, z
        string s = line;
    
        // extract numbers from the line
        // move Xx from Yy to Zz
        string delimit = " ";
        std::string token;
        std::vector<std::string> tokens;
        size_t pos = 0;
        while ((pos = s.find(delimit)) != std::string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + delimit.length());
        }
        tokens.push_back(s);

        int numberToMove = atoi(tokens[1].c_str());
        int fromStack = atoi(tokens[3].c_str());
        int toStack = atoi(tokens[5].c_str());

        std::stack<char> part2;

        // perform action on stacks
        for(int i = 0; i < numberToMove; i++){
            // part 1 solution
            // stacks[toStack-1].push(stacks[fromStack-1].top());
            // stacks[fromStack-1].pop();

            // part 2 solution
            part2.push(stacks[fromStack-1].top());
            stacks[fromStack-1].pop();
        }

        while(part2.size() > 0){
            stacks[toStack-1].push(part2.top());
            part2.pop();
        }
    }

    // print stack tops
    for(int i = 0; i < 9; i++){
        std::cout << stacks[i].top() << " ";
    }

    return 0;
}