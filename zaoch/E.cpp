#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//#define int long long
const int maxk = 5000;

struct e {
    int to, from, typ;
};
int cur = 0;

int get(int x){
    return (cur >> x) & 1;
}
void set(int ps, int x){
    if (x == 0){
        cur |= (1 << ps);
        cur ^= (1 << ps);
    }
    else{
        cur |= (1 << ps);
    }
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(n, vector<int>(maxk, 0));
    vector<e> lst;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int to, from;
        if (s[0] == 'a') {
            cin >> to >> from;
            lst.push_back({to, from, 0});
        } else if (s[0] == 'o') {
            cin >> to >> from;
            lst.push_back({to, from, 1});
        } else if (s[0] == 'x') {
            cin >> to >> from;
            lst.push_back({to, from, 2});
        } else if (s[0] == 'm') {
            cin >> to >> from;
            lst.push_back({to, from, 3});
        } else if (s[0] == 's') {
            int to, x;
            cin >> to >> x;
            lst.push_back({to, x, 4});
        } else if (s[0] == 'n') {
            int to;
            cin >> to;
            lst.push_back({to, -1, 5});
        } else if (s[0] == 'j') {
            int reg, lin;
            cin >> reg >> lin;
            lst.push_back({reg, lin, 6});
        } else {
            lst.push_back({-1, -1, -1});
        }
    }
    for (int st = 0; st < (1 << k); st++){
        cur = st;
        int bl = 1;
        int pos = 1;
        vector<pair<int, int>> nw;
        while (1){
            if (pos == n) break;
            if (dp[pos][cur] == 2){
                break;
            }
            if (dp[pos][cur] == 1){
                bl = 0;
                break;
            }
            nw.push_back({pos, cur});
            dp[pos][cur] = 1;
            if (lst[pos].typ == 0){
                int to = get(lst[pos].to);
                int from = get(lst[pos].from);
                set(lst[pos].to, to & from);
            }
            if (lst[pos].typ == 1){
                int to = get(lst[pos].to);
                int from = get(lst[pos].from);
                set(lst[pos].to, to | from);
            }
            if (lst[pos].typ == 2){
                int to = get(lst[pos].to);
                int from = get(lst[pos].from);
                set(lst[pos].to, to ^ from);
            }
            if (lst[pos].typ == 3){
                int to = get(lst[pos].to);
                int from = get(lst[pos].from);
                set(lst[pos].to, from);
            }
            if (lst[pos].typ == 4){
                set(lst[pos].to, lst[pos].from);
            }

            if (lst[pos].typ == 5){
                int to = get(lst[pos].to);
                set(lst[pos].to, !to);
            }
            if (lst[pos].typ == 6){
                int to = get(lst[pos].to);
                if (to){
                    pos = lst[pos].from;
                    continue;
                }
            }
            pos++;
        }
        if (!bl){
            cout << "No\n";
            vector<int> ans(k, 0);
            int x = (1 << (k -1));
            int res = st;
            int ind = k -1 ;
            while (ind != -1){
                if (res >= x){
                    res -= x;
                    ans[ind] = 1;
                }
                ind--;
                x /= 2;
            }
            for (int i : ans) cout << i;
            return 0;
        }
        for (int i = 0; i < nw.size(); i++){
            dp[nw[i].first][nw[i].second] = 2;
        }
    }
    cout << "Yes\n";
    return 0;
}