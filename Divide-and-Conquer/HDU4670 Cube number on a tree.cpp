#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef long long ll;

namespace Program{

const int N = 50000;
const int K = 30;

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
ll prime[K + 1];
int cnt[N + 5][K + 1];

#define hash adsnpohvapoughakslghapsdiufh
ll hash(int cnt[K + 1]){
	ll res = 0;
	
	rep(i, 0, k)
		res = (res * 3) + (cnt[i] % 3);
	
	return res;
}

bool input(){
	if(scanf("%d", &n) == EOF) return false;
	
	//primes
	scanf("%d", &k);
	rep(i, 0, k) scanf("%lld", &prime[i]);
	
	//vertices' val
	rep(i, 0, n){
		ll v; scanf("%lld", &v);
		rep(j, 0, k){
			cnt[i][j] = 0;
			while(v % prime[j] == 0){
				v /= prime[j];
				++cnt[i][j];
			}
		}
	}
	
	//graph
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		
		addEdge(u, v);
		addEdge(v, u);
	}
	
	return true;
}

ll ans;
bool fbd[N + 5];

int sz[N + 5], mx[N + 5];
int seq[N + 5], tot;
void sizeDfs(int u, int par){
	sz[u] = 1; mx[u] = 0;
	seq[tot++] = u;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		sizeDfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	
}

int findRoot(int u){
	//init
	tot = 0;
	
	sizeDfs(u, -1);
	
	rep(i, 0, tot){
		int v = seq[i];
		mx[v] = max(mx[v], tot - sz[v]);
		if(mx[u] > mx[v]) u = v;
	}
	
	return u;
}

multiset<ll> st;

int tmp[N + 1][K + 1], emp[K + 1];

ll need(int a[K + 1], int b[K + 1]){
	
	ll res = 0;
	
	rep(i, 0, k){
		int x = (3 - (a[i] + b[i])) % 3;
		if(x < 0) x += 3;
		res = res * 3 + x;
	}
	
	return res;
}

void conquerDfs(int u, int par){
	seq[tot++] = u;
	rep(i, 0, k) tmp[u][i] = tmp[par][i] + cnt[u][i];
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		conquerDfs(v, u);
	}
	
}

void conquer(int u){
	st.clear();
	
	memset(tmp[u], 0, sizeof tmp[u]);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		tot = 0;
		conquerDfs(v, u);
		rep(j, 0, tot){
			int x = seq[j];
			//path going through root
			ans += st.count(need(tmp[x], cnt[u]));
		}
		rep(j, 0, tot){
			int x = seq[j];
			st.insert(hash(tmp[x]));
		}
	}
	
	//path starting from root
	st.insert(hash(cnt[u]));
	ans += st.count(need(cnt[u], emp));
}

void divide(int u){
	fbd[u] = true;
	conquer(u);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		divide(findRoot(v));
	}
	
}

void solve(){
	ans = 0;
	rep(i, 0, n) fbd[i] = false;
	memset(emp, 0, sizeof emp);
	divide(findRoot(0));
	cout << ans << endl;
}

}//namespace Program

int main(){
	while(Program::input())
		Program::solve();
	
	return 0;
}
