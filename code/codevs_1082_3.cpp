#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,q;
int A[210000];
int top;
struct node{
	int l,r,m,s[2];
	long long sum,tag;;
}Seg[610000];
void update(int p,int w){//更新
	Seg[p].sum+=(long long)w*(Seg[p].r-Seg[p].l+1);
}
void unite(int p){//合并，注意这里要加上自己的tag
	Seg[p].sum=Seg[Seg[p].s[0]].sum+Seg[Seg[p].s[1]].sum+Seg[p].tag*(Seg[p].r-Seg[p].l+1);
}
int Segbuild(int l,int r){//建一棵线段树
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){Seg[p].sum=A[l];return p;}
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	unite(p); return p;
}
void Change(int p,int l,int r,int w){//修改
	if(Seg[p].l==l&&Seg[p].r==r){Seg[p].sum+=(long long)w*(r-l+1);Seg[p].tag+=w;return;}
	if(r<=Seg[p].m)Change(Seg[p].s[0],l,r,w);
	else
	if(Seg[p].m+1<=l)Change(Seg[p].s[1],l,r,w);
	else{
		Change(Seg[p].s[0],l,Seg[p].m,w); Change(Seg[p].s[1],Seg[p].m+1,r,w);
	}
	unite(p);
}
long long Getsum(int p,int l,int r){//查询
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum;
	long long sum=Seg[p].tag*(r-l+1);//注意这里要加上自己的tag
	if(r<=Seg[p].m)sum+=Getsum(Seg[p].s[0],l,r);
	else
	if(Seg[p].m+1<=l)sum+=Getsum(Seg[p].s[1],l,r);
	else{
		sum+=Getsum(Seg[p].s[0],l,Seg[p].m); sum+=Getsum(Seg[p].s[1],Seg[p].m+1,r);
	}
	return sum;
}
int main(){
	int i,opt,li,ri,wi;
	long long vi;
	read(n);
	for(i=1;i<=n;i++)read(A[i]);
	Segbuild(1,n);
	read(q);
	for(i=1;i<=q;i++){
		read(opt);
		if(opt==1){
			read(li); read(ri); read(wi); Change(1,li,ri,wi);
		}else{
			read(li); read(ri); vi=Getsum(1,li,ri); printf("%lld\n",vi);
		}
	}
}