#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
const double Pi=3.1415926535;
struct cop{
	double x,y;
	cop operator +(const cop &a){
		return (cop){x+a.x,y+a.y};
	}
	cop operator -(const cop &a){
		return (cop){x-a.x,y-a.y};
	}
	cop operator *(const cop &a){
		return (cop){x*a.x-y*a.y,x*a.y+y*a.x};
	}
};
struct poly{
	long long Ra[1<<18];
	cop Po[1<<18];
	void clear(){
		memset(Ra,0,sizeof(Ra));
		memset(Po,0,sizeof(Po));
	}
	void Rader(int len){
		int vi,vj,vt=0;
		for(vi=0;vi<len;vi++){
			if(vi>vt)std::swap(Po[vi],Po[vt]);
			for(vj=(len>>1);(vt^=vj)<vj;vj>>=1);
		}
	}
	void FFT(int len,int type){
		int h,vi,vj;
		Rader(len);
		for(h=2;h<=len;h<<=1){
			cop step={cos(2*Pi*type/h),sin(2*Pi*type/h)};
			for(vi=0;vi<len;vi+=h){
				cop vt,vw={1,0};
				for(vj=0;vj<(h>>1);vj++,vw=vw*step){
					vt=Po[vi+vj+(h>>1)]*vw;
					Po[vi+vj+(h>>1)]=Po[vi+vj]-vt;
					Po[vi+vj]=Po[vi+vj]+vt;
				}
			}
		}
	}
}A,C;
void conv(poly &a,poly &res,int len){
	int vi;
	a.FFT(len,1);
	for(vi=0;vi<len;vi++)res.Po[vi]=a.Po[vi]*a.Po[vi];
	res.FFT(len,-1);
	for(vi=0;vi<len;vi++)res.Ra[vi]=(int)(res.Po[vi].x/len+0.1);
}
int uplen(int x){
	int tmp=ceil(log2(x)); return 1<<tmp;
}
int n,maxn;
int Former[120000],Bucket[120000];
long long Sum[220000];
long long ans,all;
void linit(){
	int vi;
	A.clear(); C.clear(); memset(Sum,0,sizeof(Sum)); memset(Bucket,0,sizeof(Bucket));
	scanf("%d",&n);  maxn=0; ans=0; all=0;
	for(vi=1;vi<=n;vi++){
		scanf("%d",&Former[vi]); Bucket[Former[vi]]++;
		A.Po[Former[vi]].x++; maxn=std::max(maxn,Former[vi]);
	}
}
void handle(){
	int vi;
	for(vi=0;vi<=maxn<<1;vi++){
		if(!(vi&1))C.Ra[vi]-=Bucket[vi>>1];
		C.Ra[vi]>>=1;
	}
	for(vi=1;vi<=maxn<<1;vi++)Sum[vi]=Sum[vi-1]+C.Ra[vi];
	/*现在Ra是任意两条边和为x的方案数，计算两边之和小于或者等于x的方案数，就不需要考虑一大堆了*/
	for(vi=1;vi<=n;vi++)ans+=Sum[Former[vi]];
	all=(long long)n*(n-1)*(n-2)/6; ans=all-ans;
	printf("%.7f\n",(double)ans/all);
}
int T;
int main(){
	scanf("%d",&T);
	for(int al=1;al<=T;al++){
		linit();
		conv(A,C,uplen((maxn+1)<<1));
		handle();
	}
	return 0;
}