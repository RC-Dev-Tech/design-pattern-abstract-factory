# ![](https://drive.google.com/uc?id=10INx5_pkhMcYRdx_OO4rXNXxcsvPtBYq) Abstract Factory Pattern 抽象工廠模式 
> ##### 理論請自行找，網路上有很多相關的文章，這邊只關注於範例實作的部分.

---

<!--ts-->
## 目錄
* [目的](#目的)
* [使用時機](#使用時機)
* [URL結構圖](#url結構圖)
* [實作成員](#實作成員)
* [實作範例](#實作範例)
* [參考資料](#參考資料)
<!--te-->

---

## 目的
以同一個介面來建立一整族相關或相依的物件，不需要點名個物件真正所屬的具象類別.

---

## 使用時機
* 當系統必須要和最終成品的生成、組合、表達方式保持獨立時.
* 當系統組態必須能調整到與各陣營產品順利搭配時.
* 一整族相關的物件必須一塊兒使用，你又得確保不會搭配錯誤.
* 你把類別程式庫貢獻出來，卻只想要公開介面，不想公開實作細節.

---

## URL結構圖
![](https://drive.google.com/uc?id=18E5zBikOZxx60j-krhzVz0-7Y2gSbj-R)
> 圖片來源：[Refactoring.Guru - Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory)

---

## 實作成員
* AbstractFactory
  * 此介面宣告出可生成個抽象成品物件的操作.
* ConcreteFactory
  * 具體實作出可建構具象成品物件的操作.
* AbstractProduct
  * 宣告某成品物件類型之介面.
* ConcreteProduct
  - ConcreteFactory 所建構的成品物件.
  - AbstractProduct 介面的具象實作.
* Client
  * 只觸及AbstractFactory和AbstractProduct這兩個抽象類別所定的介面.

---

## 實作範例:
- [Example](https://github.com/RC-Dev-Tech/design-pattern-abstract-factory/blob/main/C%2B%2B/main.cpp) - Abstract Factory Pattern (C++).

---

## 參考資料
* [Wiki - Abstract Factory Pattern](https://en.wikipedia.org/wiki/Abstract_factory_pattern) <br>
* [Refactoring.Guru - Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory) <br>

---

<!--ts-->
#### [目錄 ↩](#目錄)
<!--te-->
---
