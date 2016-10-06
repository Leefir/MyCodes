#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

namespace Program{

const int L = 5000;
const int B = 26;

struct State{
	State *par, *go[B], *next;
	int mx, right;
	
	void init(){
		par = next = 0;
		memset(go, 0, sizeof go);
		mx = right = 0;
	}
};

struct SuffixAutomaton{
	
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
	
}a,b;

char str[L + 5];

void build(){
	scanf("%s", str);
	a.build(str);
	
	scanf("%s", str);
	b.build(str);
}

struct Pack{
	int len;
	State *x, *y;
	
	Pack(){}
	Pack(int _len, State *_x, State *_y): len(_len), x(_x), y(_y){}
};

queue<Pack>que;
void bfs(){
	while(!que.empty())que.pop();
	que.push(Pack(0, a.root, b.root));
	
	while(!que.empty()){
		Pack now = que.front(); que.pop();
		
		
		if(now.x->right == 1 && now.y->right == 1){
			printf("%d\n", now.len);
			return;
		}
		
		for(int i = 0; i < B; ++i){
			if(now.x->go[i] && now.y->go[i])
				que.push(Pack(now.len + 1, now.x->go[i], now.y->go[i]));
		}
	}
	
	puts("-1");	
}

}

int main(){
	Program::build();
	Program::bfs();
	return 0;
}
