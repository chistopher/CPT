
// baby-step giant-step algorithm
long long discreteLogarithm(long long a, long long b, long long m) {
    long long n = (int) sqrt (m) + 1;

    // Calculate a ^ n
    long long an = 1;
    for (int i = 0; i<n; ++i)
        an = (an * a) % m;

    unordered_map<long long, long long> value;

    // Store all values of a^(n*i) of LHS
    for (long long i = 1, cur = an; i<= n; ++i)
    {
        if (! value[ cur ])
            value[ cur ] = i;
        cur = (cur * an) % m;
    }

    for (long long i = 0, cur = b; i<= n; ++i)
    {
        // Calculate (a ^ j) * b and check
        // for collision
        if (value[cur])
        {
            long long ans = value[cur] * n - i;
            if (ans < m)
                return ans;
        }
        cur = (cur * a) % m;
    }
    return -1;
}


// iterating prime factorization of b
auto b = 999999;
for (long long i=2; i*i<=b; i++) {
    int prime_exponent = 0;
    while (b % i == 0) {
        prime_exponent++;
        b /= i;
    }
    if (prime_exponent == 0) continue;

    // at this point we know that i is a prime
    // and have its exponent in b's factorization
}
if (b!=1) [
        // b holds a single large prime bigger than sqrt of original b
}
