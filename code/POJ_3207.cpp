#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
int Fa[1100];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;return u;}
	int v=u,o; for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];u!=Fa[v];v=o,o=Fa[v])Fa[v]=u;
	return u;
}
void unite(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return; Fa[fu]=fv;
}
struct inf{
	int u,v;
}E[510];
inline bool mix(int l0,int r0,int l1,int r1){
	if(r0>r1){
		swap(l0,l1); swap(r0,r1);
	}
	return l0<l1&&l1<r0&&r0<r1;
}
int main(){
	int i,j; bool fl=1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&E[i].u,&E[i].v); E[i].u++; E[i].v++;
		if(E[i].u>E[i].v)swap(E[i].u,E[i].v);
	}
	for(i=1;i<=m;i++)
	for(j=i+1;j<=m;j++)if(mix(E[i].u,E[i].v,E[j].u,E[j].v)){
		unite(i,j+m); unite(i+m,j);
	}
	for(i=1;i<=m;i++)if(Getfa(i)==Getfa(i+m)){fl=0;break;}
	if(fl)printf("panda is telling the truth...\n");else printf("the evil panda is lying again\n");
}