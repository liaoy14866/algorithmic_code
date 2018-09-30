#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
const double Pi=acos(-1.0);
struct cop{
	double x,y;
	cop operator +(const cop &a)const{
		return (cop){x+a.x,y+a.y};
	}
	cop operator -(const cop &a)const{
		return (cop){x-a.x,y-a.y};
	}
	cop operator *(const cop &a)const{
		return (cop){x*a.x-y*a.y,x*a.y+y*a.x};
	}
};
struct poly{
	cop Po[1<<16];
	int func;
	void Rader(const int &len){
		int vi,vj,vt=0;
		for(vi=0;vi<len;vi++){
			if(vi>vt)swap(Po[vi],Po[vt]);
			for(vj=(len>>1);(vt^=vj)<vj;vj>>=1);
		}
	}
	void FFT(const int &len,const int &type){
		int h,vi,vj;
		Rader(len);
		for(h=2;h<=len;h<<=1){
			cop step={cos(2*Pi*type/h),sin(2*Pi*type/h)};
			for(vi=0;vi<len;vi+=h){
				cop vw={1,0},vt;
				for(vj=0;vj<(h>>1);vj++,vw=vw*step){
					vt=vw*Po[vi+vj+(h>>1)];
					Po[vi+vj+(h>>1)]=Po[vi+vj]-vt;
					Po[vi+vj]=Po[vi+vj]+vt;
				}
			}
		}
	}
}X,Y,Z;
void conv(poly &a,poly &b,poly &res,const int &len){
	int vi; res.func=a.func+b.func;
	a.FFT(len,1); b.FFT(len,1);
	for(vi=0;vi<len;vi++)res.Po[vi]=a.Po[vi]*b.Po[vi];
	res.FFT(len,-1);
	for(vi=0;vi<len;vi++)res.Po[vi].x=(long long)(res.Po[vi].x/len+0.1),res.Po[vi].y=0;
}
int uplen(const int &x){
	int tmp; tmp=ceil(log2(x)); return 1<<tmp;
}
int n,maxn,Threshold,Num,len;
int A[100010];
int LBucket[30010],RBucket[30010];
long long ans;
int main(){
	int i,j,k,l,r;
	read(n);
	for(i=1;i<=n;i++)read(A[i]),maxn=max(A[i],maxn);
	Threshold=ceil(sqrt(maxn*log2(maxn)))*4;
	Threshold=3000;
	Num=n/Threshold; if(Num*Threshold<n)Num++;
	/*3个在同一个块中*/
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++){
			for(k=j+1;k<=r;k++)if(1<=(A[j]<<1)-A[k]&&(A[j]<<1)-A[k]<=maxn)ans+=LBucket[(A[j]<<1)-A[k]];
			LBucket[A[j]]++;
		}
		for(j=l;j<=r;j++)LBucket[A[j]]=0;
	}
	/*2个在同一个块中*/
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)
		for(k=j+1;k<=r;k++)if(1<=(A[j]<<1)-A[k]&&(A[j]<<1)-A[k]<=maxn)ans+=LBucket[(A[j]<<1)-A[k]];
		for(j=l;j<=r;j++)LBucket[A[j]]++;
	}
	for(i=Num;i>=1;i--){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)
		for(k=j+1;k<=r;k++)if(1<=(A[k]<<1)-A[j]&&(A[k]<<1)-A[j]<=maxn)ans+=RBucket[(A[k]<<1)-A[j]];
		for(j=l;j<=r;j++)RBucket[A[j]]++;
	}
	len=uplen(maxn+maxn+1);
	memset(LBucket,0,sizeof(LBucket));
	/*分别在不同的块*/
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)RBucket[A[j]]--;
		for(j=0;j<=maxn;j++)X.Po[j].x=LBucket[j],X.Po[j].y=0,Y.Po[j].x=RBucket[j],Y.Po[j].y=0;
		for(j=maxn+1;j<len;j++)X.Po[j].x=X.Po[j].y=Y.Po[j].x=Y.Po[j].y=0;
		conv(X,Y,Z,len);
		for(j=l;j<=r;j++)if(1<=A[j]<<1&&A[j]<<1<=len)ans+=Z.Po[A[j]<<1].x;
		for(j=l;j<=r;j++)LBucket[A[j]]++;
	}
	printf("%lld\n",ans);
}