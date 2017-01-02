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

namespace Program{

const int N = 50000;
const int M = 100000;
const int Q = 50000;
int n, m, qc;
struct Data{
	int u, v, a, b;
	Data(){}
	void input(){
		read(u); read(v); --u; --v;
		read(a); read(b);
	}
}edge[M+5], query[Q+5];
bool cmpe(Data x, Data y){return x.a < y.a;}
bool cmpeb(int x, int y){return edge[x].b < edge[y].b;}
bool cmpqb(int x, int y){return query[x].b < query[y].b;}
int ans[Q+5];
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 0, m) edge[i].input();
	scanf("%d", &qc);
	rep(i, 0, qc) query[i].input();
}
int e[M+5], q[Q+5];
int fa[N+5], mxa[N+5], mxb[N+5], rank[N+5];
bool mem;
int mid[N], ma[N], mb[N], mr[N], mt;
void rem(int x){
	++mt;
	mid[mt] = x;
	ma[mt] = mxa[x];
	mb[mt] = mxb[x];
	mr[mt] = rank[x];
}
inline int get(int u){
	while(fa[u] != u) u = fa[u];
	return u;
}
void unite(Data &e){
	int u = get(e.u), v = get(e.v);
	if(rank[u] < rank[v]) swap(u, v);
	if(mem) rem(u), rem(v);
	fa[v] = u;
	mxa[u] = max(mxa[u], max(mxa[v], e.a));
	mxb[u] = max(mxb[u], max(mxb[v], e.b));
	if(rank[u] == rank[v]) ++rank[u];
}
void mback(){
	while(mt){
		int x = mid[mt];
		fa[x] = x;
		mxa[x] = ma[mt];
		mxb[x] = mb[mt];
		rank[x] = mr[mt];
		--mt;
	}
}
void solve(){
//	int S = sqrt(M)+1;
//	int S = n/sqrt(n)/(log(n)/log(2))+1;
	int S = sqrt(n*log(n)/log(2))+1;
	sort(edge, edge+m, cmpe);
	memset(ans, 0, sizeof ans);
	mem = false;
	rep(i, 0, m) e[i] = i;
	for(int i = 0; i < m; i += S){
		int qt = 0;
		rep(j, 0, qc) if(query[j].a >= edge[i].a && (i+S>=m || query[j].a < edge[i+S].a)) q[qt++] = j;
		if(!qt) continue;
		sort(e, e+i, cmpeb); //[0, i) [i, i+S)
		sort(q, q+qt, cmpqb);
		rep(j, 0, n) fa[j] = j, mxa[j] = mxb[j] = -1, rank[j] = 0;
		for(int j = 0, cur = 0; j < qt; ++j){
			while(cur<i && edge[e[cur]].b <= query[q[j]].b) 
				unite(edge[e[cur++]]);
			mt = 0; mem = true;
			rep(k, i, min(i+S, m)) if(edge[k].a <= query[q[j]].a && edge[k].b <= query[q[j]].b)
				unite(edge[k]);
			int u = get(query[q[j]].u), v = get(query[q[j]].v);
			if(u == v && mxa[u] == query[q[j]].a && mxb[u] == query[q[j]].b) ans[q[j]] = 1;
			mback(); mem = false;
		}
	}
}

void Main(){
	input();
	solve();
	rep(i, 0, qc){
		if(ans[i] == 0) puts("No");
		else puts("Yes");
	}
}

} //namespace Program
/*

*/
int main(){
	Program::Main();
    return 0;
}
