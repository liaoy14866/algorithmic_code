#include<cstdio>
#include<cmath>
#include<algorithm>

struct inf{
	int Arr[250];
	int Num;
};
int T,n,m,Threshold,Num,maxn;
int A[51000];
inf Block[250];
char ifdo[5];

void read(int &a){
	char c=getchar();
	for(a=0;(c<'0'||c>'9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
	(a*=10)+=c-'0';
}

void Change(int p,int k){//修改，维护A数组与块数组
	int po,j;if(p%Threshold==0)po=p/Threshold;else po=p/Threshold+1;
	for(j=1;j<=Block[po].Num;j++)if(Block[po].Arr[j]==A[p])break;
	A[p]=k; Block[po].Arr[j]=k;
	while((Block[po].Arr[j]<Block[po].Arr[j-1])&&(j!=1)){
		std::swap(Block[po].Arr[j],Block[po].Arr[j-1]); j--;
	}
	while((Block[po].Arr[j]>Block[po].Arr[j+1])&&(j!=Block[po].Num)){
		std::swap(Block[po].Arr[j],Block[po].Arr[j+1]); j++;
	}
}

int EoM(int p,int k){//找块中有多少个数比k小或相等
	if(Block[p].Arr[1]>k)return 0;
	int xl=1,xr=Block[p].Num;
	while(xl!=xr){
		int xmid=((xl+xr)>>1)+1;
		if(Block[p].Arr[xmid]<=k)xl=xmid;else xr=xmid-1;
	}
	return xl;
}

int Find(int l,int r,int k){
	int pl,pr; if(l%Threshold==0)pl=l/Threshold;else pl=l/Threshold+1;
	if(r%Threshold==0)pr=r/Threshold;else pr=r/Threshold+1;
	int tl=0,tr=maxn;
	while(tl!=tr){//二分判断，找[l..r]有多少个数比mid小或相等
		int mid=(tl+tr)>>1,sum=0;
		for(int j=pl+1;j<=pr-1;j++)sum+=EoM(j,mid);
		if(pl!=pr){
			for(int j=l;j<=pl*Threshold;j++)if(A[j]<=mid)sum++;
			for(int j=(pr-1)*Threshold+1;j<=r;j++)if(A[j]<=mid)sum++;
		}
		else for(int j=l;j<=r;j++)if(A[j]<=mid)sum++;
		if(sum>=k)tr=mid;else tl=mid+1;
	}
	return tr;
}

int main(){
	read(T);//读入
	while(T!=0){
		T--;
		read(n); read(m);
		Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;//分块
		for(int i=1;i<=n;i++){read(A[i]);if(A[i]>maxn)maxn=A[i];}
		for(int i=1;i<=Num;i++){
			int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
			Block[i].Num=r-l+1;
			for(int j=l;j<=r;j++)Block[i].Arr[j-l+1]=A[j];
			std::sort(Block[i].Arr+1,Block[i].Arr+Block[i].Num+1); //每个块维护升序数组
		}
		for(int i=1;i<=m;i++){
			scanf("%s",ifdo);
			switch (ifdo[0]){
				case 'C':{
					int p,k; read(p); read(k);
					Change(p,k);//修改
					break;
				}
				case 'Q':{
					int l,r,k; read(l); read(r); read(k);
					int w=Find(l,r,k);//查询
					printf("%d\n",w);
				}
			}
		}
		for(int i=1;i<=Num;i++){//重新还原数组
			int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
			for(int j=l;j<=r;j++){A[j]=0;Block[i].Arr[j-l+1]=0;}
			Block[i].Num=0;
		}
		maxn=0;
	}
}