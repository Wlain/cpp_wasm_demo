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

// capi_js.cc
EM_PORT_API(int) jsAdd(int a, int b);
EM_PORT_API(void) jsConsoleLogInt(int param);

EM_PORT_API(void) printTheAnswer() {
  int i = jsAdd(21, 21);
  jsConsoleLogInt(i);
}

int main() {
  cppCallJsTest();
  return 0;
}
