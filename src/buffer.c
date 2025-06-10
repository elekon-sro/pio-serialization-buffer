// SPDX-License-Identifier: MIT
// Author: ELEKON, s.r.o., Vyškov

#include "buffer.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "serde.h"

Buffer Buffer_AllocData(size_t size)
{
    Buffer result = {
            .data = malloc(size),
            .size = size,
    };
    return result;
}

void Buffer_FreeData(Buffer * buff)
{
    free(buff->data);
    buff->data = NULL;
    buff->size = 0;
}

size_t Buffer_WriteAvailable(Buffer * buff)
{
    if (buff->size >= buff->written)
        return buff->size - buff->written;

    return 0;
}

void Buffer_WriteU64(Buffer * buff, uint64_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_UInt64ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteU32(Buffer * buff, uint32_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_UInt32ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteU16(Buffer * buff, uint16_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_UInt16ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteU8(Buffer * buff, uint8_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    buff->data[buff->written] = val;
    buff->written += sizeof(val);
}

void Buffer_WriteS64(Buffer * buff, int64_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_Int64ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteS32(Buffer * buff, int32_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_Int32ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteS16(Buffer * buff, int16_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    Serde_BE_Int16ToBytes(buff->data + buff->written, val);
    buff->written += sizeof(val);
}

void Buffer_WriteS8(Buffer * buff, int8_t val)
{
    if (buff->written + sizeof(val) > buff->size) {
        return;
    }

    buff->data[buff->written] = (uint8_t)val;
    buff->written += sizeof(val);
}

void Buffer_WriteStr(Buffer * buff, const char * data, size_t dataSize)
{
    if (buff->written + dataSize > buff->size) {
        return;
    }
    strncpy(buff->sdata + buff->written, data, dataSize);
    buff->written += dataSize;
}

void Buffer_Write(Buffer * buff, const void * data, size_t dataSize)
{
    if (buff->written + dataSize > buff->size) {
        return;
    }
    memcpy(buff->data + buff->written, data, dataSize);
    buff->written += dataSize;
}

void Buffer_Clear(Buffer * buff)
{
    buff->written = 0;
}

void Buffer_MoveBy(Buffer * buff, size_t offset)
{
    if (offset > buff->written) {
        offset = buff->written;
    }

    memmove(buff->data, buff->data + offset, buff->written - offset);
    buff->written -= offset;
}

size_t Buffer_ReadAvailable(ConstBuffer * buff)
{
    if (buff->size >= buff->read)
        return buff->size - buff->read;

    return 0;
}

uint64_t Buffer_ReadU64(ConstBuffer * buff)
{
    uint64_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToUInt64(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

uint32_t Buffer_ReadU32(ConstBuffer * buff)
{
    uint32_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToUInt32(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

uint16_t Buffer_ReadU16(ConstBuffer * buff)
{
    uint16_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToUInt16(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

uint8_t Buffer_ReadU8(ConstBuffer * buff)
{
    uint8_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = buff->data[buff->read];
    buff->read += sizeof(res);
    return res;
}

int64_t Buffer_ReadS64(ConstBuffer * buff)
{
    int64_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToInt64(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

int32_t Buffer_ReadS32(ConstBuffer * buff)
{
    int32_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToInt32(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

int16_t Buffer_ReadS16(ConstBuffer * buff)
{
    int16_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = Serde_BE_BytesToInt16(buff->data + buff->read);
    buff->read += sizeof(res);
    return res;
}

int8_t Buffer_ReadS8(ConstBuffer * buff)
{
    int8_t res = 0;

    if (buff->read + sizeof(res) > buff->size) {
        return 0;
    }
    res = (int8_t)buff->data[buff->read];
    buff->read += sizeof(res);
    return res;
}

bool Buffer_Read(ConstBuffer * source, void * destination, size_t destinationSize)
{
    if (source->read + destinationSize > source->size) {
        return 0;
    }
    memcpy(destination, source->data + source->read, destinationSize);
    source->read += destinationSize;
    return true;
}

size_t Buffer_Format(Buffer * buff, const char * format, ...)
{
    size_t result;
    va_list args;

    va_start(args, format);
    result = vsnprintf(buff->sdata + buff->written, buff->size - buff->written, format, args);
    va_end(args);

    buff->written += result;

    return result;
}
