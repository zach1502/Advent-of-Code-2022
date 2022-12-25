#include <bits/stdc++.h>
using namespace std;

queue<tuple<int, int, int, int, int, int, int, int, int>> Queue;

int solve(int costOre, int costClay, int costObsidian1, int costObsidian2, int costGeode1, int costGeode2, int time){
    int best = 0;
    // state is (ore, clay, obsidian, geodes, rateOre, rateClay, rateObsidian, rateGeode, time)
    tuple<int, int, int, int, int, int, int, int, int> S = make_tuple(0, 0, 0, 0, 1, 0, 0, 0, time);
    Queue.push(S);
    set<tuple<int, int, int, int, int, int, int, int, int>> dp;

    while(!Queue.empty()){
        tuple<int, int, int, int, int, int, int, int, int> state = Queue.front();
        Queue.pop();
        int ore, clay, obsidian, geode, rateOre, rateClay, rateObsidian, rateGeode, time;
        tie(ore, clay, obsidian, geode, rateOre, rateClay, rateObsidian, rateGeode, time) = state;
        best = max(best, geode);

        if(time == 0){
            continue;
        }

        int Core = max(costOre, max(costClay, max(costObsidian1, costGeode1)));


        // Ignore unimportant resources
        rateOre = min(rateOre, Core);
        rateClay = min(rateClay, costObsidian2);
        rateObsidian = min(rateObsidian, costGeode2);
        ore = min(ore, time * Core - rateOre * (time - 1));
        clay = min(clay, time * costObsidian2 - rateClay * (time - 1));
        obsidian = min(obsidian, time * costGeode2 - rateObsidian * (time - 1));

        // Memoize
        state = make_tuple(ore, clay, obsidian, geode, rateOre, rateClay, rateObsidian, rateGeode, time);
        if(dp.find(state) != dp.end()){
            continue;
        }
        dp.insert(state);
        if(dp.size() % 1000000 == 0){
            cout << time << " " << best << " " << dp.size() << endl;
        }

        // Try doing nothing
        Queue.push(make_tuple(ore + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian, rateGeode, time - 1));

        // or make bots
        if(ore >= costOre){ 
            Queue.push(make_tuple(ore - costOre + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre + 1, rateClay, rateObsidian, rateGeode, time - 1));
        }
        if(ore >= costClay){
            Queue.push(make_tuple(ore - costClay + rateOre, clay + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay + 1, rateObsidian, rateGeode, time - 1));
        }
        if(ore >= costObsidian1 && clay >= costObsidian2){
            Queue.push(make_tuple(ore - costObsidian1 + rateOre, clay - costObsidian2 + rateClay, obsidian + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian + 1, rateGeode, time - 1));
        }
        if(ore >= costGeode1 && obsidian >= costGeode2){
            Queue.push(make_tuple(ore - costGeode1 + rateOre, clay + rateClay, obsidian - costGeode2 + rateObsidian, geode + rateGeode, rateOre, rateClay, rateObsidian, rateGeode + 1, time - 1));
        }
    }
    return best;
}



int main(){
    ifstream fin("input.txt");

    stringstream ss;
    string line = "";

    int p1 = 0;
    int p2 = 1;

    while(getline(fin, line)){
        // Blueprint 26: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 14 clay. Each geode robot costs 2 ore and 16 obsidian.
        // parse input

        int blueprintNum;
        int oreRobotCost;
        int clayRobotCost;
        pair<int, int> obsidianRobotCost;
        pair<int, int> geodeRobotCost;

        // tokenize
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while(getline(ss, token, ' ')){
            tokens.push_back(token);
        }

        // get blueprint number
        blueprintNum = stoi(tokens[1].substr(0, tokens[1].length() - 1));

        // get ore robot cost
        oreRobotCost = stoi(tokens[6]);

        // get clay robot cost
        clayRobotCost = stoi(tokens[12]);


        // get obsidian robot cost
        obsidianRobotCost.first = stoi(tokens[18]);
        obsidianRobotCost.second = stoi(tokens[21]);

        // get geode robot cost
        geodeRobotCost.first = stoi(tokens[27]);
        geodeRobotCost.second = stoi(tokens[30]);

        int s1 = solve(oreRobotCost, clayRobotCost, obsidianRobotCost.first,  obsidianRobotCost.second, geodeRobotCost.first, geodeRobotCost.second, 24);
        p1 += blueprintNum * s1;
        if(blueprintNum < 4){
            int s2 = solve(oreRobotCost, clayRobotCost, obsidianRobotCost.first,  obsidianRobotCost.second, geodeRobotCost.first, geodeRobotCost.second, 32);
            p2 *= s2;
        }

        ss.clear();
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;

    return 0;
}
