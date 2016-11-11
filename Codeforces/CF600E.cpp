#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)

namespace Program{

const int N = (int)1e5;
typedef long long ll;
vector<int> g[N+5];
int n, color[N+5];
void input(){
	scanf("%d", &n);
	rep(i, 0, n) scanf("%d", &color[i]);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; scanf("%d %d", &u, &v); --u; --v; //id[0, n)
		g[u].push_back(v); g[v].push_back(u);
	}
}
ll ans[N+5];
int siz[N+5], son[N+5];
void sizdfs(int u, int par){
	siz[u] = 1; son[u] = -1;
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		sizdfs(v, u); siz[u] += siz[v];
		if(son[u] == -1 || siz[son[u]] < siz[v]) son[u] = v;
	}
}
void output(){
	rep(i, 0, n) cout << ans[i] << ' ';
}
int cnt[N+5];
ll sum; int mx;
void modify(int u){
	++cnt[color[u]];
	if(cnt[color[u]] > mx){
		sum = color[u]; mx = cnt[color[u]];
	}else if(cnt[color[u]] == mx)
		sum += color[u];
}
void add(int u, int par){
	modify(u);
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		add(v, u);
	}
}
void minus(int u, int par){
	--cnt[color[u]];
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		minus(v, u);
	}
}
void dfs(int u, int par, bool keep){
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par || v == son[u]) continue;
		dfs(v, u, false);
	}
	if(son[u] != -1) dfs(son[u], u, true);
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i]; if(v == par || v == son[u]) continue;
		add(v, u);
	}
	modify(u);
	ans[u] = sum;
	if(keep == false) minus(u, par), sum = 0, mx = -1;
}
void Main(){
	input();
	sizdfs(0, -1); //with root in vertex 1
	memset(cnt, 0, sizeof cnt);
	sum = 0; mx = -1;
	dfs(0, -1, true);
	output();
}

} //namespace Program

int main(){
	Program::Main();
	return 0;
}

/*

*/
