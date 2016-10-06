#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;


namespace Program{

const int N = (int)1e5;
const int B = 26;

set<int> *merge(set<int> *a, set<int> *b){
	if(a->size() < b->size()) swap(a, b);
	a->insert(b->begin(), b->end());
	
	return a;
}
namespace sam{
	struct State{
		State *par, *go[B];
		int mx;
		
		vector<State*> ch;
		set<int>*st;
		
		int cnt;
		
		State(){
			par = 0;
			memset(go, 0, sizeof(go));
			mx = 0;
			
			ch.clear();
			st = new set<int>();
		}
		
		set<int> *dfs(){
			
			for(vector<State*>::iterator it = ch.begin(); it != ch.end(); ++it)
				st = merge(st, (*it)->dfs());
				
			cnt = st->size();
			
			return st;
		}
	};
	
	State statePool[N * 2 + 5], *cur;
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
		
		if(p->go[w]){
			State *q = p->go[w];
			if(q->mx == p->mx + 1) last = q;
			else{
				State *nq = newState(p->mx + 1);
				memcpy(nq->go, q->go, sizeof q->go);
				nq->par = q->par;
				q->par = nq;
				while(p && p->go[w] == q){
					p->go[w] = nq;
					p = p->par;
				}
				last = nq;
			}
			
		}else{
			State *np = newState(p->mx + 1);
			
			while(p && p->go[w] == 0){
				p->go[w] = np;
				p = p->par;
			}
			
			if(!p) np->par = root;
			else{
				State *q = p->go[w];
				if(q->mx == p->mx + 1)
					np->par = q;
				else{
					State *nq = newState(p->mx + 1);
					memcpy(nq->go, q->go, sizeof q->go);
					nq->par = q->par;
					q->par = np->par = nq;
					while(p && p->go[w] ==q){
						p->go[w] = nq;
						p = p->par;
					}
				}
			}
			
			last = np;
		}
		
		last->st->insert(id);
	}
	
	void insert(string &s, int id){
		last = root;
		
		for(int i = 0; i < (int)s.length(); ++i)
			extend(s[i] - 'a', id);
		
	}
	
	void build(){
		for(State *t = statePool; t != cur; ++t)
			if(t->par) t->par->ch.push_back(t);
			
		root->dfs();
	}
	
	long long solve(string &s, int k){
		long long res = 0;
		
		State *t = root;
		int l = 0;
		for(int i = 0; i < (int)s.length(); ++i){
			int w = s[i] - 'a';
			
			while(t && t->go[w] == 0){
				t = t->par;
				if(t) l = t->mx;
			}
			if(t == 0)
				l = 0, t = root;
			else
				++l, t = t->go[w];
			
			while(t && t->cnt < k){
				t = t->par;
				if(t) l = t->mx;
				else t = 0;
			}
				
			res += l;
		}
		
		return res;
	}
	
};

int n, k;
string str[N + 5];

void input(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; ++i)
		cin >> str[i];
}

void build(){
	sam::init();
	for(int i = 0; i < n; ++i)
		sam::insert(str[i], i);
	sam::build();
}


void output(){
	for(int i = 0; i < n; ++i)
		cout << sam::solve(str[i], k) << " ";
	cout << endl;
}

};

int main(){
	Program::input();
	Program::build();
	Program::output();
	return 0;
}
