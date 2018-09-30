#include<cstdio>
#include<algorithm>


struct node{
	int l,r,son[2],sum;
};
int top,n,m;
int root[21000],last[21000];
node Seg[4500000];//主席树
int SegUpdate(int p,int k,int data){//主席树的更新
	top++; int now=top; Seg[now]=Seg[p]; Seg[now].sum+=data;
	if(Seg[p].l==Seg[p].r)return now;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=SegUpdate(Seg[p].son[0],k,data);
	else Seg[now].son[1]=SegUpdate(Seg[p].son[1],k,data);
	return now;
}
int SegBuild(int l,int r){//建一棵主席树
	top++; int now=top; Seg[now].l=l; Seg[now].r=r;
	if(l==r)return now;
	int m=(Seg[now].l+Seg[now].r)>>1;
	Seg[now].son[0]=SegBuild(l,m);
	Seg[now].son[1]=SegBuild(m+1,r);
	return now;
}
int SegGetsum(int p,int l,int r){//主席树的求和
	if((Seg[p].l==l)&&(Seg[p].r==r))return Seg[p].sum;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(r<=m)return SegGetsum(Seg[p].son[0],l,r);
	else
	if(l>=m+1)return SegGetsum(Seg[p].son[1],l,r);
	else
	return SegGetsum(Seg[p].son[0],l,m)+SegGetsum(Seg[p].son[1],m+1,r);
}
inline int lowbit(int x){return x&(-x);}//lowbit函数
void BITBuild(int p,int k){//初始化树状数组，只添加数字
	for(int vi=p;vi<=n;vi+=lowbit(vi))root[vi]=SegUpdate(root[vi],k,1);
}
void BITChange(int p,int For,int Now){//树状数组的修改，先删除数字，再添加数字
	for(int vi=p;vi<=n;vi+=lowbit(vi))root[vi]=SegUpdate(root[vi],For,-1);
	for(int vi=p;vi<=n;vi+=lowbit(vi))root[vi]=SegUpdate(root[vi],Now,1);
}
int BITGetsum(int l,int r,int minn,int maxn){//树状数组求区间[l..r]权值在[minn..maxn]上的和
	int sum=0;
	for(int vi=r;vi>0;vi-=lowbit(vi))sum+=SegGetsum(root[vi],minn,maxn);
	for(int vi=l;vi>0;vi-=lowbit(vi))sum-=SegGetsum(root[vi],minn,maxn);
	return sum;
}



struct inf1{
	int p,x,time;
};
struct inf2{
	int l,r,time;
};
struct inf3{
	int A,P;
	bool operator <(const inf3 &qa)const{return A<qa.A;}
};
int Qtop,Ctop,num,maxn;
char ifdo[10];
inf3 T[21000];
inf1 Ope[21000];
inf2 Que[21000];
int B[21000],tmp[21000];

int Btop;
struct Bnode{
	int data,son[2];
};
Bnode Btree[21000];
int Fa[21000];
struct Bnum{
	int root;
	void Splay(int p){//Splay单旋
		if(p==root)return;
		if(Fa[p]==root)root=p;
		int f=Fa[p],gf=Fa[f],son;
		if(Btree[f].son[0]==p){
			son=Btree[p].son[1]; Btree[p].son[1]=f; Btree[f].son[0]=son;
		}
		else{
			son=Btree[p].son[0]; Btree[p].son[0]=f; Btree[f].son[1]=son;
		}
		Fa[p]=gf; Fa[son]=f; Fa[f]=p;
		if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
	}
	void Ins(int w){//插入，根为w所在的节点
		if(!root){Btop++; Btree[Btop].data=w; root=Btop; return;}
		int p=root;
		for(;;){
			if(Btree[p].data>w){
				if(!Btree[p].son[0]){
					Btop++; Btree[Btop].data=w; Fa[Btop]=p; Btree[p].son[0]=Btop; p=Btop; break;
				}
				p=Btree[p].son[0];
			}
			else{
				if(!Btree[p].son[1]){
					Btop++; Btree[Btop].data=w; Fa[Btop]=p; Btree[p].son[1]=Btop; p=Btop; break;
				}
				p=Btree[p].son[1];
			}
		}
		while(p!=root)Splay(p);
	}
	int Posintree(int w){//查询w所在的位置（这里应该旋转到根的？）
		int p=root;
		while(Btree[p].data!=w)p=(Btree[p].data<w)?Btree[p].son[1]:Btree[p].son[0];
		return p;
	}
	int Prefix(int p){//查找前驱。如果p为最小的数字则返回0
		while(p!=root)Splay(p);
		if(!Btree[p].son[0])return 0;
		p=Btree[p].son[0];
		while(Btree[p].son[1])p=Btree[p].son[1];
		while(p!=root)Splay(p);
		return p;
	}
	int Suffix(int p){//查找后继，如果p节点为最大的数字，返回0
		while(p!=root)Splay(p);
		if(!Btree[p].son[1])return 0;
		p=Btree[p].son[1];
		while(Btree[p].son[0])p=Btree[p].son[0];
		while(p!=root)Splay(p);
		return p;
	}
	void Delete(int p){//删除p节点
		while(p!=root)Splay(p);
		int suf=Suffix(p); if(!suf){root=Btree[p].son[0];return;}
		int pre=Prefix(p); if(!pre){root=Btree[p].son[1];return;}
		if(Btree[pre].son[1]!=suf)Splay(suf);
		Btree[suf].son[0]=0;	
	}
};
Bnum PIL[21000];//储存一个数字在B中出现的位置



