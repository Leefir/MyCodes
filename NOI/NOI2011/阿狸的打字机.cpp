#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
#define per(i, a, b) for(int i = (b)-1, i##_BEGIN_ = a; i >= i##_BEGIN_; --i)
 
namespace Program{
 
const int N = (int)1e5;
inline void read(int &res){
    char c; res = 0;
    while(c = getchar(), c < '0' || c > '9');
    do res = (res*10) + (c^48);
    while(c = getchar(), c >= '0' && c <= '9');
}
char dat[N+5]; int siz;
int n, m;
int x[N+5], y[N+5];
vector<int> q[N+5];
int ans[N+5];
void input(){
    scanf("%s", dat); siz = strlen(dat);
    scanf("%d", &m);
    rep(i, 1, n+1) q[i].clear();
    rep(i, 0, m){
        read(x[i]); read(y[i]);
        q[y[i]].push_back(i);
    }
}
struct BinaryIndexedTree{
    int a[N+5];
    int n;
    void init(const int _n){
        n = _n;
        rep(i, 1, n+1) a[i] = 0;
    }
    void update(int pos, int add){
//      printf("update %d %d\n", pos, add);
        for(int i = pos; i <= n; i += i&-i)
            a[i] += add;
    }
    int query(int pos){
        int res = 0;
        for(int i = pos; i > 0; i -= i&-i)
            res += a[i];
        return res;
    }
    int sum(int l, int r){
//      printf("sum [%d, %d]\n", l, r);
        return query(r) - query(l-1);
    }
}bit;
struct AhoCorasickAutomaton{
    int ch[N+5][26], fa[N+5];
    vector<int> id[N+5]; int pos[N+5];
    //root: 1
    int allc;
    int que[N+5];
    int fail[N+5];
    vector<int> son[N+5];
    void bfs(){
        int L = 0, H = 0;
        que[H++] = 1; fail[1] = 0;
        rep(i, 0, allc+1) son[i].clear();
        rep(i, 0, 26) ch[0][i] = 1;
        while(L < H){
            int cur = que[L++];
            rep(i, 0, 26){
            	if(ch[cur][i]){
            		son[cur].push_back(ch[cur][i]);
            		fail[ch[cur][i]] = ch[fail[cur]][i];
            		que[H++] = ch[cur][i];
            	}else ch[cur][i] = ch[fail[cur]][i];
            }
        }
        //rep(i, 1, allc+1) printf("fail[%d] %d\n", i, fail[i]);
    }
    vector<int> g[N+5];
    int dfn, pre[N+5], post[N+5];
    void dfs(int u){
        pre[u] = ++dfn;
        rep(i, 0, (int)g[u].size()) dfs(g[u][i]);
        post[u] = dfn;
    }
    void build(){
        memset(ch, 0, sizeof ch);
        memset(fa, 0, sizeof fa);
        allc = 1; n = 0;
        int cur = 1; 
        rep(i, 0, siz){
            if(dat[i] == 'P') id[cur].push_back(++n), pos[n] = cur;
            else if(dat[i] == 'B') cur = fa[cur];
            else{
                int c = dat[i]-'a';
                if(ch[cur][c] == 0) ch[cur][c] = ++allc, fa[allc] = cur, id[allc].clear();
                cur = ch[cur][c];
            }
        }
        bfs();
        rep(i, 1, allc+1) g[i].clear();
        rep(i, 2, allc+1) g[fail[i]].push_back(i);
        dfn = 0; dfs(1);
    }
    void rec(int u){
        bit.update(pre[u], 1);
        rep(i, 0, (int)id[u].size()){
            int Y = id[u][i];
            rep(j, 0, (int)q[Y].size()){
                int qid = q[Y][j];
                int X = x[qid]; assert(y[qid] == Y);
                ans[qid] = bit.sum(pre[pos[X]], post[pos[X]]);
            }
        }
        rep(i, 0, (int)son[u].size()) rec(son[u][i]);
        //rep(i, 0, 26) if(ch[u][i]) rec(ch[u][i]);
        bit.update(pre[u], -1);
    }
    void solve(){
        bit.init(dfn);
        rec(1);
    }
}acm;
void output(){
    rep(i, 0, m) printf("%d\n", ans[i]);
}
void Main(){
    input();
     
    acm.build();
    acm.solve();
    output();
}
 
} //namespace Program
 
/*
 
*/
int main(){
    Program::Main();
    return 0;
}
