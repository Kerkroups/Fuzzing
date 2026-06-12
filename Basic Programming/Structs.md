Структура это объединения разных типов данных в один, например:  
```
struct MYSTRUCT {
  int a;
  char b[10];
  float c;
  char *myFunc();
}
int main(){
  struct MYSTRUCT data;
  data.a = 1;
  data.b[0] = 'a';
  data.c = 1.0;
}
```
Объявление через typedef:  
```
typedef struct {
   int a;
   char b[10];
} MYSTRUCT;

MYSTRUCT data;
MYSTRUCT data2 = {1,'a',2.0, NULL} //Объявление структуры и задание значений переменным в соответствии с порядком типов данных в структуре.
```
Использование malloc для выделения памяти элементу структуры:  
```
typedef struct {
  int *arr;
} Data;

Data d;
d.arr = malloc(sizeof(int) * 5); // Выделим память для хранения данных 5 элементов типа int; аналогично int arr[5];
```

Шаблон структуры:  
```
struct имя {
  тип поле;
  ...
} список переменых;
```

Доступ к элементам стрктуры осуществляется с помощью оператора ```.``` или ```->```, напрмер: ```data.a, data->a```;  

**Функции в структурах**:  
В Си структуры не могут содержать функции внутри себя. Функции в структуре можно сымитировать с помощью указателей на функции, сделав их полями структуры.  

```
#include <stdio.h>

int get_area(int x, int y) {
  return x*y;
}

struct Rectangle {
  int width;
  int height;
  int (*area)(int, int); // Указатель на функцию;
}

int main() {
  struct Rectangle rect;
  rect.width = 5;
  rect.height = 5;
  rect.area = get_area; // Можно записать как rect.area = &get_area;
  int result = rect.area(rect.width, rect.height);
  printf("Area: %d\n", result);
  return 0;
}
```
**Передача структур в функции**:  
Передача структуры в аргументы функции осуществляется двумя способами:  
1. По значению: создается копия структуры.
2. По указателю: передается адрес структуры. Позволяет функции менять оригинальные данные в структуре.

```
#include <stdio.h>

struct Rectangle {
  int x;
  int y;
}

int move_point(struct Rectangle *p, int x, int y) {
  p->x += x;
  p->y += y;
}

int main() {
  struct Rectangle my_point = {10, 20};
  move_point(&my_point, 5, -5); // 10 + 5, 20 - 5
  printf("X: %d, Y: %d", my_point.x, my_point.y); // X: 15, Y: 15
  return 0;
}
```
**Вложенные структуры**:  
Структуры могту быть объявлденны внутри других структур. Существует два основных способа создания вложенных структур:  
1. Прямое объявление - тип вложенной структуры определяется внутри главной.
2. Использование ссылок - создание структуры отдельно, а затем включение экземпляра или указателя на нее в качестве поля.

```
#include <stdio.h>
#include <string.h>

struct Address {
  char city[50];
  char street[50];
  int house;
}

struct Employee {
  char name[50];
  int id;
  struct Address address;
}

int main() {
  struct Employee emp;
  strncpy(emp.name, "Test", sizeof(emp.name - 1));
  emp.id = 100;
  strncpy(emp.address.city, "Washington", sizeof(emp.address.city - 1);
  strncpy(emp.address.street, "Test street", sizeof(emp.address.street - 1);
  emp.address.house = 1;
  return 0;
}
```  
**Размер структуры**: sizeof() структуры равен сумме всех её полей (с учетом выравнивания памяти компилятором).  
**Динамические структуры**:  
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
  char *city;
  int house;
}

struct Employee {
  char *name;
  struct Address *address; // Указатель на структуру.
}

int main() {
  struct Employee emp = (struct Employee *)malloc(sizeof(struct Employee)); // Выделяем память под структуру Employee;
  if (emp == NULL) return 1;
  emp->address = (struct Address *)malloc(sizeof(struct address)); // Выделяем память под структуру Address;
  if (emp->address == NULL) {
    free(emp);
    return 1;
  }
  emp->name = (char *)malloc(50 * sizeof(char)); // Выделяем память под переменную name внутри структуры Employee;
  emp->address->city = (char *)malloc(50 * sizeof(char)); // Выделяем память под переменную city внутри структуры Address;
  strncpy(emp->city, "Tester", sizeof(emp.name - 1);
  strncpy(emp->address->city, "Washington", sizeof(emp.address.city - 1);
  emp->address->house = 1;
  printf("Employee: %s, city: %s, house: %d", emp->name, emp->address->city, emp->address->house);

  free(emp->address->house);
  free(emp->address->city);
  free(emp->address);
  free(emp->name);
  free(emp);

  return 0;
}
```
Если очищать память в неправильном порядке могут возникнуть такие проблемы:  
1. Утечка памяти;
2. Segmentation fault;

Если сначала удалить основную структуру ```free(emp)```, то адресс вложенной структуры может быть потерян. Программа больше не имеет кним доступа, но операционная система считает эту память занятой.  

Use-after-free:  
```
free(emp);
free(emp->address); // Чтение из неопределенной памяти.
```
Программа попытается прочитать данные по случайному адресу.  
