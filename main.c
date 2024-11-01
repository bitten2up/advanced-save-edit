#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
//#include <endian.h>

#include "globals.h"

#define reverse_bytes_32(num) ( ((num & 0xFF000000) >> 24) | ((num & 0x00FF0000) >> 8) | ((num & 0x0000FF00) << 8) | ((num & 0x000000FF) << 24) )

#define UNLOCK_FLAG_CREAM       1 << 0
#define UNLOCK_FLAG_TAILS       1 << 1
#define UNLOCK_FLAG_KNUCKLES    1 << 2
#define UNLOCK_FLAG_AMY         1 << 3
#define UNLOCK_FLAG_BOSS_TA     1 << 4
#define UNLOCK_FLAG_SOUND_TEST  1 << 5

#define GAME_PLAY_OPTION_DIFFICULTY_EASY     1
#define GAME_PLAY_OPTION_TIME_LIMIT_DISABLED 2

#define PACKED_A_BUTTON 1
#define PACKED_B_BUTTON 2
#define PACKED_R_BUTTON 4

#define SECTOR_SECURITY_NUM    0x47544E4C
#define SECTOR_CHECKSUM_OFFSET 872
#define NUM_SAVE_SECTORS       16

#define CalcChecksum(save)                                                              \
    ({                                                                                  \
        u32 j, checksum = 0;                                                            \
        for (j = 0; j < SECTOR_CHECKSUM_OFFSET; j += sizeof(u32)) {                     \
            checksum += *(u32 *)((save) + j);                                           \
        }                                                                               \
        reverse_bytes_32(checksum);                                                     \
    })


int main(int argc, char* argv[])
{
    FILE* input = fopen("sa3.sav.bak", "rb");
    FILE* f1 = fopen("sa3.sav", "wb");

    fseek(input, 0L, SEEK_END);
    int inputsize = ftell(input);
    rewind(input);

    s16 sectorNum, i, successfulRead;

    i = 0;
    // Keep a copy of the last game state

    u32 maxVersion = 0, minVersion = 0xffffffff;
    s16 bestSector = 0;

    fseek(input, 4L, SEEK_CUR);
    u32 curSector;

    for (i = 0; i < NUM_SAVE_SECTORS; i++) {
        char dammit[4];
        fread(dammit, 4, 1, input);
        curSector = *(u32*)dammit;
        // If the value we just read was this
        if (curSector > maxVersion) {
            bestSector = i;
            maxVersion = curSector;
        }

        if (curSector < minVersion) {
            minVersion = curSector;
        }
        fseek(input, 4092L, SEEK_CUR);
    }

    if (minVersion > 0) {
        sectorNum = bestSector;
    }
    else
    {
        // if we found a min version number of 0
        // look through all the sectors for the highest
        // version number until we get to a version number
        // of <= 0xffff
        maxVersion = 0;
        for (i = 0; i < NUM_SAVE_SECTORS; i++) {
            if (maxVersion <= 0xFFFF && curSector > maxVersion) {
                sectorNum = i;
                maxVersion = curSector;
            }
        }
    }
    // newerish save file hasn't wrapped around yet
    if (maxVersion == ~0) {
	    rewind(input);
    	    fseek(input, 4L, SEEK_CUR);
	    minVersion = 0xffff0000;
	    for (i = 0; i < NUM_SAVE_SECTORS; i++) {
        	char dammit[4];
        	fread(dammit, 4, 1, input);
        	curSector = *(u32*)dammit;
        	if (minVersion >= 0xffff0000 && curSector < minVersion) {
            		bestSector = i;
	            	minVersion = curSector;
        	}
        	fseek(input, 4092L, SEEK_CUR);
	    }
	    if (minVersion == 0xffff0000) {
		    printf("ERROR: NO SUITABLE SECTORS FOUND, ARE YOU SURE THIS IS A SONIC ADVANCE 3 SAVE FILE?\n");
    	       	    printf("min version: %u\n", minVersion);
    		    printf("max version: %u\n", maxVersion);
    		    printf("best sector: %u\n", sectorNum);
		    exit(1);
	    }
    }

    printf("min version: %u\n", minVersion);
    printf("max version: %u\n", maxVersion);
    printf("best sector: %u\n", sectorNum);

    fseek(input, 4096*bestSector, SEEK_SET);
    
    union data
    {
        SaveSectorData saveFile;
        char buffer[4096];
    } save_u;

    if (1 != fread(save_u.buffer,4098, 1, input))
	{
		fclose(input);
		fputs("read failed, or file is blank\n", stderr);
        exit(1);
	}

    char test[4096];

    memcpy(test, save_u.buffer, 4096);

    //SaveSectorData *saveFile = (SaveSectorData *)buffer;

    printf("v3D was %b\n", save_u.saveFile.v3D);
    printf("v3D manual... %x\n", save_u.buffer[0x3D]);
    save_u.buffer[0x3D] |= UNLOCK_FLAG_TAILS;
    printf("Language is now %x\n", save_u.saveFile.v1C);

    for (i = 0; i<4096; i++)
    {
        //printf("0x%x: 0x%x\n", i, save_u.buffer[i]);
        if (save_u.buffer[i] != test[i])
        {
            printf("doesn't match @%x\n probally a good thing because it means it changed\n", i);
        }
    }

    u32 checksum = CalcChecksum(save_u.buffer);
    printf("Valid Checksum is: %x\n", checksum);
    save_u.buffer[SECTOR_CHECKSUM_OFFSET] = (checksum>>24) & 0xFF;
	save_u.buffer[SECTOR_CHECKSUM_OFFSET+1] = (checksum>>16) & 0xFF;
	save_u.buffer[SECTOR_CHECKSUM_OFFSET+2] = (checksum>>8) & 0xFF;
	save_u.buffer[SECTOR_CHECKSUM_OFFSET+3] = checksum & 0xFF;
    fseek(f1, 4096*bestSector, SEEK_SET);
    fwrite(save_u.buffer, sizeof(save_u.buffer), 1, f1);
    rewind(f1);
    rewind(input);


    for (i = 0; i < NUM_SAVE_SECTORS; i++)
    {

        if (i == bestSector) 
        {
            fseek(input, 4096, SEEK_CUR);
            fseek(f1, 4096, SEEK_CUR);
        }
        else
        {
            fread(save_u.buffer, sizeof(save_u.buffer), 1, input);
            fwrite(save_u.buffer, sizeof(save_u.buffer), 1, f1);
        }
    }
        

    fclose(input);
    fclose(f1);
    return 0;
}
