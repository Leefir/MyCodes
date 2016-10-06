#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

namespace Program{


const int N = (int)1e5;
const int L = (int)1e6;
const int B = 26;

namespace sam{
	
	struct State{
		State *par, *go[B], *next;
		int mx, mark, right;
		
		void init(){
			par = next = 0;
			memset(go, 0, sizeof go);
			mx = 0;
			mark = -1;
			right = 0;
		}
	};
	
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
	}
	
	void solve(char *buf, int id){
		State *t = root;
		int l = 0, len = strlen(buf);
		
		int ans = 0;
		
		for(int k = 0; k < 2; ++k)
			for(char *pt = buf; *pt; ++pt){
				int w = *pt - 'a';
				
				while(t && t->go[w] == 0){
					t = t->par;
					if(t) l = t->mx;
				}
				
				if(t == 0) l = 0, t = root;
				else ++l, t = t->go[w];
				
				if(l >= len){
					while(t->par && t->par->mx >= len){
						t = t->par;
						l = t->mx;
					}
					if(t->mark != id){
						t->mark = id;
						ans += t->right;
					}
				}
				
			}
		
		printf("%d\n", ans);
	}
}

char str[L + 5];
int n;

void input(){
	scanf("%s", str);
	scanf("%d", &n);
}

void build(){
	sam::build(str);
}

void solve(){
	for(int i = 0; i < n; ++i){
		scanf("%s", str);
		sam::solve(str, i);
	}
}

}

int main(){
	Program::input();
	Program::build();
	Program::solve();
	return 0;
}
