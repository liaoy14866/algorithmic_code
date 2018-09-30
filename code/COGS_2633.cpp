#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,m;
int A[100010];
struct node{
	int l,r,m;
	unsigned long long sum[3],tag[3];
	//sum[i]是i次幂 
}Seg[100010<<2];
unsigned long long pow2[100010],pow1[100010];
void powinit(int Up){
	unsigned long long vi;
	for(vi=1;vi<=Up;vi++)pow2[vi]=vi*vi,pow1[vi]=vi;
	for(vi=1;vi<=Up;vi++)pow2[vi]+=pow2[vi-1],pow1[vi]+=pow1[vi-1];
}
void unite(int p){
	Seg[p].sum[0]=Seg[p<<1].sum[0]+Seg[p<<1|1].sum[0];
	Seg[p].sum[1]=Seg[p<<1].sum[1]+Seg[p<<1|1].sum[1];
	Seg[p].sum[2]=Seg[p<<1].sum[2]+Seg[p<<1|1].sum[2];
}
void Segbuild(int p,int l,int r){
	Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){
		Seg[p].sum[0]=A[l]; return;
	}
	Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
	unite(p);
}
void update(int p,int l,int r,unsigned long long w0,unsigned long long w1,unsigned long long w2){
	Seg[p].sum[0]+=w0*(r-l+1); Seg[p].tag[0]+=w0;
	Seg[p].sum[1]+=w1*(pow1[r]-pow1[l-1]); Seg[p].tag[1]+=w1;
	Seg[p].sum[2]+=w2*(pow2[r]-pow2[l-1]); Seg[p].tag[2]+=w2;
}
void Down(int p){
	if(!Seg[p].tag[0]&&!Seg[p].tag[1]&&!Seg[p].tag[2])return;//
	update(p<<1,Seg[p].l,Seg[p].m,Seg[p].tag[0],Seg[p].tag[1],Seg[p].tag[2]);
	update(p<<1|1,Seg[p].m+1,Seg[p].r,Seg[p].tag[0],Seg[p].tag[1],Seg[p].tag[2]);
	Seg[p].tag[0]=Seg[p].tag[1]=Seg[p].tag[2]=0;
}
void Change(int p,int l,int r,int x,int y){
	//x是这次加操作的l，y是这次加操作的w 
	if(Seg[p].l==l&&Seg[p].r==r){
		update(p,l,r,(unsigned long long)(x-1)*(x-1)*y,(unsigned long long)2*(1-x)*y,y); return;
	}
	Down(p);
	if(r<=Seg[p].m)Change(p<<1,l,r,x,y);
	else
	if(Seg[p].m+1<=l)Change(p<<1|1,l,r,x,y);
	else
	Change(p<<1,l,Seg[p].m,x,y),Change(p<<1|1,Seg[p].m+1,r,x,y);
	unite(p);
}
unsigned long long Getsum(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum[0]+Seg[p].sum[1]+Seg[p].sum[2];
	Down(p);
	if(r<=Seg[p].m)return Getsum(p<<1,l,r);
	else
	if(Seg[p].m+1<=l)return Getsum(p<<1|1,l,r);
	else
	return Getsum(p<<1,l,Seg[p].m)+Getsum(p<<1|1,Seg[p].m+1,r);
}
unsigned long long ans;
int main(){
	int i,opt,l,r,w;
	read(n); read(m);
	powinit(n);
	Segbuild(1,1,n);
	for(i=1;i<=m;i++){
		read(opt);
		if(opt==1){
			read(l); read(r); read(w);
			Change(1,l,r,l,w);
		}else{
			read(l); read(r);
			ans^=Getsum(1,l,r);
		}
	}
	printf("%llu\n",ans);
}