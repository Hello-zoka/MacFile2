#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

struct pt {
    int x, y;
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pt> lst;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        lst.push_back({x, y});
    }
    string s;
    cin >> s;

    int ind = -1;
    for (int i = 0; i < n; i++) {
        if (ind == -1 || lst[ind].x > lst[i].x || (lst[ind].x == lst[i].x && lst[i].y < lst[ind].y)) {
            ind = i;
        }
    }
    vector<int> ans, used(n, 0);
    used[ind] = 1;
    ans.push_back(ind);
    for (int i = 1; i < n; i++) {
        int cur = -1;
        for (int j = 0; j < n; j++) {
            if (used[j]) continue;
            if (cur == -1) {
                cur = j;
            } else {
                int x = (lst[j].x - lst[ind].x) * (lst[cur].y - lst[ind].y) -
                        (lst[j].y - lst[ind].y) * (lst[cur].x - lst[ind].x);
                if (s[i - 1] == 'R') x *= -1;
                if (x > 0) cur = j;
            }
        }
        used[cur] = 1;
        ind = cur;
        ans.push_back(cur);
    }
    for (int i : ans)
        cout << i + 1 << ' ';
    return 0;
}