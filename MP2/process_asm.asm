section .data
    msg db "%.1lf",0
    comma db ", ",0

section .text
    extern printf
    bits 64
    Default rel
    global process

process:
    mov r10, rcx  ; Store the array pointer in r10
    mov r11, rdx  ; Store the array size in r11
    
    mov rax, 3    ; Start index at 3

loop:
    cmp rax, r11
    jge end
    
    mov rbx, rax
    sub rbx, 3
    cmp rbx, 0
    jl next_iteration
    
    mov rbx, rax
    add rbx, 3
    cmp rbx, r11
    jge next_iteration
    
    xorps xmm0, xmm0
    
    movsd xmm1, [r10 + (rax - 3) * 8]  ; Load num[i - 3] to xmm1
    addsd xmm0, xmm1  ; xmm0 = xmm0 + xmm1
    movsd xmm2, [r10 + (rax - 2) * 8]  ; Load num[i - 2] to xmm2
    addsd xmm0, xmm2  ; xmm0 = xmm0 + xmm2
    movsd xmm3, [r10 + (rax - 1) * 8]  ; Load num[i - 1] to xmm3
    addsd xmm0, xmm3  ; xmm0 = xmm0 + xmm3
    movsd xmm4, [r10 + rax * 8]        ; Load num[i] to xmm4
    addsd xmm0, xmm4  ; xmm0 = xmm0 + xmm4
    movsd xmm5, [r10 + (rax + 1) * 8]  ; Load num[i + 1] to xmm5
    addsd xmm0, xmm5  ; xmm0 = xmm0 + xmm5
    movsd xmm6, [r10 + (rax + 2) * 8]  ; Load num[i + 2] to xmm6
    addsd xmm0, xmm6  ; xmm0 = xmm0 + xmm6
    movsd xmm7, [r10 + (rax + 3) * 8]  ; Load num[i + 3] to xmm7
    addsd xmm0, xmm7  ; xmm0 = xmm0 + xmm7
    
    ; Print the result
    sub rsp, 8*7
    lea rcx, [msg]
    movq rdx, xmm0
    call printf
    add rsp, 8*7
    
    ; Print comma and space if not the last iteration
    mov rbx, rax
    inc rbx
    cmp rbx, r11
    jge end
    sub rsp, 8*7
    lea rcx, [comma]
    call printf
    add rsp, 8*7

next_iteration:
    inc rax
    jmp loop

end:
    ret