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
const int N = 1000000;
const int inf = (int)1e9;
int n, k, a[N+5];
void input(){
	scanf("%d %d", &n, &k);
	rep(i, 0, n) read(a[i]), --a[i]; //[0, k)
}
typedef pair<int, int> pii;
#define fi first
#define se second
pii border[N+5]; //[fi, se)
const int S = 20;
int nxt[N+5][S], last[N+5], tot[N+5];
void prepare(){
	rep(i, 0, k) border[i] = pii(inf, -inf);
	rep(i, 0, n){
		border[a[i]].fi = min(border[a[i]].fi, i);
		border[a[i]].se = max(border[a[i]].se, i+1);
	}
}
int cnt[N+5];
int que[N+5], ql, qh; //store pos
int lp, rp; //[lp, rp)
inline bool extend(int L, int R, int pos){ //[L, R)
	int c = a[pos];
	if(border[c].fi < L || border[c]. se > R) return false;
	while(border[c].fi <= lp-1) que[qh++] = --lp;
	while(rp+1 <= border[c].se) que[qh++] = rp++;
	return true;
}
void conquer(int L, int R){ //[L, R)
	int mid = L + (R-L) / 2;
	ql = qh = 0;
	lp = mid, rp = mid;
	que[qh++] = rp++;
	while(lp-1 >= L){
		que[qh++] = --lp;
		while(ql < qh) if(extend(L, R, que[ql++]) == false) return;
		cnt[lp] += cnt[rp] + 1;
		nxt[lp][tot[lp]++] = rp;
	}
}
void divide(int L, int R){ //[L, R)
	if(R - L == 1){
		if(border[a[L]].fi == L && border[a[L]].se == R){
			cnt[L]++;
			nxt[L][tot[L]++] = R;
		}
		return;
	}
	int mid = L + (R-L) / 2;
	divide(L, mid); divide(mid, R);
	conquer(L, R);
}
int work(){
	int ans = N; //切成的两段长度之差绝对值的最小值
	rep(i, 0, n){
		int cur = i;
		while(true){
			if(tot[cur] == 0) break;
			int &p = last[cur];
			while(p+1 < tot[cur] && nxt[cur][p+1] <= n/2 + i) p++;
			if(p+1 < tot[cur]) ans = min(ans, 2*(nxt[cur][p+1]-i) - n);
			if(p != -1)cur = nxt[cur][p];
			else break;
		}
		ans = min(ans, n - 2*(cur-i));
	}
	return ans;
}
void Main(){
	input();
	prepare();
	rep(i, 0, n) cnt[i] = 0, tot[i] = 0, last[i] = -1;
	divide(0, n-1); //[0, n-1) 要求a[n-1]一定在另一个项链里 
	
	long long ans = 0;
	rep(i, 0, n) ans += cnt[i];
	cout << ans << ' ' << work() << endl; 
}

}

int main(){
	Program::Main();
	return 0;
}
/*
方案数量（保证至少存在一种）
保证k种颜色各出现至少一次
k<=n
*/
