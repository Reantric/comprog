#include <chrono>

#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<lll> vlll;


#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx512f")

using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using namespace std;

/*
* Solution based on https://codeforces.com/blog/entry/117947
* Iterative and in-place version.
* Uses signed montgomery
* Optimized to minimize memory usage
* Trying out 4 radix recursive DFS NTT
*/


// IO from https://judge.yosupo.jp/submission/142782


// Solution based on https://codeforces.com/blog/entry/117947

ll MOD = 998244353;
const long long MOD2 = (long long) MOD * MOD;
ll root = 3;
const int alim = 64; // Bound for using O(n^2) polynomial mult



long long binpow(long long a, long long b, ll M = MOD) {
    a %= M;
    long long res = 1;
    while (b > 0) {
        // this is really smart, its basically cycling through all binary digits and if there's a 1 there, multiply res by it!
        if (b & 1) // bit hacky way of checking b % 2 == 1
            res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res % M;
}

int modpow(int b, int e) {
    int ans = 1;
    for (; e; b = (long long) b * b % MOD, e /= 2)
        if (e & 1) ans = (long long) ans * b % MOD;
    return ans;
}

const int MODinv = 2 - MOD; // pow(-MOD, -1, 2**32)
inline int m_reduce(long long x) {
    int m = x * MODinv;
    return (x>>32) - (((long long) m * MOD) >> 32);
}

const int r2 = modpow(2, 64);
inline int m_transform(int x) {
    return m_reduce((long long)x * r2);
}

inline int m_add(int x, int y) {
    int z = x + y;
    return z < 0 ? z + MOD : z - MOD;
}

inline int m_sub(int x, int y) {
    int z = x - y;
    return z < 0 ? z + MOD : z - MOD;
}

inline int m_mult(int x, int y) {
    return m_reduce((long long) x * y);
}

vector<int> rt = {1};
vector<int> transformed_rt;
vector<int> transformed_rt2;

template<int a>
void transform(vector<int> &P) {
    int m = P.size();
    int n = m / a;

    int size = rt.size();
    while (2 * size < n) {
        rt.resize(n / 2);
        int r = modpow(root, MOD / (4 * size));
        for (int i = 0; i < size; ++i)
            rt[i + size] = (long long) r * rt[i] % MOD;
        size *= 2;
    }

    // For montgomery
    for (int i = transformed_rt.size(); i < rt.size(); ++i) {
        transformed_rt.resize(rt.size());
        transformed_rt[i] = m_transform(rt[i]);
        transformed_rt2.resize(rt.size());
        transformed_rt2[i] = (unsigned int) MODinv * transformed_rt[i];
    }

    // Radix 4 recursive NTT
    auto dfs = [&](auto &&self, int i, int k) -> void {
        if (k == 1)
            return;
        int step = k * a;
        int quarter_step = step / 4;

        int R20 = transformed_rt2[2 * i];
        int RR0 = transformed_rt[2 * i];

        int R21 = transformed_rt2[2 * i + 1];
        int RR1 = transformed_rt[2 * i + 1];

        int R2 = transformed_rt2[i];
        int RR = transformed_rt[i];

        int *P1 = &P[i * step];
        int *P2 = P1 + quarter_step;
        int *P3 = P2 + quarter_step;
        int *P4 = P3 + quarter_step;

#pragma GCC ivdep
        for (int j = 0; j < quarter_step; ++j) {
            int z0;
            {
                int z = P3[j];
                int m = (unsigned int) R2 * z;
                z0 = ((long long) z * RR - (long long) m * MOD) >> 32;
            }

            int z1;
            {
                int z = P4[j];
                int m = (unsigned int) R2 * z;
                z1 = ((long long) z * RR - (long long) m * MOD) >> 32;
            }

            int sum0 = m_add(P1[j], z0);
            int diff0 = m_sub(P1[j], z0);
            int sum1 = P2[j] + z1;
            int diff1 = P2[j] - z1;

            // [sum0, sum1, diff0, diff1]

            int zz0;
            {
                int z = sum1;
                int m = (unsigned int) R20 * z;
                zz0 = ((long long) z * RR0 - (long long) m * MOD) >> 32;
            }

            int zz1;
            {
                int z = diff1;
                int m = (unsigned int) R21 * z;
                zz1 = ((long long) z * RR1 - (long long) m * MOD) >> 32;
            }

            P1[j]  = m_add(sum0, zz0);
            P2[j]  = m_sub(sum0, zz0);
            P3[j]  = m_add(diff0, zz1);
            P4[j]  = m_sub(diff0, zz1);
        }

        self(self, 4*i+0, k/4);
        self(self, 4*i+1, k/4);
        self(self, 4*i+2, k/4);
        self(self, 4*i+3, k/4);
    };

    int k = n;
    while (k >= 4) k /= 4;

    if (k == 2) {
        int step = n * a;
        int half_step = step / 2;
        for (int j1 = 0; j1 < half_step; ++j1) {
            int j2 = j1 + half_step;

            int diff = m_sub(P[j1], P[j2]);
            P[j1] = m_add(P[j1], P[j2]);
            P[j2] = diff;
        }
        k = n/2;
        dfs(dfs, 0, k);
        dfs(dfs, 1, k);
    } else {
        k = n;
        dfs(dfs, 0, k);
    }

    for (int i = 0; i < m; ++i)
        if (P[i] < 0) P[i] += MOD;
}

template<int a>
void inverse_transform(vector<int> &P) {
    int m = P.size();
    int n = m / a;
    int n_inv = m_transform(modpow(n, MOD - 2));

    vector<int> rev(n);
    for (int i = 1; i < n; ++i) {
        rev[i] = rev[i / 2] / 2 + (i & 1) * n / 2;
    }

    // P = [p * n_inv for p in P]
    for (int i = 0; i < m; ++i)
        P[i] = m_mult(n_inv, P[i]);

    // P = [P[a * rev[i // a] + (i % a)] for i in range(m)]
    for (int i = 1; i < n; ++i)
        if (i < rev[i])
            swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * rev[i]);

    // P = [P[-a * (i // a) + (i % a)] for i in range(m)]
    for (int i = 1; i < n/2; ++i)
        swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * (n - i));

    transform<a>(P);

    // P = [P[a * rev[i // a] + (i % a)] for i in range(m)]
    for (int i = 1; i < n; ++i)
        if (i < rev[i])
            swap_ranges(P.begin() + a * i, P.begin() + a * i + a, P.begin() + a * rev[i]);
}

