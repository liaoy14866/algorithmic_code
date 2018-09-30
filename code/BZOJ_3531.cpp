#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,top;
int w[110000],c[110000];//w[i]是要计算的权值（评级），c[i]元素的种类（宗教信仰）
struct Rec{
	int x,next;
};
int Tree[110000];
Rec Etree[210000];
inline void ins(int f,int s){
	top++; Etree[top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
int Fa[110000],Depth[110000],Size[110000],Wson[110000],PIH[110000],Top[110000],A[110000],B[110000];
//A[i]是按照树链剖分序的c[i]，B[i]是按照树链剖分序的w[i]。
/*树链剖分*/
void DFS1(int f,int x,int d){
	Fa[x]=f; Depth[x]=d; Size[x]=1; int maxn=0,v;
	for(v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=f){
			DFS1(x,Etree[v].x,d+1);
			Size[x]+=Size[Etree[v].x];
			if(Size[Etree[v].x]>maxn){
				Wson[x]=Etree[v].x; maxn=Size[Etree[v].x];
			}
		}
	}
}
void DFS2(int t,int x){
	PIH[x]=++top; Top[x]=t; A[PIH[x]]=c[x]; B[PIH[x]]=w[x]; if(Wson[x])DFS2(t,Wson[x]);
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=Fa[x]&&Etree[v].x!=Wson[x])DFS2(Etree[v].x,Etree[v].x);
	}
}
/*平衡树*/
int root[110000];//root的下标是A[i]
struct Bnode{
	int son[2],pos,B,Bmax,posmin,posmax,Bsum;//按照pos排序，前去后继的查找需要维护子树pos的最值。题目要求而维护B的最值与和
};
Bnode Btree[410000];
int Bfa[410000];
inline void Union(int p){//合并（好长……）
	Btree[p].Bmax=
	std::max(Btree[p].B,std::max(Btree[Btree[p].son[0]].Bmax,Btree[Btree[p].son[1]].Bmax));
	Btree[p].posmax=std::max(Btree[p].pos,
	std::max(Btree[Btree[p].son[0]].posmax,Btree[Btree[p].son[1]].posmax));
	Btree[p].posmin=Btree[p].pos;
	if(Btree[p].son[0])Btree[p].posmin=std::min(Btree[p].posmin,Btree[Btree[p].son[0]].posmin);
	if(Btree[p].son[1])Btree[p].posmin=std::min(Btree[p].posmin,Btree[Btree[p].son[1]].posmin);
	Btree[p].Bsum=Btree[p].B+Btree[Btree[p].son[0]].Bsum+Btree[Btree[p].son[1]].Bsum;
}
void Splay(int r,int p){//单旋
	int f=Bfa[p],gf=Bfa[f],son,v=Btree[f].son[0]!=p; if(f==root[r])root[r]=p;
	son=Btree[p].son[v^1]; Btree[p].son[v^1]=f; Btree[f].son[v]=son;
	Bfa[f]=p; Bfa[p]=gf; Bfa[son]=f;
	if(gf){v=Btree[gf].son[0]!=f; Btree[gf].son[v]=p;}
	Union(f); Union(p);
}
void Spins(int r,int B,int pos){//插入
	if(!root[r]){//如果初始为空的话，需要先插入两个左右端点，在区间查询的时候不会找不到前驱或者后继
		top+=2; root[r]=top; Btree[top].son[0]=top-1; Btree[top].pos=n+1; Bfa[top-1]=top;
		Btree[top].posmax=n+1;
	}
	int p=root[r],v;
	for(;;){
		v=pos>Btree[p].pos;
		if(!Btree[p].son[v]){
			top++; Btree[top].B=Btree[top].Bsum=Btree[top].Bmax=B; 
			Btree[top].pos=Btree[top].posmin=Btree[top].posmax=pos;
			Btree[p].son[v]=top; Bfa[top]=p; break;
		}else p=Btree[p].son[v];
	}
	while(top!=root[r])Splay(r,top);
}
inline bool precmp(int x,int w){//前驱
	return x<w;
}
int prefix(int r,int w){
	if(!precmp(Btree[root[r]].posmin,w))return 0;
	int p=root[r];
	while(!precmp(Btree[p].pos,w))p=Btree[p].son[0];
	for(;;){
		if(Btree[p].son[1]&&precmp(Btree[Btree[p].son[1]].posmin,w))p=Btree[p].son[1];
		else if(Btree[p].son[0]&&(!precmp(Btree[p].pos,w)))p=Btree[p].son[0];
		else break;
	}
	while(p!=root[r])Splay(r,p); return p;
}
inline bool sufcmp(int x,int w){//后继
	return x>w;
}
int suffix(int r,int w){
	if(!sufcmp(Btree[root[r]].posmax,w))return 0;
	int p=root[r];
	while(!sufcmp(Btree[p].pos,w))p=Btree[p].son[1];
	for(;;){
		if(Btree[p].son[0]&&sufcmp(Btree[Btree[p].son[0]].posmax,w))p=Btree[p].son[0];
		else if(Btree[p].son[1]&&(!sufcmp(Btree[p].pos,w)))p=Btree[p].son[1];
		else break;
	}
	while(p!=root[r])Splay(r,p); return p;
}
int SpGetsum(int ro,int l,int r){//Splay区间求和
	int pr=suffix(ro,r),pl=prefix(ro,l);if(Btree[pl].son[1]!=pr)Splay(ro,pr); 
	return Btree[Btree[pr].son[0]].Bsum;
}

