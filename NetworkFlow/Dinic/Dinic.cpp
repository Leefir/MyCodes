#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int SIZE=15;
const int INF=0x7fffffff;
const int N=105;
const int V=N*N+N+10;
const int E=V*3;
struct Edge{
    int to,cap;
}G[E<<1];
int head[V],nxt[E<<1],work[E<<1];
int dist[V]={0},Q[V];
int Gsz=0;
inline void add_edge(int u,int v,int c){
    G[Gsz]=(Edge){v,c};nxt[Gsz]=head[u];head[u]=Gsz;Gsz++;
    G[Gsz]=(Edge){u,0};nxt[Gsz]=head[v];head[v]=Gsz;Gsz++;
}
int source,destination;
bool BFS(){
    int L=0,H=0;
    memset(dist,-1,sizeof(dist));
    dist[source]=0;
    Q[H++]=source;
    while(L<H){
        int now=Q[L++];
        for(int i=head[now];~i;i=nxt[i]){
            int nxt=G[i].to;
            if(dist[nxt]==-1&&G[i].cap){
                dist[nxt]=dist[now]+1;
                Q[H++]=nxt;
            }
        }
    }
    return dist[destination]>=0;
}
int dfs(int u,int flow){
    if(u==destination||flow==0)return flow;
    int res=0;
    for(int &i=work[u];~i;i=nxt[i])if(G[i].cap>0&&dist[G[i].to]==dist[u]+1){
        int tmp=dfs(G[i].to,min(G[i].cap,flow));
        if(tmp){
            G[i].cap-=tmp;
            G[i^1].cap+=tmp;
            res+=tmp;
            flow-=tmp;
            if(flow==0)break;
        }
    }
    return res;
}
int Dinic(){
    int flow=0;
    while(BFS()){
        for(int i=0;i<=destination;i++)work[i]=head[i];
        flow+=dfs(source,INF);
    }
    return flow;
}int a[N],b[N],w[N][N],id_edge[N][N],id_node[N],id_num[15];
char str[N];
void solve(){
    int n;scanf("%d",&n);
    scanf("%s",str);
    for(int i=0;i<10;++i){
        scanf("%d%d",&a[i],&b[i]);
    }
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            scanf("%d",&w[i][j]);
    source=0;
    destination=0;
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
            id_edge[i][j]=++destination;
    for(int i=0;i<n;++i){
        str[i]-='0';
        id_node[i]=++destination;
    }
    for(int i=0;i<10;++i)
        id_num[i]=++destination;
    ++destination;
    for(int i=0;i<=destination;i++)head[i]=-1;
    Gsz=0;
    int tot=0;
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j){
            tot+=w[i][j]+w[j][i];
            add_edge(source,id_edge[i][j],w[i][j]+w[j][i]);
            add_edge(id_edge[i][j],id_node[i],INF);
            add_edge(id_edge[i][j],id_node[j],INF);
        }
    for(int i=0;i<n;++i){
        add_edge(id_node[i],id_num[(int)str[i]],INF);
        add_edge(id_node[i],destination,a[(int)str[i]]);
    }
    for(int i=0;i<10;++i)add_edge(id_num[i],destination,b[i]-a[i]);
    printf("%d\n",tot-Dinic());
}
int main(){
    int cas,kase=0;
    for(scanf("%d",&cas);cas--;){
        printf("Case #%d: ",++kase);
        solve();
    }
    return 0;
}
