#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=300;
const int M=50000;
std::vector<int>g[N+5];
int a[N+5],b[N+5];
bool mp[N+5][N+5];
int n,v,m;
bool input(){
	scanf("%d %d %d",&n,&v,&m);
	
	rep(i,0,n)scanf("%d",&a[i]);
	rep(i,0,n)scanf("%d",&b[i]);
	
	rep(i,0,n)g[i].clear();
	rep(i,0,n)rep(j,0,n)mp[i][j]=i==j;
	rep(i,0,m){
		int u,v;
		scanf("%d %d",&u,&v);
		--u;--v;
		
		mp[u][v]=mp[v][u]=true;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	rep(k,0,n)rep(i,0,n)rep(j,0,n)mp[i][j]|=mp[i][k]&&mp[k][j];
	
	rep(i,0,n){
		long long sum=0;
		rep(j,0,n)if(mp[i][j])sum+=a[j]-b[j];
		if(sum!=0)return false;
	}
	return true;
}
struct Transfusion{
	Transfusion(){}
	Transfusion(int _u,int _v,int _d):u(_u),v(_v),d(_d){}
	int u,v,d;
};
std::vector<Transfusion>vec;
void output(){
	printf("%d\n",(int)vec.size());
	rep(i,0,(int)vec.size())
		printf("%d %d %d\n",vec[i].u+1,vec[i].v+1,vec[i].d);
}
int stk[N+5],top;
bool vis[N+5];
bool dfs(int u,int aim){
	stk[++top]=u;
	vis[u]=true;
	if(u==aim)return true;
	int mem=top;
	rep(i,0,(int)g[u].size()){
		int v=g[u][i];
		if(!vis[v]&&mp[v][aim]){
//		printf("%d -> %d\n",u+1,v+1);
			if(dfs(v,aim))return true;
			else top=mem;
		}
	}
	return false;
}
int t[N+5];
void run(int u,int v,int delta){
	stk[top=0]=-1;
	rep(i,0,n)vis[i]=false;
	dfs(u,v);
	for(int i=top;i>1;--i){
		int x=stk[i-1],y=stk[i];
//		printf("stk %d %d\n",x+1,y+1);
		if(a[x]>=delta){
			a[x]-=delta;
			a[y]+=delta;
			t[x]=0;
			vec.push_back(Transfusion(x,y,delta));
		}else{
			a[y]+=a[x];
			vec.push_back(Transfusion(x,y,a[x]));
			t[x]=delta-a[x];
			a[x]=0;
		}
	}
	for(int i=1;i<top;++i){
		int x=stk[i],y=stk[i+1];
		if(t[x]){
			a[x]-=t[x];
			a[y]+=t[x];
			vec.push_back(Transfusion(x,y,t[x]));
		}
	}
}
void solve(){
	vec.clear();
	
	rep(i,0,n)if(a[i]>b[i]){
		rep(j,0,n)if(a[j]<b[j]&&mp[i][j]){
			int delta=std::min(a[i]-b[i],b[j]-a[j]);
			run(i,j,delta);
			if(a[i]==b[i])break;
		}
	}
	
	output();
}
int main(){
	if(!input())puts("NO");
	else solve();
	return 0;
}
