#include<cstdio>
#include<map>
#include<cmath>
#include<algorithm>
const int maxblock=410;
const int maxnum=250;
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
map<int,int> P;
int A[100010];
int n,m,tot,Threshold,Num;
struct inf{
	int x,num;
	bool operator <(const inf &a)const{
		return x<a.x;
	}
};
struct block{
	int tag,top;
	inf A[maxblock];
}B[maxnum];
int Bucket[200010];
bool flag[200010];
void Restruct(int po){
	if(!B[po].tag)return;
	int vi,l=(po-1)*Threshold+1,r=po*Threshold; if(r>n)r=n;
	for(vi=l;vi<=r;vi++)A[vi]=B[po].tag;
	for(vi=1;vi<=B[po].top;vi++)B[po].A[vi].x=B[po].A[vi].num=0;
	B[po].top=1; B[po].A[1].x=B[po].tag; B[po].A[1].num=r-l+1; B[po].tag=0;
}
inf tmp[maxblock]; int tmptop;
int l,r,w;
int pl,pr,vi;
int sil,sir,sipo,sinum;
bool IN;
void sichange(){
	sinum=0; IN=0;
	for(vi=sil;vi<=sir;vi++)flag[A[vi]]=1,Bucket[A[vi]]++,sinum+=(A[vi]==w);
	for(vi=1;vi<=B[sipo].top;vi++){
		if(flag[B[sipo].A[vi].x])B[sipo].A[vi].num-=Bucket[B[sipo].A[vi].x];
		if(B[sipo].A[vi].x==w){
			IN=1;
			B[sipo].A[vi].num+=sir-sil+1;
		}
	}
	if(!IN){
		B[sipo].top++; B[sipo].A[B[sipo].top].x=w; B[sipo].A[B[sipo].top].num=sir-sil+1;
	}
	for(vi=B[sipo].top-1;vi>=1;vi--)if(B[sipo].A[vi].x>B[sipo].A[vi+1].x)swap(B[sipo].A[vi],B[sipo].A[vi+1]);else break;
	for(vi=sil;vi<=sir;vi++)flag[A[vi]]=0,Bucket[A[vi]]=0,A[vi]=w;
	tmptop=0;
	for(vi=1;vi<=B[sipo].top;vi++)if(B[sipo].A[vi].num)tmp[++tmptop]=B[sipo].A[vi];
	for(vi=1;vi<=tmptop;vi++)B[sipo].A[vi]=tmp[vi]; B[sipo].top=tmptop;
}
void Change(){
	pl=(l-1)/Threshold+1; pr=(r-1)/Threshold+1;
	for(vi=pl+1;vi<=pr-1;vi++)B[vi].tag=w;
	/*我们把Bucket与flag用起来*/
	Restruct(pl); Restruct(pr);
	if(pl!=pr){
		sil=l; sir=pl*Threshold; sipo=pl;
		sichange();
		sil=(pr-1)*Threshold+1; sir=r; sipo=pr;
		sichange();
	}else{
		sil=l; sir=r; sipo=pl; sichange();
	}
}
int sum;
inf vk;
void Getsum(){
	pl=(l-1)/Threshold+1; pr=(r-1)/Threshold+1; sum=0;
	Restruct(pl); Restruct(pr);
	for(vi=pl+1;vi<=pr-1;vi++){
		if(B[vi].tag){
			sum+=(B[vi].tag==w)*Threshold; continue;
		}
		if(B[vi].A[B[vi].top].x<w)continue;
		vk=*lower_bound(B[vi].A+1,B[vi].A+B[vi].top+1,(inf){w,0}); if(vk.x!=w)continue;
		sum+=vk.num;
	}
	if(pl!=pr){
		for(vi=pl*Threshold;vi>=l;vi--)sum+=(A[vi]==w);
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)sum+=(A[vi]==w);
	}else for(vi=l;vi<=r;vi++)sum+=(A[vi]==w);
}
int main(){
	int i,j,opt;
	while(scanf("%d%d",&n,&m)!=EOF){
		tot=0; P.clear(); Threshold=ceil(sqrt(0.1*n*log2(n))); Num=n/Threshold; if(Num*Threshold<n)Num++;
		for(i=1;i<=n;i++){
			read(A[i]); if(P.find(A[i])==P.end())P[A[i]]=++tot; A[i]=P[A[i]];
		}
		for(i=1;i<=Num;i++){
			l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
			for(j=l;j<=r;j++)Bucket[A[j]]++;
			for(j=l;j<=r;j++)if(!flag[A[j]]){
				B[i].top++; B[i].A[B[i].top].x=A[j]; B[i].A[B[i].top].num=Bucket[A[j]]; flag[A[j]]=1;
			}
			for(j=l;j<=r;j++)flag[A[j]]=0,Bucket[A[j]]=0;
			sort(B[i].A,B[i].A+B[i].top+1);
		}
		for(i=1;i<=m;i++){
			read(opt); read(l); l++; read(r); r++; read(w);
			if(P.find(w)==P.end())P[w]=++tot; w=P[w];
			if(opt==1)Change();else Getsum(),printf("%d\n",sum);
			
		}
		for(i=1;i<=Num;i++)B[i].top=B[i].tag=0;
	}
}