#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define int long long

struct pt {
    int x, y;
};

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int sq(vector<pt> &lst) {
    int res = 0;
    for (int i = 0; i < lst.size(); i++) {
        pt p2 = lst[i], p1 = lst[(i - 1 + lst.size()) % lst.size()];
        res += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return abs(res) / 2;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pt> lst;
    for (int i = 0; i < n; i++) {
        pt x;
        cin >> x.x >> x.y;
        lst.push_back(x);
    }
    if (n < 3) {
        cout << 0;
        return 0;
    }
    int s = sq(lst);
    int cel = 0;
    for (int i = 0; i < n; i++) {
        cel += gcd(abs(lst[i].x - lst[(i - 1 + n) % n].x), abs(lst[i].y - lst[(i - 1 + n) % n].y));
    }
    cout << s - cel / 2 + 1;
}