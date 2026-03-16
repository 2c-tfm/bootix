#include "../inc/bootix.h"

///////////////////////////  DBG  ///////////////////////////
#ifdef DBG
static void print_partition(partition_table *ptbl){
	puts("[PARTITION TABLE]");
	printf("\tboot_indicator %d\n", ptbl->boot_indicator);
	printf("\tstart_head %d\n", ptbl->start_head);
	printf("\tstart_sector %d\n", ptbl->start_sector);
	printf("\tstart_cylinder %d\n", ptbl->start_cylinder);
	printf("\tsys_id %d\n", ptbl->sys_id);
	printf("\tend_sector %d\n", ptbl->end_sector);
	printf("\tend_cylinder %d\n", ptbl->end_cylinder);
	printf("\tLBA %d\n", ptbl->lba);
	printf("\tsectors %d\n", ptbl->sectors);

}
#endif
///////////////////////////  DBG  ///////////////////////////



// init_partable - inits partition table
void init_partable(partition_table *ptbl, void *ptbl_addr){
	uint8_t *raw = (uint8_t*) ptbl_addr;
	ptbl->boot_indicator = raw[0];
	ptbl->start_head     = raw[1];
	ptbl->start_sector   = raw[2] & 0x3F;
	ptbl->start_cylinder = ((raw[2] & 0xC0) << 2) | raw[3];
	ptbl->sys_id	     = raw[4];
	ptbl->end_sector     = raw[5] & 0x3F;
	ptbl->end_cylinder   = ((raw[5] & 0xC0) << 2) | raw[6];
	ptbl->lba            = *(uint32_t*)(raw + 8);
	ptbl->sectors        = *(uint32_t*)(raw + 12);
}

void extended_parts(partition_table *ext, partition_table **parts, uint32_t it){

}

partition_table **detect_partitions(){
	// iterating over all the partition tables
	partition_table **parts = malloc(sizeof(partition_table) * 0x20);
	memset(parts, 0, sizeof(partition_table) * 0x20);


	int i = -1;
	while (++i < 4){
		parts[i] = malloc(sizeof(partition_table));
		init_partable(parts[i], (void *) PARTABLE_LOC + (16 * i));
		if (parts[i]->sys_id == 5){
			// handle extended partitions here
		}
#ifdef DBG
		print_partition(parts[i]);
#endif
	}

}

void multiboot(){
	partition_table **parts = detect_partitions();
	char buff[512];
	read_sector_lba(buff, 1, parts[0]->lba);
}