int SpGetmax(int ro,int l,int r){//Splay中区间求max
	int pr=suffix(ro,r),pl=prefix(ro,l);if(Btree[pl].son[1]!=pr)Splay(ro,pr);
	return Btree[Btree[pr].son[0]].Bmax;
}
int Sppos(int r,int w){//查找w（一个位置）在Splay中的位置，保证w在Splay中
	int p;
	for(p=root[r];Btree[p].pos!=w;p=(Btree[p].pos<w?Btree[p].son[1]:Btree[p].son[0]));
	while(p!=root[r])Splay(r,p); return p;
}
void SpDelete(int r,int w){//删除一个节点。由于Splay中元素一定是不重合的，所以可这样操作
	int pr=suffix(r,w),pl=prefix(r,w);if(Btree[pl].son[1]!=pr)Splay(r,pr);
	Btree[pr].son[0]=0; Union(pr); Union(pl);
}
int Getmax(int u,int v){//树上求最值
	int fu,fv,maxn=0,col=A[PIH[u]];
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		maxn=std::max(maxn,SpGetmax(col,PIH[fu],PIH[u])); u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); maxn=std::max(maxn,SpGetmax(col,PIH[u],PIH[v])); return maxn;
}
int Getsum(int u,int v){//树上求和
	int fu,fv,sum=0,col=A[PIH[u]];
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		sum+=SpGetsum(col,PIH[fu],PIH[u]); u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); sum+=SpGetsum(col,PIH[u],PIH[v]); return sum;
}
inline void ch1(char &a){
	for(a=getchar();a!='C'&&a!='Q';a=getchar());
}
int main(){
	int i,u,v,t; char ifdo;
	read(n); read(m);//读入
	for(i=1;i<=n;i++)read(w[i]),read(c[i]);
	for(i=1;i<=n-1;i++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	DFS1(0,1,1); top=0; DFS2(1,1);//树链剖分
	top=0; for(i=1;i<=n;i++)Spins(A[i],B[i],i);
	for(i=1;i<=m;i++){
		ch1(ifdo);
		if(ifdo=='Q'){//查询
			ifdo=getchar(); read(u); read(v);
			t=(ifdo=='S'?Getsum(u,v):Getmax(u,v));
			printf("%d\n",t);
		}else{
			ifdo=getchar(); read(u); read(t);
			if(ifdo=='C'){//修改
				Spins(t,B[PIH[u]],PIH[u]); SpDelete(A[PIH[u]],PIH[u]); A[PIH[u]]=t;
			}else{
				v=Sppos(A[PIH[u]],PIH[u]); Btree[root[A[PIH[u]]]].B=t; Union(root[A[PIH[u]]]);
				B[PIH[u]]=t;
			}
		}
	}
}