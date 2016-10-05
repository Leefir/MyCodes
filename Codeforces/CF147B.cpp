#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=300;
const int inf=(int)1e9;
inline int max(int x,int y){
	if(x>y)return x;
	return y;
}
int n,m;
int g[10][N][N],tmp[N][N];
void mul(int a[N][N],int b[N][N]){
	rep(i,0,n)rep(j,0,n){
		tmp[i][j]=-inf;
		rep(k,0,n)tmp[i][j]=max(tmp[i][j],a[i][k]+b[k][j]);
	}
}
void copy(int to[N][N]){
	rep(i,0,n)rep(j,0,n)to[i][j]=tmp[i][j];
}
void input(){
	scanf("%d %d",&n,&m);
	rep(i,0,n)rep(j,0,n)g[0][i][j]=i==j?0:-inf;
	rep(i,0,m){
		int u,v,x,y;
		scanf("%d %d %d %d",&u,&v,&x,&y);
		--u;--v;
		g[0][u][v]=x;g[0][v][u]=y;
	}
}
int now[N][N];
bool chk(int a[N][N]){
	rep(i,0,n)if(a[i][i]>0)return true;
	return false;
}
int find(){
	int ans=0;
	rep(i,0,n)rep(j,0,n)now[i][j]=i==j?0:-inf;
	for(int i=8;i>=0;--i){
		mul(now,g[i]);
		if(!chk(tmp)){
			ans+=1<<i;
			copy(now);
		}
	}
//	printf("ans %d\n",ans);
	if(ans>n)return 0;
	return ans+1;
}
void print(int a[N][N]){
	rep(i,0,n){
		rep(j,0,n)printf("%d ",a[i][j]);
		puts("");
	}
}
int main(){
	input();
	for(int i=1;i<=8;++i){
		mul(g[i-1],g[i-1]);
		copy(g[i]);
	}
//	puts("YES");
	printf("%d\n",find());
	return 0;	
}
