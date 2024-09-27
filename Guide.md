## AFL++, make  

**make** - утилита которая выполняет компиляцию файлов. Для описания действий и опций компиляции используется файл **Makefile**.  

**Инструментация файла** (Instrumenting the target) - в контексте фаззинга это процесс компиляции кода программы с помощью компиляторов, которое поставляются вмете с фаззером, например afl-clang-fast.  

**Компиляторы AFL++**:  
  -  LTO: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md
  -  LLVM: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md
  -  GCC: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.gcc_plugin.md

**Опции инструментации**:  
 - COMPCOV: AFL_LLVM_LAF_ALL=1
 - Input-to-State: AFL_LLVM_CMPLOG=1  
 - ASAN: AFL_USE_ASAN=1
 - MSAN: AFL_USE_MSAN=1
 - USBAN: AFL_USE_UBSAN=1
 - CFISAN: AFL_USE_CFISAN=1
 - TSAN: AFL_USE_TSAN=1
 - LSAN: AFL_USE_LSAN=1. __AFL_LEAK_CHECK(); добавляется во все области целевого исходного кода, где необходимо проверить утечку! Чтобы игнорировать проверку на утечку памяти для определенных распределений __AFL_LSAN_OFF();  
