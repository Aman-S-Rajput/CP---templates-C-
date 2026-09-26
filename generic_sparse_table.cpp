#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template <typename T, typename Op>
struct SparseTable {
    int n, max_log;
    vector<vector<T>> mat;
    Op op;
    // Build the sparse table in O(N log N)
    SparseTable(const vector<T>& a, Op op = Op()) : op(op) {
        n = a.size();
        max_log = 32 - __builtin_clz(n); // log2(n) + 1
        mat.resize(max_log, vector<T>(n));
        
        // Base case: length 2^0 = 1
        for (int i = 0; i < n; i++) {
            mat[0][i] = a[i];
        }
        // DP: length 2^j
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    // O(1) query for idempotent operations (Min, Max, GCD, AND, OR)
    T query(int L, int R) {
        // Find the largest power of 2 that fits in the range
        int j = 31 - __builtin_clz(R - L + 1);
        
        // Combine the overlapping intervals
        return op(mat[j][L], mat[j][R - (1 << j) + 1]);
    }
};
int main() {
    vector<int> arr = {1, 5, 2, 4, 3, 6, 8, 7};

    // 1. Range Minimum Query (RMQ)
    auto min_op = [](int a, int b) { return min(a, b); };
    SparseTable<int, decltype(min_op)> st_min(arr, min_op);
    cout << "Min [1, 4]: " << st_min.query(1, 4) << "\n"; // Output: 2

    // 2. Range Maximum Query
    auto max_op = [](int a, int b) { return max(a, b); };
    SparseTable<int, decltype(max_op)> st_max(arr, max_op);
    cout << "Max [0, 3]: " << st_max.query(0, 3) << "\n"; // Output: 5

    // 3. Range GCD Query
    auto gcd_op = [](int a, int b) { return std::gcd(a, b); };
    SparseTable<int, decltype(gcd_op)> st_gcd(arr, gcd_op);
    cout << "GCD [0, 7]: " << st_gcd.query(0, 7) << "\n"; // Output: 1

    return 0;
}
