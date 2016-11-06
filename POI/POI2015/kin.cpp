#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
typedef long long ll;

inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c - '0');
	while(c = getchar(), c >= '0' && c <= '9');
}

const int N = 1000000;
int n, m;
int f[N + 5], w[N + 5];
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 1, n + 1) read(f[i]);
	rep(i, 1, m + 1) read(w[i]);
}

struct SegmentTree{
	ll mi[N * 4 + 5], lazy[N * 4 + 5];
	#define root 1, 1, n + 1
	#define lch (p << 1)
	#define rch (p << 1 | 1)
	#define mid ((L + R) >> 1)
	#define lson lch, L, mid
	#define rson rch, mid + 1, R
	inline ll min(ll x, ll y){
		if(x < y) return x;
		return y;
	}
	inline void modify(int p, ll x){
		lazy[p] += x;
		mi[p] += x;
	}
	inline void pushDown(int p){
		if(lazy[p]){
			modify(lch, lazy[p]);
			modify(rch, lazy[p]);
			lazy[p] = 0;
		}
	}
	void b(int p, int L, int R){
		mi[p] = lazy[p] = 0;
		if(L == R) return;
		b(lson);
		b(rson);
		mi[p] = min(mi[lch], mi[rch]);
	}
	void build(){
		b(root);
	}
	ll q(int p, int L, int R, int l, int r){
		if(L == l && R == r) return mi[p];
		pushDown(p);
		if(r <= mid) return q(lson, l, r);
		else if(mid < l) return q(rson, l, r);
		else return min(q(lson, l, mid), q(rson, mid + 1, r));
	}
	ll query(int l, int r){
		return q(root, l + 1, r + 1);
	}
	void u(int p, int L, int R, int l, int r, ll add){
		if(L == l && R == r) {modify(p, add); return;}
		pushDown(p);
		if(r <= mid) u(lson, l, r, add);
		else if(mid < l) u(rson, l, r, add);
		else u(lson, l, mid, add), u(rson, mid + 1, r, add);
		mi[p] = min(mi[lch], mi[rch]);
	}
	void update(int l, int r, ll add){
		u(root, l + 1, r + 1, add);
	}
}sgt;
int last[N + 5], llast[N + 5];
void solve(){
	ll ans = 0;
	sgt.build();
	ll sum = 0;
	rep(i, 1, m + 1) last[i] = 0, llast[i] = 0;
	rep(i, 1, n + 1){
		if(last[f[i]] == 0) sum += w[f[i]];
		else sgt.update(llast[f[i]], last[f[i]] - 1, w[f[i]]), sgt.update(last[f[i]], i - 1, -w[f[i]]);
		llast[f[i]] = last[f[i]]; last[f[i]] = i;
		ans = max(ans, sum - sgt.query(0, i - 1));
		sgt.update(i, i, sum);
	}
	cout << ans << endl;
}

int main(){
	input();
	solve();
	return 0;
}

/*
long long

*/
