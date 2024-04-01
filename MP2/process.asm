section .text
bits 64
default rel
global process

process:
	xor r11, r11 ; Initialize counter to 0
	mov r12, 3 ; Start index at 3

loop:
	; Ensure out of bounds elements is not accessed
	mov r10, r12
	sub r10, 3
	cmp r10, 0
	jl next_iteration

	; Exit the loop when end of array has been reached
	mov r10, r12
	add r10, 3
	cmp r10, rdx
	jge end

	; Initialize xmm0 to 0
	xorps xmm0, xmm0

	; Perform calculations
	movsd xmm1, [rcx + (r12 - 3) * 8] ; Load num[i - 3] to xmm1
	addsd xmm0, xmm1 ; xmm0 = xmm0 + xmm1
	movsd xmm2, [rcx + (r12 - 2) * 8] ; Load num[i - 2] to xmm2
	addsd xmm0, xmm2 ; xmm0 = xmm0 + xmm2
	movsd xmm3, [rcx + (r12 - 1) * 8] ; Load num[i - 1] to xmm3
	addsd xmm0, xmm3 ; xmm0 = xmm0 + xmm3
	movsd xmm4, [rcx + r12 * 8] ; Load num[i] to xmm4
	addsd xmm0, xmm4 ; xmm0 = xmm0 + xmm4
	movsd xmm5, [rcx + (r12 + 1) * 8] ; Load num[i + 1] to xmm5
	addsd xmm0, xmm5 ; xmm0 = xmm0 + xmm5
	movsd xmm6, [rcx + (r12 + 2) * 8] ; Load num[i + 2] to xmm6
	addsd xmm0, xmm6 ; xmm0 = xmm0 + xmm6
	movsd xmm7, [rcx + (r12 + 3) * 8] ; Load num[i + 3] to xmm7
	addsd xmm0, xmm7 ; xmm0 = xmm0 + xmm7

	; Add sum to Y array
	movsd [r8 + r11 * 8], xmm0
	inc r11

next_iteration:
	inc r12
	jmp loop

end:
	ret