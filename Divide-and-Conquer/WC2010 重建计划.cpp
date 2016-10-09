#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef double db;

inline void rd(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do{
		res = (res * 10) + (c ^ 48);
	}while(c = getchar(), c >= '0' && c <= '9');
}

namespace Program{

const int N = 100000;
const int V = (int)1e6;

//graph
struct Edge{
	int to, val, nxt;
	Edge(){}
	Edge(int _to, int _val, int _nxt): to(_to), val(_val), nxt(_nxt){}
}edge[N * 2 + 5];
int Gsz, head[N + 5];

void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}

inline void addEdge(int u, int v, int val){
	edge[Gsz] = Edge(v, val, head[u]);
	head[u] = Gsz++;
}

int n, L, U;

void input(){
	scanf("%d", &n);
	scanf("%d %d", &L, &U);
	
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v, val;
		//id [0, n)
		rd(u); rd(v); rd(val);
		--u; --v;
		
		addEdge(u, v, val);
		addEdge(v, u, val);
	}
}

db ans;
bool fbd[N + 5];

int sz[N + 5], mx[N + 5];
int seq[N + 5], seqtot;

void sizeDfs(int u, int par){
	sz[u] = 1; mx[u] = 0;
	seq[seqtot++] = u;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		sizeDfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	
}

int findRoot(int u){
	seqtot = 0;
	sizeDfs(u, -1);
	
	rep(i, 0, seqtot){
		int v = seq[i];
		mx[v] = max(mx[v], seqtot - sz[v]);
		if(mx[u] > mx[v]) u = v;
	}
	
	return u;
}

db mid;

int son[N + 5], sontot, sonval[N + 5];
bool cmp(int x, int y){
	return sz[x] < sz[y];
}

db f[N + 5];
//f[x]  max value among paths of length x

db tmp[N + 5];
int lenmx;
void conquerDfs(int u, int par, db val, int len){
	//update tmp & lenmx
	if(lenmx < len){
		lenmx = len;
		tmp[len] = val;
	}else tmp[len] = max(tmp[len], val);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		conquerDfs(v, u, val + edge[i].val - mid, len + 1);
	}
	
}

int que[N + 5];

bool chk(int u){
	//val - mid
	
	//init
	bool res = false;
	
	int mx = 0;
	
	rep(i, 0, sontot){
		int v = son[i];
		
		lenmx = 0;
		conquerDfs(v, u, sonval[v] - mid, 1);
		
		//[1, lenmx] usable
		//chk
		int l = max(L - 1, 1), r = min(mx, U - 1);
		//k satisfies L <= j + k <= U
		//originally j = 1
		
		int ql = 0, qh = 0;
		for(int i = r; i >= l; --i){
			while(qh > ql && f[que[qh - 1]] < f[i]) --qh;
			que[qh++] = i;
		}
		
		rep(j, 1, lenmx + 1){
//			if(ql < qh && L <= que[ql] + j && que[ql] + j <= U && f[que[ql]] + tmp[j] >= 0){
			if(ql < qh && f[que[ql]] + tmp[j] >= 0){
				res = true;
				break;
			}
			
			//update queue
			if(j + r == U) --r;
			while(qh > ql && que[ql] >= r) ++ql;
			if(l - 1 >= 1){
				--l;
				while(qh > ql && f[que[qh - 1]] < f[l]) --qh;
				que[qh++] = l;
			}
		}
		
		//update
		mx = max(mx, lenmx);
		rep(j, 1, lenmx + 1)
			f[j] = max(f[j], tmp[j]);
		
		if(res) break;
	}
	
	//paths starting from root
	rep(i, L, min(U, mx) + 1)
		res |= (f[i] >= 0);
	
	//clear -1e18
	rep(i, 0, mx + 1) f[i] = -1e18;
	
	return res;
}

void conquer(int u){
	
	//sort subtrees
	sontot = 0;
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		son[sontot++] = v;
		sonval[v] = edge[i].val;
	}
	sort(son, son + sontot, cmp);
	
	//binary search
	db l = ans, r = 1e6;
	while(fabs(r - l) > 1e-4){
		mid = l + (r - l) / 2;
		if(chk(u)) l = mid;
		else r = mid;
	} 
		
	ans = l; // l >= ans
}

void divide(int u){
	
	fbd[u] = true;
	conquer(u);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		if(sz[v] < L) continue;
		
		divide(findRoot(v));
	}
	
}

void solve(){
	ans = 0;
	rep(i, 0, n) fbd[i] = false;
	rep(i, 0, n + 1) f[i] = -1e18;
	
	divide(findRoot(0));
	
	printf("%.3lf\n", ans);
}

}//namespace Program

int main(){
	Program::input();
	Program::solve();
	return 0;
}
