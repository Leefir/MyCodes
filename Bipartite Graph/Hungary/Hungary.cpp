#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=500;
const int M=1000;
struct Bipartite_Graph{
	static const int V=N;
	static const int E=M;
	//graph
	int to[E+5],nxt[E+5];
	int g,head[V+5];
	inline void add_edge(int u,int v){
		to[g]=v;nxt[g]=head[u];head[u]=g++;
	}
	
	//init
	int X,Y;
	void init(int _X,int _Y){
		X=_X;Y=_Y;
		rep(i,0,X)head[i]=-1;
		g=0;
	}
	
	//Hungary
	int match[V+5];//match[Yi]=Xj;
	bool vis[V+5];//vis[Yi]
	bool find(int x){
		for(int i=head[x];~i;i=nxt[i]){
			int y=to[i];
			if(vis[y])continue;
			vis[y]=true;
			if(match[y]==-1||find(match[y])){
				match[y]=x;
				return true;
			}
		}
		return false;
	}
	int Hungary(){
		int res=0;
		//here |X|=|Y|
		rep(i,0,Y)match[i]=-1;
		rep(i,0,X){
			rep(j,0,Y)vis[j]=false;
			res+=find(i);
		}
		return res;
	}
}bpt;
int k,n,m;
void input(){
	scanf("%d %d",&n,&m);
	bpt.init(n,m);
	rep(i,0,k){
		int x,y;
		scanf("%d %d",&x,&y);
		--x;--y;
		bpt.add_edge(x,y);
	}
}
void Main(){
	input();
	printf("%d\n",bpt.Hungary());
}
int main(){
	while(scanf("%d",&k),k!=0)Main();
	return 0;
}
