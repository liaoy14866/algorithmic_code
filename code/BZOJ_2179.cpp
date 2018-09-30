#include<cstdio>
#include<cmath>
#include<algorithm>
struct cop{
	double x,y;
	cop operator +(const cop &q){
		return (cop){x+q.x,y+q.y};
	}
	cop operator -(const cop &q){
		return (cop){x-q.x,y-q.y};
	}
	cop operator *(const cop &q){
		return (cop){x*q.x-y*q.y,x*q.y+y*q.x};
	}
};
char c;
struct poly{
	int Ra[1<<17],func;
	cop Po[1<<17];
	void read(){
		int vi;
		for(c=getchar();c>'9'||c<'0';c=getchar());
		for(vi=0;vi<=func;vi++,c=getchar())Ra[func-vi]=c-'0',Po[func-vi].x=Ra[func-vi];
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
};
poly A,B,C;
void conv(poly &a,poly &b,poly &res,int len){
	int vi; res.func=a.func+b.func;
	a.FFT(len,1); b.FFT(len,1);
	for(vi=0;vi<len;vi++)res.Po[vi]=a.Po[vi]*b.Po[vi];
	res.FFT(len,-1);
	for(vi=0;vi<len;vi++)res.Ra[vi]=(int)(res.Po[vi].x/len+0.1);
}
int uplen(int x){
	int tmp=ceil(log2(x)); return 1<<tmp;
}
int n,rem;
int stk[1<<17];
int main(){
	int i;
	scanf("%d",&n);
	A.func=n-1; B.func=n-1;
	A.read(); B.read();
	conv(A,B,C,uplen(n<<1));
	for(i=0;i<=C.func-1;i++){
		rem+=C.Ra[i]; stk[C.func-i]=rem%10; rem/=10;
	}
	stk[0]=rem+C.Ra[C.func];
	for(i=0;i<=C.func;i++)printf("%d",stk[i]); 
}