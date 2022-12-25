#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<int> v;
    string str = "";
    long long sum = 0;

    stringstream ss;
    string line = "";
    while(getline(fin, line)){
        ss << line;

        // every item type is identified by a single lowercase or uppercase letter
        // first half of string is first compartemnt and second half is second compartment
        // find the common letter between the 2 compartments

        // find the common letter
        string cmp1 = "";
        string cmp2 = "";
        for(int i = 0; i < line.length()/2; i++){
            cmp1 += line[i];
        }
        for(int i = line.length()/2; i < line.length(); i++){
            cmp2 += line[i];
        }

        // find intersection of 2 sets
        set<char> s1;
        set<char> s2;
        for(int i = 0; i < cmp1.length(); i++){
            s1.insert(cmp1[i]);
        }
        for(int i = 0; i < cmp2.length(); i++){
            s2.insert(cmp2[i]);
        }
        set<char> s3;
        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s3, s3.begin()));
        char common = *s3.begin();

        //Lowercase item types a through z have value 1 through 26.
        //Uppercase item types A through Z have value  27 through 52.

        // find the value of the common letter

        int value = 0;

        if(common >= 'a' && common <= 'z'){
            value += common - 'a' + 1;
        } else if (common >= 'A' && common <= 'Z'){
            value += common - 'A' + 27;
        }

        sum += value;

        ss.clear();
    }

    std::cout << sum << std::endl;
    return 0;
}