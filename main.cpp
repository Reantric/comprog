#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const ll INF = LONG_LONG_MAX - 1;
const int MOD = 1e9 + 7;
const int MOD2 = 998244353;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
const double PI = 3.14159265358979323846;
#define fast_io ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define print(a) cout << (a) << "\n";
#define printPair(a) cout << (a).first << " " << (a).second << "\n";

template<typename T>
void printArray(T arr[], unsigned int n) {
    for (int t = 0; t < n; ++t) {
        cout << arr[t] << " ";
    }
    cout << endl;
}

void put(bool p) {
    print(p ? "YES" : "NO");
}

template<typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/*std::ostream& operator<<(std::ostream& o, const __int128& x) {
    if (x == std::numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
} */

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

long long int mod(long long int a, long long int b) {
    long long int ret = a % b;
    if (ret < 0)
        ret += b;
    return ret;
}

ll highestPowerof2LessThan(ll v) {
    // check for the set bits
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    v >>= 1;
    return v;
}

ll highestPowerof2LessThanOrEq(ll x) {
    // check for the set bits
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x ^ (x >> 1);
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

ll quickCeil(ll x, ll y) {
    return x / y + (x % y != 0);
}

bool isOverflow(ll a, ll b) {
    return log10(a) + log10(b) > 18;
}

int numberOfOneBits(int x) {
    return __builtin_popcountll(x);
}

ll preciseFloor(ll a, ll b) {
    ll val = a / b;
    while (val * b > a)
        val--;
    return val;
}


void fenwickUpdate(int *a, int n, int i, int val) {
    while (i < n) {
        a[i] += val;
        i += i & -i;
    }
}

int fenwickRightHandQuery(const int *a, int r) {
    int sum = 0;
    while (r > 0) {
        sum += a[r];
        r -= r & -r;
    }
    return sum;
}

int fenwickQuery(int *a, int l, int r) { // assuming one-indexed array!
    return fenwickRightHandQuery(a, r) - fenwickRightHandQuery(a, l - 1);
}

template<ll mod = MOD>
struct mint {
    ll x;

    mint() : x(0) {}

    mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    mint &operator+=(const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint &operator-=(const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint &operator*=(const mint &a) {
        x = (ull) x * a.x % mod;
        return *this;
    }

    mint pow(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while (pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }

    mint inv() const {
        assert(x != 0);
        ll t = x;
        ll res = 1;
        while (t != 1) {
            ll z = mod / t;
            res = (ull) res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }

    mint &operator/=(const mint &a) {
        return *this *= a.inv();
    }

    mint operator+(const mint &a) const {
        return mint(*this) += a;
    }

    mint operator-(const mint &a) const {
        return mint(*this) -= a;
    }

    mint operator*(const mint &a) const {
        return mint(*this) *= a;
    }

    mint operator/(const mint &a) const {
        return mint(*this) /= a;
    }

    bool operator==(const mint &a) const {
        return x == a.x;
    }

    bool operator!=(const mint &a) const {
        return x != a.x;
    }

    bool operator<(const mint &a) const {
        return x < a.x;
    }

    friend ostream &operator<<(ostream &out, const mint &m) {
        out << m.x;
        return out;
    }
};

template <class T> class Segtree {

private:

    const T DEFAULT = INF/2;  // Will overflow if T is an int


    vector<T> segtree;

    int len;


public:

    Segtree(int len) : len(len), segtree(len * 2, DEFAULT) {}


    /** Sets the value at ind to val. */

    void set(int ind, T val) {

        ind += len;

        segtree[ind] = val;

        for (; ind > 1; ind /= 2) {

            segtree[ind / 2] = std::min(segtree[ind], segtree[ind ^ 1]);

        }

    }


    /** @return the minimum element in the range [start, end) */

    T rmin(int start, int end) {

        T sum = DEFAULT;

        for (start += len, end += len; start < end; start /= 2, end /= 2) {

            if (start % 2 == 1) { sum = std::min(sum, segtree[start++]); }

            if (end % 2 == 1) { sum = std::min(sum, segtree[--end]); }

        }

        return sum;

    }

};

using Mint = mint<MOD>;

struct fenwick { // not one-indexed
    vector<ll> a;
    int n;

    fenwick(int ne) {
        n = ne;
        a = vector<ll>(n + 1, 0);
    }

    void update(int i, ll v) { // later make this subscript overloaded
        i++;
        while (i <= n) {
            a[i] += v;
            i += i & -i;
        }
    }

    ll frq(int r) {
        ll sum = 0;
        while (r > 0) {
            sum += a[r];
            r -= r & -r;
        }
        return sum;
    }

    ll query(int l, int r) {
        l++;
        r++;
        return frq(r) - frq(l - 1);
    }
};


struct dsu {
    vi parent, s;
    int numCC;

    dsu(int n) {
        parent = vi(n);
        numCC = n;
        s = vi(n, 1);
        for (int i = 1; i < n; ++i)
            parent[i] = i;
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            numCC--;
            if (s[u] < s[v])
                swap(u, v);
            parent[v] = u;
            s[u] += s[v];
        }
    }

    int getNumConnComp() const {
        return numCC;
    }


};


/* ll spf[(int) 1e5 + 10]; // cler
void sieve(ll n) {
    for (int i = 1; i <= n; ++i)
        spf[i] = i & 1 ? i : 2;
    for (int i = 3; i * i <= n; ++i) {
        if (spf[i] == i) {
            for (int p = i * i; p <= n; p += i) {
                if (spf[p] == p)
                    spf[p] = i;
            }
        }
    }
} */

struct stronglyConnectedComponents {
    int id = 1;
    int scc = 0;
    stack<int> s;
    vi ids,low;
    vll clumped;
    vector<bool> vis;
    vector<set<int>> cond; // condensed Graph hu
    vi* adj;
    vi sz;

    stronglyConnectedComponents(vi* g, int n){ // assuming 1 indexed, which it usually always is
        adj = g;
        ids = vi(n+1,-1);
        low = vi(n+1,0);
        clumped = vll(n+1,0);
        vis = vector<bool>(n+1,false);
        cond = vector<set<int>>(n+1);
        sz = vi(n+1);

        for (int i = 1; i <= n; ++i){
            if (ids[i] != -1)
                continue;
            dfs(i);
        }

        for (int i = 1; i <= n; ++i){
            sz[low[i]]++;
            for (auto c: adj[i]){
                if (low[c] == low[i])
                    continue;
                cond[low[i]].insert(low[c]);
            }
        }
    }



    void dfs(int v){
        s.push(v);
        vis[v] = true;
        ids[v] = low[v] = id++;

        for (auto c: adj[v]){
            if (ids[c] == -1)
                dfs(c);
            if (vis[c])
                low[v] = min(low[v],low[c]);
        }

        if (ids[v] == low[v]){
            while (!s.empty()){
                int x = s.top();
                s.pop();
                vis[x] = false;
                low[x] = ids[v];
                if (x == v)
                    break;
            }
            scc++;
        }
    }

    int getSCCcnt(){
        return scc;
    }
};

const int MAXN = (int) 2e5 + 7;


void preload() {
    //sieve((int) 1e5 + 3);
}

void solve() {
    ll a,b,c,d;
    cin >> a >> b >> c >> d;
    ll g = gcd(c,d);
    c /= g;
    d /= g;

    int n = 1+floor(log10(a));
    for (int mask = 0; mask < (1 << n); ++mask){
        // choose some values of a to REMOVE
        // then check if a*d/c is b with the vals from a removed
        vi freqR(10,0);
        auto astr = to_string(a);
        string a1str;
        for (int i = 0; i < astr.size(); ++i){
            if ((mask & (1<<i)) == 0) {
                freqR[astr[i] - '0']++;

            } else
                a1str += astr[i];
        }
        if (a1str.empty())
            continue;
        ll a1 = stoll(a1str);
        if (a1 % c != 0 || a1 == 0 || a1str[0] == '0')
            continue;
        if (log10(a1) + log10((d+0.0)/c) > 18)
            continue;
        ll x = a1/c * d;
        // so x is the new b, now we need to remove A's shit

        if (x == 0)
            continue;
        //compare x and b

        auto x1 = to_string(x);
        auto b1 = to_string(b);

        int y = 0;
        vi freq(10,0);
        for (int i = 0; i < b1.size(); ++i){
            if (y < x1.size() && b1[i] == x1[y]){
                y++;
                continue;
            } else
                freq[b1[i]-'0']++;
        }
        bool ok = y == x1.size();
        for (int i = 0; i < 10; ++i)
            ok &= freq[i] == freqR[i];
        ok &= x1[0] != 0;
        if (ok){
            print("possible")
            cout << a1 << " " << x << "\n";
            return;
        }
    }
    print("impossible");


}


int main() {
    fast_io;
    preload();
    int t;
    t = 1;
    //cin >> t;
    while (t-- > 0)
        solve();
    return 0;
}