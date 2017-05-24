#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) ((int)(x).size())
#define two(x) (1<<(x))
#define twol(x) (1ll<<(x))
#define debug(x) cout<<#x<<" = "<<x<<endl;
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<pii> vpii;
const int inf=0x20202020;
const ll mod=1000000007;
const db eps=1e-9;
const db pi=acos(-1);
ll powmod(ll a,ll b){ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
inline void addmod(int &x, int y){ if((x+=y)>=mod) x-=mod;}
inline void mnsmod(int &x, int y){ if((x-=y)<0) x+=mod;}
class AquaparkPuzzle {
    public:
    static const int N = 11;
    int n, m, k; vi c;
    bool ok[1<<N|5];
    int bincnt[1<<N|5];
    int dp[1<<N][N+1];
    int C[N+5];
    int solve(int S){
    	vi seq(0); rep(i, 0, n) if(S>>i&1) seq.pb(i);
    	int w = sz(seq);
    	rep(i, 0, 1<<w) rep(j, 0, w+1) dp[i][j] = 0;
    	dp[0][0] = 1;
    	rep(i, 0, 1<<n) if(ok[i] && (i&S)){
    		int to = 0;
    		rep(j, 0, w) if(i>>seq[j]&1) to |= 1<<j;
    		++dp[to][1];
    	}
    	rep(t, 2, w+1) rep(i, 1, 1<<w){
    		for(int j = (i-1)&i; j; j = (j-1)&i){
    			addmod(dp[i][t], dp[j][t-1]*(ll)dp[i^j][1]%mod);
    		}
    	}
    	int res = 0;
    	int cnt = 0; rep(i, 0, 1<<n) if(ok[i] && (i&S)==0) ++cnt;
    	rep(t, 0, min(k, w)+1){
    		int sum = 0;
    		rep(i, 0, 1<<w) addmod(sum, dp[i][t]);
    		sum = sum*(ll)C[t]%mod*powmod(cnt, k-t)%mod;
    		addmod(res, sum);
    	}
    	return res;
    }
    int brute(int S){
    	if(k != 3) return -1;
    	int res = 0;
    	rep(i, 0, 1<<n) if(ok[i])
    	rep(j, 0, 1<<n) if(ok[j])
    	rep(k, 0, 1<<n) if(ok[k]){
    		bool yes = true;
    		rep(t, 0, n) if(S>>t&1){
    			if((i>>t&1)+(j>>t&1)+(k>>t&1) > 1) yes = false;
    		}
    		res += yes;
    	}
    	return res;
    }
    int countSchedules(int _k, int _m, vector<int> _c) {
    	n = sz(_c); m = _m; k = _k; c = _c;
    	bincnt[0] = 0; rep(i, 1, 1<<N) bincnt[i] = bincnt[i>>1] + (i&1);
    	C[0] = 1; rep(i, 1, n+1) C[i] = C[i-1]*(ll)(k-i+1)%mod*powmod(i, mod-2)%mod;//C[i] = C(k, i)
    	rep(i, 0, 1<<n){
    		int s = 0; rep(j, 0, n) if(i>>j&1) s += c[j];
    		ok[i] = s<=m;
//    		printf("ok[%d] %d\n", i, ok[i]);
    	}
    	int res = 0;
    	rep(i, 0, 1<<n){
//    		printf("i %d solve(i) %d brute(i) %d\n", i, solve(i), brute(i));
    		if(bincnt[i]&1) mnsmod(res, solve(i));
    		else addmod(res, solve(i));
    	}
        return res;
    }
};

// CUT begin
ifstream data("AquaparkPuzzle.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int k, int m, vector<int> c, int __expected) {
    time_t startClock = clock();
    AquaparkPuzzle *instance = new AquaparkPuzzle();
    int __result = instance->countSchedules(k, m, c);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int k;
        from_stream(k);
        int m;
        from_stream(m);
        vector<int> c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, m, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1495493884;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "AquaparkPuzzle (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
