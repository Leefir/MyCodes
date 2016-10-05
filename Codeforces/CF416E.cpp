#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=500;
const int inf=(int)1e9;
//500 * 1e6 =5e8
int g[N+5][N+5],mp[N+5][N+5];
int n,m;
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)rep(j,0,n){
		if(i==j)g[i][j]=0;
		else g[i][j]=inf;
	}
	rep(i,0,m){
		int u,v,val;
		scanf("%d %d %d",&u,&v,&val);
		--u;--v;
		g[u][v]=g[v][u]=val;
	}
}
void floyd(){
	rep(i,0,n)rep(j,0,n)mp[i][j]=g[i][j];
	rep(k,0,n)rep(i,0,n)rep(j,0,n)
		mp[i][j]=std::min(mp[i][j],mp[i][k]+mp[k][j]);
}
int ans[N+5][N+5];
int in[N+5];
void solve(int s){
	rep(i,0,n)in[i]=0;
	rep(i,0,n)rep(j,0,n)if(i!=j&&g[i][j]!=inf&&mp[s][i]+g[i][j]==mp[s][j])in[j]++;
	rep(i,0,n){
		ans[s][i]=0;
		rep(j,0,n)if(mp[s][j]+mp[j][i]==mp[s][i])ans[s][i]+=in[j];
	}
}
void output(){
	rep(i,0,n)rep(j,i+1,n)printf("%d ",ans[i][j]);
}
int main(){
	input();
	floyd();
	rep(i,0,n)solve(i);
	output();
	return 0;
}
