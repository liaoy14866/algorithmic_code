procedure push_down(p:int64);//下传tag
 begin
  if tree[p].tag=0 then exit;
  inc(tree[p*2].sum,tree[p].tag*(tree[p*2].r-tree[p*2].l+1)); 
  inc(tree[p*2+1].sum,tree[p].tag*(tree[p*2+1].r-tree[p*2+1].l+1));
  inc(tree[p*2].tag,tree[p].tag); inc(tree[p*2+1].tag,tree[p].tag); tree[p].tag:=0;
 end;
procedure build(p,l,r:int64);//建树
 var m:int64;//当时的我居然把m设置为了int64……
 begin
  tree[p].l:=l; tree[p].r:=r;
  if l<>r then begin m:=(l+r) shr 1; build(p shl 1,l,m); build(p shl 1+1,m+1,r); end;
 end;
procedure change(p,l,r,data:int64);//修改
 var m:int64;
 begin
  if (tree[p].l=l) and (tree[p].r=r) then//若重合，则修改+弹出
  begin inc(tree[p].sum,(r-l+1)*data); inc(tree[p].tag,data); exit; end;
  push_down(p);//下传tag
  m:=(tree[p].l+tree[p].r) shr 1;
  if r<=m then change(p*2,l,r,data)
   else if m+1<=l then change(p*2+1,l,r,data)
   else begin change(p*2,l,m,data); change(p*2+1,m+1,r,data); end;
  tree[p].sum:=tree[p*2].sum+tree[p*2+1].sum;//更新
 end;
function getsum(p,l,r:int64):int64;//求和
 var m:int64;
 begin
  if (tree[p].l=l) and (tree[p].r=r) then exit(tree[p].sum);//若重合则弹出
  push_down(p);//下传tag
  m:=(tree[p].l+tree[p].r) shr 1;
  if r<=m then exit(getsum(p*2,l,r))
   else if m+1<=l then exit(getsum(p*2+1,l,r))
   else exit(getsum(p*2,l,m)+getsum(p*2+1,m+1,r));
 end;