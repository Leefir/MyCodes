#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace Program{

const int L = 5000;
const int B = 26;

struct State{
	State *par, *go[B], *next;
	int mx, right, val;
	
	void init(){
		par = next = 0;
		memset(go, 0, sizeof go);
		mx = right = val = 0;
	}
};

namespace sam{
	
	State statePool[L * 2 + 5], *cur;
	State *root, *last;
	State *firstMx[L + 5];
	
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
	
	inline void extend(int w){
		State *p = last;
		State *np = newState(p->mx + 1);
		np->right = 1;
		
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
		
		for(int i = last->mx; i >= 0; --i)
			for(State *t = firstMx[i]; t; t = t->next)
				if(t->par) t->par->right += t->right;
		root->right = 0;
	}

	int run(char *buf){
		State *t = root;
		
		for(char *pt = buf; *pt; ++pt){
			int w = *pt - 'a';
			while(t && t->go[w] == 0)
				t = t->par;
			
			if(t == 0) t = root;
			else t = t->go[w];
			
			t->val++;
		}
		
		int mi = (int)1e9;;
		
		for(State *t = statePool; t != cur; ++t)
			if(t->right == 1 && t->val == 1)
				mi = min(mi, t->par ? t->par->mx + 1 : 0);
		
		if(mi == (int)1e9)return -1;
		return mi;
	}	
}

char str[L + 5];

void input(){
	scanf("%s", str);
	sam::build(str);
}

void solve(){
	scanf("%s", str);
	printf("%d\n", sam::run(str));
}


}

int main(){
	Program::input();
	Program::solve();
	return 0;
}
