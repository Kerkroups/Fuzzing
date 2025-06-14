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

