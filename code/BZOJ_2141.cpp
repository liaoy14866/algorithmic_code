#include<cstdio>
#include<algorithm>

const int maxn=1e9+7;
inline void read(int &a){
	char c=getchar();
	for(a=0;(c<'0'||c>'9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
}

int Btop;
struct Splaynode{//平衡树节点
	int data,num,son[2];
};
Splaynode Btree[6000000];
int Size[6000000],Fa[6000000];
struct Segnode{//线段树节点
	int l,r,son[2],root;
	void Splay(int p){//单旋
		int f=Fa[p],gf=Fa[f],son;
		if(root==p)return;
		if(root==Fa[p])root=p;
		if(Btree[f].son[0]==p){
			son=Btree[p].son[1]; Btree[p].son[1]=f; Btree[f].son[0]=son;
		}
		else{
			son=Btree[p].son[0]; Btree[p].son[0]=f; Btree[f].son[1]=son;
		}
		Fa[f]=p; Fa[p]=gf; Fa[son]=f;
		if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
		Size[f]=Size[Btree[f].son[0]]+Size[Btree[f].son[1]]+Btree[f].num;
		Size[p]=Size[Btree[p].son[0]]+Size[Btree[p].son[1]]+Btree[p].num;
	}
	void Ins(int w){//插入，根为插入的节点
		if(!root){
			Btop++; root=Btop; Btree[Btop].data=w; Btree[Btop].num=1; Size[Btop]=1; return;
		}
		int p=root;
		for(;;){
			Size[p]++; if(Btree[p].data==w){Btree[p].num++; break;}
			if(w<Btree[p].data){
				if(!Btree[p].son[0]){
					Btop++; Btree[p].son[0]=Btop; Size[Btop]=1; Fa[Btop]=p;
					Btree[Btop].data=w; Btree[Btop].num=1; p=Btop; break;
				}else p=Btree[p].son[0];
			}
			else{
				if(!Btree[p].son[1]){
					Btop++; Btree[p].son[1]=Btop; Size[Btop]=1; Fa[Btop]=p;
					Btree[Btop].data=w; Btree[Btop].num=1; p=Btop; break;
				}else p=Btree[p].son[1];
			}
		}
		while(root!=p)Splay(p);
	}
	int Posintree(int w){//查找w的位置，根为查找的节点
		int p=root;
		while(Btree[p].data!=w)p=(Btree[p].data>w)?Btree[p].son[0]:Btree[p].son[1];
		while(p!=root)Splay(p); return p;
	}
	int Prefix(int p){//查找前驱，根为前驱
		while(p!=root)Splay(p); if(!Btree[p].son[0])return -1;
		p=Btree[root].son[0]; while(Btree[p].son[1])p=Btree[p].son[1];
		while(p!=root)Splay(p); return p;
	}
	int Suffix(int p){//查找后继，根为后继
		while(p!=root)Splay(p); if(!Btree[p].son[1])return -1;
		p=Btree[root].son[1]; while(Btree[p].son[0])p=Btree[p].son[0];
		while(p!=root)Splay(p); return p;
	}
	void Delete(int p){//删除节点
		if(Btree[p].num>1){Btree[p].num--;while(p!=root)Splay(p);return;}
		int suf=Suffix(p); if(suf==-1){root=Btree[p].son[0];Fa[root]=0;return;}
		int pre=Prefix(p); if(pre==-1){root=Btree[p].son[1];Fa[root]=0;return;}
		if(Btree[pre].son[1]!=suf)Splay(suf);
		Size[pre]--; Size[suf]--; Btree[suf].son[0]=0; Fa[p]=0;
	}
};

int n,m;
int A[20010];
int Stop,Segroot;
int ans;
Segnode Seg[80040];//线段树
int SegBuild(int l,int r){//建一棵线段树
	Stop++; int now=Stop;
	Seg[now].l=l; Seg[now].r=r; 
	for(int vi=l;vi<=r;vi++)Seg[now].Ins(A[vi]);
	if(l==r)return now;
	int m=(Seg[now].l+Seg[now].r)>>1;
	Seg[now].son[0]=SegBuild(l,m); Seg[now].son[1]=SegBuild(m+1,r);
	return now;
}
int Getsum(int p,int l,int r,int minn,int maxn){//查询在[l..r]中有多少个;[minn..maxn]的数字
	if((l<1)||(r>n)||(l>r)||(minn>maxn)||(!Seg[p].root))return 0;
	if((Seg[p].l==l)&&(Seg[p].r==r)){
		Seg[p].Ins(maxn); int pmax=Seg[p].root; Seg[p].Ins(minn); int pmin=Seg[p].root;
		if(Btree[pmin].son[1]!=pmax)Seg[p].Splay(pmax);
		int sum=Size[pmin]-Size[Btree[pmin].son[0]]-Size[Btree[pmax].son[1]]-2;
		Seg[p].Delete(pmin); Seg[p].Delete(pmax);
		return sum;
	}
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(r<=m)return Getsum(Seg[p].son[0],l,r,minn,maxn);
	else
	if(m+1<=l)return Getsum(Seg[p].son[1],l,r,minn,maxn);
	else
	return Getsum(Seg[p].son[0],l,m,minn,maxn)+Getsum(Seg[p].son[1],m+1,r,minn,maxn);
}
void Remove(int p,int k){//在线段树p节点删去A[k]这个数字
	int q=Seg[p].Posintree(A[k]); Seg[p].Delete(q);
	if(Seg[p].l==Seg[p].r)return;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Remove(Seg[p].son[0],k);else Remove(Seg[p].son[1],k);
}
void Add(int p,int k){//在线段树p节点加入A[k]这个数字
	Seg[p].Ins(A[k]);
	if(Seg[p].l==Seg[p].r)return;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Add(Seg[p].son[0],k);else Add(Seg[p].son[1],k);
}

int Q[20010],Temp[20010];
void merge(int l,int m,int r){//先归并排序计算出所有的逆序对
	int tl=l,tr=m+1,tt=l;
	while(tt<=r)
	if((tr>r)||((tl<=m)&&(Q[tl]<=Q[tr]))){
		Temp[tt]=Q[tl]; tl++; tt++;
	}
	else{
		ans+=m-tl+1;
		Temp[tt]=Q[tr];tr++; tt++;
	}
	for(tt=l;tt<=r;tt++)Q[tt]=Temp[tt];
}
void sort(int l,int r){
	int m=(l+r)>>1;
	if(l<m)sort(l,m); if(m+1<r)sort(m+1,r);
	merge(l,m,r);
}


int main(){
	read(n);//读入
	for(int i=1;i<=n;i++)read(A[i]),Q[i]=A[i];
	sort(1,n);//计算出所有的逆序对
	printf("%d\n",ans);//输出一遍答案
	Segroot=SegBuild(1,n);//建一棵树套树
	read(m);
	for(int i=1;i<=m;i++){
		int u,v; read(u); read(v);
		ans-=Getsum(Segroot,1,u-1,A[u]+1,maxn)+Getsum(Segroot,u+1,n,1,A[u]-1); Remove(Segroot,u);
		ans-=Getsum(Segroot,1,v-1,A[v]+1,maxn)+Getsum(Segroot,v+1,n,1,A[v]-1); Remove(Segroot,v);//扣除A[u]与A[v]的影响
		std::swap(A[u],A[v]);//交换A[u]与A[v]
		Add(Segroot,u); ans+=Getsum(Segroot,1,u-1,A[u]+1,maxn)+Getsum(Segroot,u+1,n,1,A[u]-1);//加上A[u]与A[v]的影响
		Add(Segroot,v); ans+=Getsum(Segroot,1,v-1,A[v]+1,maxn)+Getsum(Segroot,v+1,n,1,A[v]-1);
		printf("%d\n",ans);//输出答案
	}
}