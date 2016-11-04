#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)

const int N = 1000;
int n, m, a, b;
char g[N+5][N+5], f[N+5][N+5];
typedef pair<int, int> pii;
pii pos[N*N+5];
int cntg, cntf;
bool flag;
void paint(int x, int y){
	rep(i, 0, cntf){
		int p = pos[i].first + x;
		int q = pos[i].second + y;
		if(p < 0 || q < 0 || p >= n || q >= m || g[p][q] == '.'){
			flag = true;
			return;
		}
		g[p][q] = '.';
	}
}
void solve(){
	flag = false;
	scanf("%d %d %d %d", &n, &m, &a, &b);
	cntg = 0;
	rep(i, 0, n){
		scanf("%s", g[i]);
		rep(j, 0, m) cntg += g[i][j] == 'x';
	}
	cntf = 0;
	rep(i, 0, a) {
		scanf("%s", f[i]);
		rep(j, 0, b) if(f[i][j] == 'x')
			pos[cntf++] = pii(i, j);
	}
	if(cntf == 0) {puts("NIE"); return;}
	rep(i, 0, n) rep(j, 0, m) if(g[i][j] == 'x'){
		int x = i - pos[0].first, y = j - pos[0].second;
		paint(x, y);
		if(flag) {puts("NIE"); return;}
		cntg -= cntf;
	}
	if(cntg == 0) puts("TAK");
	else puts("NIE");
}
int main(){
	int q; scanf("%d", &q);
	while(q--) solve();
	return 0;
}

/*

不能把墨水印到纸外面。

纸上的同一个格子   不可以  印多次。 
*/
