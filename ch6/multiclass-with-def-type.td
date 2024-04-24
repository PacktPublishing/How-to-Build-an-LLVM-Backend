class Gift {
  string label = "Just a gift";
}

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
  def C: Gift {
    string color = "red";
  }
}

class ShippingPrice<int arg> {
  int shippingPrice = arg;
}

defm valuedBundle : Bundle<"valued">, ShippingPrice<5>;

def AnotherRecord {
  list<Gift> gifts = [valuedBundleC];
}
