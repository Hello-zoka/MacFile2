#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

//#define int long long
vector<set<int>> row, col;
//map<pair<int, int>, pair<int, int>> dp;

pair<int, int> get_row(int x, int y) {
    if (x == -1){
        return {-1, -1};
    }
    auto it = row[x].lower_bound(y);
    auto it2 = row[x].upper_bound(y);

    int r, l;
    if (it2 == row[x].end()) r = -1;
    else r = *it2;
    if (it == row[x].begin()) l = -1;
    else l = *(--it);
    return {l, r};
}

pair<int, int> get_col(int x, int y) {
    int l, r;
    auto it = col[y].lower_bound(x);
    auto it2 = col[y].upper_bound(x);
    if (it2 == col[y].end()) r = -1;
    else r = *it2;
    if (it == col[y].begin()) l = -1;
    else l = *(--it);
    return {l, r};
}

int n, m, q;
vector<vector<int>> lst;

void rel() {
    vector<int> ans(m, 0);
    int res = 0;
    for (int i = 0; i < m; i++) {
        int xx = -1, yy = i;

        int cur = 0;
        while (1) {
            //cerr << xx << " " << yy  << '\n';
            pair<int, int> co = get_col(xx, yy);
            pair<int, int> ro = get_row(xx, yy);
//            cerr << co.first << " " << co.second << '\n';
//            cerr << ro.first << " " << ro.second << "\n\n";
            if (cur == 0) {
                xx = co.second;
                if (xx == -1) {
                    if (ans[yy]++ == 0) res++;
                    break;
                }
                if (lst[xx][yy] == 1) {
                    cur = 1;
                } else {
                    cur = 2;
                }
            } else if (cur == 1) {
                yy = ro.second;
                if (yy == -1) {
                    break;
                }
                if (lst[xx][yy] == 1) {
                    cur = 0;
                } else {
                    cur = 3;
                }
            } else if (cur == 2) {
                yy = ro.first;
                if (yy == -1) {
                    break;
                }
                if (lst[xx][yy] == 1) {
                    cur = 3;
                } else {
                    cur = 0;
                }
            } else {
                xx = co.first;
                if (xx == -1) {
                    break;
                }
                if (lst[xx][yy] == 1) {
                    cur = 2;
                } else {
                    cur = 1;
                }
            }
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    row.assign(n, {});
    col.assign(m, {});
//    for (int i = 0; i < m; i++) {
//        dp[0][i].first = i;
//    }
    lst.assign(n, vector<int>(m, 0));
    for (int qq = 0; qq < q; qq++) {
        int a, x, y;
        cin >> a >> x >> y;
        x--;
        y--;
        if (a == 1) {
            lst[x][y] = 1;
            row[x].insert(y);
            col[y].insert(x);
        } else if (a == 2) {
            lst[x][y] = 2;
            row[x].insert(y);
            col[y].insert(x);
        }
        else{
            lst[x][y] = 0;
            row[x].erase(y);
            col[y].erase(x);
        }
        rel();
    }

    return 0;
}

