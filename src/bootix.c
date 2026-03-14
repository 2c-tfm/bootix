#include "../inc/bootix.h"

void version(){
	puts("BOOTIX version " VERSION);
	puts("--- An experimental bootloader ---");
}

int boot_main(void){
	version();
	// char *chunka = malloc(0x20);
	// (void) chunka;
	// char *chunkb = malloc(0x20);
	// printf("fucking chunka: %p, chunkb: %p\n", chunka, chunkb);
	puts("fuck off\r\n");

	while (true);			// delete me later
	return (0);
}
