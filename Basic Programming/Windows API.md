## БАЗОВЫЕ ТИПЫ ДАННЫХ  
Для использования базовых типов данных необходимо добавить заголовок Windows.h ```#include <Windows.h>```  

Полный справочник по типам данных в Windows: [https://learn.microsoft.com/ru-ru/windows/win32/winprog/windows-data-types](https://learn.microsoft.com/ru-ru/windows/win32/winprog/windows-data-types)  

HANDLE - универсальный дескриптор объекта.
```
HANDLE fileHandle = CreateFile(
  "file.txt",
  GENERIC_READ,
  FILE_SHARE_READ,
  NULL,
  OPEN_EXISTING,
  FILE_ATTRIBUTE_NORMAL,
  NULL);
```

HWBD - дескриптор окна.
```
HWND myWindow = CreateWindowA(
  "STATIC",             // Window class
  "Initial Title",      // Window title
  WS_OVERLAPPEDWINDOW,  // Style
  CW_USEDEFAULT, 0,     // Position
  300, 200,             // Size
  NULL, NULL, NULL, NULL);
```

HINSTANCE - указатель на объект в памяти (exe,dll,etc.)  
```
HINSTANCE hInstance = GetModuleHandle(NULL);
```

VOID - любой тип. (применяется к функциям. Выполнить действие без возврата значения)
```
void myFunction(){ //Perform actions without return value }
```

HMODULE - дескриптор модуля, указывает на базовый адрес модуля в памяти, похож на HINSTANCE. 

```
HMODULE hModule = LoadLibrary("library.dll");
```  

