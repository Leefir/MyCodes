#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{

const int M = 600;
typedef long long ll;
typedef vector<ll> vl;
#define pb(x) push_back(x)
#define sz(x) (int)((x).size())
int m; ll a[M+5];
void input(){
	scanf("%d", &m); 
	rep(i, 0, m) cin >> a[i];
}
const int S = (int)1e6;
const int PN = 78498;
int prime[PN+5], primetot;
bool isprime[S+5];
void prepare(){
	rep(i, 2, S+1) isprime[i] = true;
	primetot = 0;
	rep(i, 2, S+1) if(isprime[i]){
		prime[primetot++] = i;
		for(int j=i+i; j <= S; j+=i) isprime[j] = false;
	}
}
vl vec, uni; //两个素数之积 或 一个素数 
int cnt[PN+5];
void decomposition(int id){
	ll x = a[id];
	rep(i, 0, primetot){
		int p = prime[i];
		while(x%p == 0){
			x /= p;
			cnt[i]++;
		}
	}
	if(x > 1) vec.pb(x);
}
int mx, ans; //ans为非凡 素 因子个数 
inline void modify(int c){
	if(c > mx){mx = c; ans = 1;}
	else if(c == mx) ++ans;
}
void dealSmall(){
	rep(i, 0, primetot) modify(cnt[i]);
}
ll addmod(ll b, ll k, ll mod){
	ll res = 0;
	while(k){
		if(k&1) res = (res+b)%mod;
		b = (b+b)%mod;
		k>>=1;
	}
	return res;
}
ll powmod(ll b, ll mod){
	b %= mod;
	ll k = mod-1;
	ll res = 1;
	while(k){
		if(k&1) res = addmod(res, b, mod);
		b = addmod(b, b, mod);
		k>>=1;
	}
	return res;
}
bool judge(ll x){ //判断x是否为素数 
	rep(i, 0, 10){
		int t = rand()+233;
		if(powmod(t, x) != 1) return false;
	}
	return true;
}
ll gcd(ll x, ll y){
	if(x == 0) return y;
	return gcd(y%x, x);
}
#define all(x) (x).begin(), (x).end()
vl he;
void dealHuge(){
	uni.clear(); 
	rep(i, 0, sz(vec)) rep(j, 0, sz(vec)){
		ll tmp = gcd(vec[i], vec[j]);
		if(tmp != 1) uni.pb(tmp);
	}
	sort(all(uni)); uni.erase(unique(all(uni)), uni.end());
	he.clear();
	rep(i, 0, sz(uni)){
		bool ok = true;
		rep(j, 0, sz(uni))
			if(uni[j] != uni[i] && uni[i] % uni[j] == 0){ ok = false; break;} //uni[i]的真因子在了
		if(ok) he.pb(uni[i]);
	} 
	rep(i, 0, sz(he)){
//		printf("he %lld\n", he[i]);
		ll sq = (ll)sqrt(he[i]);
		int c = 0;
		rep(j, 0, sz(vec)){
			ll tmp = vec[j];
			while(tmp%he[i] == 0){ //如果uni[i]为一个素数的平方，若因gcd进入了uni，则当前c不会成为mx 
				tmp /= he[i];
				++c;
			}
		}
		if(sq * sq == he[i]){ //sq为一个大素数 
			c *= 2;
			modify(c);
		}else if(judge(he[i])){ //uni[i]为大素数
		 	modify(c);
		}else{ //he[i]为两个不同素数乘积 
			modify(c); modify(c);
		}
	}
	//也可能是一个大素数的平方 
}
int num[1000], len;
int tmp[1000];
void print(int x){
	//2^x - 1    2^x末尾非0（无因子5） 
	memset(num, 0, sizeof num); len = 1; num[0] = 1;
	while(x--){
		rep(i, 0, len+1) tmp[i] = 0;
		rep(i, 0, len){
			tmp[i] += num[i] * 2;
			if(tmp[i] >= 10){
				tmp[i] -= 10;
				tmp[i+1]++;
			}
		}
		if(tmp[len] != 0) len++;
		rep(i, 0, len) num[i] = tmp[i];
	}
	num[0]--;
	per(i, 0, len) putchar(num[i]+'0');
}
void Main(){
	input();
	prepare();
	vec.clear(); 
	memset(cnt, 0, sizeof cnt);
	rep(i, 0, m) decomposition(i);
	mx = -1; ans = 0;
	dealSmall();
	dealHuge();
	//先统计非凡素因子，mx已定
	printf("%d\n", mx);
	print(ans);
}

} //namespace Program

/*

*/
int main(){
	srand(time(NULL));
	Program::Main();
	return 0;
}

