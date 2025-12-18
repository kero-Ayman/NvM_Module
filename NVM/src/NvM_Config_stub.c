#include "NvM_ConfigTypes.h"

/* Minimal RAM for blocks */
static uint8 ram_block0[64];
static uint8 ram_block1[64];

static const NvM_BlockDescriptorType blockDescriptors[] = {
    {
        .NvramBlockIdentifier = 0,
        .BlockManagementType = NVM_BLOCK_NATIVE,
        .BlockJobPriority = 0,
        .BlockWriteProt = FALSE,
        .WriteBlockOnce = FALSE,
        .SelectBlockForReadall = TRUE,
        .ResistantToChangesSw = FALSE,
        .SingleBlockCallback = NULL,
        .NvBlockLength = sizeof(ram_block0),
        .BlockUseCrc = FALSE,
        .BlockCRCType = NVM_CRC16,
        .RamBlockDataAddress = ram_block0,
        .CalcRamBlockCrc = FALSE,
        .NvBlockNum = 1,
        .NvramDeviceId = 0,
        .NvBlockBaseNumber = 1,
        .RomBlockNum = 0,
        .RomBlockDataAdress = NULL,
        .InitBlockCallback = NULL
    },
    {
        .NvramBlockIdentifier = 1,
        .BlockManagementType = NVM_BLOCK_NATIVE,
        .BlockJobPriority = 0,
        .BlockWriteProt = FALSE,
        .WriteBlockOnce = FALSE,
        .SelectBlockForReadall = TRUE,
        .ResistantToChangesSw = FALSE,
        .SingleBlockCallback = NULL,
        .NvBlockLength = sizeof(ram_block1),
        .BlockUseCrc = FALSE,
        .BlockCRCType = NVM_CRC16,
        .RamBlockDataAddress = ram_block1,
        .CalcRamBlockCrc = FALSE,
        .NvBlockNum = 1,
        .NvramDeviceId = 0,
        .NvBlockBaseNumber = 2,
        .RomBlockNum = 0,
        .RomBlockDataAdress = NULL,
        .InitBlockCallback = NULL
    }
};

const NvM_ConfigType NvM_Config = {
    .Common = { .MultiBlockCallback = NULL },
    .BlockDescriptor = blockDescriptors
};
