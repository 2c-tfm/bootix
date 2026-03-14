#ifndef MBR_H
#define MBR_H

#define PARTABLE_SIZE	16

typedef struct partition_table {
	uint8_t		boot_indicator;
	uint8_t		start_head;
	uint8_t		start_sector;
	uint16_t	start_cylinder;
	uint8_t		system_id;
	uint8_t		end_sector;
	uint16_t	end_cylinder;
	uint32_t	lba;
	uint32_t	sectors;
} partition_table;

#endif
