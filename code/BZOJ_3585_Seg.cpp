#include<cstdio>
#include<algorithm>
using namespace std;
const int none=1e9+7;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,top;
int A[200010];
struct node{
	int minn,s[2];
}Seg[200010*33];
int root[200010];
void unite(int p){
	Seg[p].minn=min(Seg[Seg[p].s[0]].minn,Seg[Seg[p].s[1]].minn);
}
int update(int x,int l,int r,int k,int pos){
	int p=++top; Seg[p].s[0]=Seg[x].s[0]; Seg[p].s[1]=Seg[x].s[1];
	if(l==r){
		Seg[p].minn=pos; return p;
	}
	int m=(l+r)>>1; if(k<=m)Seg[p].s[0]=update(Seg[x].s[0],l,m,k,pos);else Seg[p].s[1]=update(Seg[x].s[1],m+1,r,k,pos);
	unite(p);
	return p;
}
int mex(int p,int l,int r,int key){
	if(l==r)return l;
	int m=(l+r)>>1;
	if(Seg[Seg[p].s[0]].minn<key)return mex(Seg[p].s[0],l,m,key);else return mex(Seg[p].s[1],m+1,r,key);
}
int main(){
	int i,l,r,w;
	read(n); read(m);
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=n;i++)root[i]=update(root[i-1],0,none,A[i],i);
	for(i=1;i<=m;i++){
		read(l); read(r); 
		w=mex(root[r],0,none,l); 
		printf("%d\n",w);
	}
}