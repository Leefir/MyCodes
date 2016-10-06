#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace Program{

const int N = 100000;
const int M = 500000;
const int L = 100000;

namespace sam{
	
	const int B = 26;
	struct State{
		State *par, *go[B];
		int mx;
		
		void init(){
			par = 0;
			memset(go, 0, sizeof go);
			mx = 0;
		}
	};
	
	State statePool[L * 2 + 5], *cur;
	State *root, *last;
	
	inline State *newState(int mx){
		State *res = cur++;
		res->init();
		res->mx = mx;
		
		return res;
	}
	
	void init(){
		cur = statePool;
		root = last = newState(0);
	}
	
	inline void extend(int w){
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
			State *np =newState(p->mx + 1);
			
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
		
	}
	
	void insert(char *buf){
		last = root;
		
		for(char *pt = buf; *pt; ++pt)
			extend(*pt - 'a');
			
	}
	
	int run(char *buf){
	
		State *t = root;
		
		for(char *pt = buf; *pt; ++pt){
			int w = *pt -'a';
			if(t->go[w] == 0) return 0;
			t = t->go[w];
		}
		int pre = 0;
		if(t->par) pre = t->par->mx;
		return t->mx - pre;
	}
}

int n, m;

void input(){
	scanf("%d %d", &n, &m);
}

char str[L + 5];

void build(){
	sam::init();
	
	for(int i = 0; i < n; ++i){
		scanf("%s", str);
		sam::insert(str);
	}
		
}

void solve(){
	while(m--){
		scanf("%s", str);
		printf("%d\n", sam::run(str));
	}
}

}
int main(){
	int cas; scanf("%d", &cas);
	
	for(int i = 1; i <= cas; ++i){
		printf("Case #%d:\n", i);
		Program::input();
		Program::build();
		Program::solve();
	}
	//assumse the dictionary is 'a' ~ 'z'
	
	return 0;
}
