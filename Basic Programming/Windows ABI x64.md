x64 Application Binary Interface (ABI) использует четыре регистра, fast-call calling convention по-умолчанию. В стеке вызовов выделяется место в качестве "теневого хранилища", в котором вызываемые функции (callee) могут сохранять эти регистры. Передеваемый аргумент, размер которого превышает 8 бай или не равен 1, 2, 4 или 8 байтам должен передаваться по ссылке. Один аргумент не никогда распределяется не распределяется по нескольким регистрам.  
```
func1(int a, int b, int c, int d, int e, int f);
// a в RCX, b в RDX, c в R8, d в R9, f затем e помещаются в стэк.
```
```
func2(float a, double b, float c, double d, float e, float f);
// a в XMM0, b в XMM1, c в XMM2, d в XMM3, f затем e помещаются в стэк.
```
```
func3(int a, double b, int c, float d, int e, float f);
// a в RCX, b в XMM1, c в R8, d в XMM3, f затем e помещаются в стэк.
```
```
func4(__m64 a, __m128 b, struct c, float d, __m128 e, __m128 f);
// a в RCX, указатель на b в RDX, указатель на c в R8, d в XMM3, указатель на f помещаеся в стэк, затем указатель на e помещается в стэк.
```
```
func1();
func2() {   // RCX = 2, RDX = XMM1 = 1.0, and R8 = 7
   func1(2, 1.0, 7);
}
```

**Возвращаемое значение**:  
```
__int64 func1(int a, float b, int c, int d, int e);
// Caller помещает a в RCX, b в XMM1, c в R8, d в R9, e помещается на стэк, callee возвращает __int64 результат в RAX.
```
```
__m128 func2(float a, double b, int c, __m64 d);
// Caller помещает a в XMM0, b в XMM1, c в R8, d в R9, callee возвращает __m128 результат в XMM0.
```

Возврат указателя:  
```
struct Struct1 {
   int j, k, l;    // Struct1 превышает 64 бит.
};
Struct1 func3(int a, double b, int c, float d); // Caller выделяет память для Struct1, затем передает указатель в RCX, a в RDX, b в XMM2, c в R9, d помещается в стэк; callee возвращает указатель на Struct1, затем помещает результат в RAX.
```

Возврат значения:  
```
struct Struct2 {
   int j, k;    // Struct2 помещается в 64 бит, и соотетствует требованию для возврата по значению.
};
Struct2 func4(int a, double b, int c, float d); // Caller помещает a в RCX, b в XMM1, c в R8, and d в XMM3; callee возвращает Struct2 результат по значение в RAX.
```

## Информация:  
1. https://learn.microsoft.com/ru-ru/cpp/build/stack-usage?view=msvc-170
2. https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170#x64-register-usage
3. https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170
