#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long LL;

template<typename T>
inline void oo(string str, T val) { cerr << str << val << endl; }

template<typename T>
inline T read() {
    T x;
    cin >> x;
    return x;
}

#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)

int main() {
    int n = read<int>();
    stack<char> S;
    int tot = 0;
    FOR(i, 0, n) {
        string s = read<string>();
        if (not S.empty() and S.top() == s[0]) {
            ++tot;
            while (not S.empty())S.pop();
        }
        S.push(s[0]);
        S.push(s[1]);
    }
    if (not S.empty())tot++;
    cout << tot << endl;
    return 0;
}
