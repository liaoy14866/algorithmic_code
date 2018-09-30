inline bool precmp(int x,int w){
	return x<w;
}
bool prefix(int w){
	if(!precmp(Btree[root].minn,w))return 0;
	int p=root;
	while(!precmp(Btree[p].data,w))p=Btree[p].son[0];
	for(;;){
		if(Btree[p].son[1]&&precmp(Btree[Btree[p].son[1]].minn,w))p=Btree[p].son[1];
		else if(Btree[p].son[0]&&(!precmp(Btree[p].data,w)))p=Btree[p].son[0];
		else break;
	}
	while(p!=root)Splay(p); return 1;
}
inline bool sufcmp(int x,int w){
	return x>w;
}
int suffix(int w){
	if(!sufcmp(Btree[root].maxn,w))return 0;
	int p=root;
	while(!sufcmp(Btree[p].data,w))p=Btree[p].son[1];
	for(;;){
		if(Btree[p].son[0]&&sufcmp(Btree[Btree[p].son[0]].maxn,w))p=Btree[p].son[0];
		else if(Btree[p].son[1]&&(!sufcmp(Btree[p].data,w)))p=Btree[p].son[1];
		else break;
	}
	while(p!=root)Splay(p); return 1;
}