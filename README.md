# Bootix

Bootix is a custom, experimental legacy multiboot bootloader built from the ground up to load multiple operating systems.

## How it Works

1. **Stage 1 (MBR)**: The BIOS loads the tiny 512-byte `boot.s` into memory and runs it. This code finds the FAT32 partition, searches for `STAGE2.BIN`, loads it into memory, and jumps to it.
2. **Stage 2 (Protected Mode)**: `entry.s` switches the CPU into 32-bit protected mode and hands control over to the C code (`bootix.c`).
3. **Configuration**: The bootloader parses the partition table (`mbr.c`), initializes a FAT32 driver (`fat32.c`), and reads the `btx.cnf` configuration file (`conf.c`) to figure out what operating system and kernel parameters the user wants.
4. **Loading Linux**: `kboot.c` reads the `vmlinuz` Linux kernel from the disk. It carefully parses the official Linux boot protocol, loads the real-mode setup code and the protected-mode kernel payload into memory, points the CPU payload to them, and makes the final jump to boot the OS.

## Codebase Breakdown

### Core Boot Sequence (`src/`)
* **`boot.s`**: The Stage 1 assembly code (Master Boot Record). It sets up the earliest environment, uses BIOS interrupts to read the hard drive, and loads Stage 2.
* **`entry.s`**: The bridge between assembly and C. It handles the complicated CPU transitions between 16-bit real mode and 32-bit protected mode.
* **`bootix.c`**: The main C entry point. It prints the welcome message and coordinates the sequence of finding partitions and booting the OS.
* **`kboot.c`**: The specialized Linux loader. It implements the standard Linux x86 boot protocol, setting up memory structures (like the zero page) and putting the kernel exactly where it expects to be in RAM before jumping to it.

### Filesystem & Disk (`src/`)
* **`mbr.c`**: Parses the disk's Master Boot Record to identify the layout of partitions and locate the active/bootable ones.
* **`fat32.c`**: A custom FAT32 driver. It traverses directories and clusters to find and read files (like the kernel or the config file) straight off the raw disk platter.
* **`int.c`**: Handles dropping temporarily back to real mode to ask the BIOS to read raw sectors from the hard drive (using Interrupt 0x13).

### Standard Library Replacements (`src/`)
Because a bootloader runs before the OS exists, we can't use standard libraries (like `<stdio.h>` or `<stdlib.h>`). Bootix implements its own mini-versions:
* **`alloc.c`**: A custom heap memory allocator (`malloc` and `free`) so the C code can dynamically request memory.
* **`fmt.c`**: A lightweight custom `printf` implementation for formatting text.
* **`string.c`**: Basic memory and string utilities (`memcpy`, `strcmp`, `strlen`, etc.).
* **`io.c`**: Low-level port communication, primarily used to output text over the serial port for debugging.
* **`log.c`**: A basic wrapper for printing debug, warning, and error messages.
* **`conf.c`**: A custom TOML-style parser built to read and understand the `btx.cnf` boot configuration file.

## Building and Testing

Add your own compiled `kernel`, `btx.cnf` and `initramfs` to `env/`  

`btx.cnf `example:  
```
[Linux]
	name = "Average Linux distro"
	kernel = vmlinuz
	# kernel = notlinux
	# kernel = wintoes
	boot_part = 0
	cmdline = "root=/dev/sda2 ro debug earlyprintk=serial,ttyS0,115200 console=tty0 console=ttyS0,115200"
```

Compiling the bootloader:
```bash
make clean
make build
make run
```
