#include "testlib.h"


int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerTestlibCmd(argc, argv);
    // Now there are three global variables specifying testlib streams:
    // inf - stream with the testdata.
    // ouf - stream with the contestant output.
    // ans - stream with the jury answer.
    // All those streams provide the similar interface for reading data.

    // This function reads a single integer from the participant output that
    // should be between -2000 and 2000. If it doesn't belong to the specified
    // range, checker finishes with verdict _pe and comment saying that [sum of numbers]
    // is outside of the specified range.
    int t = inf.readInt(); // Reading number of test cases

    for(int caseNo = 1; caseNo <= t; caseNo++) {
        // Reading each test case parameters
        int n = inf.readInt();
        inf.readSpace();
        int k = inf.readInt();
        inf.readSpace();
        int d = inf.readInt();
        inf.readEoln();

        // Reading coefficients, note that they are not directly used in the checker
        // but we need to read them to correctly follow the input
        for(int i = 0; i <= d; i++) {
            inf.readInt();
            if (i < d) {
                inf.readSpace(); // Reading space between coefficients
            } else {
                inf.readEoln(); // Reading end of line after the last coefficient
            }
        }

        // Since the problem statement doesn't specify a range for the output integers
        // but you might want to set a reasonable one based on the context or constraints
        // Here, assuming the output should be a non-negative integer within a certain range
        long long MOD = 1000000007; // Example modulus or range, adjust accordingly

        long long pans = ouf.readLong(0ll, MOD-1, "participant's answer");
        long long jans = ans.readLong(0ll, MOD-1, "jury's answer"); // Reading jury's answer

        if (pans != jans)
            quitf(_wa, "Case #%d failed: expected %lld, found %lld", caseNo, jans, pans);
    }

    quitf(_ok, "All cases passed! Nice job Snow! maybe you can defeat the moniforces...");
}