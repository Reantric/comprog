#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int sum_n = opt<int>("sum-n");
    int min_n = opt<int>("min-n", 1);
    int sum_d = opt<int>("sum-d");
    int min_d = opt<int>("min-d", 1);
    long long min_value = opt<long long>("min-value", 1);
    long long max_value = opt<long long>("max-value", 1000 * 1000 * 1000);
    int value_bias = opt<int>("value-bias", 0);

    // Ensure the total sum of n does not exceed 2*10^5 and adjust for sum_d and min_d
    sum_n = min(sum_n, 200000);
    sum_d = min(sum_d, 20); // Assuming you want to limit the total sum of d to 20 as an example
    int t = rnd.next(1,min(sum_n/min_n,sum_d/min_d));


    vector<int> d_list = rnd.partition(t, sum_d, min_d);
    vector<int> n_list = rnd.partition(t,sum_n,min_n);
     // Distribute d values across test cases

    cout << min(n_list.size(),d_list.size()) << "\n";
    for (size_t test_case = 0; test_case < min(n_list.size(),d_list.size()); ++test_case) {
        int n = n_list[test_case];
        int d = d_list[test_case]; // Use distributed d value

        // Ensure k is between 1 and n
        int k = rnd.next(1, n);

        vector<long long> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = rnd.wnext(min_value, max_value, value_bias);
        }

        cout << n << " " << k << " " << d << "\n";
        for (int i = 0; i <= d; ++i) {
            cout << rnd.next(min_value, max_value);
            if (i < d) cout << " ";
        }
        cout << "\n";
    }
}