#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
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
inline int min(int x, int y){
	if(x < y) return x;
	return y;
}
inline int max(int x, int y){
	if(x > y) return x;
	return y;
}
const int N = 50;
const int M = 4000;
const int V = 500000;
const int INF = 0x7fffffff;
int n, m;
int a[M+5], b[M+5], c[M+5];
int seq[M+5], tot;
void input(){
	scanf("%d %d", &n, &m);
	tot = 0;
	rep(i, 0, m){
		read(a[i]), read(b[i]), read(c[i]);
		seq[tot++] = c[i];
	}
	sort(seq, seq+tot);
	tot = unique(seq, seq+tot) - seq;
	rep(i, 0, m) c[i] = lower_bound(seq, seq+tot, c[i]) - seq;
}
typedef pair<int, int> pii;
int dp[N+1][N+1][M+5];
pii opt[N+1][N+1][M+5]; //fisrt->pos  second->mi
int cnt[M+5];
inline void getcnt(int l, int r, int p){
	rep(i, 0, m) cnt[c[i]] += l <= a[i] && a[i] <= p && p <= b[i] && b[i] <= r;
}
void solve(){
	rep(len, 1, n+1) rep(l, 1, n+1){
		int r = l + len - 1; //[l, r]
		if(r > n) break;
		rep(mi, 0, tot) dp[l][r][mi] = -INF;
		rep(p, l, r+1){
			getcnt(l, r, p);
			int sum = 0;
			per(mi, 0, tot){
				sum += cnt[mi]; cnt[mi] = 0;//clear cnt! 我在卡常! 
				int tmp = sum * seq[mi];
				if(l < p) tmp += dp[l][p-1][mi];
				if(p < r) tmp += dp[p+1][r][mi];
				if(dp[l][r][mi] < tmp) dp[l][r][mi] = tmp, opt[l][r][mi] = pii(p, mi);
			}
		}
		per(mi, 0, tot-1) if(dp[l][r][mi+1] > dp[l][r][mi]) 
			dp[l][r][mi] = dp[l][r][mi+1], opt[l][r][mi] = opt[l][r][mi+1];
	}
}
int ans[N+5];
void back(int l, int r, int mi){ //[l, r]
	int p = opt[l][r][mi].first;
	assert(l <= p);
	assert(p <= r);
	ans[p] = seq[mi];
	if(l <= p-1) back(l, p-1, opt[l][p-1][mi].second);
	if(p+1 <= r) back(p+1, r, opt[p+1][r][mi].second);
}
void output(){
	printf("%d\n", dp[1][n][0]); //4000 * 500000 = 20e8
	back(1, n, opt[1][n][0].second);
	rep(i, 1, n+1) printf("%d%c", ans[i], " \n"[i==n]);
}
void Main(){
	input();
	memset(cnt, 0, sizeof cnt);
	solve();
	output();
}

}

int main(){
	Program::Main();
	return 0;
}
/*
1<=n<=50，1<=m<=4000
正整数价格p[i]
1<=a[i]<=b[i]<=n
*/
