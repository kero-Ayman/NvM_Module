#ifndef MEMIF_H
#define MEMIF_H

#include "Std_Types.h"

/* MemIf status */
typedef enum {
    MEMIF_IDLE,
    MEMIF_BUSY
} MemIf_StatusType;

/* MemIf job result */
typedef enum {
    MEMIF_JOB_OK,
    MEMIF_JOB_FAILED,
    MEMIF_JOB_PENDING
} MemIf_JobResultType;

/* Additional job result codes used by NvM logic */
#define MEMIF_BLOCK_INVALID     0x10
#define MEMIF_BLOCK_INCONSISTENT 0x11
//use this to load the storage with test data
void MemIf_Init(void);

/* Function prototypes */
Std_ReturnType MemIf_Read(uint8 deviceId,
                          uint16 block,
                          uint16 offset,
                          uint8* data,
                          uint16 length);

Std_ReturnType MemIf_Write(uint8 deviceId,
                           uint16 block,
                           const uint8* data);

MemIf_StatusType MemIf_GetStatus(uint8 deviceId);
MemIf_JobResultType MemIf_GetJobResult(uint8 deviceId);
/* Invalidate a logical block (optional MemIf extension used by NvM) */
Std_ReturnType MemIf_InvalidateBlock(uint8 deviceId, uint16 block);

#endif
