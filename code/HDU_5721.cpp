#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int T;
int n;
struct point{
	int x,y,num;
	void write(int p){
		fprintf(stderr,"P[%d].x=%d,y=%d,num=%d\n",p,x,y,num);
	}
}P[100010],Q[100010];
inline bool Acmp(const point &a,const point &b){
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
inline bool Bcmp(const point &a,const point &b){
	return a.y!=b.y?a.y<b.y:a.x<b.x;
}
long long ans,tmp,S;
int ansx,ansy,nowx,nowy;
void init(){
	int vi;
	read(n); S=0;
	for(vi=1;vi<=n;vi++)read(P[vi].x),read(P[vi].y),P[vi].num=vi;
	sort(P+1,P+n+1,Acmp);
}
long long PDIS(const point &x,const point &y){
	return ((long long)x.x-y.x)*(x.x-y.x)+((long long)x.y-y.y)*(x.y-y.y);
}
long long update(const point &x,const point &y){
	tmp=PDIS(x,y);
	if(tmp<=ans){
		ansx=x.num; ansy=y.num; ans=tmp;
	}
	return tmp;
}
long long Div(int l,int r){
	if(l==r)return 1e18;
	if(r-l+1==2)return update(P[l],P[r]);
	int m=(l+r)>>1,vi,vj,tl,tr,midline=P[m].x;
	long long mind=min(Div(l,m),Div(m+1,r));
	for(tl=l;tl<=r;tl++)if((long long)(P[tl].x-midline)*(P[tl].x-midline)<mind)break;
	for(tr=r;tr>=l;tr--)if((long long)(P[tr].x-midline)*(P[tr].x-midline)<mind)break;
	if(tl>tr)return mind;
	for(vi=tl;vi<=tr;vi++)Q[vi]=P[vi];
	sort(Q+tl,Q+tr+1,Bcmp);
	for(vi=tl;vi<=tr;vi++)
	for(vj=1;vj<=7;vj++)
	if(vi-vj>=tl)mind=min(mind,update(Q[vi],Q[vi-vj]));
	return mind;
}
int main(){
	int i;
	read(T);
	for(int al=1;al<=T;al++){
		init();
		ans=1e18; Div(1,n); S+=ans*(n-2); nowx=ansx; nowy=ansy;
		for(i=1;i<=n-1;i++)if(P[i].num==nowx)swap(P[i],P[i+1]);
		ans=1e18; Div(1,n-1); S+=ans;
		for(i=n;i>=2;i--)if(Acmp(P[i],P[i-1]))swap(P[i],P[i-1]);
		for(i=1;i<=n-1;i++)if(P[i].num==nowy)swap(P[i],P[i+1]);
		ans=1e18; Div(1,n-1); S+=ans;
		printf("%I64d\n",S);
	}
}