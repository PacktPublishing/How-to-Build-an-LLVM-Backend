define i64 @foo(i64 %src, i64 %ub) {
entry:
  br label %loop

loop:
  br i1 false, label %loop, label %end

end:
  %umax = call i64 @llvm.umax.i64(i64 %ub, i64 1)
  %tmp = add i64 %umax, %src
  %res = add i64 %tmp, %umax
  ret i64 %res
}

declare i64 @llvm.umax.i64(i64, i64)
