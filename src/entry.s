;; STAGE 2 of bootix

bits 16;
section .stage2;
global stage2;

stage2:
	call clear_screen;
	call real_to_prot;		;; switching to protected mode
	jmp $;

clear_screen:
	mov ah, 0x0;
	mov al, 0x03;
	int 0x10;
	ret;

section .modes
bits 16;

%define NULL_SEG 0
%define CODE_SEG 0x8
%define DATA_SEG 0x10

; real mode gdt
rgdt:
rgdt_code:
	dw 0xFFFF
	dw 0
	db 0
	db 0x9e
	db 0
	db 0

rgdt_data:
	dw 0xFFFF
	dw 0
	db 0
	db 0x92
	db 0
	db 0
rgdt_end:

rgdt_desc:
	dw rgdt_end-rgdt-1
	dd rgdt



; protected mode gdt
pgdt: 
pgdt_null:
	dq 0x0;
pgdt_code:
	dw 0x0ffff			;; segment limiter
	dw 0x0				;; base address
	db 0x0;				;; base address
	db 0b10011010;
	db 0b11001111;
	db 0

pgdt_data:
	dw 0x0ffff			;; segment limiter
	dw 0x0				;; base address
	db 0x0
	db 0b10010010
	db 0b11001111
	db 0
pgdt_end:


pgdt_desc:
	dw pgdt_end-pgdt-1
	dd pgdt



real_to_prot:
	cli;				;; clearing interrupts
	xor ax, ax;			;; clearing ds since gdt descriptor must be in ds:gdt_desc
	mov ds, ax;
	lgdt [pgdt_desc];
	mov eax, cr0;			;; setting bit 0 in cr0 register
	or eax, 1;
	mov cr0, eax;
	mov ax, DATA_SEG
	jmp CODE_SEG:load_c
	ret;

load_asm:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	sti
	ret;

bits 32;

%define RCODE_SEG 0x18
%define RDATA_SEG 0x20

load_c:
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	esp,kernel_stack_top;
	pusha
	extern boot_main;
	call boot_main;
	popa
	jmp -2;

prot_to_real:
	cli;
	mov ax, RDATA_SEG;
	mov ds, ax;
	mov es, ax;
	mov ss, ax;
	mov sp, 0xFFFF
	lgdt [rgdt];
	mov eax, cr0
	and eax, 0xfffffffe
	mov cr0, eax;
	jmp 0:load_asm
	ret;


section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top:
