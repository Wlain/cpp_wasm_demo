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
        function getCurrentUrl()
        　　{
        　　　　var url = document.location.toString();
        　　　　return url;
        　　}
        getCurrentUrl()
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
  std::cout << "cpp value {g_double} is:" << g_double << std::endl; // 这是一个坑，会变成整数
  printf("C{g_double:%lf}\n", g_double);
}

int main() {
  cppCallJsTest();
  return 0;
}
