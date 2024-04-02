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
	movss xmm1, [rcx + (rax - 3) * 4]      ; Load num[i - 3] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + (rax - 2) * 4]      ; Load num[i - 2] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + (rax - 1) * 4]      ; Load num[i - 1] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + rax * 4]            ; Load num[i] to xmm4
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + (rax + 1) * 4]      ; Load num[i + 1] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + (rax + 2) * 4]      ; Load num[i + 2] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1
	movss xmm1, [rcx + (rax + 3) * 4]      ; Load num[i + 3] to xmm1
	addss xmm0, xmm1                       ; xmm0 = xmm0 + xmm1

	; Add sum to Y array
	movss [r8 + r11 * 4], xmm0

	inc r11

next_iteration:
	inc rax
	jmp loop

end:
	ret