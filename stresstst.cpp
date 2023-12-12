std::random_device rd;
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> distribA(1,(int) 1000);
std::uniform_int_distribution<> distribN(1,(int) 100000);

for (int y = 0; y < 1; ++y) {
    int n = distribN(gen);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    a[i] = distribA(gen);

    }
}