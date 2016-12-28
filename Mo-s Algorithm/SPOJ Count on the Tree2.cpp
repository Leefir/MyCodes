#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = 40000;
const int M = 100000;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
void printPositive(int x){
	if(x == 0) return;
	printPositive(x / 10);
	putchar(x %10 ^ 48);
}
inline void print(int x){
	if(x == 0) putchar('0');
	else printPositive(x);
}
int n, m;
int w[N+5], x[N+5];
int head[N+5], nxt[N*2+5], to[N*2+5], Gsz;
inline void addEdge(int u, int v){
	to[Gsz] = v; nxt[Gsz] = head[u]; head[u] = Gsz++;
}
struct Query{
	int u, v, lca, qid;
	int l, r, lid;
	Query(){}
	bool operator <(const Query tmp)const{
		if(lid != tmp.lid) return lid < tmp.lid;
		return (r < tmp.r)^(lid&1);
	}
}q[M+5];
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 0, n) read(w[i]), x[i] = w[i];
	sort(x, x+n); int k = unique(x, x+n)-x;
	rep(i, 0, n) w[i] = lower_bound(x, x+k, w[i])-x;
	
	rep(i, 0, n) head[i] = -1; Gsz = 0;
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		addEdge(u, v); addEdge(v, u);
	}
	
	rep(i, 0, m){
		read(q[i].u); read(q[i].v);
		--q[i].u; --q[i].v;
		q[i].qid = i;
	}
}
int dfn, pre[N+5], post[N+5], seq[N*2+5];
const int F = 16; int fa[N+5][F], dep[N+5];
void dfs(int u, int par){
	pre[u] = ++dfn; seq[dfn] = u;
	fa[u][0] = par;
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	for(int i = head[u]; ~i; i = nxt[i]){
		int v = to[i]; if(v == par) continue;
		dfs(v, u);
	}
	post[u] = ++dfn; seq[dfn] = u;
}
inline int LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int step = dep[u]-dep[v];
	per(i, 0, F) if(step>>i&1) u = fa[u][i];
	if(u != v){
		per(i, 0, F) if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
		u = fa[u][0];
	}
	return u;
}
void prepare(){
	rep(i, 1, F) rep(j, 0, n){
		if(fa[j][i-1] == -1) fa[j][i] = -1;
		else fa[j][i] = fa[fa[j][i-1]][i-1];
	}
	rep(i, 0, m){
		int u = q[i].u, v = q[i].v, &lca = q[i].lca;
		lca = LCA(u, v);
		if(pre[u] > pre[v]) swap(u, v);
		if(lca == u) q[i].l = pre[u], q[i].r = pre[v], lca = -1;
		else q[i].l = post[u], q[i].r = pre[v];
		q[i].lid = q[i].l/200;
	}
}
int ans[N+5];
int cnt[N+5], sum;
int mark[N+5];
inline void add(int val, int flag){
	if(flag == 1){
		if(cnt[val] == 0) sum++;
		cnt[val]++;
	}else if(flag == -1){
		if(cnt[val] == 1) sum--;
		--cnt[val];
	}else assert(false);
}
inline void move(int pos, int flag){
	int u = seq[pos];
	if(flag == 1){
		if(mark[u] == 0) add(w[u], 1);
		else if(mark[u] == 1) add(w[u], -1);
		mark[u]++;
	}else if(flag == -1){
		if(mark[u] == 2) add(w[u], 1);
		else if(mark[u] == 1) add(w[u], -1);
		mark[u]--;
	}else assert(false);
}
void solve(){
	sort(q, q+m);
	int l = 1, r = 0;
	sum = 0; memset(cnt, 0, sizeof cnt);
	memset(mark, 0, sizeof mark);
	rep(i, 0, m){
		while(l < q[i].l) move(l++, -1);
		while(q[i].l < l) move(--l, 1);
		while(r < q[i].r) move(++r, 1);
		while(q[i].r < r) move(r--, -1);
		ans[q[i].qid] = sum + (q[i].lca!=-1 && cnt[w[q[i].lca]]==0);
	}
}
void Main(){
	input();
	dfn = 0; dfs(0, -1);
	prepare();
	solve();
	rep(i, 0, m) print(ans[i]), putchar('\n');
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

