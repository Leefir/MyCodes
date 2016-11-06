#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)

inline void read(int &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
	while(c = getchar(), c >= '0' && c <= '9');
}

const int N = 1000000;
typedef long long ll;
int n, m;
int num[N+5];
int seq[N+5], seqtot;
int f[N+5], x[N+5], y[N+5];
char str[10];
void input(){
	scanf("%d %d", &n, &m);
	seqtot = 0;
	seq[seqtot++] = 0;
	rep(i, 0, m){
		scanf("%s", str); 
		read(x[i]); read(y[i]);
		if(str[0] == 'U') f[i] = 0, seq[seqtot++] = y[i];
		else f[i] = 1;
	}
	sort(seq, seq + seqtot);
	seqtot = unique(seq, seq + seqtot) - seq;
}
typedef pair<ll, int> pli;
#define fi first
#define se second
struct BinaryIndexedTree{
	int n;
	pli a[N+5];
	void init(int _n){
		n = _n;
		rep(i, 0, n+1) a[i] = pli(0, 0);
	}
	inline pli combine(pli x, pli y){
		return pli(x.fi + y.fi, x.se + y.se);
	}
	inline void modify(int pos, pli add){
		for(int i = pos; i <= n; i += i & -i)
			a[i] = combine(a[i], add);
	}
	inline pli query(int pos){ // [1, pos]
		pli res(0, 0);
		for(int i = pos; i; i -= i & -i)
			res = combine(res, a[i]);
		return res;
	}
}bit;
void solve(){
	bit.init(seqtot); //[0, seqtot) -> [1, seqtot]
	int id = lower_bound(seq, seq + seqtot, 0) - seq + 1;
	rep(i, 1, n+1) num[i] = id; //一开始都是0
	bit.modify(id, pli(0, n));
	
	rep(i, 0, m){
		if(f[i] == 0){ //U k a 将序列中第k个数修改为a。
			int k = x[i], a = lower_bound(seq, seq + seqtot, y[i]) - seq + 1;
			bit.modify(num[k], pli(-seq[num[k]-1], -1));
			num[k] = a;
			bit.modify(num[k], pli(seq[num[k]-1], 1));
		}else if(f[i] == 1){ //Z c s 在这个序列上，每次选出c个正数，并将它们都减去1，询问能否进行s次操作。
			int c = x[i], s = upper_bound(seq, seq + seqtot, y[i]) - seq + 1 - 1; //s为<=y[i]的最大下标 
			pli tmp = bit.query(s);
			ll sum = tmp.fi + (n - tmp.se) * (ll)y[i];
//			printf("tmp %lld %d\n", tmp.fi, tmp.se);
//			printf("sum %lld c*y %lld\n", sum, c*(ll)y[i]);
			if(sum >= c * (ll)y[i]) puts("TAK");
			else puts("NIE");
		}else assert(false);
	}
}
int main(){
	input();
	solve();
	return 0;
}
/*
修改不独立 
每次询问独立，即每次询问不会对序列进行修改。

*/
