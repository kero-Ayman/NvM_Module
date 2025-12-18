#include "Crc.h"
#include <stdint.h>
#include <stddef.h>

uint16 Crc_CalculateCRC16(const void *data, uint16 length, uint16 initValue) {
    (void)data; (void)length; (void)initValue;
    return 0xffff;
}

uint32 Crc_CalculateCRC32(const void *data, uint16 length, uint32 initValue) {
    (void)data; (void)length; (void)initValue;
    return 0xffffffffUL;
}
