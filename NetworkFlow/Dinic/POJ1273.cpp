#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_end_=b;i<i##_end_;++i)
const int N=200;
const int M=200;
const int INF=0x7fffffff;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N;
	static const int E=M*2;
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
		rep(i,0,n)dist[i]=INF;
		dist[src]=0;
		que[H++]=src;
		while(L<H){
			int u=que[L++];
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(dist[v]==INF&&edge[i].cap>0){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}
		}
		return dist[dest]!=INF;
	}
	
	int work[V+5];
	int dfs(int u,int aug){
		if(u==dest)return aug;
		int res=0;
		for(int &i=work[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>0&&dist[v]==dist[u]+1){
				int tmp=dfs(v,min(edge[i].cap,aug));
				edge[i].cap-=tmp;
				edge[i^1].cap+=tmp;
				aug-=tmp;
				res+=tmp;
				if(aug==0)break;
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
int n,m;
void input(){
	nw.init(0,n-1,n);
	rep(i,0,m){
		int u,v,c;
		scanf("%d %d %d",&u,&v,&c);
		--u;--v;
		nw.add_edge(u,v,c);
	}
}
void Main(){
	input();
	printf("%d\n",nw.Dinic());
}
int main(){
	while(scanf("%d %d",&m,&n)!=EOF)Main();
	return 0;
}
