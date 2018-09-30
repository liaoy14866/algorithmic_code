/*8160ms*/
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int T;
int n,m,tot;
bool fl;
struct inf{
	int u,v;
}tmpE[11000],E[210*3];
inline bool Acmp(const inf &a,const inf &b){
	return a.u<b.u;
}
int tim;
int flag[210][210];
int order[210],PIC[210];
/*order[i]记录哈密顿回路按照顺序的编号，PIC[i]记录把哈密顿回路摆成一个环以后重新的编号*/
bool init(){
	int vi;
	read(n); read(m);
	for(vi=1;vi<=m;vi++){
		read(tmpE[vi].u); read(tmpE[vi].v);
	}
	for(vi=1;vi<=n;vi++)read(order[vi]),PIC[order[vi]]=vi;
	if(m>3*n)return 0;
	tim++;
	for(vi=1;vi<=n-1;vi++)flag[order[vi]][order[vi+1]]=flag[order[vi+1]][order[vi]]=tim;
	flag[order[n]][order[1]]=flag[order[1]][order[n]]=tim;
	tot=0;
	for(vi=1;vi<=m;vi++){
		if(flag[tmpE[vi].u][tmpE[vi].v]==tim)continue;
		E[++tot]=tmpE[vi];
	}
	for(vi=1;vi<=tot;vi++){
		E[vi].u=PIC[E[vi].u]; E[vi].v=PIC[E[vi].v]; if(E[vi].u>E[vi].v)swap(E[vi].u,E[vi].v);
	}
	sort(E+1,E+tot+1,Acmp);
	return 1;
}
int Arrmap[3*210*2];
struct rec{
	int x,ne;
}Arre[3*210*2*3*210*4];
int top;
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
void Build(){
	memset(Arrmap,0,sizeof(Arrmap)); memset(Arre,0,sizeof(Arre)); top=0;
	int vi,vj;
	for(vi=1;vi<=tot;vi++)
	for(vj=vi+1;vj<=tot;vj++)
	if(E[vi].u<E[vj].u&&E[vj].u<E[vi].v&&E[vi].v<E[vj].v){
		ins(vi,vj+tot); ins(vj+tot,vi);
		ins(vj,vi+tot); ins(vi+tot,vj);
	}
}
int stktop;
int vis[3*210*2],IN[3*210*2],stk[3*210*2],low[3*210*2],dfn[3*210*2],Nar[3*210*2];
int cnt,ant;
void Tarjan(int x){
	dfn[x]=low[x]=++cnt; stk[++stktop]=x; vis[x]=IN[x]=tim; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(vis[Arre[v].x]!=tim){
		Tarjan(Arre[v].x); low[x]=min(low[x],low[Arre[v].x]);
	}else if(IN[Arre[v].x]==tim)low[x]=min(low[x],low[Arre[v].x]);
	if(low[x]==dfn[x]){
		ant++;
		while(stk[stktop]!=x){
			Nar[stk[stktop]]=ant; IN[stktop]=0; stk[stktop--]=0;
		}
		Nar[x]=ant; IN[x]=0; stk[stktop--]=0;
	}
}
bool Handle(){
	int vi;
	tim++; cnt=ant=stktop=0;
	for(vi=1;vi<=tot<<1;vi++)if(vis[vi]!=tim)Tarjan(vi);
	for(vi=1;vi<=tot;vi++)if(Nar[vi]==Nar[vi+tot])return 0;
	return 1;
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		fl=init();
		if(fl){
			Build();
			fl=Handle();
		}
		if(fl)printf("YES\n");else printf("NO\n");
	}
}

/*116ms*/
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int T;
int n,m,tot;
bool fl;
struct inf{
	int u,v;
}tmpE[11000],E[210*3];
inline bool Acmp(const inf &a,const inf &b){
	return a.u<b.u;
}
int tim;
int flag[210][210];
int order[210],PIC[210];
/*order[i]记录哈密顿回路按照顺序的编号，PIC[i]记录把哈密顿回路摆成一个环以后重新的编号*/
bool init(){
	int vi;
	read(n); read(m);
	for(vi=1;vi<=m;vi++){
		read(tmpE[vi].u); read(tmpE[vi].v);
	}
	for(vi=1;vi<=n;vi++)read(order[vi]),PIC[order[vi]]=vi;
	if(m>3*n)return 0;
	tim++;
	for(vi=1;vi<=n-1;vi++)flag[order[vi]][order[vi+1]]=flag[order[vi+1]][order[vi]]=tim;
	flag[order[n]][order[1]]=flag[order[1]][order[n]]=tim;
	tot=0;
	for(vi=1;vi<=m;vi++){
		if(flag[tmpE[vi].u][tmpE[vi].v]==tim)continue;
		E[++tot]=tmpE[vi];
	}
	for(vi=1;vi<=tot;vi++){
		E[vi].u=PIC[E[vi].u]; E[vi].v=PIC[E[vi].v]; if(E[vi].u>E[vi].v)swap(E[vi].u,E[vi].v);
	}
	sort(E+1,E+tot+1,Acmp);
	return 1;
}
int Fa[3*210*2];
int Getfa(int u){
	int v=u,o; for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v]);
	return u;
}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	Fa[fu]=fv;
}
void Build(){
	int vi,vj;
	for(vi=1;vi<=tot<<1;vi++)Fa[vi]=vi;
	for(vi=1;vi<=tot;vi++)
	for(vj=vi+1;vj<=tot;vj++)
	if(E[vi].u<E[vj].u&&E[vj].u<E[vi].v&&E[vi].v<E[vj].v){
		Union(vi,vj+tot); Union(vi+tot,vj);
	}
}
bool Handle(){
	int vi;
	for(vi=1;vi<=tot;vi++)if(Getfa(vi)==Getfa(vi+tot))return 0;
	return 1;
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		fl=init();
		if(fl){
			Build();
			fl=Handle();
		}
		if(fl)printf("YES\n");else printf("NO\n");
	}
}