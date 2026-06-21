## GDB + GEF

Компилируем бинарник с опцией "-g" для добавления отладочной информации.  
```list``` - показать код на Си.  
```b <имя функции / строка кода / *адресс>``` - установка точки останова.  
```set disassembly-flavor intel``` - установка синтаксиса инструкций ассамблера Intel.  
```disassemble <имя функции>``` - дизассаблирование функции, выведет инструкции на языке ассамблер.  
```info proc mappings``` - отобразит память процесса.  
```info locals``` - отобразит значение переменных.  
```print *my_pointer``` - выведет значение указателя.  
```x/32xw my_pointer``` - выведет 32 word в формате hex указателя (переменной).   
```x/s my_pointer``` - выведет значение указателя / переменной в виде строки.  
```find start_address, end_address, "secret_string"``` - поиск строк в диапазоне адрессов.  
**GEF**:  
```
heap arenas: Inspect the active arenas and top chunk.
heap chunks: Display a structured list of all allocated and free chunks.
heap chunk [address]: Examine a specific chunk's metadata in detail
```




## PWNTOOLS  

## Информация:  
1. https://www.zerosday.com/post/my-ebook/my-ebook-part-4-05-debugging-and-binary-analysis
