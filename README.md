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
