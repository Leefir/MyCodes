#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=10;
const int T=60;
const int inf=(int)1e9;
int n,t;
char A[N][N+1],B[N][N+1];
void input(){
	scanf("%d %d",&n,&t);
	rep(i,0,n)scanf("%s",A[i]);
	rep(i,0,n)scanf("%s",B[i]);
}
bool fbd[T+5][N][N];
bool reach[N][N][N][N];
struct node{
	int x,y,dis;
	node(){}
	node(int _x,int _y,int _dis):x(_x),y(_y),dis(_dis){}
}que[N*N*T+5];
bool mark[N][N];
int D[]={0,1,0,-1,0};
inline bool chk(char c){
	return '1'<=c&&c<='9';
}
void bfs(bool rc[N][N],int sx,int sy){
	rep(i,0,n)rep(j,0,n){
		rc[i][j]=false;
		mark[i][j]=false;
	}
	int L=0,H=0;
	que[H++]=node(sx,sy,0);
	mark[sx][sy]=true;
	while(L<H){
		node now=que[L++];
		if(now.dis>t)continue;
		if((now.dis==0||!fbd[now.dis-1][now.x][now.y])&&chk(B[now.x][now.y]))rc[now.x][now.y]=true;
		if(fbd[now.dis][now.x][now.y])continue;
		rep(i,0,4){
			int xx=now.x+D[i],yy=now.y+D[i+1];
			if(xx<0||xx>=n||yy<0||yy>=n)continue;
			if(mark[xx][yy]||A[xx][yy]=='Y')continue;
			mark[xx][yy]=true;
			que[H++]=node(xx,yy,now.dis+1);
		}
	}
}
void search(){
	rep(i,0,n)rep(j,0,n)fbd[0][i][j]=A[i][j]=='Z';
	rep(k,1,t+1){
		rep(i,0,n)rep(j,0,n)fbd[k][i][j]=fbd[k-1][i][j];
		rep(i,0,n)rep(j,0,n)if(fbd[k-1][i][j])rep(d,0,4){
			int x=i+D[d],y=j+D[d+1];
			if(x<0||x>=n||y<0||y>=n)continue;
			if(A[x][y]=='Y')continue;
			fbd[k][x][y]=true;
		}
//		rep(i,0,n){
//			rep(j,0,n)printf("%d",fbd[k][i][j]);
//			puts("");
//		}
//		puts("");
	}
	rep(i,0,n)rep(j,0,n)if(chk(A[i][j]))
		bfs(reach[i][j],i,j);
}
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
struct NetWork{
	static const int V=N*N*2+2;
	static const int E=N*N*N*N*2;
	
	//graph
	struct Edge{
		int to,cap,nxt;
		Edge(){}
		Edge(int _to,int _cap,int _nxt):to(_to),cap(_cap),nxt(_nxt){}
	}edge[E*2+5];
	int Gsz,head[V+5];
	inline void add_edge(int u,int v,int cap){
//		printf("%d -> %d   %d\n",u,v,cap);
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
	int dist[V+5];
	int que[V+5];
	bool bfs(){
		rep(i,0,n)dist[i]=-1;
		int L=0,H=0;
		que[H++]=src;
		dist[src]=0;
		while(L<H){
			int u=que[L++];
//			printf("bfs %d\n",u);
			for(int i=head[u];~i;i=edge[i].nxt){
				int v=edge[i].to;
//				printf("to %d\n",v);
				if(edge[i].cap>0&&dist[v]==-1){
					dist[v]=dist[u]+1;
					que[H++]=v;
				}
			}
		}
		return dist[dest]!=-1;
	}
	int work[N+5];
	int dfs(int u,int aug){
		if(u==dest||aug==0)return aug;
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
			res+=dfs(src,inf);
		}
		return res;
	}
	
	void output(int n){
		for(int i=0;i<Gsz;i+=2){
			int u=edge[i^1].to,v=edge[i].to;
			if(u==src||v==dest)continue;
			if(inf-edge[i].cap)printf("( %d , %d ) -> ( %d , %d )   %d\n",u/n,u%n,v/n-n,v%n,inf-edge[i].cap);
		}
	}
}nw;
void build(){
	nw.init(n*n*2);
	rep(i,0,n)rep(j,0,n)if(chk(A[i][j])){
		nw.add_edge(nw.src,i*n+j,A[i][j]-'0');
		rep(x,0,n)rep(y,0,n)if(chk(B[x][y])&&reach[i][j][x][y]){
//			printf("( %d , %d ) -> ( %d , %d ) \n",i,j,x,y);
			nw.add_edge(i*n+j,x*n+y+n*n,inf);
		}
	}
	rep(i,0,n)rep(j,0,n)if(chk(B[i][j]))
		nw.add_edge(i*n+j+n*n,nw.dest,B[i][j]-'0');
}
int main(){
	input();
	search();
	build();
	printf("%d\n",nw.Dinic());
//	nw.output(n);
	//try SAP
	return 0;
}
