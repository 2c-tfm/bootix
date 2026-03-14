#ifndef FAT32_H
#define FAT32_H

typedef struct {
	uint8_t 	filename[11];
	uint8_t 	attr;           	// file attributes (fat32_dir_attr)
	uint8_t 	nt_reserved;    	// reserved for NT
	uint8_t 	creation_tenths; 	// creation time (tenths of sec)
	uint16_t	creation_time;   	// creation time
	uint16_t	creation_date;  	 // creation date
	uint16_t	access_date;     	// last access date
	uint16_t	first_cluster_hi;	// high 16 bits of first cluster
	uint16_t	write_time;		// last write time
	uint16_t	write_date;      	// last write date
	uint16_t	first_cluster_lo;	// low 16 bits of first cluster
	uint32_t	file_size;      	 // file size in bytes
} fat32_dir_entry;

typedef enum fat32_dir_attr {
	RD_ONLY	= (1 << 0),			// READ_ONLY lsb
	HIDDEN	= (1 << 1),			// hidden dir (should not show in dir listing)
	SYS	= (1 << 2),			// System directory
	VOLID	= (1 << 3),			// Volume ID
	SUBDIR	= (1 << 4),			// Subdirectory
	ARCHIVE	= (1 << 5),			// has changed since last backup
} fat32_dir_attr;

#endif
