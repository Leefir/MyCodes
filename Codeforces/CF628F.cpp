#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=(int)1e4;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N+5+2;
	static const int E=5+N+N;
	static const int inf=(int)1e9;
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
	
	//MaxFlow
	int dist[V+5],que[V+5];
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
	void Dinic(){
		while(bfs()){
			rep(i,0,n)work[i]=head[i];
			dfs(src,inf);
		}
	}
	
	//judge full flow
	bool full(){
		rep(i,0,Gsz)if(edge[i].to==dest&&edge[i].cap>0)return false;
		return true;
	}
}nw;
int n,b,q;
typedef std::pair<int,int> pii;
#define fi first
#define se second
pii a[N+5];
void input(){
	scanf("%d %d %d",&n,&b,&q);
	rep(i,0,q)scanf("%d %d",&a[i].fi,&a[i].se);
	a[q++]=pii(b,n);
}
bool flag;
void build(){
	sort(a,a+q);
	flag=false;
	int pre=0,cnt=0;
	
	nw.init(q+5);
	rep(i,0,5)nw.add_edge(nw.src,q+i,n/5);
	
	rep(i,0,q){
//		printf("%d %d\n",a[i].fi,a[i].se);
		if(a[i].se-cnt>a[i].fi-pre){
			flag=true;
			return;
		}
		nw.add_edge(i,nw.dest,a[i].se-cnt);
		
		int tmp[5]={0};
		rep(j,pre+1,a[i].fi+1)tmp[j%5]++;
		
		rep(j,0,5)if(tmp[j])nw.add_edge(q+j,i,tmp[j]);
		
		pre=a[i].fi,cnt=a[i].se;
	}
}
int main(){
	input();
	build();
	if(flag){
		puts("unfair");
		return 0;
	}
	
//	puts("pass");
	nw.Dinic();
	if(nw.full())puts("fair");
	else puts("unfair");
	return 0;
}
