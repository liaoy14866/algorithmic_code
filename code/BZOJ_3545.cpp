/*
题目大意：给出一张无向图，边有边权点有点权。给出m个询问：查询某个点仅通过边权不超过x的边的情况下，走到的点权第k大的点权。
离线排序。
启发式合并即可。
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}

int buf[60];
void write(int x){
	buf[0]=0;
	while(x)buf[++buf[0]]=x%10,x/=10;
	if(!buf[0])buf[0]=1,buf[1]=0;
	while(buf[0])putchar('0'+buf[buf[0]--]);
}

int n,m,q,now;
struct inf1{
	int u,v,w;
}E[510000];
struct inf2{
	int u,k,w,num,ans;
}Q[510000];
inline bool Acmp(const inf1 &a,const inf1 &b){
	return a.w<b.w;
}
inline bool Bcmp(const inf2 &a,const inf2 &b){
	return a.w<b.w;
}
inline bool Ccmp(const inf2 &a,const inf2 &b){
	return a.num<b.num;
}
struct node{
	int val,s[2];
}Btr[110000];
int Fa[110000],Size[110000];
inline void unite(int p){Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;}
void rot(int p){
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p;
	int s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){while(Fa[p])rot(p);}
int ro;
void ins(int p,int v){
	int u; for(u=Btr[v].val>Btr[p].val;Btr[p].s[u];p=Btr[p].s[u],u=Btr[v].val>Btr[p].val)Size[p]++;
	Btr[p].s[u]=v; Fa[v]=p; Size[p]++; Splay(v); ro=v;
}
int Rank(int p,int k){
	for(;Size[Btr[p].s[0]]!=k-1;)
	if(Size[Btr[p].s[0]]>k-1)p=Btr[p].s[0];
	else k-=Size[Btr[p].s[0]]+1,p=Btr[p].s[1];
	return p;
}
int Bfa[110000];
int Getfa(int u){
	if(!Bfa[u]){Bfa[u]=u;return u;}
	int v=u; for(;u!=Bfa[u];u=Bfa[u]);
	for(int o=Bfa[v];Bfa[v]!=u;Bfa[v]=u,v=o,o=Bfa[v]);
	return u;
}
void ergodic(int p){
	if(Btr[p].s[0])ergodic(Btr[p].s[0]); if(Btr[p].s[1])ergodic(Btr[p].s[1]);
	Fa[p]=Btr[p].s[0]=Btr[p].s[1]=0; Size[p]=1; ins(ro,p);
}
void Union(int u,int v){
	Splay(u); Splay(v); if(Size[u]>Size[v])std::swap(u,v); Bfa[u]=v;
	ro=v; ergodic(u);
}
int main(){
	int i,fu,fv;
	read(n); read(m); read(q);
	for(i=1;i<=n;i++)read(Btr[i].val),Size[i]=1;
	for(i=1;i<=m;i++){
		read(E[i].u); read(E[i].v); read(E[i].w);
	}
	for(i=1;i<=q;i++){
		read(Q[i].u); read(Q[i].w); read(Q[i].k); Q[i].num=i;
	}
	std::sort(E+1,E+m+1,Acmp); std::sort(Q+1,Q+q+1,Bcmp);
	now=1;
	for(i=1;i<=q;i++){
		while(E[now].w<=Q[i].w&&now<=m){
			fu=Getfa(E[now].u); fv=Getfa(E[now].v); if(fu!=fv)Union(fu,fv); now++;
		}
		Splay(Q[i].u);
		if(Size[Q[i].u]<Q[i].k)Q[i].ans=-1;else fu=Rank(Q[i].u,Size[Q[i].u]-Q[i].k+1),Q[i].ans=Btr[fu].val;
	}
	std::sort(Q+1,Q+q+1,Ccmp);
	for(i=1;i<=q;i++)/*printf("%d\n",Q[i].ans);*/write(Q[i].ans),puts("");
}