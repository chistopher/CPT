
vector<size_t> z_algorithm(vector<size_t>& s) {
    size_t l = 0, r = 0;
    vector<size_t> z(s.size(), 0);
    for(size_t i = 1; i < s.size(); ++i) {
        size_t zi = 0;
        if(i <= r)
            zi = min(z[i-l], r - i + 1);
        while (zi + i < s.size() && s[zi] == s[zi + i])
            zi++;
        z[i] = zi;
        if (r < i + zi - 1)
            l = i, r = i + zi - 1;
    }
    return z;
}

vector<size_t> prefix_function(vector<size_t>& s) {
    vector<size_t> b(s.size(), 0);
    for(size_t i = 1; i < s.size(); ++i) {
        auto k = b[i - 1];
        while(k > 0 && s[k] != s[i])
            k = b[k - 1];
        if(s[k] == s[i])
            b[i] = k + 1;
    }
    return b;
}
