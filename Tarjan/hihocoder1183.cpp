#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<pii> vpii;
#define sz(x) ((int)(x).size())
#define pb push_back
const int N=20000;
const int M=100000;
int edge[M+5];
vi g[N+5];
int n,m;
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v;scanf("%d %d",&u,&v);
		--u;--v;edge[i]=u^v;
		g[u].pb(i);g[v].pb(i);
	}
}
int dfs_clock,dfn[N+5],low[N+5];
int top,stk[M+5];
bool is_cut[N+5];
int bcc_cnt;
vi bcc[N+5];
vpii bridge;
void dfs(int u,int par){
	dfn[u]=low[u]=++dfs_clock;
	int child_cnt=0;
	
	rep(i,0,sz(g[u])){
		int eid=g[u][i],v=edge[eid]^u;
		
		if(!dfn[v]){
			stk[++top]=eid;
			child_cnt++;
			
			dfs(v,u);
			low[u]=std::min(low[u],low[v]);
			
			if(low[v]>dfn[u])bridge.pb(pii(std::min(u,v),std::max(u,v)));
			if(low[v]>=dfn[u]){
				is_cut[u]=true;
				bcc_cnt++;bcc[bcc_cnt].clear();
				while(true){
					int x=stk[top--];
					bcc[bcc_cnt].pb(x);
					if(x==eid)break;
				}
			}
		}else if(dfn[v]<dfn[u]&&v!=par){
			stk[++top]=eid;
			low[u]=std::min(low[u],dfn[v]);
		}
	}
	
	if(par==-1&&child_cnt==1)is_cut[u]=false;
}
void Tarjan(){
	dfs_clock=top=bcc_cnt=0;
	rep(i,0,n){
		dfn[i]=0;
		is_cut[i]=false;
	}
	
	rep(i,0,n)if(!dfn[i])dfs(i,-1);
}
void output(){
	int cut_cnt=0;
	rep(i,0,n)cut_cnt+=is_cut[i];
	if(cut_cnt==0)puts("Null");
	else rep(i,0,n)if(is_cut[i])printf("%d%c",i+1," \n"[--cut_cnt==0]);
	
	std::sort(bridge.begin(),bridge.end());
	rep(i,0,sz(bridge))printf("%d %d\n",bridge[i].first+1,bridge[i].second+1);
}
int main(){
	input();
	Tarjan();
	output();
	return 0;
}
