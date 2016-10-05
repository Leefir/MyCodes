#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
typedef long double ldb;
typedef pair<int,ldb> pr;
#define fi first
#define se second
const int N=(int)2e5;
pr stk[N+5];
inline ldb calc(pr x,int pos){
	ldb d=x.fi-pos;
	return d*d/4/x.se;
}
int main(){
	int n;scanf("%d",&n);
	int top=0;
	rep(i,0,n){
		int x,rr;
		ldb r;
		scanf("%d %d",&x,&rr);r=rr;
		while(top){
			ldb tr=calc(stk[top],x);
			if(r>tr)r=tr;
			if(r<stk[top].se)break;
			top--;
		}
		printf("%.12LF\n",r);
		stk[++top]=pr(x,r);
	}
	return 0;
}
