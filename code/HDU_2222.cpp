#include<cstdio>
#include<queue>
#include<cstring>

struct node{
	int son[30],tag;
};
int T;
node Trie[500050];
int Failp[500050];
std::queue<int> Arr;
int lenan,n,top,ans;
char an[1000050];

void Linit(){
	memset(Trie,0,sizeof(Trie));
	memset(Failp,0,sizeof(Failp));
	while(!Arr.empty())Arr.pop();
	top=0; ans=0;
}

void insan(){
	int p=0,row=0,next;
	do{
		next=an[row]-97;
		if(Trie[p].son[next]==0){top++;Trie[p].son[next]=top;}
		p=Trie[p].son[next]; row++;
	}while(row<lenan);
	Trie[p].tag++;
}

void Put(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",an); lenan=strlen(an);
		insan();
	}
}

void Failbuild(){
	Failp[0]=-1;
	for(int vi=0;vi<=25;vi++)if(Trie[0].son[vi]!=0){Failp[Trie[0].son[vi]]=0; Arr.push(Trie[0].son[vi]);}
	while(!Arr.empty()){
		int v=Arr.front(); Arr.pop();
		for(int vi=0;vi<=25;vi++)if(Trie[v].son[vi]!=0){
			int pi=Failp[v],now=Trie[v].son[vi];
			while((Trie[pi].son[vi]==0)&&(pi!=-1))pi=Failp[pi];
			if(pi==-1)Failp[now]=0;else Failp[now]=Trie[pi].son[vi];
			Arr.push(now);
		}
	}
}

void Matchan(){
	int pi=0;
	for(int vi=0;vi<lenan;vi++){
		int next=an[vi]-97;
		while((Trie[pi].son[next]==0)&&(pi!=-1))pi=Failp[pi];
		if(pi==-1){pi=0;continue;}else pi=Trie[pi].son[next];
		int ui=pi;
		while((Trie[ui].tag!=0)&&(ui!=0)){ans+=Trie[ui].tag; Trie[ui].tag=0; ui=Failp[ui];}
	}
}

int main(){
	scanf("%d",&T);
	while(T!=0){
		T--;
		Linit();
		Put();
		Failbuild();
		scanf("%s",an); lenan=strlen(an);
		Matchan();
		printf("%d\n",ans);
	}
}