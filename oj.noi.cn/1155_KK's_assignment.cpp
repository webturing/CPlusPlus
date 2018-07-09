//
// Created by ubuntu on 18-7-9.
//

#include <bits/stdc++.h>

using namespace std;
const int N = 1001;
bool f[N];
vector<int> prime;

void init() {
    memset(f, true, sizeof(f));
    f[0] = f[1] = false;
    for (int i = 2; i < N; i++) {
        if (f[i]) {
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && prime[j] * i < N; j++) {
            f[i * prime[j]] = false;
        }
    }
    //copy(prime.begin(), prime.end(), ostream_iterator<int>(cout, " "));cout << endl;
}

struct BigInteger : vector<int> {

    BigInteger(int n = 0) {
        push_back(n);
        check();
    }

    BigInteger &check() {
        while (!empty() && !back())pop_back();
        if (empty())return *this;
        for (int i = 1; i < size(); ++i) {
            (*this)[i] += (*this)[i - 1] / 10;
            (*this)[i - 1] %= 10;
        }
        while (back() >= 10) {
            push_back(back() / 10);
            (*this)[size() - 2] %= 10;
        }
        return *this;
    }
};

istream &operator>>(istream &is, BigInteger &n) {
    string s;
    is >> s;
    n.clear();
    for (int i = s.size() - 1; i >= 0; --i)n.push_back(s[i] - '0');
    return is;
}

ostream &operator<<(ostream &os, const BigInteger &n) {
    if (n.empty())os << 0;
    for (int i = n.size() - 1; i >= 0; --i)os << n[i];
    return os;
}

bool operator!=(const BigInteger &a, const BigInteger &b) {
    if (a.size() != b.size())return 1;
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])return 1;
    return 0;
}

bool operator==(const BigInteger &a, const BigInteger &b) {
    return !(a != b);
}

bool operator<(const BigInteger &a, const BigInteger &b) {
    if (a.size() != b.size())return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i])return a[i] < b[i];
    return 0;
}

bool operator>(const BigInteger &a, const BigInteger &b) {
    return b < a;
}

bool operator<=(const BigInteger &a, const BigInteger &b) {
    return !(a > b);
}

bool operator>=(const BigInteger &a, const BigInteger &b) {
    return !(a < b);
}


BigInteger &operator+=(BigInteger &a, const BigInteger &b) {
    if (a.size() < b.size())a.resize(b.size());
    for (int i = 0; i != b.size(); ++i)a[i] += b[i];
    return a.check();
}

BigInteger operator+(BigInteger a, const BigInteger &b) {
    return a += b;
}

BigInteger &operator-=(BigInteger &a, BigInteger b) {
    if (a < b)swap(a, b);
    for (int i = 0; i != b.size(); a[i] -= b[i], ++i)
        if (a[i] < b[i]) {
            int j = i + 1;
            while (!a[j])++j;
            while (j > i) {
                --a[j];
                a[--j] += 10;
            }
        }
    return a.check();
}

BigInteger operator-(BigInteger a, const BigInteger &b) {
    return a -= b;
}


BigInteger operator*(const BigInteger &a, const BigInteger &b) {
    BigInteger n;
    n.assign(a.size() + b.size() - 1, 0);
    for (int i = 0; i != a.size(); ++i)
        for (int j = 0; j != b.size(); ++j)
            n[i + j] += a[i] * b[j];
    return n.check();
}

BigInteger &operator*=(BigInteger &a, const BigInteger &b) {
    return a = a * b;
}


BigInteger divmod(BigInteger &a, const BigInteger &b) {
    BigInteger ans;
    for (int t = a.size() - b.size(); a >= b; --t) {
        BigInteger d;
        d.assign(t + 1, 0);
        d.back() = 1;
        BigInteger c = b * d;
        while (a >= c) {
            a -= c;
            ans += d;
        }
    }
    return ans;
}

BigInteger operator/(BigInteger a, const BigInteger &b) {
    return divmod(a, b);
}

BigInteger &operator/=(BigInteger &a, const BigInteger &b) {
    return a = a / b;
}

BigInteger &operator%=(BigInteger &a, const BigInteger &b) {
    divmod(a, b);
    return a;
}

BigInteger operator%(BigInteger a, const BigInteger &b) {
    return a %= b;
}


BigInteger pow(const BigInteger &n, const BigInteger &k) {
    if (k.empty())return 1;
    if (k == 2)return n * n;
    if (k.back() % 2)return n * pow(n, k - 1);
    return pow(pow(n, k / 2), 2);
}

BigInteger gcd(BigInteger n, BigInteger m) {
    BigInteger rem = n % m;
    if (rem == 0)
        return m;
    else
        return gcd(m, rem);
}

int result[N];

int main() {
    init();
    ifstream cin("input.txt");
    int n;
    cin >> n;
    unsigned int x, pos;
    int answer = -1;
    while (n--) {
        cin >> x;
        if (x == 0)answer = 0;
        pos = 0;
        while (x != 1) {
            if (x % prime[pos] == 0) {
                result[prime[pos]]++;

                x /= prime[pos];
            } else {
                pos++;
            }
        }
    }
    int m;
    cin >> m;
    while (m--) {
        cin >> x;
        pos = 0;
        while (x != 1) {
            if (x % prime[pos] == 0) {
                result[prime[pos]]--;
                x /= prime[pos];
            } else {
                pos++;
            }
        }
    }
    if (answer == 0) {
        cout << 0 << endl;
    } else {
        BigInteger up(1);
        for (int i = 0; i <= N; i++) {
            if (result[i] >= 1) {
                for (int j = 1; j <= result[i]; j++) {
                    up *= i;
                }
            }
        }
        cout << up << endl;
    }
    BigInteger down(1);
    for (int i = 0; i <= N; i++) {
        if (result[i] < 0) {
            result[i] = -result[i];
            while (result[i]--) {
                down *= i;
            }
        }
    }
    cout << down << endl;
}