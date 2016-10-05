#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int M=10000;
const int oo=1e9;
int head[M],mark[M],fa_edge[M],pre[M],Q[M*10];
int dis[M],flow[M];
int tot,src,dest;
struct node {
    int to,cap,cost,next;
} edge[M*6];
inline void rd(int &res){
    char c;res=0;
    while(c=getchar(),!isdigit(c));
    do{
        res=(res<<1)+(res<<3)+(c^48);
    }while(c=getchar(),isdigit(c));
}
inline void add(int a, int b, int c, int d) {
    edge[tot].to = b, edge[tot].cap = c, edge[tot].cost = d, edge[tot].next = head[a], head[a] = tot++;
    edge[tot].to = a, edge[tot].cap = 0, edge[tot].cost = -d, edge[tot].next = head[b], head[b] = tot++;
}
bool SPFA() {
    int i, j, k, top, y, L, H;
    for (i = 0; i <= dest; i++)mark[i] = 0, dis[i] = oo;
    mark[src] = 1, dis[src] = 0;
    top = 0, flow[src] = oo;
    L = H = 0;
    Q[H++] = src;
    while (L < H) {
        k = Q[L++];
        mark[k] = 0;
        for (i = head[k]; i != -1; i = edge[i].next) {
            y = edge[i].to;
            if (edge[i].cap > 0 && dis[y] > dis[k] + edge[i].cost) {
                dis[y] = dis[k] + edge[i].cost;                
                pre[y] = k;
                fa_edge[y] = i;
                flow[y] = min(flow[k], edge[i].cap);
                if (!mark[y]) {
                    mark[y] = 1;
                    Q[H++] = y;
                }
            }
        }
    }
    return (dis[dest] != oo);
}

int maxflow_mincost() {
    int ans = 0, x;
    while (SPFA()) {
        ans += dis[dest] * flow[dest];
        x = dest;
        while (x != src) {
            edge[fa_edge[x]].cap -= flow[dest];
            edge[fa_edge[x]^1].cap += flow[dest];
            x = pre[x];
        }
    }
    return ans;
}
int N,m;
void input(){
	scanf("%d %d",&N,&m);
	src=0;dest=N+1;
	for(int i=0;i<=dest;i++)head[i]=-1;
	tot=0;
	for(int i=0;i<m;i++){
		int u,v,val;
		scanf("%d %d %d",&u,&v,&val);
		add(u,v,1,val);
		add(v,u,1,val);
	}
	add(src,1,2,0);
	add(N,dest,2,0);
}
int main(){
    input();
    printf("%d\n",maxflow_mincost());
    return 0;
}
