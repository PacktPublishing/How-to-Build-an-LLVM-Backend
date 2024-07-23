; ModuleID = '<stdin>'
source_filename = "hadd_vector.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

%struct.Vec4 = type { i32, i32, i32, i32 }

; Function Attrs: noinline nounwind ssp uwtable(sync)
define i32 @hadd(ptr noundef %arg) #0 {
bb:
  %i = alloca ptr, align 8
  store ptr %arg, ptr %i, align 8
  %i1 = load ptr, ptr %i, align 8
  %i2 = getelementptr inbounds %struct.Vec4, ptr %i1, i32 0, i32 0
  %i3 = load i32, ptr %i2, align 4
  %i4 = load ptr, ptr %i, align 8
  %i5 = getelementptr inbounds %struct.Vec4, ptr %i4, i32 0, i32 1
  %i6 = load i32, ptr %i5, align 4
  %i7 = add nsw i32 %i3, %i6
  %i8 = load ptr, ptr %i, align 8
  %i9 = getelementptr inbounds %struct.Vec4, ptr %i8, i32 0, i32 2
  %i10 = load i32, ptr %i9, align 4
  %i11 = add nsw i32 %i7, %i10
  %i12 = load ptr, ptr %i, align 8
  %i13 = getelementptr inbounds %struct.Vec4, ptr %i12, i32 0, i32 3
  %i14 = load i32, ptr %i13, align 4
  %i15 = add nsw i32 %i11, %i14
  ret i32 %i15
}

attributes #0 = { noinline nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 15.0.0 (clang-1500.3.9.4)"}
