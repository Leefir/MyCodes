#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

typedef long long ll;
const int M = 1442249+5; //[0, M)
ll table[M+5];
void prepare(){
	table[0] = 0;
	rep(i, 1, M) table[i] = table[i-1] + i*(ll)i;
}
const int inf = (int)1e9;
int hehe[] =
{
0,1,1000000000,1000000000,2,2,1000000000,1000000000,1000000000,3,3,1000000000,1000000000,3,3,1000000000,4,4,1000000000,1000000000,4,4,1000000000,1000000000,1000000000,4,4,1000000000,1000000000,4,4,1000000000,1000000000,1000000000,5,5,6,6,5,5,6,5,5,1000000000,1000000000,5,5,1000000000,1000000000,6,5,5,6,6,5,5,6,6,7,7,1000000000,6,6,7,8,6,6,1000000000,8,7,6,6,1000000000,8,6,6,1000000000,6,6,7,8,6,6,7,7,7,6,6,7,7,6,6,1000000000,8,7,7,1000000000,9,7,7,7,7,7,7,7,7,7,9,1000000000,8,7,7,1000000000,8,7,7,8,8,8,7,7,8,8,7,7,8,7,7,1000000000,8,7,7,9,8,8,7,7,9,8,7,7,8,8,8,9,8,8,8,8,8,8,8,8,8,8,8,9,10,8,8,9,9,8,8,8,8,8,8,8,8,8,9,9,10,8,8,9,10,8,8,9,9,9,8,8,9,9,8,8,10,8,8,9,10,8,8,9,9,9,8,8,9,9,8,8,9,9,9,9,10,9,9,9,10,9,9,9,9,10,9,9,9,9,9,9,10,9,9,9,9,9,9,9,9,9,9,9,10,10,9,9,10,10,9,9,9,9,9,9,9,9,9,10,10,10,9,9,11,10,9,9,10,10,10,9,9,10,10,9,9,10,9,9,11,10,9,9,11,10,10,9,9,10,10,9,9,10,10,10,11,10,10,10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,10,10,10,11,10,10,10,10,11,10,10,10,10,10,10,11,10,10,10,10,10,10,10,10,10,10,10,11,11,10,10,11,11,10,10,10,10,10,10,10,10,10,11,11,11,10,10,11,11,10,10,11,11,11,10,10,11,11,10,10,11,10,10,11,11,10,10,11,12,11,10,10,11,11,10,10,11,11,11,11,11,11,11,11,12,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,12,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,11,11,11,12,11,11,11,11,12,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,12,12,11,11,12,12,11,11,11,11,11,11,11,11,11,12,12,12,11,11,12,12,11,11,12,12,12,11,11,12,12,11,11,12,11,11,12,12,11,11,12,12,12,11,11,12,12,11,11
};
ll n;
int t;
void solve(){
	ll w = table[t] - n;
	if(w <= 506 && hehe[w] == inf) printf("%d ", t+1); else printf("%d ", t);
	int cnt = 175 + (t-12)*31;
	rep(i, 1, 506+1) if(hehe[i] == inf && table[t]-i <= n) cnt++;
	printf("%d\n", cnt);
}
void Main(){
	prepare();
	cin >> n;
	if(n <= 506){
		if(hehe[n] == inf) printf("- "); else printf("%d ", hehe[n]);
		int mi = inf;
		int cnt = 0;
		per(i, n+1, 506+1) mi = min(mi, hehe[i]);
		per(i, 1, n+1){
			cnt += hehe[i] > mi;
			mi = min(mi, hehe[i]);
		}
		printf("%d\n", cnt);
		return;
	}
	t = lower_bound(table, table+M, n) - table;
	solve();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}
