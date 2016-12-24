#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = 1000000;
const int S = 100;
const int L = (int)1e9;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
int n, s, mx;
int d[N*2+5];
void input(){
	scanf("%d %d", &n, &s);
	d[0] = 0; mx = 0;
	rep(i, 1, n+1){
		read(d[i]); mx = max(mx, d[i]);
		d[i+n] = d[i];
	}
	rep(i, 1, n*2+1) d[i] += d[i-1]; //d[i]<=L*2=2e9
}
int w;
int nxt[N+5];
void prepare(){
	for(int l = 1, r = 1; l <= n; ++l){
		while(r+1 <= 2*n && d[r+1] - d[l] <= w) ++r;
		nxt[l] = r;
	}
}
int ans;
bool vis[N+5];
int seq[N+5];
void work(int x){
	int p = x, v = x;
	int tot = 0, l = 0;
	while(true){
		seq[tot++] = v;
		vis[p] = true;
		v += nxt[p]-p;
		p = nxt[p]; if(p > n) p -= n;
		while(v-seq[l] >= n){
			ans = min(ans, tot-l);
			if(l+1<tot && v-seq[l+1] >= n) ++l;
			else break;
		}
		if(vis[p]) break;
	}
}
inline void response(){
	read(w); //printf("read %d\n", w);
	if(w < mx){puts("NIE"); return;}
	prepare();
	rep(i, 1, n+1) if(nxt[i] >= i+n){ puts("1"); return;}
	ans = INT_MAX;
	memset(vis, false, sizeof vis);
	rep(i, 1, n+1) if(!vis[i]) work(i);
	printf("%d\n", ans);
}
void Main(){
	input();
	while(s--) response();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

