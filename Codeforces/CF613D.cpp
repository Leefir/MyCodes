#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
typedef std::vector<int> vi;
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
const int N=(int)1e5;
inline void rd(int &res){
	char c;res=0;
	while(c=getchar(),c<'0'||c>'9');
	do res=(res<<1)+(res<<3)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
}
int n;
vi g[N+5];
void input(){
	scanf("%d",&n);
	
	rep(i,0,n)g[i].clear();
	rep(i,0,n-1){
		int u,v;
		rd(u);rd(v);
		--u;--v;
		
		g[u].push_back(v);
		g[v].push_back(u);
	}
}
const int S=17;
int fa[S][N+5],dep[N+5];
int dfs_clock,dfn[N+5],dnn[N+5];
void dfs(int u){
	dfn[u]=++dfs_clock;
	
	rep(i,0,sz(g[u])){
		int v=g[u][i];
		if(v==fa[0][u])continue;
		
		fa[0][v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
	
	dnn[u]=dfs_clock;
}
void prepare_lca(){
	rep(i,1,S)rep(j,0,n){
		if(fa[i-1][j]==-1)fa[i][j]=-1;
		else fa[i][j]=fa[i-1][fa[i-1][j]];
	}
}
inline int LCA(int u,int v){
	if(dep[u]<dep[v])std::swap(u,v);
	int step=dep[u]-dep[v];
	per(i,0,S)if(step>>i&1)u=fa[i][u];
	
	if(u^v){
		per(i,0,S)if(fa[i][u]!=fa[i][v]){
			u=fa[i][u];
			v=fa[i][v];
		}
		u=fa[0][u];
	}
	return u;
}
vi in,vec;
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
vi gg[N+5];
bool key[N+5];
int stk[N+5];

const int inf=(int)1e9;
int dp[N+5][2];
void doit(int u){
//	printf("doit %d\n",u+1);
	dp[u][0]=dp[u][1]=0;
	
	int tmp0=0;
	
	rep(i,0,sz(gg[u])){
		int v=gg[u][i];
		
//		printf("go %d -> %d\n",u+1,v+1);
		
		doit(v);
		int tmp[2]={inf,inf};
		if(dep[v]-dep[u]>1)dp[v][0]=std::min(dp[v][0],dp[v][1]+1);
		tmp0+=std::min(dp[v][0],dp[v][1]);
		rep(a,0,2)rep(b,0,2)if(a+b<=1)tmp[a+b]=std::min(tmp[a+b],dp[u][a]+dp[v][b]);
		rep(a,0,2)dp[u][a]=tmp[a];
	}
	if(key[u])dp[u][1]=dp[u][0],dp[u][0]=inf;
	else dp[u][0]=std::min(dp[u][0],tmp0+1);
}
void response(){
	int m;rd(m);
	in.resize(m);
	vec.clear();
	rep(i,0,m){
		rd(in[i]);--in[i];
		vec.pb(in[i]);
	}
	
	std::sort(all(vec),cmp);
	rep(i,0,m-1)vec.pb(LCA(vec[i],vec[i+1]));
	std::sort(all(vec),cmp);
	vec.resize(std::unique(all(vec))-vec.begin());
	
	rep(i,0,sz(vec)){
		int u=vec[i];
		gg[u].clear();
		key[u]=false;
	}
	rep(i,0,sz(in)){
		int u=in[i];
		key[u]=true;
	}
	
	int top=0;
	rep(i,0,sz(vec)){
		int u=vec[i];
		while(top){
			if(dfn[stk[top]]<=dfn[u]&&dfn[u]<=dnn[stk[top]])break;
			--top;
		}
		if(top)gg[stk[top]].pb(u);
		stk[++top]=u;
	}
	
	int rt=vec[0];
	doit(rt);
	int ans=std::min(dp[rt][0],dp[rt][1]);
	if(ans<=n)printf("%d\n",ans);
	else puts("-1");
}
int main(){
	input();
	
	fa[0][0]=-1;dep[0]=0;
	dfs_clock=0;dfs(0);
	
	prepare_lca();
	
	int q;scanf("%d",&q);
	while(q--)response();
	return 0;
}
