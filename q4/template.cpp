#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");

    // change type here
    std::vector<std::pair<int, int>> ranges;
    long long sum = 0;
    long long max = -1;
    long long count = 0;

    stringstream ss;
    string line = "";
    while(getline(fin, line)){
        ss << line;

        unsigned int a, b;
        unsigned int c, d;

        char ch;
        ss >> a >> ch >> b >> ch >> c >> ch >> d;

        std::cout << a << " " << b << " " << c << " " << d << std::endl;

        // check if a and b are in range c and d
        if(a >= c && b <= d){
            count++;
        }
        // check if c and d are in range a and b
        else if(a <= c && b >= d){
            count++;
        }
        else if( a >= c && a <= d){
            count++;
        }
        else if( b >= c && b <= d){
            count++;
        }
        else if (c >= a && c <= b){
            count++;
        }
        else if (d >= a && d <= b){
            count++;
        }

        ss.clear();
    }

    std::cout << count << std::endl;


    return count;
}



