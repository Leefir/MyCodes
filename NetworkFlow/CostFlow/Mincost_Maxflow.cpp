//SDOI2010 starrace  submitted in free 1232
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int M=805*2;
const int oo=0x7fffffff;
int head[M],mark[M],fa_edge[M],pre[M],Q[M*100];
int dis[M],flow[M];
int tot,src,dest;
struct node {
    int to,cap,cost,next;
} edge[(M*2+15005)*2];
inline void Rd(int &res){
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
                flow[y] = min(flow[k],edge[i].cap);
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
int N;
void input(){
    int m;
    Rd(N);Rd(m);
    int station=N*2+1;
    src=N*2+2,dest=N*2+3;
    for(int i=1;i<=dest;i++)head[i]=-1;
    for(int i=1;i<=N;i++){
        add(src,i,1,0);
        add(i+N,dest,1,0);
    }
    for(int i=1;i<=N;i++){
        int val;Rd(val);
        add(i,station,oo,0);
        add(station,i+N,oo,val);
    }
    for(int i=0;i<m;i++){
        int u,v,val;Rd(u);Rd(v);Rd(val);
        if(u>v)swap(u,v);
        add(u,v+N,oo,val);
    }
}
int main(){
	input();
    printf("%d\n",maxflow_mincost());
	return 0;
}