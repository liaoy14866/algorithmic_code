/*
题目大意：给出一张无向图，要求使得其中一些边变为有向边，其他的边擦去，使得这张图每个点的入度为1.求是否存在方案。
个人解法：
对于一个连通块而言——
1.一棵树自然不可以。
2.一棵树的基础上多一条边，即生成了一个环。我们把这个环变为一个有向环，剩余的链都从环发散开。
3.图2的基础上多了若干条，删去即可。
于是问题变为求一个连通块是否又环。
用tag标记即可
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m;
int Fa[110000],Size[110000];
bool tag[110000];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;Size[u]=1;return u;}
	int v=u;
	for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v])Size[o]-=Size[v];
	return u;
}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv){tag[fu]|=1;return;}
	if(Size[fu]>Size[fv])std::swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; tag[fv]|=tag[fu];
}
int main(){
	int i,u,v;
	read(n); read(m);
	for(i=1;i<=m;i++){
		read(u); read(v); Union(u,v);
	}
	for(i=1;i<=n;i++){
		if(!tag[Getfa(i)]){printf("NIE");return 0;}
	}
	printf("TAK");
}