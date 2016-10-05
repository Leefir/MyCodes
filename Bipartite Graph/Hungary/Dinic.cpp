#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=500;
const int M=1000;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWrok{
	static const int V=N+N+2;
	static const int E=(M+N+N)*2;
	static const int INF=0x7fffffff;
	//graph
	int to[E+5],cap[E+5],nxt[E+5];
	int g,head[V+5];
	inline void add_edge(int u,int v,int c){
		to[g]=v;cap[g]=c;nxt[g]=head[u];head[u]=g++;
		to[g]=u;cap[g]=0;nxt[g]=head[v];head[v]=g++;
	}
	
	//init
	int src,dest,n;
	void init(int _n){
		n=_n;
		src=n++;dest=n++;
		rep(i,0,n)head[i]=-1;
		g=0;
	}
	
	//Dinic
	int que[V+5],dist[V+5];
	bool bfs(){
		rep(i,0,n)dist[i]=INF;
		int L=0,H=0;
		que[H++]=src;dist[src]=0;
		while(L<H){
			int u=que[L++];
			for(int i=head[u];~i;i=nxt[i]){
				int v=to[i];
				if(dist[v]==INF&&cap[i]>0){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}
		}
		return dist[dest]!=INF;
	}
	int work[V+5];
	int dfs(int u,int aug){
		if(u==dest||aug==0)return aug;
		int res=0;
		for(int &i=work[u];~i;i=nxt[i]){
			int v=to[i];
			if(cap[i]>0&&dist[v]==dist[u]+1){
				int tmp=dfs(v,min(cap[i],aug));
				cap[i]-=tmp;cap[i^1]+=tmp;
				aug-=tmp;res+=tmp;
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
int k,n,m;
void input(){
	scanf("%d %d",&n,&m);
	nw.init(n+m);
	rep(i,0,k){
		int x,y;
		scanf("%d %d",&x,&y);
		//X [ 0 , n ) y [ n , n+m )
		--x;--y;y+=n;
		nw.add_edge(x,y,1);
	}
	rep(i,0,n)nw.add_edge(nw.src,i,1);
	rep(i,0,m)nw.add_edge(i+n,nw.dest,1);
}
void Main(){
	input();
	printf("%d\n",nw.Dinic());
}
int main(){
	while(scanf("%d",&k),k!=0)Main();
	return 0;
}
