#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int N = (int)1e9;
const int M = (int)1e6;
typedef long long ll;
int n, a, b, p, m;
char str[M+5];
inline int min(int x, int y){
	if(x < y) return x;
	return y;
}
inline int max(int x, int y){
	if(x > y) return x;
	return y;
}
int l1, r1, l2, r2;
inline void get(int k){ //第k个约束条件 
	int t = (k * (ll)a + b) % n;
	if(str[k] == '0'){ //0 <=(x+t)%n < p
		l1 = 0, r1 = max(p-t, 0); //[l1, r1)
		l2 = n-t, r2 = min(p+n-t, n); //[l2, r2)
	}else if(str[k] == '1'){ //p<= (x+t)%n < n
		l1 = max(p-t, 0), r1 = n-t;
		l2 = min(n+p-t, n), r2 = n;
	}else assert(false);
}
int seq[M*6+5], tot;
inline void add(int pos, int f){
	if(f == 1) seq[tot++] = pos << 1;
	else if(f == -1) seq[tot++] = pos << 1 | 1;
	else assert(false);
}
void doit(){
	tot = 0;
	rep(i, 0, m){
		get(i);
		add(l1, 1); add(r1, -1);
		add(l2, 1); add(r2, -1);
	}
	rep(i, n-m+1, n){ //[n-m+1, n-m+1+m) n-m+1+m = n+1 > n
		int x = (i * (ll)a) % n;
		add(x, -1); add(x+1, 1); //可以让位置x无法达到m 
		//最后m-1个要删掉 
	}
	add(n, -1);
	int sum = 0;
	int ans = 0;
	sort(seq, seq + tot);
	rep(i, 0, tot-1){
		if(seq[i] & 1) --sum; else ++sum;
		if(sum == m) ans += (seq[i+1] >> 1) - (seq[i] >> 1);
	}
	printf("%d\n", ans);
}
void Main(){
	scanf("%d %d %d %d %d", &n, &a, &b, &p, &m);
	scanf("%s", str);
	doit();
}

}//namespace Program
int main(){
	Program::Main();
	return 0;
}

/*

n,a互质
c[i]==0当且仅当(ai+b) mod n < p
*/
