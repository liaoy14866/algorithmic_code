#include<cstdio>
#include<algorithm>

struct Snode{//平衡树节点
	int data,son[2],num;//num记录当前权值的个数，意味着没有重复的数字
};
Snode Btree[4400000];//平衡树
int maxn,Btop;
int Size[4400000],Fa[4400000];
struct Bnode{//树状数组套平衡树
	int root;
	void Splay(int p){//单旋
		if(p==root)return; if(Fa[p]==root)root=p;
		int f=Fa[p],gf=Fa[f],son;
		if(Btree[f].son[0]==p){son=Btree[p].son[1]; Btree[f].son[0]=son; Btree[p].son[1]=f;}
		else{son=Btree[p].son[0]; Btree[f].son[1]=son; Btree[p].son[0]=f;}
		Fa[p]=gf; Fa[f]=p; Fa[son]=(!son)?0:f;
		if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
		Size[f]=Size[Btree[f].son[0]]+Size[Btree[f].son[1]]+Btree[f].num;
		Size[p]=Size[Btree[p].son[0]]+Size[Btree[p].son[1]]+Btree[p].num;
	}
	void Ins(int w){//插入节点，根为w的节点
		if(!root){
			Btop++; Btree[Btop].data=w; Btree[Btop].num=1; Size[Btop]=1; root=Btop; return;
		}
		int p=root;
		for(;;){
			Size[p]++; if(Btree[p].data==w){Btree[p].num++;break;}
			if(Btree[p].data>w){
				if(!Btree[p].son[0]){
					Btop++; Btree[Btop].data=w; Btree[Btop].num=1; 
					Size[Btop]=1; Fa[Btop]=p; Btree[p].son[0]=Btop; p=Btop; break;
				}else p=Btree[p].son[0];
			}
			else{
				if(!Btree[p].son[1]){
					Btop++; Btree[Btop].data=w; Btree[Btop].num=1; 
					Size[Btop]=1; Fa[Btop]=p; Btree[p].son[1]=Btop; p=Btop; break;
				}else p=Btree[p].son[1];
			}
		}
		while(p!=root)Splay(p);
	}
	int Posintree(int w){//找到w的位置，根为w所在的位置
		int p; for(p=root;Btree[p].data==w;p=(Btree[p].data>w)?Btree[p].son[0]:Btree[p].son[1]);
		while(p!=root)Splay(p); return p;
	}
	int Prefix(int p){//找到p的前驱，根为p的前驱
		while(p!=root)Splay(p); if(!Btree[p].son[0])return -1;
		p=Btree[p].son[0]; while(Btree[p].son[1])p=Btree[p].son[1];
		while(p!=root)Splay(p); return p;
	}
	int Suffix(int p){//找到p的后继，根为p的后继
		while(p!=root)Splay(p); if(!Btree[p].son[1])return -1;
		p=Btree[p].son[1]; while(Btree[p].son[0])p=Btree[p].son[0];
		while(p!=root)Splay(p); return p;
	}
	void Delete(int p){//删除p节点
		while(p!=root)Splay(p);
		if(Btree[p].num>1){Btree[p].num--;Size[p]--;return;}
		int suf=Suffix(p); if(suf==-1){root=Btree[root].son[0];Fa[root]=0;return;}
		int pre=Prefix(p); if(pre==-1){root=Btree[root].son[1];Fa[root]=0;return;}
		if(Btree[pre].son[1]!=suf)Splay(suf);
		Size[pre]--; Size[suf]--; Btree[suf].son[0]=0; Fa[p]=0;
	}
};

Bnode BIT[200020];//树状数组
inline int lowbit(int x){return x&(-x);}
void Change(int p,int w){//修改。由于只是从A[p]=0改到A[p]=w，所以可以直接插入w
	for(int vi=p;vi<=maxn;vi+=lowbit(vi))BIT[vi].Ins(w);
}
int Getsum(int p,int k){//查找[1..p]小于或者等于k的数字的个数
	int sum=0;
	for(int vi=p;vi>0;vi-=lowbit(vi)){
		BIT[vi].Ins(k); sum+=Size[BIT[vi].root]-Size[Btree[BIT[vi].root].son[1]]-1;
		BIT[vi].Delete(BIT[vi].root);
	}
	return sum;
}

struct inf{//花的属性
	int A,B,C;
	bool operator ==(const inf &qa)const{return ((A==qa.A)&&(B==qa.B)&&(C==qa.C));}//判断相等
	bool operator <(const inf &qa)const{//判断大小
		if(A!=qa.A)return A<qa.A;//按照3个关键字排序
		else if(B!=qa.B)return B<qa.B;
		else return C<qa.C;
	}
};
int n;
inf Num[100010];
int ans[100010],Bucket[100010];

int main(){
	scanf("%d%d",&n,&maxn);//读入
	
	for(int i=1;i<=n;i++)scanf("%d%d%d",&Num[i].A,&Num[i].B,&Num[i].C),std::push_heap(Num+1,Num+i+1);
	for(int i=n;i>=1;i--)std::pop_heap(Num+1,Num+i+1);//排序
	
	for(int i=1;i<=n;i++){
		if((!(Num[i]==Num[i+1]))||(i==n)){//如果尚且与下一个不同，那么计算本次的答案
			ans[i]=Getsum(Num[i].B,Num[i].C);
			for(int j=i-1;(Num[j]==Num[j+1])&&(j>=1);j--)ans[j]=ans[j+1];//之后更新前面可能是相同的答案
		}
		Change(Num[i].B,Num[i].C);//修改
	}
	for(int i=1;i<=n;i++)Bucket[ans[i]]++;//统计答案
	for(int i=0;i<n;i++)printf("%d\n",Bucket[i]);//输出
}