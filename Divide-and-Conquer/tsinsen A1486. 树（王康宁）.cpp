#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i ##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = 100000;
//1≤N≤100000, 0≤K≤N, 0≤Vi≤1e9

//graph
struct Edge{
	int to, nxt;
	Edge(){}
	Edge(int _to, int _nxt): to(_to), nxt(_nxt){}
}edge[N * 2 + 5];
int Gsz, head[N + 5];

void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}

inline void addEdge(int u, int v){
	edge[Gsz] = Edge(v, head[u]);
	head[u] = Gsz++;
}

int n, k;
bool key[N + 5];
int val[N + 5];

void input(){
	scanf("%d %d", &n, &k);
	
	//key points
	rep(i, 0, n){
		int x; scanf("%d", &x);
		key[i] = x;
	}
	
	//vertices' val
	rep(i, 0, n) scanf("%d", &val[i]);
	
	//graph
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		
		addEdge(u, v);
		addEdge(v, u);
	}
	
}


//点权异或和最大
//至少K个喜欢的点(key)
int ans;
bool fbd[N + 5];

int sz[N + 5], mxsz[N + 5];
int seq[N + 5], seqtot;

void sizeDfs(int u, int par){
	sz[u] = 1; mxsz[u] = 0;
	seq[seqtot++] = u;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		sizeDfs(v, u);
		sz[u] += sz[v];
		mxsz[u] = max(mxsz[u], sz[v]);
	}
	
}

int findRoot(int u){
	
	//init
	seqtot = 0;
	sizeDfs(u, -1);
	
	rep(i, 0, seqtot){
		int v = seq[i];
		mxsz[v] = max(mxsz[v], seqtot - sz[v]);
		if(mxsz[u] > mxsz[v]) u = v;
	}
	
	return u;
}

namespace Trie{
	const int B = 30; // 2^30 = 1,073,741,824
	int ch[N * B + 5][2];
	int mx[N * B + 5];//mx[i] max number of keys among paths passing node i
	int sz, rt;
	//memory N * B * 3 = 9,000,000 ints
	
	inline int newnode(){
		++sz;
		
		ch[sz][0] = ch[sz][1] = 0;
		mx[sz] = -1;
		
		return sz;
	}
	
	
	//start from the highest bit
	
	inline void insert(int num, int keycnt){
		int u = rt;
		mx[u] = max(mx[u], keycnt);
		per(i, 0, B){
			int f = num >> i & 1;
			if(ch[u][f] == 0)ch[u][f] = newnode();
			u = ch[u][f];
			
			mx[u] = max(mx[u], keycnt);
		}
		
	}
	
	inline int query(int num, int keycnt){
		if(mx[rt] < k - keycnt) return -1;
		
		int u = rt, res = 0;
		
		per(i, 0, B){
			int f = num >> i & 1;
			if(ch[u][!f] != 0 && mx[ch[u][!f]] >= k - keycnt){
				u = ch[u][!f];
				res = res << 1 | 1;
			}else{
				u = ch[u][f];
				res = res << 1;
			}
		}
		
		return res;
	}
	
	void init(){
		sz = 0;
		rt = newnode();
	}
}

typedef pair<int, int> pii;
pii tmp[N + 5];
int tmptot;

void conquerDfs(int u, int par, int num, int keycnt){
	//by the way query on Trie and update ans!
	num ^= val[u]; keycnt += key[u];
	tmp[tmptot++] = pii(num, keycnt);
	
	ans = max(ans, Trie::query(num, keycnt));
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		conquerDfs(v, u, num, keycnt);
	}
	
}

void conquer(int u){
	Trie::init();
	Trie::insert(val[u], key[u]);

	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		tmptot = 0;
		conquerDfs(v, u, 0, 0);
		
		//include root when inserting
		rep(j, 0, tmptot){
			int num = tmp[j].first ^ val[u], keycnt = tmp[j].second + key[u];
			Trie::insert(num, keycnt);
		}
	}
	
	//paths starting from root
	ans = max(ans, Trie::query(0, 0));
}

void divide(int u){
	fbd[u] = true;
	conquer(u);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		if(sz[v] < k) continue;
		//no path with >= k keypoints exits in this subtree!
		
		divide(findRoot(v));
	}
	
}

void solve(){
	
	//init
	ans = -1;
	rep(i, 0, n) fbd[i] = false;
	
	divide(findRoot(0));
	
	printf("%d\n", ans);
//无解-1 
}

}//namespace Program

int main(){
	Program::input();
	Program::solve();
	
	return 0;
}
