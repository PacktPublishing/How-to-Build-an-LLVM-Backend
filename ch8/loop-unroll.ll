define i64 @foo(ptr %arg) {
bb:
  br label %bb3

bb3:
  %idx = phi i64 [ 0, %bb ], [ %i9, %bb8 ]
  %i = icmp slt i64 %idx, 3
  br i1 %i, label %bb4, label %bb10

bb4:
  %i5 = getelementptr inbounds i64, ptr %arg, i64 %idx
  %i6 = load i64, ptr %i5
  %i7 = icmp ne i64 %i6, 0
  br i1 %i7, label %bb10, label %bb8

bb8:
  %i9 = add nsw i64 %idx, 1
  br label %bb3

bb10:
  %res = phi i64 [ %idx, %bb4 ], [ -1, %bb3 ]
  ret i64 %res
}
