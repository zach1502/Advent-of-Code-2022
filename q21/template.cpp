#include <bits/stdc++.h>
#include "./BigInt.hpp"
using namespace std;

struct shout {
    bool isOp;
    string op;
    long long num;
    string monke1;
    string monke2;

    shout(){
        isOp = false;
        op = "NULL";
        num = INT_MIN;
        monke1 = "";
        monke2 = "";
    }
};

long long monkeMagick(unordered_map<string, shout> v, string name, long long pt2){
    shout s = v[name];
    if(name == "humn" && pt2 >= 0){
        return pt2;
    }

    if(s.num != INT_MIN){
        return s.num;
    }
    else {
        string monke1 = s.monke1;
        string monke2 = s.monke2;

        long long val1 = monkeMagick(v, monke1, pt2);
        long long val2 = monkeMagick(v, monke2, pt2);

        if(s.op == "*"){
            return val1 * val2;
        }
        else if (s.op == "+"){
            return val1 + val2;
        }
        else if (s.op == "/"){
            return val1 / val2;
        }
        else if (s.op == "-"){
            return val1 - val2;
        }
        else{
            return -1; // something gone wrong
        }
    }
}

BigInt monkeMagick(unordered_map<string, shout> v, string name, BigInt pt2){
    shout s = v[name];

    if(name == "humn" && pt2 >= 0){
        std::cout << "humn: " << pt2 << std::endl;
        return pt2;
    }

    if(s.num != INT_MIN){
        return s.num;
    }
    else {
        string monke1 = s.monke1;
        string monke2 = s.monke2;

        BigInt val1 = monkeMagick(v, monke1, pt2);
        BigInt val2 = monkeMagick(v, monke2, pt2);

        if(s.op == "*"){
            return val1 * val2;
        }
        else if (s.op == "+"){
            return val1 + val2;
        }
        else if (s.op == "/"){
            return val1 / val2;
        }
        else if (s.op == "-"){
            return val1 - val2;
        }
        else{
            return -1; // something gone wrong
        }
    }
}

int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    unordered_map<string, shout> v;
    string str = "";
    long long sum = 0;
    long long max = -1;

    stringstream ss;
    string line = "";
    while(getline(fin, line)){
        // root: pppw + sjmn

        // tokenize
        ss << line;
        string token;
        vector<string> tokens;
        while(getline(ss, token, ' ')){
            tokens.push_back(token);
        }
        ss.clear();

        string map1 = tokens[0];
        // delete last char
        map1.pop_back();
        shout sht;

        // op
        if(tokens.size() > 2){
            sht.isOp = true;
            sht.op = tokens[2];
            sht.monke1 = tokens[1];
            sht.monke2 = tokens[3];
        }
        else{
            sht.isOp = false;
            sht.num = stoi(tokens[1]);
        }

        v[map1] = sht;
    }

    // part 1
    long long ans = monkeMagick(v, "root", -1);
    std::cout << "part 1: " << ans << std::endl;

    // part 2
    string monke1 = v["root"].monke1;
    string monke2 = v["root"].monke2;

    BigInt target = monkeMagick(v, monke2, (BigInt)0);
    
    BigInt low = 0;
    BigInt high = LONG_LONG_MAX;

    while (low < high){
        BigInt mid = low + (high - low) / 2;
        BigInt ans = target - monkeMagick(v, monke1, mid);

        if(ans == 0){
            std::cout << "part 2: " << mid << std::endl;
            break;
        }
        else if(ans > 0){
            high = mid;
        }
        else{
            low = mid;
        }
    }

    return 0;
}