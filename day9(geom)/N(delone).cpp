#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>
#include <map>

using namespace std;

#define int long long
#define double long double

struct pt {
    double x, y;
};
struct cir {
    pt c;
    double r;
};
const double eps = 0.0000005;

double dist(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool PtsOnLine(pt a, pt b, pt c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) == 0;
}

int sqr(int a) {
    return a * a;
}

cir build(pt a, pt b, pt c) {
    cir res;
//    if (PtsOnLine(a, b, c)) {
//        res.r = -1;
//        return res;
//    }
    res.c.x = -1.0 / 2 *
              ((a.y * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
               b.y * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
               c.y * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
              (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    res.c.y = 1.0 / 2 *
              ((a.x * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
               b.x * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
               c.x * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
              (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    res.r = dist(a, res.c);
    return res;
}

bool ch(pt a, pt b, pt c, pt d) {
    cir x = build(a, b, c);
    cir y = build(a, b, d);
    return !(dist(d, x.c) - x.r < -eps || dist(c, y.c) - y.r < -eps);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int q = 0; q < t; q++) {
        vector<pt> lst;
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            pt x;
            cin >> x.x >> x.y;
            lst.push_back(x);
        }
        map<pair<int, int>, pair<int, int>> cur;
        vector<pair<int, int>> edg;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            int aa = min(a, min(b, c)), cc = max(a, max(b, c)), dd;
            if (a != aa && a != cc) dd = a;
            if (b != aa && b != cc) dd = b;
            if (c != aa && c != cc) dd = c;
            a = aa;
            b = dd;
            c = cc;
            if (cur.find(make_pair(a, b)) == cur.end()) {
                // cerr << i << " 1 ";
                cur[make_pair(a, b)] = {c, -1};
            } else {
                // cerr << i << " 2 ";
                cur[make_pair(a, b)].second = c;
            }
            if (cur.find(make_pair(a, c)) == cur.end()) {
                cur[make_pair(a, c)] = {b, -1};
            } else {
                cur[make_pair(a, c)].second = b;
            }
            if (cur.find(make_pair(b, c)) == cur.end()) {
                cur[make_pair(b, c)] = {a, -1};
            } else {
                cur[make_pair(b, c)].second = a;
            }
            edg.push_back({a, b});
            edg.push_back({a, c});
            edg.push_back({b, c});
        }
        int bl = 1;
        for (int i = 0; i < edg.size(); i++) {
            pair<int, int> x = cur[edg[i]];
            int a = x.first, b = x.second;
            // cerr << edg[i].first << " " << edg[i].second << " " << a << " " << b << '\n';
            if (b == -1 || a == -1) continue;
            if (!ch(lst[edg[i].first - 1], lst[edg[i].second - 1], lst[a - 1], lst[b - 1])) {
                bl = 0;
                break;
            }
        }
        if (bl)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}