define i1 @foo(i64 %b) {
  %a = and i64 %b, u0xfffffffffffffffc
  %mod = urem i64 %a, 2
  %cond = icmp eq i64 %mod, 0
  ret i1 %cond
}
