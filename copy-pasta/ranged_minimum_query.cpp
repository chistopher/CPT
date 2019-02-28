
constexpr int ilog(unsigned int i) {
    return 31 - __builtin_clz(i); // integer logarithm
}

const auto N = 5000; // pls insert max value for n
const auto LOGN = ilog(N);

long long rmq[N][LOGN+1]; // rmq[i][j] stores min of interval [i, i+2^j)
void buildRMQ(vector<long long>& arr) {
    auto n = arr.size();
    for(int i=0; i<n; ++i) rmq[i][0] = arr[i];
    // compute rmq array via DP
    // the interval [i, i+2^k) splits nicely into two sub-intervals [i, i+2^{k-1}) and [i+2^{k-1}, i+2^k)
    for (int k = 1; k <= ilog(n); k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            rmq[i][k] = max(rmq[i][k-1], rmq[i + (1 << (k-1))][k-1]);
}

long long query(int l, int r) {
    int log = ilog(r-l);
    return max(rmq[l][log], rmq[r - (1 << log)][log]);
}

