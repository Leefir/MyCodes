#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_begin_=(a);i>=i##_begin_;--i) 
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
const int inf=(int)1e9;
const int INF=0x7fffffff;
const ll linf=1LL<<60;

const int N=(int)3e5;
int n,m,k;
vi g[N+5];
int d[N+5];
void input(){
	scanf("%d %d %d",&n,&m,&k);
	rep(i,0,n){
		g[i].clear();
		d[i]=0;
	}
	rep(i,0,m){
		int u,v;scanf("%d %d",&u,&v);
		--u;--v;
		g[u].pb(v);
		g[v].pb(u);
		++d[u];++d[v];
	}
}
bool disreachable[N+5];
int seq[N+5],q[N+5];
int tot;
struct node{
	int u,d;
	bool operator <(const node &tmp)const{
		return d>tmp.d;
	}
};
priority_queue<node>que;
bool vis[N+5];
void go(int u){
	
	vis[u]=true;
	rep(i,0,sz(g[u])){
		int v=g[u][i];
		disreachable[v]=true;
	}
	
	tot=0;
	int L=0,H=0;
	rep(i,1,n){
		//except 0
		if(disreachable[i])seq[tot++]=i;
		else q[H++]=i;
		disreachable[i]=false;//clear
	}
	
	while(L<H){
		int u=q[L++];
//		printf("queue %d\n",u);
		rep(i,0,sz(g[u])){
			int v=g[u][i];
			disreachable[v]=true;
		}
		
		rep(i,0,tot)if(seq[i]!=-1&&!disreachable[seq[i]]){
			q[H++]=seq[i];
			seq[i]=-1;
		}
		
		//clear
		rep(i,0,sz(g[u])){
			int v=g[u][i];
			disreachable[v]=false;
		}
	}
	rep(i,0,H)vis[q[i]]=true;
}
int count(){
	while(!que.empty())que.pop();
	//except 0 
	rep(i,1,n){
		que.push((node){i,d[i]});
	}
	rep(i,0,n)vis[i]=false;vis[0]=true;
	int res=0;
	while(!que.empty()){
		int u=que.top().u;que.pop();
		if(vis[u])continue;
		++res;
		go(u);
	}
	return res;
}
void solve(){
	if(n-1-d[0]<k){
		puts("impossible");
		return;
	}

	
	rep(i,0,n)disreachable[i]=false;
	
	int cnt=count();
	
	
	if(cnt>k){
		puts("impossible");
		return;
	}
	
	rep(i,0,n)disreachable[i]=false;
	//d[u]<=2*m/n
	int u=0;
	rep(i,0,n)if(d[i]<d[u])u=i;
	rep(i,0,sz(g[u])){
		int v=g[u][i];
		disreachable[v]=true;
	}
	
	tot=0;
	int L=0,H=0;
	rep(i,0,n){
		if(disreachable[i])seq[tot++]=i;
		else q[H++]=i;
		disreachable[i]=false;//clear
	}
	
	while(L<H){
		int u=q[L++];
//		printf("queue %d\n",u);
		rep(i,0,sz(g[u])){
			int v=g[u][i];
			disreachable[v]=true;
		}
		
		rep(i,0,tot)if(seq[i]!=-1&&!disreachable[seq[i]]){
			q[H++]=seq[i];
			seq[i]=-1;
		}
		
		//clear
		rep(i,0,sz(g[u])){
			int v=g[u][i];
			disreachable[v]=false;
		}
	}
	rep(i,0,tot)if(seq[i]!=-1){
		puts("impossible");
		return;
	}
	puts("possible");
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	input();
	solve();
	return 0;
}
