define i32 @foo(ptr %src) {
  %res = load i32, ptr %src
  ret i32 %res
}
