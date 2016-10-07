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

const int N = 500;
const int L = 100000;

char str[L + 5];
int n, m, x, y;

void input(){
	scanf("%d %d %d %d", &n, &m, &x, &y);
	scanf("%s", str);
}

int tot;

bool mark[N + 5][N + 5];

void go(int dx, int dy){
	int tx = x + dx, ty = y + dy;
	if(tx <= 0 || tx > n){
		printf("0 ");
		return;
	}
	if(ty <= 0 || ty > m){
		printf("0 ");
		return;
	}
	if(mark[tx][ty] == false){
		printf("1 ");
		mark[tx][ty] = true;
		++tot;
	}else printf("0 ");
	
	x = tx; y = ty;
}

void solve(){
	tot = 0;
	memset(mark, 0, sizeof mark);
	printf("1 "); ++tot; mark[x][y] = true;
	rep(i, 0, strlen(str) - 1){
		char c = str[i];
		if(c == 'U') go(-1, 0);
		if(c == 'D') go(1, 0);
		if(c == 'L') go(0, -1);
		if(c == 'R') go(0, 1);
	}
	printf("%d\n", n * m - tot);
}

int main(){
	input();
	solve();
	return 0;
}

/*
or stay idle if moving in the given direction is impossible

*/
