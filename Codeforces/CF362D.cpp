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

const int N=(int)1e5;
int n,m,p,q,a,b,c;
//undirected graph
//long long for value
int fa[N+5];
ll sum[N+5];
//int get(int u){
//	for(;u!=fa[u];)u=fa[u]=fa[fa[u]];
//	return fa[u];
//}
int get(int u){
	if(u!=fa[u])fa[u]=get(fa[u]);
	return fa[u];
}
void input(){
	scanf("%d %d %d %d",&n,&m,&p,&q);
	
	//init
	rep(i,0,n){
		fa[i]=i;
		sum[i]=0;
	}
	
	//id [ 0 , n )
	rep(i,0,m){
		int val;
		scanf("%d %d %d",&a,&b,&val);
		--a;--b;
		
		int aa=get(a),bb=get(b);
		if(aa!=bb){
			fa[bb]=aa;
			sum[aa]+=sum[bb];
		}
		sum[aa]+=val;
	}
	c=0;
	rep(i,0,n)c+=get(i)==i;
}
struct node{
	int x;
	bool operator <(const node &tmp)const{
		return sum[x]>sum[tmp.x];
	}
};
priority_queue<node>Q;
void solve(){
	puts("YES");
	while(!Q.empty())Q.pop();
	rep(i,0,n)if(get(i)==i)
		Q.push((node){i});
	rep(i,0,c-q){
		int u=Q.top().x;Q.pop();
		int v=Q.top().x;Q.pop();
		u=get(u);v=get(v);
		sum[u]+=sum[v]+min((ll)1e9,sum[u]+sum[v]+1);
		fa[v]=u;
		Q.push((node){u});
		
		printf("%d %d\n",u+1,v+1);
		a=u;b=v;
	}
	p-=c-q;
	rep(i,0,p)printf("%d %d\n",a+1,b+1);
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	input();
	if(c<q||c-q>p||(n==q&&p>0)){
		puts("NO");
		return 0;
	}
	solve();
	return 0;
}
