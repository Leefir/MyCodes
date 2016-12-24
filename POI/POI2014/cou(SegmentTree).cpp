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
inline void read(int &res){
    char c; res = 0;
    while(c = getchar(), c < '0');
    do res = (res*10) + (c^48);
    while(c = getchar(), c >= '0');
}
void printPositive(int x){
    if(x == 0) return;
    printPositive(x / 10);
    putchar(x % 10 ^ 48);
}
inline void print(int x){
    if(x == 0) putchar('0');
    else printPositive(x);
}

template<class tp>
struct vector{
	tp *arr;
	int sz, lim;
	void init(){
		arr = new tp[1];
		sz = 0; lim = 1;
	}
	void rebuild(){
		tp *tmp = new tp[lim*=2];
		rep(i, 0, sz) tmp[i] = arr[i];
		delete []arr;
		arr = tmp;
	}
	inline void pb(tp x){
		if(sz == lim) rebuild();
		arr[sz++] = x;
	}
	inline int count(int l, int r){
		return upper_bound(arr, arr+sz, r) - lower_bound(arr, arr+sz, l);
	}
};
const int N = 500000;
int n, m;
vector<int> vec[N+5];
int a[N+5];
void input(){
	scanf("%d %d", &n, &m);
	rep(i, 1, n+1) vec[i].init();
	rep(i, 1, n+1){
		read(a[i]);
		vec[a[i]].pb(i);
	}
}
#define root 1, 1, n
#define mid ((L+R)>>1)
#define lch (p<<1)
#define rch (p<<1|1)
#define lson lch, L, mid
#define rson rch, mid+1, R
struct SegmentTree{
	struct node{
		int val, cnt;
		node(){}
		node(int _v, int _c)
			:val(_v), cnt(_c){}
		inline node operator +(const node tmp){
			if(val == tmp.val) return node(val, cnt+tmp.cnt);
			else if(cnt > tmp.cnt) return node(val, cnt-tmp.cnt);
			else return node(tmp.val, tmp.cnt-cnt);
		}
	}tree[N*4+5];
	void build(int p, int L, int R){
		if(L == R){
			tree[p] = node(a[L], 1);
			return;
		}
		build(lson);
		build(rson);
		tree[p] = tree[lch]+tree[rch];
	}
	node query(int p, int L, int R, int l, int r){
		if(L == l && R == r) return tree[p];
		if(r <= mid) return query(lson, l, r);
		else if(mid < l) return query(rson, l, r);
		else return query(lson, l, mid)+query(rson, mid+1, r);
	}
}sgt;
inline void response(){
	int l, r; read(l); read(r);
	int val = sgt.query(root, l, r).val;
	if(vec[val].count(l, r)*2 > r-l+1) print(val), putchar('\n');
	else puts("0");
}
void Main(){
	input();
	sgt.build(root);
	while(m--) response();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

