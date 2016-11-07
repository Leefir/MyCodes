#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

template <typename Tp>inline void read(Tp &res){
    char c;res=0;
    while(c=getchar(),!isdigit(c));
    do res=(res<<1)+(res<<3)+(c^48);
    while(c=getchar(),isdigit(c));
}
template <typename Tp>void printPositive(Tp x){
    if(x==0)return;
    printPositive(x/10);
    putchar(x%10^48);
}
template <typename Tp>inline void print(Tp x){
    if(x==0)putchar('0');
    else if(x<0)putchar('-'),printPositive(-x);
    else printPositive(x);
}
inline int min(int x, int y){
	if(x < y) return x;
	return y;
}

const int N = 100000;
const int M = 200000;
const int K = 300000;
const int LIM = (int)1e9;
int n, s, m;
int l[M+5], r[M+5], k[M+5], constraint[M+5];
int deg[N+5], lim[N+5], ans[N+5];
vector<int> vec[N+5];
void input(){
	scanf("%d %d %d", &n, &s, &m);
	rep(i, 1, n+1) lim[i] = LIM, ans[i] = -1;
	rep(i, 0, s){
		int p, d; read(p); read(d);
		ans[p] = d;
	}
	rep(i, 1, n+1) vec[i].clear(), deg[i] = 0;
	rep(i, 0, m){
		read(l[i]); read(r[i]); read(k[i]);
		constraint[i] = LIM;
		deg[l[i]]++; deg[r[i]+1]--; //差分 
		rep(j, 0, k[i]){
			int x; read(x);
			vec[x].push_back(i);
		}
	}
	rep(i, 2, n+1) deg[i] += deg[i-1];
	rep(i, 1, n+1) deg[i] -= (int)vec[i].size();
}
#define root 1, 1, n
#define lch (p<<1)
#define rch (p<<1|1)
#define mid ((L+R)>>1)
#define lson lch, L, mid
#define rson rch, mid+1, R
struct node{
	int pos, lim, deg;
	node(){}
	node(int _p, int _l, int _d){pos = _p; lim = _l; deg = _d;}
};
struct SegmentTree{
	node t[N*4+5];
	int ll[N*4+5], dl[N*4+5]; //lim_lazy deg_lazy
	inline node pushUp(node x, node y){ //返回度数较小的一个 
		if(x.deg < y.deg) return x;
		return y;
	}
	inline void modify(int p, int lim, int dlt){
		t[p].lim = min(t[p].lim, lim);
		ll[p] = min(ll[p], lim);
		t[p].deg += dlt;
		dl[p] += dlt;
	}
	inline void pushDown(int p){
		modify(lch, ll[p], dl[p]);
		modify(rch, ll[p], dl[p]);
		dl[p] = 0;
	}
	void build(int p, int L, int R){
		ll[p] = LIM; dl[p] = 0;
		if(L == R){
			t[p] = node(L, lim[L], deg[L]);
			return;
		}
		build(lson);
		build(rson);
		t[p] = pushUp(t[lch], t[rch]);
	}
	void update(int p, int L, int R, int l, int r, int lim, int dlt){
		if(L == l && R == r){
			modify(p, lim, dlt);
			return;
		}
		pushDown(p);
		if(r <= mid) update(lson, l, r, lim, dlt);
		else if(mid < l) update(rson, l, r, lim, dlt);
		else update(lson, l, mid, lim, dlt), update(rson, mid+1, r, lim, dlt);
		t[p] = pushUp(t[lch], t[rch]);
	}
}sgt;
void Main(){
	input();
	sgt.build(root);
	rep(i, 0, n){
		node now = sgt.t[1];
		int pos = now.pos;
		if(now.deg != 0 || now.lim < 1){ puts("NIE"); return;}
		if(ans[pos] != -1 && ans[pos] > now.lim){ puts("NIE"); return;}
		if(ans[pos] == -1) ans[pos] = now.lim;
		sgt.update(root, pos, pos, LIM, (int)1e9);
		rep(j, 0, (int)vec[pos].size()){
			int id = vec[pos][j];
			constraint[id] = min(constraint[id], ans[pos]-1);
			if(--k[id] == 0) sgt.update(root, l[id], r[id], constraint[id], -1);
		}
	}
	puts("TAK");
	rep(i, 1, n+1) print(ans[i]), putchar(' ');
}

}

int main(){
	Program::Main();
	return 0;
}

/*
严格大于，即没有等号
任意构造出一组满足条件的方案，或者判断无解。
每个数都在1到10^9范围内
*/
