#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

//#define int long long
#define INF 1e9
#define MAXN 1005

struct e {
    int u, v, cap, f;
};

struct be {
    int u, v;
    double c;
};
int n, m;
vector<e> ed, ed2;
vector<vector<int>> lst, lst2;
int q[MAXN];
vector<int> ptr, d;
int lm;
int st, fi;
int bfs() {
    int l = 0, r = 0;
    q[r++] = st;
    d.assign(n + m + 2, INF);
    d[st] = 1;
    while (l < r && d[fi] == INF) {
        int v = q[l++];
        for (int i : lst[v]) {
            int to = ed[i].v;
            if (d[to] == INF && ed[i].cap - ed[i].f >= lm) {
                q[r++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[fi] != INF;
}

int dfs(int v, int f) {
    if (f == 0 || v == fi) return f;
    while (ptr[v] < lst[v].size()) {
        int ind = lst[v][ptr[v]], to = ed[ind].v;
        if (d[to] == d[v] + 1 && ed[ind].cap - ed[ind].f >= f) {
            int cur = dfs(to, f);
            if (cur) {
                ed[ind].f += f;
                ed[ind ^ 1].f -= f;
                return f;
            }
        }
        ptr[v]++;
    }
    return 0;
}


void add_ed(int a, int b, int x) {
    ed.push_back({a, b, x, 0});
    ed.push_back({b, a, 0, 0});
    lst[a].push_back(ed.size() - 2);
    lst[b].push_back(ed.size() - 1);
}

void add_ed2(int a, int b, int x) {
    ed2.push_back({a, b, x, 0});
    ed2.push_back({b, a, 0, 0});
    lst2[a].push_back(ed2.size() - 2);
    lst2[b].push_back(ed2.size() - 1);
}
vector<be> cur;

bool ch(int x){
    lst = lst2;
    ed = ed2;
    for (int i = 0; i <= x; i++){
        add_ed(cur[i].u, cur[i].v, 1);
    }
    int ans = 0;
    for (lm = 1 << 30; lm >= 1;) {
        if (!bfs()) {
            lm >>= 1;
            continue;
        }
        ptr.assign(n + m + 2, 0);
        while (int curr = dfs(st, lm)) ans += curr;
    }
    return ans == n;
}
int bin(){
    int l = -1, r = cur.size() - 1;
    while (l + 1 != r){
        int mi = (l + r) / 2;
        if (ch(mi)){
            r = mi;
        }
        else l = mi;
    }
    return r;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    st = n + m, fi = n + m + 1;
    vector<pair<int, int>> uch, poi;
    lst.assign(n + m + 2, {});
    lst2.assign(n + m + 2, {});
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        uch.push_back({x, y});
        add_ed2(st, i, 1);
    }
    for (int i = 0; i < m; i++) {
        int x, y, mxsz;
        cin >> x >> y >> mxsz;
        add_ed2(n + i, fi, mxsz);
        poi.push_back({x, y});
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cur.push_back({i, n + j, sqrt((1LL * uch[i].first - poi[j].first) * (1ll * uch[i].first - poi[j].first) +
                                          (1LL * uch[i].second - poi[j].second) * (1LL * uch[i].second - poi[j].second))});
        }
    }
    sort(cur.begin(), cur.end(), [&](const be &a, const be &b) {
        return (a.c < b.c);
    });
    cout << setprecision(10) << fixed << cur[bin()].c;
    return 0;
}