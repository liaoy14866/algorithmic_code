#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
char c;
inline void read(int &a){
	c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,root;
struct rec{
	int x,ne;
}Arre[210000];
int Arrmap[110000];
int top;
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int Depth[110000],Size[110000],Wson[110000],PIH[110000],Top[110000],Fa[110000];
void DFS1(int f,int x,int d){
	int v,maxn=0;
	Depth[x]=d; Size[x]=1; Fa[x]=f;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f){
		DFS1(x,Arre[v].x,d+1); Size[x]+=Size[Arre[v].x];
		/*听说这里要用>=*/
		if(Size[Arre[v].x]>=maxn){maxn=Size[Arre[v].x];Wson[x]=Arre[v].x;}
	}
}
void DFS2(int f,int x){
	PIH[x]=++top; Top[x]=f; if(Wson[x])DFS2(f,Wson[x]); int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=Fa[x]&&Arre[v].x!=Wson[x])DFS2(Arre[v].x,Arre[v].x);
}
struct Segnode{
	int l,r,m,s[2];
	priority_queue<int> H[2];//0表示插入的 ,1表示删除的，
	void Handle(const int &w,const int &type){H[type].push(w);}
	int Qmax(){
		while(H[1].size())if(H[0].top()==H[1].top())H[0].pop(),H[1].pop();else break;
		/*如果没有元素的取top会RE……*/
		if(H[0].size())return H[0].top();else return -1;
	}
}Seg[110000<<2];
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; if(l==r)return p;
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	return p;
}
void SegChange(int p,const int &l,const int &r,const int &w,const int &type){
	if(Seg[p].l==l&&Seg[p].r==r){Seg[p].Handle(w,type);
	return;}
	if(r<=Seg[p].m)SegChange(Seg[p].s[0],l,r,w,type);
	else
	if(Seg[p].m+1<=l)SegChange(Seg[p].s[1],l,r,w,type);
	else
	SegChange(Seg[p].s[0],l,Seg[p].m,w,type),SegChange(Seg[p].s[1],Seg[p].m+1,r,w,type);
}
int SegGetmax(int p,int k){
	int maxn=Seg[p].Qmax(); 
	if(Seg[p].l==Seg[p].r)return maxn;
	if(k<=Seg[p].m)return max(maxn,SegGetmax(Seg[p].s[0],k));else return max(maxn,SegGetmax(Seg[p].s[1],k));
}
struct line{
	int l,r;
}L[30];
inline bool Acmp(const line &a,const line &b){
	return a.l<b.l;
}
void Getsection(int u,int v,const int &w,const int &type){
	int fu,fv;int ltop=0;
	for(;Top[u]!=Top[v];){
		fu=Top[u]; fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			swap(fu,fv); swap(u,v);
		}
		ltop++; L[ltop].l=PIH[fu]; L[ltop].r=PIH[u]; u=Fa[fu];
	}
	if(PIH[u]>PIH[v])swap(u,v); ltop++; L[ltop].l=PIH[u]; L[ltop].r=PIH[v];
	sort(L+1,L+ltop+1,Acmp);
	int vi,last;
	for(last=0,vi=1;vi<=ltop;last=L[vi].r,vi++)
	if(last+1<=L[vi].l-1)SegChange(1,last+1,L[vi].l-1,w,type);
	if(L[ltop].r+1<=n)SegChange(1,L[ltop].r+1,n,w,type);
}
struct opt{
	int u,v,w;
}O[210000];
int main(){
	int i,opt,u,v,w; srand((unsigned)time(NULL));
	read(n); read(m);
	for(i=1;i<n;i++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	root=rand()%n+1; root=4;
	DFS1(0,root,1); top=0; DFS2(root,root);
	top=0; Segbuild(1,n);
	for(i=1;i<=m;i++){
		read(opt);
		if(!opt){
			read(O[i].u); read(O[i].v); read(O[i].w); Getsection(O[i].u,O[i].v,O[i].w,0);
		}else if(opt==1){
			read(u); Getsection(O[u].u,O[u].v,O[u].w,1);
		}else{
			read(u); w=SegGetmax(1,PIH[u]); printf("%d\n",w);
		}
	}
}