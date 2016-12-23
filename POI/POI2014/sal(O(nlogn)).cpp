#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = (int)1e6;
int n; char str[N+5];
int pre[N+5];
vector<int> vec[N+5];
void prepare(){
	pre[0] = 0;
	rep(i, 1, n+1){
		if(str[i] == 'j') pre[i] = i;
		else if(str[i] == 'p'){
			int t = pre[i-1];
			if(t == 0) pre[i] = 0;
			else{
				assert(str[t] == 'j');
				pre[i] = pre[t-1];
			}
		}else assert(false);
	}
	rep(i, 0, n+1) vec[i].clear();
	rep(i, 0, n+1) if(pre[i] != i) vec[pre[i]].push_back(i);
}
int nxt[N+5];
void calcnxt(){
	nxt[n+1] = n+1;
	per(i, 1, n+1){
		if(str[i] == 'j') nxt[i] = i;
		else if(str[i] == 'p'){
			int t = nxt[i+1];
			if(t == n+1) nxt[i] = n+1;
			else{
				assert(str[t] == 'j');
				nxt[i] = nxt[t+1];
			}
		}else assert(false);
	}
}
struct BinaryIndexedTree{
	int mx[N+5];
	void init(){
		rep(i, 0, n+1) mx[i] = 0;
	}
	void update(int pos, int x){
		for(int i = pos; i <= n; i += i&-i)
			mx[i] = max(mx[i], x);
	}
	int query(int pos){
		int res = 0;
		for(int i = pos; i > 0; i -= i&-i)
			res = max(res, mx[i]);
		return res;
	}
}bit;
void solve(){
	int ans = 0;
	bit.init();
	rep(i, 1, n+1){
		if(n-i+1<=ans) break;
		rep(j, 0, (int)vec[i-1].size())
			bit.update(vec[i-1][j], vec[i-1][j]);
		if(nxt[i] == i) continue;
		int mx = bit.query(nxt[i]-1);
		ans = max(ans, mx - i + 1);
	}
	printf("%d\n", ans);
}
void Main(){
	scanf("%d %s", &n, str+1);
	assert(strlen(str+1) == n);
	prepare();
	calcnxt();
	solve();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

