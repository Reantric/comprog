#include "testlib.h"
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "t");
    inf.readEoln();

    int totalN = 0, totalK = 0, totalD = 0;

    for (int i = 0; i < T; ++i) {
        int n = inf.readInt(1, 200000, "n");
        inf.readSpace();
        int k = inf.readInt(1, 200000, "k");
        inf.readSpace();
        int d = inf.readInt(1, 20, "d");
        inf.readEoln();
        ensuref(k <= n,"k larger than n");
        totalN += n;
        totalK += k;
        totalD += d;

        for (int j = 0; j <= d; ++j) {
            inf.readInt(-1000*1000*1000, 1000*1000*1000, "p_i");
            if (j != d) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    ensuref(totalN <= 200000 && totalD <= 20, "Sum of n, k, d over all test cases exceed limits");

    inf.readEof(); // Ensure no extra data is present
}
