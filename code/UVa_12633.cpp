#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<set>
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
	int func;
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
					vt=Po[vi+vj+(h>>1)]*vw;
					Po[vi+vj+(h>>1)]=Po[vi+vj]-vt;
					Po[vi+vj]=Po[vi+vj]+vt;
				}
			}
		}
	}
	void clear(){
		memset(Ra,0,sizeof(Ra)); memset(Po,0,sizeof(Po));
		func=0;
	}
}A,B,C;
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
int T;
int row,col,n;
struct point{
	int x,y;
}P[51000];
bool done[110000];
long long ans;
void linit(){
	int vi;
	A.clear(); B.clear(); C.clear(); ans=0;
	for(vi=1;vi<=n;vi++)done[P[vi].x+P[vi].y]=0;
	scanf("%d%d%d",&row,&col,&n);
	A.func=row-1; B.func=col-1;
	for(vi=1;vi<=n;vi++){
		scanf("%d%d",&P[vi].x,&P[vi].y);
		P[vi].x=row-P[vi].x; P[vi].y--;
		done[P[vi].x+P[vi].y]=1;
	}
};
void handle(){
	int vi;
	for(vi=1;vi<=n;vi++)A.Po[P[vi].x].x=-1,B.Po[P[vi].y].x=-1;
	for(vi=0;vi<=A.func;vi++)A.Po[vi].x++;
	for(vi=0;vi<=B.func;vi++)B.Po[vi].x++;
	conv(A,B,C,uplen(A.func+B.func+1));
	for(vi=0;vi<=C.func;vi++)if(!done[vi])ans+=C.Ra[vi];
}
int main(){
	scanf("%d",&T);
	for(int al=1;al<=T;al++){
		linit();
		handle();
		printf("Case %d: %lld\n",al,ans);
	}
}