Соглашение вызова - это правила передач аргументов в функкции, как обрабатываются возвращаемые значения и какие регистры вызываемая функция может может свободно модифицировать.  

fastcall

cdecl

stdcall

**Function prologue example**:  
```
push rbp
mov rbp, rsp
sub rsp, 24
```

**Function epilogue example**:  
```
mov rsp, rbp
pop rbp
ret
```
OR  
```
leave
ret
```  

## Информация:  
1. https://learn.microsoft.com/ru-ru/cpp/build/x64-calling-convention?view=msvc-170
