ENTRY(stage2)
OUTPUT_FORMAT("binary")
SECTIONS {
	. = 0x7c00;
	.text :
	{
		*(.stage2)
	}
	.text :
	{
		*(.modes)
	}
	.text :
	{
		*(.text)
	}
	.rodata :
	{
		*(.rodata)
	}
	.data :
	{
		*(.data)
	}
	.bss :
	{
		*(.bss)
	}
}
