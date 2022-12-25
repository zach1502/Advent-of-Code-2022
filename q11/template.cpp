#include <bits/stdc++.h>
using namespace std;

struct monkey {
    vector<long long> worryItems;
    bool multiply;
    bool square;
    long long modulo;
    long long trueMonkey;
    long long falseMonkey;
    long long multiplyer;
    long long numInspected;

    long long operation(long long worry){
        if(multiply){
            return worry * multiplyer;
        } 
        else if(square){
            return worry * worry;
        } 
        else {
            return  worry + multiplyer;
        }
    }

    long long test(long long worry){
        if(worry % modulo == 0){
            return trueMonkey;
        } else {
            return falseMonkey;
        }
    }

    monkey(){
        worryItems = vector<long long>();
        multiply = false;
        square = false;
        modulo = 0;
        trueMonkey = 0;
        falseMonkey = 0;
        multiplyer = 0;
        numInspected = 0;
    }
};


int main(){
    ifstream fin("input.txt");

    // change type here
    string x;
    vector<long long> v;
    string str = "";
    long long sum = 0;
    long long max = INT_MIN;

    // bool multiply;
    // long long modulo;
    // long long trueMonkey;
    // long long falseMonkey;
    // long long modulableNum;
    

//     Monkey 0:
//   Starting items: 66, 79
//   Operation: new = old * 11
//   Test: divisible by 7
//     If true: throw to monkey 6
//     If false: throw to monkey 7
    vector<monkey> m = vector<monkey>(8);
    m[0].worryItems.push_back(66);
    m[0].worryItems.push_back(79);
    m[0].multiply = true;
    m[0].multiplyer = 11;
    m[0].square = false;
    m[0].modulo = 7;
    m[0].trueMonkey = 6;
    m[0].falseMonkey = 7;

//     Monkey 1:
//   Starting items: 84, 94, 94, 81, 98, 75
//   Operation: new = old * 17
//   Test: divisible by 13
//     If true: throw to monkey 5
//     If false: throw to monkey 2

    m[1].worryItems.push_back(84);
    m[1].worryItems.push_back(94);
    m[1].worryItems.push_back(94);
    m[1].worryItems.push_back(81);
    m[1].worryItems.push_back(98);
    m[1].worryItems.push_back(75);
    m[1].multiply = true;
    m[1].multiplyer = 17;
    m[1].square = false;
    m[1].modulo = 13;
    m[1].trueMonkey = 5;
    m[1].falseMonkey = 2;


//     Monkey 2:
//   Starting items: 85, 79, 59, 64, 79, 95, 67
//   Operation: new = old + 8
//   Test: divisible by 5
//     If true: throw to monkey 4
//     If false: throw to monkey 5.

    m[2].worryItems.push_back(85);
    m[2].worryItems.push_back(79);
    m[2].worryItems.push_back(59);
    m[2].worryItems.push_back(64);
    m[2].worryItems.push_back(79);
    m[2].worryItems.push_back(95);
    m[2].worryItems.push_back(67);
    m[2].multiply = false;
    m[2].square = false;
    m[2].modulo = 5;
    m[2].trueMonkey = 4;
    m[2].falseMonkey = 5;
    m[2].multiplyer = 8;

//     Monkey 3:
//   Starting items: 70
//   Operation: new = old + 3
//   Test: divisible by 19
//     If true: throw to monkey 6
//     If false: throw to monkey 0

    m[3].worryItems.push_back(70);
    m[3].multiply = false;
    m[3].square = false;
    m[3].modulo = 19;
    m[3].trueMonkey = 6;
    m[3].falseMonkey = 0;
    m[3].multiplyer = 3;

// Monkey 4:
//   Starting items: 57, 69, 78, 78
//   Operation: new = old + 4
//   Test: divisible by 2
//     If true: throw to monkey 0
//     If false: throw to monkey 3

    m[4].worryItems.push_back(57);
    m[4].worryItems.push_back(69);
    m[4].worryItems.push_back(78);
    m[4].worryItems.push_back(78);
    m[4].multiply = false;
    m[4].square = false;
    m[4].multiplyer = 4;
    m[4].modulo = 2;
    m[4].trueMonkey = 0;
    m[4].falseMonkey = 3;

// Monkey 5:
//   Starting items: 65, 92, 60, 74, 72
//   Operation: new = old + 7
//   Test: divisible by 11
//     If true: throw to monkey 3
//     If false: throw to monkey 4

    m[5].worryItems.push_back(65);
    m[5].worryItems.push_back(92);
    m[5].worryItems.push_back(60);
    m[5].worryItems.push_back(74);
    m[5].worryItems.push_back(72);
    m[5].multiply = false;
    m[5].square = false;
    m[5].multiplyer = 7;
    m[5].modulo = 11;
    m[5].trueMonkey = 3;
    m[5].falseMonkey = 4;

// Monkey 6:
//   Starting items: 77, 91, 91
//   Operation: new = old * old
//   Test: divisible by 17
//     If true: throw to monkey 1
//     If false: throw to monkey 7

    m[6].worryItems.push_back(77);
    m[6].worryItems.push_back(91);
    m[6].worryItems.push_back(91);
    m[6].square = true;
    m[6].multiply = false;
    m[6].modulo = 17;
    m[6].trueMonkey = 1;
    m[6].falseMonkey = 7;

// Monkey 7:
//   Starting items: 76, 58, 57, 55, 67, 77, 54, 99
//   Operation: new = old + 6
//   Test: divisible by 3
//     If true: throw to monkey 2
//     If false: throw to monkey 1

    m[7].worryItems.push_back(76);
    m[7].worryItems.push_back(58);
    m[7].worryItems.push_back(57);
    m[7].worryItems.push_back(55);
    m[7].worryItems.push_back(67);
    m[7].worryItems.push_back(77);
    m[7].worryItems.push_back(54);
    m[7].worryItems.push_back(99);
    m[7].multiply = false;
    m[7].square = false;
    m[7].modulo = 3;
    m[7].trueMonkey = 2;
    m[7].falseMonkey = 1;
    m[7].multiplyer = 6;

    // multiply all modulos together
    long long superModulo = 1;
    for(long long i = 0; i < 8; i++) {
        superModulo *= m[i].modulo;
    }

    bool part1 = false;
     
    // round count
    for(long long i = 0; i < 10000; i++) {
        for(long long j = 0; j < 8; j++) {
            for(long long k = 0; k < m[j].worryItems.size(); k++) {
                long long item = m[j].worryItems[k];

                // printf("Monkey %lld is inspecting item %lld\n", j, item);
                m[j].numInspected++;
                long long newItem = m[j].operation(item) % superModulo;
                if(part1) newItem /= 3;

                // printf("The new item is %lld\n", newItem);
                long long nextMonkey = m[j].test(newItem);
                m[nextMonkey].worryItems.push_back(newItem);
            }

            m[j].worryItems.clear();
        }
    }

    for(long long i = 0; i < 8; i++) {
        cout << "Monkey " << i << " inspected " << m[i].numInspected << " items." << endl;
    }

    std::sort(m.begin(), m.end(), [](monkey a, monkey b) { return a.numInspected > b.numInspected; });

    for(long long i = 0; i < 8; i++) {
        cout << "Monkey " << i << " inspected " << m[i].numInspected << " items." << endl;
    }

    std::cout << "The answer is " << m[0].numInspected * m[1].numInspected << std::endl;
    return 0;
}