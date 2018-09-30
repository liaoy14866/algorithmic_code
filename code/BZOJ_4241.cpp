#include<cstdio>
#include<cmath>
#include<algorithm>
int A[120000],Temp[120000],Former[120000],FIT[120000];
/*
A为排序后的数组，Former为原来的数组，Temp开始是离散化所用，后面用于记录数字出现次数，
FIT记录Former数组中的第i个位置在Temp中的位置，也就是离散后的大小
*/
int Sum[120000][350];
//Sum[i][j]记录i这种数字在前j块的出现次数
long long Ans[350][350];
//Ans[i][j]记录第i块到第j块的答案
int n,m,Threshold,Num,top;

int Find(int x){//二分离散查找
	int tl=1; int tr=top; int mid;
	while(tl!=tr){
		mid=(tl+tr)>>1;
		if(Temp[mid]==x)return(mid);
		else
		if(x<Temp[mid])tr=mid-1;
		else tl=mid+1;
	}
	return tl;
}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);Former[i]=A[i];}
	std::sort(A+1,A+n+1);//排序
	Threshold=ceil(sqrt(n));//分块
	Num=n/Threshold; if(Num*Threshold<n)Num++;
	Temp[0]=-1;
	for(int i=1;i<=n;i++)if(A[i]==A[i-1])continue;else{top++;Temp[top]=A[i];}
	for(int i=1;i<=n;i++)FIT[i]=Find(Former[i]);//离散化
	
	for(int i=1;i<=Num;i++){//更新Sum数组
		int l=(i-1)*Threshold+1; int r=i*Threshold; if(r>n)r=n;
		for(int j=l;j<=r;j++){
			int p=FIT[j];
			Sum[p][i]++;
		}
	}
	for(int i=1;i<=top;i++)
	for(int j=1;j<=Num;j++)
	Sum[i][j]+=Sum[i][j-1];
	
	for(int i=1;i<=Num;i++){//更新Ans数组
		int l=(i-1)*Threshold+1; int r=i*Threshold; if(r>n)r=n;
		for(int j=l;j<=r;j++){
			int p=FIT[j];
			long long w=(long long)Former[j]*(Sum[p][i]-Sum[p][i-1]);
			if(Ans[i][i]<w)Ans[i][i]=w;
		}
	}
	for(int len=2;len<=Num;len++)
	for(int l=1;l<=Num;l++){
		int r=l+len-1; if(r>Num)break;
		Ans[l][r]=Ans[l+1][r];
		for(int k=(l-1)*Threshold+1;k<=l*Threshold;k++){
			int p=FIT[k];
			long long w=(long long)Former[k]*(Sum[p][r]-Sum[p][l-1]);
			if(Ans[l][r]<w)Ans[l][r]=w;
		}
	}
	
	for(int i=0;i<=top;i++)Temp[i]=0;//Temp变为用来计数的数组
	for(int i=1;i<=m;i++){
		int l,r,pl,pr;
		long long w=0,k;
		scanf("%d%d",&l,&r);
		if(l%Threshold==0)pl=l/Threshold;else pl=l/Threshold+1;
		if(r%Threshold==0)pr=r/Threshold;else pr=r/Threshold+1;//确定l与r所在的块pl与pr
		w=Ans[pl+1][pr-1];//得到中间的答案
		if(pr-pl+1>2){//扫描剩余部分
			for(int j=l;j<=pl*Threshold;j++)Temp[FIT[j]]++;
			for(int j=(pr-1)*Threshold+1;j<=r;j++)Temp[FIT[j]]++;//统计剩余部分的数字出现次数
			for(int j=l;j<=pl*Threshold;j++){
				int p=FIT[j];
				k=(long long)Former[j]*(Sum[p][pr-1]-Sum[p][pl]+Temp[p]);
				if(w<k)w=k;
			}
			for(int j=(pr-1)*Threshold+1;j<=r;j++){
				int p=FIT[j];
				k=(long long)Former[j]*(Sum[p][pr-1]-Sum[p][pl]+Temp[p]);
				if(w<k)w=k;
			}
			for(int j=l;j<=pl*Threshold;j++)Temp[FIT[j]]--;//恢复Temp数组
			for(int j=(pr-1)*Threshold+1;j<=r;j++)Temp[FIT[j]]--;
		}
		else{
			for(int j=l;j<=r;j++)Temp[FIT[j]]++;//统计剩余部分的数字出现次数
			for(int j=l;j<=r;j++){
				int p=FIT[j];
				k=(long long)Former[j]*Temp[p];
				if(w<k)w=k;
			}
			for(int j=l;j<=r;j++)Temp[FIT[j]]--;//恢复Temp数组
		}
		printf("%lld",w);//输出
	} 
}