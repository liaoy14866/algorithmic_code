#include<cstdio>
#include<cmath>
#include<algorithm>

struct inf{
	int Arr[51000];//升序数组
	int Num,minnum;//Num维护当前块中的元素个数，minnum维护当前块中最小的数的个数
};

int n,m,Threshold,Num,ifdo,maxn;
int A[51000],Temp[250];
inf Block[250];

void read(int &a){
	char c=getchar();
	for(a=0;(c<'0'||c>'9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
}

void Change(int p,int w){//单点修改
	int po,j;if(p%Threshold==0)po=p/Threshold;else po=p/Threshold+1;//找到该点所在的块
	for(j=1;j<=Block[po].Num;j++)if(Block[po].Arr[j]==A[p])break;//且找到在块中的位置
	Block[po].Arr[j]=w; A[p]=w;//修改
	while((Block[po].Arr[j]<Block[po].Arr[j-1])&&(j!=1)){//插入排序调整
		std::swap(Block[po].Arr[j],Block[po].Arr[j-1]); j--;
	}
	while((Block[po].Arr[j]>Block[po].Arr[j+1])&&(j!=Block[po].Num)){
		std::swap(Block[po].Arr[j],Block[po].Arr[j+1]); j++;
	}
	Block[po].minnum=0;//重新更新minnum
	for(int j=1;j<=Block[po].Num;j++)
	if(Block[po].Arr[j]==Block[po].Arr[1])Block[po].minnum++;else break;
}

void Findmin(int l,int r){//查询[l..r]内最小的数以及有多少个
	int pl,pr,top,now=maxn+1,inoth=0; //用now记录最小值
	if(l%Threshold==0)pl=l/Threshold;else pl=l/Threshold+1;
	if(r%Threshold==0)pr=r/Threshold;else pr=r/Threshold+1;//找到l与r所在的块
	for(int j=pl+1;j<=pr-1;j++)
	if(Block[j].Arr[1]<now){top=1;now=Block[j].Arr[1];Temp[top]=j;}//用Temp记录拥有最小元素的块是哪些
	else if(Block[j].Arr[1]==now){top++;Temp[top]=j;}
	bool inblo=true;//inblo为true表示最小值在整块中，false表示在剩余部分
	if(pl!=pr){
		for(int j=l;j<=pl*Threshold;j++)//在剩余部分查找最小值
		if(A[j]<now){inblo=false; now=A[j]; inoth=1;}
		else if(A[j]==now)inoth++;//inoth记录，如果最小值在剩余部分，有多少个在剩余部分
		for(int j=(pr-1)*Threshold+1;j<=r;j++)
		if(A[j]<now){inblo=false; now=A[j]; inoth=1;}
		else if(A[j]==now)inoth++;
	}
	else{
		for(int j=l;j<=r;j++)
		if(A[j]<now){inblo=false; now=A[j]; inoth=1;}
		else if(A[j]==now)inoth++;
	}
	if(inblo==false){//如果最小值在剩余部分，直接输出now与inoth即可
		printf("%d ",now); printf("%d\n",inoth); return;
	}
	else{//否则，查询块中的有多少个最小值。同时加上剩余部分的有多少个最小值
		for(int j=1;j<=top;j++)inoth+=Block[Temp[j]].minnum;
		printf("%d ",now); printf("%d\n",inoth); return;
	}
}

int Div(int blo,int line){//二分在块blo中查找有多少个小于或等于line的数字
	if(Block[blo].Arr[1]>line)return 0;
	int tl=1,tr=Block[blo].Num;
	while(tl!=tr){
		int mid=((tl+tr)>>1)+1;
		if(Block[blo].Arr[mid]<=line)tl=mid;else tr=mid-1;
	}
	return tl;
}

void Getless(int l,int r,int line){//查找一个区间内有多少个比line小的数字
	int pl,pr,sum=0;
	if(l%Threshold==0)pl=l/Threshold;else pl=l/Threshold+1;
	if(r%Threshold==0)pr=r/Threshold;else pr=r/Threshold+1;//找到l与r所在的块
	for(int j=pl+1;j<=pr-1;j++)sum+=Div(j,line);//统计整个块的数量
	if(pl!=pr){//统计剩余部分数量
		for(int j=l;j<=pl*Threshold;j++)if(A[j]<=line)sum++;
		for(int j=(pr-1)*Threshold+1;j<=r;j++)if(A[j]<=line)sum++;
	}
	else for(int j=l;j<=r;j++)if(A[j]<=line)sum++;
	printf("%d\n",sum);//输出答案
}
int main(){
	read(n); read(m); Threshold=ceil(sqrt(n)); //读入
	Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(int i=1;i<=n;i++){read(A[i]);if(maxn<A[i])maxn=A[i];}//这个maxn，是原始A[i]中的，以及包括了之后修改的时候的值的最大值
	for(int i=1;i<=Num;i++){//初始化块的信息
		int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
		for(int j=l;j<=r;j++)Block[i].Arr[j-l+1]=A[j];
		Block[i].Num=r-l+1;
		std::sort(Block[i].Arr+1,Block[i].Arr+Block[i].Num+1);//排序
		for(int j=1;j<=Block[i].Num;j++)
		if(Block[i].Arr[j]==Block[i].Arr[1])Block[i].minnum++;else break;
	}
	for(int i=1;i<=m;i++){//处理询问
		read(ifdo);
		switch (ifdo){
			case 1:{
				int p,w; read(p); read(w); if(w>maxn)maxn=w;
				Change(p,w);
				break; 
			}
			case 2:{
				int l,r; read(l); read(r);
				Findmin(l,r);
				break;
			}
			case 3:{
				int l,r,k; read(l); read(r); read(k);
				Getless(l,r,k);
				break;
			}
		}
	}
}