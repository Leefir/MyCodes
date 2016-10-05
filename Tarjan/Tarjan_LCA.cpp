#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=40000;
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
typedef std::pair<int,int>pii;
typedef std::vector<pii> vpii;
vpii to[N+5],query[N+5];
int n,m;
int ans[N+5];
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)to[i].clear();
	rep(i,0,n-1){
		int u,v,val;
		scanf("%d %d %d",&u,&v,&val);
		--u;--v;
		to[u].pb(pii(v,val));
		to[v].pb(pii(u,val));
	}
	rep(i,0,n)query[i].clear();
	rep(i,0,m){
		int u,v;
		scanf("%d %d",&u,&v);
		--u;--v;
		query[u].pb(pii(v,i));
		query[v].pb(pii(u,i));
	}
}
int dfs_clock,dfn[N+5];
int fa[N+5],dep[N+5];
int get(int u){
	int rt=u;
	while(fa[rt]!=rt)rt=fa[rt];
	while(u!=rt){
		int t=fa[u];
		fa[u]=rt;
		u=t;
	}
	return rt;
}
void dfs(int u,int par){
	dfn[u]=++dfs_clock;
	fa[u]=u;
	rep(i,0,sz(query[u])){
		int v=query[u][i].fi,id=query[u][i].se;
		if(dfn[v]!=-1)ans[id]=dep[u]+dep[v]-dep[get(v)]*2;
	}
	rep(i,0,sz(to[u])){
		int v=to[u][i].fi;
		if(v==par)continue;
		dep[v]=dep[u]+to[u][i].se;
		dfs(v,u);
		fa[v]=u;
	}
}
void solve(){
	rep(i,0,n)dfn[i]=-1;
	dfs_clock=0;
	dep[0]=0;dfs(0,-1);
}
void output(){
	rep(i,0,m)printf("%d\n",ans[i]);
}
void Main(){
	input();
	solve();
	output();
}
int main(){
	int cas;scanf("%d",&cas);
	while(cas--)Main();
	return 0;
}
