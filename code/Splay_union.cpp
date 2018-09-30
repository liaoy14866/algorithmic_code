struct node{
	int val,s[2];
}Btr[110000];
int Fa[110000],Size[110000];
inline void unite(int p){Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;}
void rot(int p){//单旋
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p;
	int s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){while(Fa[p])rot(p);}
int ro;
void ins(int p,int v){//插入，在根为p的Splay中插入Btr[v]这一个节点
	int u; for(u=Btr[v].val>Btr[p].val;Btr[p].s[u];p=Btr[p].s[u],u=Btr[v].val>Btr[p].val)Size[p]++;
	Btr[p].s[u]=v; Size[p]++; Fa[v]=p; Splay(v); ro=v;
}
int Rank(int p,int k){//查询排名为k的节点
	for(;Size[Btr[p].s[0]]!=k-1;)if(Size[Btr[p].s[0]]>k-1)p=Btr[p].s[0];else k-=Size[Btr[p].s[0]]+1,p=Btr[p].s[1];
	return p;
}
void ergodic(int p){//遍历
	if(Btr[p].s[0])ergodic(Btr[p].s[0]); if(Btr[p].s[1])ergodic(Btr[p].s[1]);//先处理子部分
	Fa[p]=Btr[p].s[0]=Btr[p].s[1]=0; Size[p]=1; ins(ro,p);//清空当前节点在原来的Splay中的父亲与儿子关系，仅保留最初始的状态
}
void Union(int u,int v){
	Splay(u); Splay(v); if(Size[u]>Size[v])std::swap(u,v);
	ro=v; ergodic(u);//遍历size小的部分
}