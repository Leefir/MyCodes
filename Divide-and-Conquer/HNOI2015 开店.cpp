#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = a, i##_END_ = b; i < i##_END_; ++i)
namespace Program{

const int N = 150000;
const int Q = 200000;
typedef long long ll;
typedef pair<int, ll> pil;
//边权 1 <= c <= 1000
//n<=150000,Q<=200000

template <typename Tp>inline void read(Tp &res){
    char c;res=0;
    while(c=getchar(),!isdigit(c));
    do res=(res<<1)+(res<<3)+(c^48);
    while(c=getchar(),isdigit(c));
}
template <typename Tp>void print_positive(Tp x){
    if(x==0)return;
    print_positive(x/10);
    putchar(x%10^48);
}
template <typename Tp>inline void print(Tp x){
    if(x==0)putchar('0');
    else if(x<0)putchar('-'),print_positive(-x);
    else print_positive(x);
}

//graph
struct Edge{
	int to, val, nxt;
	Edge(){}
	Edge(int _to, int _val, int _nxt): to(_to), val(_val), nxt(_nxt){}
}edge[N * 2 + 5];
int Gsz, head[N + 5];

inline void addEdge(int u, int v, int val){
	edge[Gsz] = Edge(v, val, head[u]);
	head[u] = Gsz++;
}

void initGraph(const int n){
	Gsz = 0;
	rep(i, 0, n) head[i] = -1;
}


int n, q, A;
int x[N + 5];
//0 <= x_i < A <=10^9 注意可以等于0

void input(){
	scanf("%d %d %d", &n, &q, &A);
	rep(i, 0, n) read(x[i]);
	
	//init!
	initGraph(n);
	
	//input edges
	rep(i, 0, n - 1){
		//id [0, n)
		int u, v, val;
		read(u); read(v); read(val);
		--u; --v;
		
		addEdge(u, v, val);
		addEdge(v, u, val);
	}
	
}

namespace st{
	int seq[N * 2 + 5], seqtot;
	int pos[N + 5], dep[N + 5];
	ll dist[N + 5];//with edge val!
	
	void dfs(int u, int par){
		pos[u] = seqtot;
		seq[seqtot++] = u;
		
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			if(v == par) continue;
			
			dep[v] = dep[u] + 1;
			dist[v] = dist[u] + edge[i].val;
			dfs(v, u);
			seq[seqtot++] = u;
		}
		
	}
	
	inline int min(int x, int y){
		if(dep[x] < dep[y]) return x;
		return y;
	}
	
	inline void swap(int &x, int &y){
		x ^= y; y ^= x; x ^= y;
	}
	
	int lg[N * 2 + 5];
	const int S = 19;
	int mi[N * 2 + 5][S];
	
	inline int lca(int u, int v){
		int l = pos[u], r = pos[v];
		if(l > r) swap(l, r);
		
		int k = lg[r - l + 1];
		return min(mi[l][k], mi[r - (1 << k) + 1][k]);
	}
	
	inline ll dis(int u, int v){
		return dist[u] + dist[v] - dist[lca(u, v)] * 2;
	}
	
	void build(){
		seqtot = 0;
		dep[0] = dist[0] = 0;
		dfs(0, -1);
		
		//lg
		lg[1] = 0;
		rep(i, 2, seqtot + 1) lg[i] = lg[i >> 1] + 1;
		
		//mi
		rep(i, 0, seqtot) mi[i][0] = seq[i];
		rep(i, 1, S) for(int j = 0; j + (1 << i) <= seqtot; ++j)
			mi[j][i] = min(mi[j][i - 1], mi[j + (1 << i - 1)][i - 1]);
			 
	}
}

namespace dt{
	int rt, fa[N + 5];
	bool fbd[N + 5];
	typedef pair<int, vector<pil> > pr;
	vector<pr> son[N + 5];
	
	int sz[N + 5], szmx[N + 5];
	int seq[N + 5], seqtot;
	
	void sizeDfs(int u, int par){
		sz[u] = 1; szmx[u] = 0;
		seq[seqtot++] = u;
		
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			if(fbd[v] || v == par) continue;
			
			sizeDfs(v, u);
			sz[u] += sz[v];
			szmx[u] = max(szmx[u], sz[v]);
		}
		
	}
	
	int findRoot(int u){
		seqtot = 0;
		sizeDfs(u, -1);
		
		rep(i, 0, seqtot){
			int v = seq[i];
			szmx[v] = max(szmx[v], seqtot - sz[v]);
			if(szmx[u] > szmx[v]) u = v;
		}
		
		return u;
	}
	
	void divide(int u){
		fbd[u] = true;
		son[u].clear();
		
		//向分治树上的祖先对应的子树(back)里加入节点u的信息 
		for(int v = fa[u]; v != -1; v = fa[v])
			son[v].back().second.push_back(pil(x[u], st::dis(u, v)));
			
		for(int i = head[u]; ~i; i = edge[i].nxt){
			int v = edge[i].to;
			if(fbd[v]) continue;
			
			int to = findRoot(v);
			fa[to] = u;
			son[u].push_back(pr(to, vector<pil>(0)));
			divide(to);
			
		}
		
		//维护重心u的各个子树的前缀信息
		rep(i, 0, (int)son[u].size()){
			vector<pil> &vec = son[u][i].second;
			sort(vec.begin(), vec.end());
			rep(j, 1, (int)vec.size())
				vec[j].second += vec[j - 1].second;
		}
	}
	
	void build(){
		rep(i, 0, n) fbd[i] = false;
		
		rt = findRoot(0);
		
		fa[rt] = -1;
		divide(rt);
		
	}
	
	ll query(int u, int lim){
		ll res = 0;
		
		for(int v = u, pre = -1; v != -1; pre = v, v = fa[v]){
			rep(i, 0, (int)son[v].size()){
			//这个树所有顶点的度数都小于或等于 3。
				if(son[v][i].first == pre) continue;
				vector<pil> &vec = son[v][i].second;
				
				vector<pil>::iterator it = upper_bound(vec.begin(), vec.end(), pil(lim, 1LL<<60));
				int cnt = it - vec.begin();
				if(cnt) res += (--it)->second + cnt * st::dis(u, v);
			}
			if(x[v] <= lim) res += st::dis(u, v);
		}
		
		return res;
	}
	
}//namespace dt

//long long for path val!

void build(){
	st::build();
	dt::build();
}

ll work(int u, int L, int R){
	return dt::query(u, R) - dt::query(u, L - 1);
	//L - 1 may cause -1 !
}

void solve(){
	ll ans = 0;
	
	while(q--){
		int u, L, R;
		int a, b;
		//id [0, n)
		read(u); read(a); read(b);
		--u;
		L = (int)min((a + ans) % A, (b + ans) % A);
		R = (int)max((a + ans) % A, (b + ans) % A);
	/*
	强制在线！
	 
	对于其中第 1 行，L 和 R 的计算方法为：L=min(a%A,b%A), 
R=max(a%A,b%A)。对于第 2到第 Q行，假设前一行得到的方便值为 ans，那么当
前行的 L 和 R 计算方法为： L=min((a+ans)%A,(b+ans)%A), 
R=max((a+ans)%A,(b+ans)%A)。 
	*/
		
		ans = work(u, L, R);
		print(ans);putchar('\n');
	}
	
}

}//namespace Program

int main(){
	Program::input();
	Program::build();
	Program::solve();
	//id [0, n)
	
	return 0;
}
