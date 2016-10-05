#include <cstdio>
#include <cstring>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
using namespace std;
const int N=305;
int w[N][N];
int X[N],Y[N];
int visx[N],visy[N];
int n;
int match[N];//match[Yi]=Xj
int find(int);
int KM();
int main(){
	while(~scanf("%d",&n)){
		rep(i,0,n)rep(j,0,n)scanf("%d",&w[i][j]);
		printf("%d\n",KM());
	}
	return 0;
}
int find(int x){
	visx[x]=1;
	rep(y,0,n)if(!visy[y]&&X[x]+Y[y]==w[x][y]){
		visy[y]=1;
		if(match[y]==-1||find(match[y])){
			match[y]=x;
			return 1;
		}
	}
	return 0;
}
int KM(){
	rep(x,0,n){
		X[x]=0x80000000;
		Y[x]=0;
		match[x]=-1;
		rep(y,0,n)if(X[x]<w[x][y])X[x]=w[x][y];
	}
	rep(i,0,n){
//		rep(j,0,n)visx[j]=visy[j]=false;
		while(true){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(find(i))break;
				int delta=0x7fffffff;
				rep(x,0,n)if(visx[x])
					rep(y,0,n)if(!visy[y]&&delta>X[x]+Y[y]-w[x][y])
						delta=X[x]+Y[y]-w[x][y];
				rep(i,0,n){
					if(visx[i])X[i]-=delta;
					if(visy[i])Y[i]+=delta;
				}
		}
	}
	int res=0;
	rep(i,0,n)if(match[i]!=-1)res+=w[match[i]][i];
	return res;
}
