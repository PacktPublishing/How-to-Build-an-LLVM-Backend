define void @useOfArrayType(ptr %dst) {
  store [12 x [36 x i32]] zeroinitializer, ptr %dst, align 8
  ret void
}
