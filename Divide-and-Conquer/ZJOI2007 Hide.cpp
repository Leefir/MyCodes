#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)

namespace Program{

const int N = 100000;
const int Q = 500000;

inline void read(int &res){
	//read non-negative number
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do{
		res = (res * 10) + (c ^ 48);
	}while(c = getchar(), c >= '0' && c <='9');
}

//graph
struct Edge{
	int to, nxt;
	Edge(){}
	Edge(int _to, int _nxt): to(_to), nxt(_nxt){}
}edge[N * 2 + 5];
int Gsz, head[N + 5];

inline void addEdge(int u, int v){
	edge[Gsz] = Edge(v, head[u]);
	head[u] = Gsz++;
}

void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}


int n;
int offcnt;
bool off[N + 5];

void input(){
	scanf("%d", &n);
	rep(i, 0, n) off[i] = false;
	
	initGraph(n);
	rep(i, 0, n - 1){
		//id [0, n)
		int u, v;
		read(u); read(v);
		--u; --v;
		
		addEdge(u, v);
		addEdge(v, u);
	}
}

namespace st{
	
	int dep[N + 5];
	int seq[N * 2 + 5], seqtot;
	int pos[N + 5];
	
	inline int min(int x, int y){
		if(dep[x] < dep[y]) return x;
		return y;
	}
	
	void dfs(int u, int par){
		pos[u] = seqtot;
		seq[seqtot++] = u;
		
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			
			if(v == par) continue;
			
			dep[v] = dep[u] + 1;
			dfs(v, u);
			
			seq[seqtot++] = u;
		}
		
	}
	
	const int S = 18;
	int lg[N * 2 + 5];
	int mi[N * 2 + 5][S];
	
	void build(){
		seqtot = 0;
		dep[0] = 0;
		dfs(0, -1);
		
		lg[1] = 0;
		rep(i, 2, seqtot + 1) lg[i] = lg[i >> 1] + 1;
		
		rep(i, 0, seqtot) mi[i][0] = seq[i];
		
		rep(i, 1, S) for(int j = 0; j + (1 << i) <= seqtot; ++j)
			mi[j][i] = min(mi[j][i - 1], mi[j + (1 << i - 1)][i - 1]);
	}
	
	inline void swap(int &x, int &y){
		x ^= y; y ^= x; x ^= y;
	}
	
	inline int LCA(int u, int v){
		int l = pos[u], r = pos[v];
		if(l > r) swap(l, r);
		
		int k = lg[r - l + 1];
		return min(mi[l][k], mi[r - (1 << k) + 1][k]);
	}
	
	inline int dis(int u, int v){
		return dep[u] + dep[v] - dep[LCA(u,v)] * 2;
	}
}

struct PQ{
	priority_queue<int> que, del;
	
	inline void clear(){
		while(!que.empty()) que.pop();
		while(!del.empty()) del.pop();
	}
	
	inline void insert(int x){
		que.push(x);
	}
	
	inline void erase(int x){
		del.push(x);
	}
	
	inline int top(){
		while(!que.empty() && !del.empty() && que.top() == del.top()){
			que.pop();
			del.pop();
		}
		
		if(que.empty()) return 0;
		return que.top();
	}
	
	inline int size(){
		return que.size() - del.size();
	}
	
	inline bool empty(){
		return que.size() == del.size();
	}
	
	inline void pop(){
		while(!que.empty() && !del.empty() && que.top() == del.top()){
			que.pop();
			del.pop();
		}
		
		que.pop();
	}
	
	inline int top2(){
	
		int tmp = top(); pop();
		int res = top(); insert(tmp);
		
		return res;
	}
	
}all, part[N + 5], road[N + 5];

namespace dt{
	int fa[N + 5];
	int rt;
	
	bool fbd[N + 5];
	
	int sz[N + 5], szmx[N + 5];
	int seq[N + 5], seqtot;
	
	void sizeDfs(int u, int par){
		sz[u] = 1; szmx[u] = 0;
		seq[seqtot++] = u;
		
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			
			if(v == par || fbd[v]) continue;
			
			sizeDfs(v, u);
			sz[u] += sz[v];
			szmx[u] = max(szmx[u], sz[v]);
		}
		
	}
	
	int findRoot(int u){
		seqtot = 0;
		
		sizeDfs(u, -1);
		
		rep(i, 0, seqtot){
			int v = seq[i];
			szmx[v] = max(szmx[v], seqtot - sz[v]);
			if(szmx[u] > szmx[v]) u = v;
		}
		
		return u;
	}
	
	void divide(int u){
		fbd[u] = true;
		
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			
			if(fbd[v]) continue;
			
			int to = findRoot(v);
			fa[to] = u;
			divide(to);
			
		}
		
	}
	
	void build(){
		//init
		all.clear();
		rep(i, 0, n){
			part[i].clear();
			road[i].clear();
			fbd[i] = false;
		}
		
		rt = findRoot(0);
		
		fa[rt] = -1;
		divide(rt);
		
	}
	
	void remove(int u){
		for(int v = u; v != -1; v = fa[v]) if(part[v].size() >= 2)
			all.erase(part[v].top() + part[v].top2());
		for(int v = u; fa[v] != -1; v = fa[v]) if(!road[v].empty()) part[fa[v]].erase(road[v].top());// + st::dis(v, fa[v]));
	}
	
	void maintain(int u){
		for(int v = u; fa[v] != -1; v = fa[v]) if(!road[v].empty()) part[fa[v]].insert(road[v].top());// + st::dis(v, fa[v]));
		for(int v = u; v != -1; v = fa[v]) if(part[v].size() >= 2)
			all.insert(part[v].top() + part[v].top2());
	}
	
	void turnOn(int u){
	
		remove(u);
		off[u] = false;
		--offcnt;
		
		part[u].erase(0);
		for(int v = u; fa[v] != -1; v = fa[v]) road[v].erase(st::dis(u, fa[v]));
		maintain(u);
	}
	
	void turnOff(int u){
	
		remove(u);
		off[u] = true;
		++offcnt;
		
		part[u].insert(0);
		for(int v = u; fa[v] != -1; v = fa[v]) road[v].insert(st::dis(u, fa[v]));
		maintain(u);
	}
}//namespace dt


void build(){
	st::build();
	dt::build();
	
	offcnt = 0;
	rep(i, 0, n)dt::turnOff(i);
	//在起初的时候，所有的灯都没有被打开
	
}

char str[10];

void solve(){
	int q;
	scanf("%d", &q);
	
	while(q--){
		scanf("%s", str);
		if(str[0] == 'C'){
			//change
			
			int id; read(id); --id;
			if(off[id]) dt::turnOn(id);	
			else dt::turnOff(id);
			
		}else if(str[0] == 'G'){
			//game
			
			if(offcnt == 0)	puts("-1");
			else printf("%d\n", all.top());
			
	//若只有一个房间是关着灯的，输出0
	//若所有房间的灯都开着，输出-1。
	
		}else assert(false);
	}
	
}

}//namespace Program

int main(){
	Program::input();
	Program::build();
	Program::solve();
	
	return 0;
}
