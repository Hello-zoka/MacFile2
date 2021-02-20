#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

//#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct pt {
    int x, y;
};

#define INF 1000000009

bool ptsOnLine(const pt &a, const pt &b, const pt &c) {
    return (1LL * c.x * (b.y - a.y) - 1LL * c.y * (b.x - a.x) == 1LL * a.x * b.y - 1LL * b.x * a.y);
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int q = 0; q < t; q++) {
        int n, k;
        cin >> n >> k;
        vector<pt> lst;
        for (int i = 0; i < n; i++) {
            pt x;
            cin >> x.x >> x.y;
            lst.push_back(x);
        }
        int stt = clock();
        int ans = 0;
        while ((clock() - stt) * (long long)1000 <  (long long)n * CLOCKS_PER_SEC) {
            //cerr <<  (clock() - stt) / CLOCKS_PER_SEC  << " " << 2 * (n / (double)100000) << '\n';
            random_shuffle(lst.begin(), lst.end());
            vector<pair<pt, pt>> lines;
            pt prev = {-INF, -INF};
            int bl = 0;
            for (int i = 0; i < n; i++) {
                int cur = 0;
                for (int j = 0; j < lines.size(); j++) {
                    if (ptsOnLine(lines[j].first, lines[j].second, lst[i])) {
                        cur = 1;
                        break;
                    }
                }
                if (cur) continue;
                if (prev.x == -INF) {
                    prev = lst[i];
                } else {
                    lines.push_back({lst[i], prev});
                    prev = {-INF, -INF};
                }
                if (lines.size() > k) {
                    bl = 1;
                    break;
                }
            }
            if (bl || (lines.size() == k && prev.x != -INF)) {
                continue;
            }
            ans = 1;
            if (prev.x != -INF) {
                lines.push_back({prev, {prev.x + 1, prev.y + 1}});
            }
            cout << "Yes\n";
            cout << lines.size() << '\n';
            for (int i = 0; i < lines.size(); i++) {
                cout << lines[i].first.x << " " << lines[i].first.y << " " << lines[i].second.x << " "
                     << lines[i].second.y << '\n';
            }
            break;
        }
        if (!ans) cout << "No\n";
    }
}