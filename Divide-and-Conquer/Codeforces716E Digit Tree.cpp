#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef long long ll;

namespace Program{

const int N = (int)1e5;
const int M = (int)1e9;
// M * 10 > intmx !

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

int n, mod;

void extgcd(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1; y = 0;
	}else{
		extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
}

int inverse(int a){
	ll x, y;
	
	//gcd(pow(10), mod) = 1
	extgcd(a, mod, x, y);
	x %= mod;
	if(x < 0) x += mod;
	
	return (int)x;
}

ll pow[N + 5], inv[N + 5];

void prepare(){
	inv[1] = inverse(10);
//	extgcd(10, mod, inv[1], y);
	rep(i, 2, n + 1)
		inv[i] = inv[i - 1] * inv[1] % mod;

	pow[0] = 1 % mod;
	rep(i, 1, n + 1)
		pow[i] = pow[i - 1] * 10 %mod;
}

void input(){
	scanf("%d %d", &n, &mod);
	
	//graph
	initGraph(n);
	rep(i, 0, n - 1){
		int u, v, val;
		//id [0, n)
		scanf("%d %d %d", &u, &v, &val);
		
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

int tmp[N + 5], tmptot;

map<int, int> mp;

void conquerDfs(int u, int par, int dep, ll num_, ll _num){
	// watch out! M * 10 > intmx!
	mp[_num]++;
	
	ll x = (-num_) * inv[dep] % mod;
	if(x < 0) x += mod;
	tmp[tmptot++] = x;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(v == par || fbd[v]) continue;
		
		int val = edge[i].val;
		conquerDfs(v, u, dep + 1, (num_ * 10 + val) % mod, (_num + val * pow[dep]) % mod);
	}
	
}

ll calc(int u, int dep, ll num){
	mp.clear();
	tmptot = 0;
	
	conquerDfs(u, -1, dep, num, num);
	
	ll res = 0;
	
	rep(i, 0, tmptot){
		ll _num = tmp[i];
		res += mp[_num];
	}
	
	return res;
}

void conquer(int u){
	
	ans += calc(u, 0, 0) - 1;
	
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to;
		if(fbd[v]) continue;
		
		ans -= calc(v, 1, edge[i].val % mod);
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
	
	//divide and conquer!
	rep(i, 0, n) fbd[i] = false;
	divide(findRoot(0));
	
	cout << ans << endl;
}

}//namespace Program

int main(){
	Program::input();
	Program::prepare();
	Program::solve();
	return 0;
}
