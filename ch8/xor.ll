define i64 @xor(i64 %x) {
  %res = xor i64 %x, %x
  ret i64 %res
}
