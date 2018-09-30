/*
题目大意：给出一张无向图，以及一些操作。每一个操作为删除一个点。
查询未操作时以及每一个操作之后，连通块的个数。
解法：操作倒过来做，并查集即可
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,k,top,now;
struct Rec{
	int x,next;
}Arre[410000];
int Arrmap[410000];
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
int stk[410000];
bool Des[410000];
int Fa[410000],Size[410000];
int Ans[410000];
int Getfa(int x){
	if(!Fa[x]){Fa[x]=x;Size[x]=1;return x;}
	int v=x,o;
	while(x!=Fa[x])x=Fa[x];
	while(x!=Fa[v]){
		o=Fa[v]; Size[o]-=Size[v]; Fa[v]=x; v=o;
	}
	return x;
}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	if(Size[fu]>Size[fv])std::swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; now--;
}
int main(){
	int i,u,v;
	read(n); read(m); now=n;
	for(i=1;i<=m;i++){
		read(u); read(v); u++; v++; ins(u,v); ins(v,u);
	}
	read(k); top=0; now=n-k;
	for(i=1;i<=k;i++){
		read(u); u++; stk[++top]=u; Des[u]=1;
	}
	for(i=1;i<=n;i++)if(!Des[i]){
		for(v=Arrmap[i];v;v=Arre[v].next){
			if(!Des[Arre[v].x])Union(i,Arre[v].x);
		}
	}
	Ans[top+1]=now;
	for(i=top;i>=1;i--){
		now++; Des[stk[i]]=0;
		for(v=Arrmap[stk[i]];v;v=Arre[v].next){
			if(!Des[Arre[v].x])Union(stk[i],Arre[v].x);
		}
		Ans[i]=now;
	}
	for(i=1;i<=top+1;i++)printf("%d\n",Ans[i]);
}