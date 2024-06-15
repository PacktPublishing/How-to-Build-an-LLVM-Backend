target triple = "arm64-apple-macosx14.0.0"


define void @foo(ptr noalias noundef %arg, ptr noalias noundef %arg1, ptr noalias noundef %arg2) {
bb:
  br label %bb3

bb3:
  %idx = phi i64 [ 0, %bb ], [ %i14, %bb4 ]
  %i = icmp ne i64 %idx, 24
  br i1 %i, label %bb4, label %bb15

bb4:
  %i5 = getelementptr inbounds i16, ptr %arg1, i64 %idx
  %i6 = load i16, ptr %i5
  %i7 = sext i16 %i6 to i32
  %i8 = getelementptr inbounds i16, ptr %arg2, i64 %idx
  %i9 = load i16, ptr %i8
  %i10 = sext i16 %i9 to i32
  %i11 = add nsw i32 %i7, %i10
  %i12 = trunc i32 %i11 to i16
  %i13 = getelementptr inbounds i16, ptr %arg, i64 %idx
  store i16 %i12, ptr %i13
  %i14 = add nsw i64 %idx, 1
  br label %bb3

bb15:
  ret void
}
