# cpp_wasm_demo

this is a demo for webAssemably

#### JavaScript函数注入的优缺点：

* 优点：使用JavaScript函数注入可以保持C代码的纯净——既C代码中不包含任何JavaScript的成分
* 缺点：该方法需要额外创建一个.js库文件，维护略为麻烦



####Module.buffer对照表

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


		