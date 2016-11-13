#include <cstdio>
#include <cstring>
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)
namespace Program{

const int N = 200000;
const int M = 100000;
const int inf = (int)1e9;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
	while(c = getchar(), c >= '0' && c <= '9');
}
int n, m;
int l[M+5], r[M+5];
int mi[N+5], mx[N+5];
//mi[i]=min{r[j] | l[j] == i}  mx[i]=max{r[j] | l[j] == i}
inline int min(int x, int y){
	if(x < y) return x;
	return y;
}
inline int max(int x, int y){
	if(x > y) return x;
	return y;
}
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 0, n+1) mi[i] = inf, mx[i] = -inf;
	rep(i, 0, m){
		read(l[i]), read(r[i]);
		mi[l[i]] = min(mi[l[i]], r[i]);
		mx[l[i]] = max(mx[l[i]], r[i]);
	}
	rep(i, 2, n+1) mx[i] = max(mx[i], mx[i-1]);
	mi[n+1] = inf; per(i, 1, n) mi[i] = min(mi[i], mi[i+1]);
}
int dp[N+5];
void solve(){
	dp[n+1] = 0;
	for(int i = n; i >= 1; --i){
		dp[i] = -inf;
		rep(j, max(mx[i], i)+1, min(mi[i+1], n+1)+1) dp[i] = max(dp[i], dp[j]+1);
	}
	int mi = inf;
	rep(i, 0, m) mi = min(mi, r[i]);
	int ans = -1;
	rep(i, 1, min(mi,n)+1) ans = max(ans, dp[i]);
	printf("%d\n", ans);
}
void Main(){
	input();
	solve();
}

} //namespace Program

int main(){
	Program::Main();
	return 0;
}

/*
最多可能有多少斑点奶牛
无解输出-1 
*/
