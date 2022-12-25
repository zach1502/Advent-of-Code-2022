#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> rates;
unordered_map<string, vector<string>> graph;
unordered_map<string, int> nameToIndex;
unordered_map<string, unordered_map<string, int>> T;

void visit(string v, int budget, int state, int flow, unordered_map<int, int>& answer){
    answer[state] = max(answer[state], flow);
    for(auto u: rates){
        int newbudget = budget - T[v][u.first] - 1;
        if ((nameToIndex[u.first] & state) || newbudget <= 0){
            continue;
        }
        visit(u.first, newbudget, state | nameToIndex[u.first], flow + newbudget * rates[u.first], answer);
    }
}

int main(){
    ifstream fin("input.txt");

    // change type here
    string line = "";

    int index = 0;
    while(getline(fin, line)){
        // Valve JT has flow rate=9; tunnels lead to valves ES, RL, BL, BN
        // n tunnels
        // parse input
        string name;
        string flowStr;
        int flowRate;
        vector<string> tunnels;
        // after Valve 
        int i = 6;
        while(line[i] != ' '){
            name += line[i];
            i++;
        }
        // after has flow rate=
        i = 23;
        while(line[i] != ';'){
            flowStr += line[i];
            i++;
        }
        flowRate = stoi(flowStr);
        flowStr.clear();
        // find index of "valves"
        i = line.find("to valve") + 9;
        line.erase(0, i);
        // remove whitespace at the beginning
        while(line[0] == ' '){
            line.erase(0, 1);
        }
        i=0;
        while(i < line.length()){
            string tunnel = "";
            tunnel += line[i];
            tunnel += line[i+1];
            tunnels.push_back(tunnel);
            i += 4;
        }

        if (flowRate != 0){
            rates[name] = flowRate;
            nameToIndex[name] = 1 << index;
            index++;
        }

        graph[name] = tunnels;
    }

    //unordered_map<string, unordered_map<string, int>> T;
    for(auto x: graph){
        for(auto y: graph){
            auto gx = x.second;
            
            // check if y is in gx
            bool found = false;
            for(auto z: gx){
                if (z == y.first){
                    found = true;
                    break;
                }
            }

            T[x.first][y.first] = found ? 1 : SHRT_MAX;
        }
    }



    for(auto k: T){
        for(auto i: T){
            for(auto j: T){
                T[i.first][j.first] = min(T[i.first][j.first], T[i.first][k.first] + T[k.first][j.first]);
            }
        }
    }

    unordered_map<int, int> answer;
    unordered_map<int, int> visited;
    int budget = 30;
    int state = 0;
    int flow = 0;
    string start = "AA";
    visit(start, budget, state, flow, answer);
    int total1 = 0;
    for(auto x: answer){
        total1 = max(total1, x.second);
    }

    budget = 26;
    state = 0;
    flow = 0;
    visit(start, budget, state, flow, visited);
    int total2 = 0;
    for(auto x: visited){
        for(auto y: visited){
            if ((x.first & y.first) == 0){
                total2 = max(total2, x.second + y.second);
            }
        }
    }

    cout << total1 << " " << total2 << endl;
}