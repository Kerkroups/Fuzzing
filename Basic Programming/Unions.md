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
- Полиморфизм в С.

```
typedef enum {
  JSON_STR,
  JSON_BYTE,
  JSON_INT
} json_type_t;

#define JSON_MAX_STR 64;

typedef struct {
  json_type_t type;
  union {
    char str[JSON_MAX_STR];
    char byte;
    int number;
  };
} json_t;

void print_JSON(json_t *json) {
  switch(json->type){
    case JSON_STR:
      printf("%s\n", json->str);
      break;
    case JSON_BYTE:
      printf("%c\n", json->byte);
      break;
    case JSON_INT:
      printf("%d\n", json->number);
      break;
  }
}

int main(int argc, char *argv[]) {
  json_t my_json;
  my_json.type = JSON_INT;
  my_json.number = 42;
  print_JSON(&my_json);
}
```
