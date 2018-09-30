#include<cstdio>
#include<cmath>
struct inf{
	int l,r,Block,Num;
};
int n,m,Threshold,Sum;
int A[105000],Bucket[25000],Ans[105000];
inf Que[105000];
inline void read(int &a){
    char c=getchar();
    bool f=0;
    for(a=0;(c<'0'||c>'9')&&c!='-';c=getchar());
    if(c=='-')f=1,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
    if(f)a=-a;
}

void swap(int &a,int &b){int c=a;a=b;b=c;}//排序
void Sort(int l,int r){
	int tl=l,tr=r,p=(l+r)>>1,x=Que[p].Block,y=Que[p].r;
	do{
		while((Que[tl].Block<x)||((Que[tl].Block==x)&&(Que[tl].r<y)))tl++;
		while((Que[tr].Block>x)||((Que[tr].Block==x)&&(Que[tr].r>y)))tr--;
		if(tl<=tr){
			swap(Que[tl].l,Que[tr].l);
			swap(Que[tl].r,Que[tr].r);
			swap(Que[tl].Block,Que[tr].Block);
			swap(Que[tl].Num,Que[tr].Num);
			tl++; tr--;
		}
	}
	while(tl<=tr);
	if(l<tr)Sort(l,tr);
	if(tl<r)Sort(tl,r);
}

void Moarr(int l1,int r1,int l2,int r2){//转移
	if(l1<l2)
	for(int j=l1;j<=l2-1;j++){
		Bucket[A[j]]--;
		if(Bucket[A[j]]>0){if(Bucket[A[j]]%2==1)Sum--;else Sum++;}
	}
	else
	for(int j=l1-1;j>=l2;j--){
		Bucket[A[j]]++;
		if(Bucket[A[j]]>1){if(Bucket[A[j]]%2==1)Sum--;else Sum++;}
	}
	if(r1<r2)
	for(int j=r1+1;j<=r2;j++){
		Bucket[A[j]]++;
		if(Bucket[A[j]]>1){if(Bucket[A[j]]%2==1)Sum--;else Sum++;}
	}
	else
	for(int j=r1;j>=r2+1;j--){
		Bucket[A[j]]--;
		if(Bucket[A[j]]>0){if(Bucket[A[j]]%2==1)Sum--;else Sum++;}
	}
}

int main(){
	read(n); read(m);
	for(int i=1;i<=n;i++)read(A[i]);
	Threshold=ceil(sqrt(n));
	for(int i=1;i<=m;i++){//读入
		read(Que[i].l); read(Que[i].r);
		Que[i].Num=i;
		Que[i].Block=Que[i].l/Threshold;
	}
	Sort(1,m);//排序
	int Lastl=1,Lastr=1;
	Bucket[A[1]]=1;
	for(int i=1;i<=m;i++){
		Moarr(Lastl,Lastr,Que[i].l,Que[i].r);//转移
		Lastl=Que[i].l; Lastr=Que[i].r;
		Ans[Que[i].Num]=Sum;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);//输出
}