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

const int N = 100000;
const int Q = 100000;
const int S = 17;
int n, m, q;

namespace P30{ //Trajan LCA 内存若干个500*500  Q <= 100000

const int N = 500;
const int V = N*N;
vi g[N+5];
int seq[N+5][N+5], siz[N+5];
int fa[V+5], dep[V+5];
void dfs(int u, int par){
	fa[u] = par;
	int &tot = siz[u]; tot = 0; seq[u][tot++] = u;
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	rep(i, 0, sz(g[u])){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u);
		rep(j, 0, siz[v]) seq[u][tot++] = seq[v][j];
	}
	sort(seq[u], seq[u]+tot); //可以归并 
}
int allc;
void input(){
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		g[u].pb(v); g[v].pb(u);
	}
	dfs(0, -1);
	allc = n;
	rep(i, 0, m){
		int x, to; read(x); read(to); --x; --to;
		int allcmem = allc;
		rep(j, 0, siz[x]){
			if(seq[x][j] == x) fa[allc] = to;
			else fa[allc] = allcmem + lower_bound(seq[x], seq[x]+siz[x], fa[seq[x][j]])-seq[x];
			dep[allc] = dep[to]+dep[seq[x][j]]-dep[x]+1;
			allc++;
		}
	}
}
struct Query{
	int v, qid;
	Query(){}
	Query(int _v, int _qid)
		: v(_v), qid(_qid){}
};
vector<Query> query[V+5];
int qu[Q+5], qv[Q+5], lca[Q+5];
vi son[V+5];
namespace us{
int n;
int fa[V+5];
void init(const int _n){
	n = _n;
	rep(i, 0, n) fa[i] = i;
}
int get(int u){
	if(fa[u] != u) fa[u] = get(fa[u]);
	return fa[u];
}

} //namespace us
bool vis[V+5];
void Tarjan(int u){
	vis[u] = true;
	rep(i, 0, sz(query[u])){
		int v = query[u][i].v, qid = query[u][i].qid;
		if(vis[v]) lca[qid] = us::get(v);
	}
	rep(i, 0, sz(son[u])){
		int v =son[u][i];
		Tarjan(v);
		us::fa[us::get(v)] = u;
	}
}
void Main(){
	input();
	rep(i, 0, allc) son[i].clear();
	rep(i, 1, allc) son[fa[i]].pb(i);
	rep(i, 0, allc) query[i].clear();
	rep(i, 0, q){
		read(qu[i]); read(qv[i]); --qu[i]; --qv[i];
		query[qu[i]].pb(Query(qv[i], i));
		query[qv[i]].pb(Query(qu[i], i));
	}
	us::init(allc);
	memset(vis, false, sizeof vis);
	Tarjan(0);
	rep(i, 0, q)
		printf("%d\n", dep[qu[i]] + dep[qv[i]] - dep[lca[i]]*2);
}

} //namespace P30

namespace P100{


namespace t0{

vi g[N+5];
int fa[N+5][S], dep[N+5], siz[N+5];
int dfn, pre[N+5], post[N+5], dfnseq[N+5]; //[1, n]
void dfs(int u, int par){
	++dfn; pre[u] = dfn; dfnseq[dfn] = u;
	
	fa[u][0] = par;
	if(par == -1) dep[u] = 0; else dep[u] = dep[par]+1;
	rep(i, 1, S){
		if(fa[u][i-1] == -1) fa[u][i] = -1;
		else fa[u][i] = fa[fa[u][i-1]][i-1];
	}
	
	siz[u] = 1;
	rep(i, 0, sz(g[u])){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u); siz[u] += siz[v];
	} 
	
	post[u] = dfn;
}
void input(){
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		g[u].pb(v); g[v].pb(u);
	}
	dfn = 0; dfs(0, -1);
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
inline int distance(int u, int v){
	return dep[u]+dep[v]-dep[LCA(u, v)]*2;
}

}// namespace t0

namespace ct{ //ChairmanTree


/*bruteforce version 
int seq[N+5], tot;
void dfs(int u, int par){
	seq[tot++] = u;
	rep(i, 0, sz(t0::g[u])){
		int v = t0::g[u][i];
		if(v == par) continue;
		dfs(v, u);
	}
}
int getid(int u, int rank){ //subtree(u) rank[0, siz[u])->id[0, n)
	tot = 0;
	dfs(u, t0::fa[u][0]);
	sort(seq, seq+tot);
	return seq[rank];
}
void build(){
}
*/
struct node{
	node *lch, *rch;
	int sum;
	node(){lch = rch = NULL; sum = 0;}
	inline void pushUp(){
		sum = 0;
		if(lch != NULL) sum += lch->sum;
		if(rch != NULL) sum += rch->sum;
	}
}*root[N+5];
void Build(node *&cur, int L, int R){
	cur = new node();
	if(L == R) return;
	int mid = (L+R)>>1;
	Build(cur->lch, L, mid);
	Build(cur->rch, mid+1, R);
//	cur->pushUp();
}
void insert(node *&cur, node *od, int L, int R, int pos){
	cur = new node();
	cur->lch = od->lch; cur->rch = od->rch;
	cur->sum = od->sum + 1;
	if(L == R) return;
	int mid = (L+R)>>1;
	if(pos <= mid) insert(cur->lch, od->lch, L, mid, pos);
	else insert(cur->rch, od->rch, mid+1, R, pos);
}
int query(node *lp, node *rp, int L, int R, int rank){
	if(L == R){
		assert(rp->sum - lp->sum == 1);
		return L;
	}
	int mid = (L+R)>>1;
	int tmp = rp->lch->sum - lp->lch->sum;
	if(rank < tmp) return query(lp->lch, rp->lch, L, mid, rank);
	else return query(lp->rch, rp->rch, mid+1, R, rank-tmp);
}//return [1, n] 
int getid(int u, int rank){ //return [0, n)
	return query(root[t0::pre[u]-1], root[t0::post[u]], 1, n, rank)-1;
}
void build(){
	Build(root[0], 1, n);
	rep(i, 1, t0::dfn+1) //n == t0::dfn
		insert(root[i], root[i-1], 1, n, t0::dfnseq[i]+1); //seq[i]+1 [1, n]
}

}// namespace ct

