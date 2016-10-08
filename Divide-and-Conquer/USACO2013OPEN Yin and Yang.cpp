#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef long long ll;
namespace Program{

const int N = (int)1e5;


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


int n;

inline void rd(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do{
		res = (res * 10) + (c ^ 48);
	}while(c = getchar(), c >= '0' && c <= '9');
}

void input(){
	scanf("%d", &n);
	
	//graph
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v, val;
		rd(u); rd(v); rd(val);
		--u; --v;
		if(val == 0) val = -1;
		
		addEdge(u, v, val);
		addEdge(v, u, val);
	}
	
}

ll ans;
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

//array
int fullcnt[N * 2 + 5], halfcnt[N * 2 + 5];
int cnt[N * 2 + 5];
int clr[N + 5], clrtot;
int fulltmp[N + 5], fulltmptot;
int halftmp[N + 5], halftmptot;


void donate(){
	//extra special condition: choose root as rest point
	
	rep(j, 0, halftmptot){
		int val = halftmp[j];
		//val + need = N * 2
		if(val == N) ans += fullcnt[N] + halfcnt[N];
		else ans += fullcnt[N * 2 - val];
	}
	
	rep(j, 0, fulltmptot){
		int val = fulltmp[j];
		if(val == N) ans += fullcnt[N] + halfcnt[N] + 1;
		else ans += halfcnt[N * 2 - val] + fullcnt[N * 2 - val];
	}
		
}

void update(){
	rep(j, 0, halftmptot){
		int val = halftmp[j];
		halfcnt[val]++;
		clr[clrtot++] = val;
	}
	
	rep(j, 0, fulltmptot){
		int val = fulltmp[j];
		fullcnt[val]++;
		clr[clrtot++] = val;
	}
}

void conquerDfs(int u, int par, int val){
	if(cnt[val] > 0) fulltmp[fulltmptot++] = val;
	else halftmp[halftmptot++] = val;
	
	
	++cnt[val];
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		conquerDfs(v, u, val + edge[i].val);
	}
	
	--cnt[val];
}

void conquer(int u){

	clrtot = 0;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		fulltmptot = 0;
		halftmptot = 0;
		conquerDfs(v, u, N + edge[i].val);
		
		//donate to ans
		donate();
		
		//update to array
		update();
		
	}
	
	//clear
	rep(i, 0, clrtot)
		fullcnt[clr[i]] = halfcnt[clr[i]] = 0;
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
	//init
	ans = 0;
	rep(i, 0, n) fbd[i] = false;
	
	memset(fullcnt, 0, sizeof fullcnt);
	memset(halfcnt, 0, sizeof halfcnt);
	memset(cnt, 0, sizeof cnt);
	
	divide(findRoot(0));
	
	cout << ans << endl;
}

}//namespace Program

int main(){
	Program::input();
	Program::solve();
	
	return 0;
}
