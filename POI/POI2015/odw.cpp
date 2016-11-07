#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
	while(c = getchar(), c >= '0' && c <= '9');
}
void printPositive(int x){
	if(x == 0) return;
	printPositive(x / 10);
	putchar(x % 10 ^ 48);
}
inline void print(int x){
	if(x == 0) putchar('0');
	else printPositive(x);
}
const int N = 50000;
const int B = 223;
const int S = 16; //2^16 = 65536
struct Edge{
	int to, nxt;
	Edge(){}
	Edge(int _to, int _nxt){ to = _to; nxt = _nxt;}
}edge[N*2+5];
int Gsz, head[N+5];
void initGraph(const int n){
	rep(i, 0, n) head[i] = -1;
	Gsz = 0;
}
inline void addEdge(int u, int v){
	edge[Gsz] = Edge(v, head[u]);
	head[u] = Gsz++;
}
int n, val[N+5];
int b[N+5];
vector<int> vec[N+5];
int ans[N+5];
void input(){
	scanf("%d", &n);
	rep(i, 0, n) read(val[i]);
	initGraph(n);
	rep(i, 0, n-1){
		int u, v;
		read(u); read(v);
		--u; --v; //id[0, n)
		addEdge(u, v);
		addEdge(v, u);
	}
	rep(i, 0, n) read(b[i]), --b[i]; //id[0, n)
	rep(i, 1, n) vec[i].clear(); //[1, n)
	rep(i, 0, n-1){
		int c; read(c);
		vec[c].push_back(i);
	}
}
int block;
int dep[N+5], fa[N+5][S];
void dfs(int u, int par){
	if(par == -1) fa[u][0] = u; else fa[u][0] = par;
	for(int i = head[u]; ~i; i = edge[i].nxt){
		int v = edge[i].to; if(v == par) continue;
		dep[v] = dep[u] + 1; dfs(v, u);
	}
}
void prepare(){
	rep(i, 1, S) rep(j, 0, n)
		fa[j][i] = fa[fa[j][i-1]][i-1];
}
inline int goup(int u, int step){
	per(i, 0, S) if(step >>i & 1) u = fa[u][i];
	return u;
}
inline int LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int step = dep[u] - dep[v];
	u = goup(u, step);
	if(u != v){
		per(i, 0, S) if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
		u = fa[u][0];
	}
	return u;
}
int up[N+5][S], sum[N+5][S];
int k;
void prepare1(){
	rep(i, 1, S) rep(j, 0, n){
		up[j][i] = up[up[j][i-1]][i-1];
		sum[j][i] = sum[j][i-1] + sum[up[j][i-1]][i-1];
	}
}
inline int goup1(int u, int step){
	int res = 0;
	per(i, 0, S) if(step >> i & 1){
		res += sum[u][i];
		u = up[u][i];
	}//一次走k边 一共走step*k边 
	return res;
}
inline int goup2(int u, int step){
	int res = 0;
	while(step--){
		int v = goup(u, k);
		res += val[v];
		u = v;
	}
	return res;
}
inline void single(int id){
	int u = b[id], v = b[id+1];
	int lca = LCA(u, v); //u -> lca -> v
	int dis = dep[u] + dep[v] - dep[lca] * 2;
	if(dis % k == 0) ans[id] = 0;
	else ans[id] = val[v], v = goup(v, dis % k);
	ans[id] += goup2(u, (dep[u]-dep[lca]) / k) + val[u] + goup2(v, (dep[v]-dep[lca]) / k) + val[v];
	if((dep[u] - dep[lca]) % k == 0 && (dep[v] - dep[lca]) % k == 0) ans[id] -= val[lca];		
}
void solve1(){ //[1, block)
	rep(i, 0, n) up[i][0] = i;
	for(k = 1; k < block; ++k){
		rep(i, 0, n){
			up[i][0] = fa[up[i][0]][0];
			sum[i][0] = val[up[i][0]];
		}
//		if(vec[k].size() * (n / k) * S <= n *S)
		if((int)vec[k].size() <= k){
			rep(j, 0, (int)vec[k].size())
				single(vec[k][j]);
			continue;
		}
		prepare1();
		rep(j, 0, (int)vec[k].size()){
			int id = vec[k][j]; //b[id] -> b[id+1]
			int u = b[id], v = b[id+1];
			int lca = LCA(u, v); //u -> lca -> v
			int dis = dep[u] + dep[v] - dep[lca] * 2;
			if(dis % k == 0) ans[id] = 0;
			else ans[id] = val[v], v = goup(v, dis % k);
			ans[id] += goup1(u, (dep[u]-dep[lca]) / k) + val[u] + goup1(v, (dep[v]-dep[lca]) / k) + val[v];
			if((dep[u] - dep[lca]) % k == 0 && (dep[v] - dep[lca]) % k == 0) ans[id] -= val[lca];
		}
	}
}
void solve2(){ //[blcok, n)
	for(k = block; k < n; ++k)
		rep(j, 0, (int)vec[k].size())
			single(vec[k][j]);
}
void output(){
	rep(i, 0, n-1) print(ans[i]), putchar('\n');
}
void Main(){
	input();
	block = (int)sqrt(n);
	dep[0] = 0; dfs(0, -1);
	prepare();
	solve1();
	solve2();
	output();
}

} //namespace Program

int main(){
	Program::Main();
	return 0;
}
/*

*/
