#include <bits/stdc++.h>

using namespace std;

signed main(){
    ifstream fin ("input.txt");
    int res = 0;

    vector<int> v;
    int X = 1;
    v.push_back(0);
    for(int i = 0; i < 140; i++) {
        string str;
        fin >> str;

        // noop or addX <num>
        if(str[0] == 'n') {
            v.push_back(X);
        }
        else {
            int x; // cast
            fin >> x;
            v.push_back(X);
            v.push_back(X);
            X += x;
        }
    }

    // check cycles
    for(int i = 20; i <= 220; i += 40) {
        res += i * v[i];
    }

    cout << res << endl;

    int t = 1;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 40; j++) {
            if(j == v[t] - 1 || j == v[t] || j == v[t] + 1) cout << "#";
            else cout << " ";
            t++;
        }
        cout << endl;
    }

    return 0;
}