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

const int N = 5000;
typedef long long ll;
vector<int> g[N+5];
int n;
void input(){
	scanf("%d", &n);
	rep(i, 0, n) g[i].clear();
	rep(i, 0, n-1){
		int u, v; scanf("%d %d", &u, &v); --u; --v;
		g[u].push_back(v); g[v].push_back(u);
	}
}
ll ans;
ll cnt[2][N+5], tmp[2][N+5];
void dfs(int u, int par, int dep){
	tmp[0][dep]++;
	tmp[1][dep]+=cnt[0][dep];
	ans += cnt[1][dep];
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i];
		if(v == par) continue;
		dfs(v, u, dep+1);
	}
}
void work(int u){
	memset(cnt, 0, sizeof cnt);
	rep(i, 0, (int)g[u].size()){
		int v = g[u][i];
		memset(tmp, 0, sizeof tmp);
		dfs(v, u, 1);
		rep(j, 0, N+5){
			cnt[0][j] += tmp[0][j];
			cnt[1][j] += tmp[1][j];
		}
	}
}
void Main(){
	input();
	ans = 0;
	rep(i, 0, n) work(i);
	cout << ans << endl;
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

