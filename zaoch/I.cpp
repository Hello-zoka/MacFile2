#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//#define int long long
#define ll long long
vector<vector<int>> g;

int tim = 1;
vector<int> vis;

ll sz;
void dfs(int st){
    vis[st] = tim;
    sz++;
    for (int to : g[st]){
        if (vis[to] != tim){
            dfs(to);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> val(n - 1);
    vector<pair<int, int>> edg;
    //vector<vector<pair<int, int>>> lst(n);
    for (int i = 1; i < n; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        v--;
        u--;
        val[i - 1] = x;
        //lst[u].push_back({v, i - 1});
        //lst[v].push_back({u, i - 1});
        edg.push_back({u, v});
    }
    vector<vector<int>> ind;;
    vector<int> used(1000007, -1);
    vector<int> del;
    for (int i = 0; i < n - 1; i++) {
        int x = val[i];
        for (int j = 1; j * j <= x; j++) {
            if (x % j == 0) {
                if (used[j] == -1) {
                    used[j] = ind.size();
                    ind.push_back({});
                    del.push_back(j);
                }
                ind[used[j]].push_back(i);
                if (j * j != x) {
                    int y = x / j;;
                    if (used[y] == -1) {
                        used[y] = ind.size();
                        ind.push_back({});
                        del.push_back(y);
                    }
                    ind[used[y]].push_back(i);
                }
            }
        }
    }
    g.assign(n, {});
    vector<ll> ans(10000007);
    vis.assign(n, 0);
    for (int i = 0; i < ind.size(); i++){
        vector<int> hist;
        for (int j = 0; j < ind[i].size(); j++){
            g[edg[ind[i][j]].first].push_back(edg[ind[i][j]].second);
            if (g[edg[ind[i][j]].first].size() == 1){
                hist.push_back(edg[ind[i][j]].first);
            }
            g[edg[ind[i][j]].second].push_back(edg[ind[i][j]].first);
            if (g[edg[ind[i][j]].second].size() == 1){
                hist.push_back(edg[ind[i][j]].second);
            }
        }
        ll res = 0;
        for (int j = 0; j < ind[i].size(); j++){
            if (vis[edg[ind[i][j]].first] < tim){
                sz = 0;
                dfs(edg[ind[i][j]].first);
                res += sz * (sz - 1);
            }
        }
        //cerr << del[i] << " " << res <<  '\n';
        ans[del[i]] = res;
        tim++;
        for (int j : hist){
            g[j].clear();
        }
    }
    //cerr << "\n\n\n";
    sort(del.begin(), del.end());
    vector<ll> tot(ind.size(), 0);
    vector<int>del2(ind.size(), 1);
    for (int i = del.size() - 1; i >= 0 ; i--){
        ll cur = ans[del[i]];
        for (int j = 2; j * del[i] <= del.back(); j++){
            if (used[j * del[i]] != -1)
                cur -= tot[used[j * del[i]]];
        }
        //cerr << del[i] << " " << cur << '\n';
        tot[used[del[i]]] = cur;
        del2[used[del[i]]] = del[i];
    }
    ll answer = 0;
    for (int i =0; i < del2.size(); i++){
        answer += 1LL * del2[i] * tot[i];
    }
    cout << answer;
}