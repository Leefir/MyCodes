#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = (int)1e6;
int n;
char str[N+5];
int sum[3][N+5];
void input(){
	scanf("%d %s", &n, str+1);
	assert(strlen(str+1) == n);
	sum[0][0]=sum[1][0]=sum[2][0]=0;
	rep(i, 1, n+1){
		if(str[i] == 'B') str[i] = 0;
		else if(str[i] == 'C') str[i] = 1;
		else if(str[i] == 'S') str[i] = 2;
		else assert(false);
		rep(j, 0, 3) sum[j][i] = sum[j][i-1] + (str[i] == j);
	}
}
int ans;
void prechk(){
	//one color
	for(int i = 1; i <= n;){
		int j = i;
		while(j <= n && str[j] == str[i]) ++j;
		//[i, j)
		ans = max(ans, j-i);
		i = j;
	}
}
typedef pair<int, int> pii;
map<pii, int> mp;
int cnt[3][N*2+5]; //cnt[i][j+N]
void modify(int id, int f){
	int x = sum[1][id]-sum[0][id], y = sum[2][id]-sum[1][id], z = sum[0][id]-sum[2][id];
	mp[pii(x, y)] += f;
	cnt[0][x+N] += f;
	cnt[1][y+N] += f;
	cnt[2][z+N] += f;
}
void solve(){
	//2 or 3 colors
	mp.clear();
	memset(cnt, 0, sizeof cnt);
	for(int r = 1; r <= n; ++r){
		if(r-ans-1 >= 0) modify(r-ans-1, 1);
		while(r-ans >= 1){
			int x = sum[1][r]-sum[0][r], y = sum[2][r]-sum[1][r], z = sum[0][r]-sum[2][r];
			int tmp = cnt[0][x+N] + cnt[1][y+N] + cnt[2][z+N] - (mp.find(pii(x, y))!=mp.end()? mp[pii(x, y)]*2 : 0);
			if(tmp < r-ans) modify(r-ans-1, -1), ++ans;
			else break;	
		}
	}
}
void Main(){
	input();
	ans = 0;
	prechk();
	solve();
	printf("%d\n", ans);
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

