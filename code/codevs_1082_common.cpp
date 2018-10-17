#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
int n,m;
int A[200010];
struct node{
	int l,r,m;
	long long tag,sum;
};
node Seg[500010];//一般还是乘以2.5 
inline void update(int p,int w){
	Seg[p].sum+=(long long)(Seg[p].r-Seg[p].l+1)*w;
	Seg[p].tag+=w;
}
inline void unite(int p){
	Seg[p].sum=Seg[p<<1].sum+Seg[p<<1|1].sum;
}
inline void Down(int p){
	if(Seg[p].tag)update(p<<1,Seg[p].tag),update(p<<1|1,Seg[p].tag),Seg[p].tag=0;
}
void Segbuild(int p,int l,int r){
	Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(Seg[p].l==Seg[p].r){Seg[p].sum=A[l];return;}
	Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
	unite(p);
}
void Change(int p,int l,int r,int w){
	if((Seg[p].l==l)&&(Seg[p].r==r)){update(p,w);return;}
	Down(p);
	if(r<=Seg[p].m)Change(p<<1,l,r,w);
	else if(Seg[p].m+1<=l)Change(p<<1|1,l,r,w);
	else Change(p<<1,l,Seg[p].m,w),Change(p<<1|1,Seg[p].m+1,r,w);
	unite(p);
}
long long Getsum(int p,int l,int r){
	if((Seg[p].l==l)&&(Seg[p].r==r))return Seg[p].sum;
	Down(p);
	if(r<=Seg[p].m)return Getsum(p<<1,l,r);
	else if(Seg[p].m+1<=l)return Getsum(p<<1|1,l,r);
	else return Getsum(p<<1,l,Seg[p].m)+Getsum(p<<1|1,Seg[p].m+1,r);
}
int main(){
	int vi,opt,li,ri,wi;
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	read(n);
	for(vi=1;vi<=n;vi++)read(A[vi]);
	read(m);
	Segbuild(1,1,n);
	for(vi=1;vi<=m;vi++){
		read(opt); read(li); read(ri);
		if(opt==1)read(wi),Change(1,li,ri,wi);else printf("%lld\n",Getsum(1,li,ri));
	}
}
