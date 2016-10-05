//HNOI2014 frame  submitted in free 1173
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf=1e9;
const int INF=0x7fffffff;
inline void Rd(int &res){
	char c;res=0;
	while(c=getchar(),!isdigit(c));
	do{
		res=(res<<1)+(res<<3)+(c^48);
	}while(c=getchar(),isdigit(c));
}
inline void chk_min(int &x,int y){
	if(x>y)x=y;
}
inline void chk_max(int &x,int y){
	if(x<y)x=y;
}
typedef pair<int,int>pr;
const int SIZE=75;
int N;
int A[SIZE][SIZE],B[SIZE][SIZE];
void input(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			Rd(A[i][j]);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			Rd(B[i][j]);
}
struct Stack{
	int element[SIZE*2];
	int sz;
	Stack(){sz=0;}
	void clear(){sz=0;}
	void push(int x){
		element[++sz]=x;
	}
	int top(){
		return element[sz];
	}
	void pop(){
		sz--;
	}
	bool empty(){
		return sz<=0;
	}
}stk;
int w[SIZE][SIZE];
int U[SIZE],V[SIZE];
void init(){
	for(int i=1;i<=N;i++){
		U[i]=-INF;
		for(int j=1;j<=N;j++)
			chk_max(U[i],w[i][j]);
	}
	for(int i=1;i<=N;i++)
		V[i]=0;
}
bool visited[2][SIZE]={0};
void clear_mark(){
	while(!stk.empty()){
		int x=stk.top();stk.pop();
		visited[x&1][x>>1]=false;
	}
}
int umatch[SIZE]={0},vmatch[SIZE]={0};
bool find(int u){
	visited[0][u]=true;
	stk.push(u<<1);
	for(int v=1;v<=N;v++)if(U[u]+V[v]==w[u][v]&&!visited[1][v]){
		visited[1][v]=true;
		stk.push(v<<1|1);
		if(!vmatch[v]||find(vmatch[v])){
			vmatch[v]=u;
			umatch[u]=v;
			return true;
		}
	}
	return false;
}
void change(){
	int delta=INF;
	for(int i=1;i<=N;i++)if(visited[0][i]){
		for(int j=1;j<=N;j++)if(!visited[1][j]){
			chk_min(delta,U[i]+V[j]-w[i][j]);
		}
	}
	while(!stk.empty()){
		int x=stk.top();stk.pop();
		if(x&1)V[x>>1]+=delta;
		else U[x>>1]-=delta;
		visited[x&1][x>>1]=false;
	}
}
int calc(int x[SIZE][SIZE]){
	int res=0;
	for(int i=1;i<=N;i++){
		res+=x[i][umatch[i]];
//		printf("%d - %d\n",i,umatch[i]);
//		printf("x %d\n",x[i][umatch[i]]);
	}
//	printf("%d\n",res);
	return res;
}
void KM(){
	init();
	for(int i=1;i<=N;i++){
		while(!find(i))change();
		clear_mark();
	}
}
void clear(){
	//clear match
	for(int i=1;i<=N;i++)
		vmatch[i]=umatch[i]=0;
}
int ans=INF;
pr begin(int x[SIZE][SIZE]){
	pr res;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			w[i][j]=-x[i][j];
	KM();
	res.first=calc(A);res.second=calc(B);
	chk_min(ans,res.first*res.second);
	clear();
	return res;
}
void work(pr x,pr y){
	int lA=-(y.second-x.second),lB=y.first-x.first;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			w[i][j]=lA*A[i][j]+lB*B[i][j];
	KM();
	pr c;c.first=calc(A);c.second=calc(B);
//	printf("c %d %d\n",c.first,c.second);
	chk_min(ans,c.first*c.second);
	clear();
	int lC=-(lA*x.first+lB*x.second);
	int dis=lA*c.first+lB*c.second+lC;
//	printf("dis %d\n",dis);
	if(dis<=0)return;
	work(x,c);work(c,y);
}
void solve(){
	input();
	ans=INF;
	//(70*200)^2=196,000,000
	pr a,b;
	a=begin(A),b=begin(B);
//	printf("a %d %d\n",a.first,a.second);
//	printf("b %d %d\n",b.first,b.second);
//	printf("ans %d\n",ans);
//	chk_min(ans,a.first*a.second);
//	chk_min(ans,b.first*b.second);
//	printf("ans %d\n",ans);
//	work(a,b);
	work(b,a);
	printf("%d\n",ans);
	clear();
}
int main(){
	int cas;
	scanf("%d",&cas);
	while(cas--)solve();
	return 0;
}