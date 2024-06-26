/*
https://codeforces.com/contest/1427/problem/B
*/
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define SZ(x) ((int)((x).size()))
 
template <typename T1, typename T2>
string print_iterable(T1 begin_iter, T2 end_iter, int counter) {
    bool done_something = false;
    stringstream res;
    res << "[";
    for (; begin_iter != end_iter and counter; ++begin_iter) {
        done_something = true;
        counter--;
        res << *begin_iter << ", ";
    }
    string str = res.str();
    if (done_something) {
        str.pop_back();
        str.pop_back();
    }
    str += "]";
    return str;
}
 
vector<int> SortIndex(int size, std::function<bool(int, int)> compare) {
    vector<int> ord(size);
    for (int i = 0; i < size; i++) ord[i] = i;
    sort(ord.begin(), ord.end(), compare);
    return ord;
}
 
template <typename T>
bool MinPlace(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
 
template <typename T>
bool MaxPlace(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
 
template <typename S, typename T>
ostream& operator <<(ostream& out, const pair<S, T>& p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& v) {
    out << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        out << v[i];
        if (i != (int)v.size()-1) out << ", ";
    }
    out << "]";
    return out;
}
 
template<class TH>
void _dbg(const char* name, TH val){
    clog << name << ": " << val << endl;
}
template<class TH, class... TA>
void _dbg(const char* names, TH curr_val, TA... vals) {
    while(*names != ',') clog << *names++;
    clog << ": " << curr_val << ", ";
    _dbg(names+1, vals...);
}
 
#if DEBUG && !ONLINE_JUDGE
    ifstream input_from_file("input.txt");
    #define cin input_from_file
 
    #define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
    #define dbg_arr(x, len) clog << #x << ": " << print_iterable(x, x+len, -1) << endl;
#else
    #define dbg(...)
    #define dbg_arr(x, len)
#endif
 
///////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT TOUCH BEFORE THIS LINE ////////////////////////
///////////////////////////////////////////////////////////////////////////
 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); // Remove in problems with online queries!
 
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;
        int winning_streaks_cnt = 0;
        int wins = 0;
        int losses = 0;
        vector<int> losing_streaks; 
        for (int i = 0; i < N; i++) {
            if (S[i] == 'W') {
                wins++;
                if (i == 0 or S[i-1] == 'L') winning_streaks_cnt++;
            }
            if (S[i] == 'L') {
                losses++;
                if (i == 0 or S[i-1] == 'W') losing_streaks.push_back(0);
                losing_streaks.back()++;
            }
        }
        if (K >= losses) {
            cout << 2*N-1 << "\n";
            continue;
        }
        if (wins == 0) {
            if (K == 0) cout << 0 << "\n";
            else cout << 2*K-1 << "\n";
            continue;
        }
        if (S[0] == 'L') losing_streaks[0] = 1e8;
        if (S[N-1] == 'L') losing_streaks.back() = 1e8;
        sort(losing_streaks.begin(), losing_streaks.end());
        wins += K;
        for (int ls: losing_streaks) {
            if (ls > K) break;
            K -= ls;
            winning_streaks_cnt--;
        }
        cout << 2*wins - winning_streaks_cnt << "\n";
    }
}