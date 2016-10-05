#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_end_=b;i<i##_end_;++i)
const int N=1200;
const int M=1200;
const int INF=0x7fffffff;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N+M+2;
	static const int E=(N+M+N*M)*2;
	struct Edge{
		int to,cap,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _nxt):to(_to),cap(_cap),nxt(_nxt){}
	}edge[E+5];
	int head[V+5];
	int Gsz;
	inline void add_edge(int u,int v,int cap){
		edge[Gsz]=Edge(v,cap,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,head[v]);head[v]=Gsz++;
	}
	
	int src,dest,n;
	void init(int _src,int _dest,int _n){
		src=_src;dest=_dest;n=_n;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	int dist[V+5];
	int que[V+5];
	bool bfs(){
		int L=0,H=0;
		rep(i,0,n)dist[i]=-1;
		dist[src]=0;
		que[H++]=src;
		while(L<H){
			int u=que[L++];
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(dist[v]==-1&&edge[i].cap>0){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}
		}
		return dist[dest]!=-1;
	}
	
	int work[V+5];
	int dfs(int u,int flow){
		if(u==dest||flow==0)return flow;
		int res=0;
		for(int &i=work[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>0&&dist[v]==dist[u]+1){
				int tmp=dfs(v,min(edge[i].cap,flow));
				edge[i].cap-=tmp;
				edge[i^1].cap+=tmp;
				flow-=tmp;
				res+=tmp;
				if(flow==0)break;
			}
		}
		return res;
	}
	int Dinic(){
		int res=0;
		while(bfs()){
			rep(i,0,n)work[i]=head[i];
			res+=dfs(src,INF);
		}
		return res;
	}
}nw;
int n,m,Sum;
void input(){
	Sum=0;
	scanf("%d %d",&n,&m);
	//task [ 0 , n )
	//machine [ n , n+m )
	//source n+m
	//destination n+m+1
	nw.init(n+m,n+m+1,n+m+2);
	rep(i,0,n){
		int profit,cnt;
		scanf("%d %d",&profit,&cnt);
		nw.add_edge(nw.src,i,profit);
		Sum+=profit;
		rep(j,0,cnt){
			int id,cost;
			scanf("%d %d",&id,&cost);
			--id;
			nw.add_edge(i,id+n,cost);
		}
	}
	rep(i,0,m){
		int cost;scanf("%d",&cost);
		nw.add_edge(i+n,nw.dest,cost);
	}
}
int main(){
	input();
	printf("%d\n",Sum-nw.Dinic());
	return 0;
}
