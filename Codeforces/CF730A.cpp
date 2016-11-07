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
#include <queue>
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

const int N = 100;
int n;
int r[N + 5];
struct node{
	int id;
	node(){}
	node(int _id): id(_id){}
	bool operator <(const node &tmp)const{
		return r[id] < r[tmp.id];
	}
};
priority_queue<node>que;

char ans[10005][N+5];
int tot=0;
vi tmp;
inline void add(int cnt){
	rep(i, 0, n) ans[tot][i] = '0';
	ans[tot][n] = 0;
	while(cnt--) ans[tot][tmp.back()] = '1', --r[tmp.back()], tmp.pop_back();
	tot++;
}
int main(){
	scanf("%d", &n);
	while(!que.empty()) que.pop();
	rep(i, 0, n) {
		scanf("%d", &r[i]);
		que.push(node(i));
	}
	int x=que.top().id;que.pop();
	while(r[x] != r[que.top().id]){
		int y = que.top().id;que.pop();
		if(r[x] > 0) r[x]--;
		if(r[y] > 0) r[y]--;
		rep(i, 0, n) ans[tot][i] = '0';
		ans[tot][x] = ans[tot][y] = '1';
		ans[tot++][n] = 0;
		que.push(node(y));
	}
	int mi = N;
	rep(i, 0, n) mi = min(mi, r[i]);
	for(int i = r[x]; i > mi; --i){
		tmp.clear();
		rep(j, 0, n) if(r[j] == i) tmp.pb(j);
		while(sz(tmp) >= 10) add(5);
		if(sz(tmp) <= 5) add(sz(tmp));
		else add(sz(tmp)/2), add(sz(tmp));
	}
	printf("%d\n%d\n", mi, tot);
	rep(i, 0, tot) puts(ans[i]);
	return 0;
}

/*

*/

