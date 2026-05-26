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

SIZE_T - беззнаковое целочисленное. x32 = 4 байта, x64 = 8 байт. Всегда положителен. Используется везде, где фигурируют размеры памяти или кодичесвто элементов.  

ULONG_PTR - беззнаковое целочисленное, по размеру в точности совпадает с размером указателя текущей платформы. x32 = 4 байта, x64 = 8 байт. Используется для побитовых операций или адрессной арифметике. Может хранить указатель как десятичное число.  
```
ULONG_PTR ptrValue = (ULONG_PTR)somePointer;
```

PVOID - указатель на любой тип.
```
PVOID pVoid = malloc(10);
```

DWORD - беззнаковое 32-разрядное число. Диапазон от 0 до 4294967295.  
```
DWORD dWord = 0xFFFFFFFF;
WORD wValue = 0xFFFF;
BYTE bValue = 0xFF;
```

LPSTR - указатель на строку, завершаемую NULL, из 8-разрядных (8 бит) символов Windows (ANSI).  
```
LPSTR str = "Windows string";
```

LPCSTR - указатель на константную строку, завершаемую NULL, из 8-разрядных (8 бит) символов Windows (ANSI).
```
LPСSTR сStr = "Constant Windows string";
```

LPWSTR - указатель на строку, завершаемую NULL, из 16-разрядных (16 бит) символов Unicode.  
```
LPWSTR lStr = L"Unicode string";
```

LPWCSTR - указатель на константную строку, завершаемую NULL, из 16-разрядных (16 бит) символов Unicode.  
```
LPWCSTR lCStr = L"Constant Unicode string";
```  

LPARAM - параметр сообщения. Используется для передачи дополнительной информации о каком либо системном событии. Выступает в роли контейнера для данных при обработке сообщений (клик мыши, нажатие клавиши, изменение размера окна, и т.д.). Выступает указателем на блок памяти (структуру или строку) если для события нужно передать большой объем данных.  
```
LPARAM lParam = (LPARAM)somePointer;
```

WPARAM - беззнаковый параметр сообщения.  
```
WPARAM wParam = (WPARAM)someUnsignedPointer;
```

LPCVOID - указатель на константу любого типа (READ ONLY).  
```
LPCVOID pcVoid = malloc(10);
```  
