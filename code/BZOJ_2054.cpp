/*
题目大意：给出一个长度为n的序列，给出m个操作，每一次操作将一段区间染色。求最后的序列
解法：Fa[i]表示大于或者等于i坐标的第一个没有被染过色的
倒过来操作即可
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,p,q;
struct inf{
	int li,ri;
}O[10000040];
int Fa[1000040],A[1000040];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o;u!=Fa[v];o=Fa[v],Fa[v]=u,v=o);
	return u;
}
int main(){
	int i,u;
	read(n); read(m); read(p); read(q);
	for(i=1;i<=m;i++){
		O[i].li=(i*p+q)%n+1; O[i].ri=(i*q+p)%n+1; if(O[i].li>O[i].ri)std::swap(O[i].li,O[i].ri);
	}
	for(i=m;i>=1;i--){
		for(u=Getfa(O[i].li);u<=O[i].ri;Fa[u]=Getfa(u+1),u=Getfa(u))A[u]=i;
	}
	for(i=1;i<=n;i++)printf("%d\n",A[i]);
}