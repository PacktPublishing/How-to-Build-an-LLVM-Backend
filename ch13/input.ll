define i64 @def_in_loop_use_outside(i64 %src, i64 %upper_bound) {
entry:
  br label %loop

loop:
  %iv = phi i64 [0, %entry], [%iv_plus_1, %loop]
  %iv_plus_1 = add i64 %iv, 1
  %cond = icmp ult i64 %iv_plus_1, %upper_bound
  br i1 %cond, label %loop, label %end

end:
  %tmp = add i64 %iv_plus_1, %src
  %res = add i64 %tmp, %iv_plus_1
  ret i64 %res
}
