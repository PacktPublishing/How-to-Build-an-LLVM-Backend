define i64 @foo(i64 %in0, i64 %in1) {
  %v0 = add i64 %in0, %in1
  %v1 = add i64 %v0, 2
  %v2 = sub i64 %v1, %in1
  ret i64 %v2
}
