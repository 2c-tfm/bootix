#ifndef INT_H
#define INT_H

extern uint8_t boot_drive;

typedef struct bios_regs{
	uint16_t	eax;
	uint16_t	ebx;
	uint16_t	ecx;
	uint16_t	edx;
	uint16_t	esi;
	uint16_t	edi;
	uint16_t	intno;
}bios_regs;

typedef struct dap {
	uint8_t		size;
	uint8_t		reserv;
	uint16_t	count;
	uint16_t	offset;
	uint16_t	segment;
	uint32_t	lba_low;
	uint32_t	lba_high;

} dap;

void	read_sector_lba(char *buffer, uint16_t sectors, uint32_t lba);

#endif
