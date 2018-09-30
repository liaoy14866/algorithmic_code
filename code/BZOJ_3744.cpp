#include<cstdio>
#include<cmath>

int n,m,Threshold,Num,Top;
int Lessi[50010][250],Times[50010][250];
//Lessi[i][j]表示前j块中比i小的数有多少个，Times[i][j]表示前j块中，与i相等的数有多少个
int Ans[250][250];//Ans[i][j]表示第i个块到第j个块的答案
int A[50010],C[50010],P[50010],B[50010];

inline void read(int &a){
    char c=getchar();
    bool f=0;
    for(a=0;(c<'0'||c>'9')&&c!='-';c=getchar());
    if(c=='-')f=1,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
    if(f)a=-a;
}

void swap(int &a,int &b){int c=a;a=b;b=c;}
void Sort(int l,int r){
	int tl=l,tr=r,x=B[(l+r)>>1];
	do{
		while(B[tl]<x)tl++; while(B[tr]>x)tr--;
		if(tl<=tr){
			swap(B[tl],B[tr]);
			swap(P[tl],P[tr]);
			tl++; tr--;
		}
	}
	while(tl<=tr);
	if(l<tr)Sort(l,tr);
	if(tl<r)Sort(tl,r);
}

int lowbit(int x){return(x&(-x));}
void Change(int p,int w){while(p<=Top){C[p]+=w;p+=lowbit(p);}}
int Getsum(int p){int w=0;while(p>0){w+=C[p];p-=lowbit(p);}return w;}

int main(){
	int Lastans=0;
	read(n);
	for(int i=1;i<=n;i++){read(B[i]);P[i]=i;};//读入
	
	Sort(1,n);
	B[0]=-1;
	for(int i=1;i<=n;i++)if(B[i]==B[i-1])A[P[i]]=A[P[i-1]];//离散
	else A[P[i]]=A[P[i-1]]+1;
	Top=A[P[n]];
	
	Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	
	for(int i=1;i<=Num;i++){
		int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
		for(int j=l;j<=r;j++){
			Change(A[j],1);
			Times[A[j]][i]++;//更新Times数组
		}
		for(int j=1;j<=Top;j++){
			Lessi[j][i]=Getsum(j-1);//更新Lessi数组
			Times[j][i]+=Times[j][i-1];
		}
	}
	
	for(int i=1;i<=Top;i++)C[i]=0;
	for(int i=1;i<=Num;i++){
		int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
		for(int j=r;j>=l;j--){
			Ans[i][i]+=Getsum(A[j]-1);//更新Ans数组
			Change(A[j],1);
		}
		for(int j=l;j<=r;j++)Change(A[j],-1);
	}
	for(int len=2;len<=Num;len++)
	for(int i=1;i<=Num;i++){
		int j=i+len-1; if(j>Num)break;
		Ans[i][j]=Ans[i+1][j]+Ans[i][i];
		int l=(i-1)*Threshold+1,r=i*Threshold;
		for(int k=l;k<=r;k++){Ans[i][j]+=Lessi[A[k]][j]-Lessi[A[k]][i];}
	}
	
	for(int i=1;i<=Top;i++)C[i]=0;
	read(m);
	for(int i=1;i<=m;i++){
		int l,r,pl,pr,Now=0;
		read(l); read(r);//读入
		l=l^Lastans; r=r^Lastans;
		if(l%Threshold==0)pl=l/Threshold;else pl=l/Threshold+1;
		if(r%Threshold==0)pr=r/Threshold;else pr=r/Threshold+1;//确定l与r所在的块
		Lastans=Ans[pl+1][pr-1];
		if(pl==pr){//如果l与r在同一个块，直接求逆序对
			Lastans=0;
			for(int j=r;j>=l;j--){
				Lastans+=Getsum(A[j]-1);
				Change(A[j],1);
			}
			for(int j=r;j>=l;j--)Change(A[j],-1);//还原数组
		}
		else{
			for(int j=l;j<=pl*Threshold;j++){//枚举左边剩余部分，找到中间的块中比左边剩余部分大的数有多少个
				Lastans+=Lessi[A[j]][pr-1]-Lessi[A[j]][pl];
				Now++; P[Now]=A[j];
			}
			for(int j=(pr-1)*Threshold+1;j<=r;j++){//枚举右边剩余部分，找到中间的块中比右边剩余部分小的数有多少个
				int Less=Lessi[A[j]][pr-1]-Lessi[A[j]][pl];
				int Same=Times[A[j]][pr-1]-Times[A[j]][pl];
				int More=(pr-pl-1)*Threshold-Less-Same;
				Now++; P[Now]=A[j];
				Lastans+=More;
			}
			for(int j=Now;j>=1;j--){//将剩余部分一起求一次逆序对
				Lastans+=Getsum(P[j]-1);
				Change(P[j],1);
			}
			for(int j=Now;j>=1;j--)Change(P[j],-1);//还原数组
		}
		printf("%d\n",Lastans);//输出
	}
	return 0;
}