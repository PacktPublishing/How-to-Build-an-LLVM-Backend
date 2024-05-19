define i32 @foo(i32, i32, i32 %arg) noinline noreturn {
entry:
  %myid = add i32 %0, %1
  %31 = mul i32 %myid, 2
  %45 = shl i32 %31, 5
  %"00~random~00" = udiv i32 %45, %arg
  br label %46

  br label %47

47:
  ret i32 %"00~random~00"
}

!0 = !{!"zero"}
!2 = !{!"two"}
!1 = !{!"one"}
; A named metadata.
!name = !{!0, !1, !2}
