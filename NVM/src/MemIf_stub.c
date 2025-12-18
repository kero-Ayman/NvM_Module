#include "MemIf.h"
#include "Std_Types.h"
#include <string.h>

/* Simple in-memory storage to simulate persistent NV blocks. */
#define MEMIF_MAX_BLOCKS 256
#define MEMIF_MAX_BLOCK_LEN  520
//virtual nvram size: 256 blocks of 512 bytes + 8 bytes CRc
static uint8 memif_storage[MEMIF_MAX_BLOCKS][MEMIF_MAX_BLOCK_LEN];
// use this load the storage with test data
void MemIf_Init(void)
{
    /* Pretend Flash already contains data */
    for (int i = 0; i < MEMIF_MAX_BLOCK_LEN; i++) {
        memif_storage[2][i] = 0x66;  /* Block 2 starts with 0x55 */
    }
}


Std_ReturnType MemIf_Read(uint8 deviceId,
                          uint16 block,
                          uint16 offset,
                          uint8* data,
                          uint16 length)
{
    (void)deviceId;
    if (block >= MEMIF_MAX_BLOCKS) return E_NOT_OK;
    if ((uint32)offset + (uint32)length > MEMIF_MAX_BLOCK_LEN) return E_NOT_OK;
    memcpy(data, &memif_storage[block][offset], length);
    return E_OK;
}

Std_ReturnType MemIf_Write(uint8 deviceId,
                           uint16 block,
                           const uint8* data)
{
    (void)deviceId;
    if (block >= MEMIF_MAX_BLOCKS) return E_NOT_OK;
    /* Copy up to max len from provided pointer; caller is expected to provide full block+crc */
    memcpy(memif_storage[block], data, MEMIF_MAX_BLOCK_LEN);
    return E_OK;
}

MemIf_StatusType MemIf_GetStatus(uint8 deviceId)
{
    (void)deviceId;
    return MEMIF_IDLE;
}

MemIf_JobResultType MemIf_GetJobResult(uint8 deviceId)
{
    (void)deviceId;
    return MEMIF_JOB_OK;
}

Std_ReturnType MemIf_InvalidateBlock(uint8 deviceId, uint16 block)
{
    (void)deviceId;
    (void)block;
    return E_OK;
}
