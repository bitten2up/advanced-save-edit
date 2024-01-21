#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "globals.h"

#define reverse_bytes_32(num) ( ((num & 0xFF000000) >> 24) | ((num & 0x00FF0000) >> 8) | ((num & 0x0000FF00) << 8) | ((num & 0x000000FF) << 24) )

#define CalcChecksum(save)                                                              \
    ({                                                                                  \
        u32 j, checksum = 0;                                                            \
        for (j = 0; j < SECTOR_CHECKSUM_OFFSET; j += sizeof(u32)) {                     \
            checksum += *(u32 *)((save) + j);                                           \
        }                                                                               \
        reverse_bytes_32(checksum);                                                     \
    })

#define SECTOR_SECURITY_NUM    0x4C45474
#define SECTOR_CHECKSUM_OFFSET 872
#define NUM_SAVE_SECTORS       10


int main(int argc, char* argv[])
{
    FILE* input = fopen("sa3.sav.bak", "r");

    fseek(input, 0L, SEEK_END);
    int inputsize = ftell(input);
    rewind(input);
    
    char* buffer = calloc(1, inputsize+1);

    if (buffer == NULL)
	{
		fclose(input);
		free(buffer);
		fputs("mem alloc failed\n", stderr);
		exit(1);
	}
    if (1 != fread(buffer,inputsize, 1, input))
	{
		fclose(input);
        free(buffer);
		fputs("read failed, or file is blank\n", stderr);
        exit(1);
	}
    fclose(input);
    u32 checksum = CalcChecksum(buffer);
    printf("Valid Checksum is: %x\n", checksum);
    buffer[SECTOR_CHECKSUM_OFFSET] = (checksum>>24) & 0xFF;
	buffer[SECTOR_CHECKSUM_OFFSET+1] = (checksum>>16) & 0xFF;
	buffer[SECTOR_CHECKSUM_OFFSET+2] = (checksum>>8) & 0xFF;
	buffer[SECTOR_CHECKSUM_OFFSET+3] = checksum & 0xFF;
    FILE* f1 = fopen("sa3.sav", "wb");
    fwrite(buffer, sizeof(char), inputsize, f1);
    fclose(f1);
    free(buffer);
    buffer = NULL;
    return 0;
}
