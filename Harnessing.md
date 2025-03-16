1. Идентифицировать целевую функцию.
2. Изучить формат ввода данных и интерфейс функции.

```
#include <libraries>

#ifndef __AFL_FUZZ_TESTCASE_LEN
  ssize_t len; //Определяем переменную которая будет хранить длину входных данных, считанных из stdin.
  #define __AFL_FUZZ_TESTCASE_LEN len //Макрос ссылается на переменную len.
  unsigned char fuzz_buf[1024000]; //Определяем переменную которая будет определять значение буфера. Используется для передачи входных данных фазеру.
  #define __AFL_FUZZ_TESTCASE_BUF buf //Макрос ссылается на переменную buf.
  #define __AFL_LOOP(x) ((fuzz_len = read(0, fuzz_buf, sizeof(fuzz_buf))) > 0 ? 1 : 0) //Читаем данные из stdin в buf. Записываем размер данных в len. Проверяем успешно ли прошло чтение.
#endif

__AFL_FUZZ_INIT();

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  //Обработка входных данных
return 0;
}

//To check: set this before "main()" unsigned char *buffer = __AFL_FUZZ_TESTCASE_BUF;

int main(int argc, char **argv) {

//To check: set this first after "main()" int len = __AFL_FUZZ_TESTCASE_LEN;

#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

    uint8_t buffer[MAX_SIZE]; OR unsigned char *buffer = __AFL_FUZZ_TESTCASE_BUF;

    while (__AFL_LOOP(10000)) { // Persistent Mode
        size_t size = read(0, buffer, MAX_SIZE);
        LLVMFuzzerTestOneInput(buffer, len);
    }
    return 0;
```
---------------------------------------------------------------------------------

```
#include <stdio.h>
#include <unistd.h>

int main() {
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
