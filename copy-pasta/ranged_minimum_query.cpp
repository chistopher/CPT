
// integer logarithmus
constexpr int ilog(unsigned int i) {
    return 31 - __builtin_clz(i);
}

const auto N = 5000; // pls insert max value for n
const auto LOGN = ilog(N);

int rmq[N][LOGN];
void buildRMQ(vector<int>& arr) {
    auto n = arr.size();
    for(int i=0; i<n; ++i) rmq[i][0] = arr[i];
    for (int k = 1; k <= ilog(n)+1; k++) {
        for (int i = 0; i < n; i++) {
            if (i + (1 << (k-1)) >= n)
                break;
            rmq[i][k] = max(rmq[i][k-1], rmq[i + (1 << (k-1))][k-1]);
        }
    }
}

int query(int l, int r) {
    int log = ilog(r-l);
    return max(rmq[l][log], rmq[r - (1 << log)][log]);
}
