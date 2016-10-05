#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int N_MAX=17;
const int K_MAX=9;
int N,M,KK,K,S;
int mp[N_MAX][N_MAX]={0};
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
short Astar[N_MAX][N_MAX]={0};
struct Snake{
	char headx,heady;
	short step,body;
	bool operator <(const Snake &tmp)const{
		return step+Astar[headx][heady]>tmp.step+Astar[tmp.headx][tmp.heady];
	}
	bool moveable(int d){
		char x=headx+dx[d],y=heady+dy[d];
		if(mp[x][y]==false)return false;
		char tx=headx,ty=heady;
		for(int i=0;i<K-1;i++){
			int t=(body>>(i<<1))&3;
			tx-=dx[t],ty-=dy[t];
			if(tx==x&&ty==y)return false;
		}
		return true;
	}
	void move(int d){
		body=(body<<2|d)&KK;
		headx+=dx[d];heady+=dy[d];
		step++;
	}
}begin;
int dir_f(int x,int y){
	if(x==0&&y==1)return 0;
	if(x==1&&y==0)return 1;
	if(x==0&&y==-1)return 2;
	if(x==-1&&y==0)return 3;
	return -1;
}
int aimx,aimy;
char str[N_MAX][N_MAX];
void input(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++)scanf("%s",str[i]+1);
	K=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++){
			K+=str[i][j]>='1'&&str[i][j]<='9';
			if(str[i][j]=='1')begin.headx=i,begin.heady=j;
			if(str[i][j]=='@')aimx=i,aimy=j;
		}
	K=K-1;
	KK=(1<<(K<<1))-1;
	char tx=begin.headx,ty=begin.heady;
	for(int i=0;i<K;i++){
		char c='0'+i+2;
		for(int j=1;j<=N;j++)
			for(int k=1;k<=M;k++)
				if(str[j][k]==c){
					int x,y;
					x=j;y=k;
					begin.body|=dir_f(tx-x,ty-y)<<(i<<1);
					tx=x;ty=y;
				}
	}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			mp[i][j]=true;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)if(str[i][j]=='#')
			mp[i][j]=false;
}
struct A_star{
	struct node{
		char x,y;
		short step;
	};
	queue<node>Q;
	bool mark[N_MAX][N_MAX];
	void InitAstar(){
		memset(Astar,127,sizeof(Astar));
		memset(mark,0,sizeof(mark));
		while(!Q.empty())Q.pop();
		Q.push((node){aimx,aimy,0});
		while(!Q.empty()){
			node now=Q.front();Q.pop();
			if(mark[now.x][now.y])continue;
			mark[now.x][now.y]=true;
			Astar[now.x][now.y]=now.step;
			for(int i=0;i<4;i++){
				node nxt=now;
				nxt.x+=dx[i];nxt.y+=dy[i];nxt.step++;
				if(mark[nxt.x][nxt.y])continue;
				if(mp[nxt.x][nxt.y]==0)continue;
				Q.push(nxt);
			}
		}
	}
}AS;
bool mark[N_MAX][N_MAX][1<<16]={0};//7929856bool*4
priority_queue<Snake>Q;
//Snake Q[N_MAX*N_MAX*(1<<(2*7))+1000000];//(7929856+1000000)*2int
int bfs(){
	if(begin.headx==aimx&&begin.heady==aimy)return 0;
	begin.step=0;
	Q.push(begin);
	while(!Q.empty()){
		Snake now=Q.top();Q.pop();
		if(mark[now.headx][now.heady][now.body])continue;
		mark[now.headx][now.heady][now.body]=true;
		for(int i=0;i<4;i++){
			Snake nxt=now;
			if(!nxt.moveable(i))continue;
			nxt.move(i);
			if(mark[nxt.headx][nxt.heady][nxt.body])continue;
			if(nxt.headx==aimx&&nxt.heady==aimy)return nxt.step;
			Q.push(nxt);
		}
	}
	return -1;
}
int main(){
	input();
	AS.InitAstar();
	printf("%d\n",bfs());
	return 0;
}
