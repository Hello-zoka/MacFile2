#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <iomanip>

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
vector<pair<double, pair<int, int>>> aa;

vector<cir> lst;
int n, m;

vector<int> par, rnk;

void make_set(int v) {
    par[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == par[v])
        return v;
    return par[v] = find_set(par[v]);
}

void uni(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        par[b] = a;
        if (rnk[a] == rnk[b])
            ++rnk[a];
    }
}

double dist(pt a, pt b) {
    return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<int> answ(int pos) {
    vector<vector<int>> used(4);
    if (find_set(n) == find_set(n + 1)) {
        used[0].push_back(1);
        used[0].push_back(2);
        used[0].push_back(3);
        used[1].push_back(0);
        used[2].push_back(0);
        used[3].push_back(0);
    }
    if (find_set(n) == find_set(n + 2)) {
        used[3].push_back(1);
        used[3].push_back(2);
        used[3].push_back(0);
        used[1].push_back(3);
        used[2].push_back(3);
        used[0].push_back(3);
    }
    if (find_set(n) == find_set(n + 3)) {
        used[0].push_back(3);
        used[0].push_back(2);
        used[1].push_back(2);
        used[1].push_back(3);
        used[3].push_back(0);
        used[3].push_back(1);
        used[2].push_back(0);
        used[2].push_back(1);
    }
    if (find_set(n + 1) == find_set(n + 2)) {
        used[0].push_back(2);
        used[0].push_back(1);
        used[3].push_back(2);
        used[3].push_back(1);
        used[1].push_back(0);
        used[1].push_back(3);
        used[2].push_back(0);
        used[2].push_back(3);
    }
    if (find_set(n + 1) == find_set(n + 3)) {
        used[1].push_back(0);
        used[1].push_back(2);
        used[1].push_back(3);
        used[2].push_back(1);
        used[3].push_back(1);
        used[0].push_back(1);
    }
    if (find_set(n + 2) == find_set(n + 3)) {
        used[2].push_back(0);
        used[2].push_back(1);
        used[2].push_back(3);
        used[1].push_back(2);
        used[3].push_back(2);
        used[0].push_back(2);
    }
    vector<int> curr = {1, 1, 1, 1};
    for (int to : used[aa[pos].second.first]) {
        curr[to] = 0;
    }
    return curr;
}

signed main() {
    cin >> n >> m;
    int w, h;
    par.assign(n + 4, 0);
    rnk.assign(n + 4, 0);
    cin >> w >> h;
    for (int i = 0; i < n; i++) {
        cir cur;
        cin >> cur.c.x >> cur.c.y >> cur.r;
        lst.push_back(cur);
    }
    lst.push_back({{0, -1}, -1});
    lst.push_back({{-1, 0}, -1});
    lst.push_back({{-1, (double) h}, -1});
    lst.push_back({{(double) w, -1}, -1});

    for (int i = 0; i < m; i++) {
        double r;
        int x;
        cin >> r >> x;
        x--;
        aa.push_back({r, {x, i}});
    }
    sort(aa.begin(), aa.end());
    vector<pair<double, pair<int, int>>> d;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < lst.size(); j++) {
            if (lst[j].r == -1) {
                if (j == n) {
                    d.push_back({abs(lst[i].c.x - lst[i].r), {i, j}});
                } else if (j == n + 1) {
                    d.push_back({abs(lst[i].c.y - lst[i].r), {i, j}});
                } else if (j == n + 2) {
                    d.push_back({abs(h - lst[i].c.y - lst[i].r), {i, j}});
                } else {
                    d.push_back({abs(w - lst[i].c.x - lst[i].r), {i, j}});
                }
            } else {
                d.push_back({dist(lst[i].c, lst[j].c) - lst[i].r - lst[j].r, {i, j}});
            }
        }
    }
    sort(d.begin(), d.end());
    int pos = 0;
    vector<vector<int>> ans(m);
    for (int i = 0; i < lst.size(); i++) {
        make_set(i);
    }
    for (int i = 0; i < d.size(); i++) {
        while (pos != aa.size() && d[i].first >= 2 * aa[pos].first) {
            // cout << i << " ";
            ans[aa[pos].second.second] = answ(pos);
            pos++;
        }
        uni(d[i].second.first, d[i].second.second);
        // cerr << d[i].first << " " << d[i].second.first << " " << d[i].second.second << '\n';
    }
    while (pos != aa.size()) {
        ans[aa[pos].second.second] = answ(pos);
        pos++;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 4; j++) {
            if (ans[i][j] == 1) {
                cout << j + 1;
            }
        }
        cout << '\n';
    }
}
