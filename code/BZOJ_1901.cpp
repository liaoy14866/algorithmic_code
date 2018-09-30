#include<cstdio>
#include<algorithm>

int n,m,maxn;
struct node{//主席树节点
	int l,r,son[2],sum;
};
int top;
int root[20010];
node Seg[6000000];//主席树

int SegBuild(int l,int r){//建一棵主席树
	top++; int now=top;
	Seg[now].l=l; Seg[now].r=r;
	if(l==r)return now; int m=(Seg[now].l+Seg[now].r)>>1;
	Seg[now].son[0]=SegBuild(l,m); Seg[now].son[1]=SegBuild(m+1,r);
	return now;
}

int SegUpdate(int p,int k,int data){//主席树的更新
	top++; int now=top;
	Seg[now]=Seg[p]; Seg[now].sum+=data;
	if(Seg[p].l==Seg[p].r)return now;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=SegUpdate(Seg[p].son[0],k,data);
	else Seg[now].son[1]=SegUpdate(Seg[p].son[1],k,data);
	return now;
}

int lowbit(int x){return x&(-x);}
void BITBuild(int p,int k){//初始化树状数组
	for(int vi=p;vi<=n;vi+=lowbit(vi))
	root[vi]=SegUpdate(root[vi],k,1);
}
void BITChange(int p,int former,int now){//树状数组的修改
	for(int vi=p;vi<=maxn;vi+=lowbit(vi))root[vi]=SegUpdate(root[vi],former,-1);
	for(int vi=p;vi<=maxn;vi+=lowbit(vi))root[vi]=SegUpdate(root[vi],now,1);
}

int DSeq[32],ASeq[32],Dtop,Atop;//用一个数组记录主席树上二分的节点
int SegDiv(int k){//在主席树上二分
	if((Seg[DSeq[Dtop]].l==Seg[DSeq[Dtop]].r)&&(Seg[ASeq[Atop]].l==Seg[ASeq[Atop]].r))
	return (Dtop!=0)?Seg[DSeq[Dtop]].l:Seg[ASeq[Atop]].l;
	int sum=0,vi;
	for(vi=1;vi<=Atop;vi++)sum+=Seg[Seg[ASeq[vi]].son[0]].sum;
	for(vi=1;vi<=Dtop;vi++)sum-=Seg[Seg[DSeq[vi]].son[0]].sum;
	if(sum>=k){
		for(vi=1;vi<=Atop;vi++)ASeq[vi]=Seg[ASeq[vi]].son[0];
		for(vi=1;vi<=Dtop;vi++)DSeq[vi]=Seg[DSeq[vi]].son[0];
		return SegDiv(k);
	}
	else{
		for(vi=1;vi<=Atop;vi++)ASeq[vi]=Seg[ASeq[vi]].son[1];
		for(vi=1;vi<=Dtop;vi++)DSeq[vi]=Seg[DSeq[vi]].son[1];
		return SegDiv(k-sum);
	}
}
int Query(int x,int y,int k){//查询
	Dtop=0,Atop=0;
	for(int vi=y;vi>0;vi-=lowbit(vi))ASeq[++Atop]=root[vi];
	for(int vi=x;vi>0;vi-=lowbit(vi))DSeq[++Dtop]=root[vi];
	return SegDiv(k);
}

struct inf1{
	int pos,time;
};
struct inf2{
	int l,r,k,time,ans;
};
struct inf3{
	int A,P;
};
int cnt,fnt,Ctop,Qtop;
int B[20010],Temp[20010];//B[i]是离散数组，Temp[i]记录没有重复数字的数字
char ifdo[10];
inf1 Ope[20010];//修改
inf2 Que[20010];//询问
inf3 Num[20020];//数字。其中Num[1..n]是A[1..n]，Num[n+1..cnt]是Ope[1..Ctop]

inline bool cmp2(const inf2 &a,const inf2 &b){return a.time<b.time;}
inline bool cmp3(const inf3 &a,const inf3 &b){return a.A<b.A;}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++)scanf("%d",&Num[i].A),Num[i].P=i; cnt=n;
	
	for(int i=1;i<=m;i++){//离线操作
		scanf("%s",ifdo);
		if(ifdo[0]=='C'){
			scanf("%d",&Ope[++Ctop].pos);Ope[Ctop].time=i; scanf("%d",&Num[++cnt].A),Num[cnt].P=cnt;
		}
		else{
			Que[++Qtop].time=i; scanf("%d%d%d",&Que[Qtop].l,&Que[Qtop].r,&Que[Qtop].k);
		}
	}
	std::sort(Num+1,Num+cnt+1,cmp3);//离散排序
	for(int i=1;i<=cnt;i++)if(Num[i].A==Num[i-1].A)B[Num[i].P]=B[Num[i-1].P];
	else{
		B[Num[i].P]=B[Num[i-1].P]+1;
		Temp[++fnt]=Num[i].A;
	}
	
	maxn=B[Num[cnt].P];
	root[0]=SegBuild(1,maxn);//建一棵空的主席树
	for(int i=1;i<=n;i++)root[i]=root[0];//所有的节点根均指向这棵空的主席树
	for(int i=1;i<=n;i++)BITBuild(i,B[i]);//初始化树状数组
	int now=1;
	for(int i=1;i<=Qtop;i++){
		while((Ope[now].time<Que[i].time)&&(now<=Ctop)){
			BITChange(Ope[now].pos,B[Ope[now].pos],B[now+n]);//修改
			B[Ope[now].pos]=B[now+n]; now++;//更新原数组的值
		}
		Que[i].ans=Temp[Query(Que[i].l-1,Que[i].r,Que[i].k)];//查询
	}
	std::sort(Que+1,Que+Qtop+1,cmp2);//按照时间排序
	for(int i=1;i<=Qtop;i++)printf("%d\n",Que[i].ans);//输出
}