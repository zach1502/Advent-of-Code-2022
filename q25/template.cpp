
#include <bits/stdc++.h>
#include "./BigInt.hpp"

using namespace std;

vector<char> lookUp = {'=', '-', '0', '1', '2'};


BigInt from_snafu(string text) {
    BigInt ans = 0;
    BigInt mul = 1;
    for (int i = text.size() - 1; i >= 0; i--) {
        char x = text[i];
        if ('0' <= x && x <= '2') {
            ans += (x - '0') * mul;
        } else if (x == '-') {
            ans -= mul;
        } else {
            ans -= 2 * mul;
        }
        mul *= 5;
    }
    return ans;
}

string to_snafu(BigInt num) {
    BigInt curr = 1;
    BigInt total = 2;
    BigInt snafuLength = 0;
    while (num > total) {
        curr *= 5;
        total += 2 * curr;
        snafuLength += 1;
    }

    string firstDigit;
    if (total - num < curr) {
        firstDigit = "2";
        num -= curr;
    } else {
        firstDigit = "1";
    }

    total /= 5;
    num -= total + 1;
    string restOfTheDigits = "";
    while (num != 0) {
        if (num % 5 == 0){
            restOfTheDigits += '=';
        }
        else if (num % 5 == 1) {
            restOfTheDigits += '-';
        }
        else if (num % 5 == 2) {
            restOfTheDigits += '0';
        }
        else if (num % 5 == 3) {
            restOfTheDigits += '1';
        }
        else if (num % 5 == 4) {
            restOfTheDigits += '2';
        }

        num /= 5;
    }

    while (restOfTheDigits.size() < snafuLength) {
        restOfTheDigits += '=';
    }

    reverse(restOfTheDigits.begin(), restOfTheDigits.end());
    return firstDigit + restOfTheDigits;
}

int main() {
    ifstream fin("input.txt");
    string line;
    BigInt ans = 0;
    while (getline(fin, line)) {
        ans += from_snafu(line);
    }
    cout << to_snafu(ans) << endl;
}
