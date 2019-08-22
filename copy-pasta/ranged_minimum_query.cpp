
auto ilog = [](uint32_t i) { return 31 - __builtin_clz(i); };
using T = long long;
int n = 10;
auto arr = vector<T>(n);

auto rmq = vector<vector<T>>(ilog(n)+1, vector<T>(n)); // rmq[k][i] stores min of interval [i, i+2^k)
// the interval [i, i+2^k) splits nicely into two sub-intervals [i, i+2^{k-1}) and [i+2^{k-1}, i+2^k)
rmq[0] = arr; // init bottom level
for (int k = 1; k <= ilog(n); k++)
    for (int i = 0; i + (1 << k) <= n; i++)
        rmq[k][i] = min(rmq[k-1][i], rmq[k-1][i + (1 << (k-1))]);
auto query = [&rmq, &ilog](int l, int r) { // exclusive query
    auto log = ilog(r-l);
    return min(rmq[log][l], rmq[log][r - (1 << log)]);
};


// RMQ query object generator
auto createRMQ = [](int n, auto init, auto combine) { // returns an exclusive query lambda
    using T = decltype(init(0));
    auto ilog = [](uint32_t i) { return 31 - __builtin_clz(i); };
    auto rmq = vector<vector<T>>(ilog(n)+1, vector<T>(n)); // rmq[k][i] stores min of interval [i, i+2^k)
    for (int i = 0; i < n; ++i) rmq[0][i] = init(i); // init bottom level
    for (int k = 1; k <= ilog(n); k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            rmq[k][i] = combine(rmq[k-1][i], rmq[k-1][i + (1 << (k-1))]);
    return [rmq=move(rmq), ilog, combine](int l, int r) mutable { // mutable s.t. combine can take non-const args
        auto log = ilog(r-l);
        return combine(rmq[log][l], rmq[log][r - (1 << log)]);
    };
};
