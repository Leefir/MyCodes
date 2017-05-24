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
#define x first
#define y second
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

/*
{0, 1, 2, 3, 4, 5, 6}
{0, 0, 0, 0, 0, 0, 0}

{4, 5, 6, 7, 8, 9, 10}
{0, 0, 0, 0, 0, 0, 0}

{0, 2, 4}, {0, 0, 0}}

{{0}, {0}, {1000000}, {1000000}, {1, 2, 2}, {2, 1, 2}}

*/
class ArmyTeleportation {
    public:
    vi xt, yt;
    ll dltx, dlty;
    bool chk(){
    	ll a0 = 2*xt[0]-2*xt[2], b0 = 2*xt[1]-2*xt[2];
    	ll a1 = 2*yt[0]-2*yt[2], b1 = 2*yt[1]-2*yt[2];
    	ll c0 = dltx, c1 = dlty;
    	if(a0*b1!=a1*b0){
    		return (b0*c1-b1*c0)%(a0*b1-a1*b0)==0 && (a0*c1-a1*c0)%(a0*b1-a1*b0)==0;
    	}else{
    		if(b0*c1-b1*c0!=0 || a0*c1-a1*c0!=0) return false;
    		if(__gcd(a0, b0)!=0 && c0%__gcd(a0, b0)!=0) return false;
    		if(__gcd(a1, b1)!=0 && c1%__gcd(a1, b1)!=0) return false;
    		return true;
    	}
    }
    string ifPossible(vi x1, vi y1, vi x2, vi y2, vi _xt, vi _yt) {
    	xt = _xt, yt = _yt;
    	bool res = false;
    	int n = sz(x1);
    	vpii a(n), b(n);
    	
    	rep(i, 0, n) a[i] = pii(x1[i], y1[i]), b[i] = pii(x2[i], y2[i]);
    	sort(all(a)); sort(all(b));
    	dltx = b[0].x-a[0].x, dlty = b[0].y-a[0].y; bool ok = true;
    	rep(i, 0, n) if(b[i].x-a[i].x!=dltx || b[i].y-a[i].y!=dlty) ok = false;
    	if(ok) res |= chk();
   	printf("res %d\n", res);
    	rep(i, 0, n) a[i] = pii(-x1[i], -y1[i]), b[i] = pii(x2[i], y2[i]);
    	sort(all(a)); sort(all(b));
    	dltx = b[0].x-a[0].x, dlty = b[0].y-a[0].y; ok = true;
    	rep(i, 0, n) if(b[i].x-a[i].x!=dltx || b[i].y-a[i].y!=dlty) ok = false;
    	if(ok){
    		dltx -= 2*xt[2]; dlty -= 2*yt[2];
    		res |= chk();
    	}
    	if(res) return "possible";
        return "impossible"; 
	}	 
};

// CUT begin
ifstream data("ArmyTeleportation.sample");

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

bool do_test(vector<int> x1, vector<int> y1, vector<int> x2, vector<int> y2, vector<int> xt, vector<int> yt, string __expected) {
    time_t startClock = clock();
    ArmyTeleportation *instance = new ArmyTeleportation();
    string __result = instance->ifPossible(x1, y1, x2, y2, xt, yt);
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
        vector<int> x1;
        from_stream(x1);
        vector<int> y1;
        from_stream(y1);
        vector<int> x2;
        from_stream(x2);
        vector<int> y2;
        from_stream(y2);
        vector<int> xt;
        from_stream(xt);
        vector<int> yt;
        from_stream(yt);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x1, y1, x2, y2, xt, yt, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1495405544;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ArmyTeleportation (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
