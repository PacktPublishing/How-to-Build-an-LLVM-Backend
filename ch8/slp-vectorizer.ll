;target triple="aarch64-apple-ios"

define <2 x i64> @foo(i64 %in0, i64 %in1) {
  %v0 = add i64 %in0, 2
  %v1 = add i64 %in1, 5
  %partial = insertelement <2 x i64> poison, i64 %v0, i32 0 
  %res = insertelement <2 x i64> %partial, i64 %v1, i32 1 
  ret <2 x i64> %res
}
