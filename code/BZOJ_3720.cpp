#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,Num,Threshold;
struct graph{//原树的邻接链表
	int top;
	struct rec{
		int x,ne;
	}E[121000];
	int Fi[61000],Fa[61000];
	inline void ins(int f,int s){
		top++; E[top].x=s; E[top].ne=Fi[f]; Fi[f]=top;
	}
}G;
struct Block_Tree{//块状树的邻接链表
	int top;
	struct rec{
		int x,ne;
	}E[61000];
	int Fi[61000];
	inline void ins(int f,int s){
		top++; E[top].x=s; E[top].ne=Fi[f]; Fi[f]=top;
	}
}BT;
int val[61000];
struct Block{//块的信息
	int T[400];
	int top;
	int vi,tl,tr,mid;
	void ins(int w){//插入
		top++; T[top]=w;
		for(vi=top;vi>1&&T[vi]<T[vi-1];vi--)std::swap(T[vi],T[vi-1]);
	}
	void add(int w){//往后面加一个元素
		top++; T[top]=w;
	}
	/*在初始化的时候，我们只需要最后排序一趟，而不用一个一个O(sqrt(n))加入*/
	void rest(){
		std::sort(T+1,T+top+1);
	}
	void change(int fr,int to){//修改
		for(vi=1;vi<=top;vi++)if(T[vi]==fr){
			T[vi]=to;
			for(;vi>1&&T[vi]<T[vi-1];vi--)std::swap(T[vi],T[vi-1]);
			for(;vi<top&&T[vi]>T[vi+1];vi++)std::swap(T[vi],T[vi+1]);
			return;
		}
	}
	int bigger(int w){//查询
		if(T[top]<=w)return 0; tl=1; tr=top;
		while(tl!=tr){
			mid=(tl+tr)>>1;
			if(T[mid]>w)tr=mid;else tl=mid+1;
		}
		return top-tr+1;
	}
}B[61000];//这里数组要达到O(n)，切记切记
int Belong[61000];
void Block_DFS(int f,int x){//建一棵块状树
	G.Fa[x]=f;
	if(B[Belong[f]].top<Threshold){
		Belong[x]=Belong[f]; B[Belong[x]].add(val[x]);
	}else{
		Num++; Belong[x]=Num; B[Num].add(val[x]); BT.ins(Belong[f],Belong[x]);
	}
	for(int v=G.Fi[x];v;v=G.E[v].ne)if(G.E[v].x!=f)Block_DFS(x,G.E[v].x);

}
int Getblock(int p,int w){//查询整块的信息
	int sum=B[p].bigger(w);
	for(int v=BT.Fi[p];v;v=BT.E[v].ne)sum+=Getblock(BT.E[v].x,w);
	return sum;
}
int Getans(int f,int x,int w){//查询答案
	int sum=val[x]>w;
	for(int v=G.Fi[x];v;v=G.E[v].ne){
		if(G.E[v].x==f)continue;
		if(Belong[G.E[v].x]==Belong[x])sum+=Getans(x,G.E[v].x,w);//如果是相同的块的话，递归节点
		else sum+=Getblock(Belong[G.E[v].x],w);//否则递归块
	}
	
	return sum;
}
void Change(int p,int w){//修改
	B[Belong[p]].change(val[p],w); val[p]=w;
}
int lastans;
int main(){
	int i,u,v,w,opt;
	read(n);
	for(i=1;i<=n-1;i++){
		read(u); read(v); G.ins(u,v); G.ins(v,u);
	}
	for(i=1;i<=n;i++)read(val[i]);
	read(m);
	Threshold=ceil(sqrt(n+m)); Num=1; Belong[1]=1; B[1].ins(val[1]);
	for(i=G.Fi[1];i;i=G.E[i].ne)Block_DFS(1,G.E[i].x);//建一棵块状树
	for(i=1;i<=Num;i++)B[i].rest();//每个块排序
	for(i=1;i<=m;i++){
		read(opt); read(u); read(w); u^=lastans; w^=lastans;
		switch(opt){
			case 0:{//查询
				lastans=Getans(G.Fa[u],u,w); printf("%d\n",lastans); break;
			}
			case 1:{//修改
				Change(u,w); break;
			}
			case 2:{//插入节点
				n++; val[n]=w; G.ins(u,n); G.Fa[n]=u;
				if(B[Belong[u]].top<Threshold){
					Belong[n]=Belong[u]; B[Belong[u]].ins(val[n]);
				}
				else{
					Num++; Belong[n]=Num; B[Belong[n]].ins(val[n]); BT.ins(Belong[u],Belong[n]);
				}
				break;
			}
		}
	}
}