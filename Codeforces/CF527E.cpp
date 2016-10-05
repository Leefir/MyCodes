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

const int N=100000;
const int M=500000;
pii edge[M+5];
int n,m;
vi g[N+5];
int head[N+5];
int d[N+5];
void input(){
	scanf("%d %d",&n,&m);
	rep(i,1,n+1)d[i]=0;
	rep(i,0,m){
		int u,v;
		scanf("%d %d",&u,&v);
		edge[i]=pii(u,v);
		d[u]++;d[v]++;
	}
	int x=-1;
	rep(i,1,n+1)if(d[i]&1){
		if(x==-1)x=i;
		else{
			edge[m++]=pii(x,i);
			x=-1;
		}
	}
	if(m&1)edge[m++]=pii(1,1);//self loop
	
	//build graph
	rep(i,1,n+1)g[i].clear();
	rep(i,0,m){
		g[edge[i].fi].pb(i);
		g[edge[i].se].pb(i);
	}
}
bool mark[M+5];
int seq[M+5];
int tot;
void dfs(int u){
//	printf("visit %d\n",u);
	for(int &i=head[u];i<sz(g[u]);++i){
		int id=g[u][i];
		if(mark[id])continue;
		mark[id]=true;
		int v=edge[id].fi^edge[id].se^u;
		dfs(v);
	}
	seq[tot++]=u;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	input();
	printf("%d\n",m);
	rep(i,1,n+1)head[i]=d[i]=0;
	rep(i,0,m)mark[i]=false;
	tot=0;
	dfs(1);
	bool f=false;
	rep(i,0,tot-1){
		if(f)printf("%d %d\n",seq[i],seq[i+1]);
		else printf("%d %d\n",seq[i+1],seq[i]);
		f^=1;
	}
	return 0;
}
