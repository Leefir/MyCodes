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

const int N = 100000;

int n;
int a[N + 5];
int pos[N + 5];
void input(){
	scanf("%d", &n);
	rep(i, 0, n){
		scanf("%d", &a[i]);
		--a[i];
		pos[a[i]] = i;
	}
}

int dp[N + 5];//dp[val]
void solve(){
	rep(i, 0, n) dp[i] = inf;
	
	int ans = 0;
	rep(i, 0, n){
		dp[a[i]] = 1;
		if(a[i] - 1 >= 0 && dp[a[i] - 1] !=inf) dp[a[i]] = dp[a[i] - 1] + 1;
		ans = max(ans, dp[a[i]]);
	}
	printf("%d\n", n - ans);
}

int main(){
	input();
	solve();
	return 0;
}

/*
the numbers of all the cars are distinct

*/
