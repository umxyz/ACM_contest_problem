program berry_sol_chain_all;
{$APPTYPE CONSOLE}
uses SysUtils;

const
  maxn = 10000;

var
  deg: array [1..maxn] of integer;
  li: array [1..maxn, 1..2] of integer;
  i, j, p, n, m, k, t, l, r: integer;
  v, q: array [1..maxn] of integer;
  FileName: string;

procedure error(const msg: string);
begin
  writeln(msg);
  close(input);
  halt(1);
end;

function get_k(const top: integer): integer;
var
  t, i: integer;
begin
  result := 0;
  t := 0;
  for i:=1 to n do
  begin
    inc(t, v[q[i]]);
    if t >= top then
    begin
      t := 0;
      inc(result);
    end;
  end;
end;

procedure get_k_and_out(const top: integer);
var
  t, i, j: integer;
begin
  t := 0;
  j := 1;
  for i:=1 to n do
  begin
    inc(t, v[q[i]]);
    if t >= top then
    begin
      t := 0;
      write(i - j + 1);
      while j <= i do
      begin
        write(' ', q[j]);
        inc(j);
      end;
      writeln;
    end;
  end;
  if j <= n then
  begin
    writeln('additional:');
    write(n - j + 1);
    while j <= n do
    begin
      write(' ', q[j]);
      inc(j);
    end;
  end;
end;

begin
  write('File Name: '); readln(FileName);
  assign(input, FileName);
  reset(input);
  fillchar(deg, sizeof(deg), 0);
  read(n, m, k);
  if m <> n - 1 then error('no chain!');
  for i:=1 to n do read(j, v[j]);
  for p:=1 to m do
  begin
    read(i, j);
    inc(deg[i]); inc(deg[j]);
    if deg[i] > 2 then error('no chain! edge');
    if deg[j] > 2 then error('no chain! edge');
    li[i, deg[i]] := j;
    li[j, deg[j]] := i;
  end;
  for i:=1 to n do
   if deg[i] = 1 then break;
  j := i;
  i := li[i, 1];
  p := 1;
  q[1] := j;
  while deg[i] <> 1 do
  begin
    inc(p);
    q[p] := i;
    if li[i, 1] = j then
    begin
      j := i;
      i := li[i, 2];
    end else
    begin
      j := i;
      i := li[i, 1];
    end;
  end;
  inc(p);
  q[p] := i;

  assign(output, 'berry.std');
  rewrite(output);
{  p := k;
  for k:=1 to p do
  begin
    r := 0;
    for i := 1 to n do inc(r, v[q[i]]);
    l := 0;
    while l <= r do
    begin
      t := (l + r) shr 1;
      if get_k(t) < k then r := t - 1 else l := t + 1;
    end;
    writeln(k, ' ', r);
  end;}
  get_k_and_out(54974); // 17 parts
  close(output);

  close(input);
end.
