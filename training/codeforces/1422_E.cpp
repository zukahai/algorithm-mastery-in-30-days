/*
https://codeforces.com/contest/1422/problem/E
*/
#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define reunique(v) v.resize(std::unique(v.begin(), v.end()) - v.begin())
#define sz(v) ((int)(v).size())
 
#define vec1d(x) vector<x>
#define vec2d(x) vector<vec1d(x)>
#define vec3d(x) vector<vec2d(x)>
#define vec4d(x) vector<vec3d(x)>
 
#define ivec1d(x, n, v) vec1d(x)(n, v)
#define ivec2d(x, n, m, v) vec2d(x)(n, ivec1d(x, m, v))
#define ivec3d(x, n, m, k, v) vec3d(x)(n, ivec2d(x, m, k, v))
#define ivec4d(x, n, m, k, l, v) vec4d(x)(n, ivec3d(x, m, k, l, v))
 
#ifdef LOCAL
#include "pretty_print.h"
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif
 
#define nl "\n"
 
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
 
template <typename T> T sqr(T x) { return x * x; }
template <typename T> T abs(T x) { return x < 0? -x : x; }
template <typename T> T gcd(T a, T b) { return b? gcd(b, a % b) : a; }
template <typename T> bool chmin(T &x, const T& y) { if (x > y) { x = y; return true; } return false; }
template <typename T> bool chmax(T &x, const T& y) { if (x < y) { x = y; return true; } return false; }
 
auto random_address = [] { char *p = new char; delete p; return (uint64_t) p; };
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
mt19937_64 rngll(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
 
 
int main(int /* argc */, char** /* argv */)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifdef LOCAL
    assert(freopen("i.txt", "r", stdin));
    assert(freopen("o.txt", "w", stdout));
#endif
 
    string s;
    while (cin >> s) {
        int n = s.size();
        vector<int> a(n + 2, 0);
        for (int i = 0; i < n; ++i) {
            a[i] = s[i] - 'a' + 1;
        }
 
        int m = 1;
        while ((1 << m) <= n) {
            m += 1;
        }
 
        const int P = 29;
        vector<ull> p(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p[i] = p[i - 1] * P;
        }
 
        auto hsh = ivec2d(ull, n + 1, m, 0);
        auto nxt = ivec2d(int, n + 1, m, n);
        auto len = ivec1d(int, n + 1, 0);
        auto jmp = ivec1d(int, n + 1, 0);
        iota(all(jmp), 0);
 
        auto cmp = [&](int x, int y) {
            x = jmp[x];
            y = jmp[y];
            for (int i = m - 1; i >= 0; --i) {
                if (hsh[x][i] == hsh[y][i]) {
                    x = nxt[x][i];
                    y = nxt[y][i];
                }
            }
            return a[x] < a[y];
        };
 
        auto upd = [&](int x, int v) {
            v = jmp[v];
            len[x] = len[v] + 1;
            hsh[x][0] = a[x];
            nxt[x][0] = v;
            for (int i = 1; i < m; ++i) {
                int y = nxt[x][i - 1];
                nxt[x][i] = nxt[y][i - 1];
                hsh[x][i] = hsh[x][i - 1] * p[1 << (i - 1)] + hsh[y][i - 1];
            }
        };
 
        for (int i = n - 1; i >= 0; --i) {
            upd(i, i + 1);
            if (i + 1 < n && a[i] == a[i + 1] && cmp(i + 2, i)) {
                jmp[i] = jmp[jmp[i + 2]];
                len[i] = len[jmp[i]];
            }
        }
 
        for (int i = 0; i < n; ++i) {
            cout << len[i] << " ";
            int x = jmp[i];
            for (int j = 0, limit = len[i] <= 10? len[i] : 5; j < limit; ++j, x = nxt[x][0]) {
                cout << s[x];
            }
            if (len[i] > 10) {
                int d = len[i] - 5 - 2;
                for (int i = m - 1; i >= 0; --i) {
                    if ((1 << i) <= d) {
                        d -= 1 << i;
                        x = nxt[x][i];
                    }
                }
                cout << "...";
                for (int j = 0; j < 2; ++j, x = nxt[x][0]) {
                    cout << s[x];
                }
            }
            cout << nl;
        }
    }
 
#ifdef LOCAL
    cerr << "Time execute: " << clock() / (double)CLOCKS_PER_SEC << " sec" << endl;
#endif
    return 0;
}