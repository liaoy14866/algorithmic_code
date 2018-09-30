#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,M,root,top;
long long ans;
int val[110000],cost[110000];
struct Rec{
	int x,next;
}Etree[110000];
int Tree[110000];
inline void Trins(int f,int s){
	top++; Etree[top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
struct node{
	int s[2],maxp;
	long long sum;
}Btr[110000];
int Fa[110000],Size[110000];
inline void unite(int p){//更新子树信息
	Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;
	Btr[p].sum=Btr[Btr[p].s[0]].sum+Btr[Btr[p].s[1]].sum+cost[p];
	int v=Btr[Btr[p].s[cost[Btr[Btr[p].s[0]].maxp]<cost[Btr[Btr[p].s[1]].maxp]]].maxp;
	if(cost[p]>cost[v])Btr[p].maxp=p;else Btr[p].maxp=v;
}
void rot(int p){//旋转
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p,s;
	s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){while(Fa[p])rot(p);}//单旋
int ro;//临时记录根
void ins(int p,int v){//插入
    int u; for(u=cost[v]>cost[p];Btr[p].s[u];p=Btr[p].s[u],u=cost[v]>cost[p]);
    Btr[p].s[u]=v; Fa[v]=p; Splay(v); ro=v;
}
int pre(int p){//前驱
	Splay(p); for(p=Btr[p].s[0];Btr[p].s[1];p=Btr[p].s[1]); if(p)Splay(p); return p;
}
int suf(int p){//后继
	Splay(p); for(p=Btr[p].s[1];Btr[p].s[0];p=Btr[p].s[0]); if(p)Splay(p); return p;
}
void del(int p){//删除。如果用不可重复集合的Splay就可以直接旋转到根删除了。以为我们每次删除最大花费的节点
	int pr=suf(p); if(!pr){Fa[ro=Btr[p].s[0]]=0; return;} int pl=pre(p); if(!pl){Fa[ro=Btr[p].s[1]]=0;return;}
	if(Btr[pl].s[1]!=pr)rot(pr); Btr[pr].s[0]=0; unite(pr); unite(pl); ro=pl;
}
void ergodic(int p){//遍历插入
	if(Btr[p].s[0])ergodic(Btr[p].s[0]);
	if(Btr[p].s[1])ergodic(Btr[p].s[1]);
	Btr[p].s[0]=Btr[p].s[1]=Fa[p]=0; Btr[p].sum=cost[p]; Btr[p].maxp=p; Size[p]=1;
	if(cost[p]<=cost[Btr[ro].maxp]||cost[p]+Btr[ro].sum<=M){
		ins(ro,p); while(Btr[ro].sum>M){del(Btr[ro].maxp);}
	}
}
void Union(int u,int v){//合并
	Splay(u); Splay(v); if(Size[u]>Size[v])std::swap(u,v);
	ro=v; if(!Size[u])return; ergodic(u);
}
int DFS(int x){//返回以x为根的子树合并完成之后根的位置
	int e,no=x,ne;//no为now，记录当前的Splay的根，ne为next，记录将要合并的Splay的根
	for(e=Tree[x];e;e=Etree[e].next){
		ne=DFS(Etree[e].x); Union(ne,no); no=ro;//在这里把当前的Splay的根变为合并完成后的临时根ro
		if(ans<(long long)val[x]*Size[ro])ans=(long long)val[x]*Size[ro];//更新答案
	}
	return no;
}
int main(){
	int i,f;
	read(n); read(M);//读入
	for(i=1;i<=n;i++){
		read(f); if(f)Trins(f,i);else root=i; read(cost[i]); read(val[i]);
		if(cost[i]<=M){//直接定义i节点在Splay中的下标为i
			Size[i]=1; Btr[i].sum=cost[i]; Btr[i].maxp=i; if(ans<val[i])ans=val[i];
		}
	}
	DFS(root);//DFS求解
	printf("%lld\n",ans);//输出
}