
template <ll p, ll M>
struct PHash {
    ll curHash = 0;
    ll curPow = 1;

    void add(ll x){
        curHash = (curHash + curPow*x) % M;
        curPow *= p;
        curPow %= M;
    }

    PHash operator+(PHash const &other) const{
        return {(curHash + other.curHash) % M};
    }

    PHash operator-(PHash const &other) const {
        return {(M + curHash - other.curHash) % M};
    }

    PHash operator*(PHash const &other) const {
        return {(curHash * other.curHash) % M};
    }

    bool operator==(PHash const &other) const {
        return curHash == other.curHash;
    }

    bool operator<(const PHash& other) const {
        return curHash < other.curHash;
    }

};

struct CombinedHash {
    PHash<31, 1000000007> h1;
    PHash<37, 998244353> h2;
    PHash<41, 1000000009> h3;

    // Add element to all three hashes
    void add(ll x) {
        h1.add(x);
        h2.add(x);
        h3.add(x);
    }

    // Combine two CombinedHash objects
    CombinedHash operator+(const CombinedHash &other) const {
        CombinedHash result;
        result.h1 = h1 + other.h1;
        result.h2 = h2 + other.h2;
        result.h3 = h3 + other.h3;
        return result;
    }

    // Subtract two CombinedHash objects
    CombinedHash operator-(const CombinedHash &other) const {
        CombinedHash result;
        result.h1 = h1 - other.h1;
        result.h2 = h2 - other.h2;
        result.h3 = h3 - other.h3;
        return result;
    }

    // Compare two CombinedHash objects for equality
    bool operator==(const CombinedHash &other) const {
        return h1 == other.h1 && h2 == other.h2 && h3 == other.h3;
    }

    bool operator<(const CombinedHash& other) const {
        if (h1 < other.h1) return true;
        if (other.h1 < h1) return false;
        if (h2 < other.h2) return true;
        if (other.h2 < h2) return false;
        return h3 < other.h3;
    }
};

struct CombinedHashHasher {
    std::size_t operator()(const CombinedHash& ch) const {
        // Combine the hashes of h1, h2, and h3
        std::size_t res = 0;
        res ^= std::hash<long long>()(ch.h1.curHash) + 0x9e3779b9 + (res << 6) + (res >> 2);
        res ^= std::hash<long long>()(ch.h2.curHash) + 0x9e3779b9 + (res << 6) + (res >> 2);
        res ^= std::hash<long long>()(ch.h3.curHash) + 0x9e3779b9 + (res << 6) + (res >> 2);
        return res;
    }
};