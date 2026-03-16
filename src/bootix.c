#include "../inc/bootix.h"

void version(){
	puts("BOOTIX version " VERSION);
	puts("--- An experimental bootloader ---");
}


int boot_main(void){
	version();
	multiboot();
	while (true);			// delete me later
	return (0);
}
