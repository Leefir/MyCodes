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

const int N = (int)1e6;
int n; char str[N+5];
int sum[N+5], nxt[N*2+5];
int R[N+5];
void Main(){
	scanf("%d %s", &n, str+1);
	assert(strlen(str+1) == n);
	sum[0] = N; rep(i, 1, n+1) sum[i] = sum[i-1] + (str[i]=='p'? 1 : -1);
	memset(nxt, -1, sizeof nxt);
	R[n] = nxt[sum[n]] = n;
	int ans = 0;
	per(i, 0, n){
		if(sum[i] < sum[i+1]){
			R[i] = R[i+1];
			int t = nxt[sum[i]];
			if(t != -1 && sum[R[t]] >= sum[R[i]]) R[i] = R[t];
		}else R[i] = i;
		ans = max(ans, R[i]-i);
		nxt[sum[i]] = i;
	}
	printf("%d\n", ans);
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

