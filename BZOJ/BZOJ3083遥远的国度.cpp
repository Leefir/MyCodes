#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef unsigned int ui;

namespace Program{

const int N = 100000;
template<typename tp>
inline void read(tp &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
void printPositive(ui x){
	if(x == 0) return;
	printPositive(x/10);
	putchar(x%10^48);
}
inline void print(ui x){
	if(x == 0) putchar('0');
	else printPositive(x);
}
struct Edge{
	int to, nxt;
	Edge(){}
	Edge(const int _to, const int _nxt){to = _to; nxt = _nxt;}
}edge[N*2+5];
int Gsz, head[N+5];
inline void addEdge(int u, int v){
	edge[Gsz] = Edge(v, head[u]); head[u] = Gsz++;
}
void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}
int n, m, rt;
ui defence[N+5];
void input(){
	scanf("%d %d", &n, &m);
	initGraph(n);
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v; //id[0, n)
		addEdge(u, v); addEdge(v, u);
	}
	rep(i, 0, n) read(defence[i]);
	scanf("%d", &rt); --rt; //id[0, n)
}
int fa[N+5], dep[N+5];
int siz[N+5], son[N+5];
void sondfs(int u, int par){
	fa[u] = par; if(par == -1) dep[u] = 0; else dep[u] = 1+dep[par];
	siz[u] = 1; son[u] = -1;
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to; if(v == par) continue;
		sondfs(v, u); siz[u] += siz[v];
		if(son[u] == -1 || siz[son[u]] < siz[v]) son[u] = v;
	}
}
int top[N+5];
int dfsClock, dfin[N+5], dfout[N+5], back[N+5];
void topdfs(int u, int tp){
	top[u] = tp;
	dfin[u] = ++dfsClock; back[dfin[u]] = u;
	if(son[u] != -1) topdfs(son[u], tp);
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to; if(v == fa[u] || v == son[u]) continue;
		topdfs(v, v);
	}
	dfout[u] = dfsClock;
}
#define root 1, 1, dfsClock
#define lch (p<<1)
#define rch (p<<1|1)
#define mid ((L+R)>>1)
#define lson lch, L, mid
#define rson rch, mid+1, R
const ui fbd = (((ui)1)<<31)+1;
inline ui min(ui x, ui y){
	if(x < y) return x;
	return y;
}
struct SegmentTree{
	ui mi[N*4+5], lazy[N*4+5];
	inline void modify(int p, ui c){
		mi[p] = c; lazy[p] = c;
	}
	inline void pushDown(int p){
		if(lazy[p] != fbd){
			modify(lch, lazy[p]);
			modify(rch, lazy[p]);
			lazy[p] = fbd;
		}
	}
	void build(int p, int L, int R){
		mi[p] = lazy[p] = fbd;
		if(L == R){mi[p] = defence[back[L]]; return;}
		build(lson); build(rson);
		mi[p] = min(mi[lch], mi[rch]);
	}
	void update(int p, int L, int R, int l, int r, ui c){
		if(L == l && R == r){modify(p, c); return;}
		pushDown(p);
		if(r <= mid) update(lson, l, r, c);
		else if(mid < l) update(rson, l, r, c);
		else update(lson, l, mid, c), update(rson, mid+1, r, c);
		mi[p] = min(mi[lch], mi[rch]);
	}
	ui query(int p, int L, int R, int l, int r){
		if(L == l && R == r) return mi[p];
		pushDown(p);
		if(r <= mid) return query(lson, l, r);
		else if(mid < l) return query(rson, l, r);
		else return min(query(lson, l, mid), query(rson, mid+1, r));
	}
}sgt;
void build(){
	sondfs(0, -1); //以0为根
	dfsClock = 0; topdfs(0, 0);
	sgt.build(root);
}
inline void swap(int &x, int &y){
	x ^= y; y ^= x; x ^= y;
}
inline void update(int u, int v, ui c){
	int tu = top[u], tv = top[v];
	while(tu != tv){
		if(dep[tu] < dep[tv]) swap(u, v), swap(tu, tv);
		sgt.update(root, dfin[tu], dfin[u], c);
		u = fa[tu]; tu = top[u];
	}
	if(dep[u] > dep[v]) swap(u, v);
	sgt.update(root, dfin[u], dfin[v], c);
}
inline void response(){
	//id[0, n)
	int f; read(f);
	if(f == 1){ //把首都修改为id
		int u; read(u); --u; //id[0, n)
		rt = u;
	}else if(f == 2){ //将p1 p2路径上的所有城市的防御值修改为v
		int u, v; ui c; read(u); read(v); read(c); --u; --v; //id[0, n)
		update(u, v, c);
	}else if(f == 3){ //询问以城市id为根的子树中的最小防御值
		int u; read(u); --u; //id[0, n)
		ui ans = fbd;
		if(u == rt) ans = sgt.query(root, 1, dfsClock);
		else if(dfin[u] < dfin[rt] && dfin[rt] <= dfout[u]){
			int v;
			if(dfin[son[u]] <= dfin[rt] && dfin[rt] <= dfout[son[u]]) v = son[u]; //son[u]!=-1 
			else{
				v = rt; while(fa[top[v]] != u) v = fa[top[v]];
				v = top[v];
			}
			ans = fbd;
			if(1 <= dfin[v]-1) ans = min(ans, sgt.query(root, 1, dfin[v]-1));
			if(dfout[v]+1 <= dfsClock) ans = min(ans, sgt.query(root, dfout[v]+1, dfsClock));
		}else ans = sgt.query(root, dfin[u], dfout[u]);
		print(ans); putchar('\n');
	}else assert(false);
}
void Main(){
	input();
	build();
	while(m--) response();
}
//ui!
} //namespace Program

int main(){
	Program::Main();
	return 0;
}
/*
0<所有权值<=2^31。 要用unsigned int!!! 
*/
