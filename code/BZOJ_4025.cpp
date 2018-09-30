#include<cstdio>
#include<vector>
using namespace std;
char c;
inline void read(int &a){
	c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,T;
int Fa[100010],Size[100010];
bool Dis[100010];/*记录到fu的边的条数，1为奇数，2位偶数*/
struct ope{
	int x,y;//如果x为-1表示该次操作无效 
}O[200010];
int Getfa(int u,int &dis){
	dis=0; for(;u!=Fa[u];u=Fa[u])dis^=Dis[u]; return u;
}
bool unite(const int &u,const int &v,const int &type){
	/*如果没有奇环返回1，否则返回0*/
	/*type表示操作的编号*/
	int wu,fu=Getfa(u,wu); int wv,fv=Getfa(v,wv);
	if(fu==fv)return wu^wv;
	if(Size[fu]>Size[fv])swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; Dis[fu]=wu^wv^1;
	O[type].x=fu; O[type].y=fv;
	return 1;
}
void cancel(const int &type){
	if(!O[type].x)return;
	Fa[O[type].x]=O[type].x; Size[O[type].y]-=Size[O[type].x]; Dis[O[type].x]=0;
	O[type].x=O[type].y=0;
}
struct inf{
	int u,v,s,t,num;
};
inf edge;
bool Ans[100010];
vector<inf> A;
void Div(const int &l,const int &r,const vector<inf> &A){
	int vi; bool fl=1;
	for(vi=0;vi<A.size();vi++)if(A[vi].s==l&&A[vi].t==r){
		if(!unite(A[vi].u,A[vi].v,A[vi].num)){fl=0; break;}
	}
	if(!fl){
		for(vi--;vi>=0;vi--)if(A[vi].s==l&&A[vi].t==r)cancel(A[vi].num);
		for(vi=l;vi<=r;vi++)Ans[vi]=0;
		return;
	}
	if(l==r){
		for(vi--;vi>=0;vi--)if(A[vi].s==l&&A[vi].t==r)cancel(A[vi].num);
		Ans[l]=1;
		return;
	}
	vector<inf> L,R; inf tmp={0,0,0,0,0}; int m=(l+r)>>1;
	for(vi=0;vi<A.size();vi++)if(A[vi].s!=l||A[vi].t!=r){
		if(A[vi].t<=m)L.push_back(A[vi]);
		else
		if(m+1<=A[vi].s)R.push_back(A[vi]);
		else{
			tmp=A[vi]; tmp.t=m; L.push_back(tmp);
			tmp.t=A[vi].t; tmp.s=m+1; R.push_back(tmp);
		}
	}
	Div(l,m,L); Div(m+1,r,R);
	for(vi=0;vi<A.size();vi++)if(A[vi].s==l&&A[vi].t==r)cancel(A[vi].num);
}
int main(){
	int i;
	read(n); read(m); read(T);
	for(i=1;i<=n;i++)Fa[i]=i,Size[i]=1;
	for(i=1;i<=m;i++){
		read(edge.u); read(edge.v); read(edge.s); edge.s++; read(edge.t); edge.num=i;
		A.push_back(edge);
	}
	Div(1,T,A);
	for(i=1;i<=T;i++)if(Ans[i])printf("Yes\n");else printf("No\n");
}