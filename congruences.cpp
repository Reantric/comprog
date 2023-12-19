long long chinese_remainder_theorem(vector<pll> const& congruences) {
long long M = 1;
for (auto const& congruence : congruences) {
M *= congruence.second;
}

pi eegcd(int a, int b) {
    int x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return {x,y};
}

long long solution = 0;
for (auto const& congruence : congruences) {
long long a_i = congruence.first;
long long M_i = M / congruence.second;
long long N_i = mod_inv(M_i, congruence.second);
solution = (solution + a_i * M_i % M * N_i) % M;
}
return solution;
}