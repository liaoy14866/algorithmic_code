#include<cstdio>
#include<cmath>

int A[300000],Belong[300000],Step[300000],Aim[300000];
//A表示步数，Belong表示i所属的块，Step记录当前位置需要跳多少步可以跳出块，Aim记录当前位置跳出块时的位置
int n,m,ifdo,Threshold,Num;

void Restructure(int p){//重构块的信息
	int l=(p-1)*Threshold+1; int r=p*Threshold; if(r>n)r=n;
	for(int j=r;j>=l;j--){//注意逆序枚举
		if(j+A[j]>r){Aim[j]=j+A[j];Step[j]=1;}
		else{Aim[j]=Aim[j+A[j]];Step[j]=Step[j+A[j]]+1;}
	}
}

int main(){
	scanf("%d",&n);
	Threshold=ceil(sqrt(n));
	
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		if(i%Threshold==0){Belong[i]=i/Threshold;}else{Belong[i]=i/Threshold+1;}//初始化块的信息
	}
	if(Threshold*Threshold<n)Num=Threshold+1;else Num=Threshold;
	
	for(int i=Num;i>=1;i--){Restructure(i);}//重构块
	
	scanf("%d",&m);
	int p,k;
	for(int i=1;i<=m;i++){
		scanf("%d",&ifdo);
		switch (ifdo){
			case 1:{
				scanf("%d",&p); p++; k=0;
				while(p<=n){k+=Step[p];p=Aim[p];}//统计答案
				printf("%d\n",k);
				break;
			}
			case 2:{
				scanf("%d%d",&p,&k); p++;
				A[p]=k;
				Restructure(Belong[p]);//修改，并重构块
				break;
			}
		}
	}
}
