#include <ctime>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
const int inf=(int)1e9;
const int INF=0x7fffffff;
const ll linf=1LL<<60;

//the absolute or relative error shouldn't exceed 10e-6
const int N=400;
int n,rt;
pii point[N+5];
void input(){
	scanf("%d",&n);
	int mx=-1;
	rep(i,0,n){
		scanf("%d %d",&point[i].fi,&point[i].se);
		if(point[i].se>mx)mx=point[i].se;
	}
	rt=-1;
	rep(i,0,n){
		if(point[i].se==mx){
			if(rt==-1)rt=i;
			else{
				rt=-2;
				break;
			}
		}
	}
}
struct Network{
	static const int V=N+N-1+2;
	static const int E=(N*N+N+N)*2;
	static const db inf=10000*N;
	struct Edge{
		int to,cap,nxt;
		db cost;
		Edge(){}
		Edge(int _to,int _cap,db _cost,int _nxt):to(_to),cap(_cap),cost(_cost),nxt(_nxt){}
	}edge[E+5];
	int Gsz,head[V+5];
	inline void add_edge(int u,int v,int cap,db cost){
		edge[Gsz]=Edge(v,cap,cost,head[u]);head[u]=Gsz++;
		edge[Gsz]=Edge(u,0,-cost,head[v]);head[v]=Gsz++;
	}
	
	int src,dest,n;
	void init(int _src,int _dest,int _n){
		src=_src;dest=_dest;n=_n;
		Gsz=0;
		rep(i,0,n)head[i]=-1;
	}
	bool full(){
		//check the edges linking to dest
		rep(i,0,Gsz)if(edge[i].to==dest&&edge[i].cap>0){
//			printf("form %d cap %d\n",edge[i^1].to,edge[i].cap);
			return false;
		}
		return true;
	}
	
	int que[V+5];
	bool inque[V+5];
	db dis[V+5];
	int flow[V+5],pre_edge[V+5];
	bool SPFA(){
		rep(i,0,n){
			dis[i]=inf;
			inque[i]=false;
		}
		int L=0,H=0;
		que[H++]=src;if(H==V+5)H=0;
		dis[src]=0;inque[src]=true;
		flow[src]=INF;
		
		while(L!=H){
			int u=que[L++];if(L==V+5)L=0;
			inque[u]=false;
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
//				printf("%d - > %d cap %d\n",u,v,edge[i].cap);
				if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].cost){
					dis[v]=dis[u]+edge[i].cost;
					pre_edge[v]=i;
					flow[v]=min(flow[u],edge[i].cap);
					if(!inque[v]){
						que[H++]=v;if(H==V+5)H=0;
						inque[v]=true;
					}
				}
			}
		}
		return dis[dest]<inf-100;
	}
	db CostFlow(){
		db res=0;
		while(SPFA()){
//			puts("**********");
			res+=dis[dest]*flow[dest];
			int u=dest;
			for(;;){
//				printf("path %d\n",u);
				int id=pre_edge[u];
				edge[id].cap-=flow[dest];
				edge[id^1].cap+=flow[dest];
				u=edge[id^1].to;
				if(u==src)break;
			}
		}
		return res;
	}
}nw;
db dis(int a,int b){
	db x=point[a].fi-point[b].fi;
	db y=point[a].se-point[b].se;
	return sqrt(x*x+y*y);
}
int id[N+5][2];
void build(){
	int tot=0;
	rep(i,0,n){
		id[i][0]=tot++;
		if(i!=rt)id[i][1]=tot++;
	}
//	rep(i,0,n){
//		printf("id[%d] %d %d\n",i,id[i][0],id[i][1]);
//	}
	
	nw.init(tot,tot+1,tot+2);
	
	rep(i,0,n)nw.add_edge(nw.src,id[i][0],2,0);
	rep(i,0,n)if(i!=rt)nw.add_edge(id[i][1],nw.dest,1,0);
	rep(i,0,n)rep(j,0,n)if(point[i].se>point[j].se){
		//i is higher than j
		nw.add_edge(id[i][0],id[j][1],1,dis(i,j));
	}
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	input();
	if(rt==-2){puts("-1");return 0;}
	build();
	db ans=nw.CostFlow();
	if(nw.full())printf("%.15f\n",ans);
	else puts("-1");
	return 0;
}
