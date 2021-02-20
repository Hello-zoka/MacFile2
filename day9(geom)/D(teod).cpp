#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define int long long

struct pt {
    int x, y;
};
struct ang {
    int a, b;
};


bool operator<(const ang &a, const ang &b) {
    if (b.b == 0 && a.b == 0) {
        return a.a < b.a;
    }
    return a.a * b.b < b.a * a.b;
}

int sq(pt a, pt b, pt c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<pt> lst;
    int ind = -1;
    for (int i = 0; i < n; i++) {
        pt a;
        cin >> a.x >> a.y;
        lst.push_back(a);
        if (ind == -1 || lst[i].x < lst[ind].x || (lst[i].x == lst[ind].x && lst[i].y < lst[ind].y)) {
            ind = i;
        }
    }
    pt st = lst[ind];
    rotate(lst.begin(), lst.begin() + ind, lst.end());
    lst.erase(lst.begin());
    n--;
    vector<ang> a(n);
    for (int i = 0; i < n; i++) {
        a[i].a = lst[i].y - st.y;
        a[i].b = lst[i].x - st.x;
        if (a[i].a == 0)
            a[i].b = a[i].b < 0 ? -1 : 1;
    }
    for (int i = 0; i < m; i++) {
        pt cur;
        cin >> cur.x >> cur.y;
        bool in = false;
        if (cur.x >= st.x) {
            if (cur.x == st.x && cur.y == st.y) {
                in = true;
            } else {
                ang x = {cur.y - st.y, cur.x - st.x};
                if (x.a == 0) {
                    x.b = x.b < 0 ? -1 : 1;
                }
                auto it = upper_bound(a.begin(), a.end(), x);
                if (it == a.end() && x.a == a[n - 1].a && x.b == a[n - 1].b) {
                    it--;
                }
                if (it != a.end() && it != a.begin()) {
                    int p1 = (int) (it - a.begin());
                    if (sq(lst[p1], lst[p1 - 1], cur) <= 0)
                        in = true;
                }
            }
        }
        if (in) k--;
    }
    if (k <= 0)
        cout << "YES";
    else
        cout << "NO";
}