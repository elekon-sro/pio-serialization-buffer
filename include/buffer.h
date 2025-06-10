#ifndef BUFFER_H
#define BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct _buffer {
    union {
        uint8_t * data;
        char * sdata;
    };
    size_t size;
    size_t written;
};
typedef struct _buffer Buffer;

struct _constBuffer {
    union {
        const uint8_t * data;
        const char * sdata;
    };
    size_t size;
    size_t read;
};
typedef struct _constBuffer ConstBuffer;

/**
 * @brief Allocate Buffer internal data
 *
 * @param size
 * @return Buffer
 */
Buffer Buffer_AllocData(size_t size);

/**
 * @brief Free Buffer internal data
 *
 * @param buff
 */
void Buffer_FreeData(Buffer * buff);

/**
 * Buffer_WriteAvailable
 * @param buff
 * @return the number of bytes which can be written to buffer
 */
size_t Buffer_WriteAvailable(Buffer * buff);

/**
 * @brief Write uint64 to the buffer
 *
 * @param buff
 * @param val
 */
void Buffer_WriteU64(Buffer * buff, uint64_t val);

/**
 * @brief Write uint32 to the buffer
 *
 * @param buff
 * @param val
 */
void Buffer_WriteU32(Buffer * buff, uint32_t val);

/**
 * Buffer_WriteU16
 * before calling, it is necessary to check the number of available bytes in the buffer
 * @param buff
 * @param writing value
 */
void Buffer_WriteU16(Buffer * buff, uint16_t val);

/**
 * @brief Write uint8 to the buffer
 *
 * @param buffer
 * @param val
 */
void Buffer_WriteU8(Buffer * buffer, uint8_t val);

/**
 * @brief Write int64 to the buffer
 *
 * @param buff
 * @param val
 */
void Buffer_WriteS64(Buffer * buff, int64_t val);

/**
 * @brief Write uint32 to the buffer
 *
 * @param buff
 * @param val
 */
void Buffer_WriteS32(Buffer * buff, int32_t val);

/**
 * @brief Write int16 to the buffer
 *
 * @param buff
 * @param val
 */
void Buffer_WriteS16(Buffer * buff, int16_t val);

/**
 * @brief Write int8 to the buffer
 *
 * @param buffer
 * @param val
 */
void Buffer_WriteS8(Buffer * buffer, int8_t val);

/**
 * @brief Write string to the buffer
 *
 * @param buff
 * @param data
 * @param dataSize
 */
void Buffer_WriteStr(Buffer * buff, const char * data, size_t dataSize);

/**
 * Write multiple data to the buffer
 *
 * @param buff
 * @param data
 * @param dataSize
 */
void Buffer_Write(Buffer * buff, const void * data, size_t dataSize);

/**
 * @brief Clear written data in the buffer
 *
 * @param buff
 */
void Buffer_Clear(Buffer * buff);

/**
 * @brief Move data in the buffer by offset
 *
 * Effectively discadring first bytes up to the offset and copying the rest of written data
 * at the beggining of the buffer. Size of the buffer will be the same but written bytes will
 * decrese by offset.
 * @param buff
 * @param offset
 */
void Buffer_MoveBy(Buffer * buff, size_t offset);

/**
 * Buffer_ReadAvailable
 * @param buff
 * @return the number of bytes which can be read from buffer
 */
size_t Buffer_ReadAvailable(ConstBuffer * buff);

/**
 * @brief Read uint64 from the buffer
 *
 * @param buff
 * @return uint64_t
 */
uint64_t Buffer_ReadU64(ConstBuffer * buff);

/**
* Buffer_ReadU32
* before calling, it is necessary to check the number of available bytes in the buffer
* @param buff
* @return read value
 */
uint32_t Buffer_ReadU32(ConstBuffer * buff);

/**
 * Buffer_ReadU16
 * before calling, it is necessary to check the number of available bytes in the buffer
 * @param buff
 * @return read value
 */
uint16_t Buffer_ReadU16(ConstBuffer * buff);

/**
* Buffer_ReadU8
* before calling, it is necessary to check the number of available bytes in the buffer
* @param buff
* @return read value
 */
uint8_t Buffer_ReadU8(ConstBuffer * buff);

/**
 * @brief Read int64 from the buffer
 *
 * @param buff
 * @return uint64_t
 */
int64_t Buffer_ReadS64(ConstBuffer * buff);

/**
 * @brief Read int32 from the buffer
 *
 * @param buff
 * @return uint64_t
 */
int32_t Buffer_ReadS32(ConstBuffer * buff);

/**
 * @brief Read int16 from the buffer
 *
 * @param buff
 * @return uint64_t
 */
int16_t Buffer_ReadS16(ConstBuffer * buff);

/**
 * @brief Read int8 from the buffer
 *
 * @param buff
 * @return uint64_t
 */
int8_t Buffer_ReadS8(ConstBuffer * buff);

/**
 * Buffer_Read
 * read remaining data from source buffer to destination pointer
 * @param source
 * @param destination
 * @param destinationSize
 * @return
 */
bool Buffer_Read(ConstBuffer * source, void * destination, size_t destinationSize);

/**
 * @brief Write formated data to the buffer
 *
 * @param buff
 * @param format
 * @param ...
 * @return written value
 * @see printf
 */
size_t Buffer_Format(Buffer * buff, const char * format, ...);

#ifdef __cplusplus
}
#endif

#endif /* BUFFER_H */
