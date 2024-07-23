; *** IR Dump Before SLPVectorizerPass on hadd ***
; ModuleID = '/Users/qcolombet/clones/open/How-to-build-an-LLVM-backend/ch10/debug_capabilities/hadd_vector.ll'
source_filename = "hadd_vector.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

; Function Attrs: mustprogress nofree noinline norecurse nosync nounwind ssp willreturn memory(argmem: read) uwtable(sync)
define i32 @hadd(ptr nocapture noundef readonly %arg) local_unnamed_addr #0 {
bb:
  %i3 = load i32, ptr %arg, align 4
  %i5 = getelementptr inbounds i8, ptr %arg, i64 4
  %i6 = load i32, ptr %i5, align 4
  %i7 = add nsw i32 %i6, %i3
  %i9 = getelementptr inbounds i8, ptr %arg, i64 8
  %i10 = load i32, ptr %i9, align 4
  %i11 = add nsw i32 %i7, %i10
  %i13 = getelementptr inbounds i8, ptr %arg, i64 12
  %i14 = load i32, ptr %i13, align 4
  %i15 = add nsw i32 %i11, %i14
  ret i32 %i15
}

attributes #0 = { mustprogress nofree noinline norecurse nosync nounwind ssp willreturn memory(argmem: read) uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 4]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 15.0.0 (clang-1500.3.9.4)"}
