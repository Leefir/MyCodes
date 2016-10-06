#include <cstdio>
#include <cstring>

const int N = 250000;
const int B = 26;

char buf[N + 5];

struct Suffix_Automaton{
	struct State{
		State*par, *go[B];
		int mx;
		
		State(): par(0), mx(0){
			memset(go, 0, sizeof go);
		}
	}*root, *last;
	State statePool[N * 2 + 5], *cur;
	
	void init(){
		cur = statePool;
		root = last = cur++;
	}
	
	void extend(int w){
		State*p = last, *np = cur++;
		np->mx = p->mx + 1;
		
		while(p && p->go[w] == 0){
			p->go[w] = np;
			p = p->par;
		}
		
		if(!p)
			np->par = root;
		else{
			State*q = p->go[w];
			if(q->mx == p->mx + 1)
				np->par = q;
			else{
				State*nq = cur++;
				memcpy(nq->go, q->go, sizeof q->go);
				nq->mx = p->mx + 1;
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
	
	void build(char*buf){
		init();
		for(char*pt = buf; *pt; ++pt)
			extend(*pt - 'a');
	}
	
	int LCS(char*buf){
		int ans = 0;
		
		State*t = root;
		int l = 0;
		
		for(char*pt = buf; *pt; ++pt){
			int w = *pt - 'a';
			
			while(t && t->go[w] == 0){
				t = t->par;
				if(t)l = t->mx;
			}
			if(t == 0) l = 0, t = root;
			else ++l, t = t->go[w];
			
			if(ans < l)
				ans = l;
		}
		
		return ans;
	}
}sam;

int main(){
	scanf("%s", buf);
	sam.build(buf);

	scanf("%s", buf);
	printf("%d\n", sam.LCS(buf));
	
	return 0;
}
