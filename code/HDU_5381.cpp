#include<cstdio>
#include<vector> 
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
int c;
int gcd(int a,int b){
	for(c=a%b;c;a=b,b=c,c=a%b); return b;
}
int T;
int n,m,Threshold;
struct inf{
	int gys,pos;
};
vector<inf> L[100010],R[100010];
//L[i][j]表示以i为左端点，往右延伸的第j种gys的<值,左端点>，R[i]表示以i为右端点……<值,右端点>
int A[100010];
void gysinit(){
	int vi,vj,gys,now;
	for(vi=1;vi<=n;vi++){
		R[vi].push_back((inf){A[vi],vi}); now=A[vi];
		for(vj=0;vj<R[vi-1].size();vj++){
			gys=gcd(R[vi-1][vj].gys,now);
			if(gys==now)continue;
			R[vi].push_back((inf){gys,R[vi-1][vj].pos}); now=gys;
		}
	}
	for(vi=n;vi>=1;vi--){
		L[vi].push_back((inf){A[vi],vi}); now=A[vi];
		for(vj=0;vj<L[vi+1].size();vj++){
			gys=gcd(L[vi+1][vj].gys,now);
			if(gys==now)continue;
			L[vi].push_back((inf){gys,L[vi+1][vj].pos}); now=gys;
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
int vj; long long sum;
long long LCBT(int l,int r){
	sum=0;
	for(vj=1;vj<L[l].size();vj++){
		if(L[l][vj].pos>r)break; sum+=(long long)L[l][vj-1].gys*(L[l][vj].pos-L[l][vj-1].pos);
	}
	vj--;
	sum+=(long long)L[l][vj].gys*(r-L[l][vj].pos+1);
	return sum;
}
long long RCBT(int l,int r){
	sum=0;
	for(vj=1;vj<R[r].size();vj++){
		if(R[r][vj].pos<l)break; sum+=(long long)R[r][vj-1].gys*(R[r][vj-1].pos-R[r][vj].pos);
	}
	vj--;
	sum+=(long long)R[r][vj].gys*(R[r][vj].pos-l+1);
	return sum;
}
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; nowans+=LCBT(nowl,nowr);
	}
	while(nowr>r){
		nowans-=RCBT(nowl,nowr); nowr--;
	}
	while(nowr<r){
		nowr++; nowans+=RCBT(nowl,nowr);
	}
	while(nowl<l){
		nowans-=LCBT(nowl,nowr); nowl++;
	}
}
long long Ans[100010];
int main(){
	int i;
	read(T);
	for(int al=1;al<=T;al++){
		for(i=1;i<=n;i++)vector<inf>().swap(L[i]),vector<inf>().swap(R[i]);
		read(n);
		for(i=1;i<=n;i++)read(A[i]);
		gysinit();
		read(m); Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
		for(i=1;i<=m;i++)read(Q[i].l),read(Q[i].r),Q[i].num=i;
		sort(Q+1,Q+m+1,Acmp);
		nowl=1; nowr=1; nowans=A[1];
		for(i=1;i<=m;i++){
			Moarr(Q[i].l,Q[i].r);
			Ans[Q[i].num]=nowans;
		}
		for(i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	}
}