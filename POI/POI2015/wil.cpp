#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = 2000000;
typedef long long ll;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
int n, d; ll p;
int w[N+5];
ll sum[N+5];
void input(){
	std::cin >> n >> p >> d;
	sum[0] = 0;
	rep(i, 1, n+1){
		read(w[i]);
		sum[i] = sum[i-1] + w[i];
	}
}
inline ll calc(int l, int r){
	return sum[r] - sum[l-1];
}
inline ll max(ll x, ll y){
	if(x > y) return x;
	return y;
}
int que[N+5];
int L, H;
void push(int l){
	ll val = calc(l, l+d-1);
	while(L<H && calc(que[H-1], que[H-1]+d-1) <= val) H--;
	que[H++] = l;
}
void solve(){
	int ans = d;
	L = H = 0;
	que[H++] = 1;
	for(int l = 1, r = d; l+d-1<=n; ++l){
		while(L<H && que[L]<l) ++L;
		while(r+1 <= n){
			ll tmp = calc(r+1-d+1, r+1);
			if(calc(l, r+1) - max(tmp, calc(que[L], que[L]+d-1)) <= p){
				push(r+1-d+1);
				++r;
			}else break;
		}
		ans = max(ans, r-l+1);
	}
	printf("%d\n", ans);
}
void Main(){
	input();
	solve();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

