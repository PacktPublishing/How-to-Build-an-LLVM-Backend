multiclass Bundle<string base> {
  def A {
    string name = !strconcat(base, "-", "A");
    int price = 12;
    int weight = 1;
  }
  def B {
    string name = !strconcat(base, "-", "B");
    string tag = "special";
  }
}

class ShippingPrice<int arg> {
  int shippingPrice = arg;
}

defm valuedBundle : Bundle<"valued">, ShippingPrice<5>;
