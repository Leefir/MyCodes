#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
using namespace std;
const int N=(int)1e5;
int n,m;
vpii g[N+5];
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v;scanf("%d %d",&u,&v);
		--u;--v;
		g[v].pb(pii(u,i));
	}
}
int dp[N+5],ans[N+5];
int dfs(int u){
	int &res=dp[u];
	if(res==-1){
		res=1;ans[u]=0;
		rep(i,0,sz(g[u])){
			int v=g[u][i].fi,id=g[u][i].se;
			int tmp=dfs(v)+1;
			if(res<tmp){
				res=tmp;
				ans[u]=max(ans[v],id);
			}
		}
	}
	return res;
}
void solve(){
	rep(i,0,n)dp[i]=-1;
	rep(i,0,n)if(dfs(i)==n){
		printf("%d\n",ans[i]+1);
		return;
	}
	puts("-1");
}
int main(){
	input();
	solve();
	return 0;
}
