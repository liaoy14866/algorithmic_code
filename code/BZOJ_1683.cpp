#include<cstdio>
#include<algorithm>

struct inf1{
	int x[2],y[2];
	int a;//a=-1 means Query else means Change
	long long ans;//反感long long
};
struct inf2{
	int x,y,a;
	bool operator <(const inf2 &qa)const{
		return x<qa.x;
	}
};
struct inf3{
	int x,pos;
	bool Dir;//Dir is true means left else right
	bool operator <(const inf3 &qa)const{
		if(x!=qa.x)return x<qa.x;
		else return Dir;
	}
};

int n,cnt;
long long C[310000];//树状数组（似乎不必清空的说）
inf1 Ope[310000];//操作序列
inf2 Cha[310000];//记录左半部分修改的数组
inf3 Que[310000];//记录右半部分询问的数组

int lowbit(int x){return x&(-x);}
void Change(int p,int w){while(p<=n){C[p]+=w;p+=lowbit(p);}}
long long Getsum(int p){long long sum=0;while(p>0){sum+=C[p];p-=lowbit(p);}return sum;}//树状数组

void Div(int l,int r){//CDQ分治
	if(l==r)return;
	int m=(l+r)>>1,Ctop=0,Qtop=0,now=1;
	Div(l,m);//处理左半部分问题
	//计算影响。这里并没有改动原数组的位置
	for(int vi=l;vi<=m;vi++)if(Ope[vi].a!=-1){//把左半部分的修改搞出来
		Ctop++;
		Cha[Ctop].x=Ope[vi].x[0]; Cha[Ctop].y=Ope[vi].y[0]; Cha[Ctop].a=Ope[vi].a;
		std::push_heap(Cha+1,Cha+Ctop+1);
	}
	for(int vi=Ctop;vi>=1;vi--)std::pop_heap(Cha+1,Cha+vi+1);//排序
	for(int vi=m+1;vi<=r;vi++)if(Ope[vi].a==-1){//把右半部分的询问边界搞出来
		Qtop+=2;
		Que[Qtop-1].x=Ope[vi].x[0]; Que[Qtop-1].pos=vi; Que[Qtop-1].Dir=true;
		std::push_heap(Que+1,Que+Qtop);
		Que[Qtop].x=Ope[vi].x[1]; Que[Qtop].pos=vi; Que[Qtop].Dir=false;
		std::push_heap(Que+1,Que+Qtop+1);
	}
	for(int vi=Qtop;vi>=1;vi--)std::pop_heap(Que+1,Que+vi+1);//排序
	
	for(int vi=1;vi<=Qtop;vi++){//计算影响
		int y[2]; y[0]=Ope[Que[vi].pos].y[0]; y[1]=Ope[Que[vi].pos].y[1];
		if(Que[vi].Dir){
			while((Cha[now].x<Que[vi].x)&&(now<=Ctop)){Change(Cha[now].y,Cha[now].a);now++;}
			Ope[Que[vi].pos].ans-=Getsum(y[1])-Getsum(y[0]-1);
		}
		else{
			while((Cha[now].x<=Que[vi].x)&&(now<=Ctop)){Change(Cha[now].y,Cha[now].a);now++;}
			Ope[Que[vi].pos].ans+=Getsum(y[1])-Getsum(y[0]-1);
		}
	}
	Div(m+1,r);//处理右半部分问题
}
int main(){
	int ifdo;
	scanf("%d",&n);//读入
	while(1){
		scanf("%d",&ifdo); cnt++;
		if(ifdo==3)break;
		if(ifdo==1){scanf("%d%d%d",&Ope[cnt].x[0],&Ope[cnt].y[0],&Ope[cnt].a); }
		else{
			Ope[cnt].a=-1;
			scanf("%d%d%d%d",&Ope[cnt].x[0],&Ope[cnt].y[0],&Ope[cnt].x[1],&Ope[cnt].y[1]);
		}
	}
	
	Div(1,cnt);//分治
	
	for(int i=1;i<=cnt;i++)if(Ope[i].a==-1)printf("%lld\n",Ope[i].ans);//输出
	return 0;
}