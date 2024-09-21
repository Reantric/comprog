template <class T> class Segtree {

private:

    const T DEFAULT = -INF/3;  // Will overflow if T is an int


    vector<T> segtree;

    vector<T> lazy; // add lazy prop later

    int len;


public:

    Segtree(int len) : len(len), segtree(len * 2, DEFAULT), lazy(len * 2, 0) {

    }


    /** Sets the value at ind to val. */

    void set(int ind, T val) {

        ind += len;

        segtree[ind] = val;

        for (; ind > 1; ind /= 2) {

            segtree[ind / 2] = std::max(segtree[ind], segtree[ind ^ 1]);

        }

    }


    /** @return the max element in the range [start, end] */

    T rmax(int start, int end) {
        end++;
        T sum = DEFAULT;

        for (start += len, end += len; start < end; start /= 2, end /= 2) {

            if (start % 2 == 1) { sum = std::max(sum, segtree[start++]); }

            if (end % 2 == 1) { sum = std::max(sum, segtree[--end]); }

        }

        return sum;

    }

};
