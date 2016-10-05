#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 250000;
const int B = 26;

struct Suffix_Automaton{
	struct State{
		State *par, *go[B], *next;
		int mx,right;
		
		State(): par(0), next(0), mx(0){
			right = 0;
			memset(go, 0, sizeof go);
		}
	};
	
	State *root, *last;
	State *firstMx[N + 5];
	
	Suffix_Automaton(){
		memset(firstMx, 0, sizeof firstMx);
	}
	
	inline State *newState(int mx){
		State *res = new State;
		res->mx = mx;
		
		res->next = firstMx[mx];
		firstMx[mx] = res;
		
		return res;
	}
	
	void init(){
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		np->right = 1;
		
		for(;p && !p->go[w]; p = p->par)
			p->go[w] = np;
		
		if(!p)
			np->par = root;
		else{
			State *q = p->go[w];
			
			if(q->mx == p->mx +1)
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
	
	void build(char *buf){
		init();
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a');
		
	}
	
	int ans[N + 5];
	void work(){
		int len = last->mx;
		for(int i = 1; i <= len; ++i)
			ans[i] = 0;
		
		
		for(int i = len; i >= 0; --i)
			for(State *t = firstMx[i]; t; t= t->next){
				ans[t->mx] = std::max(ans[t->mx], t->right);
				if(t->par)
					t->par->right += t->right;
			}
		
		for(int i = len; i > 1; --i)
			ans[i - 1] = std::max(ans[i - 1], ans[i]);
		
		for(int i = 1; i <= len; ++i)
			printf("%d\n", ans[i]);
	}
}sam;

char buf[N + 5];

int main(){
	scanf("%s", buf);
	sam.build(buf);
	sam.work();
	return 0;
}


