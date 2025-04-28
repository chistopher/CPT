
// #include <bits/stdc++.h> // includes all; gcc only
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

// ignore next 2 lines for now. It's just for lazy people to type less
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      begin(a),end(a)

using namespace std; // lets you omit the `std::` prefix; never use in real code!
using ll = long long; // alias for 64bit integers

int main() {
    ios::sync_with_stdio(false); // make IO faster as long as you don't use C-style IO (scanf/printf)
    cin.tie(nullptr); // don't flush stdout each time you read stdin
    cout.precision(10); // print floats with more digits

    // READ INPUT
    int n;
    cin>>n; // skips all whitespace
    vector input(n, 0); // type is deduced from parameter `0` -> vector<int>
    for(auto& ai : input) { // `auto` to let the compiler determine the type
        // without the `&` we would iterate over copies and leave `input` unchanged
        cin >> ai; // read directly into `&ai`
    }

    // COMPUTE RESULT
    ll sum = 0; // `0` is implicitly cast from `int` to `long long`
    for(auto& ai : input)
        sum += ai;  // can omit braces if loop body is just one statement
    // actually, let's use standard lib for this!
    auto sum2 = accumulate(begin(input), end(input), 0ll); // literal `0ll` determines the return type
    assert(sum == sum2);

    // OUTPUT RESULT
    cout << sum << '\n';

    return 0; // stdout will flush when main ends (or you flush manually)
}
