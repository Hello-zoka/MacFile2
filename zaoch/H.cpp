#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

#define int long long
#define INF 1e12
signed main() {
    int n;
    cin >> n;
    vector<int> lst;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        lst.push_back(x);
    }
    vector<pair<int, int>> l, r;
    vector<int> cur(n, 1);
    for (int i = 0; i < n; i++) {
        while (l.size() > 0 && l.back().first >= lst[i]) {
            l.pop_back();
        }
        l.push_back({lst[i], i});
        auto it = lower_bound(l.begin(), l.end(), make_pair(lst[i], (int) -1));
        if (it == l.begin()) {
            cur[i] += i;
            continue;
        }
        it--;
        cur[i] += i - (*it).second - 1;
    }
    pair<int, int> ans = {INF, INF};
    for (int i = n - 1; i >= 0; i--) {
        while (r.size() > 0 && r.back().first >= lst[i]) {
            r.pop_back();
        }
        r.push_back({lst[i], i});
        auto it = lower_bound(r.begin(), r.end(), make_pair(lst[i], (int) -1));
        if (it == r.begin()) {
            cur[i] += (n - 1 - i);
            continue;
        }
        it--;
        cur[i] += (*it).second - i - 1;
        if (cur[i] >= lst[i]) {
            ans.second = min(ans.second, cur[i]);
            ans.first = min(ans.first, lst[i]);
        } else {
            ans.second = min(ans.second, lst[i]);
            ans.first = min(ans.first, cur[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (lst[i] == 0) continue;
        if (cur[i] >= lst[i]) {
            ans.second = min(ans.second, cur[i]);
            ans.first = min(ans.first, lst[i]);
        } else {
            ans.second = min(ans.second, lst[i]);
            ans.first = min(ans.first, cur[i]);
        }
    }
    cout << ans.first * ans.second;
}