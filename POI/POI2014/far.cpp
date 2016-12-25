#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = 500000;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
#define sz(x) (int)((x).size())
#define pb(x) push_back(x)
vector<int> g[N+5];
int n, c[N+5];
void input(){
	scanf("%d", &n);
	rep(i, 0, n) read(c[i]);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; read(u); read(v); --u; --v;
		g[u].pb(v); g[v].pb(u);
	}
}
int dp[N+5], siz[N+5];
int seq[N+5], tot;
inline int max(int x, int y){
	if(x > y) return x;
	return y;
}
bool cmp(int x, int y){
//	return dp[x]-siz[x]*2 > dp[y]-siz[y]*2;
	return max(dp[x], 2*siz[x]+dp[y]) < max(dp[y], 2*siz[y]+dp[x]);
}
void dfs(int u, int par){
	siz[u] = 1;
	rep(i, 0, sz(g[u])){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u); siz[u] += siz[v];
	}
	tot = 0;
	rep(i, 0, sz(g[u])) if(g[u][i] != par) seq[tot++] = g[u][i];
	sort(seq, seq+tot, cmp);
	dp[u] = c[u]; int sum = 0;
	rep(i, 0, tot){
		int v = seq[i];
		dp[u] = max(dp[u], sum+dp[v]+1);
//		printf("update u %d v %d sum+dp[v]+1 %d\n", u+1, v+1, sum+dp[v]+1);
		sum += siz[v]*2;
	}
	dp[u] = max(dp[u], sum);
	if(u == 0) dp[u] = max(dp[u], sum+c[u]);
//	printf("dp[%d] %d siz[%d] %d\n", u+1, dp[u], u+1, siz[u]);
}
void Main(){
	input();
	dfs(0, -1);
	printf("%d\n", dp[0]);
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

