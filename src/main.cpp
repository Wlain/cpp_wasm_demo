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
int main() {
  cppCallJsTest();
  return 0;
}
