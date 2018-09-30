#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const int intp=201314;
int n,q;
struct node{
	int s[2];
	int data,sum,tag;
	bool inv;
};
node Btr[110000];
int Fa[110000],Size[110000];
/*LCT*/
inline void Union(int p){
	Btr[p].sum=(Btr[Btr[p].s[0]].sum+Btr[Btr[p].s[1]].sum+Btr[p].data)%intp;
	Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;
}
void Down(int p){
	if(Btr[p].inv){
		std::swap(Btr[p].s[0],Btr[p].s[1]); Btr[p].inv^=1;
		Btr[Btr[p].s[0]].inv^=1; Btr[Btr[p].s[1]].inv^=1;
	}
	if(Btr[p].tag){
		(Btr[Btr[p].s[0]].tag+=Btr[p].tag)%=intp; (Btr[Btr[p].s[1]].tag+=Btr[p].tag)%=intp;
		(Btr[p].sum+=(long long)Size[p]*Btr[p].tag)%=intp;
		(Btr[p].data+=Btr[p].tag)%=intp; Btr[p].tag=0;
	}
}
inline bool Beroot(int p){
	return Btr[Fa[p]].s[0]!=p&&Btr[Fa[p]].s[1]!=p;
}
void rotate(int p){
	int f=Fa[p],gf=Fa[f],s,v=Btr[f].s[0]!=p;
	Down(f); Down(Btr[f].s[0]); Down(Btr[f].s[1]); Down(p); Down(Btr[p].s[0]); Down(Btr[p].s[1]);
	s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[f]=p; Fa[p]=gf; Fa[s]=f; Union(f); Union(p);
	if(gf){if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p;}
}
void Splay(int p){while(!Beroot(p))rotate(p);}
void Access(int x){
	for(int t=0;x;t=x,x=Fa[x]){
	    /*在这里只需要Down(x)，Down(Btr[x].s[0])。
	    对于此题而言，down(t)是没有影响的，0的data会改变但是sum不会改变。union的时候是没有影响的。自然也不会查询0的data
	    再者down(t)是不必要的，t是之前的x，而x已经被down过了
	    */
		Splay(x); Down(x); Down(Btr[x].s[0]); Btr[x].s[1]=t; Union(x);
	}
}
void Make_root(int x){
	Access(x); Splay(x); Btr[x].inv^=1;
}
void Link(int x,int y){
	Make_root(x); Fa[x]=y;
}
void Plus(int x){//把x到根的路径+1
	Access(x); Splay(x); Btr[x].tag++;
}
int Getsum(int x){//查询x到根的路径的点权和
	Access(x); Splay(x); return Btr[x].sum;
}
/*处理询问*/
struct inf{
	int x,p,k;
};
int Qtop;
inf Q[210000];
int Atop;
int Ans[110000];
bool vis[110000];
inline bool Acmp(const inf &a,const inf &b){return a.x<b.x;}
int main(){
	int i,u;
	read(n); read(q);
	for(i=1;i<=n;i++)Size[i]=1;
	for(i=2;i<=n;i++){read(u); u++; Link(i,u);}//读入
	Make_root(1);
	for(i=1;i<=q;i++){//做一些处理
		Qtop+=2; Q[Qtop].p=Q[Qtop-1].p=i; read(Q[Qtop-1].x); Q[Qtop-1].x--; read(Q[Qtop].x);
		read(u); Q[Qtop].k=Q[Qtop-1].k=++u; Q[Qtop-1].x++; Q[Qtop].x++;
	}
	std::sort(Q+1,Q+Qtop+1,Acmp); Atop=1;
	for(i=1;i<=Qtop;i++){//处理询问
		while(Atop<=Q[i].x&&Atop<=n){Plus(Atop); Atop++;}
		if(!vis[Q[i].p]){Ans[Q[i].p]-=Getsum(Q[i].k); vis[Q[i].p]=1;}else Ans[Q[i].p]+=Getsum(Q[i].k);
	}
	for(i=1;i<=q;i++){if(Ans[i]<0)Ans[i]+=intp; printf("%d\n",Ans[i]);}//输出
}