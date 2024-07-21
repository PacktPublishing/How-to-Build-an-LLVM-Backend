define i32 @foo(i32 noundef %arg) {
bb:
  %i = ashr i32 6, 3
  %i1 = icmp ne i32 %arg, 0
  br i1 %i1, label %bb2, label %bb4

bb2:
  %i3 = udiv i32 3, %i
  br label %bb6

bb4:
  %i5 = or i32 %i, 3855
  br label %bb6

bb6:
  %.0 = phi i32 [ %i3, %bb2 ], [ %i5, %bb4 ]
  %i7 = add i32 %.0, 1
  ret i32 %i7
}

define i32 @bar(i32 noundef %arg) {
bb:
  %i = ashr i32 6, 3
  %i1 = icmp ne i32 %arg, 0
  br i1 %i1, label %bb2, label %bb4

bb2:
  %i3 = sdiv i32 3, %i
  br label %bb6

bb4:
  %i5 = or i32 %i, 3855
  br label %bb6

bb6:
  %.0 = phi i32 [ %i3, %bb2 ], [ %i5, %bb4 ]
  %i7 = add i32 %.0, 1
  ret i32 %i7
}
