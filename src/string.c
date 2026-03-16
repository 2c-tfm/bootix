#include "../inc/bootix.h"

void memcpy(void *dst, void *src, uint32_t n){
	if (dst == NULL || src == NULL)
		return ;
	uint32_t i = 0;
	while (i < n){
		*(uint8_t *)dst++ = *(uint8_t *)src++;
		i++;
	}
}

void memset(void *s, uint8_t c, uint32_t n){
	uint32_t i = 0;
	while(i < n){
		*(char *)s = c;
		i++;
	}

}
