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

const int N = 200000;
const int M = 1000000;
inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
int n, m;
typedef pair<int, int> pii;
#define fi first
#define se second
int a[N+5][2];
inline void swap(int &x, int &y){
	int t = x; x = y; y = t;
}
void input(){
	scanf("%d", &n);
	rep(i, 1, n+1){
		read(a[i][0]); read(a[i][1]);
	}
}
#define root 1, 1, n
#define mid ((L+R)>>1)
#define lch (p<<1)
#define rch (p<<1|1)
#define lson lch, L, mid
#define rson rch, mid+1, R
inline void chkMin(int &x, int y){
	if(x > y) x = y;
}
struct SegmentTree{
	struct node{
		int x[2], mi[2];
		node(){mi[0] = mi[1] = INT_MAX;}
		inline node operator +(const node tmp){
			node res;
			res.x[0] = x[0]; res.x[1] = x[1];
			rep(i, 0, 2) rep(j, 0, 2) if(mi[i]<=tmp.x[j])
				chkMin(res.mi[i], tmp.mi[j]);
			return res;
		}
	}tree[N*4+5];
	void build(int p, int L, int R){
		if(L == R){
			rep(i, 0, 2) tree[p].x[i] = tree[p].mi[i] = a[L][i];
			return;
		}
		build(lson);
		build(rson);
		tree[p] = tree[lch]+tree[rch];
	}
	void update(int p, int L, int R, int pos){
		if(L == R){
			rep(i, 0, 2) tree[p].x[i] = tree[p].mi[i] = a[pos][i];
			return;
		}
		if(pos <= mid) update(lson, pos);
		else update(rson, pos);
		tree[p] = tree[lch]+tree[rch];
	}
	inline bool query(){
		return tree[1].mi[0] != INT_MAX || tree[1].mi[1] != INT_MAX;
	}
}sgt;
inline void response(){
	int x, y; read(x); read(y);
	swap(a[x][0], a[y][0]);
	swap(a[x][1], a[y][1]);
	sgt.update(root, x);
	sgt.update(root, y);
	if(sgt.query()) puts("TAK");
	else puts("NIE");
}
void Main(){
	input();
	sgt.build(root);
	scanf("%d", &m);
	while(m--) response();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

