#include<cstdio>
struct node{
	long long sum,tag;
	int l,r,son[2];
};
int n,m,ifdo,top;
int A[210000];
node Seg[810000];

int Newnode(int l,int r){
	top++; Seg[top].l=l; Seg[top].r=r;
	return top;
}
void Pushdown(int p){
	if((Seg[p].son[0])&&(Seg[p].son[1])&&(!Seg[p].tag))return;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(!Seg[p].son[0])Seg[p].son[0]=Newnode(Seg[p].l,m);
	if(!Seg[p].son[1])Seg[p].son[1]=Newnode(m+1,Seg[p].r);
	Seg[Seg[p].son[1]].sum+=(Seg[p].r-m)*Seg[p].tag; Seg[Seg[p].son[1]].tag+=Seg[p].tag;
	Seg[Seg[p].son[0]].sum+=(m-Seg[p].l+1)*Seg[p].tag; Seg[Seg[p].son[0]].tag+=Seg[p].tag;
	Seg[p].tag=0;
}
void Change(int p,int l,int r,int w){
	if((Seg[p].l==l)&&(Seg[p].r==r)){
		Seg[p].sum+=(Seg[p].r-Seg[p].l+1)*w; Seg[p].tag+=w; return;
	}
	Pushdown(p);//Newnode in Pushdown
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(r<=m)Change(Seg[p].son[0],l,r,w);
	else 
	if(m+1<=l)Change(Seg[p].son[1],l,r,w);
	else{
		Change(Seg[p].son[0],l,m,w); Change(Seg[p].son[1],m+1,r,w);
	}
	Seg[p].sum=Seg[Seg[p].son[0]].sum+Seg[Seg[p].son[1]].sum;
} 
long long Getsum(int p,int l,int r){
	if((Seg[p].l==l)&&(Seg[p].r==r))return Seg[p].sum; 
	Pushdown(p);
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(r<=m)return Getsum(Seg[p].son[0],l,r);
	else
	if(m+1<=l)return Getsum(Seg[p].son[1],l,r);
	else
	return Getsum(Seg[p].son[0],l,m)+Getsum(Seg[p].son[1],m+1,r); 
}

int main(){
	scanf("%d",&n); top=1; Seg[1].l=1;Seg[1].r=n;
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);Change(1,i,i,A[i]);}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&ifdo);
		if(ifdo==1){
			int l,r,w; scanf("%d%d%d",&l,&r,&w); 
			Change(1,l,r,w); 
		}else{
			int l,r; scanf("%d%d",&l,&r); 
			long long w=Getsum(1,l,r); printf("%lld\n",w);
		}
	}
}