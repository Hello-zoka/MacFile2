#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <set>
#include <random>
#include <chrono>

using namespace std;

#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    int n = 100, m = 100 , q = rng() % 10000 + 1;
    vector<vector<int>> lst(n, vector<int>(m, 0));
    cout << n << " " << m << " " << q << '\n';
    for (int qq = 0; qq < q; qq++) {
        int x = rng() % n, y = rng() % m;
        if (lst[x][y])
            cout << "0 " << x + 1 << " " << y + 1 << '\n';
        else
            cout << "1 " << x + 1 << " " << y + 1 << '\n';
        lst[x][y] ^= 1;
    }
    return 0;
}
