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
	while(c = getchar(), c < '0' || c > '9');
	do res = (res*10) + (c^48);
	while(c = getchar(), c >= '0' && c <= '9');
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
int n, k, m, l;
int c[N+5], a[N+5];
void input(){
	scanf("%d %d", &n, &k);
	rep(i, 1, n+1) read(c[i]);
	scanf("%d %d", &m, &l);
	rep(i, 1, m+1) read(a[i]);
	per(i, m, m+l) read(a[i]);
}
int pos[N+5], nxt[N+5];
void prepare(){
	memset(pos, -1, sizeof pos);
	per(i, 1, n+1){
		int &p = pos[c[i]];
		if(p == -1) nxt[i] = -1; else nxt[i] = p;
		p = i;
	}	
}
int ans[N+5], anstot;
int seq[N+5];
int cnt[2][N+5], sum;
bool init(){
	int cur = 1;
	rep(i, 1, n+1){
		if(c[i] == a[cur]) seq[cur++] = i;
		if(cur == m+l) break;
	}
	if(cur != m+l) return false;
	per(i, 1, m){
		while(nxt[seq[i]] != -1 && nxt[seq[i]] < seq[i+1]) seq[i] = nxt[seq[i]];
	}
	sum = 0;
	memset(cnt, 0, sizeof cnt);
	rep(i, 1, seq[1]) cnt[0][c[i]]++;
	rep(i, seq[m+l-1]+1, n+1){
		cnt[1][c[i]]++;
		if(cnt[0][c[i]] && cnt[1][c[i]] == 1) sum++;
	}
	return true;
}
void solve(){
	anstot = 0;
	if(!init()){puts("0\n"); return;}
	if(sum) ans[anstot++] = seq[m];
	while(true){
		int mem1 = seq[1], mem2 = seq[m+l-1];
		seq[m] = nxt[seq[m]];
		if(seq[m] == -1) break;
		int p = m;
		while(p-1 >= 1){
			--p; if(nxt[seq[p]] == -1 || !(nxt[seq[p]] < seq[p+1])) break;
			while(nxt[seq[p]] != -1 && nxt[seq[p]] < seq[p+1]) seq[p] = nxt[seq[p]];
		}
		rep(i, mem1, seq[1]) if(cnt[0][c[i]]++ == 0 && cnt[1][c[i]]) sum++;
		p = m;
		bool ok = true;
		while(p+1 < m+l){
			++p; if(seq[p-1] < seq[p]) break;
			while(!(seq[p-1] < seq[p])){
				if(nxt[seq[p]] == -1){ ok = false; break;}
				seq[p] = nxt[seq[p]];
			}
			if(ok == false) break;
		}
		if(ok == false) break;
		rep(i, mem2+1, seq[m+l-1]+1) if(--cnt[1][c[i]] == 0 && cnt[0][c[i]]) sum--;
		if(sum) ans[anstot++] = seq[m];
	}
	printf("%d\n", anstot);
	rep(i, 0, anstot){
		print(ans[i]); putchar(' ');
	}puts("");
}
void Main(){
	input();
	prepare();
	solve();
}

} //namespace Program

/*

*/
int main(){
	Program::Main();
	return 0;
}

