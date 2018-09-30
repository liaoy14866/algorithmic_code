#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,Threshold,Num;
struct inf{//块内信息
	double A[1400],L[1400];
	int Atop,Ltop;
	int getmax(double w){//查询
		if(L[Ltop]<=w)return 0; int tl=1,tr=Ltop,mid;
		while(tl!=tr){
			mid=(tl+tr)>>1;
			if(L[mid]>w)tr=mid;else tl=mid+1;
		}
		return Ltop-tr+1;
	}
	void change(int pos,double w){//修改
		A[pos]=w; double maxn=0; Ltop=0;
		for(int vi=1;vi<=Atop;vi++)if(A[vi]>maxn)L[++Ltop]=maxn=A[vi];
	}
}B[1400];
int Getans(){//统计答案
	double maxn=0;int sum=0;
	for(int vi=1;vi<=Num;vi++){
		sum+=B[vi].getmax(maxn); maxn=std::max(maxn,B[vi].L[B[vi].Ltop]);
	}
	return sum;
}
void Change(int p,int h){//单点修改
	int po=p/Threshold+(p%Threshold?1:0); B[po].change(p-(po-1)*Threshold,(double)h/p);
}
int main(){
	int i,w,p,ans;
	read(n); read(m); Threshold=ceil(sqrt(n/2*log2(n))); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(i=1;i<=Num;i++)B[i].Atop=Threshold; if(Num*Threshold>n)B[Num].Atop=n-(Num-1)*Threshold;
	for(i=1;i<=m;i++){
		read(p); read(w); Change(p,w); ans=Getans(); printf("%d\n",ans);//修改与输出
	}
}