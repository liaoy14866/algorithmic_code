var
 c,a:array[0..100000] of longint;//aΪԭ���飬cΪ��״����
 n,m,i,u,l,r,w,ifdo:longint;
function lowbit(x:longint):longint;//��״���麯��
procedure change(p,data:longint);//�޸�
function getsum(p:longint):longint;//ͳ��ǰ׺��
begin
 read(n);
 for i:=1 to n do read(a[i]);
 for i:=1 to n do change(i,a[i]-a[i-1]);//��ʼ��
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