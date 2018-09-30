#include<cstdio>
#include<algorithm>
const long long none=1e18;
int n,m,top;
int val[110000];
struct Rec{
	int x,next;
};
int Tree[110000];
Rec Etree[210000];
inline void ins(int f,int s){
	Etree[++top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
/*树链剖分*/
int Size[110000],PIH[110000],Ba[110000],Wson[110000],Fa[110000],Top[110000],Depth[110000];
void DFS1(int f,int x,int d){
	Size[x]=1; Fa[x]=f; Depth[x]=d; int maxn=0;
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=f){
			DFS1(x,Etree[v].x,d+1);
			Size[x]+=Size[Etree[v].x];
			if(Size[Etree[v].x]>maxn){
				maxn=Size[Etree[v].x]; Wson[x]=Etree[v].x;
			}
		}	
	}
}
void DFS2(int t,int x){
	Top[x]=t; PIH[x]=++top; Ba[PIH[x]]=val[x]; if(Wson[x])DFS2(t,Wson[x]);
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=Fa[x]&&Etree[v].x!=Wson[x])DFS2(Etree[v].x,Etree[v].x);
	}
}
struct node{
	int l,r,m;
	int negp,negnum;
	long long negmax,absum,tag;
	//negmax记录最大的负数（即绝对值最小），negp记录其位置。absum记录区间绝对值之和
};
node Seg[410000];
int PIS[110000];
void Pushdown(int p){
	//pushdown的时候已经完全保证了不会有负数变为正数
	for(int v=0;v<=1;v++){
		int s=(p<<1)|v;
		Seg[s].negmax+=Seg[p].tag; Seg[s].tag+=Seg[p].tag;
		Seg[s].absum+=(Seg[s].r-Seg[s].l+1-(Seg[s].negnum<<1))*Seg[p].tag;
	}
	Seg[p].tag=0;
}
void Union(int p){
	int u=Seg[p<<1].negmax<Seg[p<<1|1].negmax;
	Seg[p].negmax=Seg[(p<<1)|u].negmax; Seg[p].negp=Seg[(p<<1)|u].negp;
	Seg[p].absum=Seg[p<<1].absum+Seg[p<<1|1].absum;
	Seg[p].negnum=Seg[p<<1].negnum+Seg[p<<1|1].negnum;
}
void Segbuild(int p,int l,int r){
	Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){
		if(Ba[l]<0)
		Seg[p].negmax=Ba[l],Seg[p].negp=l,Seg[p].absum=-Ba[l],Seg[p].negnum=1;
		else Seg[p].negmax=-none,Seg[p].negp=0,Seg[p].absum=Ba[l];
		PIS[l]=p; return;
	}
	Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
	Union(p);
}
int SegNegmax(int p,int l,int r,int w){
    //找到一个被修改之后会变为非负数的就直接返回
	if(Seg[p].l==l&&Seg[p].r==r)return (Seg[p].negmax+w>=0?Seg[p].negp:0);
	Pushdown(p);
	if(r<=Seg[p].m)return SegNegmax(p<<1,l,r,w);
	else
	if(Seg[p].m+1<=l)return SegNegmax(p<<1|1,l,r,w);
	else{
		int u=SegNegmax(p<<1,l,Seg[p].m,w); if(u)return u;
		u=SegNegmax(p<<1|1,Seg[p].m+1,r,w); if(u)return u;
		return 0;
	}
}
void Segpoint(int k,int w){
    //从线段树底端单点修改，再合并上来
	int vi;
	for(vi=1;Seg[vi].l!=Seg[vi].r;vi=(k<=Seg[vi].m?vi<<1:vi<<1|1))Pushdown(vi);
	Seg[vi].negmax=-none; Seg[vi].negnum=0; Seg[vi].negp=0; Seg[vi].absum=w-Seg[vi].absum;
	//由于需要用到低端节点的信息，因此需要先Pushdown沿途所有信息
	for(vi>>=1;vi;vi>>=1)Union(vi);
	
}
void SegChange(int p,int l,int r,int w){
	if(Seg[p].l==l&&Seg[p].r==r){
		Seg[p].negmax+=w;  Seg[p].tag+=w;
		Seg[p].absum+=(Seg[p].r-Seg[p].l+1-(Seg[p].negnum<<1))*(long long)w;
		return;
	}
	Pushdown(p);
	if(r<=Seg[p].m)SegChange(p<<1,l,r,w);
	else
	if(Seg[p].m+1<=l)SegChange(p<<1|1,l,r,w);
	else{
		SegChange(p<<1,l,Seg[p].m,w); SegChange(p<<1|1,Seg[p].m+1,r,w);
	}
	Union(p);
}
long long SegGetsum(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].absum;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetsum(p<<1,l,r);
	else
	if(Seg[p].m+1<=l)return SegGetsum(p<<1|1,l,r);
	else
	return SegGetsum(p<<1,l,Seg[p].m)+SegGetsum(p<<1|1,Seg[p].m+1,r);
}
int stktop;
int stk[110000];
void Splitwork(int l,int r,int w){
    //修改[l..r]上的信息
	int x;
	for(x=SegNegmax(1,l,r,w);x;x=SegNegmax(1,l,r,w)){
		Segpoint(x,w); stk[++stktop]=x;//如果有被修改之后变为非负的负数，就先改动它
	}
	SegChange(1,l,r,w);//区间修改
	while(stktop){
		SegChange(1,stk[stktop],stk[stktop],-w); stktop--;//由于那些特殊的负数被加了两次，需要再减一次
	}
}
void SplitChange(int u,int v,int w){
	int fu,fv;
	while(Top[u]!=Top[v]){
		fu=Top[u]; fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		Splitwork(PIH[fu],PIH[u],w);
		u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); Splitwork(PIH[u],PIH[v],w);
}
long long SplitGetsum(int u,int v){
	int fu,fv;
	long long sum=0;
	while(Top[u]!=Top[v]){
		fu=Top[u]; fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		sum+=SegGetsum(1,PIH[fu],PIH[u]);
		u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); sum+=SegGetsum(1,PIH[u],PIH[v]);
	return sum;
}
int ifdo,u,v;
long long w;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	for(int i=1;i<=n-1;i++){
		int u,v; scanf("%d%d",&u,&v); ins(u,v); ins(v,u);
	}
	DFS1(0,1,1); top=0; DFS2(1,1); top=0; Segbuild(1,1,n);//树链剖分
	for(int i=1;i<=m;i++){
		scanf("%d",&ifdo);
		if(ifdo==1){
			scanf("%d%d%lld",&u,&v,&w); 
			SplitChange(u,v,w);//修改
		}else{
			scanf("%d%d",&u,&v); 
			w=SplitGetsum(u,v); printf("%lld\n",w);//查询
		}
	}
}