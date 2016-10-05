#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=80;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N*N+2;
	static const int E=N*N+N*N*2+N*4;
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
	void init(int _n){
		n=_n;
		src=n++;dest=n++;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	//CostFlow mincost
	int que[V+5];
	bool inque[V+5];
	int dis[V+5],pre[V+5];
	bool SPFA(){
		int L=0,H=0;
		rep(i,0,n){
			inque[i]=false;
			dis[i]=inf;
		}
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;
		dis[src]=0;
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					pre[v]=i;
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
			res+=dis[dest];
			int u=dest;
			for(;;){
				int id=pre[u];
				edge[id].cap--;
				edge[id^1].cap++;
				u=edge[id^1].to;
				if(u==src)break;
			}
		}
		return res;
	}
}nw;
int n,m;
int a[N+5][N+5];
int D[]={0,-1,0,1,0};
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)rep(j,0,m)scanf("%d",&a[i][j]);
	nw.init(n*m);
	rep(i,0,n)rep(j,0,m){
		int id=i*m+j;
		if((i+j)&1){
			rep(k,0,4){
				int x=i+D[k],y=j+D[k+1];
				if(x<0||x>=n||y<0||y>=m)continue;
				nw.add_edge(id,x*m+y,1,a[i][j]!=a[x][y]);
			}
			nw.add_edge(nw.src,id,1,0);
		}else nw.add_edge(id,nw.dest,1,0);
	}
}
int main(){
	input();
	printf("%d\n",nw.CostFlow());
	return 0;
}
