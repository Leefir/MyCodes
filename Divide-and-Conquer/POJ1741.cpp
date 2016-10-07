#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)


namespace Program{

const int N = 10000;

int n, k;
typedef pair<int,int> pii;
vector<pii>g[N + 5];

bool input(){
	scanf("%d %d", &n, &k);
	if(n == 0 && k == 0) return false;
	
	rep(i, 0, n) g[i].clear();
	
	rep(i, 0, n - 1){
		int u, v, val;
		scanf("%d %d %d", &u, &v, &val);
		--u; --v;
		
		g[u].push_back(pii(v, val));
		g[v].push_back(pii(u, val));
	}
	
	return true;
}

int ans;
bool fbd[N + 5];

int seq[N + 5], tot;
int sz[N + 5], mx[N + 5];
void sizeDfs(int u, int par){
	sz[u] = 1; mx[u] = 0;
	
	seq[tot++] = u;
	
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i].first;
		if(v == par || fbd[v])continue;
		
		sizeDfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	
}

int findRoot(int u){
	tot = 0;
	sizeDfs(u, -1);
	for(int i = 0; i < tot; ++i){
		int v = seq[i];
		mx[v] = max(mx[v], tot - sz[v]);
		if(mx[u] > mx[v]) u = v;
	}
	return u;
}

int a[N + 5], sum;

void conquerDfs(int u, int par, int dis){
	a[sum++] = dis;
	
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i].first;
		if(v == par || fbd[v]) continue;
		
		conquerDfs(v, u, dis + g[u][i].second);
	}
	
}

int calc(int u, int dis){
	sum = 0;
	conquerDfs(u, -1, dis);
	
	sort(a, a + sum);
	int l = 0, r = sum - 1;
	
	int res = 0;
	while(l < r){
		if(a[l] + a[r] <= k){ res += r - l; ++l;}
		else --r;
	}
	
	return res;
}

void divide(int u){
	
	fbd[u] = true;
	ans += calc(u, 0);
	
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i].first;
		if(!fbd[v]){
			ans -= calc(v, g[u][i].second);
			divide(findRoot(v));
		}
	}
	
}

void solve(){
	rep(i, 0, n) fbd[i] = false;
	
	ans = 0;
	divide(findRoot(0));
	
	printf("%d\n", ans);
}

}//namespace Progarm

int main(){
	while(Program::input())
		Program::solve();
	return 0;
}
