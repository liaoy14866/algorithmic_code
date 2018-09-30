/*
题目大意：给出一大小为n的树，要求支持：
1.一条边的边权修改为w
2.一条路径的边权变为相反数
3.查询一条路径边权最大/小值
4.查询一条路径边权和
把边权变为深度较大的端点的点权即可转换边权。之后树链剖分即可
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
const int none=2e9+7;
int n,m,logn,top;
struct Rec{
	int x,w,next;
};
int Tree[21000];
Rec Etree[41000];
inline void ins(int f,int s,int w){
	top++; Etree[top].x=s; Etree[top].w=w; Etree[top].next=Tree[f]; Tree[f]=top;
}
struct edge{
	int x,y;
};
int etop;
edge E[41000];
int val[21000];
int Size[21000],Wson[21000],Top[21000],Depth[21000],PIH[21000],Ba[21000];
int Fm[21000][20];
void DFS1(int f,int x,int d){
	Fm[x][0]=f; Depth[x]=d; Size[x]=1; int maxn=0;
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=f){
			DFS1(x,Etree[v].x,d+1);
			Size[x]+=Size[Etree[v].x]; val[Etree[v].x]=Etree[v].w;
			if(Size[x]>maxn){
				Wson[x]=Etree[v].x; maxn=Size[x];
			}
		}
	}
}
void DFS2(int t,int x){
	PIH[x]=++top; Ba[PIH[x]]=val[x]; Top[x]=t; if(Wson[x])DFS2(t,Wson[x]);
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=Wson[x]&&Etree[v].x!=Fm[x][0])DFS2(Etree[v].x,Etree[v].x);
	}
}
struct node{
	int l,r,m,son[2];
	int maxn,minn,sum;
	bool tag;
};
node Seg[41000];
inline void Update(int p){
	std::swap(Seg[p].maxn,Seg[p].minn); Seg[p].maxn=-Seg[p].maxn; Seg[p].minn=-Seg[p].minn;
	Seg[p].sum=-Seg[p].sum; Seg[p].tag^=1;
}
inline void Pushdown(int p){
	if(!Seg[p].tag)return;
	Update(Seg[p].son[0]); Update(Seg[p].son[1]); Seg[p].tag=0;
}
inline void Union(int p){
	Seg[p].maxn=std::max(Seg[Seg[p].son[0]].maxn,Seg[Seg[p].son[1]].maxn);
	Seg[p].minn=std::min(Seg[Seg[p].son[0]].minn,Seg[Seg[p].son[1]].minn);
	Seg[p].sum=Seg[Seg[p].son[0]].sum+Seg[Seg[p].son[1]].sum;
}
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){
		Seg[p].maxn=Seg[p].minn=Seg[p].sum=Ba[l]; return p;
	}
	Seg[p].son[0]=Segbuild(l,Seg[p].m);Seg[p].son[1]=Segbuild(Seg[p].m+1,r);
	Union(p); return p;
}
void SegChange(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r){Update(p);return;}
	Pushdown(p);
	if(r<=Seg[p].m)SegChange(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)SegChange(Seg[p].son[1],l,r);
	else{
		SegChange(Seg[p].son[0],l,Seg[p].m); SegChange(Seg[p].son[1],Seg[p].m+1,r);
	}
	Union(p);
}
int SegGetmin(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].minn;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetmin(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)return SegGetmin(Seg[p].son[1],l,r);
	else return 
	std::min(SegGetmin(Seg[p].son[0],l,Seg[p].m),SegGetmin(Seg[p].son[1],Seg[p].m+1,r));
}
int SegGetmax(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].maxn;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetmax(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)return SegGetmax(Seg[p].son[1],l,r);
	else return
	std::max(SegGetmax(Seg[p].son[0],l,Seg[p].m),SegGetmax(Seg[p].son[1],Seg[p].m+1,r));
}
int SegGetsum(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetsum(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)return SegGetsum(Seg[p].son[1],l,r);
	else return
	SegGetsum(Seg[p].son[0],l,Seg[p].m)+SegGetsum(Seg[p].son[1],Seg[p].m+1,r);
}
int stk[21000];
int stktop;
void SegPoint(int k,int w){
	int v; stktop=0;
	for(v=1;Seg[v].l!=Seg[v].r;v=(k<=Seg[v].m?Seg[v].son[0]:Seg[v].son[1])){
		Pushdown(v); stk[++stktop]=v;
	}
	Seg[v].minn=Seg[v].maxn=Seg[v].sum=w;
	for(v=stktop;v>=1;v--)Union(stk[v]);
}
void lcainit(){
	logn=ceil(log2(n));
	for(int vj=1;vj<=logn;vj++)
	for(int vi=1;vi<=n;vi++)
	Fm[vi][vj]=Fm[Fm[vi][vj-1]][vj-1];
}
void Change(int u,int v){
	int fu,fv;
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fm[fu][0]]<Depth[Fm[fv][0]]){
			std::swap(fu,fv); std::swap(u,v);
		}
		SegChange(1,PIH[fu],PIH[u]); u=Fm[fu][0];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); SegChange(1,PIH[u],PIH[v]);
}
int Getsum(int u,int v){
	int fu,fv,sum=0;
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fm[fu][0]]<Depth[Fm[fv][0]]){
			std::swap(fu,fv); std::swap(u,v);
		}
		sum+=SegGetsum(1,PIH[fu],PIH[u]); u=Fm[fu][0];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); sum+=SegGetsum(1,PIH[u],PIH[v]);
	return sum;
}
int Getmax(int u,int v){
	int fu,fv,maxn=-none;
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fm[fu][0]]<Depth[Fm[fv][0]]){
			std::swap(fu,fv); std::swap(u,v);
		}
		maxn=std::max(maxn,SegGetmax(1,PIH[fu],PIH[u])); u=Fm[fu][0];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); maxn=std::max(maxn,SegGetmax(1,PIH[u],PIH[v]));
	return maxn;
}
int Getmin(int u,int v){
	int fu,fv,minn=none;
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fm[fu][0]]<Depth[Fm[fv][0]]){
			std::swap(fu,fv); std::swap(u,v);
		}
		minn=std::min(minn,SegGetmin(1,PIH[fu],PIH[u])); u=Fm[fu][0];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); minn=std::min(minn,SegGetmin(1,PIH[u],PIH[v]));
	return minn;
}
int lca(int u,int v){
	if(Depth[u]<Depth[v])std::swap(u,v);
	int k=Depth[u]-Depth[v],l=0;
	for(;k;k>>=1,l++)if(k&1)u=Fm[u][l];
	if(u==v)return u; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	for(;;){
		for(k=1;k<=logn;k++)if(Fm[u][k]==Fm[v][k])break;
		k--; u=Fm[u][k]; v=Fm[v][k]; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	}
}
int close(int u,int fu){
	if(Fm[u][0]==fu)return u; int k;
	for(;;){
		for(k=1;k<=logn;k++)if(Depth[Fm[u][k]]>=Depth[fu])break;
		k--; u=Fm[u][k]; if(Fm[u][0]==fu)return u;
	}
}
char ifdo[10];
int u,v,l,lu,lv,w;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w); u++; v++; ins(u,v,w); ins(v,u,w);
		etop++; E[etop].x=u; E[etop].y=v;
	}
	DFS1(0,1,1); top=0; DFS2(1,1); top=0; Segbuild(1,n);
	lcainit();
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		switch(ifdo[0]){
			case 'C':{
				scanf("%d%d",&u,&w);
				v=Depth[E[u].x]<Depth[E[u].y]?E[u].y:E[u].x;
				SegPoint(PIH[v],w);
				break;
			}
			case 'N':{
				scanf("%d%d",&u,&v); u++; v++;
				l=lca(u,v); Change(u,l); Change(v,l);
				break;
			}
			case 'S':{
				scanf("%d%d",&u,&v); u++; v++; 
				l=lca(u,v);
				w=Getsum(u,l)+Getsum(v,l)-(Getsum(l,l)<<1);
				printf("%d\n",w); break;
			}
			case 'M':{
				scanf("%d%d",&u,&v); u++; v++; if(Depth[u]<Depth[v])std::swap(u,v);
				l=lca(u,v);
				if(l==v){
					lu=close(u,l);
					if(ifdo[1]=='A')w=Getmax(u,lu);else w=Getmin(u,lu);
				}else{
					lu=close(u,l); lv=close(v,l);
					if(ifdo[1]=='A')w=std::max(Getmax(u,lu),Getmax(v,lv));
					else w=std::min(Getmin(u,lu),Getmin(v,lv));
				}
				printf("%d\n",w); break;
			}
		}
	}
}