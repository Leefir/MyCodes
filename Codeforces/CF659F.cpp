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

const int N=1000;
int a[N+5][N+5],id[N+5][N+5];
int n,m;
ll k;
pii p[N*N+5];
int tot;
bool cmp(pii x,pii y){
	return a[x.fi][x.se]>a[y.fi][y.se];
}
void input(){
	scanf("%d %d %I64d",&n,&m,&k);
	tot=0;
	rep(i,0,n)rep(j,0,m){
		scanf("%d",&a[i][j]);
		p[tot++]=pii(i,j);
	}
	sort(p,p+tot,cmp);
	rep(i,0,tot)id[p[i].fi][p[i].se]=i;
}
int fa[N*N+5],cnt[N*N+5];
int get(int v){
	if(fa[v]!=v)fa[v]=get(fa[v]);
	return fa[v];
}
void unite(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[y]=x;
	cnt[x]+=cnt[y];
}
int D[]={0,1,0,-1,0};
int combine(int x,int y,int v){
	rep(i,0,4){
		int tx=x+D[i],ty=y+D[i+1];
		if(tx<0||tx>=n)continue;
		if(ty<0||ty>=m)continue;
		if(a[tx][ty]>v||(a[tx][ty]==v&&id[tx][ty]<id[x][y]))unite(id[x][y],id[tx][ty]);
	}
	return get(id[x][y]);
	//return rt
}
int sum;
int b[N+5][N+5];
void flood(int x,int y,int v){
	if(b[x][y])return;
	if(sum==0)return;
	sum--;
	b[x][y]=v;
	rep(i,0,4){
		int tx=x+D[i],ty=y+D[i+1];
		if(tx<0||tx>=n)continue;
		if(ty<0||ty>=m)continue;
		if(a[tx][ty]>=v)flood(tx,ty,v);
	}
}
void print(int x,int y,int v){
	//flood fill begin from (x,y)
	//change k/v points to v
	rep(i,0,n)rep(j,0,m)b[i][j]=0;
	sum=k/v;//k/v<=cnt[rt]
	flood(x,y,v);
	rep(i,0,n)rep(j,0,m)
		printf("%d%c",b[i][j]," \n"[j==m-1]);
}
void solve(){
	rep(i,0,tot){
		fa[i]=i;
		cnt[i]=1;
	}
	rep(i,0,tot){
		int x=p[i].fi,y=p[i].se,v=a[x][y];
		int t=combine(x,y,v);
		if(k%v==0&&cnt[t]>=k/v){
			puts("YES");
			print(x,y,v);
			return;
		}
	}
	puts("NO");
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	input();
	solve();
	return 0;
}
