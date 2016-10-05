#include <cstdio>
#include <cassert>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=250;
const int M=26;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N*3+2+2;
	static const int E=N*N+N*5+1;
	static const int inf=(int)1e9;
	
	//graph
	struct Edge{
		int to,cap,flow,cost,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _cost,int _nxt):to(_to),cap(_cap),cost(_cost),nxt(_nxt){flow=0;}
	}edge[E*2+5];
	int Gsz,head[V+5];
	bool key[E*2+5];
	inline void add_edge(int u,int v,int cap,int cost,bool flag){
		key[Gsz]=key[Gsz+1]=flag;
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
	
	//mincost
	int dis[V+5],flow[V+5],pre[V+5];
	int que[V+5];
	bool inque[V+5];
	bool SPFA(){
		rep(i,0,n){
			dis[i]=inf;
			inque[i]=false;
		}
		int L=0,H=0;
		que[H++]=src;if(H==V+5)H=0;
		inque[src]=true;
		dis[src]=0;flow[src]=inf;
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to,rest=edge[i].cap-edge[i].flow;
				if(rest>0&&dis[v]>dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					flow[v]=min(flow[u],rest);
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
			res+=flow[dest]*dis[dest];
			for(int u=dest;u!=src;u=edge[pre[u]^1].to){
				edge[pre[u]].flow+=flow[dest];
				edge[pre[u]^1].flow-=flow[dest];
			}
		}
		return res;
	}
}nw;
int n,m;
int a[N+5],q[N+5];
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n){
		scanf("%d",&a[i]);
		q[i]=0;
		rep(j,0,31)q[i]+=a[i]>>j&1;
	}
}
void build(){
	nw.init(2*n+2);
	int x=2*n,y=2*n+1;
	nw.add_edge(nw.src,y,m,0,false);
	rep(i,0,n){
		nw.add_edge(nw.src,i,1,0,true);
		nw.add_edge(i+n,nw.dest,1,0,true);
		nw.add_edge(y,i+n,1,q[i],false);
		rep(j,i+1,n)nw.add_edge(i,j+n,1,a[i]==a[j]?0:q[j],false);
	}
}
int nxt[N+5];
int id[N+5],change[N+5];
void output(){
	int penalty=nw.CostFlow();
	rep(i,0,n)nxt[i]=-1;
	for(int i=0;i<nw.Gsz;i+=2){
		int u=nw.edge[i^1].to,v=nw.edge[i].to,cap=nw.edge[i].cap,flow=nw.edge[i].flow;
		assert(cap>0);
		if(0<=u&&u<n&&n<=v&&v<2*n)
			if(flow>0)nxt[u]=v-n;
	}
	rep(i,0,n){
		id[i]=-1;
		change[i]=-1;
	}
	int cur=0,cnt=0;
	rep(i,0,n)if(id[i]==-1){
		int p=i;
//		penalty+=q[p];
		change[p]=a[p];cnt++;
		for(;;){
			id[p]=cur;
			if(nxt[p]==-1)break;
			if(a[p]!=a[nxt[p]]){
				change[nxt[p]]=a[nxt[p]];
				cnt++;
			}
			p=nxt[p];
		}
		cur++;
	}
	printf("%d %d\n",cnt+n,penalty);
	rep(i,0,n){
		char c=id[i]+'a';
		if(change[i]!=-1)printf("%c=%d\n",c,change[i]);
		printf("print(%c)\n",c);
	}
}
int main(){
	input();
	build();
	output();
	return 0;
}
/*
5 5
1 1 1 1 1
*/
