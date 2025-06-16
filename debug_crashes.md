Before test maybe need to disable ASLR:
```
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

Enable ASLR:
```
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space
```

Run binary in gdb:  
```
gdb --args ./[binary_name] [binary_options] crashes/[crash-id]
```

Set Intel syntax:  
```
set disassembly-flavor intel
```

[OPTIONAL]: Set pre-defined breakpoints.

Show backtrace:  
```
bt full
```

Registers information:
```
// Show information about values that stored in registers.
info registers

// Show instruction pointer value (next address to execute commands)
x/i $rip
```

In general we interested in RIP, RAX, RDI, RDX, RCX, RSI registers. If we got valuse from file in RCX, RDI, RSI - it's interesting, need to examine.

Searching for loaded libraries:  
```
info proc mapping
```

Get information about binary:  
```
// Get information about binary headers
readelf -S ./binary_name
```

Get information which shared libraries used by application:  
```
ldd ./binary_name
```

Get information abount application sections:  
```
readelf -p [section_name] ./binary_name
OR
objdump -s --section [section_name] ./binary_name
```

Get function names that used in application:  
```
nm -D --demangle ./binary_name
```

## Assambler:  

- [...] всегда означает «разыменуй адрес».  
- Если [...] слева — запись в память;  
- Если [...] справа — чтение из памяти.
- Heap - растет от младших адресов к старшим.
- Stack - растет от сарших адресов к младшим. Используется для хранения локальных переменных, передачи аргументов в тело функции.

.text = code segment, machine instruction.  
.data = initialized global and static variables.  
.bss = uninitialized global and static variables.  

```mov rax, [rdx]``` = move in RAX content of RDX point to. [] = dereference value betwen them. a = *b.  
```mov rax, rdx``` = move content from RDX to RAX.  
```mov rax, 1``` = move 1 to RAX.  
```call 0x11223344``` = call the function at address.  
```cmp rax, 1``` = compare RAX with 1.  
```jmp 0x11223344``` = unconditional jump to address.  
x/gx $rbp-8   # посмотреть возможную канарейку
x/gx $rbp     # сохранённый rbp
x/gx $rbp+8   # адрес возврата


BYTE = 1 byte = 8 bits.  
WORD = 2 bytes = 16 bits.  
DWORD = 4 bytes = 32 bits.  
QWORD = 8 bytes = 64 buts.  

## PTL + GOT  (https://lief.re/doc/latest/tutorials/05_elf_infect_plt_got.html)
PLT (Procedure Linkage Table) — это специальная таблица (и набор инструкций) в ELF-бинарниках, которая используется для вызова функций из динамических библиотек (например, libc), до тех пор, пока не будет известен их реальный адрес.
GOT (Global Offset Table) используется только в динамически слинкованных ELF-бинарниках.  
  - Она хранит адреса функций из динамических библиотек (например, libc.so.6).
  - При первом вызове функции (через PLT) из стандартной библиотеки, туда заносится реальный адрес, загруженный динамическим линковщиком (ld-linux.so).
  - GOT — это способ обеспечить отложенное связывание (lazy binding) и позиционно-независимую работу кода.

Можем эксплуатировать GOT если соблюденые такие условия:
  - Динамически слинкованный ELF (не -static).
  - Не включён RELRO=full (или RELRO=partial, тогда GOT можно переписать до разрешения символа).
  - Нет защиты NX (или есть возможность переписать адрес с помощью write-primitive).

ВАЖНО: проверить в какой области памяти находятся регистры. Например rsi,rax,rdi,rdx в heap? mmap?

Контролируеая операция ```memcpy(dst, src, size);``` может привести к RCE. arbitrary write (dst = какой-то ptr, src = shellcode)
