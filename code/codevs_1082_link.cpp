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
int top;
struct node{
	int l,r,m,son[2];
	long long sum,tag;
};
node Seg[500010];
inline void update(int p,int w){Seg[p].sum+=(long long)w*(Seg[p].r-Seg[p].l+1); Seg[p].tag+=w;}
inline void unite(int p){Seg[p].sum=Seg[Seg[p].son[0]].sum+Seg[Seg[p].son[1]].sum;}
inline void down(int p){if(Seg[p].tag)update(Seg[p].son[0],Seg[p].tag),update(Seg[p].son[1],Seg[p].tag),Seg[p].tag=0;}
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){Seg[p].sum=A[l]; return p;}
	Seg[p].son[0]=Segbuild(l,Seg[p].m); Seg[p].son[1]=Segbuild(Seg[p].m+1,r);
	unite(p); return p;
}
void Change(int p,int l,int r,int w){
	if((Seg[p].l==l)&&(Seg[p].r==r)){update(p,w);return;}
	down(p);
	if(r<=Seg[p].m)Change(Seg[p].son[0],l,r,w);
	else if(Seg[p].m+1<=l)Change(Seg[p].son[1],l,r,w);
	else Change(Seg[p].son[0],l,Seg[p].m,w),Change(Seg[p].son[1],Seg[p].m+1,r,w);
	unite(p);
}
long long Getsum(int p,int l,int r){
	if((Seg[p].l==l)&&(Seg[p].r==r))return Seg[p].sum;
	down(p);
	if(r<=Seg[p].m)return Getsum(Seg[p].son[0],l,r);
	else if(Seg[p].m+1<=l) return Getsum(Seg[p].son[1],l,r);
	else return Getsum(Seg[p].son[0],l,Seg[p].m)+Getsum(Seg[p].son[1],Seg[p].m+1,r); 
}
int main(){
	int vi,opt,l,r,w;
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	read(n); read(m);
	for(vi=1;vi<=n;vi++)read(A[vi]);
	Segbuild(1,n);
	for(vi=1;vi<=m;vi++){
		read(opt); read(l); read(r);
		if(opt==1)read(w),Change(1,l,r,w); else printf("%lld\n",Getsum(1,l,r));
	}
}
