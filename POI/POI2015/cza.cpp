#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
const int N = 1000000;
const int K = 100000;
int n, k, p;
bool l[N+5][4], r[N+5][4]; //forbbiden
void input(){
	scanf("%d %d %d", &n, &k, &p);
	memset(l, false, sizeof l);
	memset(r, false, sizeof r);
	rep(i, 0, k){
		int a, b; read(a); read(b);
		//b 不能坐在 a 的右边
		if(b>a && b-a<=3) r[a][b-a] = true;
		if(a>b && a-b<=3) l[b][a-b] = true;
	}
}
const int mod = (int)1e9+7;
inline void addmod(int &x, int y){
	if((x+=y) >= mod) x -= mod;
}
int dp[N+5][10];
void solve3(){
	//init
	memset(dp, 0, sizeof dp);
	if(!l[n-3][3] && !r[n-1][1]) dp[n-4][0] = 1;
	if(!l[n-3][3] && !r[n-2][2]) dp[n-4][1] = 1;
	if(!l[n-2][2] && !r[n-1][1]) dp[n-4][2] = 1;
	if(!l[n-2][2] && !r[n-3][3]) dp[n-4][3] = 1;
	if(!l[n-1][1] && !r[n-2][2]) dp[n-4][4] = 1;
	if(!l[n-1][1] && !r[n-3][3]) dp[n-4][5] = 1;
	for(int i = n-4; i >= 1; --i){
		//dp[i][0]
		if(!r[i+2][1]) addmod(dp[i-1][2], dp[i][0]);
		if(!r[i][3]) addmod(dp[i-1][3], dp[i][0]);
		//dp[i][1]
		if(!r[i][3] && !l[i+2][1]) addmod(dp[i-1][7], dp[i][1]);
		if(!r[i+1][2] && !l[i][3]) addmod(dp[i-1][8], dp[i][1]);
		//dp[i][2]
		if(!r[i+1][2]) addmod(dp[i-1][4], dp[i][2]);
		if(!r[i][3]) addmod(dp[i-1][5], dp[i][2]);
		//dp[i][3]
		if(!r[i][3] && !l[i+1][2]) addmod(dp[i-1][9], dp[i][3]);
		if(!r[i+2][1] && !l[i][3]) addmod(dp[i-1][6], dp[i][3]);
		//dp[i][4]
		if(!l[i][3]) addmod(dp[i-1][0], dp[i][4]);
		if(!l[i+1][2]) addmod(dp[i-1][2], dp[i][4]);
		//dp[i][5]
		if(!l[i][3]) addmod(dp[i-1][1], dp[i][5]);
		if(!l[i+2][1]) addmod(dp[i-1][4], dp[i][5]);
		//dp[i][6]
		if(true) addmod(dp[i-1][2], dp[i][6]);
		//dp[i][7]
		if(true) addmod(dp[i-1][4], dp[i][7]);
		//dp[i][8]
		if(!r[i][3]) addmod(dp[i-1][7], dp[i][8]);
		//dp[i][9]
		if(!l[i][3]) addmod(dp[i-1][6], dp[i][9]);
	}
	int ans = 0;
	if(!r[1][1] && !r[2][1]) addmod(ans, dp[0][0]);
	if(!r[1][2] && !l[2][1]) addmod(ans, dp[0][1]);
	if(!l[1][1] && !r[1][2]) addmod(ans, dp[0][2]);
	if(!r[2][1] && !l[1][2]) addmod(ans, dp[0][3]);
	if(!l[1][2] && !r[1][1]) addmod(ans, dp[0][4]);
	if(!l[2][1] && !l[1][1]) addmod(ans, dp[0][5]);
	if(!r[1][1]) addmod(ans, dp[0][6]);
	if(!l[1][1]) addmod(ans, dp[0][7]);
	if(!r[1][2]) addmod(ans, dp[0][8]);
	if(!l[1][2]) addmod(ans, dp[0][9]);
	printf("%d\n", ans);
}
int a[N+5];
bool chk(){ //[0, n]  a[0] = a[n] = n
	rep(i, 0, n) if(abs(a[i]-a[i+1]) > p) return false;
	rep(i, 1, n+1) if(a[i-1]>a[i] && a[i-1]-a[i]<=3 && l[a[i]][a[i-1]-a[i]]) return false;
	rep(i, 0, n) if(a[i+1]>a[i] && a[i+1]-a[i]<=3 && r[a[i]][a[i+1]-a[i]]) return false;
	return true;
}
void solve2(){
	int ans = 0;
	a[0] = a[n] = n;
	int l = 1, r = n-1;
	for(int i = n-2; i >= 1; i -= 2) a[l++] = i;
	for(int i = n-1; i >= 1; i -= 2) a[r--] = i;
	ans += chk();
	assert(l == r+1);
	l = 1; r = n-1;
	for(int i = n-1; i >= 1; i -= 2) a[l++] = i;
	for(int i = n-2; i >= 1; i -= 2) a[r--] = i;
	ans += chk();
	assert(l == r+1);
	printf("%d\n", ans);
}
void solve1(){
	//n, n-1, n-2, ..., 1
	rep(i, 1, n) if(l[i][1]){ puts("0"); return;}
	puts("1");
}
void brute(){
	a[0] = a[n] = n;
	rep(i, 1, n) a[i] = i;
	int ans = 0;
	do{
		ans += chk();
	}while(next_permutation(a+1, a+n));
	printf("%d\n", ans);
}
void Main(){
	input();
	if(n <= 5){ brute(); return;}
	if(p == 3) solve3();
	else if(p == 2) solve2();
	else if(p == 1) solve1();
	else if(p == 0) printf("%d\n", n==1);
	else assert(false);
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

