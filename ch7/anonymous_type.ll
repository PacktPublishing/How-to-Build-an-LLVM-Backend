define void @useOfUnknownType(ptr %dst) {
  store {i32, ptr} zeroinitializer, ptr %dst, align 8
  ret void
}
