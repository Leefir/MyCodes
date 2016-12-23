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
const int N = (int)1e6;
int n, m, s, t;
int a[N+5];
int mx, mxid;
void input(){
	scanf("%d %d %d", &n, &s, &t); m = 0;
	rep(i, 1, n+1){
		read(a[i]); m += a[i];
	}
}
int b[N+5];
void re(){
	puts("0");
	exit(0);
}
void work(int l, int r){
	int p = l;
	while(a[mxid]--){
		b[p] = mxid;
		p += 2; if(p > r) p = l+1;
	}
	rep(i, 1, n+1) if(i != mxid){
		while(a[i]--){
			b[p] = i;
			p += 2; if(p > r) p = l+1;
		}
	}
}
inline void swap(int &x, int &y){
	x ^= y; y ^= x; x ^= y;
}
void up(int cur){
	while(cur > 1){
		if(b[cur-1] == b[cur] || b[cur+1] == b[cur]){
			if(cur-1 == 1) re();
			swap(b[cur-1], b[cur]);
			--cur;
		}else break;
	}
}
void solve(){ //m >= 3
	mx = -1;
	b[1] = s; b[m] = t; --a[t];
	rep(i, 1, n+1) if(a[i] > mx) mx = a[i], mxid = i;
	if(a[s] == mx) mxid = s, work(1, m-1);
	else --a[s], work(2, m-1);
	
	if(b[m-1] == b[m]) up(m-1);
	rep(i, 1, m) if(b[i] == b[i+1]) re();
	rep(i, 1, m+1) print(b[i]), putchar(" \n"[i==m]);
}
void Main(){
	input();
	if(m == 1) puts("1");
	else if(s == t && a[s] < 2) re();
	else if(m == 2){
		if(s == t) re();
		else printf("%d %d\n", s, t);
	}
	else solve();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

