#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
const int N=200000;
typedef std::pair<int,int> pii;
int n,s;
pii a[N+5];
pii ans[N+5];
int tot;
void input(){
	scanf("%d %d",&n,&s);
	rep(i,0,n){
		scanf("%d",&a[i].first);
		a[i].second=i+1;
	}
	std::sort(a,a+n);
}
int b[N+5];
void swap(int l,int r,int p){
	rep(i,l,r+1){
		--b[i];--b[p];
		ans[tot++]=pii(i,p);
	}
}
bool solve(){
	rep(i,0,n)b[i]=a[i].first;
	per(i,0,n){
		int cur=b[i];
		if(cur<0||cur>i)return false;
		int num=b[i-cur];
		int x=std::lower_bound(b,b+i,num)-b,y=std::upper_bound(b,b+i,num)-b;
		if(y==i){
			swap(x,x+cur-1,i);
		}else{
			int cnt=cur-(i-y);
			swap(y,i-1,i);
			swap(x,x+cnt-1,i);
		}
	}
	
	return true;
}
void output(){
	puts("Yes");
	printf("%d\n",tot);
	rep(i,0,tot)printf("%d %d\n",a[ans[i].first].second,a[ans[i].second].second);
}
int main(){
	input();
	tot=0;
	if(!solve())puts("No");
	else output();
	return 0;
}

/*
It is possible that a player has no cards initially.

particularly, he can't take cards of his color, 
no matter whether he has given out all of them or not

*/
