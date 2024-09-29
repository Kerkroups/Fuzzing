## AFL++, make  

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

  
**Выбор данных для тестирования**:  
Данные для тестирования в контексте фаззинга называются "corpus". Это могут быть любые файлы, например png,zip,pdf,etc. Расширение файла подбиравется в зависимости от того с каким расширением взаимодействует приложение. Чем больше данных для тестирирования - тем лучше.  

**Создание уникального "corpus"**:  
Утилита afl-cmin применяется для удаления из корпуса входов, которые не дают нового пути/покрытия в целевой группе.
```
afl-cmin -i INPUTS -o INPUTS_UNIQUE -- bin/target -someopt @@
```

- Если цель читает из stdin (стандартный ввод):
```
afl-cmin -i INPUTS -o INPUTS_UNIQUE -- bin/target -someopt
```
**Минимизируем файлы "corpus" **:  
```
mkdir input
cd INPUTS_UNIQUE
for i in *; do
  afl-tmin -i "$i" -o "../input/$i" -- bin/target -someopt @@
done
```
**Дополнительные опции перед началом фаззинга**:  
1. sudo afl-system-config  
2. sudo afl-persistent-config
3. export AFL_SKIP_CPUFREQ=1

**Словари**:  
- С помощью afl-clang-fast вы можете установить AFL_LLVM_DICT2FILE=/full/path/to/new/file.dic для автоматической генерации словаря во время компиляции цели. Добавление AFL_LLVM_DICT2FILE_NO_MAIN=1, чтобы не разбирать main (обычно это разбор параметров командной строки), также часто является хорошей идеей.  
- Указать afl-fuzz загрузить словарь: использовать флаг ```-x dictionaries/FORMAT.dict```.  

**Использование множества ядер**:  
Рекомендуется запускать экземпляры с кэшированием тестовых примеров. ```AFL_TESTCACHE_SIZE```, значение между 50-500MB.  

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

