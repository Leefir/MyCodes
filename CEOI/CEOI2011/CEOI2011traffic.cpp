#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb push_back
#define sz(x) ((int)(x).size())
const int N=(int)3e5;
const int M=(int)9e5;
const int inf=(int)1e9;
inline void read_non_neg(int &res){
	char c;res=0;
	while(c=getchar(),!isdigit(c));
	do{
		res=(res<<1)+(res<<3)+(c^48);
	}while(c=getchar(),isdigit(c));
}
struct Graph{
	int G[M*2+5],nxt[M*2+5];
	int Gsz,head[N+5];
	void init_Graph(const int n){
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	inline void add_edge(int u,int v){
		G[Gsz]=v;nxt[Gsz]=head[u];head[u]=Gsz++;
	}
}g,rg;
int n,m,A,B;
int x[N+5],y[N+5];
int east[N+5],west[N+5];
bool cmp(int a,int b){
	return y[a]>y[b];
	//decreasing y-coordinates
}
void input(){
	scanf("%d %d %d %d",&n,&m,&A,&B);
	int &e=east[0],&w=west[0];
	e=w=0;
	rep(i,0,n){
		read_non_neg(x[i]);
		read_non_neg(y[i]);
		if(x[i]==0)east[++e]=i;
		else if(x[i]==A)west[++w]=i;
	}
	sort(east+1,east+e+1,cmp);
	sort(west+1,west+w+1,cmp);
	g.init_Graph(n);
	rg.init_Graph(n);
	rep(i,0,m){
		int u,v,f;
		read_non_neg(u);--u;
		read_non_neg(v);--v;
		read_non_neg(f);
		if(f==1){
			//unidirectional edge
			g.add_edge(u,v);
			rg.add_edge(v,u);
		}else{
			//undirectional edge
			g.add_edge(u,v);
			g.add_edge(v,u);
			rg.add_edge(u,v);
			rg.add_edge(v,u);
		}
	}
}
bool vis[N+5];
int que[N+5];
void bfs(){
	rep(i,0,n)vis[i]=false;
	int L=0,H=0;
	rep(i,1,east[0]+1){
		int u=east[i];
		que[H++]=u;
		vis[u]=true;
	}
	while(L<H){
		int u=que[L++];
		for(int i=g.head[u];~i;i=g.nxt[i]){
			int v=g.G[i];
			if(!vis[v]){
				vis[v]=true;
				que[H++]=v;
			}
		}
	}
}
int belong[N+5];
int L[N+5],R[N+5];
vector<int>scc[N+5];
int scc_cnt;
int S[N+5],tot;
bool mark[N+5];
void dfs1(int u){
	if(mark[u])return;
	mark[u]=true;
	for(int i=g.head[u];~i;i=g.nxt[i]){
		int v=g.G[i];
		dfs1(v);
	}
	S[tot++]=u;
}
void dfs2(int u){
	if(belong[u]!=-1)return;
	belong[u]=scc_cnt;
	scc[scc_cnt].pb(u);
	for(int i=rg.head[u];~i;i=rg.nxt[i]){
		int v=rg.G[i];
		dfs2(v);
	}
}
void decompose(){
	scc_cnt=0;
	tot=0;
	rep(i,0,n){
		belong[i]=-1;
		mark[i]=false;
	}
	rep(i,0,n)dfs1(i);
	per(i,0,n)if(belong[S[i]]==-1){
		dfs2(S[i]);
		scc_cnt++;
	}
}
int tag[N+5];
void dfs(int id){
	//component id
	if(L[id]==-1){
		L[id]=inf;R[id]=-inf;
		rep(j,0,sz(scc[id])){
			int u=scc[id][j];
			if(tag[u]!=-1){
				L[id]=min(L[id],tag[u]);
				R[id]=max(R[id],tag[u]);
			}
			for(int i=g.head[u];~i;i=g.nxt[i]){
				int v=g.G[i];
				v=belong[v];
				dfs(v);
				L[id]=min(L[id],L[v]);
				R[id]=max(R[id],R[v]);
			}
		}
	}
}
void work(){
	int cnt=0;
	rep(i,0,scc_cnt)L[i]=-1,R[i]=-1;
	rep(i,0,n)tag[i]=-1;
	rep(i,1,west[0]+1){
		int u=west[i];
		if(vis[u])tag[u]=cnt++;
	}
	rep(i,0,scc_cnt)dfs(i);
//	rep(i,0,scc_cnt){
//		puts("******");
//		printf("scc %d   %d %d\n",i,L[i],R[i]);
//		rep(j,0,sz(scc[i]))printf("%d ",scc[i][j]+1);
//		puts("");
//	}
}
void output(){
	rep(i,1,east[0]+1){
		int u=east[i];
		u=belong[u];
		int res=R[u]-L[u]+1;
		if(res<0)res=0;
		printf("%d\n",res);
	}
}
int main(){
	input();
	bfs();
	decompose();
	work();
	output();
	return 0;
}
