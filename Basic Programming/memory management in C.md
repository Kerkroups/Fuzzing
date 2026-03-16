Функции malloc() и calloc() используются для динамического выделения памяти в heap. Разница между этими функциями в том, что malloc() перед выделением памяти не обнуляет её, а calloc() перед выделением памяти обнуляет её. Для использования malloc() и calloc() нужно подключить библиотеку <stdlib.h>.  

Функции для работы с памятью:  
- malloc()
- calloc()
- realloc()

**heap chunk: metadata + userdata**;  
metadata: prev_size, size; где prev_size - размер предыдущего chunk, size - размер текущего chunk.  
Чанки следуют друг за другом. Вычисление следующего чанка находится так: ```next_chunk = chunk + chunk->size```

free(ptr);
Осле освобождения чанка структура чанка меняется:  

| prev_size    |
| size         |  
| fd           |
| bk           |  
| unused space |  

fd - forward pointer;  
bk - backward pointer;  

В данный момент используется **tcache**:  
| prev_size            |
| size                 |  
| next (fd)            |


Пример для free() и malloc(): в этом примере Я пытался понять что такое use-after-free.
```
#include <stdlib.h>
#include <stdio.h>
// #include <string.h>


int main(){

int *arr1;
int *arr2;

arr1 = malloc(10 * sizeof(int));
arr2 = malloc(10 * sizeof(int));

for(int i = 0; i < 10; i++) { arr1[i] = i; }
for(int i = 0; i < 10; i++) { printf("arr[%d] => %d\n", i, arr1[i]); }

free(arr1);
printf("----------------------------------------------------------------------------------------------------------\n");
for(int i = 0; i < 10; i++) { printf("arr[%d] => %d\n", i, arr1[i]); }

return 0;
}
```
Вывод:  
```
arr[0] => 0
arr[1] => 1
arr[2] => 2
arr[3] => 3
arr[4] => 4
arr[5] => 5
arr[6] => 6
arr[7] => 7
arr[8] => 8
arr[9] => 9
----------------------------------------------------------------------------------------------------------
arr[0] => 1431655769
arr[1] => 5
arr[2] => -1008801972
arr[3] => -1489868102
arr[4] => 4
arr[5] => 5
arr[6] => 6
arr[7] => 7
arr[8] => 8
arr[9] => 9
```
После free(arr1) malloc() записыват в пользовательскую часть fd и bk;
