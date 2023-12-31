#include "testlib.h"

using namespace std;
const int LB = (int) 1e9;
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1,100000,"n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(-LB, LB, "a");
        if (i != n-1)
            inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
}
