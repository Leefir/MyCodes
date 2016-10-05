//POJ2135
#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_end_=b;i<i##_end_;++i)
const int N=1000;
const int M=10000;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N+2;
	//additional source and destination vertices
	static const int E=(2*M+2)*2;
	//divide an input undirected edge into two directed edges
	//additional edges ( src , 1 ) and ( n , dest )
	//double edges for reversed edges
	static const int inf=(int)1e9;
	//change inf if it's not enough!
	
	//graph
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
		//empty cap(initially) and opposite cost for reversed edge
	}
	
	int src,dest,n;//n here denotes |V|
	void init(int _src,int _dest,int _n){
		src=_src;dest=_dest;n=_n;
		//vertex indices [ 0 , n )
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	//queue
	int que[V+5];
	bool inque[V+5];
	
	int pre_edge[V+5],pre_vertex[V+5];
	int dis[V+5],flow[V+5];
	
	bool SPFA(){
		//init
		rep(i,0,n){
			inque[i]=false;
			dis[i]=inf;
		}
		int L=0,H=0;
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;dis[src]=0;flow[src]=inf;
		
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				//only edges with non-zero cap are accessable!
				if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].cost){
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
		return dis[dest]!=inf;
	}
	int CostFlow(){
		int res=0;
		while(SPFA()){
			res+=dis[dest]*flow[dest];
			//greedily add the flow with minimal cost into ans
			int u=dest;
			while(u!=src){
				edge[pre_edge[u]].cap-=flow[dest];
				edge[pre_edge[u]^1].cap+=flow[dest];
				u=pre_vertex[u];
				//modify the cap along the flow
			}
		}
		return res;
	}
}nw;
void input(){
	int n,m;
	scanf("%d %d",&n,&m);
	nw.init(0,n+1,n+2);
	rep(i,0,m){
		int u,v,val;
		scanf("%d %d %d",&u,&v,&val);
		nw.add_edge(u,v,1,val);
		nw.add_edge(v,u,1,val);
	}
	nw.add_edge(0,1,2,0);
	nw.add_edge(n,n+1,2,0);
}
int main(){
	input();
	printf("%d\n",nw.CostFlow());
	return 0;
}
