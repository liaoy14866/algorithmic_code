#include<cstdio>
#include<algorithm>
#include<cstring>
long long intp=1e9+7,base=2333;//模数为intp，进制位为2333

int T;
int n;
bool flag;
long long BIT[2][11000];//树状数组
void Linit(){//初始化
	flag=false; memset(BIT,0,sizeof(BIT));
	scanf("%d",&n);
}
/*模意义下的加减乘除*/
inline long long plus(long long a,long long b){
	return (a+b)%intp;
}
inline long long minus(long long a,long long b){
	long long s=a-b; if(s<0)s+=(((abs(s)/intp)+2)*intp); s=s%intp;
	return s;
}
inline long long mul(long long a,long long b){
	return (a*b)%intp;
}
long long power(long long a,long long b){
	long long s=1;
	for(long long w=a;b;b>>=1,w=mul(w,w))if(b&1)s=mul(s,w);
	return s;
}
long long inver(long long x){
	return power(x,intp-2);
}
long long div(long long a,long long b){
	return mul(a,inver(b));
}
/*树状数组的修改与查询*/
inline int lowbit(int x){return x&(-x);} 
void Change(int ifdo,int p,long long w){
	for(int vi=p;vi<=n;vi+=lowbit(vi))BIT[ifdo][vi]=plus(BIT[ifdo][vi],w);
}
long long Getsum(int ifdo,int l,int r){
	long long s=0;
	for(int vi=r;vi;vi-=lowbit(vi))s=plus(s,BIT[ifdo][vi]);
	for(int vi=l-1;vi;vi-=lowbit(vi))s=minus(s,BIT[ifdo][vi]);
	return s;
}
/*ifdo为0表示前缀Hash值，ifdo为1表示后缀Hash值*/
/*Data(i)表示i这一位如果是1，那么在Hash函数中的数值是多少*/
long long Data(int ifdo,int p){
	if(!ifdo)return power(base,p);else return power(base,n-p+1);
}
long long Sum(int ifdo,int l,int r){//查询[l..r]的前缀Hash值或者后缀Hash值
	long long s=Getsum(ifdo,l,r);
	if(!ifdo)s=div(s,Data(0,l-1));else s=div(s,Data(1,r+1));
	return s;
}
int main(){
	scanf("%d",&T);
	for(int al=1;al<=T;al++){
		Linit();
		for(int i=1;i<=n;i++){
			int w;scanf("%d",&w);//读入
			if(flag)continue;//如果已经出现了等差子序列就可以不用操作了
			int len=std::min(w-1,n-w);//确定数字串的长度
			long long Pre=Sum(0,w-len,w-1),Suf=Sum(1,w+1,w+len);//前缀Hash值与后缀Hash值
			if(Pre!=Suf){//判断
				flag=true;
			}
			Change(0,w,Data(0,w)); Change(1,w,Data(1,w));//修改
		}
		if(flag)printf("Y\n");else printf("N\n");//输出
	}
}