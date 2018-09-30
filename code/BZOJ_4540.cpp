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
int n,m,Threshold,logn;
int A[100010],stk[100010];
int lastl[100010],lastr[100010];
int STl[100010][19],STr[100010][19];
long long Suml[100010],Sumr[100010];
//0为这个点变为左端点，往右延伸的部分。1位这个点变为右端点，往左延伸的部分 
int floorlog2[100010];
void floorlog2init(){
	int vi;
	for(vi=1;vi<=n;vi++)floorlog2[vi]=floor(log2(vi));
}
void suminit(){
	int vi,stktop;
	for(stktop=0,vi=1;vi<=n;vi++){
		while(stktop&&A[stk[stktop]]>=A[vi]){
			lastl[stk[stktop]]=vi; stk[stktop--]=0;
		}
		stk[++stktop]=vi;
	}
	while(stktop){
		lastl[stk[stktop]]=n+1; stk[stktop--]=0;
	}
	for(stktop=0,vi=n;vi>=1;vi--){
		while(stktop&&A[stk[stktop]]>=A[vi]){
			lastr[stk[stktop]]=vi; stk[stktop--]=0;
		}
		stk[++stktop]=vi;
	}
	while(stktop){
		lastr[stk[stktop]]=0; stk[stktop--]=0;
	}
	for(vi=1;vi<=n;vi++)Sumr[vi]=Sumr[lastr[vi]]+(long long)A[vi]*(vi-lastr[vi]);
	for(vi=n;vi>=1;vi--)Suml[vi]=Suml[lastl[vi]]+(long long)A[vi]*(lastl[vi]-vi);
}
void STinit(){
	int vi,vj; logn=ceil(log2(n));
	for(vi=1;vi<=n;vi++)STl[vi][0]=STr[vi][0]=vi;
	for(vj=1;vj<=logn;vj++)
	for(vi=1;vi<=n;vi++){
		if(vi+(1<<vj)-1<=n){
			STl[vi][vj]=A[STl[vi][vj-1]]<=A[STl[vi+(1<<(vj-1))][vj-1]]?STl[vi][vj-1]:STl[vi+(1<<(vj-1))][vj-1];
		}else STl[vi][vj]=n+1;
		if(vi-(1<<vj)+1>=1){
			STr[vi][vj]=A[STr[vi][vj-1]]<=A[STr[vi-(1<<(vj-1))][vj-1]]?STr[vi][vj-1]:STr[vi-(1<<(vj-1))][vj-1];
		}
	}
}
struct que{
	int l,r,num;
}Q[100010];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
int nowl,nowr;
long long nowans;
long long Ans[100010];
int len,pos;
long long Bution0(int l,int r){
	if(l==r)return A[l];
	len=floorlog2[r-l+1]; pos=A[STl[l][len]]<=A[STr[r][len]]?STl[l][len]:STr[r][len];
	return (long long)A[pos]*(r-pos+1)+(Suml[lastl[l]]-Suml[pos])+(long long)A[l]*(lastl[l]-l);
}
long long Bution1(int l,int r){
	if(l==r)return A[l];
	len=floorlog2[r-l+1]; pos=A[STl[l][len]]<A[STr[r][len]]?STl[l][len]:STr[r][len];
	return (long long)A[pos]*(pos-l+1)+(Sumr[lastr[r]]-Sumr[pos])+(long long)A[r]*(r-lastr[r]);
}
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; nowans+=Bution0(nowl,nowr);
	}
	while(nowr>r){
		nowans-=Bution1(nowl,nowr); nowr--;
	}
	while(nowr<r){
		nowr++; nowans+=Bution1(nowl,nowr);
	}
	while(nowl<l){
		nowans-=Bution0(nowl,nowr); nowl++;
	}
}
int main(){
	int i;
	read(n); read(m);
	for(i=1;i<=n;i++)read(A[i]);
	suminit();
	STinit();
	floorlog2init();
	for(i=1;i<=m;i++)read(Q[i].l),read(Q[i].r),Q[i].num=i;
	Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
	sort(Q+1,Q+m+1,Acmp);
	nowl=1; nowr=1; nowans=A[1];
	for(i=1;i<=m;i++){
		Moarr(Q[i].l,Q[i].r);
		Ans[Q[i].num]=nowans;
	}
	for(i=1;i<=m;i++)printf("%lld\n",Ans[i]);
}