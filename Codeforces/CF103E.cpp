#include <cstdio>
#include <cassert>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=300;
const int inf=(int)1e9;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N+2;
	static const int E=N*N+N;
	//graph
	struct Edge{
		int to,cap,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _nxt):to(_to),cap(_cap),nxt(_nxt){}
	}edge[E*2+5];
	int Gsz,head[V+5];
	inline void add_edge(int u,int v,int cap){
		edge[Gsz]=Edge(v,cap,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,head[v]);head[v]=Gsz++;
	}
	
	//init
	int src,dest,n;
	void init(int _n){
		n=_n;
		src=n++;dest=n++;
		rep(i,0,n)head[i]=-1;
		Gsz=0;
	}
	
	int dist[V+5],que[V+5];
	bool bfs(){
		rep(i,0,n)dist[i]=-1;
		
		int L=0,H=0;
		que[H++]=src;
		dist[src]=0;
		
		while(L<H){
			int u=que[L++];
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>0&&dist[v]==-1){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}	
		}
		
		return dist[dest]!=-1;
	}
	int work[V+5];
	int dfs(int u,int aug){
		if(u==dest||aug==0)return aug;
		
		int res=0;
		
		for(int &i=work[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>0&&dist[v]==dist[u]+1){
				int tmp=dfs(v,min(edge[i].cap,aug));
				edge[i].cap-=tmp;
				edge[i^1].cap+=tmp;
				res+=tmp;aug-=tmp;
				if(aug==0)break;
			}
		}
		
		return res;
	}
	int Dinic(){
		int res=0;
		while(bfs()){
			rep(i,0,n)work[i]=head[i];
			res+=dfs(src,(int)1e9);
		}
		return res;
	}
}nw;
int cost[N+5];
struct Bipartite_Graph{
	static const int V=N+N;
	
	bool g[V+5][V+5];
	
	int n;
	void init(int _n){
		n=_n;
		rep(i,0,n)rep(j,0,n)g[i][j]=false;
	}
	
	int match[V+5];//match[Yi]=Xi
	bool visy[V+5];
	bool find(int x){
		rep(y,0,n)if(g[x][y]){
			if(visy[y])continue;
			visy[y]=true;
			if(match[y]==-1||find(match[y])){
				match[y]=x;
				return true;
			}
		}
		return false;
	}
	void Hungary(){
		//find a complete match
		rep(y,0,n)match[y]=-1;
		rep(x,0,n){
			rep(y,0,n)visy[y]=false;
			assert(find(x));
		}
	}
	
	void build(){
		//build network
		nw.init(n);
		rep(y,0,n){
			int x=match[y];
			if(cost[x]>0)nw.add_edge(nw.src,y,cost[x]);
			else nw.add_edge(y,nw.dest,-cost[x]);
			rep(i,0,n)if(g[x][i]&&i!=y)nw.add_edge(y,i,inf);
		}
	}
}bpt;
int n,sum;
void input(){
	scanf("%d",&n);
	bpt.init(n);
	
	rep(i,0,n){
		int m;scanf("%d",&m);
		rep(j,0,m){
			int x;scanf("%d",&x);--x;
			bpt.g[i][x]=true;
		}
	}
	sum=0;
	rep(i,0,n){
		scanf("%d",&cost[i]);
		cost[i]=-cost[i];
		if(cost[i]>0)sum+=cost[i];
	}
}
int main(){
	input();
	bpt.Hungary();
	bpt.build();
	printf("%d\n",-(sum-nw.Dinic()));
	return 0;
}
