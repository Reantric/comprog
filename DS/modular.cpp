template<ll mod = MOD2> struct mint {
    ll x;

    mint() : x(0) {}
    mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    mint& operator += (const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator -= (const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &a) {
        x = (ull)x * a.x % mod;
        return *this;
    }
    mint pow(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
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
        while(t != 1) {
            ll z = mod / t;
            res = (ull)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }
    mint operator + (const mint &a) const {
        return mint(*this) += a;
    }
    mint operator - (const mint &a) const {
        return mint(*this) -= a;
    }
    mint operator * (const mint &a) const {
        return mint(*this) *= a;
    }
    mint operator / (const mint &a) const {
        return mint(*this) /= a;
    }

    bool operator == (const mint &a) const {
        return x == a.x;
    }
    bool operator != (const mint &a) const {
        return x != a.x;
    }
    bool operator < (const mint &a) const {
        return x < a.x;
    }

    friend ostream& operator << (ostream &out, const mint& m){
        out << m.x;
        return out;
    }
};

using Mint = mint<>;



Mint fac[MAXN+2];
Mint inv[MAXN+2];
void preload() {
    fac[0] = 1;
    for (int i = 1; i <= MAXN; ++i)
        fac[i] = fac[i-1]*i;

    inv[MAXN] = binpow(fac[MAXN].x,MOD-2,MOD);
    // n! (n+1) = (n+1)! => 1/n! = (n+1)/(n+1)!
    for (int i = MAXN-1; i >= 0; --i){
        inv[i] = inv[i+1]*(i+1);
    }


    //sieve(MAXN);
}

Mint choose(int n, int k){
    return fac[n]*inv[k]*inv[n-k];
}

ll spf[MAXN + 10]; // cler
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
}