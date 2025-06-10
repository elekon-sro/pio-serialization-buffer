// SPDX-License-Identifier: MIT
// Author: ELEKON, s.r.o., Vyškov

#include "unity.h"

#include <string.h>

#include "buffer.h"

void test_Buffer_AllocData_FreeData(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(4);
    TEST_ASSERT_NOT_NULL(buffer.data);
    TEST_ASSERT_EQUAL(4, buffer.size);

    Buffer_FreeData(&buffer);
    TEST_ASSERT_NULL(buffer.data);
    TEST_ASSERT_EQUAL(0, buffer.size);
}

void test_Buffer_WriteAvailable(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(6);
    TEST_ASSERT_EQUAL(6, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU16(&buffer, 0);
    TEST_ASSERT_EQUAL(4, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}

void test_Buffer_WriteU64(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(9);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteU64(&buffer, 0x1122334455667788ULL);

    TEST_ASSERT_EQUAL(0x11, buffer.data[0]);
    TEST_ASSERT_EQUAL(0x22, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x33, buffer.data[2]);
    TEST_ASSERT_EQUAL(0x44, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x55, buffer.data[4]);
    TEST_ASSERT_EQUAL(0x66, buffer.data[5]);
    TEST_ASSERT_EQUAL(0x77, buffer.data[6]);
    TEST_ASSERT_EQUAL(0x88, buffer.data[7]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[8]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU64(&buffer, 0xFFFFFFFFFFFFFFFFULL);
    TEST_ASSERT_EQUAL(0x88, buffer.data[7]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[8]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}

void test_Buffer_WriteU32(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(5);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteU32(&buffer, 0x11223344UL);

    TEST_ASSERT_EQUAL(0x11, buffer.data[0]);
    TEST_ASSERT_EQUAL(0x22, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x33, buffer.data[2]);
    TEST_ASSERT_EQUAL(0x44, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU32(&buffer, 0xFFFFFFFFUL);
    TEST_ASSERT_EQUAL(0x44, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}


void test_Buffer_WriteU16(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(3);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteU16(&buffer, 0x1122);

    TEST_ASSERT_EQUAL(0x11, buffer.data[0]);
    TEST_ASSERT_EQUAL(0x22, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[2]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU16(&buffer, 0xFFFF);
    TEST_ASSERT_EQUAL(0x22, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[2]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}

void test_Buffer_WriteU8(void)
{
    uint8_t data[3] = {0};

    Buffer buffer = {
        .data = data,
        .size = 2,
        .written = 0,
    };

    Buffer_WriteU8(&buffer, 0x11);

    TEST_ASSERT_EQUAL(0x11, data[0]);
    TEST_ASSERT_EQUAL(0x00, data[1]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU8(&buffer, 0x22);
    TEST_ASSERT_EQUAL(0x11, data[0]);
    TEST_ASSERT_EQUAL(0x22, data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0, Buffer_WriteAvailable(&buffer));

    Buffer_WriteU8(&buffer, 0xff);
    TEST_ASSERT_EQUAL(0x11, data[0]);
    TEST_ASSERT_EQUAL(0x22, data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0, Buffer_WriteAvailable(&buffer));
}

void test_Buffer_WriteS64(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(9);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteS64(&buffer, -0x1122334455667788LL);

    TEST_ASSERT_EQUAL(0xee, buffer.data[0]);
    TEST_ASSERT_EQUAL(0xdd, buffer.data[1]);
    TEST_ASSERT_EQUAL(0xcc, buffer.data[2]);
    TEST_ASSERT_EQUAL(0xbb, buffer.data[3]);
    TEST_ASSERT_EQUAL(0xaa, buffer.data[4]);
    TEST_ASSERT_EQUAL(0x99, buffer.data[5]);
    TEST_ASSERT_EQUAL(0x88, buffer.data[6]);
    TEST_ASSERT_EQUAL(0x78, buffer.data[7]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[8]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteS64(&buffer, -1LL);
    TEST_ASSERT_EQUAL(0x78, buffer.data[7]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[8]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}

void test_Buffer_WriteS32(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(5);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteS32(&buffer, -0x11223344L);

    TEST_ASSERT_EQUAL(0xee, buffer.data[0]);
    TEST_ASSERT_EQUAL(0xdd, buffer.data[1]);
    TEST_ASSERT_EQUAL(0xcc, buffer.data[2]);
    TEST_ASSERT_EQUAL(0xbc, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteS32(&buffer, -1L);
    TEST_ASSERT_EQUAL(0xbc, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}


void test_Buffer_WriteS16(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(3);
    memset(buffer.data, 0, buffer.size);

    Buffer_WriteS16(&buffer, -0x1122);

    TEST_ASSERT_EQUAL(0xee, buffer.data[0]);
    TEST_ASSERT_EQUAL(0xde, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[2]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteS16(&buffer, -1);
    TEST_ASSERT_EQUAL(0xde, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[2]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_FreeData(&buffer);
}

void test_Buffer_WriteS8(void)
{
    uint8_t data[3] = {0};

    Buffer buffer = {
        .data = data,
        .size = 2,
        .written = 0,
    };

    Buffer_WriteS8(&buffer, -0x11);

    TEST_ASSERT_EQUAL(0xef, data[0]);
    TEST_ASSERT_EQUAL(0x00, data[1]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteS8(&buffer, -0x22);
    TEST_ASSERT_EQUAL(0xef, data[0]);
    TEST_ASSERT_EQUAL(0xde, data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0, Buffer_WriteAvailable(&buffer));

    Buffer_WriteS8(&buffer, -1);
    TEST_ASSERT_EQUAL(0xef, data[0]);
    TEST_ASSERT_EQUAL(0xde, data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0, Buffer_WriteAvailable(&buffer));
}

void test_Buffer_WriteStr(void)
{
    uint8_t data[] = {1, 2, 3, 4, 5};

    Buffer buffer = {
        .data = data,
        .size = sizeof(data),
        .written = 0,
    };

    Buffer_WriteStr(&buffer, "ab", 4);
    TEST_ASSERT_EQUAL('a', data[0]);
    TEST_ASSERT_EQUAL('b', data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0x00, data[3]);
    TEST_ASSERT_EQUAL(0x5, data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_WriteStr(&buffer, "cd", 4);
    TEST_ASSERT_EQUAL('a', data[0]);
    TEST_ASSERT_EQUAL('b', data[1]);
    TEST_ASSERT_EQUAL(0x00, data[2]);
    TEST_ASSERT_EQUAL(0x00, data[3]);
    TEST_ASSERT_EQUAL(0x5, data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

}

void test_Buffer_Write(void)
{
    Buffer buffer;

    buffer = Buffer_AllocData(5);
    memset(buffer.data, 0, buffer.size);

    uint8_t data1[2] = {0xbb, 0x44};
    uint8_t data2[2] = {0xdd, 0x22};

    Buffer_Write(&buffer, data1, sizeof(data1));
    TEST_ASSERT_EQUAL(0xbb, buffer.data[0]);
    TEST_ASSERT_EQUAL(0x44, buffer.data[1]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[2]);
    TEST_ASSERT_EQUAL(3, Buffer_WriteAvailable(&buffer));

    Buffer_Write(&buffer, data2, sizeof(data2));
    TEST_ASSERT_EQUAL(0xbb, buffer.data[0]);
    TEST_ASSERT_EQUAL(0x44, buffer.data[1]);
    TEST_ASSERT_EQUAL(0xdd, buffer.data[2]);
    TEST_ASSERT_EQUAL(0x22, buffer.data[3]);
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));

    Buffer_Write(&buffer, data1, sizeof(data1));
    TEST_ASSERT_EQUAL(1, Buffer_WriteAvailable(&buffer));
    TEST_ASSERT_EQUAL(0x00, buffer.data[4]);

    Buffer_FreeData(&buffer);
}

void test_Buffer_Clear(void)
{
    char data[2];
    Buffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    Buffer_WriteU8(&buffer, 0xAA);
    TEST_ASSERT_EQUAL(1, buffer.written);
    TEST_ASSERT_EQUAL(sizeof(data), buffer.size);

    Buffer_Clear(&buffer);
    TEST_ASSERT_EQUAL(0, buffer.written);
    TEST_ASSERT_EQUAL(sizeof(data), buffer.size);
}

void test_Buffer_MoveBy(void)
{
    char data[16] = "abcdefgh";
    Buffer buffer = {
            .sdata = data,
            .size = sizeof(data),
            .written = strlen(data),
    };

    TEST_ASSERT_EQUAL(8, buffer.written);

    Buffer_MoveBy(&buffer, 3);
    TEST_ASSERT_EQUAL(5, buffer.written);
    TEST_ASSERT_EQUAL(sizeof(data), buffer.size);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("defgh", buffer.sdata, 5);
    TEST_ASSERT_EQUAL(buffer.sdata, data); // check, that pointer to the original buffer don't move, just data
}

void test_Buffer_ReadAvailable(void)
{
    const char data[] = "abcdef";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };
    TEST_ASSERT_EQUAL(7, Buffer_ReadAvailable(&buffer));

    Buffer_ReadU16(&buffer);
    TEST_ASSERT_EQUAL(5, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadU64(void)
{
    const char data[] = "abcdefgh01234567";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL_UINT64(0x6162636465666768ULL, Buffer_ReadU64(&buffer));
    TEST_ASSERT_EQUAL(9, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT64(0x3031323334353637ULL, Buffer_ReadU64(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT64(0x0000000000000000ULL, Buffer_ReadU64(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadU32(void)
{
    const char data[] = "abcdefgh";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL_UINT32(0x61626364, Buffer_ReadU32(&buffer));
    TEST_ASSERT_EQUAL(5, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT32(0x65666768, Buffer_ReadU32(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT32(0x00000000, Buffer_ReadU32(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadU16(void)
{
    const char data[] = "abcd";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL_UINT16(0x6162, Buffer_ReadU16(&buffer));
    TEST_ASSERT_EQUAL(3, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT16(0x6364, Buffer_ReadU16(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT16(0x0000, Buffer_ReadU16(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadU8(void)
{
    const char data[] = "abcd";
    ConstBuffer buffer = {
            .sdata = data,
            .size = 2,
    };

    TEST_ASSERT_EQUAL_UINT8(0x61, Buffer_ReadU8(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT8(0x62, Buffer_ReadU8(&buffer));
    TEST_ASSERT_EQUAL(0, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_UINT8(0x00, Buffer_ReadU8(&buffer));
    TEST_ASSERT_EQUAL(0, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadS64(void)
{
    const char data[] = "\xff" "bcdefgh01234567";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL_INT64(-44363763471194264ll, Buffer_ReadS64(&buffer));
    TEST_ASSERT_EQUAL(9, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_INT64(0x3031323334353637LL, Buffer_ReadS64(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL_INT64(0x0000000000000000LL, Buffer_ReadS64(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadS32(void)
{
    const char data[] = "\xff" "bcdefgh";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL(-10329244, Buffer_ReadS32(&buffer));
    TEST_ASSERT_EQUAL(5, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x65666768, Buffer_ReadS32(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x00000000, Buffer_ReadS32(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadS16(void)
{
    const char data[] = "\xff" "bcd";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    TEST_ASSERT_EQUAL(-158, Buffer_ReadS16(&buffer));
    TEST_ASSERT_EQUAL(3, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x6364, Buffer_ReadS16(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x00000000, Buffer_ReadS16(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_ReadS8(void)
{
    const char data[] = "\xff" "bcd";
    ConstBuffer buffer = {
            .sdata = data,
            .size = 2,
    };

    TEST_ASSERT_EQUAL(-1, Buffer_ReadS8(&buffer));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x62, Buffer_ReadS8(&buffer));
    TEST_ASSERT_EQUAL(0, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_EQUAL(0x00, Buffer_ReadS8(&buffer));
    TEST_ASSERT_EQUAL(0, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_Read(void)
{
    const char data[] = "abcd";
    ConstBuffer buffer = {
            .sdata = data,
            .size = sizeof(data),
    };

    char dest[4];

    TEST_ASSERT_TRUE(Buffer_Read(&buffer, dest, sizeof(dest)));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(data, dest, sizeof(dest));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));

    TEST_ASSERT_FALSE(Buffer_Read(&buffer, dest, sizeof(dest)));
    TEST_ASSERT_EQUAL(1, Buffer_ReadAvailable(&buffer));
}

void test_Buffer_Format(void)
{
    char data[16];

    memset(data, 0, sizeof(data));

    Buffer buffer = {
            .sdata = data,
            .size = 10,
    };

    TEST_ASSERT_EQUAL(4, Buffer_Format(&buffer, "%d", 1234));
    TEST_ASSERT_EQUAL_CHAR_ARRAY("1234", buffer.sdata, 4);

    TEST_ASSERT_EQUAL(4, Buffer_Format(&buffer, "%d", 5678));
    TEST_ASSERT_EQUAL_CHAR_ARRAY("12345678", buffer.sdata, 8);

    TEST_ASSERT_EQUAL(4, Buffer_Format(&buffer, "%d", 9012));
    TEST_ASSERT_EQUAL_CHAR_ARRAY("123456789", buffer.sdata, 9);

    TEST_ASSERT_EQUAL(0, buffer.sdata[10]);
    TEST_ASSERT_EQUAL(0, buffer.sdata[11]);
}

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Buffer_AllocData_FreeData);

    RUN_TEST(test_Buffer_WriteAvailable);

    RUN_TEST(test_Buffer_WriteU64);
    RUN_TEST(test_Buffer_WriteU32);
    RUN_TEST(test_Buffer_WriteU16);
    RUN_TEST(test_Buffer_WriteU8);

    RUN_TEST(test_Buffer_WriteS64);
    RUN_TEST(test_Buffer_WriteS32);
    RUN_TEST(test_Buffer_WriteS16);
    RUN_TEST(test_Buffer_WriteS8);

    RUN_TEST(test_Buffer_WriteStr);

    RUN_TEST(test_Buffer_Write);
    RUN_TEST(test_Buffer_Clear);
    RUN_TEST(test_Buffer_MoveBy);

    RUN_TEST(test_Buffer_ReadAvailable);

    RUN_TEST(test_Buffer_ReadU64);
    RUN_TEST(test_Buffer_ReadU32);
    RUN_TEST(test_Buffer_ReadU16);
    RUN_TEST(test_Buffer_ReadU8);

    RUN_TEST(test_Buffer_ReadS64);
    RUN_TEST(test_Buffer_ReadS32);
    RUN_TEST(test_Buffer_ReadS16);
    RUN_TEST(test_Buffer_ReadS8);

    RUN_TEST(test_Buffer_Read);

    RUN_TEST(test_Buffer_Format);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
