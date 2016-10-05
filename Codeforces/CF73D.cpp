#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=(int)1e6;
int n,m,k;
std::vector<int>g[N+5];
void input(){
	scanf("%d %d %d",&n,&m,&k);
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v;
		scanf("%d %d",&u,&v);
		--u;--v;
		
		g[u].push_back(v);
		g[v].push_back(u);
	}
}
bool vis[N+5];
int cnt;
void dfs(int u){
	vis[u]=true;
	cnt++;
	rep(i,0,(int)g[u].size()){
		int v=g[u][i];
		if(!vis[v])dfs(v);
	}
}
void solve(){
	rep(i,0,n)vis[i]=false;
	
	int c=0,t=0;
	rep(i,0,n)if(!vis[i]){
		c++;
		cnt=0;dfs(i);
		t+=std::min(cnt,k);
	}
	if(k==1)printf("%d\n",std::max(c-2,0));
	else printf("%d\n",std::max(c-t/2-1,0));
}
int main(){
	input();
	solve();
	return 0;
}
