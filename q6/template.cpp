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
    while(getline(fin, line)){
        // substring of 14 characters
        for(int i = 0; i < line.length() - 14; i++){
            str = line.substr(i, 13);

            // check if all of the characters are unique
            bool unique = true;
            for(int j = 0; j < str.length(); j++){
                for(int k = j + 1; k < str.length(); k++){
                    if(str[j] == str[k]){
                        unique = false;
                        break;
                    }
                }
            }

            if(unique){
                std::cout << i + 14 << " " << str << std::endl;
            }
        }
    }


    return 0;
}