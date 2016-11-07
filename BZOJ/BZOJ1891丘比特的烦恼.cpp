#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)

namespace Program{

const int N = 200000;
const int M = 600000;
const int inf = (int)1e9;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
	while(c = getchar(), c >= '0' && c <= '9');
}
inline int min(int x, int y){
	if(x < y) return x;
	return y;
}
namespace bpt{
	const int V = N*2;
	const int E = M;
	struct Edge{
		int to, nxt;
		Edge(){}
		Edge(int _to, int _nxt){to = _to; nxt = _nxt;}
	}edge[E+5];
	int Gsz, head[V+5];
	inline void addEdge(int u, int v){
		edge[Gsz] = Edge(v, head[u]); head[u] = Gsz++;
	}
	int n;
	void initGraph(const int _n){
		n = _n;
		rep(i, 0, n) head[i] = -1;
		Gsz = 0;
	}
	int dfsClock, dfn[V+5], low[V+5];
	int top, stk[V+5]; //sotre vertices
	int sccCnt, sccid[V+5];
	void dfs(int u){
		dfn[u] = low[u] = ++dfsClock;
		stk[++top] = u;
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			if(dfn[v] == -1){
				dfs(v);
				low[u] = min(low[u], low[v]);
			}else if(sccid[v] == -1)
				low[u] = min(low[u], dfn[v]);
		}
		if(dfn[u] == low[u]){
			while(true){
				int x = stk[top--];
				sccid[x] = sccCnt;
				if(x == u) break;
			}
			++sccCnt;
		}
	}
	void Tarjan(){ //scc
		//init
		dfsClock = top = sccCnt = 0;
		rep(i, 0, n) dfn[i] = sccid[i] = -1;
		
		rep(i, 0, n) if(dfn[i] == -1)
			dfs(i);
	}
}
int n, m;
pair<int, int> edge[M+5];
namespace hk{
	const int V = N*2;
	const int E = M;
	struct Edge{
		int to, nxt;
		Edge(){}
		Edge(int _to, int _nxt){to = _to; nxt = _nxt;}
	}edge[E+5];
	int Gsz, head[V+5];
	inline void addEdge(int u, int v){
		edge[Gsz] = Edge(v, head[u]); head[u] = Gsz++;
	}
	int n;
	void initGraph(const int _n){
		n = _n;
		rep(i, 0, n*2) head[i] = -1;
		Gsz = 0;
	}
	int mate[V+5];
	int que[V+5], dist[V+5];
	bool bfs(){
		rep(i, 0, n*2) dist[i] = inf;
		int L = 0, H = 0;
		rep(i, 0, n) if(mate[i] == -1)
			dist[i] = 0, que[H++] = i;
		bool ok = false;
		while(L < H){
			int u =que[L++];
			if(u >= n) que[H++] = mate[u], dist[mate[u]] = dist[u] + 1;
			else for(int i = head[u]; ~i; i = edge[i].nxt){
				int v = edge[i].to;
				if(dist[v] == inf){
					dist[v] = dist[u] + 1;
					if(mate[v] == -1) ok = true;
					else que[H++] = v;
				}
			}
		}
		return ok;
	}
	bool find(int u){
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			if(dist[v] != dist[u] + 1) continue;
			dist[v] = inf;
			if(mate[v] == -1 || find(mate[v])){
				mate[v] = u; mate[u] = v;
				return true;
			}
		}
		return false;
	}
	void HK(){
		rep(i, 0, n*2) mate[i] = -1;
		while(bfs()) rep(i, 0, n) 
			if(mate[i] == -1) find(i);
		rep(i, 0, n*2) assert(mate[i] != -1);
	}
	void build(pair<int, int> *e){
		HK();
		bpt::initGraph(n*2);
		rep(i, 0, m){
			int u = e[i].first, v = e[i].second;
			if(mate[u] == v) bpt::addEdge(u, v);
			else bpt::addEdge(v, u);
		}
	}
}
void input(){
	scanf("%d %d", &n, &m);
	hk::initGraph(n);
	rep(i, 0, m){
		int u, v; read(u); read(v); --u; --v; //id[0, n)
		v += n;
		edge[i] = make_pair(u, v);
		hk::addEdge(u, v);
	}
}
char str[M+5];
void solve(){
	rep(i, 0, m){
		int u = edge[i].first, v = edge[i].second;
		if(bpt::sccid[u] == bpt::sccid[v]) str[i] = '0';
		else{
			if(hk::mate[v] == u) str[i] = '1';
			else str[i] = '2';
		}
	}
	str[m] = 0;
	puts(str);
}
void Main(){
	input();
	hk::build(edge);
	bpt::Tarjan();
	solve();
}
} //namespace Program
int main(){
	Program::Main();
	return 0;
}
