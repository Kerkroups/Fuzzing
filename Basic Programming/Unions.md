Union область памят в которой могут храниться значения сразу нескольких переменных, но память выделяется для переменной наибольшего типа, например:  
```
#include <stdio.h>

typedef struct {
  int i;
  float f;
  char ch[16];
} Data;

union my_union {
  int i;
  float f;
  char ch[16];
}

void main() {
Data d;
union my_union u;

printf("Struct d has size of = %d\n", sizeof(d)); // 24 bytes
printf("Union u has size of = %d\n", sizeof(u)); // 16 bytes

strcpy(&u.ch, "testdata");
printf("%f\n", u.f); // Представит строку "testdata" в формате float;
}
```

Примерение Union:  
- Конвертация данных.
