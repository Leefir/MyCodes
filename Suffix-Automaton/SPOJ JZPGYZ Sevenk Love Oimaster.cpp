#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 10000;
const int Q = 60000;
const int NL = 100000;
const int QL = 360000;


const int B = 128;
struct State{
	State *par;
	State *go[B + 1];
	int mx, id;
	
	vector<State*>ch;
	int in, out;
	
	State(){
		par = 0;
		mx = 0;
		memset(go, 0, sizeof go);
		id = -1;
		
		ch.clear();
	}
	
};
namespace sam{
	const int L = NL * 2;
	
	
	State statePool[L * 2 + 5], *cur;
	State *root, *last;
	
	inline State *newState(int mx){
		State *res = cur++;
		res->mx = mx;
		
		return res;
	}
	
	void init(){
		cur = statePool;
		root = last = newState(0);
	}
	
	void extend(int w, int id){
		State *p = last;
		State *np = newState(p->mx + 1);
		np->id = id;
		
		while(p && p->go[w] == 0){
			p->go[w] = np;
			p = p->par;
		}
		
		if(!p)
			np->par = root;
		else{
			State *q = p->go[w];
			
			if(q->mx == p->mx + 1)
				np->par = q;
			else{
				State *nq = newState(p->mx + 1);
				memcpy(nq->go, q->go, sizeof q->go);
				nq->par = q->par;
				q->par = np->par = nq;
				
				while(p && p->go[w] == q){
					p->go[w] = nq;
					p = p->par;
				}
			}
			
		}
		
		last = np;
		
	}
	
	State *seq[L * 2 + 5];
	int dfs_clock;
	
	void dfs(State *cur){
		cur->in = ++dfs_clock;
		seq[dfs_clock] = cur;
		
		for(vector<State*>::iterator it = cur->ch.begin(); it != cur->ch.end(); ++it)
			dfs(*it);
		
		cur->out = dfs_clock;
	}
	
	void build(){
		for(State *t = statePool; t != cur; ++t)
			if(t->par)t->par->ch.push_back(t);
		
		dfs_clock = 0;
		dfs(root);
	}
	
	State *walk(char *buf){
		State *t = root;
		for(char *pt = buf; *pt; ++pt){
			int w = *pt;
			if(t->go[w]) t = t->go[w];
			else return 0;
		}
		return t;
	}
	
};

int n,q;
char buf[NL + 5];

void input(){
	scanf("%d %d", &n, &q);
	
	sam::init();
	for(int i = 0; i < n; ++i){
		scanf("%s", buf);
		for(char *pt = buf; *pt; ++pt)
			sam::extend(*pt, i);
		sam::extend(B, -1);
	}
	
}

const int M = sam::L * 2;

struct Binary_Indexed_Tree{
	int a[M + 5];
	int n;
	
	void init(int _n){
		n = _n;
		for(int i = 0; i <= n; ++i)
			a[i] = 0;
	}
	
	inline void update(int pos, int val){
		for(int i = pos; i <= n; i += i&-i)
			a[i] += val;
	}
	
	inline int sum(int pos){
		int res = 0;
		for(int i = pos; i > 0; i -= i&-i)
			res += a[i];
		return res;
	}
	
	inline int query(int l, int r){
		return sum(r) - sum(l - 1);
	}
}bit;

namespace offline{
	struct Query{
		int id, l, r;
		Query *next;
		Query(){}
		Query(int _id, int _l, int _r, Query *p):id(_id), l(_l), r(_r), next(p){}
	}query[Q + 5];
	
	int tot;
	Query *head[M + 5];
	
	char buf[QL + 5];
	void build(){
		tot = 0;
		for(int i = 0; i < q; ++i){
			scanf("%s", buf);
			State *t = sam::walk(buf);
			if(t == 0)continue;
			query[tot++] = Query(i, t->in, t->out, head[t->out]);
			head[t->out] = &query[tot - 1];
		}
	}
	int ans[Q + 5];
	int lastPos[N + 5];
	
	void solve(){
		bit.init(sam::dfs_clock);
		
		for(int i = 0; i < n; ++i)
			lastPos[i] = -1;
		for(int i = 1; i <= sam::dfs_clock; ++i){
			int id = sam::seq[i]->id;
			if(id != -1){
				if(lastPos[id] != -1)bit.update(lastPos[id], -1);
				bit.update(i, 1);
				lastPos[id] = i;
			}
			for(Query *cur = head[i]; cur; cur = cur->next){
				ans[cur->id] = bit.query(cur->l, cur->r);
			}
		}
	}
	
	void output(){
		for(int i = 0; i < q; ++i)
			printf("%d\n", ans[i]);
	}
	
	void work(){
		for(int i = 0; i < q; ++i)ans[i] = 0;
		build();
		solve();
		output();
	}
}

int main(){
	input();
	sam::build();
	offline::work();
	return 0;
	//assume the size of dictionary is B = 128
}
