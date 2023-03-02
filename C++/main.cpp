#include <iostream>
using namespace std;

/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 * 產品系列中的每個不同產品都應該有一個基本接口。 
 * 產品的所有變體都必須實現此接口。
 */
class AbstractProductA {
 public:
  virtual ~AbstractProductA(){};
  virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 * 具體產品由相應的具體工廠創建。
 */
class ConcreteProductA1 : public AbstractProductA {
 public:
  std::string UsefulFunctionA() const override {
    return "The result of the product A1.";
  }
};

class ConcreteProductA2 : public AbstractProductA {
  std::string UsefulFunctionA() const override {
    return "The result of the product A2.";
  }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 * 
 * 這是另一個產品的基本界面。 
 * 所有產品都可以相互交互，但只有具有相同具體變體的產品之間才能進行適當的交互。
 */
class AbstractProductB {
  /**
   * Product B is able to do its own thing...
   * 產品 B 能夠做自己的事情......
   */
 public:
  virtual ~AbstractProductB(){};
  virtual std::string UsefulFunctionB() const = 0;
  /**
   * ...but it also can collaborate with the ProductA.
   * 但它也可以與 產品A 協作。
   *
   * The Abstract Factory makes sure that all products it creates are of the
   * same variant and thus, compatible.
   * 抽象工廠確保它創建的所有產品都具有相同的變體，因此是兼容的。
   */
  virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 * 具體產品由相應的具體工廠創建。
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B1.";
  }
  /**
   * The variant, Product B1, is only able to work correctly with the variant,
   * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
   * argument.
   * 
   * 變體產品 B1 只能與變體產品 A1 一起正常工作。 
   * 然而，它接受 AbstractProductA 的任何實例作為參數。
   */
  std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B1 collaborating with ( " + result + " )";
  }
};

class ConcreteProductB2 : public AbstractProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B2.";
  }
  /**
   * The variant, Product B2, is only able to work correctly with the variant,
   * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
   * argument.
   * 
   * 變體產品 B2 只能與變體產品 A2 一起正常工作。 然而，它接受 AbstractProductA 的任何實例作為參數。
   */
  std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B2 collaborating with ( " + result + " )";
  }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 * 
 * 抽象工廠接口聲明了一組返回不同抽象產品的方法。 
 * 這些產品稱為系列，並通過高級主題或概念相關聯。 
 * 一個家族的產品通常能夠相互協作。 
 * 一個產品系列可能有多個變體，但一個變體的產品與另一個變體的產品不兼容。
 */
class AbstractFactory {
 public:
  virtual AbstractProductA *CreateProductA() const = 0;
  virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 * 
 * 具體工廠生產屬於單一變體的一系列產品。 工廠保證最終產品是兼容的。 
 * 請注意，具體工廠方法的簽名返回一個抽象產品，而在方法內部實例化了一個具體產品。
 */
class ConcreteFactory1 : public AbstractFactory {
 public:
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA1();
  }
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB1();
  }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 * 每個具體工廠都有相應的產品變型。
 */
class ConcreteFactory2 : public AbstractFactory {
 public:
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA2();
  }
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB2();
  }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 * 
 * 客戶端代碼僅通過抽像類型與工廠和產品一起工作：AbstractFactory 和 AbstractProduct。 
 * 這使您可以將任何工廠或產品子類傳遞給客戶端代碼而不會破壞它。
 */

void ClientCode(const AbstractFactory &factory) {
  const AbstractProductA *product_a = factory.CreateProductA();
  const AbstractProductB *product_b = factory.CreateProductB();
  std::cout << product_b->UsefulFunctionB() << "\n";
  std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
  delete product_a;
  delete product_b;
}

int main() {
  std::cout << "Client: Testing client code with the first factory type:\n";
  ConcreteFactory1 *f1 = new ConcreteFactory1();
  ClientCode(*f1);
  delete f1;
  std::cout << std::endl;
  std::cout << "Client: Testing the same client code with the second factory type:\n";
  ConcreteFactory2 *f2 = new ConcreteFactory2();
  ClientCode(*f2);
  delete f2;
  return 0;
}