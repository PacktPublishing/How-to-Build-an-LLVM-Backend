class Person<int age, string name = "anonymous"> {
  int _age = age;
  string _name = name;
}

def A : Person<23, "A">;
def B : Person<64, "B">;
def /*Anonym*/: Person<43>;