int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++)scanf("%d",&T[i].A),T[i].P=i;
	num=n;
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		if(ifdo[0]=='Q'){
			Qtop++; scanf("%d%d",&Que[Qtop].l,&Que[Qtop].r); Que[Qtop].time=i;
		}
		else{
			Ctop++; scanf("%d%d",&Ope[Ctop].p,&Ope[Ctop].x); Ope[Ctop].time=i;
			T[++num].A=Ope[Ctop].x; T[num].P=num;//预处理修改与询问
		}
	}
	std::sort(T+1,T+num+1);//离散排序
	for(int i=1;i<=num;i++)if(T[i].A==T[i-1].A)B[T[i].P]=B[T[i-1].P];
	else B[T[i].P]=B[T[i-1].P]+1;
	for(int i=n+1;i<=num;i++)Ope[i-n].x=B[i];//注意修改也要离散
	maxn=T[num].A;
	for(int i=1;i<=n;i++)PIL[B[i]].Ins(i);
	root[0]=SegBuild(0,n);//建一棵树状数组套主席树
	for(int i=1;i<=n;i++)root[i]=root[0];//复制根
	for(int i=1;i<=n;i++)last[i]=tmp[B[i]],tmp[B[i]]=i;
	for(int i=1;i<=n;i++)BITBuild(i,last[i]);
	int tot=1;
	for(int i=1;i<=Qtop;i++){
		while((Ope[tot].time<Que[i].time)&&(tot<=Ctop)){
			if(B[Ope[tot].p]==Ope[tot].x){tot++;continue;}
			int ne,la,pre,suf,p,tmp,w;
			/*
			p表示要修改的位置。tmp表示p修改前在Btree中的位置。
			suf表示p后面第一次出现的位置在Btree的位置。Pre表示p前面第一次出现的位置在Btree中的位置 
			ne表示suf的data，la表示pre的data  
			*/
			p=Ope[tot].p; tmp=PIL[B[p]].Posintree(p); 
			suf=PIL[B[p]].Suffix(tmp); ne=Btree[suf].data;
			
			if(ne){
				BITChange(ne,last[ne],last[p]);
				last[ne]=last[p];/*last*/
			}
			
			PIL[B[p]].Delete(tmp);
			
			/*
			p表示要修改的位置。tmp表示p修改后在Btree中的位置。w是要改成的数字 
			suf表示p后面第一次出现的位置在Btree的位置。Pre表示p前面第一次出现的位置在Btree中的位置 
			ne表示suf的data，la表示pre的data 
			*/
			w=Ope[tot].x; PIL[w].Ins(p); tmp=PIL[w].Posintree(p); B[p]=w;/*B*/
			pre=PIL[B[p]].Prefix(tmp); la=Btree[pre].data;
			suf=PIL[B[p]].Suffix(tmp); ne=Btree[suf].data;
			
			BITChange(p,last[p],la); last[p]=la;/*last*/
			if(ne){
				BITChange(ne,last[ne],p);
				last[ne]=p;/*last*/
			}
			tot++;
		}
		int w=BITGetsum(Que[i].l,Que[i].r,Que[i].l,Que[i].r);//查询
		printf("%d\n",Que[i].r-Que[i].l+1-w);//输出答案
	}
}