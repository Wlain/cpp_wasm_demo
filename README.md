# cpp_wasm_demo

this is a demo for webAssemably

#### JavaScript函数注入的优缺点：

* 优点：使用JavaScript函数注入可以保持C代码的纯净——既C代码中不包含任何JavaScript的成分
* 缺点：该方法需要额外创建一个.js库文件，维护略为麻烦

#### Module.buffer对照表

|  对象   | TypedArray  |  对应C数据类型   |
|  ----  | ----  |  ----  |
|Module.HEAP8    |Int8Array    |int8|
|Module.HEAP16    |Int16Array    |int16|
|Module.HEAP32    |Int32Array    |int32|
|Module.HEAPU8    |Uint8Array    |uint8|
|Module.HEAPU16    |Uint16Array    |uint16|
|Module.HEAPU32    |Uint32Array    |uint32|
|Module.HEAPF32    |Float32Array    |float|
|Module.HEAPF64    |Float64Array    |double|

#### JavaScript与C/C++相互调用的时候，参数与返回值究竟是如何传递的？

* 答案是：一切皆为Number(JavaScript只有一种数值类型：Number，既64位浮点数（IEEE 754标准）).

#### Number从JavaScript传入C/C++有两种途径：

* JavaScript调用了带参数的C导出函数，Number通过参数传入
* C调用了由JavaScript实现的函数，Number通过注入函数的返回值传入

#### 数值从C/C++传出至JavaScript也有两种途径

* JavaScript调用了带返回值的C导出函数，通过返回值传出；
* C调用了由JavaScript实现的函数，通过注入函数的参数传出

#### allocateUTF8：该方法将在C/C内存中分配足够大的空间，并将字符串按UTF8格式拷入其中

#### JavaScript调用C/C++时只能使用Number作为参数，因此如果参数是字符串、数组等非Number类型，则需要拆分为以下步骤：

* 使用Module._malloc()在Module堆中分配内存，获取地址ptr；
* 将字符串/数组等数据拷入内存的ptr处；
* 将ptr作为参数，调用C/C++函数进行处理；
* 使用Module._free()释放ptr。

JavaScript 语法记录：

* 如果重新声明 JavaScript 变量，该变量的值不会丢失：
    ```javascript
    // 在以下两条语句执行后，变量 carname 的值依然是 "Volvo"：
    var carname="Volvo";
    var carname; 
    ```
* 变量的数据类型可以使用 typeof 操作符来查看：
    ```javascript 
    typeof "John"                // 返回 string
    typeof 3.14                  // 返回 number
    typeof false                 // 返回 boolean
    typeof [1,2,3,4]             // 返回 object
    typeof {name:'John', age:34} // 返回 object
    ```
* JavaScript 数组
    ```javascript 
    var cars=new Array();
    cars[0]="Saab";
    cars[1]="Volvo";
    cars[2]="BMW";
    // condensed array
    var cars2 = new Array("Saab","Volvo","BMW");
    // literal array
    var cars3 = ["Saab","Volvo","BMW"];
    ```
* JavaScript 对象
    ```javascript 
    var person = {firstname:"John", lastname:"Doe", id:5566};
    var person1 = {
    firstname : "John",
    lastname  : "Doe",
    id        :  5566
    };
    name=person.lastname;
    name=person["lastname"];
    ```
* 声明新变量时，可以使用关键词 "new" 来声明其类型
    ```javascript
    var carname=new String;
    var x=      new Number;
    var y=      new Boolean;
    var cars=   new Array;
    var person= new Object;
    ```
* 全局 JavaScript 变量
    ```javascript
    var var1 = 1; // 不可配置全局属性
    var2 = 2; // 没有使用 var 声明，可配置全局属性
    
    console.log(this.var1); // 1
    console.log(window.var1); // 1
    console.log(window.var2); // 2
    
    delete var1; // false 无法删除
    console.log(var1); //1
    
    delete var2;
    console.log(delete var2); // true
    console.log(var2); // 已经删除 报错变量未定义
    ```
* 如果变量在函数内没有声明（没有使用 var 关键字），该变量为全局变量。
    ```javascript
    // 此处可调用 carName 变量
    
    function myFunction() {
    carName = "Volvo";
    // 此处可调用 carName 变量
    }
    ```
