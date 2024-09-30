## AFL++, make, Instrumentation  

**make** - утилита которая выполняет компиляцию файлов. Для описания действий и опций компиляции используется файл **Makefile**.  

**Инструментация файла** (Instrumenting the target) - в контексте фаззинга это процесс компиляции кода программы с помощью компиляторов, которое поставляются вмете с фаззером, например afl-clang-fast.  

**Компиляторы AFL++**:  
  -  LTO: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md
  -  LLVM: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md
  -  GCC: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.gcc_plugin.md

**Пример компиляции**:

**Вариант 1**:  
- CC = устанавливаем компилятор для языка Си.  
- СХХ = устанавляваем компилятор для языка С++.  
- --disabled-shared = отключает использование динамических библиотек.  
```
CC=afl-clang-fast CXX=afl-clang-fast++ ./configure --disable-shared
make
```

**Вариант 2**: если система сборки настроена на make.
```
make CC=afl-clang-fast CXX=afl-clang-fast++
```
**Вариант 3**: для CMake  
- Указываем компиляторы для C и C++.
- Отключаем использование динамических библиотек (shared libraries).  
```
cmake -DCMAKE_C_COMPILER=afl-clang-fast -DCMAKE_CXX_COMPILER=afl-clang-fast++ -DBUILD_SHARED_LIBS=OFF .  
make  
```
**Вариант 4**: создание отдельной директории для сборки  
```
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=afl-clang-fast -DCMAKE_CXX_COMPILER=afl-clang-fast++ -DBUILD_SHARED_LIBS=OFF ..
make
```

**Опции инструментации**:  
 - COMPCOV: AFL_LLVM_LAF_ALL=1
 - Input-to-State: AFL_LLVM_CMPLOG=1  
 - ASAN: AFL_USE_ASAN=1
 - MSAN: AFL_USE_MSAN=1
 - USBAN: AFL_USE_UBSAN=1
 - CFISAN: AFL_USE_CFISAN=1
 - TSAN: AFL_USE_TSAN=1
 - LSAN: AFL_USE_LSAN=1. __AFL_LEAK_CHECK(); добавляется во все области целевого исходного кода, где необходимо проверить утечку! Чтобы игнорировать проверку на утечку памяти для определенных распределений __AFL_LSAN_OFF();  

Пример:  
  export AFL_LLVM_LAF_ALL=1 //Установить переменную для всех процессов в shell.  
  AFL_LLVM_LAF_ALL=1 //Установить переменную для одного процесса.  

**Дополнительные опции перед началом фаззинга**:  
1. sudo afl-system-config  
2. sudo afl-persistent-config
3. export AFL_SKIP_CPUFREQ=1
4. AFL_TMPDIR используется для записи файла .cur_input, если он существует, и в обычный каталог вывода в противном случае. Вы можете использовать его для указания на ramdisk/tmpfs. Это увеличивает скорость на небольшую величину, но также снижает нагрузку на SSD.  


