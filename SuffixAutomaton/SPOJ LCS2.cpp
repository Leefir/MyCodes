#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 100000;
const int B = 26;

struct Suffix_Automaton{
	struct State{
		State *par, *go[B], *next;
		int mx,mi,l;
		
		State(): par(0), next(0){
			memset(go, 0, sizeof go);
		}
	};
	
	State statePool[N * 2 + 5], *cur;
	State *root, *last;
	State *firstMx[N + 5];
	
	Suffix_Automaton(){
		memset(firstMx, 0, sizeof firstMx);
	}
	
	State *newState(int mx){
		cur->mx = cur->mi = mx;
		cur->next = firstMx[mx];
		firstMx[mx] = cur;
		return cur++;
	}
	
	void init(){
		cur = statePool;
		root = last = newState(0);
	}
	
	void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		
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
	
	void build(char *buf){
		init();
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a');
		
	}
	
	void insert(char *buf){
		State *t = root;
		int l = 0;
		
		for(State *t = statePool; t != cur; ++t)
			t->l = 0;
		
		for(char *pt = buf; *pt; ++pt){
			int w = *pt - 'a';
			
			if(t->go[w])
				t = t->go[w], ++l;
			else{
				for(;t && !t->go[w]; t = t->par);
				
				if(!t)
					t = root, l = 0;
				else{
					l = t->mx + 1;
					t = t->go[w];
				}
			}
			t->l = std::max(t->l, l);
		}
		
		for(int i = last->mx; i >= 0; --i){
			for(State *t = firstMx[i]; t; t = t->next){
				if(t->par)
					t->par->l = std::max(t->par->l, t->l);
				t->mi =std::min(t->mi, t->l);
			}
		}
			
	}
	
	int LCS(){
		int ans = 0;
		
		for(State *t = statePool; t != cur; ++t)
			ans = std::max(ans, t->mi);
		
		return ans;
	}
}sam;

char buf[N + 5];

int main(){
	scanf("%s", buf);
	sam.build(buf);
	
	while(scanf("%s", buf) != EOF)
		sam.insert(buf);
	
	printf("%d\n", sam.LCS());
	
	return 0;
}
