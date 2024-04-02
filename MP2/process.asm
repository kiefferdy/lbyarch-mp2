section .text
bits 64
default rel
global process

process:
	mov rax, 3       ; Start index at 3
	xor r11, r11     ; Initialize counter to 0

loop:
	; Ensure out of bounds elements is not accessed
	mov r10, rax
	sub r10, 3
	cmp r10, 0
	jl next_iteration

	; Exit the loop when end of array has been reached
	mov r10, rax
	add r10, 3
	cmp r10, rdx
	jge end

	; Initialize xmm0 to 0
	xorps xmm0, xmm0

	; Perform calculations
	movsd xmm1, [rcx + (rax - 3) * 8]      ; Load num[i - 3] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + (rax - 2) * 8]      ; Load num[i - 2] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + (rax - 1) * 8]      ; Load num[i - 1] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + rax * 8]            ; Load num[i] to xmm4
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + (rax + 1) * 8]      ; Load num[i + 1] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + (rax + 2) * 8]      ; Load num[i + 2] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movsd xmm1, [rcx + (rax + 3) * 8]      ; Load num[i + 3] to xmm1
	addsd xmm0, xmm1                       ; xmm0 = xmm0 + xmm1

	; Add sum to Y array
	movsd [r8 + r11 * 8], xmm0

	inc r11

next_iteration:
	inc rax
	jmp loop

end:
	ret