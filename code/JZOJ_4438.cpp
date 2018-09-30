#include<cstdio>
#include<cmath>
#include<algorithm>

struct inf{
	int Tag;
	int Element[350];
};

const int maxn=2e7;
int A[120000],Belong[120000];//真正的权值为A[i]+Block[Belong[i]].Tag
inf Block[400];
int n,m,ifdo,Threshold,Num;

void Restructure(int p){//重构块
	int l=(p-1)*Threshold+1; int r=p*Threshold; if(r>n)r=n;
	for(int j=l;j<=r;j++){Block[p].Element[j-l+1]=A[j];}
	std::sort(Block[p].Element+1,Block[p].Element+r-l+1+1);
}

int check(int l,int r,int Line){
	//找到小于等于（一定要包含等于）Line的数有多少个 
	int Sum=0;
	for(int k=Belong[l]+1;k<=Belong[r]-1;k++){//二分统计整个块的答案
		if(Block[k].Element[1]+Block[k].Tag>Line)continue;
		int kl=1; int kr=Threshold; int kmid;
		while(kl!=kr){
			kmid=((kl+kr)>>1)+1;
			if(Block[k].Element[kmid]+Block[k].Tag<=Line)kl=kmid;else kr=kmid-1;
		} 
		Sum+=kl;
	} 
	if(Belong[l]!=Belong[r]){//暴力枚举剩余块的答案
		for(int k=l;k<=Belong[l]*Threshold;k++)if(A[k]+Block[Belong[k]].Tag<=Line)Sum++;
		for(int k=(Belong[r]-1)*Threshold+1;k<=r;k++)if(A[k]+Block[Belong[k]].Tag<=Line)Sum++;
	}
	else{for(int k=l;k<=r;k++)if(A[k]+Block[Belong[k]].Tag<=Line)Sum++;}
	return Sum;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);}
	int l,r,w;
	Threshold=ceil(sqrt(n)); 
	int Num=n/Threshold; if(Num*Threshold<n)Num++;
	
	for(int i=1;i<=Num;i++){Restructure(i);}//初始化重构块
	
	for(int i=1;i<=n;i++){if(i%Threshold==0)Belong[i]=i/Threshold;else Belong[i]=i/Threshold+1;}//初始化每个位置所属的块
	
	for(int i=1;i<=n;i++){
		scanf("%d",&ifdo);
		switch (ifdo){
			case 1:{
				scanf("%d%d%d",&l,&r,&w);//修改
				for(int j=Belong[l]+1;j<=Belong[r]-1;j++){Block[j].Tag+=w;}//修改整个块
				if(Belong[l]!=Belong[r]){//枚举剩余部分暴力修改
					for(int j=l;j<=Belong[l]*Threshold;j++){A[j]+=w;}
					for(int j=(Belong[r]-1)*Threshold+1;j<=r;j++){A[j]+=w;}
					Restructure(Belong[l]); Restructure(Belong[r]);
				}
				else{
					for(int j=l;j<=r;j++){A[j]+=w;}
					Restructure(Belong[l]);
				}
				break;
			}
			case 2:{//查询
				scanf("%d%d%d",&l,&r,&w);
				//直接寻找小于等于mid的有多少个。有k个的所有数中，最小的那个一定是答案 
				int tl=1; int tr=maxn; int mid;
				while(tl!=tr){
					mid=(tl+tr)>>1;
					if (check(l,r,mid)>=w)tr=mid;else tl=mid+1;
					//如果有重复元素也没有关系 
				}
				printf("%d\n",tr);
				break;
			}
		}
	}
}