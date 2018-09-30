/*
由于不能静态处理（空间不支持），于是需要离线操作。
对于y大于sqrt(n)的，推导步数不会超过sqrt(n)。我们直接推导。
对于y小于sqrt(n)的，只有sqrt(n)个数字，我们直接处理出答案。
*/
#include<cstdio>
#include<cmath>
#include<algorithm>

int n,m,Threshold,now;
int A[310000];
long long F[310000];
long long ans;
struct inf{
	int x,y,num;
	long long ans;
};
inf Que[300005];

inline bool Acmp(const inf &a,const inf &b){return a.y<b.y;}
inline bool Bcmp(const inf &a,const inf &b){return a.num<b.num;}

int main(){
	scanf("%d",&n); Threshold=ceil(sqrt(n));
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&Que[i].x,&Que[i].y),Que[i].num=i;
	std::sort(Que+1,Que+m+1,Acmp);//离线操作
	for(int i=1;i<=m;i++){
		if(Que[i].y<=Threshold){
			if(Que[i].y!=now){
				for(int j=n;j>=1;j--)F[j]=A[j]+F[j+Que[i].y];//DP求解
				now=Que[i].y;
			}
			Que[i].ans=F[Que[i].x];
		}
		else{
			int p=0;
			while(Que[i].x+p*Que[i].y<=n){Que[i].ans+=A[Que[i].x+p*Que[i].y];p++;}//直接推导
		}
	}
	std::sort(Que+1,Que+m+1,Bcmp);
	for(int i=1;i<=m;i++)printf("%I64d\n",Que[i].ans);//输出答案
}