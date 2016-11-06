#include <cstdio>
#include <cstring>
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

inline void read(int &res){ // read non-negative int!
	char c; res = 0;
	while(c = getchar(), c < '0' || c > '9');
	do res = (res * 10) + (c ^ 48);
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

namespace Program{

const int N = 1000000;

int n;
int c[N + 5];
void input(){
	scanf("%d", &n);
	rep(i, 1, n + 1) read(c[i]), c[i] <<= 1;
	//c[i] even <= 2e9
}

int match[N + 5];
void output(){
	rep(i, 1, n + 1) print(match[i]), putchar(' ');
}
void solve(){
	//n to left
	memset(match, -1, sizeof match);
	match[n] = n;
	per(i, 1, n){
		int l = c[i], r = c[i + 1];
		if(match[i + 1] == i + 1) r >>= 1;
		if(l >= r) match[i] = i; else match[i] = i + 1;
		if(match[i] == i + 1){
			for(int j = i + 1; j < n && match[j] == j; ++j){
				int l = c[j], r = c[j + 1];
				if(match[j - 1] == j) l >>= 1;
				if(match[j + 1] == j + 1) r >>= 1;
				if(l >= r) break;
				match[j] = j + 1;
			}
		}
	}
	int l = c[n], r = c[1];
	if(match[n - 1] == n) l >>= 1;
	if(match[1] == 1) r >>= 1;
	if(l >= r){
		output();
		return;
	}
	
	//n to right
	memset(match, -1, sizeof match);
	match[n] = 1;
	per(i, 1, n){
		int l = c[i], r = c[i + 1];
		if(match[i + 1] == i + 1) r >>= 1;
		if(i == 1) l >>= 1;
		if(r >= l) match[i] = i + 1; else match[i] = i;
		if(match[i] == i + 1){
			for(int j = i + 1; j < n && match[j] == j; ++j){
				int l = c[j], r = c[j + 1];
				if(match[j - 1] == j) l >>= 1;
				if(match[j + 1] == j + 1) r >>= 1;
				if(l > r) break;
				match[j] = j + 1;
			}
		}
	}
	l = c[n], r = c[1];
	if(match[n - 1] == n) l >>= 1;
	if(match[1] == 1) r >>= 1;
	if(r >= l){
		output();
		return;
	}
	
	puts("NIE");
}

}//namespace Program
int main(){
	Program::input();
	Program::solve();
	return 0;
}

/*

*/
