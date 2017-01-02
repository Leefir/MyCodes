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

const int N = 1000;
int n, B;
vector<int> g[N+5];
int id[N+5], rt[N+5], tot;
void input(){
	scanf("%d %d", &n, &B);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; scanf("%d %d", &u, &v); --u; --v;
		g[u].push_back(v); g[v].push_back(u);
	}
}
void output(){
	printf("%d\n", tot);
	rep(i, 0, n) printf("%d%c", id[i], " \n"[i==n-1]);
	rep(i, 1, tot+1) printf("%d%c", rt[i]+1, " \n"[i==tot]);
}
int stk[N+5], top;
void dfs(int u, int par){
	stk[++top] = u;
	int mem = top;
	rep(i, 0, g[u].size()){
		int v = g[u][i]; if(v == par) continue;
		dfs(v, u);
		if(top - mem >= B){
			++tot; rt[tot] = u;
			while(top != mem)
				id[stk[top--]] = tot;
		}
	}
}
void solve(){
	tot = 0;
	top = 0; dfs(0, -1);
	while(top) id[stk[top--]] = tot;
	rt[tot] = 0;
	//last
}
void Main(){
	input();
	solve();
	output();
}

} //namespace Program

/*

*/
int main(){
    Program::Main();
    return 0;
}
