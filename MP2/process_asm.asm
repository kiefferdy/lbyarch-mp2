section .data
    msg db "%.1lf",0
    comma db ", ",0

section .text
    extern printf
    bits 64
    Default rel
    global process

process:
    mov r15, rcx  ; Store the array pointer in r15
    mov r14, rdx  ; Store the array size in r14
    
    mov rsi, 3    ; Start index at 3

loop:    
    mov rbx, rsi
    sub rbx, 3
    cmp rbx, 0
    jl next_iteration
    
    mov rbx, rsi
    add rbx, 3
    cmp rbx, r14
    jge end
    
    xorps xmm0, xmm0  ; Initialize xmm0 to 0
    
    ; Perform calculations
    movsd xmm1, [r15 + (rsi - 3) * 8]  ; Load num[i - 3] to xmm1
    addsd xmm0, xmm1  ; xmm0 = xmm0 + xmm1
    movsd xmm2, [r15 + (rsi - 2) * 8]  ; Load num[i - 2] to xmm2
    addsd xmm0, xmm2  ; xmm0 = xmm0 + xmm2
    movsd xmm3, [r15 + (rsi - 1) * 8]  ; Load num[i - 1] to xmm3
    addsd xmm0, xmm3  ; xmm0 = xmm0 + xmm3
    movsd xmm4, [r15 + rsi * 8]        ; Load num[i] to xmm4
    addsd xmm0, xmm4  ; xmm0 = xmm0 + xmm4
    movsd xmm5, [r15 + (rsi + 1) * 8]  ; Load num[i + 1] to xmm5
    addsd xmm0, xmm5  ; xmm0 = xmm0 + xmm5
    movsd xmm6, [r15 + (rsi + 2) * 8]  ; Load num[i + 2] to xmm6
    addsd xmm0, xmm6  ; xmm0 = xmm0 + xmm6
    movsd xmm7, [r15 + (rsi + 3) * 8]  ; Load num[i + 3] to xmm7
    addsd xmm0, xmm7  ; xmm0 = xmm0 + xmm7
    
    ; Print the result
    sub rsp, 8*5
    lea rcx, [msg]
    movq rdx, xmm0
    call printf
    add rsp, 8*5
    
    ; Print comma and space if not the last iteration
    mov rbx, rsi
    add rbx, 4
    cmp rbx, r14
    jge end

    sub rsp, 8*5
    lea rcx, [comma]
    call printf
    add rsp, 8*5

next_iteration:
    inc rsi
    jmp loop

end:
    xor rax, rax
    ret