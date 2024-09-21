/*
 * CRT
 */
pll eegcd(ll a, ll b) {
    ll x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return {x,y};
}

ll mod_inv(long long a, long long b){
    auto x = eegcd(a,b);
    if (a*x.first + b*x.second != 1)
        return -1;
    return (x.first + b) % b;
}

long long chinese_remainder_theorem(vector<pll> const& congruences) {
long long M = 1;
for (auto const& congruence : congruences) {
M *= congruence.second;
}

long long solution = 0;
for (auto const& congruence : congruences) {
long long a_i = congruence.first;
long long M_i = M / congruence.second;
long long N_i = mod_inv(M_i, congruence.second);
if (N_i == -1)
return -1;
solution = (solution + a_i * M_i % M * N_i) % M;
}
return solution;
}

/*
 * FACTORIALS
 */
Mint fac[(int) 3e5 + 3];
Mint inv[(int) 3e5 + 3];
void preload() {
    // sieve(MAXN);
    fac[0] = 1;
    for (int i = 1; i <= (int) 3e5; ++i)
        fac[i] = fac[i-1]*i;

    inv[(int) 3e5] = binpow(fac[(int) 3e5].x,MOD-2,MOD);
    // 1/n! = 1/n * 1/(n-1)!
    for (int i = ((int) 3e5)-1; i >= 0; --i)
        inv[i] = inv[i+1]*(i+1);

}

Mint choose(int n, int k){
    if (k == 0 || k == n)
        return 1;
    if (k < 0 || k > n)
        return 0;
    return fac[n]*inv[k]*inv[n-k];
}