namespace t1{

int ft[N+5][S], fv[N+5], x[N+5];
int tdep[N+5];
ll dep[N+5]; //dep(treei's root)
ll sum[N+5];
void input(){
	rep(i, 0, S) ft[0][i] = -1; fv[0] = -1; x[0] = 0;
	tdep[0] = 0; dep[0] = 0;
	sum[0] = n;
	rep(i, 1, m+1){
		ll to; read(x[i]); read(to); --x[i]; --to;
		int ftid = upper_bound(sum, sum+i, to)-sum;
		int fvid = ct::getid(x[ftid], to-(ftid==0?0:sum[ftid-1]));
		ft[i][0] = ftid;
		rep(j, 1, S){
			if(ft[i][j-1] == -1) ft[i][j] = -1;
			else ft[i][j] = ft[ft[i][j-1]][j-1];
		}
		fv[i] = fvid;
		tdep[i] = tdep[ftid]+1;
		dep[i] = dep[ftid]+t0::dep[fvid]-t0::dep[x[ftid]]+1;
		sum[i] = sum[i-1] + t0::siz[x[i]];
	}
//	rep(i, 0, m+1) printf("_____________i %d ft %d fv %d dep %lld\n", i, ft[i][0], fv[i], dep[i]);
}
int TLCA(int u, int v){ //u, v are tid
	if(tdep[u] < tdep[v]) swap(u, v);
	int step = tdep[u]-tdep[v];
	per(i, 0, S) if(step>>i&1) u = ft[u][i];
	if(u != v){
		per(i, 0, S) if(ft[u][i] != ft[v][i])
			u = ft[u][i], v = ft[v][i];
		u = ft[u][0];
	}
	return u;
}
int getto(int u, int anc){ //u, anc are tid
	int step = tdep[u]-tdep[anc]-1;
	per(i, 0, S) if(step>>i&1) u = ft[u][i];
	assert(ft[u][0] == anc);
	return u;
}
ll response(ll u, ll v){
	if(u > v) swap(u, v); //u <= v  -> utid <= vtid
	int utid = upper_bound(sum, sum+m+1, u)-sum;
	int vtid = upper_bound(sum, sum+m+1, v)-sum;
//	printf("____________response u %lld v %lld x %d %lld\n", u, v, x[vtid], v-(vtid==0?0:sum[vtid-1]));
	u = ct::getid(x[utid], u-(utid==0?0:sum[utid-1]));
	v = ct::getid(x[vtid], v-(vtid==0?0:sum[vtid-1]));
	if(utid == vtid) return t0::distance(u, v);
	int tlca = TLCA(utid, vtid);
//	printf("__________tlca %d utid %d vtid %d u %lld v %lld\n", tlca, utid, vtid, u, v);
	if(utid == tlca){ //utid <= vtid
		int to = getto(vtid, tlca); //ft[to][0] = tlca
//		printf("______qdis %d v %lld\n", t0::dep[v], v);
		return t0::distance(u, fv[to]) + 1 + dep[vtid]-dep[to] + t0::dep[v]-t0::dep[x[vtid]];
	}else{
		int tou = getto(utid, tlca), tov = getto(vtid, tlca);
		return t0::distance(fv[tou], fv[tov]) + 1+dep[utid]-dep[tou]+t0::dep[u]-t0::dep[x[utid]] + 1+dep[vtid]-dep[tov]+t0::dep[v]-t0::dep[x[vtid]];
	}
	//long long
}

}// namespace t1

void Main(){
	t0::input();
	ct::build();
	t1::input();
	rep(i, 0, q){
//		if(i%10000 == 0)fprintf(stderr, "i %d %.15lf\n", i, clock()/(double)CLOCKS_PER_SEC);
		ll u, v; read(u); read(v); --u; --v;
		print(t1::response(u, v)); putchar('\n');
		//long long
	}
}

} //namespace P100

/*

*/
int main(){
	scanf("%d %d %d", &n, &m, &q);

//	P30::Main();
	P100::Main();
	
//	if(n<=500 && m<=500) P30::Main();
//	else P100::Main();
    return 0;
}
