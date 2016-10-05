#include <cstdio>
#include <cassert>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
const int N=(int)1e5;
int n,m,a[N+5];
void input(){
	scanf("%d",&n);
	rep(i,1,n+1)scanf("%d",&a[i]);
	scanf("%d",&m);
}
inline int max(int x,int y){
	if(x>y)return x;
	return y;
}
inline int min(int x,int y){
	if(x<y)return x;
	return y;
}
inline void swap(int &x,int &y){
	x^=y;y^=x;x^=y;
}
struct node{
	int pre_mx,pre_mxr,suf_mx,suf_mxl;
	int sub_mx,sub_mxl,sub_mxr;
	
	int pre_mi,pre_mir,suf_mi,suf_mil;
	int sub_mi,sub_mil,sub_mir;
	
	int sum,l,r;
	
	void print(){
		printf("pre_mx %d suf_mx %d sub_mx %d\n",pre_mx,suf_mx,sub_mx);
		printf("sum %d l %d r %d\n",sum,l,r);
	}
	void init(int pos,int val){
		pre_mx=suf_mx=sub_mx=val;
		pre_mxr=suf_mxl=sub_mxl=sub_mxr=pos;
		
		pre_mi=suf_mi=sub_mi=val;
		pre_mir=suf_mil=sub_mil=sub_mir=pos;
		
		sum=val,l=r=pos;
	}
	void reverse(){
		swap(pre_mx,pre_mi);pre_mx=-pre_mx;pre_mi=-pre_mi;swap(pre_mxr,pre_mir);
		swap(suf_mx,suf_mi);suf_mx=-suf_mx;suf_mi=-suf_mi;swap(suf_mxl,suf_mil);
		
		swap(sub_mx,sub_mi);sub_mx=-sub_mx;sub_mi=-sub_mi;
		swap(sub_mxl,sub_mil);swap(sub_mxr,sub_mir);
		
		sum=-sum;
	}
};
#define root 1,1,n
struct Segment_Tree{
	node tree[N*4+5];
	bool rev[N*4+5];
		
	#define mid ((L+R)>>1)
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define lson ls,L,mid
	#define rson rs,mid+1,R
	inline void modify(int p){
		rev[p]^=1;
		tree[p].reverse();
	}
	
	inline node push_up(const node x,const node y){
		node res;
		
		if(x.pre_mx>x.sum+y.pre_mx)res.pre_mx=x.pre_mx,res.pre_mxr=x.pre_mxr;
		else res.pre_mx=x.sum+y.pre_mx,res.pre_mxr=y.pre_mxr;
		if(y.suf_mx>x.suf_mx+y.sum)res.suf_mx=y.suf_mx,res.suf_mxl=y.suf_mxl;
		else res.suf_mx=x.suf_mx+y.sum,res.suf_mxl=x.suf_mxl;
		if(x.suf_mx+y.pre_mx>max(x.sub_mx,y.sub_mx))res.sub_mx=x.suf_mx+y.pre_mx,res.sub_mxl=x.suf_mxl,res.sub_mxr=y.pre_mxr;
		else if(x.sub_mx>y.sub_mx)res.sub_mx=x.sub_mx,res.sub_mxl=x.sub_mxl,res.sub_mxr=x.sub_mxr;
		else res.sub_mx=y.sub_mx,res.sub_mxl=y.sub_mxl,res.sub_mxr=y.sub_mxr;
		
		if(x.pre_mi<x.sum+y.pre_mi)res.pre_mi=x.pre_mi,res.pre_mir=x.pre_mir;
		else res.pre_mi=x.sum+y.pre_mi,res.pre_mir=y.pre_mir;
		if(y.suf_mi<x.suf_mi+y.sum)res.suf_mi=y.suf_mi,res.suf_mil=y.suf_mil;
		else res.suf_mi=x.suf_mi+y.sum,res.suf_mil=x.suf_mil;
		if(x.suf_mi+y.pre_mi<min(x.sub_mi,y.sub_mi))res.sub_mi=x.suf_mi+y.pre_mi,res.sub_mil=x.suf_mil,res.sub_mir=y.pre_mir;
		else if(x.sub_mi<y.sub_mi)res.sub_mi=x.sub_mi,res.sub_mil=x.sub_mil,res.sub_mir=x.sub_mir;
		else res.sub_mi=y.sub_mi,res.sub_mil=y.sub_mil,res.sub_mir=y.sub_mir;
		
		res.sum=x.sum+y.sum;
		res.l=x.l;res.r=y.r;
		
		return res;
	}
	inline void push_down(int p){
		if(rev[p]){
			modify(p<<1);
			modify(p<<1|1);
			rev[p]=false;
		}
	}
//	inline void push_down(int p){
//		if(rev[p]^rev[p<<1])modify(p<<1);
//		if(rev[p]^rev[p<<1|1])modify(p<<1|1);
//	}
	void build(int p,int L,int R){
		rev[p]=false;
		if(L==R){
			tree[p].init(L,a[L]);
			return;
		}
		
		build(lson);
		build(rson);
		
		tree[p]=push_up(tree[ls],tree[rs]);
//		puts("_____________");
//		tree[p].print();
//		printf("[ %d , %d ] sub_mx %d sum %d lsum %d rsum %d\n",L,R,tree[p].sub_mx,tree[p].sum,tree[p<<1].sum,tree[p<<1|1].sum);
	}
	void update(int p,int L,int R,int pos,int val){
		if(L==R){
			tree[p].init(pos,val);
			return;
		}
		
		push_down(p);
		
		if(pos<=mid)update(lson,pos,val);
		else update(rson,pos,val);
		
		tree[p]=push_up(tree[ls],tree[rs]);
	}
	node query(int p,int L,int R,int l,int r){
		if(L==l&&R==r)return tree[p];
		
		push_down(p);
		
		if(r<=mid)return query(lson,l,r);
		else if(mid<l)return query(rson,l,r);
		else return push_up(query(lson,l,mid),query(rson,mid+1,r));
	}
	void reverse(int p,int L,int R,int l,int r){
//		printf("[ %d , %d ] [ %d , %d ]\n",L,R,l,r);
		if(L==l&&R==r){
			modify(p);
			return;
		}
		
		push_down(p);
		
		if(r<=mid)reverse(lson,l,r);
		else if(mid<l)reverse(rson,l,r);
		else reverse(lson,l,mid),reverse(rson,mid+1,r);
		
		tree[p]=push_up(tree[ls],tree[rs]);
	}
}sgt;
int sl[25],sr[25];
void response(){
	int flag;scanf("%d",&flag);
	if(flag==0){
		int pos,val;
		scanf("%d %d",&pos,&val);
		sgt.update(root,pos,val);
	}else if(flag==1){
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		int res=0,tot=0;
		rep(i,0,k){
			node now=sgt.query(root,l,r);
			if(now.sub_mx<=0)break;
			res+=now.sub_mx;
			sl[tot]=now.sub_mxl;
			sr[tot]=now.sub_mxr;
//			printf("response reverse [ %d , %d ]\n",sl[tot],sr[tot]);
			sgt.reverse(root,sl[tot],sr[tot]);
			tot++;
		}
		printf("%d\n",res);
		rep(i,0,tot)sgt.reverse(root,sl[i],sr[i]);
	}else assert(false);
}
int main(){

//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	
	input();
	sgt.build(root);
	while(m--)response();
	return 0;
}
