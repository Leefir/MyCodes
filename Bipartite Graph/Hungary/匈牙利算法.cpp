#include<cstdio>
const int M=1005;
struct Edge{
	int to,nxt;
}edge[M<<1];
int T=0,head[M],n,m;
void add(int s,int t){
	edge[T]=(Edge){t,head[s]};
	head[s]=T++;
}
bool visit[M];
int match[M];
bool find(int v){
	for(int i=head[v];~i;i=edge[i].nxt){
		int to=edge[i].to;
		if(visit[to]) continue;
		visit[to]=1;
		if(!match[to]||find(match[to])){
			match[to]=v;
			return true;
		}
	}
	return false;
}
void init(){
	for(int i=0;i<n;i++)
		visit[i]=0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		head[i]=-1;
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(i,a);add(i,b);
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		init();
		if(find(i)) ans++;
		else break;//题目特定，原算法没有。 
	}
	printf("%d\n",ans);
	return 0;
}
