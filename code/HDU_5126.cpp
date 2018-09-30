#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int T;
int n,alltop,qtop,numtop,maxn;
struct num{
	int x,p;
}P[610000];
int B[610000];
inline bool Acmp(const num &a,const num &b){
	return a.x<b.x;
}
struct inf{
	int x,y,z1,z2,ans,num;
	/*修改：表示把(x,y,z1)++
	查询：表示查询(1..x,1..y,z1..z2)的和*/
	int opt;//0表示修改，非0表示查询，特别的，1表示加，-1表示减 
}A1[210000],tmp[210000],A2[210000];
inline bool xcmp(const inf &a,const inf &b){
	return a.x!=b.x?a.x<=b.x:a.y<=b.y;
}
inline bool ycmp(const inf &a,const inf &b){
	return a.y<=b.y;
}
int Ans1[51000],Ans2[51000];
void init(){
	memset(Ans1,0,sizeof(Ans1)); memset(Ans2,0,sizeof(Ans2)); alltop=qtop=numtop=0;
	int vi,opt,now=0;
	read(n);
	for(vi=1;vi<=n;vi++){
		read(opt);
		if(opt==1){
			A1[++alltop].opt=0; read(P[++numtop].x); read(P[++numtop].x); read(P[++numtop].x);
		}else{
			qtop++;
			read(P[++numtop].x); read(P[++numtop].x); read(P[++numtop].x); //(x1,y1,z1)
			read(P[++numtop].x); read(P[++numtop].x); read(P[++numtop].x); //(x2,y2,z2)
			A1[++alltop].opt=1; A1[alltop].num=qtop; A1[++alltop].opt=1; A1[alltop].num=qtop;
			A1[++alltop].opt=-1; A1[alltop].num=qtop; A1[++alltop].opt=-1; A1[alltop].num=qtop;
		}
	}
	for(vi=1;vi<=numtop;vi++)P[vi].p=vi;
	sort(P+1,P+numtop+1,Acmp);
	for(vi=1;vi<=numtop;vi++)B[P[vi].p]=B[P[vi-1].p]+(P[vi].x!=P[vi-1].x); maxn=B[P[numtop].p];
	now=1;
	for(vi=1;vi<=alltop;vi++)
	if(!A1[vi].opt){
		A1[vi].x=B[now++]; A1[vi].y=B[now++]; A1[vi].z1=B[now++]; A1[vi].z2=0; A1[vi].num=0; A1[vi].ans=0;
	}else{
		/*B[now..now+5]分别为坐标，A1[vi..vi+3]分别为询问*/
		A1[vi].x=B[now+3]; A1[vi].y=B[now+1+3]; A1[vi].z1=B[now+2]; A1[vi].z2=B[now+2+3]; A1[vi].ans=0;
		vi++;
		A1[vi].x=B[now]-1; A1[vi].y=B[now+1]-1; A1[vi].z1=B[now+2]; A1[vi].z2=B[now+2+3]; A1[vi].ans=0;
		vi++;
		A1[vi].x=B[now]-1; A1[vi].y=B[now+1+3]; A1[vi].z1=B[now+2]; A1[vi].z2=B[now+2+3]; A1[vi].ans=0;
		vi++;
		A1[vi].x=B[now+3]; A1[vi].y=B[now+1]-1; A1[vi].z1=B[now+2]; A1[vi].z2=B[now+2+3]; A1[vi].ans=0;
		now+=6;
	}
}
int BIT[610000];
void Change(int p,int w){
	for(;p<=maxn;p+=p&-p)BIT[p]+=w;
}
int Getsum(int p){
	int sum=0; for(;p;p-=p&-p)sum+=BIT[p]; return sum;
}
void CDQ2(const int &l,const int &r){
	/*进来的是A2*/
	if(l==r)return;
	int m=(l+r)>>1,tl,tr,tt;
	CDQ2(l,m); CDQ2(m+1,r);
	/*上来的是按照y排序的*/
	for(tl=l,tr=m+1;tr<=r;tr++){
		if(!A2[tr].opt)continue;
		while(ycmp(A2[tl],A2[tr])&&tl<=m){
			if(!A2[tl].opt)Change(A2[tl].z1,1); tl++;
		}
		A2[tr].ans+=Getsum(A2[tr].z2)-Getsum(A2[tr].z1-1);
	}
	for(tt=tl-1;tt>=l;tt--)if(!A2[tt].opt)Change(A2[tt].z1,-1);
	for(tl=l,tr=m+1,tt=l;tt<=r;tt++)
	if((tr>r)||(tl<=m&&ycmp(A2[tl],A2[tr])))tmp[tt]=A2[tl++];else tmp[tt]=A2[tr++];
	for(tt=l;tt<=r;tt++)A2[tt]=tmp[tt];
}
int putin1[210000];
inline void put1(const int &i1,const int &i2){
	A2[i2]=A1[i1]; A2[i2].ans=0; A2[i2].num=i2; putin1[i1]=i2;
}
void CDQ1(const int &l,const int &r){
	/*进来的是A1*/
	if(l==r)return;
	int m=(l+r)>>1,tl,tr,tt;
	CDQ1(l,m); CDQ1(m+1,r);
	/*上来的是按照x排序的*/
	for(tt=l-1,tl=l,tr=m+1;tr<=r;tr++){
		if(!A1[tr].opt)continue;
		while(xcmp(A1[tl],A1[tr])&&tl<=m){
			if(!A1[tl].opt)put1(tl,++tt); tl++;
		}
		put1(tr,++tt);
	}
	if(l<=tt){
		CDQ2(l,tt);
		int vi;
		for(vi=l;vi<=tt;vi++)Ans2[A2[vi].num]=A2[vi].ans;
		for(vi=l;vi<=r;vi++)if(putin1[vi])A1[vi].ans+=Ans2[putin1[vi]],putin1[vi]=0;
		for(vi=l;vi<=tt;vi++)Ans2[A2[vi].num]=0;
	}
	for(tt=l,tl=l,tr=m+1;tt<=r;tt++)
	if((tr>r)||(tl<=m&&xcmp(A1[tl],A1[tr])))tmp[tt]=A1[tl++];else tmp[tt]=A1[tr++];
	for(tt=l;tt<=r;tt++)A1[tt]=tmp[tt];
}
void write(){
	int vi;
	for(vi=1;vi<=alltop;vi++)if(A1[vi].opt)Ans1[A1[vi].num]+=A1[vi].ans*A1[vi].opt;
	for(vi=1;vi<=qtop;vi++)printf("%d\n",Ans1[vi]);
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		init();
		CDQ1(1,alltop);
		write();
	}
}