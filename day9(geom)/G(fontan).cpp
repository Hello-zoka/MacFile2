#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

// #define int long long
// #define double long double
double INF;
struct pt {
    double x, y;
};
struct cir {
    pt c;
    double r;
};
vector<cir> lst;
int n;
double m;

double dist(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double sqr(double x) {
    return x * x;
}

bool ch(pt a, pt b) {
    // 1 1000
    // if (a.y < 0 || b.y < 0) return true;
    if (abs(a.x - b.x) < 1e-7 || abs(a.y - b.y) < 1e-7) return false;
    for (int i = 0; i < n; i++) {
        if (dist(a, lst[i].c) <= sqr(lst[i].r + m) && dist({a.x, b.y}, lst[i].c) <= sqr(lst[i].r + m) &&
            dist({b.x, a.y}, lst[i].c) <= sqr(lst[i].r + m) && dist(b, lst[i].c) <= sqr(lst[i].r + m)) {
            // cerr << "Wrf";
            return true;
        }
    }
    return ch(a, {(a.x + b.x) / 2, (a.y + b.y) / 2}) && ch({(a.x + b.x) / 2, a.y}, {b.x, (a.y + b.y) / 2}) &&
           ch({a.x, (a.y + b.y) / 2}, {(a.x + b.x) / 2, b.y}) && ch({(a.x + b.x) / 2, (a.y + b.y) / 2}, b);
}

double w, h;

double bin() {
    double l = 0, r = INF;
    while (r - l > 1e-7) {
        m = (l + r) / 2;
        // cerr << l << " " << r << " " << m << '\n';
        if (w < m * 2 || h < m * 2) {
            r = m;
            continue;
        }
        if (ch({m, m}, {w - m, h - m}))
            r = m;
        else
            l = m;
    }
    // cerr << 1;
    return l;
}

signed main() {
    cin >> w >> h;
    cin >> n;
    INF = min(w, h) / (double) 2 + 0.1;
    for (int i = 0; i < n; i++) {
        cir x;
        cin >> x.c.x >> x.c.y >> x.r;
        lst.push_back(x);
    }
    double x = bin();
    cout << setprecision(20) << fixed << x;
}