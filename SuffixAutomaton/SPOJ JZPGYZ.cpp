#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int N = 10000;
const int Q = 60000;
const int NL = 100000;
const int QL = 360000;

set<int>*merge(set<int>*a, set<int>*b){
	if(a->size() < b->size())
		swap(a, b);
	a->insert(b->begin(), b->end());
	delete b;
	return a;
}

const int B = 128;

struct Suffix_Automaton{
	static const int L = NL * 2;
	
	struct State{
		State *par;
//		map<int, State*>go;
		State *go[B + 1];
		int mx, id;
		
		vector<State*>ch;
		
		State(){
			par = 0;
			mx = 0;
//			go.clear();
			memset(go, 0, sizeof go);
			id = -1;
			
			ch.clear();
		}
		
		int cnt;
		
		set<int>*dfs(){
			set<int>*st = new set<int>();
			if(id != -1)
				st->insert(id);
		
			for(vector<State*>::iterator it = ch.begin(); it != ch.end(); ++it)
				st = merge(st, (*it)->dfs());
			
			cnt = st->size();
			
			return st;
		}
		
	};
	
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
//				nq->go = q->go;
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
	
	void build(){
		for(State *t = statePool; t != cur; ++t)
			if(t->par)t->par->ch.push_back(t);
		
		root->dfs();
	}
	
	char buf[QL + 5];
	void solve(){
		scanf("%s", buf);
		
		State *t = root;
		
		for(char *pt = buf; *pt; ++pt){
			int w = *pt;
//			if(t->go.find(w) == t->go.end()){
			if(t->go[w] == 0){
				puts("0");
				return;
			}
			t = t->go[w];
		}
		printf("%d\n", t->cnt);
	}
}sam;

int n,q;
char buf[NL + 5];

void input(){
	scanf("%d %d", &n, &q);
	
	sam.init();
	for(int i = 0; i < n; ++i){
		scanf("%s", buf);
		for(char *pt = buf; *pt; ++pt)
			sam.extend(*pt, i);
		sam.extend(B, -1);
	}
	
}

int main(){
	input();
	sam.build();
	while(q--)sam.solve();
	return 0;
}
/*

3 3
aa
bb
ab

a
b
ab

3 3
bb
aa
ab

b
a
ab
*/
