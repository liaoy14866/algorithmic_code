#include<cstdio>
#include<cmath>
#include<algorithm>
const int intp=786433;
const int g=10;
int T;
int power(int a,int b){
	long long s=1,w=a;
	for(;b;b>>=1,w=w*w%intp)if(b&1)s=s*w%intp;
	return s;
}
int A[1<<18],B[1<<18],C[1<<18];
void Rader(int *a,int len){
	int vi,vj,vt=0;
	for(vi=0;vi<len;vi++){
		if(vi>vt)std::swap(a[vi],a[vt]);
		for(vj=(len>>1);(vt^=vj)<vj;vj>>=1); 
	} 
}
void NTT(int *a,int len){
	Rader(a,len);
	int h,vi,vj;
	for(h=2;h<=len;h<<=1){
		int step=power(g,(intp-1)/h);
		for(vi=0;vi<len;vi+=h){
			long long vt,vw=1;
			for(vj=0;vj<(h>>1);vj++,vw=vw*step%intp){
				vt=vw*a[vi+vj+(h>>1)]%intp;
				a[vi+vj+(h>>1)]=(-vt+intp+a[vi+vj])%intp;
				a[vi+vj]=(a[vi+vj]+vt)%intp;
			} 
		}
	}
}
int uplen(int x){
	int tmp=ceil(log2(x)); return 1<<tmp;
}
int F[1<<18];
int func[1<<18];
void Div(int l,int r){
	if(l==r){F[l]=(F[l]+func[l])%intp;return;}
	int mid=(l+r)>>1;
	Div(l,mid);
	int vi,lenc=uplen(mid+r-(l<<1)+1);
	for(vi=0;vi<r-l+1;vi++)A[vi]=func[vi+1]; for(vi=r-l+1;vi<lenc;vi++)A[vi]=0;
	for(vi=0;vi<mid-l+1;vi++)B[vi]=F[vi+l]; for(vi=mid-l+1;vi<lenc;vi++)B[vi]=0;
	/*拿A[1..r-l+1]卷积F[l..mid]*/
	NTT(A,lenc); NTT(B,lenc);
	for(vi=0;vi<lenc;vi++)C[vi]=(long long)A[vi]*B[vi]%intp;
	NTT(C,lenc);
	for(vi=1;vi<(lenc>>1);vi++)std::swap(C[vi],C[lenc-vi]);
	int inv=power(lenc,intp-2);
	for(vi=0;vi<lenc;vi++)C[vi]=(long long)C[vi]*inv%intp;
	for(vi=mid+1;vi<=r;vi++)F[vi]=(F[vi]-C[vi-l-1]+intp)%intp;
	Div(mid+1,r);
}
void linit(){
	int vi;
	func[0]=1;
	for(vi=1;vi<=50010;vi++)func[vi]=(long long)func[vi-1]*vi%intp;
	Div(1,50010);
}
int n,k;
void slove(){
	int vi,vj,maxn,minn,x,c,ans=1;
	scanf("%d%d",&n,&k);
	for(vi=1;vi<=k;vi++){
		scanf("%d",&x); minn=maxn=0;
		for(vj=1;vj<=x;vj++){
			scanf("%d",&c);
			if(!minn||minn>c)minn=c; if(!maxn||maxn<c)maxn=c;
		}
		if(maxn-minn+1!=x)ans=0;
		ans=(long long)ans*F[x]%intp;
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	linit();
	for(int al=1;al<=T;al++)slove();
}