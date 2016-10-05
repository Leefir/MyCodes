//POJ 1273
#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_end_=b;i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=a;i>=i##_begin_;--i)
const int V=200;
const int E=200;
const int INF=0x7fffffff;
//0 <= Ci <= 10,000,000
struct Edge{
	int to,cap;
}G[E*2+5];
int head[V+5],nxt[E*2+5];
//E*2 for addtional reversed edges
int Gsz;
void init_Graph(const int n){
	rep(i,0,n)head[i]=-1;
	Gsz=0;
}
inline void add_edge(int u,int v,int cap){
	G[Gsz]=(Edge){v,cap};nxt[Gsz]=head[u];head[u]=Gsz++;
	G[Gsz]=(Edge){u,0};nxt[Gsz]=head[v];head[v]=Gsz++;
}
int n,m;
int src,dest;
void input(){
	src=0,dest=n-1;
	init_Graph(n);
	rep(i,0,m){
		int u,v,c;
		scanf("%d %d %d",&u,&v,&c);
		--u;--v;
		add_edge(u,v,c);
	}
}
int q[V+5];
int dist[V+5];
bool bfs(){
	int L=0,H=0;
	rep(i,0,n)dist[i]=-1;
	dist[src]=0;
	q[H++]=src;
	while(L<H){
		int u=q[L++];
		for(int i=head[u];~i;i=nxt[i]){
			int v=G[i].to;
			if(dist[v]==-1&&G[i].cap>0){
				dist[v]=dist[u]+1;
				q[H++]=v;
			}
		}
	}
	return dist[dest]!=-1;
}
int work[V+5];
bool vis[V+5];
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
int dfs(int u,int flow){
	vis[u]=true;
	if(u==dest)return flow;
	for(int &i=work[u];~i;i=nxt[i]){
		int v=G[i].to;
		if(!vis[v]&&G[i].cap>0&&dist[v]==dist[u]+1){
			int tmp=dfs(v,min(flow,G[i].cap));
			if(tmp>0){
				G[i].cap-=tmp;
				G[i^1].cap+=tmp;
				return tmp;
			}
		}
	}
	return 0;
}
int Dinic(){
	int flow=0;
	while(bfs()){
		rep(i,0,n)work[i]=head[i];
		for(;;){
			rep(i,0,n)vis[i]=false;
			int tmp=dfs(src,INF);
			if(tmp>0)flow+=tmp;
			else break;
		}
	}
	return flow;
}
void Main(){
	input();
	printf("%d\n",Dinic());
}
int main(){
	while(scanf("%d %d",&m,&n)!=EOF)Main();
	return 0;
}
