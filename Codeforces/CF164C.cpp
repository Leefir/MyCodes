#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a,i##_end_=b;i<i##_end_;++i)
const int N=1000;
const int K=50;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
int n,k;
struct NetWork{
	static const int V=N*2+3;
	static const int E=(1+N+N+N*N+N)*2;
	static const int inf=(int)1e9;
	
	struct Edge{
		int to,cap,cost,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _cost,int _nxt):to(_to),cap(_cap),cost(_cost),nxt(_nxt){}
	}edge[E+5];
	int head[V+5];
	int Gsz;
	inline void add_edge(int u,int v,int cap,int cost){
		edge[Gsz]=Edge(v,cap,cost,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,-cost,head[v]);head[v]=Gsz++;
	}
	
	int src,dest,n;
	void init(int _src,int _dest,int _n){
		src=_src;dest=_dest;n=_n;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	int que[V+5];
	bool inque[V+5];
	
	int pre_edge[V+5],pre_vertex[V+5];
	int dis[V+5],flow[V+5];
	
	bool SPFA(){
		//longest path
		rep(i,0,n){
			inque[i]=false;
			dis[i]=-inf;
		}
		int L=0,H=0;
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;dis[src]=0;flow[src]=inf;
		
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
//			printf("u %d\n",u);
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				//longest path
				if(edge[i].cap>0&&dis[v]<dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					pre_vertex[v]=u;
					pre_edge[v]=i;
					flow[v]=min(flow[u],edge[i].cap);
					if(!inque[v]){
						que[H++]=v;if(H==V+5)H=0;
						inque[v]=true;
					}
				}
			}
		}
		return dis[dest]!=-inf;
	}
	int CostFlow(){
		int res=0;
		while(SPFA()){
//			printf("flow %d\n",flow[dest]);
			res+=dis[dest]*flow[dest];
//			rep(i,0,n)printf("dis[%d] %d\n",i,dis[i]);
			int u=dest;
			while(u!=src){
//				printf("path %d\n",u);
				edge[pre_edge[u]].cap-=flow[dest];
				edge[pre_edge[u]^1].cap+=flow[dest];
				u=pre_vertex[u];
			}
		}
		return res;
	}
	void output(const int n){
		int ans[N+5];
		rep(i,0,n){
			int id=i*2;
			printf("%d ",edge[id].cap==0);
		}
	}
}nw;
int s[N+5],t[N+5],c[N+5];
int x[N*2+5];
void input(){
	scanf("%d %d",&n,&k);
	int cnt=0;
	rep(i,0,n){
		scanf("%d %d %d",&s[i],&t[i],&c[i]);
		t[i]=s[i]+t[i];
		x[cnt++]=s[i];
		x[cnt++]=t[i];
	}
	sort(x,x+cnt);
	cnt=unique(x,x+cnt)-x;
	//[ s , t ]
	nw.init(cnt,cnt+1,cnt+2);
	rep(i,0,n){
		nw.add_edge(lower_bound(x,x+cnt,s[i])-x,lower_bound(x,x+cnt,t[i])-x,1,c[i]);
//		printf("add %d %d\n",lower_bound(x,x+cnt,s[i])-x,lower_bound(x,x+cnt,t[i])-x);
	}
	nw.add_edge(nw.src,0,k,0);
	nw.add_edge(cnt-1,nw.dest,k,0);
	rep(i,1,cnt)nw.add_edge(i-1,i,k,0);
}
int main(){
	input();
	nw.CostFlow();
	nw.output(n);
	return 0;
}
