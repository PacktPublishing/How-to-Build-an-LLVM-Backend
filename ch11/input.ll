target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

define i32 @_Z3fooPxx(ptr nocapture noundef readonly %arg, i64 noundef %arg1) local_unnamed_addr {
bb:
  %i = icmp slt i64 %arg1, 0
  br i1 %i, label %bb2, label %bb4

bb2:                                              ; preds = %bb
  %i3 = tail call i64 @_Z3barx(i64 noundef %arg1)
  br label %bb4

bb4:                                              ; preds = %bb2, %bb
  %i5 = phi i64 [ %i3, %bb2 ], [ %arg1, %bb ]
  %i6 = add nsw i64 %i5, 18
  %i7 = getelementptr inbounds i64, ptr %arg, i64 %i6
  %i8 = load i64, ptr %i7, align 8
  %i9 = add nsw i64 %i8, %i5
  %i10 = trunc i64 %i9 to i32
  ret i32 %i10
}

declare i64 @_Z3barx(i64 noundef) local_unnamed_addr
