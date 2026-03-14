#include "../inc/bootix.h"

// init_partable - inits partition table
void init_partable(partition_table *ptbl, void *ptbl_addr){
	uint8_t *raw = (uint8_t*) ptbl_addr;
	ptbl->boot_indicator = raw[0];
	ptbl->start_head     = raw[1];
	ptbl->start_sector   = raw[2] & 0x3F;
	ptbl->start_cylinder = ((raw[2] & 0xC0) << 2) | raw[3];
	ptbl->system_id      = raw[4];
	ptbl->end_sector     = raw[5] & 0x3F;
	ptbl->end_cylinder   = ((raw[5] & 0xC0) << 2) | raw[6];
	ptbl->lba            = *(uint32_t*)(raw + 8);
	ptbl->sectors        = *(uint32_t*)(raw + 12);
}

void multiboot(){

}
