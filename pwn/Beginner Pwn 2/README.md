# Beginner Pwn 2

This program is an example of a typical ret2win. In this case you need to overwrite the return pointer with the pointer to the beginning of the win function.

# To solve

The length between the start of the buffer and the return pointer is 18 bytes. So you can write 18 bytes up to the return pointer and replace it with the pointer to win.

python3 exploit.py