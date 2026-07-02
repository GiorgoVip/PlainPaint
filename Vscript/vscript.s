BITS 64

%include "./vscript/interface.s"

;global CreateVscript

default rel
section .text


global _chopTest

_chopTest:
push rdi

.count:
cmp [rdi], byte 0
je .end
inc rdi
jmp .count

.end:
mov rax, rdi
pop rdi
mov [rax-1], byte '!'
sub rax, rdi
ret



global _inter

_inter:

	
