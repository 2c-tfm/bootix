bits 16;
section .stage2;
global stage2;

stage2:
	mov si, hello_entry;		;; switching to protected mode
	call prstr;
	jmp $;


prstr:
	lodsb;
	or al, al;
	jz done;
	mov ah, 0xe;		interrupt
	mov bh, 0x0;
	int 0x10;
	jmp prstr;

done:
	ret;

hello_entry		db "Stage 2 loaded", 0xd, 0xa, 0;

section .modes
bits 16;
real_to_prot:
	ret;

bits 32;
prot_to_real:
	ret;


