Если ничего не записать по адресу в памяти, то там наверняка будет какой нибудь мусор, а не нули или какие лиюо действительные команды.  

**Прямая адрессация**:  
```
mov rsi, rax ; Копирует RAX в RSI.
```

**Непрямая адрессация**:  
```
mov rax, [rbx] ; Скопировать значение из памяти по адресу из регистра RBX в RAX
mov rsi, [rax] ; Копирует содержимое памяти (8 последовательных байт) начинающееся по адресу указанному в регистре RAX в RSI.
//
mov rdi, my_array ; Загружаем начальный адрес массива в RDI
mov rax, [rdi]    ; RAX теперь равен первому элементу массива
//
mov al, [rbx + 4] ; Взять байт по адресу (RBX + 4)
//
mov edx, [rcx + rsi*4] ; Доступ к элементу массива int (4 байта)
```
**Спецификаторы типа**:  
BYTE = 1 байт;  
WORD = 2 байт;  
DWORD = 4 байта;  
QWORD = 8 байт;  
TBYTE = 10 байт;  


## Информация:  
1. https://www.zerosday.com/post/my-ebook/my-ebook-part-4-03-x86-x64-arm-architectures
2. https://www.zerosday.com/post/my-ebook/my-ebook-part-4-04-registers-memory-stack
3. https://www.zerosday.com/category/assembly-ebook?sort=old
