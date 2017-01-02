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
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

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

namespace Program{

const int N = (int)1e5;
//vi, wi <= 1e6
int n, m, qtot;
int v[N+5], w[N+5]; //v[0, m)  w[1, n]
vector<int> g[N+5]; //g[0, n)
int dfn, pre[N+5], post[N+5], dfnseq[N*2+5];
const int S = 17; int fa[N+5][S], dep[N+5];
void dfs(int u, int par){
	pre[u] = ++dfn; dfnseq[dfn] = u;
	fa[u][0] = par;
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	rep(i, 1, S){
		if(fa[u][i-1] == -1) fa[u][i] = -1;
		else fa[u][i] = fa[fa[u][i-1]][i-1];
	}
	rep(i, 0, g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u);
	}
	post[u] = ++dfn; dfnseq[dfn] = u;
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
int c[N+5]; //c[0, n)
struct Query{
	int dl, dr, lca, t, qid;
	Query(){}
	Query(int _dl, int _dr, int _lca, int _t, int _qid)
		: dl(_dl), dr(_dr), lca(_lca), t(_t), qid(_qid){}
}query[N+5]; int qcnt;
int id[N+5], cc[N+5];
void input(){
	scanf("%d %d %d", &n, &m, &qtot);
	rep(i, 0, m) read(v[i]);
	rep(i, 1, n+1) read(w[i]);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		g[u].push_back(v); g[v].push_back(u);
	}
	dfn = 0; dfs(0, -1);
	rep(i, 0, n) read(c[i]), --c[i];
	int T = 0;
	qcnt = 0;
	rep(i, 0, qtot){
		int f, x, y; read(f); read(x); read(y); --x; --y;
		if(f == 0){
			++T;
			id[T] = x;
			cc[T] = y;
		}else{
			int lca = LCA(x, y);
			if(pre[x] > pre[y]) swap(x, y);
			if(x == lca) query[qcnt] = Query(pre[x], pre[y], -1, T, qcnt);
			else query[qcnt] = Query(post[x], pre[y], lca, T, qcnt);
			++qcnt;
		}
	}
}
int bid[N*2+5];
bool cmp(Query x, Query y){
	if(bid[x.dl] != bid[y.dl]) return bid[x.dl] < bid[y.dl];
	if(bid[x.dr] != bid[y.dr]) return bid[x.dr] < bid[y.dr];
	return (bid[x.dr]&1) ? x.t > y.t : x.t < y.t;
}
typedef long long ll;
ll sum, ans[N+5];
int cnt[N+5]; //cnt[c] 
bool in[N+5]; //in[u]
inline void inc(int c){
	sum += v[c] * (ll)w[++cnt[c]];
}
inline void dec(int c){
	sum -= v[c] * (ll)w[cnt[c]--];
//	assert(cnt[c] >= 0);
}
inline void move(int x){ //x :dfnid [1, dfn]
	int u = dfnseq[x];
	if(in[u]) in[u] = false, dec(c[u]);
	else in[u] = true, inc(c[u]);
}
inline void refresh(int t){
	int u = id[t];
	if(in[u]) dec(c[u]);
	swap(c[u], cc[t]);
	if(in[u]) inc(c[u]);
}
void solve(){
	int S = ceil(pow(n, 2.0/3));
	rep(i, 1, dfn+1) bid[i] = i/S;
	//block decomposition
	sort(query, query+qcnt, cmp);
	memset(ans, 0, sizeof ans);
	sum = 0;
	memset(cnt, 0, sizeof cnt);
	memset(in, false, sizeof in);
	int l = 0, r = -1, T = 0;
	rep(i, 0, qcnt){
		Query &q = query[i];
		while(q.dl < l) move(--l);
		while(r < q.dr) move(++r);
		while(l < q.dl) move(l++);
		while(q.dr < r) move(r--);
		while(T < q.t) refresh(++T);
		while(q.t < T) refresh(T--);
		if(q.lca != -1) inc(c[q.lca]);
		ans[q.qid] = sum;
		if(q.lca != -1) dec(c[q.lca]);
	}
}
void Main(){
	input();
	solve();
	rep(i, 0, qcnt) print(ans[i]), putchar('\n');
}

} //namespace Program


int main(){
    Program::Main();
    return 0;
}
