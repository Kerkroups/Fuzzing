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

