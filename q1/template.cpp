#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    vector<int> v;
    int x;
    long long count = 0;
    long long max = -1;
    long long secondMax = -2;
    long long thirdMax = -3;

    stringstream ss;
    string line;
    while(getline(fin, line)){
        ss << line;

        if(line == ""){
            if(count > max){
                thirdMax = secondMax;
                secondMax = max;
                max = count;
            }else if(count > secondMax){
                thirdMax = secondMax;
                secondMax = count;
            }else if(count > thirdMax){
                thirdMax = count;
            }
            count = 0;
        }

        while(ss >> x){
            count += x;
        }

        ss.clear();
    }

    std::cout << max << std::endl;
    std::cout << secondMax << std::endl;
    std::cout << thirdMax << std::endl;

    return 0;
}