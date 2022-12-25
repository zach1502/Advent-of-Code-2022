#include <bits/stdc++.h>
using namespace std;

bool checkInCardinalDirections(vector<vector<int>> v ,int  i,int j){
    // check left and right for smaller values
    const int ogI = i;
    const int ogJ = j;

    bool visibleFromRight = true;
    bool visibleFromLeft = true;
    bool visibleFromUp = true;
    bool visibleFromDown = true;

    for(int i = ogI+1; i < v.size(); i++){
        if(v[i][ogJ] >= v[ogI][ogJ]){
            visibleFromRight = false;
            break;
        }
    }
    if(visibleFromRight) return true;

    for(int j = ogJ+1; j < v[i].size(); j++){
        if(v[ogI][j] >= v[ogI][ogJ]){
            visibleFromDown = false;
            break;
        }
    }
    if(visibleFromDown) return true;

    for(int j = ogJ-1; j < v[i].size(); j--){
        if(v[ogI][j] >= v[ogI][ogJ]){
            visibleFromUp = false;
            break;
        }
    }
    if(visibleFromUp) return true;

    for(int i = ogI-1; i < v.size(); i--){
        if(v[i][ogJ] >= v[ogI][ogJ]){
            visibleFromLeft = false;
            break;
        }
    }
    if(visibleFromLeft) return true;

    return false;
}

int getScenicScore(vector<vector<int>> v, int  i,int j){
    // check left and right for smaller values
    const int ogI = i;
    const int ogJ = j;

    bool visibleFromRight = true;
    bool visibleFromLeft = true;
    bool visibleFromUp = true;
    bool visibleFromDown = true;
    // distBeforeBlocked
    int dBBR = 0;
    int dBBL = 0;
    int dBBU = 0;
    int dBBD = 0;


    for(int i = ogI+1; i < v.size(); i++){
        dBBR++;
        if(v[i][ogJ] >= v[ogI][ogJ]){
            visibleFromRight = false;
            break;
        }
    }

    for(int j = ogJ+1; j < v[i].size(); j++){
        dBBD++;
        if(v[ogI][j] >= v[ogI][ogJ]){
            visibleFromDown = false;
            break;
        }
    }

    for(int j = ogJ-1; j < v[i].size(); j--){
        dBBU++;
        if(v[ogI][j] >= v[ogI][ogJ]){
            visibleFromUp = false;
            break;
        }
    }

    for(int i = ogI-1; i < v.size(); i--){
        dBBL++;
        if(v[i][ogJ] >= v[ogI][ogJ]){
            visibleFromLeft = false;
            break;
        }
    }

    return dBBR * dBBL * dBBU * dBBD;
}

int main(){
    ifstream fin("input.txt");

    int count = 0;

    // change type here
    string x;
    string str = "";
    long long sum = 0;
    long long max = -1;

    vector<vector<int>> v;

    string line = "";
    vector<int> innervect;
    while(getline(fin, line)){
        string str = line;
        vector<int> innervect;
        for(int i = 0; i < str.length(); i++){
            innervect.push_back(str[i] - '0');
        }

        v.push_back(innervect);
    }

    // pt 1
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[i].size(); j++){
            if(checkInCardinalDirections(v, i, j)){
                count++;
            }
        }
    }

    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[i].size(); j++){
            int temp = getScenicScore(v, i, j);
            if(max < temp){
                max = temp;
            }
        }
    }

    cout << count << endl;
    cout << max << endl;

    return 0;
}