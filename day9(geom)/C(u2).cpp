#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define int long long

struct pt {
    int x, y;
};

bool operator<(const pt &a, const pt &b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool go(pt a, pt b, pt c) {
    return (a.y - b.y) * (a.x - c.x) <= (a.y - c.y) * (a.x - b.x);
}

void con(vector<pt> &lst) {
    if (lst.size() <= 1) return;
    // sort(lst.begin(), lst.end());
    // for (int i =0; i < lst.size(); i++)
    // cerr << lst[i].x << " " << lst[i].y << '\n';

    vector<pt> up = {lst[0], lst[1]};
    for (int i = 2; i < lst.size(); i++) {
        while (up.size() >= 2 && go(up[up.size() - 2], up.back(), lst[i])) {
            up.pop_back();
        }
        up.push_back(lst[i]);
    }
    lst.clear();
    for (int i = 0; i < up.size(); i++) {
        lst.push_back(up[i]);
    }
}

signed main() {
    int n;
    cin >> n;
    vector<pt> lst;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        lst.push_back({x, y - x * x});
    }
    sort(lst.begin(), lst.end());
    vector<pt> a = {lst[0]};
    for (int i = 1; i < n; i++) {
        if (a[a.size() - 1].x == lst[i].x)
            a.back() = lst[i];
        else
            a.push_back(lst[i]);
    }
    con(a);
    cout << a.size() - 1;
}