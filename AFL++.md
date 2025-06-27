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
    
**Выбираем компилятор**:  
![](https://appsec.guide/docs/fuzzing/c-cpp/aflpp/aflpp-decision.drawio.svg)  
Источник картинки: https://appsec.guide/docs/fuzzing/c-cpp/aflpp/

**ДОПОЛНИТЕЛЬНЫЕ ОПЦИИ ДЛЯ afl-clang-fast / afl-clang-fast++ / afl-clang-lto / afl-clang-lto++**:  
```AFL_LLVM_ALLOWLIST/AFL_LLVM_DENYLIST``` - переменные, которые указывают на файл в которых содержаться имена файлов или функций, которые должны быть инструментированы или не должны быть инструментированы.  

**CTX**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md#6-afl-context-sensitive-branch-coverage  
**LTO**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md  
**LAF-INTEL**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.laf-intel.md  

- https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/env_variables.md

## СЛОВАРИ:  
- С помощью afl-clang-fast вы можете установить AFL_LLVM_DICT2FILE=/full/path/to/new/file.dic для автоматической генерации словаря во время компиляции цели. Добавление AFL_LLVM_DICT2FILE_NO_MAIN=1, чтобы не разбирать main (обычно это разбор параметров командной строки), также часто является хорошей идеей.  
- Указать afl-fuzz загрузить словарь: использовать флаг ```-x dictionaries/FORMAT.dict```.  


## ПРЕДВАРИТЕЛЬНАЯ КОНФИГУРАЦИЯ СИСТЕМЫ:  

**Дополнительные опции перед началом фаззинга**:  
1. ```sudo afl-system-config```  
2. ```sudo afl-persistent-config```
3. ```export AFL_SKIP_CPUFREQ=1```
4. AFL_TMPDIR используется для записи файла .cur_input, если он существует, и в обычный каталог вывода в противном случае. Вы можете использовать его для указания на ramdisk/tmpfs. Это увеличивает скорость на небольшую величину, но также снижает нагрузку на SSD:
    **Монтирование tmpfs**:```sudo mount -t tmpfs -o size=6g tmpfs /home/fuzzing```  

## ПРОИЗВОДИТЕЛЬНОСТЬ:  
**Использование множества ядер**:  
-    Рекомендуется запускать экземпляры с кэшированием тестовых примеров. ```AFL_TESTCACHE_SIZE```, значение между 50-500MB.  
-    Перед запуском фазера объявить переменную ```AFL_FINAL_SYNC=1```.

Должен быть один главный фаззер (опция -M main-$HOSTNAME - установите также AFL_FINAL_SYNC=1) и столько вторичных фаззеров (например, -S variant1), сколько у вас ядер, которые вы используете. Каждая запись -M/-S должна иметь уникальное имя (которое может быть любым), однако для всех экземпляров должно использоваться одно и то же местоположение выходного каталога -o.  

```
for i in $(seq 1 19); do
    afl-fuzz -i input_dir -o output_dir -S slave$i -- ./target_binary @@ &
done
```

Для каждого вторичного фаззера должна быть своя вариация, например:  
-  несколько целей, скомпилированы с активированными санитайзерами (export AFL_USE_ASAN=1 ; export AFL_USE_UBSAN=1 ; export AFL_USE_CFISAN=1).
-  один или два должны выполнить проверку цели с помощью CMPLOG/redqueen.
-  от одного до трех фаззеров должны фаззить цель, скомпилированную с помощью laf-intel/COMPCOV (Если запущенно несколько фаззеров laf-intel/COMPCOV, то для чтобы они делились своими промежуточными результатами, главный фаззер (-M) должен быть одним из них (хотя на самом деле это не рекомендуется)).

## НАЧАЛО ФАЗИНГА:  

**Запуск основного фазера**: ```afl-fuzz -i input -o output -M main-$(HOSTNAME) -- ./harness @@```  
**Запуск второстепенного фазера**: ```afl-fuzz -i input -o output -S secondary-0 -- ./harness @@```  
**Остановка фазера**: CTRL + C  
**Возобновить работу фазера**: ```afl-fuzz -D -i - -o out ./test_fuzzer @@```  
