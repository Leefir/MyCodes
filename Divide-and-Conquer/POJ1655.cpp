#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
namespace Program{

const int N = 20000;

int n;
vector<int> g[N + 5];
void input(){
	scanf("%d", &n);
	
	//init
	rep(i, 0, n) g[i].clear();
	
	rep(i, 0, n - 1){
		int u, v;
		scanf("%d %d", &u, &v);
		--u; --v;
		
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int sz[N + 5], mx[N + 5];

void dfs(int u, int par){
	sz[u] = 1;
	mx[u] = 0;
	
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i];
		if(v == par)continue;
		
		dfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
}

void solve(){
	dfs(0, -1);
	int u = 0;
	rep(i, 0, n){
		mx[i] = max(mx[i], n - sz[i]);
		if(mx[i] < mx[u]) u = i;
	}
	printf("%d %d\n", u + 1, mx[u]);
}

}

int main(){
	int cas; scanf("%d", &cas);
	while(cas--){
		Program::input();
		Program::solve();
	}
	
	return 0;
}
