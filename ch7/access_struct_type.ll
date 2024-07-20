%my.type = type {i32, {ptr, half}, {i32, i1, i1}}

define half @useOfMyType(ptr %dst) {
  %addr_half_field = getelementptr inbounds %my.type, ptr %dst, i64 0, i32 1, i32 1
  %res = load half, ptr %addr_half_field, align 8
  ret half %res
}
