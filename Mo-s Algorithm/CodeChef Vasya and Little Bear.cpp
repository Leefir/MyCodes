#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)
 
namespace Program{
 
const int N = (int)1e5;
const int Q = (int)1e4;
int n;
int c[N+5], h[N+5];
vector<int> g[N+5];
void input(){
	scanf("%d", &n);
	rep(i, 0, n) scanf("%d", &c[i]);
	rep(i, 0, n) scanf("%d", &h[i]);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; scanf("%d %d", &u, &v); --u; --v;
		g[u].push_back(v); g[v].push_back(u);
	}
}
const int S = 17; int fa[N+5][S], dep[N+5];
int dfn, pre[N+5], post[N+5], seq[N*2+5];
void dfs(int u, int par){
	pre[u] = ++dfn; seq[dfn] = u;
	fa[u][0] = par; 
	rep(i, 1, S){
		if(fa[u][i-1] == -1) fa[u][i] = -1;
		else fa[u][i] = fa[fa[u][i-1]][i-1];
	}
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u);
	}
	post[u] = ++dfn; seq[dfn] = u;
}
int LCA(int u, int v){
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
int q;
struct Query{
	int l, r, lid, lca, qid;
	Query(){}
	bool operator <(const Query tmp)const{
		if(lid != tmp.lid) return lid < tmp.lid;
		return r < tmp.r;
	}
}query[Q+5];
void build(){
	dfn = 0; dfs(0, -1);
	scanf("%d", &q);
	rep(i, 0, q){
		int u, v; scanf("%d %d", &u, &v); --u; --v;
		if(pre[u] > pre[v]) swap(u, v);
		int &lca = query[i].lca; lca = LCA(u, v);
		int &l = query[i].l, &r = query[i].r;
		if(u == lca) l = pre[u], r = pre[v];
		else l = post[u], r = pre[v];
		query[i].lid = l/320;
		query[i].qid = i;
	}
}
typedef long long ll;
deque<int> que[11];
ll sum[11];
ll ans[Q+5];
bool mark[N+5];
#define mul(x) (x)*(ll)(x)
void lmove(int u){
	int x = c[u], y = h[u];
	if(mark[u]){
		mark[u] = false;
		que[x].pop_front();
		if(!que[x].empty()) sum[x] -= mul(que[x].front()-y);
	}else{
		mark[u] = true;
		if(!que[x].empty()) sum[x] += mul(que[x].front()-y);
		que[x].push_front(y);
	}
}
void rmove(int u){
	int x = c[u], y = h[u];
	if(mark[u]){
		mark[u] = false;
		que[x].pop_back();
		if(!que[x].empty()) sum[x] -= mul(que[x].back()-y);
	}else{
		mark[u] = true;
		if(!que[x].empty()) sum[x] += mul(que[x].back()-y);
		que[x].push_back(y);
	}
}
void solve(){
	sort(query, query+q);
	rep(i, 0, 11) que[i].clear();
	memset(sum, 0, sizeof sum);
	memset(mark, false, sizeof mark);
	int l = 1, r = 0;
	rep(i, 0, q){
		while(query[i].l < l) lmove(seq[--l]);
		while(l < query[i].l) lmove(seq[l++]);
		while(r < query[i].r) rmove(seq[++r]);
		while(query[i].r < r) rmove(seq[r--]);
		int id = query[i].qid;
		ans[id] = 0;
		rep(j, 0, 11) if(j != c[query[i].lca]) ans[id] += sum[j];
	}
	rep(i, 0, q) printf("%lld\n", ans[i]);
}
void Main(){
	input();
	build();
	solve();
}
 
} //namespace Program
 
/*
 
*/
int main(){
	Program::Main();
	return 0;
}
