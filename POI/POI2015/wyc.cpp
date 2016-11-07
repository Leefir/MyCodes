#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b) - 1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)

namespace Program{
typedef long long ll;
typedef double db;
bool flag;
int n, m; 
ll K; //不能和矩阵里的循环变量冲突！ 
struct Matrix{
	ll a[120][120]; //28,800 ints
	Matrix(){memset(a, 0, sizeof a);}
	void clear(){
		memset(a, 0, sizeof a);
	}
	Matrix operator +(const Matrix &tmp)const{
		flag = false;
		Matrix res;
		rep(i, 0, n*3) rep(j, 0, n*3)
			if((res.a[i][j] = a[i][j] + tmp.a[i][j]) >= K){flag = true; return res;}
		return res;
	}
	Matrix operator *(const Matrix &tmp)const{
		flag = false;
		Matrix res;
		rep(i, 0, n*3) rep(j, 0, n*3){
			res.a[i][j] = 0;
			rep(k, 0, n*3){
				if(tmp.a[k][j] != 0 && a[i][k] >= K / tmp.a[k][j]){flag = true; return res;}
				if((res.a[i][j] += a[i][k] * tmp.a[k][j]) >= K){flag = true; return res;}
			}
		}
		return res;
	}
	bool sum(){
		ll res = 0;
		rep(i, 0, n) rep(j, 0, n){ //只统计左上角
			if((res += a[i][j]) >= K) return true;
		}
		return false;
	}
}G[62], S[62];
void input(){
	cin >> n >> m >> K; //k long long
	G[0].clear();
	rep(i, 0, n) G[0].a[i + n*2][i + n] = 1, G[0].a[i + n][i] = 1;
	rep(i, 0, m){
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		--u; --v;
		G[0].a[u][v + (c-1)*n]++;
	}
}
int B;
ll ans;
void prepare(){
	S[0] = G[0];
	B = 1;
	for(B = 1; B <= 60; ++B){
		G[B] = G[B-1] * G[B-1]; if(flag){ans = 1LL<<B; return;}
		S[B] = G[B-1] * S[B-1] + S[B-1]; if(flag){ans = (1LL<<B)-1; return;}
	}
}
void solve(){
	ll now = 0;
	Matrix t; t.clear();
	per(i, 0, B){
		Matrix tmp = t * G[i];
		if(flag){ans = min(ans, now + (1LL<<i)); continue;}
		tmp = tmp + S[i];
		if(flag || tmp.sum()){ans = min(ans, now + (1LL<<i)); continue;}
		now += 1LL<<i;
		t = tmp;
	}
}
void Main(){
	input();
	ans = 1LL<<62;
	prepare();
	if(G[1].sum()){ puts("1"); return;}
	solve();
	if(ans == (1LL<<62)) ans = -1;
	cout << ans << endl;
}

}

int main(){
	Program::Main();
	return 0;
}

/*
带权有向图
可能有重边（要算作不同方案），无自环 
不存在，输出-1。
*/
