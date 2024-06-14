define i64 @foo(i64 %src, i64 %ub, ptr %addr) {
entry:
  br label %loop

loop:
  %iv = phi i64 [0, %entry], [%iv1, %loop]
  %offset = load i64, ptr %addr
  %iv1 = add i64 %iv, %offset
  %cond = icmp ult i64 %iv1, %ub
  br i1 %cond, label %loop, label %end

end:
  %res = add i64 %src, %iv1
  ret i64 %res
}
