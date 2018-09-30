#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
const double Pi=acos(-1.0);
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
void Rader(cop *a,const int &len){
	int vi,vj,vt=0;
	for(vi=0;vi<len;vi++){
		if(vi>vt)std::swap(a[vi],a[vt]);
		for(vj=(len>>1);(vt^=vj)<vj;vj>>=1);
	}
}
void FFT(cop *a,const int &len,const int &type){
	int h,vi,vj;
	Rader(a,len);
	for(h=2;h<=len;h<<=1){
		cop step={cos(2*Pi*type/h),sin(2*Pi*type/h)};
		for(vi=0;vi<len;vi+=h){
			cop vt,vw={1,0};
			for(vj=0;vj<(h>>1);vj++,vw=vw*step){
				vt=vw*a[vi+vj+(h>>1)];
				a[vi+vj+(h>>1)]=a[vi+vj]-vt;
				a[vi+vj]=a[vi+vj]+vt;
			}
		}
	}
}
cop A[1<<18],B[1<<18],C[1<<18];
char an[1<<18],bn[1<<18];
int lena,lenb,lenc;
int ax[1<<18],bx[1<<18];
int ans;
int stk[1<<18];
int main(){
	int vi,vj;
	scanf("%s",an); scanf("%s",bn);
	lena=strlen(an); lenb=strlen(bn);
	for(vi=0,vj=lenb-1;vi<vj;vi++,vj--)std::swap(bn[vi],bn[vj]);
	for(vi=0;vi<lena;vi++)ax[vi]=an[vi]-'a'+1;
	for(vi=0;vi<lenb;vi++)bx[vi]=(bn[vi]=='?'?0:bn[vi]-'a'+1);
	/*开始FFT*/
	lenc=ceil(log2(lena+lenb+1)); lenc=1<<lenc;
	for(vi=0;vi<lenc;vi++)A[vi].x=ax[vi]*ax[vi],A[vi].y=0;
	for(vi=0;vi<lenc;vi++)B[vi].x=bx[vi],B[vi].y=0;
	FFT(A,lenc,1); FFT(B,lenc,1);
	for(vi=0;vi<lenc;vi++)C[vi]=C[vi]+A[vi]*B[vi];
	
	for(vi=0;vi<lenc;vi++)A[vi].x=ax[vi],A[vi].y=0;
	for(vi=0;vi<lenc;vi++)B[vi].x=2*bx[vi]*bx[vi],B[vi].y=0;
	FFT(A,lenc,1); FFT(B,lenc,1);
	for(vi=0;vi<lenc;vi++)C[vi]=C[vi]-A[vi]*B[vi];
	
	for(vi=0;vi<lenc;vi++)A[vi].x=1,A[vi].y=0;
	for(vi=0;vi<lenc;vi++)B[vi].x=bx[vi]*bx[vi]*bx[vi],B[vi].y=0;
	FFT(A,lenc,1); FFT(B,lenc,1);
	for(vi=0;vi<lenc;vi++)C[vi]=C[vi]+A[vi]*B[vi];
	
	FFT(C,lenc,-1);
	for(vi=0;vi<lenc;vi++)C[vi].x=C[vi].x/lenc,C[vi].y=0;
	/*计算答案*/
	for(vi=lenb-1;vi<lena;vi++)if(C[vi].x<0.5)stk[++ans]=vi-lenb+1;
	printf("%d\n",ans);
	for(vi=lenb-1;vi<lena;vi++)if(C[vi].x<0.5)printf("%d\n",vi-lenb+1);
}