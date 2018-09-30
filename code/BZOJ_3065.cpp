#include<cstdio>
#include<cmath>
struct inf{
	int Top;
	int Element[500],P[500];
	//P应该记录这个点是这个块在原区间上的第几个数，这样应该就不必修改后面的块了 
	int Step[2];
};

const int maxn=8e4;
int A[50000];
inf Block[250],Temp;
int n,m,Threshold,tot,Now;
char ifdo[5];
int Num=1;

int Pos(int x){//找到x所在的块
	int p=1;
	tot=0;
	while(tot+Block[p].Top<x){tot+=Block[p].Top,p=Block[p].Step[1];}
	return p;
}

void swap(int &a,int &b){int c=a;a=b;b=c;}//交换

void Sort(int t,int l,int r){//排序。在初始化的时候需要对Element排序，P数组跟着走。于是手写了一个排序
	int tl=l,tr=r,x=Block[t].Element[(l+r)>>1];
	do{
		while(Block[t].Element[tl]<x)tl++;
		while(Block[t].Element[tr]>x)tr--;
		if(tl<=tr){
			swap(Block[t].Element[tl],Block[t].Element[tr]);
			swap(Block[t].P[tl],Block[t].P[tr]);
			tl++; tr--;
		}
	}
	while(tl<=tr);
	if(l<tr)Sort(t,l,tr);
	if(tl<r)Sort(t,tl,r); 
}

int check(int l,int r,int Line){
	//找到小于等于（一定要包含等于）Line的数有多少个 
	int Sum=0;
	int pl=Pos(l); int Numl=tot; int pr=Pos(r); int Numr=tot;
	int k=Block[pl].Step[1];
	if((k!=pr)&&(pl!=pr))
	while(1){
		if(Block[k].Element[1]<=Line){
			int kl=1; int kr=Block[k].Top; int kmid;
			while(kl!=kr){
				kmid=((kl+kr)>>1)+1;
				if(Block[k].Element[kmid]<=Line)kl=kmid;else kr=kmid-1;
			} 
			Sum+=kl;
		}
		if(k==Block[pr].Step[0])break;
		k=Block[k].Step[1];
	}	
	if(pl!=pr){
		for(k=1;k<=Block[pl].Top;k++)
		if((Block[pl].Element[k]<=Line)&&(Numl+Block[pl].P[k]>=l))Sum++;
		for(k=1;k<=Block[pr].Top;k++)
		if((Block[pr].Element[k]<=Line)&&(Numr+Block[pr].P[k]<=r))Sum++;
	}
	else{
		for(k=1;k<=Block[pl].Top;k++)
		if((Block[pr].Element[k]<=Line)&&(Numl+Block[pl].P[k]<=r)&&(Numr+Block[pr].P[k]>=l))Sum++;
	}
	return Sum;
}

void Change(int x,int w){//单点修改
	int p=Pos(x),Numt=tot;
	int k;
	for(k=1;k<=Block[p].Top;k++)if(Block[p].P[k]==x-Numt)break;
	Block[p].Element[k]=w;
	for(int l=k-1;l>=1;l--)if(Block[p].Element[l]>Block[p].Element[l+1]){
		swap(Block[p].Element[l],Block[p].Element[l+1]);
		swap(Block[p].P[l],Block[p].P[l+1]);
	}else break;
	for(int l=k+1;l<=Block[p].Top;l++)if(Block[p].Element[l-1]>Block[p].Element[l]){
		swap(Block[p].Element[l],Block[p].Element[l-1]);
		swap(Block[p].P[l],Block[p].P[l-1]);
	}else break;
}

void Copy(int s,int t){//裂块时复制信息
	Temp.Top=0;
	for(int l=1;l<=Block[s].Top;l++){
		if(Block[s].P[l]<=Threshold)
		{Temp.Top++; Temp.Element[Temp.Top]=Block[s].Element[l]; Temp.P[Temp.Top]=Block[s].P[l];}
		else
		{Block[t].Top++; Block[t].Element[Block[t].Top]=Block[s].Element[l]; Block[t].P[Block[t].Top]=Block[s].P[l]-Threshold;}
		Block[s].Element[l]=0; Block[s].P[l]=0;
	}
	Block[s].Top=Threshold;
	for(int l=1;l<=Block[s].Top;l++){Block[s].Element[l]=Temp.Element[l]; Block[s].P[l]=Temp.P[l];}
}

void Ins(int x,int w){//插入一个点
	int p=Pos(x); int Numt=tot;
	for(int k=1;k<=Block[p].Top;k++)if(Block[p].P[k]>=x-Numt)Block[p].P[k]++;
	Block[p].Top++; Block[p].Element[Block[p].Top]=w; Block[p].P[Block[p].Top]=x-Numt;
	for(int k=Block[p].Top-1;k>=1;k--)if(Block[p].Element[k]>Block[p].Element[k+1]){
		swap(Block[p].Element[k],Block[p].Element[k+1]);
		swap(Block[p].P[k],Block[p].P[k+1]);
	}
	if(Block[p].Top>Threshold<<1){//如果达到了阈值的两倍就裂块
		Num++;
		Copy(p,Num);
		Block[Num].Step[0]=p; Block[Num].Step[1]=Block[p].Step[1];
		Block[Block[p].Step[1]].Step[0]=Num; Block[p].Step[1]=Num;
	}
}
int main(){
	scanf("%d",&n);
	Threshold=ceil(sqrt(n));
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);}
	n++;
//样例中有一个地方，只有15个点，但插入到了第16个点的前面。题目描述中，插入到第k个点的前面是指插入完之后从左往右数是第k个。这样一来需要先放一个最末端的元素进去，方便插入
	
	for(int i=1;i<=n;i++){//初始化块的信息
		Block[Num].Top++;
		Block[Num].Element[Block[Num].Top]=A[i];
		Block[Num].P[Block[Num].Top]=Block[Num].Top;
		if(Block[Num].Top==Threshold){
			Sort(Num,1,Block[Num].Top);
			Num++;
		}
	}
	if(Block[Num].Top==0)Num--;
	else{Sort(Num,1,Block[Num].Top);}
	for(int i=1;i<Num;i++){Block[i].Step[1]=i+1;Block[i+1].Step[0]=i;}
	
	scanf("%d",&m);
	int l,r,w;
	int lastAns=0;
	
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		switch (ifdo[0]){
			case 'M':{
				scanf("%d%d",&l,&w);
				l=l^lastAns; w=w^lastAns;//修改
				Change(l,w);
				break;
			}
			case 'Q':{
				scanf("%d%d%d",&l,&r,&w);
				l=l^lastAns; r=r^lastAns; w=w^lastAns;
				//直接寻找小于等于mid的有多少个。有k个的所有数中，最小的那个一定是答案 
				int tl=0; int tr=maxn; int mid;
				while(tl!=tr){
					mid=(tl+tr)>>1;
					if (check(l,r,mid)>=w)tr=mid;else tl=mid+1;
					//如果有重复元素也没有关系 
				}
				lastAns=tr;
				printf("%d\n",lastAns);
				break;
			}
			case 'I':{//插入
				scanf("%d%d",&l,&w);
				l=l^lastAns; w=w^lastAns;
				Ins(l,w);
				break;
			}
		}
	}
}