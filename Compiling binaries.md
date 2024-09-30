## AFL++, make, Instrumentation  

**make** - утилита которая выполняет компиляцию файлов. Для описания действий и опций компиляции используется файл **Makefile**.  

**Инструментация файла** (Instrumenting the target) - в контексте фаззинга это процесс компиляции кода программы с помощью компиляторов, которое поставляются вмете с фаззером, например afl-clang-fast.  

**Компиляторы AFL++**:  
  -  LTO: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md
  -  LLVM: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md
  -  GCC: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.gcc_plugin.md
  
**Если в системе установлен clang/clang++ 11+**:
-  Используем LTO mode (afl-clang-lto/afl-clang-lto++)
```R=llvm-ar RANLIB=llvm-ranlib AS=llvm-as```  

**Если в системе установлен clang/clang++ 3.8+**:  
-  Используем LLVM mode (afl-clang-fast/afl-clang-fast++)
```LLVM_CONFIG=llvm-config-17```  

**Если в системе есть gcc5+**:  
-  Используем GCC_PLUGIN mode (afl-gcc-fast/afl-g++-fast)

**Если нет GCC с поддержкой плагинов**:  
-  Используем GCC mode (afl-gcc/afl-g++) (or afl-clang/afl-clang++ for clang)


**Варианты сборки и компиляции**:  
-  Используется связка configure + make:
    ```
    CC=afl-clang-fast CXX=afl-clang-fast++ ./configure --disable-shared
    make
    ```
-  Испольуется make:
    ```
    make CC=afl-clang-fast CXX=afl-clang-fast++ -j$(nproc)
    ```  

-  Используется cmake:
    ```
    cmake -DCMAKE_C_COMPILER=afl-clang-fast -DCMAKE_CXX_COMPILER=afl-clang-fast++ -DBUILD_SHARED_LIBS=OFF ..
    make -j$(nproc)
    ```

## ОПЦИИ ИНСТРУМЕНТАЦИИ:    
 - Активировать санитайзер COMPCOV: AFL_LLVM_LAF_ALL=1
 - Активировать санитайзер Input-to-State: AFL_LLVM_CMPLOG=1  
 - Активировать санитайзер ASAN: AFL_USE_ASAN=1
 - Активировать санитайзер MSAN: AFL_USE_MSAN=1
 - Активировать санитайзер USBAN: AFL_USE_UBSAN=1
 - Активировать санитайзер CFISAN: AFL_USE_CFISAN=1
 - Активировать санитайзер TSAN: AFL_USE_TSAN=1
 - Активировать санитайзер LSAN: AFL_USE_LSAN=1. __AFL_LEAK_CHECK(); добавляется во все области целевого исходного кода, где необходимо проверить утечку! Чтобы игнорировать проверку на утечку памяти для определенных распределений __AFL_LSAN_OFF();
 - AFL_HARDEN=1  

## ПРЕДВАРИТЕЛЬНАЯ КОНФИГУРАЦИЯ СИСТЕМЫ:  

**Дополнительные опции перед началом фаззинга**:  
1. sudo afl-system-config  
2. sudo afl-persistent-config
3. export AFL_SKIP_CPUFREQ=1
4. AFL_TMPDIR используется для записи файла .cur_input, если он существует, и в обычный каталог вывода в противном случае. Вы можете использовать его для указания на ramdisk/tmpfs. Это увеличивает скорость на небольшую величину, но также снижает нагрузку на SSD.  


