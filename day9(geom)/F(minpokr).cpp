#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;


struct pt {
    double x, y;
};
typedef long long ll;
struct circ {
    pt c;
    double r;
};

double dist(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool ptsOnLine(const pt &a, const pt &b, const pt &c) {
    return (c.x * (b.y - a.y) - c.y * (b.x - a.x) == a.x * b.y - b.x * a.y);
}

ll sqr(ll a) {
    return a * a;
}

circ build(const pt &a, const pt &b, const pt &c) {
    if (ptsOnLine(a, b, c)) {
        circ per;
        per.r = -1;
        return per;
    }
    circ cc;
    cc.c.x = -1.0 / 2 *
             ((a.y * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
              b.y * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
              c.y * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
             (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    cc.c.y = 1.0 / 2 *
             ((a.x * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
              b.x * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
              c.x * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
             (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    cc.r = abs(a.x - cc.c.x) * abs(a.x - cc.c.x) + abs(a.y - cc.c.y) * abs(a.y - cc.c.y);
    return cc;
}


circ disk2(vector<pt> lst, pt x, pt y) {
    circ d;
    d.c.x = (y.x + x.x) / 2;
    d.c.y = (y.y + x.y) / 2;
    d.r = dist(y, d.c);
    vector<pt> cur = {x, y};
    for (int i = 0; i < lst.size(); i++) {
        if (dist(lst[i], d.c) > d.r) {
            d = build(x, y, lst[i]);
        }
        cur.push_back(lst[i]);
    }
    return d;
}

circ disk1(vector<pt> lst, pt x) {
    random_shuffle(lst.begin(), lst.end());
    circ d;
    d.c.x = (lst[0].x + x.x) / 2;
    d.c.y = (lst[0].y + x.y) / 2;
    d.r = dist(lst[0], d.c);
    vector<pt> cur = {lst[0], x};
    for (int i = 1; i < lst.size(); i++) {
        if (dist(lst[i], d.c) > d.r) {
            d = disk2(cur, lst[i], x);
        }
        cur.push_back(lst[i]);
    }
    return d;
}

circ disk(vector<pt> lst) {
    random_shuffle(lst.begin(), lst.end());
    circ d;
    d.c.x = (lst[0].x + lst[1].x) / 2;
    d.c.y = (lst[0].y + lst[1].y) / 2;
    d.r = dist(lst[0], d.c);
    vector<pt> cur = {lst[0], lst[1]};
    for (int i = 2; i < lst.size(); i++) {
        if (dist(d.c, lst[i]) > d.r) {
            d = disk1(cur, lst[i]);
        }
        cur.push_back(lst[i]);
    }
    return d;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
//    freopen("circlecover.in", "r", stdin);
//    freopen("circlecover.out", "w", stdout);
    int n;
    cin >> n;
    vector<pt> lst;
    for (int i = 0; i < n; i++) {
        pt x;
        cin >> x.x >> x.y;
        lst.push_back(x);
    }
    circ ans = disk(lst);
    cout << setprecision(10) << fixed << ans.c.x << " " << ans.c.y << '\n';
    cout << setprecision(10) << fixed << sqrtl(ans.r);

    return 0;
}