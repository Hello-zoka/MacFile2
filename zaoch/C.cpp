#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

//#define int long long

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<vector<pair<int, int>>> lst;
    lst.assign(n, {});
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        lst[a].push_back({b, c});
        lst[b].push_back({a, c});
    }
    vector<bool> zap(n, 0);
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x--;
        zap[x] = true;
    }
    priority_queue<pair<int, int>> q;
    q.push({s, 0});
    vector<int> d(n, -1);
    vector<int> used(n, 0);
    d[0] = s;
    while (!q.empty()) {
        pair<int, int> x = q.top();
        q.pop();
        if (used[x.second]) continue;
        if (zap[x.second]) {
            x.first = s;
            d[x.second] = s;
        }
        for (int i = 0; i < lst[x.second].size(); i++) {
            int to = lst[x.second][i].first, cst = lst[x.second][i].second;
            if (d[to] < x.first - cst) {
                d[to] = x.first - cst;
                q.push({d[to], to});
                used[to] = 0;
            }
        }
        used[x.second] = 1;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (d[i] != -1) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << " ";

    return 0;
}