* `===` 为恒等计算符，同时检查表达式的值与类型
    ```javascript
  typeof undefined             // undefined
  typeof null                  // object
  null === undefined           // false // 类型不相等
  null == undefined            // true
  //（1）undefined：是所有没有赋值变量的默认值，自动赋值。
  //（2）null：主动释放一个变量引用的对象，表示一个变量不再指向任何对象地址。
  // 当使用完一个比较大的对象时，需要对其进行释放内存时，设置为 null。
   ```
* JavaScript 数据类型
  * 6 种不同的数据类型：
    * string   
    * number 
    * boolean 
    * object 
    * function 
    * symbol
  * 3种对象类型：
    * Object
    * Date
    * Array
  * 2个不包含任何值的数据类型：
    * null——表示变量声明过但并未赋过值。
    * undefined——表示一个变量将来可能指向一个对象。
    
    ```javascript
    typeof "John"                 // 返回 string
    typeof 3.14                   // 返回 number
    typeof NaN                    // 返回 number
    typeof false                  // 返回 boolean
    typeof [1,2,3,4]              // 返回 object
    typeof {name:'John', age:34}  // 返回 object
    typeof new Date()             // 返回 object
    typeof function () {}         // 返回 function
    typeof myCar                  // 返回 undefined (如果 myCar 没有声明)
    typeof null                   // 返回 object
    ```
  * constructor 属性:constructor 属性返回所有 JavaScript 变量的构造函数
      ```javascript
      "John".constructor                 // 返回函数 String()  { [native code] }
      (3.14).constructor                 // 返回函数 Number()  { [native code] }
      false.constructor                  // 返回函数 Boolean() { [native code] }
      [1,2,3,4].constructor              // 返回函数 Array()   { [native code] }
      {name:'John', age:34}.constructor  // 返回函数 Object()  { [native code] }
      new Date().constructor             // 返回函数 Date()    { [native code] }
      function () {}.constructor         // 返回函数 Function(){ [native code] }
      // 可以使用 constructor 属性来查看对象是否为数组 (包含字符串 "Array"):
      function isArray(myArray) {
      return myArray.constructor.toString().indexOf("Array") > -1;
      }  
      // 使用 constructor 属性来查看对象是否为日期 (包含字符串 "Date"):
      function isDate(myDate) {
        return myDate.constructor.toString().indexOf("Date") > -1;
      }
    ```
* JavaScript 正则表达式
    ```javascript
    // search() 方法使用正则表达式
    var str = "Visit Runoob!"; 
    var n = str.search(/Runoob/i); // n -> 6
    var str = "Visit Runoob!"; 
    var n = str.search("Runoob");
    // replace() 方法使用正则表达式:
    // 将字符串中的 Microsoft 替换为 Runoob 
    var str = document.getElementById("demo").innerHTML; 
    var txt = str.replace(/microsoft/i,"Runoob");
    // replace() 方法将接收字符串作为参数：
    var str = document.getElementById("demo").innerHTML; 
    var txt = str.replace("Microsoft","Runoob");
   ```
* debugger 关键字：debugger 关键字用于停止执行 JavaScript，并调用调试函数
* JavaScript 中的所有数据都是以 64 位浮点型数据(float) 来存储
    ```javascript
    var x = 0.1;
    var y = 0.2;
    var z = x + y            // z 的结果为 0.30000000000000004
    if (z == 0.3)            // 返回 false
    ```
* JavaScript let 和 const
  * let 声明的变量只在 let 命令所在的代码块内有效。 
  * const 声明一个只读的常量，一旦声明，常量的值就不能改变。
  ```javascript
    { 
    var x = 2; 
    }
    // 这里可以使用 x 变量
    { 
    let y = 2;
    }
    // 这里不能使用 y 变量  
    // 重新定义变量
    var x = 10;
    // 这里输出 x 为 10
    {
    let x = 2;
    // 这里输出 x 为 2
    }
    // 这里输出 x 为 10
  ```
* JavaScript JSON：JSON 英文全称 JavaScript Object Notation，是一种轻量级的数据交换格式，是独立的语言
  * JSON 是用于存储和传输数据的格式。
  * JSON 通常用于服务端向网页传递数据。
* JavaScript 类继承
  ```javascript
    // 基类
    class Animal {
    // eat() 函数
    // sleep() 函数
    };
    
    
    //派生类
    class Dog extends Animal {
    // bark() 函数
    };
    ```
* JavaScript 判断当期设备是移动端浏览器还是 PC 端浏览器。
    ```javascript
    if( /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent) ) {
      document.write("移动")
      } else {
      document.write("PC")
      }
    ```
* 有用的demo：https://www.runoob.com/js/js-examples.html
