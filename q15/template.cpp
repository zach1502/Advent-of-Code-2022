#include <bits/stdc++.h>
using namespace std;


set<pair<int, int>> listOfNotBeacon(vector<int*> sigbea, set<int> &beac, int tgt){

    vector<pair<int, int>> signal_reach;
    for(int i = 0; i < sigbea.size(); i++){
        int sx = sigbea[i][0];
        int sy = sigbea[i][1];
        int bx = sigbea[i][2];
        int by = sigbea[i][3];

        // manhattan distance
        int dist = abs(sx - bx) + abs(sy - by) ;
        if(by == tgt){
            beac.insert(bx);
        }
        dist = dist - abs(tgt - sy);
        if(dist < 0) continue;

        int reachX = sx - dist;
        int reachY = sx + dist;

        signal_reach.emplace_back(make_pair(reachX, reachY));
    }

    // Remove Dups
    set<pair<int, int>> zoneCovered;
    for (auto xy : signal_reach) {
        for (int i = xy.first; i <= xy.second; i++) {
            zoneCovered.insert(make_pair(i, tgt));
        }
    }

    return zoneCovered;
}

vector<pair<int, int>> pt2ListOfNotBeacon(vector<int*> sigbea, set<int> &beac, int tgt){
    vector<pair<int, int>> signal_reach;
    for(int i = 0; i < sigbea.size(); i++){
        int sx = sigbea[i][0];
        int sy = sigbea[i][1];
        int bx = sigbea[i][2];
        int by = sigbea[i][3];

        // manhattan distance
        int dist = abs(sx - bx) + abs(sy - by) ;
        if(by == tgt){
            beac.insert(bx);
        }
        dist = dist - abs(tgt - sy);
        if(dist < 0) continue;

        int reachX = sx - dist;
        int reachY = sx + dist;

        signal_reach.emplace_back(make_pair(reachX, reachY));
    }

    // combine overlapping ranges
    sort(signal_reach.begin(), signal_reach.end());


    // condense
    int j = 0;
    bool isLastLoop = false;
    while(signal_reach.size() >= 2){
        int i = 0;
        while(i < signal_reach.size() - 1){
            signal_reach[i].first = max(signal_reach[i].first, 0);
            if(signal_reach[i].second + 1 >= signal_reach[i+1].first){
                signal_reach[i].second = max(signal_reach[i + 1].second, signal_reach[i].second);
                signal_reach[i].second = min(signal_reach[i].second, 4000000);
                signal_reach.erase(signal_reach.begin() + i + 1);
            }
            i++;
        }
        j++;

        if(signal_reach.size() <= 2){
            if(isLastLoop) break;
            isLastLoop = true;
        }
    }


    // print
    // for(auto xy : signal_reach){
    //     cout << xy.first << " " << xy.second << endl;
    // }

    return signal_reach;
}

int main(){
    ifstream fin("input.txt");

    // change type here
    string str = "";
    unsigned long long sum = 0;
    long long max = -1;

    stringstream ss;
    string line = "";

    int tgt = 2000000;
    vector<pair<int, int>> signal_reach;
    set<int> beac;
    vector<int*> v;

    while(getline(fin, line)){
        // input will look like this
        // Sensor at x=1872146, y=1228203: closest beacon is at x=1213036, y=1428271

        // get the x and y coordinates of the sensor
        int sx = stoi(line.substr(line.find("x=") + 2, line.find(", y=") - line.find("x=") - 2));
        int sy = stoi(line.substr(line.find("y=") + 2, line.find(": closest beacon") - line.find("y=") - 2));

        // clear sensor data
        line = line.substr(line.find(": closest beacon") + 17);
        // get the x and y coordinates of the beacon
        int bx = stoi(line.substr(line.find("x=") + 2, line.find(", y=") - line.find("x=") - 2));
        int by = stoi(line.substr(line.find("y=") + 2));

        int* p = new int[4];
        p[0] = sx;
        p[1] = sy;
        p[2] = bx;
        p[3] = by;
        v.push_back(p);
    }

    set<pair<int, int>> zoneCovered = listOfNotBeacon(v, beac, 2000000);

    // part 1
    std::cout << zoneCovered.size() - beac.size() << std::endl;

    pt2ListOfNotBeacon(v, beac, 2000000);

    // look up i, j in set
    // part 2
    int gapX = 0;
    int gapY = 0;
    unsigned long long sol;
    for (int y = 0; y < 4000000; y++) {
        vector<pair<int, int>> ranges = pt2ListOfNotBeacon(v, beac, y);

        if(ranges.size() <= 1) continue;

        // found the gap
        gapX = ranges[0].second + 1;
        gapY = y;

        std::cout << "gapX: " << gapX << " gapY: " << gapY << std::endl;
        break;
    }

    sol = gapX * 4000000 + gapY;
    std::cout << sol << std::endl;

    //
    // MUST MANUALLY PUT INTO CALCULATOR, I DON"T HAVE BIG INT CLASS
    //

    return 0;
}