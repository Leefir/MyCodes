#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;

typedef long long ll;

const int N = (int)1e5;
const int B = 27;

set<int>*merge(set<int>*a, set<int>*b){
	if(a->size() <b->size())
		swap(a, b);
	a->insert(b->begin(), b->end());
	delete b;
	return a;
}
struct Suffix_Automaton{
	static const int L = N * 2;
	//addtional separate character
	
	struct State{
		State *par, *go[B];
		int mx, id;
		
		vector<State*>ch;
		
		
		State(): par(0), mx(0){
			memset(go, 0, sizeof go);
			ch.clear();
			id = -1;
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
		
		for(;p && !p->go[w]; p = p->par)
			p->go[w] = np;
		
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
				
				for(;p && p->go[w] == q; p = p->par)
					p->go[w] = nq;
			}
			
		}
		
		last = np;
		
	}
	
	void build(){
		for(State *t = statePool; t != cur; ++t)
			if(t->par) t->par->ch.push_back(t);
		
		root->dfs();
	}
	
	ll solve(string &s, int k){
		int l = 0;
		ll ans = 0;
		
		State *t = root;
		
		for(int i = 0; i < (int)s.length(); ++i){
			int w = s[i] - 'a';
			
			while(t && t->go[w] == 0){
				t = t->par;
				if(t) l = t->mx;
			}
			if(t){
				t = t->go[w];
				++l;
			}else{
				t = root;
				l = 0;
			}
			while(t && t->cnt <k){
				t = t->par;
				if(t) l = t->mx;
				else l = 0;
			}
			ans += l;
		}
		
		return ans;
	}
	
}sam;

int n, k;
string str[N + 5];

void input(){
	scanf("%d %d",&n ,&k);
	for(int i = 0; i < n; ++i)
		cin>>str[i];
}

void build(){
	sam.init();
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < (int)str[i].length(); ++j)
			sam.extend(str[i][j] - 'a', i);
		sam.extend(26, -1);
	}
	
	sam.build();
}

int main(){
	input();
	build();
	for(int i = 0; i < n; ++i)
		cout << sam.solve(str[i], k) << " ";
	cout << endl;
	return 0;
}

