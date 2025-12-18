/* Simple test harness to exercise NvM module */
#include <stdio.h>
#include "Std_Types.h"
#include "NvM_Types.h"
#include "NvM.h"
#include "NvM_ConfigTypes.h"
//#include "MemIf.h"

int main(void) {
    NvM_RequestResultType status;

    printf("Starting NvM test\n");

    NvM_Init();
    //MemIf_Init();  /* Initialize MemIf stub storage */

    /* Trigger a ReadAll and process it */
    NvM_ReadAll();
    for (int i = 0; i < 20; i++) {
        NvM_MainFunction();
        (void)NvM_GetErrorStatus(0, &status);
        printf("ReadAll iteration %d: status=%u\n", i, status);
    }
    

    /* Trigger a WriteAll and process it */
    /* Write a pattern to blockId 2 (second block) */
    {
        NvM_BlockIdType bid = 2;
        uint8 testData[64];
        //read the block first
         Std_ReturnType rs = NvM_ReadBlock(bid, NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress);
        printf("NvM_ReadBlock returned %u\n", rs);

        for (int i = 0; i < 20; i++) {
            NvM_MainFunction();
            (void)NvM_GetErrorStatus(0, &status);
            printf("Read iteration %d: status=%u\n", i, status);
        }
        /* Verify RAM content */
        printf("Verifying read data for block %u:\n", bid);
        for (int i = 0; i < 64; i++) {
            printf("%02X ", NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress[i]);
            if ((i & 15) == 15) printf("\n");
        }
        printf("\n");

        for (int i = 0; i < 64; i++) testData[i] = 0xAA;

        printf("Requesting write of block %u\n", bid);
        Std_ReturnType wr = NvM_WriteBlock(bid, testData);
        printf("NvM_WriteBlock returned %u\n", wr);

        for (int i = 0; i < 20; i++) {
            NvM_MainFunction();
            (void)NvM_GetErrorStatus(0, &status);
            printf("WriteAll iteration %d: status=%u\n", i, status);
        }

        

        /* Zero RAM buffer then request read */
        printf("Zeroing RAM buffer and requesting read of block %u\n", bid);
        /* The RAM buffer is the configured RamBlockDataAddress; clear it */
        for (int i = 0; i < 64; i++) NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress[i] = 0;

        printf("Ram after zeroing\n");
        for (int i = 0; i < 64; i++) {
            printf("%02X ", NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress[i]);
            if ((i & 15) == 15) printf("\n");
        }
        printf("\n");

        Std_ReturnType rr = NvM_ReadBlock(bid, NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress);
        printf("NvM_ReadBlock returned %u\n", rr);

        for (int i = 0; i < 20; i++) {
            NvM_MainFunction();
            (void)NvM_GetErrorStatus(0, &status);
            printf("Read iteration %d: status=%u\n", i, status);
        }

        /* Verify RAM content */
        printf("Verifying read data for block %u:\n", bid);
        for (int i = 0; i < 64; i++) {
            printf("%02X ", NvM_Config.BlockDescriptor[bid-1].RamBlockDataAddress[i]);
            if ((i & 15) == 15) printf("\n");
        }
        printf("\n");
    }

    printf("NvM test finished\n");
    return 0;
}
