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
typedef long long ll;
inline void read(ll &res){
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
}
int n, s;
ll t[N+5], dp[N+5];
void Main(){
	scanf("%d %d", &n, &s);
	t[0] = dp[0] = -1;
	rep(i, 1, n+1){
		read(t[i]);
		t[i] = max(t[i], t[i-1]+1);
	}
	int k = 0;
	rep(i, 1, n+1){
		while(k+1 < i && t[i] >= dp[k+1]+i-(k+1)-1) k++;
		dp[i] = max(t[i], dp[k]+i-k-1) + s+s+i-k-1;
	}
	
	cout << dp[n] << endl;
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

