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
int n,qtop,ctop,m,Threshold;
int nowl,nowr,nowans,nowtim;
struct que{
	int l,r,num,tim;
}Q[11000];
inline bool Acmp(const que  &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:(a.r/Threshold!=b.r/Threshold?a.r<b.r:a.tim<b.tim);
}
struct ope{
	int p,fr,to;
}O[11000];
int A[11000];
int Bucket[1100100];
void Put(int p,int w){
	Bucket[p]+=w;
	if(w<0&&Bucket[p]==0)nowans--; if(w>0&&Bucket[p]==1)nowans++;
}
void Change(int p,int fr,int to,int l,int r){
	A[p]=to; if(l<=p&&p<=r)Put(fr,-1),Put(to,1);
}
void Moarr(int l,int r,int tim){
	while(nowtim<tim){
		nowtim++; Change(O[nowtim].p,O[nowtim].fr,O[nowtim].to,nowl,nowr);
	}
	while(nowtim>tim){
		Change(O[nowtim].p,O[nowtim].to,O[nowtim].fr,nowl,nowr); nowtim--;
	}
	while(nowl>l){
		nowl--; Put(A[nowl],1);
	}
	while(nowr>r){
		Put(A[nowr],-1); nowr--;
	}
	while(nowr<r){
		nowr++; Put(A[nowr],1);
	}
	while(nowl<l){
		Put(A[nowl],-1); nowl++;
	}
}
int Ans[11000];
int main(){
	int i; char opt;
	read(n); read(m); Threshold=ceil(sqrt(n));
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=m;i++){
		for(opt=getchar();opt!='Q'&&opt!='R';opt=getchar());
		if(opt=='Q'){
			qtop++; read(Q[qtop].l); read(Q[qtop].r); Q[qtop].num=qtop; Q[qtop].tim=ctop;
		}else{
			ctop++; read(O[ctop].p); read(O[ctop].to); O[ctop].fr=A[O[ctop].p]; A[O[ctop].p]=O[ctop].to;
		}
	}
	sort(Q+1,Q+qtop+1,Acmp);
	nowl=1; nowr=1; nowans=1; nowtim=ctop; Bucket[A[1]]++;
	for(i=1;i<=qtop;i++){
		Moarr(Q[i].l,Q[i].r,Q[i].tim);
		Ans[Q[i].num]=nowans;
	}
	for(i=1;i<=qtop;i++)printf("%d\n",Ans[i]);
}