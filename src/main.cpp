#include <iostream>

#ifndef EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#else
#define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#endif
#else
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype
#else
#define EM_PORT_API(rettype) rettype
#endif
#endif
#endif

EM_PORT_API(void) jsCallCpp(int index) {
  std::cout << "hello world cpp" << std::endl;
}

EM_PORT_API(int) add(int a, int b) { return a + b; }

void cppCallJsTest() {
  const char *const getCurrentUrlScript = R"+++(
        function getStringFormJs()
        　　{
        　　　　return "getStringFormJs";
        　　}
        getStringFormJs()
    )+++";
  const char *const printScript = R"+++(
        console.log("hello world js");
    )+++";
  std::string url = emscripten_run_script_string(getCurrentUrlScript);
  std::cout << url.c_str() << std::endl;
  emscripten_run_script(printScript);
}

EM_PORT_API(int) jsAdd(int a, int b);
EM_PORT_API(void) jsConsoleLogInt(int param);

EM_PORT_API(int) showMeTheAnswer();

EM_PORT_API(void) func() { printf("%d\n", showMeTheAnswer()); }

EM_PORT_API(void) printTheAnswer() {
  int i = jsAdd(21, 21);
  jsConsoleLogInt(i);
}

int g_int = 42;
double g_double = 3.1415926;

EM_PORT_API(int *) getIntPtr() { return &g_int; }

EM_PORT_API(double *) getDoublePtr() { return &g_double; }

EM_PORT_API(void) printData() {
  std::cout << "cpp value {g_int} is:" << g_int << std::endl;
  std::cout << "cpp value {g_double} is:" << g_double
            << std::endl; // 这是一个坑，会变成整数
  printf("C{g_double:%lf}\n", g_double);
}

EM_PORT_API(void) printInt(int a) { printf("C{printInt() a:%d}\n", a); }

EM_PORT_API(void) printFloat(float a) { printf("C{printFloat() a:%f}\n", a); }

EM_PORT_API(void) printString(const char *str) {
  printf("C{printString() a:%s}\n", str);
}

EM_PORT_API(void) printDouble(double a) {
  printf("C{printDouble() a:%lf}\n", a);
}

EM_PORT_API(int *) fibonacci(int count) {
  if (count <= 0)
    return nullptr;
  int *re = (int *)malloc(count * 4);
  if (nullptr == re) {
    printf("Not enough memory.\n");
    return nullptr;
  }
  re[0] = 1;
  int i0 = 0, i1 = 1;
  for (int i = 1; i < count; i++) {
    re[i] = i0 + i1;
    i0 = i1;
    i1 = re[i];
  }
  return re;
}

EM_PORT_API(void) freeBuf(void *buf) { free(buf); }

EM_PORT_API(void) jsPrintFib(int *ptr, int count);

EM_PORT_API(void) fibonacci20() {
  static const int count = 20;
  int re[count];

  re[0] = 1;
  int i0 = 0, i1 = 1;
  for (int i = 1; i < count; i++) {
    re[i] = i0 + i1;
    i0 = i1;
    i1 = re[i];
  }

  jsPrintFib(re, count);
}

// C函数sum()求传入的int数组的各项之和
EM_PORT_API(int) sum(int *ptr, int count) {
  int total = 0;
  for (int i = 0; i < count; i++) {
    total += ptr[i];
  }
  return total;
}

// 将C/C++的字符串转换为JavaScript字符串
EM_PORT_API(const char *) getCppString() {
  static const char str[] = "cpp said: Hello, wolrd!";
  return str;
}

EM_PORT_API(double) addDouble(double a, int b) { return a + (double)b; }

EM_PORT_API(int) sumUint8(uint8_t *ptr, int count) {
  int total = 0, temp;
  for (int i = 0; i < count; i++) {
    memcpy(&temp, ptr + i * 4, 4);
    total += temp;
  }
  return total;
}

EM_PORT_API(const char *) getString() {
  const static char str[] = "getString called This is a test.";
  return str;
}
int main() {
  cppCallJsTest();
  // call js use micro:EM_ASM宏只能执行嵌入的JavaScript代码,
  // 无法传入参数或获取返回结果
  EM_ASM(console.log('你好，Emscripten！'));
  EM_ASM(var k = 42; console.log('The answer is:', k););
  EM_ASM(var k = 42; // define k
         console.log('The answer is:', k););
  // EM_ASM_支持输入数值类型的可变参数
  int sum = EM_ASM_({ return $0 + $1 + $2; }, 1, 2, 3);
  printf("sum(1, 2, 3): %d\n", sum);

  char buf[32];
  double pi = 3.14159;
  EM_ASM_(
      {
        console.log('addr of buf:', $0);
        console.log('sqrt(pi):', $1);
      },
      buf, sqrt(pi));
  // EM_ASM_DOUBLE用法与EM_ASM_基本一致，区别是EM_ASM_DOUBLE返回值为double
  double pi2 = EM_ASM_DOUBLE({ return $0 * $1; }, pi, 2.0);
  printf("pi2: %lf\n", pi2);

  EM_ASM_(
      {
        console.log('arguments count:', arguments.length);
        for (var i = 0; i < arguments.length; i++) {
          console.log('$', i, ':', arguments[i]);
        }
      },
      42, 13);

  //如果嵌入的JavaScript代码不需要参数，可以使用EM_ASM_INT_V/EM_ASM_DOUBLE_V宏
  int answer = EM_ASM_INT_V(return 42);
  printf("The answer is:%d\n", answer);
  double pi_js = EM_ASM_DOUBLE_V(return 3.14159);
  printf("PI:%lf\n", pi_js);
  return 0;
}
