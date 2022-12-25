#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<int> v;
    string opponentMove = "";
    string myMove = "";

    unsigned long long  addScore = 0;

    stringstream ss;
    string line = "";
    while(getline(fin, line)){
        ss << line;
        ss >> opponentMove;
        ss >> myMove;

        // opponent = A for rock B for paper C for scissors
        // my = X to lose y to tie z to win
        // detect my win

        if (opponentMove == "C" && myMove == "X"){ // rock gives 1 point
            addScore += 0;
            addScore += 2;
        }
        if (opponentMove == "C" && myMove == "Y"){ // rock gives 1 point
            addScore += 3;
            addScore += 3;
        }
        if (opponentMove == "C" && myMove == "Z"){ // rock gives 1 point
            addScore += 6;
            addScore += 1;
        }
        if (opponentMove == "A" && myMove == "X"){ // paper gives 2 points
            addScore += 0;
            addScore += 3;
        }
        if (opponentMove == "A" && myMove == "Y"){ // paper gives 2 points
            addScore += 3;
            addScore += 1;
        }
        if (opponentMove == "A" && myMove == "Z"){ // paper gives 2 points
            addScore += 6;
            addScore += 2;
        }
        if (opponentMove == "B" && myMove == "X"){ // scissors gives 3 points
            addScore += 1;
            addScore += 0;
        }
        if (opponentMove == "B" && myMove == "Y"){ // scissors gives 3 points
            addScore += 2;
            addScore += 3;
        }
        if (opponentMove == "B" && myMove == "Z"){ // scissors gives 3 points
            addScore += 3;
            addScore += 6;
        }



        ss.clear();
    }

    std::cout << addScore << std::endl;

    return 0;
}