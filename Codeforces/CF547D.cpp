#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
int n;
pii p[N+5];
bool del[N+5];
int ans[N+5];
map<pii,int>mat;

vi g[N*2+5];
bool deg[N*2+5];
int x[N*2+5];

set<int>d[2];

void input(){
	scanf("%d",&n);
	rep(i,0,2*N)g[i].clear();
	mat.clear();
	rep(i,0,n){
		int x,y;
		scanf("%d %d",&x,&y);
		--x;--y;
		p[i]=pii(x,y);
		g[x<<1].pb(i);
		g[y<<1|1].pb(i);
		mat[p[i]]=i;
	}
}
void init(){
	d[0].clear();d[1].clear();
	rep(i,0,n)del[i]=false;
	rep(i,0,2*N){
		d[sz(g[i])&1].insert(i);
		deg[i]=sz(g[i])&1;
		x[i]=0;
	}
}
vi seq;
void euler(int u){
	while(!g[u].empty()){
		int id=g[u].back();g[u].pop_back();
		if(!del[id]){
			del[id]=true;
			int v=(p[id].fi<<1|1)^(p[id].se<<1)^u;
			euler(v);
		}
	}
	seq.pb(u);
}
void delete_edge(int id){
	del[id]=true;
	int u[]={p[id].fi<<1,p[id].se<<1|1};
	rep(i,0,2){
		int v=u[i];
		d[deg[v]].erase(v);
		deg[v]^=1;
		d[deg[v]].insert(v);
	}
}
void solve(){
	if(d[1].empty()){
		rep(i,0,N*2){
			seq.clear();
			euler(i);
			rep(j,0,sz(seq)-1){
				int x=seq[j]>>1,y=seq[j+1]>>1;
				if(seq[j]&1)swap(x,y);
				ans[mat[pii(x,y)]]=j&1;
			}
		}
	}else{
		int u=*d[1].begin();
		while(!g[u].empty()&&del[g[u].back()])g[u].pop_back();
		if(g[u].empty())return;
		
		int id=g[u].back();
		int v=(p[id].fi<<1)^(p[id].se<<1|1)^u;
		delete_edge(id);
		solve();
		int c=0;
		if(x[v]>0)c=1;
		if(c==1)x[u]--,x[v]--;
		else x[u]++,x[v]++;
//		printf("edge %d %d\n",u,v);
		ans[id]=c;
	}
}
void output(){
	rep(i,0,n)putchar(ans[i]==1?'r':'b');
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	input();
	init();
	solve();
	output();
	return 0;
}
