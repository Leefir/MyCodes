#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

namespace Program{

const int N = (int)1e5;
const int B = 26;

namespace sam{
	struct State{
		State *par, *go[B], *next;
		int mx, l;
		
		void init(){
			par = next = 0;
			memset(go, 0, sizeof go);
			mx = l = 0;
		}
	};
	
	State statePool[N * 2 + 5], *cur;
	State *root, *last;
	State *firstMx[N + 5];
	
	inline State *newState(int mx){
		State *res = cur++;
		res->init();
		res->mx = mx;
		
		res->next = firstMx[mx];
		firstMx[mx] = res;
		
		return res;
	}
	
	void init(){
		memset(firstMx, 0, sizeof firstMx);
		cur = statePool;
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		
		while(p && p->go[w] == 0){
			p->go[w] = np;
			p = p->par;
		}
		
		if(p == 0) np->par = root;
		else{
			State *q = p->go[w];
			
			if(q->mx == p->mx + 1) np->par = q;
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
	
	void build(char *buf){	
		init();
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a');
			
	}
	
	void run(char *buf){
		State *t = root;
		
		int l = 0;
		for(char *pt = buf; *pt; ++pt){
			int w = *pt - 'a';
			
			while(t && t->go[w] == 0){
				t = t->par;
				if(t) l = t->mx;
			}
			if(t == 0)
				l = 0, t = root;
			else
				++l, t = t->go[w];
			
			t->l = max(t->l, l);
		}
	}
	
	long long solve(){
		long long res = 0;
		
		for(int i = last->mx; i >= 0; --i)
			for(State *t = firstMx[i]; t; t = t->next)
				if(t->par) t->par->l = max(t->par->l, t->l);
					
		for(State *t = statePool; t != cur; ++t)
			if(t->par)
				res += t->mx - max(min(t->l, t->mx), t->par->mx);
		
		return res;
	}
	
};

int n;
char str[N + 5];

void input(){
	scanf("%d", &n);
	scanf("%s", str);
}

void build(){
	sam::build(str);
	
	for(int i = 0; i < n; ++i){
		scanf("%s", str);
		sam::run(str);
	}
	
}

void solve(int cas){
	cout << "Case " << cas << ": " << sam::solve() <<endl;
}

};

int main(){
	int cas; scanf("%d", &cas);
	for(int i = 1; i <= cas; ++i){
		//init!
		Program::input();
		Program::build();
		Program::solve(i);
	}
	return 0;
}
