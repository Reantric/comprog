/**
 * gen-array-with-opt
 *                      -sum-n <num>
 *                      [-min-n <num>]
 *                      [-min-value <num>] [-max-value <num>]
 *                      [-value-bias <num>]
 *
 * Generate a test with `test-count` test cases, each test case is an
 * array. The sum of lengths of all arrays will equal `sum-n`.
 *
 * Arguments:
 * -sum-n: specify the sum of array lengths over all test cases. Required.
 * -min-n: specify the minimum array length for all test cases. Default: 1.
 * -min-value: specify the minimum value for the array element. Default: 1.
 * -max-value: specify the maximum value for the array element. Default: 10^9.
 * -value-bias: specify the bias for generating the value. The bigger the
 *  _positive_ value-bias, the closer the element to max-value. The smaller the
 *  _negative_ value-bias, the closer the element to min-value. See rnd.wnext()
 *  function. Default: 0 (no bias).
 */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int sum_n = opt<int>("sum-n");
    int min_n = opt<int>("min-n", 1);

    int min_value = opt<int>("min-value", -1000*1000*1000);
    int max_value = opt<int>("max-value", 1000 * 1000 * 1000);
    int value_bias = opt<int>("value-bias", 0);

    vector<int> n_list = rnd.partition(1, sum_n, min_n);
    for (int test_case = 0; test_case < 1; ++test_case) {
        int n = n_list[test_case];
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = rnd.wnext(min_value, max_value, value_bias);
        }
        println(n);
        println(arr);
    }
}