define i64 @foo() {
  %local = alloca i64
  store i64 2, ptr %local
  %res = call i64 @bar(ptr %local)
  ret i64 %res
}

define internal i64 @bar(ptr %local) {
  %val = load i64, ptr %local
  %res = add i64 %val, 2
  ret i64 %res
}

