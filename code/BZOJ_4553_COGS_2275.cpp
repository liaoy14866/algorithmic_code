#include<cstdio>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
const int maxnum=1e5;
int n,m,numtop,ans;
struct num{
	int x,p;
}P[200010];
inline bool Pcmp(const num &a,const num &b){
	return a.x<b.x;
}
int B[200010],Pos[100010];
int minn[100010],maxn[100010],A[100010];
struct inf{
	int x,y,f,num;
}O[100010];
inline bool Acmp(const inf &a,const inf &b){
	return a.num<b.num;
}
inline bool Bcmp(const inf &a,const inf &b){
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
inline bool Ccmp(const inf &a,const inf &b){
	return a.x!=b.x?a.x<b.x:a.y<=b.y;
}
int BIT[100010];
void Change(int p,int w){
	for(;p<=maxnum;p+=p&-p)BIT[p]=max(BIT[p],w);
}
int Getmax(int p){
	int maxw=0; for(;p;p-=p&-p)maxw=max(maxw,BIT[p]); return maxw;
}
void Cancel(int p){
	for(;p<=maxnum;p+=p&-p)BIT[p]=0;
}
void CDQ(int l,int r){
	if(l==r){
		O[l].f++; return;
	}
	int m=(l+r)>>1,vi,vj;
	CDQ(l,m);
	for(vi=l;vi<=m;vi++)O[vi].x=A[O[vi].num],O[vi].y=maxn[O[vi].num];
	for(vi=m+1;vi<=r;vi++)O[vi].x=minn[O[vi].num],O[vi].y=A[O[vi].num];
	sort(O+l,O+m+1,Bcmp); sort(O+m+1,O+r+1,Bcmp);
	for(vj=l,vi=m+1;vi<=r;vi++){
		while(vj<=m&&Ccmp(O[vj],O[vi])){
			Change(O[vj].y,O[vj].f); vj++;
		}
		O[vi].f=max(O[vi].f,Getmax(O[vi].y));
	}
	sort(O+m+1,O+r+1,Acmp);
	for(vj--;vj>=l;vj--)Cancel(O[vj].y);
	CDQ(m+1,r);
}
int main(){
	int i,u,w;
	read(n); read(m);
	for(i=1;i<=n;i++)read(A[i]),minn[i]=maxn[i]=A[i];
	for(i=1;i<=m;i++){
		read(u); read(w); minn[u]=min(minn[u],w); maxn[u]=max(maxn[u],w);
	}
	for(i=1;i<=n;i++)O[i].num=i;
	CDQ(1,n);
	for(i=1;i<=n;i++)ans=max(ans,O[i].f);
	printf("%d\n",ans);
}