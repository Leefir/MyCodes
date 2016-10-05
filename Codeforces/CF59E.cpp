#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=3000;
const int M=20000;
const int K=(int)1e5;
typedef long long ll;
typedef std::pair<int,int>pii;
std::set<ll>st;
std::vector<int>g[N+5];
pii edge[M*2+5];
int n,m,k;
void input(){
	scanf("%d %d %d",&n,&m,&k);
	
	//read edges
	rep(i,0,n)g[i].clear();
	rep(i,0,m){
		int u,v;scanf("%d %d",&u,&v);--u;--v;
		edge[i*2]=pii(u,v);g[u].push_back(i*2);
		edge[i*2+1]=pii(v,u);g[v].push_back(i*2+1);
	}
	
	//read constraints
	st.clear();
	rep(i,0,k){
		int a,b,c;scanf("%d %d %d",&a,&b,&c);--a;--b;--c;
		st.insert((ll)a*N*N+b*N+c);
	}
}
std::queue<int>que;
int dis[M*2+5],pre[M*2+5];
const int inf=(int)1e9;
int dest;
#define sz(x) ((int)(x).size())
void Dijkstra(){
	rep(i,0,m*2)dis[i]=inf;
	while(!que.empty())que.pop();
	dest=-1;
	
	//start from 0
	rep(i,0,sz(g[0])){
		int eid=g[0][i];
		dis[eid]=1;
		que.push(eid);
	}
	
	while(!que.empty()){
		int eid=que.front();que.pop();
		
		int u=edge[eid].second;
		if(u==n-1){
			dest=eid;
			return;
		}
		ll h=(ll)edge[eid].first*N*N+u*N;
		rep(i,0,sz(g[u])){
			int x=g[u][i];
			int v=edge[x].second;
			if(st.find(h+v)==st.end()){
				//an accessiable edge
				if(dis[x]==inf){
					dis[x]=dis[eid]+1;
					pre[x]=eid;
					que.push(x);
				}
			}
		}
	}
}
int stk[M*2+5];
void output(){
	if(dest==-1)puts("-1");
	else{
		//from edge(dest)
		printf("%d\n",dis[dest]);
		int top=0;
		for(;;){
			stk[++top]=edge[dest].second;
			if(edge[dest].first==0){
				stk[++top]=0;
				break;
			}
			dest=pre[dest];
		}
		while(top)printf("%d%c",stk[top--]+1," \n"[top==0]);
	}
}
int main(){
	input();
	Dijkstra();
	output();
	return 0;
}
