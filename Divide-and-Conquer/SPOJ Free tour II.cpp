#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i ##_END_; ++i)
typedef long long ll;
const ll linf = 1LL << 60;


namespace Program{

const int N = 200000;
//  -10000 <= val <= 10000

struct Edge{
	int to, val, nxt;
	Edge(){}
	Edge(int _to, int _val, int _nxt): to(_to), val(_val), nxt(_nxt){}
}edge[N * 2 + 5];
int Gsz, head[N + 5];

void initGraph(const int n){
	Gsz = 0;
	rep(i, 0, n) head[i] = -1;
}

inline void add_edge(int u, int v, int val){
	edge[Gsz] = Edge(v, val, head[u]);
	head[u] = Gsz++;
}

int n, k, m;
bool black[N + 5];
void input(){
	scanf("%d %d %d", &n, &k, &m);
	
	rep(i, 0, n)black[i] = false;
	rep(i, 0, m){
		int u; 
		scanf("%d", &u); 
		--u;
		
		black[u] = true;
	}
	
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v, val;
		scanf("%d %d %d", &u, &v, &val);
		--u; --v;
		
		add_edge(u, v, val);
		add_edge(v, u, val);
	}
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
	tot = 0;
	sizeDfs(u, -1);
	rep(i, 0, tot){
		int v = seq[i];
		mx[v] = max(mx[v], tot - sz[v]);
		if(mx[u] > mx[v]) u = v;
	}
	return u;
}

struct node{
	int blackCnt, subTreeId;
	ll dis;
	node(){}
	node(int _b, int _s, ll _d): blackCnt(_b), subTreeId(_s), dis(_d){}
	bool operator <(const node &tmp)const{
		return blackCnt < tmp.blackCnt;
	}
}a[N + 5];
int sum;

int subTreeId;
void conquerDfs(int u, int par, int blackCnt, ll dis){
	blackCnt += black[u];
	a[sum++] = node(blackCnt, subTreeId, dis);
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		if(par == -1) subTreeId = v;
		conquerDfs(v, u, blackCnt, dis + edge[i].val);
	}
}

inline void chk_max(node &mx0, node &mx1, node x){
	if(x.dis >= mx0.dis){
		if(x.subTreeId != mx0.subTreeId) mx1 = mx0, mx0 = x;
		else mx0 = x;
	}else if(x.dis >= mx1.dis && x.subTreeId != mx0.subTreeId)
		mx1 = x;
}


void conquer(int u){
	//update ans
	sum = 0;
	subTreeId = u;
	conquerDfs(u, -1, 0, 0);
	
	sort(a, a + sum);
	
	node mx0 = a[0], mx1 = node(-1, -1, -linf);
	for(int i = 1; i < sum; ++i){
		if(a[i - 1].blackCnt + a[i] .blackCnt - black[u] <= k){
			if(mx0.subTreeId != a[i].subTreeId) ans = max(ans, mx0.dis + a[i].dis);
			else if(mx1.subTreeId != -1) ans = max(ans, mx1.dis + a[i].dis);
		}else{
				
			int l, r;
			mx0 = a[0], mx1 = node(-1, -1, -linf);
			for(l = 0, r = sum - 1; l < r && r >= i; --r){
				while(l + 1 < r && a[l + 1].blackCnt + a[r].blackCnt - black[u] <= k){
					++l;
					chk_max(mx0, mx1, a[l]);
				}
				if(l < r && a[l].blackCnt + a[r] .blackCnt - black[u] <= k){
					if(mx0.subTreeId != a[r].subTreeId) ans = max(ans, mx0.dis + a[r].dis);
					else if(mx1.subTreeId != -1) ans = max(ans, mx1.dis + a[r].dis);
				}
			}
			break;
		}
		chk_max(mx0, mx1, a[i]);
	}
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
	divide(findRoot(0));
	cout << ans << endl;
}

}//namespace Program

int main(){
	Program::input();
	Program::solve();
	return 0;
}
