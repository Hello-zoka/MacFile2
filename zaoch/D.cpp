#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

//#define int long long

vector<vector<int>> lst;
int ans =0;
string s, t;

string cur = "";
void dfs(int st, int pr = -1) {
    cur += t[st];
    if (cur <= s) ans++;
    for (int to : lst[st]) {
        if (to != pr) {
            dfs(to, st);
        }
    }
    cur.pop_back();
}


signed main() {
    int n, m;
    cin >> n >> m;
    cin >> s;
    cin >> t;
    lst.assign(n, {});
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        x--;
        lst[x].push_back(i);
        lst[i].push_back(x);
        par[i] = x;
    }
    for (int i = 0; i < n; i++) {
        dfs(i);
    }
    cout << ans;
}