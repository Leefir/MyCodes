#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <ctime>
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
template <typename Tp>inline void read(Tp &res){
    char c;res=0;
    while(c=getchar(),!isdigit(c));
    do res=(res<<1)+(res<<3)+(c^48);
    while(c=getchar(),isdigit(c));
}
template <typename Tp>void print_positive(Tp x){
    if(x==0)return;
    print_positive(x/10);
    putchar(x%10^48);
}
template <typename Tp>inline void print(Tp x){
    if(x==0)putchar('0');
    else if(x<0)putchar('-'),print_positive(-x);
    else print_positive(x);
}

const int N = (int)1e5;
const int M = (int)2e5;
const int S = 17;
//Vmax <= 1e9
int n, m;
vi g[N+5];
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		g[u].pb(v); g[v].pb(u);
	}
}

namespace P100{

int dfn, pre[N+5], post[N+5];
int fa[N+5][S], dep[N+5];
void dfs(int u, int par){
	pre[u] = ++dfn;
	fa[u][0] = par;
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	rep(i, 1, S){
		if(fa[u][i-1] == -1) fa[u][i] = -1;
		else fa[u][i] = fa[fa[u][i-1]][i-1];
	}
	rep(i, 0, sz(g[u])){
		int v = g[u][i];
		if(v == par) continue;
		dfs(v, u);
	}
	post[u] = dfn;
}
inline int LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int step = dep[u]-dep[v];
	per(i, 0, S) if(step>>i&1) u = fa[u][i];
	if(u != v){
		per(i, 0, S) if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
		u = fa[u][0];
	}
	return u;
}
struct Event{
	int id; //-1 update [0, m) query
	int du, dv, dl, dl1, val, f; //f 1/-1  
	//du, dv, dl dfn
	//updaet du+f dv+f dl-f
	//query [du, dv]
}event[M+5];
int X[M+5], Xtot; //离散 
int id[M+5], ans[M+5];
void build(){
	rep(i, 0, m){
		int f; read(f);
		if(f == 0){
			int u, v, val; read(u); read(v); read(val); --u; --v;
			X[Xtot++] = val;
			int lca = LCA(u, v);
			event[i].id = -1;
			event[i].du = pre[u];
			event[i].dv = pre[v];
			event[i].dl = pre[lca];
			if(fa[lca][0] != -1) event[i].dl1 = pre[fa[lca][0]];
			else event[i].dl1 = -1;
			event[i].val = val;
			event[i].f = 1;
//			fprintf(stderr, "val %d dl %d dl1 %d\n", event[i].val, event[i].dl, event[i].dl1);
		}else if(f == 1){
			int id; read(id); --id;
			event[i] = event[id];
			event[i].f = -1;
		}else if(f == 2){
			int u; read(u); --u;
			event[i].id = i;
			event[i].du = pre[u];
			event[i].dv = post[u];
		}else assert(false);
	}
	sort(X, X+Xtot);
	Xtot = unique(X, X+Xtot)-X;
	rep(i, 0, m) if(event[i].id == -1)
		event[i].val = lower_bound(X, X+Xtot, event[i].val)-X;
	rep(i, 0, m) id[i] = i;
}
struct BinaryIndexedTree{
	int a[N+5];
	void init(){
		rep(i, 0, n+1) a[i] = 0;
	}
	inline void update(int pos, int f){
		for(int i = pos; i <= n; i += i&-i)
			a[i] += f;
	}
	inline int query(int pos){
		int res = 0;
		for(int i = pos; i > 0; i -= i&-i)
			res += a[i];
		return res;
	}
	inline int sum(int l, int r){
		return query(r) - query(l-1);
	}
}bit;
int d[M+5]; //0 -> [vl, mid)  1 -> [mid, vr)
int tmp[M+5];
void solve(int L, int R, int vl, int vr){ //[L, R)  val[vl, vr)
	if(L == R) return; //empty
//	fprintf(stderr, "___________[%d, %d) [%d, %d)\n", L, R, vl, vr);
	int mid = (vl+vr)>>1;
	int cnt = 0, Mid = L;
	rep(i, L, R){
		Event &e = event[id[i]];
		if(e.id == -1){
			if(mid<=e.val && e.val<vr){
				cnt+=e.f;
				bit.update(e.du, e.f);
				bit.update(e.dv, e.f);
				bit.update(e.dl, -e.f);
				if(e.dl1 != -1) bit.update(e.dl1, -e.f);
				d[i] = 1;
			}else d[i] = 0, ++Mid;
		}else{ //query
			if(bit.sum(e.du, e.dv) < cnt) d[i] = 1;
			else d[i] = 0, ++Mid;
		}
	}
//	fprintf(stderr, "val[%d, %d) cnt %d\n", X[vl], X[vr], cnt);
	//clear
	rep(i, L, R){
		Event &e = event[id[i]];
		if(e.id == -1 && mid<=e.val && e.val<vr){
			bit.update(e.du, -e.f);
			bit.update(e.dv, -e.f);
			bit.update(e.dl, e.f);
			if(e.dl1 != -1) bit.update(e.dl1, e.f);
		}
	}
	if(vr-vl==1){
		rep(i, L, R){
			Event &e = event[id[i]];
			if(e.id != -1){
				if(d[i] == 1) ans[id[i]] = vl;
				else ans[id[i]] = -1;
			}
		}
	}else{
		int lp = L, rp = Mid;
		rep(i, L, R){
			if(d[i] == 0) tmp[lp++] = id[i];
			else tmp[rp++] = id[i];
		}
		rep(i, L, R) id[i] = tmp[i];
		solve(L, Mid, vl, mid);
		solve(Mid, R, mid, vr);
	}
}
void output(){
	rep(i, 0, m) if(event[i].id != -1){
		if(ans[i] == -1) puts("-1");
		else print(X[ans[i]]), putchar('\n');
	}
}
void Main(){
	dfn = 0; dfs(0, -1);
	build();
	bit.init();
	memset(ans, -1, sizeof ans);
	solve(0, m, 0, Xtot);
	output();
}

} //namespace P100

/*

*/
int main(){
	
	input();
	
    P100::Main();
    
    return 0;
}
