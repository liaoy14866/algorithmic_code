#include<cstdio>
#include<cstring>
char an[110000];
int n;
int P[110000],Rank[110000],Temp[110000],SA[110000],Height[110000];
int cnt[110000];

int cmp(int a,int b,int l){return Rank[a]==Rank[b]&&Rank[a+l]==Rank[b+l];}//判断两个关键字是否相等

void Doubling(){//倍增
	for(int i=1;i<=n;i++)Rank[i]=(int)an[i],SA[i]=i;//初始化
	for(int l=0,pos=0,sig=255;pos<n;sig=pos){//sig是字符级大小
		pos=0;
		for(int i=n-l+1;i<=n;i++)pos++,P[pos]=i;
		for(int i=1;i<=n;i++)if(SA[i]>l)pos++,P[pos]=SA[i]-l;//先把第一关键字为“空格”的排好
		
		memset(cnt,0,sizeof(cnt));//基数排序既有第一关键字，又有第二关键字的
		for(int i=1;i<=n;i++)cnt[Rank[i]]++;
		for(int i=1;i<=sig;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)SA[cnt[Rank[P[i]]]]=P[i],cnt[Rank[P[i]]]--;
		
		pos=0;
		for(int i=1;i<=n;i++){if(!cmp(SA[i],SA[i-1],l))pos++;Temp[SA[i]]=pos;}//求出Rank数组。由于我们判断的时候用了Rank，所以先用Temp储存起来
		for(int i=1;i<=n;i++)Rank[i]=Temp[i];
		if(l==0)l=1;else l=l<<1;//倍增
	}
	for(int i=1;i<=n;i++)Rank[SA[i]]=i;//求出Rank。由于最终的排序结果是没有相等的，所以Rank可以直接赋值
	
	for(int i=1,j=0;i<=n;i++){//求Height数组
		int k=SA[Rank[i]-1]; if(k==0){j=0;continue;} if(j!=0)j--;//k是H[i]
		while(an[i+j]==an[k+j])j++;//暴力拓展
		Height[Rank[i]]=j;
	}
}

int main(){
	for(int i=1;;i++){char c=getchar();if(c=='\n')break;else an[i]=c;n++;}//读入
	
	Doubling();//倍增
	
	for(int i=1;i<=n;i++)printf("%d ",SA[i]);//输出
	printf("\n");
	for(int i=2;i<=n;i++)printf("%d ",Height[i]);
}