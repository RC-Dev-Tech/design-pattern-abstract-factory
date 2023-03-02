
#include <iostream>
using namespace std;

/**
 * 產品基底類別，負責宣告所有子類別必須要進行的預設操作.
 */

class Product {
 public:
  virtual ~Product() {}
  virtual std::string Operation() const = 0;
};

/**
 * 子類別繼承產品的基底類別後，則負責將預設操作的方法進行實作.
 */

class ConcreteProduct1 : public Product {
 public:
  std::string Operation() const override {
    return "{ Result of the ConcreteProduct1 }";
  }
};

class ConcreteProduct2 : public Product {
 public:
  std::string Operation() const override {
    return "{ Result of the ConcreteProduct2 }";
  }
};

/**
 * 創建者類別則聲明了應該返回產品類別對象的工廠方法.
 * 創建者的子類別則通常提供該方法的實現。
 */

class Creator {
 public:
  virtual ~Creator(){};
  virtual Product* FactoryMethod() const = 0;

 /**
  * 請注意，創建者的主要職責並不是只有創建產品。 
  * 通常會包含一些依賴於由工廠方法返回的產品對象的核心實作邏輯。 
  * 子類可以通過覆蓋工廠方法並從中返回不同類型的產品來間接更改該其實作邏輯。
  */
  std::string SomeOperation() const {
    // 調用工廠方法創建產品對象。
    Product* product = this->FactoryMethod();

    // 現在，使用該產品及其方法實作。
    std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
    delete product;
    return result;
  }
};

/**
 * 創建者的子類別，藉由覆蓋工廠方法以更改結果產品的類型。
 */
class ConcreteCreator1 : public Creator {
 public:
  Product* FactoryMethod() const override {
    return new ConcreteProduct1();
  }
};

class ConcreteCreator2 : public Creator {
 public:
  Product* FactoryMethod() const override {
    return new ConcreteProduct2();
  }
};

/**
 * 客戶端代碼與具體創建者的實例一起工作，儘管是通過其基本接口。 
 * 只要客戶端通過基接口繼續與創建者合作，您就可以將其傳遞給任何創建者的子類別。
 */
void ClientCode(const Creator& creator) {
  // ...
  std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.SomeOperation() << std::endl;
  // ...
}

/**
 * APP應用程序則根據配置或環境選擇來創建者的類型進行實作。
 */

int main() {
  std::cout << "App: Launched with the ConcreteCreator1.\n";
  Creator* creator = new ConcreteCreator1();
  ClientCode(*creator);
  std::cout << std::endl;
  std::cout << "App: Launched with the ConcreteCreator2.\n";
  Creator* creator2 = new ConcreteCreator2();
  ClientCode(*creator2);

  delete creator;
  delete creator2;
  return 0;
}