template<int a>
void fast_polymult_mod(vector<int> &P, vector<int> &Q) {
    int m = P.size();
    int n = m / a;

    transform<a>(P);
    transform<a>(Q);

    vector<int> &PQ = P;
    for (int i = 0; i < n; ++i) {
        vector<unsigned long long> res(2 * a);
        for (int j = 0; j < a; ++j) {
            if (j >= 10 && j % 9 == 8)
                for (int k = j; k < j + a - 10; ++k)
                    res[k] -= (res[k] >> 63) * 9 * MOD2;
            for (int k = 0; k < a; ++k)
                res[j + k] += (long long) P[i * a + j] * Q[i * a + k];
        }

        int c = rt[i/2];
        if (i & 1) c = MOD - c;
        for (int j = 0; j < a; ++j)
            PQ[i * a + j] = (res[j] + c * (res[j + a] % MOD)) % MOD;
    }

    inverse_transform<a>(PQ);
}

template <size_t... N>
void work(std::index_sequence<N...>, int x, std::vector<int>& a, std::vector<int>& b) {
    static void (*ptrs[])(std::vector<int>&, std::vector<int>&) = {&fast_polymult_mod<N+1>...};
    ptrs[x - 1](a, b);
}

void fast_polymult(vector<int> &P, vector<int> &Q) {
    int m1 = P.size();
    int m2 = Q.size();
    int res_len = m1 + m2 - 1;

    int b = 1;
    while ((alim << b) < res_len) ++b;
    int a = ((res_len - 1) >> b) + 1;
    int m = a << b;

    P.resize(m);
    Q.resize(m);

    // Call fast_polymult_mod<a>(P, Q);
    work(std::make_index_sequence<alim>{}, a, P, Q);

    P.resize(res_len);
}


void printPoly(const vll& p){
    int c = 0;
    for (auto x: p){
        cout << x<<" x^" << c++ << " ";
    }
    cout << "\n";
}

ll smallestPowerOf2HigherThanOrEq(ll v) {
    if (v == 0)
        return 1;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
}



ll findPrimRoot(ll p){
    set<ll> primes;
    ll d = 2;
    ll x = p-1;
    ll tot = x;
    while (d*d <= x){
        while (x % d == 0){
            primes.insert(d);
            x /= d;
        }
        d++;
    }
    if (x > 1)
        primes.insert(x);

    for (int g = 2; g < p; ++g){
        // Fuck!
        bool ok = true;
        for (auto y: primes) {
            ok &= binpow(g, tot / y, p) != 1;
            if (!ok)
                break;
        }
        if (ok){
            return g;
        }
    }

}

int main() {
    ll mult = (1<<22);
    int c = 0;
    for (ll x = 1; x*mult < UINT32_MAX; x++){
        ll p = mult*x+1;
        bool ok = true;
        for (ll j = 2; j*j <= p && ok; ++j)
            if (p % j == 0)
                ok = false;
        if (ok) {
            cout << p << ", ";
            c++;
        }
    }

    cout << c;
}