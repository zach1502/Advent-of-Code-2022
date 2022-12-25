#include <bits/stdc++.h>
using namespace std;

long long solve(int key, int iterations){
    ifstream fin("input.txt");

    stringstream ss;
    string line = "";
    vector<long long> ogValues;
    vector<long long> encryptedNums;

    int index = 0;
    while(getline(fin, line)){
        ss << line;
        long long value;
        while(ss >> value){
            long long newValue = value * key;
            ogValues.push_back(newValue);
            encryptedNums.push_back(index++);
        }
        ss.clear();
    }
    fin.close();

    for(int i = 0; i < iterations; i++){
        for(int j = 0; j < ogValues.size(); j++){

            // find the index of j in encrypted nums
            int currLocation = 0;
            for(int k = 0; k < encryptedNums.size(); k++){
                if(encryptedNums[k] == j){
                    currLocation = k;
                    break;
                }
            }

            encryptedNums.erase(encryptedNums.begin() + currLocation);

            int newLocation = currLocation + ogValues[j] % (encryptedNums.size());
            if(newLocation < 0){
                newLocation = encryptedNums.size() + newLocation;
            }
            newLocation = newLocation % encryptedNums.size();

            if(newLocation){
                encryptedNums.insert(encryptedNums.begin() + newLocation, j);
                continue;
            }
            encryptedNums.emplace_back(j);
        }
    }

    // find the index of 0 in original nums
    int nullIndex = 0;
    for(int i = 0; i < ogValues.size(); i++){
        if(ogValues[i] == 0){
            nullIndex = i;
            break;
        }
    }
    // find the index of nullIndex in encrypted nums
    int zeroIndex = 0;
    for(int i = 0; i < encryptedNums.size(); i++){
        if(encryptedNums[i] == nullIndex){
            zeroIndex = i;
            break;
        }
    }

    long long sum = 0;
    for(int i = 1; i < 4; i++){
        int index = (zeroIndex + i * 1000) % encryptedNums.size();
        sum += ogValues[encryptedNums[index]];
    }

    return sum;
}


int main(){
    std::cout << solve(1, 1) << std::endl;
    std::cout << solve(811589153, 10) << std::endl;

    return 0;
}

