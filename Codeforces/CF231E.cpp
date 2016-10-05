#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
typedef std::vector<int> vi;
typedef std::pair<int,int> pii;
typedef std::vector<pii> vpii;
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
const int N=(int)1e5;
const int mod=(int)1e9+7;
//connected undirected graph
int n,m,k;
pii edge[N+5];
vi g[N+5];
vpii query[N+5];
void input(){
	scanf("%d %d",&n,&m);
	
	//read edges
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v;scanf("%d %d",&u,&v);--u;--v;
		edge[i]=pii(u,v);
		g[u].pb(i);g[v].pb(i);
	}
	
	//read queries
	rep(i,0,n)query[i].clear();
	scanf("%d",&k);
	rep(i,0,k){
		int u,v;scanf("%d %d",&u,&v);--u;--v;
		query[u].pb(pii(v,i));
		query[v].pb(pii(u,i));
	}
}
int ans[N+5];
int dfs_clock,dfn[N+5],low[N+5];
int top,stk[N+5];
int bcc_cnt;
vi bcc[N+5];//[ 0 , bcc_cnt )
bool is_cut[N+5];

int belong[N+5];
void travel(int u,int par){
	dfn[u]=low[u]=++dfs_clock;
	
	
	rep(i,0,sz(g[u])){
		int eid=g[u][i],v=edge[eid].fi^edge[eid].se^u;
		
		if(!dfn[v]){
			stk[++top]=eid;
			travel(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u]){
//				is_cut[u]=true;
				
				if(stk[top]==eid)top--;
				else{
					bcc[bcc_cnt].clear();
					while(true){
						int x=stk[top--];
						int u=edge[x].fi,v=edge[x].se;
						if(belong[u]==-1)bcc[bcc_cnt].pb(u),belong[u]=bcc_cnt;
						if(belong[v]==-1)bcc[bcc_cnt].pb(v),belong[v]=bcc_cnt;
						if(x==eid)break;
					}
					bcc_cnt++;
				}
			}
		}else if(dfn[v]<dfn[u]&&v!=par){
			stk[++top]=eid;
			low[u]=std::min(low[u],dfn[v]);
		}
	}
}
void Tarjan(){
	//init
	dfs_clock=top=bcc_cnt=0;
	rep(i,0,n){
		dfn[i]=0;
		belong[i]=-1;
		is_cut[i]=false;
	}
	
	//connected graph
	travel(0,-1);
	rep(i,0,n)if(belong[i]==-1){
		belong[i]=bcc_cnt;
		bcc[bcc_cnt++].resize(1,i);
	}
//	rep(i,0,n)printf("belong[%d] %d\n",i+1,belong[i]);
}
int val[N+5],dis[N+5];
bool vis[N+5];
int fa[N+5];
int get(int u){
	if(fa[u]!=u)fa[u]=get(fa[u]);
	return fa[u];
}
void dfs(int id,int par){
	vis[id]=true;
	dis[id]=val[id];
	if(par!=-1)dis[id]+=dis[par];
	fa[id]=id;
	
	//deal with queries
	rep(i,0,sz(bcc[id])){
		int u=bcc[id][i];
		rep(j,0,sz(query[u])){
			int v=query[u][j].fi,qid=query[u][j].se;
			if(vis[belong[v]]){
				int lca=get(belong[v]);
				ans[qid]=dis[id]+dis[belong[v]]-dis[lca]*2+val[lca];
			}
		}
	}
	
	//go ahead
	rep(i,0,sz(bcc[id])){
		int u=bcc[id][i];
		rep(j,0,sz(g[u])){
			int eid=g[u][j],v=edge[eid].fi^edge[eid].se^u;
			if(!vis[belong[v]]){
				dfs(belong[v],id);
				fa[belong[v]]=id;
			}
		}
	}
}
void DP(){
	rep(i,0,bcc_cnt){
		val[i]=sz(bcc[i])>1;
		vis[i]=false;		
	}
	dfs(0,-1);
}
#define pow dsonfosadinflasdhglsd
int pow[N+5];
void output(){
	pow[0]=1;
	rep(i,1,n+1)pow[i]=pow[i-1]*2%mod;
	rep(i,0,k)printf("%d\n",pow[ans[i]]);
}
int main(){
	input();
	Tarjan();
	DP();
	output();
	return 0;
}
