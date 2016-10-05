#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=100;
const int B=7;
typedef std::pair<int,int> pii;
int n;
pii edge[N+5];
std::vector<int>g[B+5];
int d[B+5];
bool exist[B+5];
bool loop;
bool input(){
	scanf("%d",&n);
	rep(i,0,B){
		g[i].clear();
		d[i]=0;
		exist[i]=false;
	}
	
	rep(i,0,n){
		int u,v;scanf("%d %d",&u,&v);
		edge[i]=pii(u,v);
		
		d[u]++;d[v]++;
		exist[u]=exist[v]=true;
		
		g[u].push_back(i);
		g[v].push_back(i);
	}
	
	int cnt=0;
	rep(i,0,B)cnt+=d[i]&1;
	loop=cnt==0;
	
	if(cnt==2||cnt==0)return true;
	
	return false;
}
int stk[N+5],top;
bool flag[N+5];
bool vis[N+5];
void dfs(int u){
	rep(i,0,(int)g[u].size()){
		int e=g[u][i];
		if(vis[e])continue;
		int v=edge[e].first^edge[e].second^u;
		
		vis[e]=true;dfs(v);
		
		stk[++top]=e;
		if(u==edge[e].first)flag[top]=true;
		else flag[top]=false;
	}
}
void output(){
	if(top!=n){
		puts("No solution");
		return;
	}
	while(top){
		printf("%d %c\n",stk[top]+1,flag[top]?'+':'-');
		top--;
	}
}
void solve(){
	top=0;
	rep(i,0,n)vis[i]=false;
	
	if(loop)rep(i,0,B){
		if(exist[i]){
			dfs(i);
			break;
		}
	}else
	rep(i,0,B)if(d[i]&1){
		dfs(i);
		break;
	}
	output();
}
int main(){
	if(!input())puts("No solution");
	else solve();
	return 0;
}
