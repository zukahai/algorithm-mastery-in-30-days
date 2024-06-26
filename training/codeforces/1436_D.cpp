/*
https://codeforces.com/contest/1436/problem/D
*/
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
 
#include <bits/stdc++.h>
using namespace std;
 
bool dbg = 0;
  
clock_t start_time = clock();
#define current_time fixed<<setprecision(6)<<(ld)(clock()-start_time)/CLOCKS_PER_SEC
  
#define f first
#define s second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
#define sqr(x) ((x) * (x))
 
#define ull unsigned long long
#define ll long long
#define ld long double
#define pii pair<int,int>
#define umap unordered_map<int, int>
 
#define files1 freopen("input.txt","r",stdin)
#define files2 freopen("output.txt","w",stdout)
#define files files1;files2
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0)
 
// #define endl '\n'
#define ln(i,n) " \n"[(i) == (n) - 1]
 
void bad(string mes = "NO"){cout << mes;exit(0);}
void bad(int mes){cout << mes;exit(0);}
 
template<typename T>
string bin(T x, int st = 2){
    string ans = "";
    while (x > 0){
        ans += char('0' + x % st);
        x /= st;
    }
    reverse(ans.begin(), ans.end());
    return ans.empty() ? "0" : ans;
}
 
mt19937_64 mt_rand(
    228// chrono::system_clock::now().time_since_epoch().count()
);
 
template<typename T1, typename T2> inline bool upmax(T1& a, T2 b) { return (a < b ? (a = b, true) : false); }
template<typename T1, typename T2> inline bool upmin(T1& a, T2 b) { return (b < a ? (a = b, true) : false); }
 
// inline int popcount(int x){
//     int count = 0;
//     __asm__ volatile("POPCNT %1, %0;":"=r"(count):"r"(x):);
//     return count;
// }
  
template<typename T>
T input(){
    T ans = 0, m = 1;
    char c = ' ';
  
    while (!((c >= '0' && c <= '9') || c == '-')) {
        c = getchar();
    }
  
    if (c == '-')
        m = -1, c = getchar();
    while (c >= '0' && c <= '9'){
        ans = ans * 10 + (c - '0'), c = getchar();
    }
    return ans * m;
}
 
template<typename T>
T gcd (T a, T b) { while (b) { a %= b; swap (a, b); } return a; }
  
template<typename T> void read(T& a) { a = input<T>(); }
template<typename T> void read(T& a, T& b) { read(a), read(b); }
template<typename T> void read(T& a, T& b, T& c) { read(a, b), read(c); }
template<typename T> void read(T& a, T& b, T& c, T& d) { read(a, b), read(c, d); }
 
const int inf = 1e9 + 20;
const short short_inf = 3e4 + 20;
const long double eps = 1e-12;
const int maxn = (int)2e5 + 3, base = 1e9 + 7;
const ll llinf = 2e18 + 5;
const int mod = 998244353;
 
int binpow (int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1)
            res = 1ll * res * a % base;
        a = 1ll * a * a % base;
        n >>= 1;
    }
    return res;
}
 
int a[maxn];
int p[maxn];
 
vector<int> g[maxn];
 
map<ll, int> *cnt[maxn];
 
void add(int v, ll val) {
  ll prev = 0;
  int cc  = 0;
 
  while (cnt[v]->size()) {
    auto [h, c1] = *cnt[v]->begin();
    ll allup = 1ll * cc * (h - prev);
    if (val >= allup) {
      val -= allup;
      prev = h;
      cc += c1;
      cnt[v]->erase(cnt[v]->begin());
    } else {
      break;
    }
  }
 
  if (cc == 0) {
      (*cnt[v])[val]++;
  } else {
    ll x = prev + (val / cc);
    if (val % cc > 0) {
      (*cnt[v])[x + 1] += val % cc;
    }
    (*cnt[v])[x] += cc - val % cc;
  }
}
 
int sz[maxn];
 
void dfs(int v){
    int mx = -1, bigChild = -1;
    sz[v] = 1;
    for(auto u : g[v]) {
       dfs(u);
       sz[v] += sz[u];
       if(sz[u] > mx) {
           mx = sz[u], bigChild = u;
       }
    }
    if(bigChild != -1)
        cnt[v] = cnt[bigChild];
    else
        cnt[v] = new map<ll, int> ();
    for(auto u : g[v])
       if(u != bigChild){
           for(auto x : *cnt[u])
               (*cnt[v])[x.first] += x.second;
       }
   add(v, a[v]);
}
 
 
int main() {
//   files1;
  fast_io;
 
  int n;
  cin >> n;
 
  for (int i = 1; i < n; i++) {
    int par;
    cin >> par;
    par--;
 
    g[par].push_back(i);
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
 
  dfs(0);
 
  ll ans = 0;
  for (auto [k, v] : *cnt[0]) {
    // if (v > 0) {
      ans = max(ans, k);
    // }
  }
  cout << ans << "\n";
  return 0;
}