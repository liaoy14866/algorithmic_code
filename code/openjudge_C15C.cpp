#include<cstdio>
#include<algorithm>
using namespace std;
char c;
inline void read(int &a){
	c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,k;
int Fa[110000],Size[110000];
struct rec{
	int u,v,tim;
}E[210000];
inline bool Acmp(const rec &a,const rec &b){
	return a.tim<b.tim;
}
struct inf{
	int x,nowy;//表示当前操作把x的父亲变为了nowy，对size的影响可以直接计算，x为-1表示无用操作 
}O[210000];
int Getfa(int u){
	for(;u!=Fa[u];u=Fa[u]); return u;
}
long long sum;
long long Combn2(const int &w){
	return (long long)w*(w-1)>>1;
}
void unite(const int &u,const int &v,const int &type){
	/*type为0表示不需要记录，否则type表示操作的编号，需要记录操作*/
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv){if(type)O[type].x=-1; return;} if(Size[fu]>Size[fv])swap(fu,fv);
	sum-=Combn2(Size[fu])+Combn2(Size[fv]);
	Fa[fu]=fv; Size[fv]+=Size[fu]; if(type)O[type].x=fu,O[type].nowy=fv;
	sum+=Combn2(Size[fv]);
}
void cancel(const int &type){
	if(O[type].x==-1){O[type].x=0;return;}
	sum-=Combn2(Size[O[type].nowy]);
	Size[O[type].nowy]-=Size[O[type].x]; Fa[O[type].x]=O[type].x;
	sum+=Combn2(Size[O[type].nowy])+Combn2(Size[O[type].x]);
	O[type].x=O[type].nowy=0;
}
int mr;
void init(){
	int vi;
	for(vi=1;vi<=m;vi++)scanf("%d%d%d",&E[vi].u,&E[vi].v,&E[vi].tim);
	sort(E+1,E+m+1,Acmp);
	for(vi=1;vi<=n;vi++)Fa[vi]=vi,Size[vi]=1;
	for(vi=m;E[vi].tim>k;vi--)unite(E[vi].u,E[vi].v,0);
	mr=vi;
}
long long Ans[110000];
void Div(const int &l,const int &r,const int &ml,const int &mr){
	int vi;
	if(l==r||ml>mr){
		for(vi=l;vi<=r;vi++)Ans[vi]=sum;
		return;
	}
	int m=(l+r)>>1,em;
	for(vi=mr;vi>=ml;vi--)if(E[vi].tim>m)unite(E[vi].u,E[vi].v,vi);else break;
	em=vi;
	Div(l,m,ml,em);
	for(vi=em+1;vi<=mr;vi++)cancel(vi);
	for(vi=em;vi>=ml;vi--)unite(E[vi].u,E[vi].v,vi);
	Div(m+1,r,em+1,mr);
	for(vi=ml;vi<=em;vi++)cancel(vi);
}
void write(){
	int vi;
	for(vi=1;vi<=k;vi++)printf("%lld\n",Ans[vi]);
}
int main(){
	while(scanf("%d%d%d",&n,&m,&k)!=EOF){
		init();
		Div(1,k,1,mr);
		write();
	}
}