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
