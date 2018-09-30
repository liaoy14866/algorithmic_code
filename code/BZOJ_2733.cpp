/*
题目大意：
给出n个点m条边的无向图，给出q个操作：
1.连一条边
2.查询连通块的第k小的值
解法：
启发式合并套一个有序的容器即可。我用的是Splay
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,q;
struct node{//第i个点的下标为i
	int x,s[2];
}Btr[110000];
int Fa[110000],Size[110000];
inline void unite(int p){
	Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;
}
void rot(int p){
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p;
	int s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){
	while(Fa[p])rot(p);
}
void ins(int p,int w,int v){
    for(;;){
        Size[p]++;
        if(Btr[p].x<w){
            if(!Btr[p].s[1]){
                Btr[p].s[1]=v; Fa[v]=p; break;
            }else p=Btr[p].s[1];
        }else{
            if(!Btr[p].s[0]){
                Btr[p].s[0]=v; Fa[v]=p; break;
            }else p=Btr[p].s[0];
        }
    }
    Splay(v);
}
int Rank(int p,int k){
	if(Size[Btr[p].s[0]]==k-1)return p;
	else
	if(Size[Btr[p].s[0]]>k-1)return Rank(Btr[p].s[0],k);
	else
	return Rank(Btr[p].s[1],k-Size[Btr[p].s[0]]-1);
}
int ro;
void ergodic(int p){//启发式合并，遍历size小的Splay，一个一个插入到size大的Splay
	if(Btr[p].s[0])ergodic(Btr[p].s[0]); if(Btr[p].s[1])ergodic(Btr[p].s[1]);
	Btr[p].s[0]=Btr[p].s[1]=Fa[p]=0; ins(ro,Btr[p].x,p); ro=p;
}
int Bfa[110000];//用了一个并查集，避免已经在同一个连通块里面的点重复合并
int Getfa(int u){
	if(!Bfa[u]){Bfa[u]=u;return u;}
	int v=u; for(;u!=Bfa[u];u=Bfa[u]);
	for(int o=Bfa[v];u!=Bfa[v];Bfa[v]=u,v=o,o=Bfa[v]);
	return u;
}
void Union(int u,int v){
	u=Getfa(u); v=Getfa(v); if(u==v)return;
	Splay(u); Splay(v); if(Size[u]>Size[v])std::swap(u,v);
	ro=v; ergodic(u); Bfa[u]=v;
}
int main(){
	int i,u,v,k; char c;
	read(n); read(m);//读入
	for(i=1;i<=n;i++){
		read(u); Btr[i].x=u; Size[i]=1;
	}
	for(i=1;i<=m;i++){
		read(u); read(v); Union(u,v);
	}
	read(q);
	for(i=1;i<=q;i++){
		for(c=getchar();c!='B'&&c!='Q';c=getchar());
		if(c=='B'){
			read(u); read(v); Union(u,v);//合并
		}else{
			read(u); read(k); Splay(u); 
			if(Size[u]>=k)v=Rank(u,k);else v=-1; printf("%d\n",v);//输出
		}
	}
}