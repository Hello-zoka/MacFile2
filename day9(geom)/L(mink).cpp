#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

#define int long long
#define INF 1000000007

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

class SegmentTree {
    int sz;
    vector<int> t;

    int get(int v, int tl, int tr, int l, int r) const {
        if (r < tl || tr < l)
            return 0;
        if (l <= tl && tr <= r)
            return t[v];
        int tm = tl + (tr - tl) / 2;
        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm + 1, tr, l, r);
    }

    void modify(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] += val;
            return;
        }
        int tm = tl + (tr - tl) / 2;
        if (pos <= tm)
            modify(2 * v + 1, tl, tm, pos, val);
        else
            modify(2 * v + 2, tm + 1, tr, pos, val);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

public:
    SegmentTree(int size) {
        sz = size;
        t.resize(4 * sz);
    }

    int size() {
        return sz;
    }

    int get(int l, int r) const {
        return get(0, 0, sz - 1, l, r);
    }

    void modify(int pos, int val) {
        modify(0, 0, sz - 1, pos, val);
    }
};


class Event {
    int type, index, x, y;
public:
    Event(int type, int index, int x, int y) : type(type), index(index), x(x), y(y) {}
    bool operator<(const Event &that) const {
        return x < that.x || x == that.x && type < that.type;
    }
    void process(SegmentTree &st, vector<int> &answers) const {
        int k = st.get(y + 1, st.size() - 1);
        if (type == 1)
            answers[index] -= st.get(y + 1, st.size() - 1);
        if (type == 2)
            st.modify(y, 1);
        if (type == 3)
            answers[index] += st.get(y + 1, st.size() - 1);
    }
};


signed main() {
    vector<Event> scanLine;
    int aSize, aMax = 0;
    int n;
    cin >> n;
    vector<pair<int, int>> e;
    vector<int> cnt;
    for (int qq = 0; qq < n; qq++) {
        // cerr << 1;
        int k;
        cin >> k;
        cnt.push_back(k);
        vector<pair<int, int>> cord;
        for (int j = 0; j < k; j++) {
            int x, y;
            cin >> x >> y;
            cord.push_back({x, y});
        }
        for (int i = 0; i < k; i++) {
            e.push_back({cord[i].first - cord[(i - 1 + k) % k].first, cord[i].second - cord[(i - 1 + k) % k].second});
            int gg = gcd(abs(e[e.size() - 1].first), abs(e[e.size() - 1].second));
            e[e.size() - 1].first /= gg;
            e[e.size() - 1].second /= gg;
        }
    }
    vector<int> lst;
    map<pair<int, int>, int> cur;
    for (int i = 0; i < e.size(); i++) {
        if (cur.count(e[i]) != 0) {
            lst.push_back(cur.find(e[i])->second);
        } else {
            lst.push_back(cur.size());
            cur.emplace(e[i], lst[i]);
        }
        // cerr << lst[i] << " ";
    }

    vector<pair<int, int>> LR;
    int ccc = 0;
    for (int i = 0; i < cnt.size(); i++) {
        LR.push_back({ccc, ccc + cnt[i]});
        ccc += cnt[i];
    }
    aSize = lst.size();
    vector<int> nxt;
    nxt.assign(310000, -1);
    vector<int> l;
    l.assign(lst.size(), 310000);
    for (int i = lst.size() - 1; i >= 0; i--) {
        if (nxt[lst[i]] != -1) {
            l[i] = nxt[lst[i]];
        }
        nxt[lst[i]] = i;
    }

    for (int i = 0; i < aSize; i++) {
        int a = l[i];
        aMax = max(aMax, a);
        scanLine.push_back(Event(2, -1, i, a));
    }

    SegmentTree st(aMax + 1);

    int q;
    cin >> q;
    vector<int> bl;
    // bl.assign(q, 0);
    for (int i = 0; i < q; i++) {
        int ll, r;
        cin >> ll >> r;
        ll = LR[ll - 1].first + 1;
        r = LR[r - 1].second;
        // cerr << ll << " " << r << " ";
        // if (ll == r) bl[i] = 1;
        scanLine.push_back(Event(1, i, ll - 1, r - 1));
        scanLine.push_back(Event(3, i, r - 1, r - 1));
    }
    vector<int> answers(q);
    sort(scanLine.begin(), scanLine.end());
    for (int i = 0; i < scanLine.size(); i++)
        scanLine[i].process(st, answers);
    for (int i = 0; i < q; i++) {
        cout << answers[i] << "\n";
    }
}