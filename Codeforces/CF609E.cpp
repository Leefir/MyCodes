#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
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

const int N=(int)2e5;
struct node{
	int to;
	int val;
	bool operator <(const node &tmp)const{
		return val>tmp.val;
	}
};
struct Edge{
	int u,v,val;
}edge[N+5];
int n,m;
vector<node>g[N+5];
//val long long
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v,w;scanf("%d %d %d",&u,&v,&w);
		--u;--v;
		g[u].pb((node){v,w});
		g[v].pb((node){u,w});
		edge[i]=(Edge){u,v,w};
	}
}
const int S=19;
int fa[N+5][S],mx[N+5][S],dep[N+5];
priority_queue<node>q;
bool mark[N+5];
int dis[N+5];
ll sum;
void Prim(){
	//pick 0 as source
	fa[0][0]=0;dep[0]=0;
	while(!q.empty())q.pop();
	rep(i,0,n){
		mark[i]=false;
		dis[i]=INF;
	}
	dis[0]=0;
	q.push((node){0,0});
	sum=0;
	while(!q.empty()){
		node now=q.top();q.pop();
		int u=now.to,val=now.val;
		if(mark[u])continue;
		mark[u]=true;
		
		sum+=val;
		
		rep(i,0,sz(g[u])){
			node nxt=g[u][i];
			int v=nxt.to,val=nxt.val;
			if(!mark[v]&&dis[v]>val){
				dis[v]=val;
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				mx[v][0]=val;
				q.push((node){v,dis[v]});
			}
		}
	}
}
inline int max(int x,int y){
	if(x>y)return x;
	return y;
}
void prepare(){
	rep(i,1,S)rep(j,0,n){
		fa[j][i]=fa[fa[j][i-1]][i-1];
		mx[j][i]=max(mx[j][i-1],mx[fa[j][i-1]][i-1]);
	}
}
int LCA(int u,int v){
	int res=0;
	if(dep[u]<dep[v])swap(u,v);
	//dep[u]>dep[v]
	int step=dep[u]-dep[v];
	per(i,0,S)if(step>>i&1){
		res=max(res,mx[u][i]);
		u=fa[u][i];
	}
	if(u!=v){
		per(i,0,S)if(fa[u][i]!=fa[v][i]){
			res=max(res,mx[u][i]);
			res=max(res,mx[v][i]);
			u=fa[u][i];
			v=fa[v][i];
		}
		res=max(res,mx[u][0]);
		res=max(res,mx[v][0]);
	}
	return res;
}
void solve(){
	rep(i,0,m){
		int u=edge[i].u,v=edge[i].v,val=edge[i].val;
		printf("%I64d\n",sum-LCA(u,v)+val);
	}
}
int main(){
	input();
	Prim();
	prepare();
	solve();
	return 0;
}
