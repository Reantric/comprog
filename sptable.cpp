int sp[(int) 3e5][30];
int query(const int* a,int l, int r){
    if (r == l)
        return sp[r][0];
    int d = (int) log2(highestPowerof2LessThanOrEq(r-l));
    if (a[sp[l][d]] <= a[sp[r-(1<<d)+1][d]])
        return sp[r-(1<<d)+1][d];
    return sp[l][d];
}

for (int i = 0; i < n; ++i){
    cin >> a[i];
    sp[i][0] = i;
}

int LOGN = ceil(log2(n));
for (int j = 1; j < LOGN; ++j) {
    for (int i = 0; i < n - (1 << j) + 1; ++i) {
    if (a[sp[i][j-1]] <= a[sp[i+(1<<(j-1))][j-1]])
        sp[i][j] = sp[i+(1<<(j-1))][j-1];
    else
        sp[i][j] = sp[i][j-1];
        }
}