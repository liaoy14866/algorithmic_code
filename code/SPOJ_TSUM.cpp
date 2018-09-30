#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
const int Bon=6e4+7;
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
	int Ra[1<<18],func;
	cop Po[1<<18];
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
			cop step={cos(2*M_PI*type/h),sin(2*M_PI*type/h)};
			for(vi=0;vi<len;vi+=h){
				cop vt,vw={1,0};
				for(vj=0;vj<(h>>1);vj++,vw=vw*step){
					vt=vw*Po[vi+vj+(h>>1)];
					Po[vi+vj+(h>>1)]=Po[vi+vj]-vt;
					Po[vi+vj]=Po[vi+vj]+vt;
				}
			}
		}
	}
	void clear(){
		func=0;
		memset(Ra,0,sizeof(Ra)); memset(Po,0,sizeof(Po));
	}
	void RtoP(){
		int vi; memset(Po,0,sizeof(Po));
		for(vi=0;vi<=func;vi++)Po[vi].x=Ra[vi],Po[vi].y=0;
	}
}A1,A2,A3,C1,C2,C3,tmp1,tmp2;
void conv(poly &a,poly &b,poly &res,int len){
	int vi; res.func=a.func+b.func;
	a.FFT(len,1); b.FFT(len,1);
	for(vi=0;vi<len;vi++)res.Po[vi]=a.Po[vi]*b.Po[vi];
	res.FFT(len,-1);
	for(vi=0;vi<len;vi++)res.Ra[vi]=(int)(res.Po[vi].x/len+0.1);
	/*注意FFT里面只更新了Ra，res的Po是错误的，a与b只有Ra是正确的*/
}
void pow2(poly &a,poly &res,int len){
	int vi; res.func=a.func<<1;
	a.FFT(len,1);
	for(vi=0;vi<len;vi++)res.Po[vi]=a.Po[vi]*a.Po[vi];
	res.FFT(len,-1);
	for(vi=0;vi<len;vi++)res.Ra[vi]=(int)(res.Po[vi].x/len+0.1);
}
int uplen(int x){
	int now=ceil(log2(x)); return 1<<now;
}
int n,maxn;
int A[41000];
int Ans[1<<18];
/*统一所有坐标均+6e4*/
int main(){
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&A[i]); maxn=std::max(maxn,abs(A[i]));
	}
	for(i=1;i<=n;i++){
		A1.Po[A[i]+Bon].x++; A2.Po[(A[i]<<1)+Bon].x++; A3.Po[A[i]*3+Bon].x++;
		A1.Ra[A[i]+Bon]++; A2.Ra[(A[i]<<1)+Bon]++; A3.Ra[A[i]*3+Bon]++;
	}
	A1.func=maxn+Bon; A2.func=(maxn<<1)+Bon; A3.func=maxn*3+Bon;
	pow2(A1,tmp1,uplen(A1.func<<1|1));
	A1.RtoP(); tmp1.RtoP();
	conv(A1,tmp1,tmp2,uplen(A1.func+tmp1.func+1));
	for(i=Bon<<1;i<=tmp2.func;i++)Ans[i-(Bon<<1)]+=tmp2.Ra[i];
	tmp2.clear(); tmp1.clear(); A1.RtoP();
	conv(A1,A2,tmp1,uplen(A1.func+A2.func+1));
	for(i=Bon;i<=tmp1.func;i++)Ans[i-Bon]-=tmp1.Ra[i]*3;
	for(i=0;i<=A3.func;i++)(Ans[i]+=A3.Ra[i]<<1)/=6;
	for(i=0;i<=maxn*3+Bon;i++)if(Ans[i])printf("%d : %d\n",i-Bon,Ans[i]);
}