#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=50;
const int K=1000;
const int inf=(int)1e9;
int n,k;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N;
	static const int E=N*N*2;
	
	//graph
	struct Edge{
		int to,cap,cost,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _cost,int _nxt):to(_to),cap(_cap),cost(_cost),nxt(_nxt){}
	}edge[E*2];
	int Gsz,head[V+5];
	inline void add_edge(int u,int v,int cap,int cost){
		edge[Gsz]=Edge(v,cap,cost,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,-cost,head[v]);head[v]=Gsz++;	
	}
	
	//init
	int src,dest,n;
	void init(int _n){
		n=_n;
		src=0,dest=n-1;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	int dis[V+5],flow[V+5],pre[V+5];
	int que[V+5];
	bool inque[V+5];
	bool SPFA(){
		rep(i,0,n){
			dis[i]=inf;
			inque[i]=false;
		}
		int L=0,H=0;
		dis[src]=0;flow[src]=inf;
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					pre[v]=i;
					flow[v]=min(flow[u],edge[i].cap);
					if(!inque[v]){
						que[H++]=v;if(H==V+5)H=0;
						inque[v]=true;
					}
				}
			}
		}
		return dis[dest]!=inf;
	}
	int CostFlow(){
		int res=0;
		while(SPFA()){
			if(k<dis[dest])break;
			int cnt=flow[dest];
			if(dis[dest]!=0)cnt=min(cnt,k/dis[dest]);
			k-=dis[dest]*cnt;
			res+=cnt;
			int u=dest;
			for(;;){
				edge[pre[u]].cap-=cnt;
				edge[pre[u]^1].cap+=cnt;
				u=edge[pre[u]^1].to;
				if(u==src)break;
			}
		}
		return res;
	}
}nw;
int main(){
	scanf("%d %d",&n,&k);
	nw.init(n);
	rep(i,0,n)rep(j,0,n){
		int cap;scanf("%d",&cap);
		if(cap==0)continue;
		nw.add_edge(i,j,cap,0);
		nw.add_edge(i,j,inf,1);
	}
	printf("%d\n",nw.CostFlow());
	return 0;
}
