var
 c,a:array[0..100000] of longint;//a为原数组，c为树状数组
 n,m,i,u,l,r,w,ifdo:longint;
function lowbit(x:longint):longint;//树状数组函数
procedure change(p,data:longint);//修改
function getsum(p:longint):longint;//统计前缀和
begin
 read(n);
 for i:=1 to n do read(a[i]);
 for i:=1 to n do change(i,a[i]-a[i-1]);//初始化
 read(m);
 for i:=1 to m do
 begin
  read(ifdo);
  if ifdo=1 then
  begin read(l,r,w); change(l,w); change(r+1,-w); end
   else
  begin read(u); writeln(getsum(u)); end;
 end;
end.