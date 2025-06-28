# ШАБЛОНЫ ДЛЯ HARNESS: 

1. Идентифицировать целевую функцию.
2. Изучить формат ввода данных и интерфейс функции.

**ШАБЛОН 1**
```
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <stddef.h>

__AFL_FUZZ_INIT();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
   char filename[] = "/tmp/fuzz_image_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) return 0;

    FILE *out = fdopen(fd, "wb");
    if (!out) {
        close(fd);
        unlink(filename);
        return 0;
    }
    
    fwrite(data, 1, size, out);
    fclose(out);

    try {
        // CODE LIGIC
    } catch(...) {
    }

    unlink(filename);
    return 0;

}

extern "C" int main(int argc, char **argv) {
#ifdef __AFL_HAVE_MANUAL_CONTROL
    __AFL_INIT();
#endif

    while (__AFL_LOOP(10000)) {
        LLVMFuzzerTestOneInput(__AFL_FUZZ_TESTCASE_BUF, __AFL_FUZZ_TESTCASE_LEN);
    }

    return 0;
}


```
---------------------------------------------------------------------------------

**ШАБЛОН 2**
---------------------------------------------------------------------------------

```
#include <stdio.h>
#include <unistd.h>

int main() {

__AFL_INIT();
    unsigned char buf[1024];

    while (__AFL_LOOP(10000)) {  // 10,000 итераций в одном процессе
        ssize_t len = read(0, buf, sizeof(buf));
        if (len <= 0) break;

        // Ваша логика обработки данных
    }

    return 0;
}

```

---------------------------------------------------------------------------------  

# ИНСТРУМЕНТАЦИЯ:  

**Выборочная инструментация**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.instrument_list.md  
**CTX**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md#6-afl-context-sensitive-branch-coverage  
**LTO**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md  
**LAF-INTEL**: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.laf-intel.md

# CАНИТАЙЗЕРЫ:  

- Активировать санитайзер COMPCOV: ```AFL_LLVM_LAF_ALL=1```
- Активировать санитайзер Input-to-State: ```AFL_LLVM_CMPLOG=1 //For GCC use AFL_GCC_CMPLOG=1```
- Активировать санитайзер ASAN: ```AFL_USE_ASAN=1```
- Активировать санитайзер MSAN: ```AFL_USE_MSAN=1```
- Активировать санитайзер USBAN: ```AFL_USE_UBSAN=1```
- Активировать санитайзер CFISAN: ```AFL_USE_CFISAN=1```
- Активировать санитайзер TSAN: ```AFL_USE_TSAN=1```
- Активировать санитайзер LSAN: ```AFL_USE_LSAN=1```. __AFL_LEAK_CHECK(); добавляется во все области целевого исходного кода, где необходимо проверить утечку! Чтобы игнорировать проверку на утечку памяти для определенных распределений __AFL_LSAN_OFF();
- AFL_HARDEN=1

 # ЧАСТИЧНАЯ ИНСТРУМЕНТАЦИЯ:  
Для afl-clang-fast/afl-clang-fast++ or afl-clang-lto/afl-clang-lto++:
- ```AFL_LLVM_ALLOWLIST``` - список файлов и функций для инструментации.
- ```AFL_LLVM_DENYLIST``` - список файлов и функций запрещенных для инструментации.

# ИНСТРУМЕНТАЦИЯ ФАЛОВ ДЛЯ LIBFUZZER: 
Добавить флаг ```-fsanitize=fuzzer```  

## SOURCES:  
https://www.srlabs.de/blog-post/guide-to-writing-fuzzing-harness  
https://bushido-sec.com/index.php/2025/01/03/fuzzing-harness-guide/  
