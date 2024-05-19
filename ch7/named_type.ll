%my.type = type { i32, ptr }

define void @useOfMyType(ptr %dst) {
  store %my.type zeroinitializer, ptr %dst, align 8
  ret void
}
