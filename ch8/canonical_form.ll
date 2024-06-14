define i64 @canonical_form(i64 %b, i64 %c) {
  %a = sub i64 %b, %c
  ret i64 %a
}

define i64 @non_canonical_form(i64 %b, i64 %c) {
  %neg_c = sub i64 0, %c
  %a = add i64 %b, %neg_c
  ret i64 %a
}
