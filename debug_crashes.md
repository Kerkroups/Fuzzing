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

## Assambler:  

- [...] всегда означает «разыменуй адрес».
- Если [...] слева — запись в память;
- Если [...] справа — чтение из памяти.

```mov rax, [rdx]``` = move in RAX content of RDX point to. [] = dereference value betwen them. a = *b.  
```mov rax, rdx``` = move content from RDX to RAX.  
```mov rax, 1``` = move 1 to RAX.  
```call 0x11223344``` = call the function at address.  
```cmp rax, 1``` = compare RAX with 1.  
```jmp 0x11223344``` = unconditional jump to address.  


