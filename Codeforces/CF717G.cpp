#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=500;
const int M=100;
typedef unsigned long long ull;
#define pb push_back
#define sz(x) ((int)((x).size()))
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWrok{
	static const int V=N+2;
	static const int E=N+1+N*M;
	static const int inf=(int)1e9;
	
	//graph
	struct Edge{
		int to,cap,cost,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _cost,int _nxt):to(_to),cap(_cap),cost(_cost),nxt(_nxt){}
	}edge[E*2+5];
	int Gsz,head[V+5];
	inline void add_edge(int u,int v,int cap,int cost){
		edge[Gsz]=Edge(v,cap,cost,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,-cost,head[v]);head[v]=Gsz++;
	}
	
	//init
	int src,dest,n;
	void init(int _src,int _dest,int _n){
		src=_src,dest=_dest,n=_n;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	//max cost
	int dis[V+5],flow[V+5],pre[V+5];
	int que[V+5];
	bool inque[V+5];
	bool SPFA(){
		int L=0,H=0;
		rep(i,0,n){
			dis[i]=-1;
			inque[i]=false;
		}
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;
		dis[src]=0;flow[src]=inf;
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>0&&dis[v]<dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					flow[v]=min(flow[u],edge[i].cap);
					pre[v]=i;
					if(!inque[v]){
						que[H++]=v;if(H==V+5)H=0;
						inque[v]=true;
					}
				}
			}
		}
		return dis[dest]!=-1;
	}
	int CostFlow(){
		int res=0;
		while(SPFA()){
			res+=flow[dest]*dis[dest];
			for(int u=dest;u!=src;u=edge[pre[u]^1].to){
				edge[pre[u]].cap-=flow[dest];
				edge[pre[u]^1].cap+=flow[dest];
			}
		}
		return res;
	}
}nw;
int n,m,x;
char T[N+5],str[M+5][N+5];
int p[M+5],tl,sl[M+5];
void input(){
	scanf("%d",&n);
	scanf("%s",T);tl=strlen(T);
	scanf("%d",&m);
	rep(i,0,m){
		scanf("%s %d",str[i],&p[i]);
		sl[i]=strlen(str[i]);
	}
	scanf("%d",&x);
}
#define hash sdiojfaodsnofi
inline ull hash(char *s,int len){
	ull res=0;
	rep(i,0,len)
		res=res*26+s[i]-'a';
	return res;
}
#define pow adsifnlasd
ull pow[N+5];
bool chk(int a,int b){
	if(sl[a]<sl[b])return false;
	ull h=hash(str[b],sl[b]);
	ull m=hash(str[a],sl[b]);
	for(int i=sl[b];i<=sl[a];++i){
		if(h==m)return true;
		if(i<sl[a])m=m*26+(str[a][i]-'a')-(str[a][i-sl[b]]-'a')*pow[sl[b]];
	}
	return false;
}
void insert(int id,int val){
	ull h=hash(str[id],sl[id]);
	ull m=hash(T,sl[id]);
	for(int i=sl[id];i<=tl;++i){
		if(h==m)nw.add_edge(i-sl[id],i,1,val);
		if(i<tl)m=m*26+(T[i]-'a')-(T[i-sl[id]]-'a')*pow[sl[id]];
	}
}
void build(){
	nw.init(n+1,n,n+2);
	
	//link
	nw.add_edge(nw.src,0,x,0);
	rep(i,0,n-1)nw.add_edge(i,i+1,x,0);
	nw.add_edge(n-1,nw.dest,x,0);
	
	//inclusion
	pow[0]=1;
	rep(i,1,n+1)pow[i]=pow[i-1]*26;
	rep(i,0,m){
		int val=0;
//		rep(j,0,m)if(chk(i,j))val+=p[j];
//		printf("%s %d\n",str[i],p[i]);
		insert(i,p[i]);
	}
}
int main(){
	input();
	build();
	printf("%d\n",nw.CostFlow());
	return 0;
}
