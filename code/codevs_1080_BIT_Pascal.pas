function lowbit(x:longint):longint;//��״���麯��
 begin exit(x and (-x)); end;
procedure change(p,data:longint);//�����޸�
 begin while p<=n do begin inc(c[p],data); inc(p,lowbit(p)); end; end;
function getsum(p:longint):longint;//ͳ��1��i�ĺ�
 begin getsum:=0; while p<>0 do begin inc(getsum,c[p]); dec(p,lowbit(p)); end; end;