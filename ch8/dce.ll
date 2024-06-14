define i64 @foo(i64 %in) {
  %dead = add i64 %in, %in
  %res = mul i64 %in, 2
  ret i64 %res
}
