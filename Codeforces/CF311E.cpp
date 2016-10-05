#include <cstdio>
#include <cassert>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=(int)1e4;
const int M=2000;
const int inf=(int)1e9+1;

inline int min(int x,int y){
	if(x<y)return x;
	return y;
}

struct NetWork{
	static const int V=N+M+2;
	static const int E=N*2+10*M+M;
	
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
	
	//Dinic
	int que[V+5],dist[V+5];
	bool bfs(){
		rep(i,0,n)dist[i]=inf;
			
		int L=0,H=0;
		que[H++]=src;dist[src]=0;
		
		while(L<H){
			int u=que[L++];
			
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].cap>0&&dist[v]==inf){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}
		}
		
		return dist[dest]!=inf;
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
				res+=tmp;
				if((aug-=tmp)==0)break;
			}
		}
		
		return res;
	}
	int Dinic(){
		int res=0;
		
		while(bfs()){
			rep(i,0,n)work[i]=head[i];
			res+=dfs(src,inf);
		}
		
		return res;
	}
	
}nw;
int n,m,g,sum;
int f[N+5];
void input(){
	scanf("%d %d %d",&n,&m,&g);
	nw.init(n+m);
	
	//dogs
	rep(i,0,n)scanf("%d",&f[i]);
	rep(i,0,n){
		int val;scanf("%d",&val);
		if(f[i]==0){
			nw.add_edge(nw.src,i,val);
			nw.add_edge(i,nw.dest,0);
		}else if(f[i]==1){
			nw.add_edge(nw.src,i,0);
			nw.add_edge(i,nw.dest,val);
		}else assert(false);
	}
	
	//folks
	sum=0;
	rep(i,0,m){
		int flag,val,cnt,frd;
		scanf("%d %d %d",&flag,&val,&cnt);
		sum+=val;
		rep(j,0,cnt){
			int id;scanf("%d",&id);--id;
			if(flag==0){
				nw.add_edge(i+n,id,inf);
			}else if(flag==1){
				nw.add_edge(id,i+n,inf);
			}else assert(false);
		}
		scanf("%d",&frd);
		if(flag==0){
			nw.add_edge(nw.src,i+n,val+frd*g);
		}else if(flag==1){
			nw.add_edge(i+n,nw.dest,val+frd*g);
		}else assert(false);
	}
}
int main(){
	input();
	printf("%d\n",sum-nw.Dinic());
	return 0;
}
