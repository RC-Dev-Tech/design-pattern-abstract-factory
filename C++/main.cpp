#include <iostream>
using namespace std;

/**
 * 定義A系列產品中的每個衍生產品共用的基本接口.
 */
class AbstractProductA {
 public:
  virtual ~AbstractProductA(){};
  virtual std::string UsefulFunctionA() const = 0;
};

/**
 * 定義A系列產品的所有衍生產品都必須實現此接口。
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
 * 定義B系列產品中的每個衍生產品共用的基本接口.
 * 同時也可以規劃成是A系列產品的基本介面實作，
 * 這樣的作法可以讓所有產品都可以進行適當相互溝通.
 */
class AbstractProductB {
 public:
  virtual ~AbstractProductB(){};
  virtual std::string UsefulFunctionB() const = 0;
  /**
   * 抽象工廠可以確保它創建的所有產品都來自相同的系列，因此是兼容可以互相協作.
   */
  virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

/**
 * 定義B系列產品的所有衍生產品都必須實做基本接口及其介面操作。
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B1.";
  }

  /**
   * B系列產品B1只能與A系列產品一起正常工作. (這邊舉例A1)
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
   * B系列產品B1只能與A系列產品一起正常工作. (這邊舉例A2)
   */
  std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B2 collaborating with ( " + result + " )";
  }
};

/**
 * 抽象工廠的基底類別，負責聲明了一組返回不同抽象產品的方法。 
 * 這些產品稱為系列，藉由這些生成的抽象方法，來組裝產品，並通過抽象的介面來相互協作。 
 */
class AbstractFactory {
 public:
  virtual AbstractProductA *CreateProductA() const = 0;
  virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * 具體的工廠在藉由各個生產方法去實體化各自的具體產品，並且組裝最後產品. (工廠保證最終產品是兼容的)
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
 * 每個具體工廠都有相對應的最終產品(變型產品).
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