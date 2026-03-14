#ifndef BOOTIX_H
#define BOOTIX_H

#include <stdint.h>
#include <stdbool.h>

#define SERIAL_PORT	0x3F8
#define NULL		0
#define VERSION		"0.1"

// some fmt macros
typedef char* va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap, last)  ( ap = (va_list)&(last) + _INTSIZEOF(last) )
#define va_arg(ap, type)    ( *(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)) )
#define va_end(ap)          ( (void)0 )

// other incs
#include "fat32.h"
#include "mbr.h"
#include "alloc.h"

// io.c
void putchar(char c);
void puts(const char* str);
void print(const char *str);
void read(char *buff, uint32_t len);

// fmt
void printf(char *fmt, ...);

// string functions
void memcpy(void *dst, void *src, uint32_t n);


#endif
