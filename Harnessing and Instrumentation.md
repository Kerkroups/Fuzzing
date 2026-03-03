# ШАБЛОНЫ ДЛЯ HARNESS: 

1. Идентифицировать целевую функцию.
2. Изучить формат ввода данных и интерфейс функции.

[templates](templates)  

**Дополнительные гайды по созданию harness**:  
 - [STDIN](https://appsec.guide/docs/fuzzing/c-cpp/aflpp/#standard-input-stdin-fuzzing)
 - [FILE BASED](https://appsec.guide/docs/fuzzing/c-cpp/aflpp/#file-input-fuzzing)
 - [ARGUMENT BASED](https://appsec.guide/docs/fuzzing/c-cpp/aflpp/#argument-fuzzing)  

Если написать harness нет возможности или не хочется ломать над этим всем голову, то есть следующие варианты:  
 - Ищем в коде, который хотим пофазить, нужные нам функции и обворачиваем их в AFL PERSISTENT LOOP, предварительно не забываем подключить заголовки AFL, и инструментируем бинарник.
 - У проекта есть готовый вариант для libFuzzer. Инструментирует бинарник с флагом -fsanitize=fuzzer, после ищем бинарник для фазинга и запускаем фазинг с помощью libFuzzer.

# ИНСТРУМЕНТАЦИЯ:  

**Выборочная инструментация**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.instrument_list.md  
**CTX**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md#6-afl-context-sensitive-branch-coverage  
**LTO**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md  
**LAF-INTEL**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.laf-intel.md

# CАНИТАЙЗЕРЫ:  

- **Активировать санитайзер COMPCOV**: ```AFL_LLVM_LAF_ALL=1```
- **Активировать санитайзер Input-to-State**: ```AFL_LLVM_CMPLOG=1 //For GCC use AFL_GCC_CMPLOG=1```
- **Активировать санитайзер Address sanitizer (ASAN)**: ```AFL_USE_ASAN=1```; Помогает находить memory corruption уязвимости, например: HEAP/STACK buffer overflow, Use-After-Free, NULL pointer dereference. Замедляет фазинг в 2 раза.  
- **Активировать санитайзер Memory sanitizer (MSAN)**: ```AFL_USE_MSAN=1```; Помогает обнаружить ошибки чтения неинициализированной памяти. Замедляет фазинг в 3 раза.  
- **Активировать санитайзер Undefined Behaviour sanitizer (UBSAN)**: ```AFL_USE_UBSAN=1```; Помогает обнаружить нестандартное поведение, например превышение диапазона целочисленного числа со знаком в следствии сложения двух целых чисел со знаком.  
- **Активировать санитайзер Control Flow Integrity sanitizer (CFISAN)**: ```AFL_USE_CFISAN=1```; Помогает обнаружить Type Confusion уязвимости.  
- **Активировать санитайзер Thread sanitizer (TSAN)**: ```AFL_USE_TSAN=1```; Помогает обнаружить Race Condition. Замедляет фазинг в 5-15 раз.  
- **Активировать санитайзер Leak sanitizer (LSAN)**: ```AFL_USE_LSAN=1```. Используется для разработчиков, мало чем помогает в фазинге. __AFL_LEAK_CHECK(); добавляется во все области целевого исходного кода, где необходимо проверить утечку! __AFL_LSAN_OFF(); ставится пере выделением памяти, __AFL_LSAN_ON(); после. Код между этими двумя макросами не будет проверяться на учтечку памяти.  
- AFL_HARDEN=1

 # ЧАСТИЧНАЯ ИНСТРУМЕНТАЦИЯ:  
Для afl-clang-fast/afl-clang-fast++ or afl-clang-lto/afl-clang-lto++:
- ```AFL_LLVM_ALLOWLIST``` - список файлов и функций для инструментации.
- ```AFL_LLVM_DENYLIST``` - список файлов и функций запрещенных для инструментации.

# ИНСТРУМЕНТАЦИЯ ФАЛОВ LIBFUZZER: 
Добавить флаг ```-fsanitize=fuzzer```  

# SOURCES:  
https://www.srlabs.de/blog-post/guide-to-writing-fuzzing-harness  
https://bushido-sec.com/index.php/2025/01/03/fuzzing-harness-guide/  
