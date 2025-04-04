        global _start
        section .text
_start:
        lea r13, [data + 6144]
        xor r14, r14
        mov rdi, [rsp + 0x10]
        mov rax, 2
        xor esi, esi
        xor edx, edx
        syscall
        mov r12, rax
loop:   call next
        jmp [data + rax * 8]
next:   inc r14
        xor eax, eax
        mov rdi, r12
        lea rsi, [rsp - 1]
        mov byte [rsi], 0
        mov rdx, 1
        syscall
        movzx eax, byte [rsp - 1]
        ret
id:     sub rax, 44
        sub [r13], al
        jmp loop
lr:     sub rax, 61
        add r13, rax
        jmp loop
start:  mov al, [r13]
        test al, al
        jz .skip
        push r14
        jmp loop
.skip:  mov r15, 1
sloop:  call next
        add r15, [data + 4096 + rax * 8]
        jmp [data + 2048 + rax * 8]
dec:    jnz sloop
        jmp loop
end:    pop r14
        dec r14
        mov rsi, r14
        mov rax, 8
        mov rdi, r12
        xor edx, edx
        jmp sysjmp
io:     sub rax, 44
        shr rax, 1
        mov rdi, rax
        mov rsi, r13
        mov rdx, 1
        jmp sysjmp
exit:   mov rax, 60
        xor edi, edi
sysjmp: syscall
        jmp loop
        section .data
data:   dq exit, 42 dup(loop), id, io, id, io, 13 dup(loop), lr, loop, lr, 28 dup(loop), start, loop, end, 162 dup(loop), exit, 92 dup(sloop), dec, 162 dup(sloop), 91 dup(0), 1, 0, -1, 162 dup(0), 0x40 dup(0)
