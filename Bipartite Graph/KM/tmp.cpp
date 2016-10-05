#include <cstdio>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=300;
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
inline int max(int x,int y){
	if(x>y)return x;
	return y;
}
struct Bipartite_Graph{
	//complete bipartite graph!
	static const int V=N;
	static const int INF=0x7fffffff;
	int w[V+5][V+5];
	int X[V+5],Y[V+5];
	bool visx[V+5],visy[V+5];
	int n;
	
	void init(){
		rep(x,0,n){
			X[x]=-INF;
			rep(y,0,n)X[x]=max(X[x],w[x][y]);
		}
		rep(y,0,n){
			Y[y]=0;
			match[y]=-1;
		}
	}
	int match[V+5];//match[Yi]=Xj
	bool find(int x){
		visx[x]=true;
		rep(y,0,n)if(X[x]+Y[y]==w[x][y]&&!visy[y]){
			visy[y]=true;
			if(match[y]==-1||find(match[y])){
				match[y]=x;
				return true;
			}
		}
		return false;
	}
	void change(){
		int delta=INF;
		rep(x,0,n)if(visx[x])
			rep(y,0,n)if(!visy[y])
				delta=min(delta,X[x]+Y[y]-w[x][y]);
		rep(i,0,n){
			if(visx[i])X[i]-=delta;
			if(visy[i])Y[i]+=delta;
		}
	}
	int calc(){
		int res=0;
		rep(i,0,n)res+=w[match[i]][i];
		return res;
	}
	int KM(){
		init();
		rep(i,0,n){
			while(true){
				rep(j,0,n)visx[j]=visy[j]=false;
				if(find(i))break;
				change();
			}
		}
		return calc();
	}
}bpt;
void Main(){
	rep(i,0,bpt.n)rep(j,0,bpt.n)scanf("%d",&bpt.w[i][j]);
	printf("%d\n",bpt.KM());
}
int main(){
	while(scanf("%d",&bpt.n)!=EOF)Main();
	return 0;
}
