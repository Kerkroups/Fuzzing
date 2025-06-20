1. Идентифицировать целевую функцию.
2. Изучить формат ввода данных и интерфейс функции.

```
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__AFL_FUZZ_INIT();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FILE *fp = fmemopen((void *)data, size, "rb");
    if (!fp) return 0;

    char filename[] = "/tmp/fuzz_image_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) return 0;

    fwrite(data, 1, size, fp);
    fclose(fp);
    return 0;

    try {
        //CODE LOGIC
    } catch() {
        ...
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
## SOURCES:  
https://www.srlabs.de/blog-post/guide-to-writing-fuzzing-harness
