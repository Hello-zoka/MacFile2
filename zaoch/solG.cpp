#ifndef ONPC
  #define _FORTIFY_SOURCE 0
  #pragma GCC optimize("Ofast")
  #pragma GCC optimize("no-stack-protector")
  #pragma GCC optimize("unroll-loops")
  #pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx")
  #pragma GCC optimize("fast-math")
#endif

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <set>

#define mp make_pair
#define eb emplace_back
#define x first
#define y second

template <typename T>
bool chmax(T &a, const T &b) {
    if (a < b) {
      a = b;
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T &a, const T &b) {
    if (a > b) {
      a = b;
      return true;
    }
    return false;
}

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pt;

#ifdef ONPC
mt19937 rnd(228);
#else
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#endif

const ll MOD = 1000000007LL;
const ll MOD2 = 998244353LL;
const ld PI = acos(-1);

#ifdef ONPC
const int MAXN = 100;
#else
const int MAXN = 2e5 + 54;
#endif
//#define int long long
const int INF = 1e9;

int n, m, q;
set<pt> an[MAXN], bm[MAXN]; // an by x; bm by y

void read(){
  cin >> n >> m >> q;
}

int used[MAXN];
bool go(int x, int y, char dir){
  if (x < 0 || x >= n) {
    if (x >= n) return true;
    return false;
  }
  if (y < 0 || y >= m) return false;

  if (dir == 'U'){
    auto it = bm[y].upper_bound({x, 3});
    if (it == bm[y].begin()) return false;
    it--;
    int x1 = it->x;
    int t = it->y;
    if (t == 1) return go(x1, y - 1, 'L');
    else return go(x1, y + 1, 'R');
  }

  if (dir == 'D'){
    auto it = bm[y].lower_bound({x, -1});
    if (it == bm[y].end()) return true;
    int x1 = it->x;
    int t = it->y;
    if (t == 1) return go(x1, y + 1, 'R');
    else return go(x1, y - 1, 'L');
  }

  if (dir == 'L'){
    auto it = an[x].upper_bound({y, 3});
    if (it == an[x].begin()) return false;
    it--;
    int y1 = it->x;
    int t = it->y;
    if (t == 1) return go(x - 1, y1, 'U');
    else return go(x + 1, y1, 'D');
  }

  if (dir == 'R'){
    auto it = an[x].lower_bound({y, -1});
    if (it == an[x].end()) return false;
    int y1 = it->x;
    int t = it->y;
    if (t == 1) return go(x + 1, y1, 'D');
    else return go(x - 1, y1, 'U');
  }

  return false;
}

void solve(){
  read();

  for (int qq = 0; qq < q; qq++){
    int t, x, y;
    cin >> t >> x >> y;
    x--, y--;
    if (t == 0){
      an[x].erase(an[x].lower_bound(mp(y, -1)));
      bm[y].erase(bm[y].lower_bound(mp(x, -1)));
    } else {
      an[x].insert({y, t});
      bm[y].insert({x, t});
    }
    int cnt = 0;
    //memset(used, 0, sizeof used);
    for (int i = 0; i < m; i++){
      if (go(0, i, 'D')) { cnt++; }
    }
    //cnt = 0;
    //for (int i = 0; i < n; i++){
    //  if (used[i]) cnt++;
    //}
    cout << cnt << '\n';
  }
}

/*
#ifndef ONPC
#define FILEIO
#endif
*/
signed main()
{
    #ifdef FILEIO
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
