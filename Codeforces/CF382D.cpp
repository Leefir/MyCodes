#include <ctime>
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

const int N=2000;
int n,m;
char str[N+5][N+5];
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)scanf("%s",str[i]);
}
int ans;
bool vis[N+5][N+5];
int mx[N+5][N+5];
int dx[256],dy[256];
int D[]={0,-1,0,1,0};
inline bool in(int x,int y){
	if(x<0||x>=n)return false;
	if(y<0||y>=m)return false;
	return true;
}
inline void chk_max(int &x,int &y,int z){
	if(z>=x){
		y=x;x=z;
	}else if(z>=y){
		y=z;
	}
}
struct con{
	int x,y,dep;
}q[N*N+5];
void bfs(){
	int L=0,H=0;
	rep(i,0,n)rep(j,0,m)if(str[i][j]!='#'){
		char c=str[i][j];
		int tx=i+dx[c],ty=j+dy[c];
		if(!in(tx,ty))continue;
		if(str[tx][ty]=='#')
			q[H++]=(con){i,j,1};
	}
	while(L<H){
		int x=q[L].x,y=q[L].y,dep=q[L].dep;L++;
		assert(vis[x][y]==false);
		vis[x][y]=true;
		
		
		rep(i,0,4){
			int tx=x+D[i],ty=y+D[i+1];
			if(!in(tx,ty))continue;
			char c=str[tx][ty];
			if(c=='#')continue;
			if(tx+dx[c]==x&&ty+dy[c]==y)
				q[H++]=(con){tx,ty,dep+1};
		}
	}
	per(i,0,H){
		int x=q[i].x,y=q[i].y,dep=q[i].dep;
		
		int mx1=dep,mx2=0;
		
		rep(i,0,4){
			int tx=x+D[i],ty=y+D[i+1];
			if(!in(tx,ty))continue;
			char c=str[tx][ty];
			if(c=='#')continue;
			if(tx+dx[c]==x&&ty+dy[c]==y)
				chk_max(mx1,mx2,mx[tx][ty]);
		}
		int tmp=mx1+mx2;
		if(mx1==mx2)tmp--;
		if(tmp>ans)ans=tmp;
		
		mx[x][y]=mx1;
	}
}
void solve(){
	//init
	ans=0;
	rep(i,0,n)rep(j,0,m)vis[i][j]=false;
	
	bfs();
	int mx1=0,mx2=0;
	rep(i,0,n)rep(j,0,m)if(str[i][j]!='#'){
		char c=str[i][j];
		int tx=i+dx[c],ty=j+dy[c];
		if(!in(tx,ty))continue;
		if(str[tx][ty]=='#'){
//			dfs(i,j,1);
			chk_max(mx1,mx2,mx[i][j]);
		}
	}
	rep(i,0,n)rep(j,0,m)if(str[i][j]!='#'&&!vis[i][j]){
		puts("-1");
		return;
	}
	mx1+=mx2;
	if(mx1>ans)ans=mx1;
	printf("%d\n",ans);
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
//	rep(i,0,5){
	
	dx['^']=-1;dy['^']=0;
	dx['v']=1;dy['v']=0;
	dx['<']=0;dy['<']=-1;
	dx['>']=0;dy['>']=1;
	input();
	solve();
	
//	}
	return 0;
}
