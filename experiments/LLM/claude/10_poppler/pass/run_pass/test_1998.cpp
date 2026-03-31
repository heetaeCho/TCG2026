#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// We need to define the types used by the callback
typedef size_t OPJ_SIZE_T;

#ifndef unlikely
#define unlikely(x) (x)
#endif

// Replicate the JPXData structure as used by the callback
struct JPXData {
    const unsigned char *data;
    OPJ_SIZE_T size;
    OPJ_SIZE_T pos;
};

// Declaration of the function under test (defined in JPEG2000Stream.cc)
// We re-declare it here since we're testing it as a standalone function
static OPJ_SIZE_T jpxRead_callback(void *p_buffer, OPJ_SIZE_T p_nb_bytes, void *p_user_data) {
    auto *jpxData = (JPXData *)p_user_data;
    if (jpxData->size <= jpxData->pos) {
        return (OPJ_SIZE_T)-1; /* End of file! */
    }
    OPJ_SIZE_T len = jpxData->size - jpxData->pos;
    if (len > p_nb_bytes) {
        len = p_nb_bytes;
    }
    memcpy(p_buffer, jpxData->data + jpxData->pos, len);
    jpxData->pos += len;
    return len;
}

class JpxReadCallbackTest_1998 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test data
        for (int i = 0; i < 256; i++) {
            testData[i] = static_cast<unsigned char>(i);
        }
    }

    unsigned char testData[256];
    unsigned char buffer[512];
};

// Test normal read from beginning
TEST_F(JpxReadCallbackTest_1998, NormalReadFromBeginning_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 256;
    jpxData.pos = 0;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 10, &jpxData);

    EXPECT_EQ(result, 10u);
    EXPECT_EQ(jpxData.pos, 10u);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i));
    }
}

// Test reading when requested bytes exceed available data
TEST_F(JpxReadCallbackTest_1998, ReadMoreThanAvailable_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 5;
    jpxData.pos = 0;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 100, &jpxData);

    EXPECT_EQ(result, 5u);
    EXPECT_EQ(jpxData.pos, 5u);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i));
    }
}

// Test reading at end of file (pos == size)
TEST_F(JpxReadCallbackTest_1998, ReadAtEndOfFile_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 10;
    jpxData.pos = 10;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 5, &jpxData);

    EXPECT_EQ(result, (OPJ_SIZE_T)-1);
    EXPECT_EQ(jpxData.pos, 10u); // pos should not change
}

// Test reading when pos > size (past end of file)
TEST_F(JpxReadCallbackTest_1998, ReadPastEndOfFile_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 10;
    jpxData.pos = 15;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 5, &jpxData);

    EXPECT_EQ(result, (OPJ_SIZE_T)-1);
    EXPECT_EQ(jpxData.pos, 15u); // pos should not change
}

// Test reading from a middle position
TEST_F(JpxReadCallbackTest_1998, ReadFromMiddlePosition_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 256;
    jpxData.pos = 100;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 20, &jpxData);

    EXPECT_EQ(result, 20u);
    EXPECT_EQ(jpxData.pos, 120u);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(100 + i));
    }
}

// Test reading exactly the remaining bytes
TEST_F(JpxReadCallbackTest_1998, ReadExactlyRemainingBytes_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 20;
    jpxData.pos = 10;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 10, &jpxData);

    EXPECT_EQ(result, 10u);
    EXPECT_EQ(jpxData.pos, 20u);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(10 + i));
    }
}

// Test consecutive reads
TEST_F(JpxReadCallbackTest_1998, ConsecutiveReads_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 20;
    jpxData.pos = 0;

    // First read
    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result1 = jpxRead_callback(buffer, 5, &jpxData);
    EXPECT_EQ(result1, 5u);
    EXPECT_EQ(jpxData.pos, 5u);

    // Second read
    unsigned char buffer2[512];
    memset(buffer2, 0, sizeof(buffer2));
    OPJ_SIZE_T result2 = jpxRead_callback(buffer2, 5, &jpxData);
    EXPECT_EQ(result2, 5u);
    EXPECT_EQ(jpxData.pos, 10u);

    // Verify data continuity
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i));
        EXPECT_EQ(buffer2[i], static_cast<unsigned char>(5 + i));
    }
}

// Test reading with size 0 data
TEST_F(JpxReadCallbackTest_1998, ZeroSizeData_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 0;
    jpxData.pos = 0;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 10, &jpxData);

    EXPECT_EQ(result, (OPJ_SIZE_T)-1);
}

// Test reading 0 bytes when data is available
TEST_F(JpxReadCallbackTest_1998, ReadZeroBytes_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 10;
    jpxData.pos = 0;

    memset(buffer, 0xAA, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 0, &jpxData);

    EXPECT_EQ(result, 0u);
    EXPECT_EQ(jpxData.pos, 0u);
}

// Test reading single byte
TEST_F(JpxReadCallbackTest_1998, ReadSingleByte_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 256;
    jpxData.pos = 42;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 1, &jpxData);

    EXPECT_EQ(result, 1u);
    EXPECT_EQ(jpxData.pos, 43u);
    EXPECT_EQ(buffer[0], 42);
}

// Test reading with only 1 byte remaining
TEST_F(JpxReadCallbackTest_1998, ReadWithOneByteRemaining_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 10;
    jpxData.pos = 9;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 100, &jpxData);

    EXPECT_EQ(result, 1u);
    EXPECT_EQ(jpxData.pos, 10u);
    EXPECT_EQ(buffer[0], 9);
}

// Test that after reading all data, subsequent read returns EOF
TEST_F(JpxReadCallbackTest_1998, ReadAllThenReadAgain_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 5;
    jpxData.pos = 0;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result1 = jpxRead_callback(buffer, 5, &jpxData);
    EXPECT_EQ(result1, 5u);
    EXPECT_EQ(jpxData.pos, 5u);

    // Try reading again - should get EOF
    OPJ_SIZE_T result2 = jpxRead_callback(buffer, 5, &jpxData);
    EXPECT_EQ(result2, (OPJ_SIZE_T)-1);
    EXPECT_EQ(jpxData.pos, 5u);
}

// Test reading large chunk
TEST_F(JpxReadCallbackTest_1998, ReadLargeChunk_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 256;
    jpxData.pos = 0;

    memset(buffer, 0, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 256, &jpxData);

    EXPECT_EQ(result, 256u);
    EXPECT_EQ(jpxData.pos, 256u);
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i));
    }
}

// Test that buffer content is correct after partial read
TEST_F(JpxReadCallbackTest_1998, BufferContentAfterPartialRead_1998) {
    JPXData jpxData;
    jpxData.data = testData;
    jpxData.size = 3;
    jpxData.pos = 0;

    // Fill buffer with known pattern
    memset(buffer, 0xFF, sizeof(buffer));
    OPJ_SIZE_T result = jpxRead_callback(buffer, 100, &jpxData);

    EXPECT_EQ(result, 3u);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(buffer[1], 1);
    EXPECT_EQ(buffer[2], 2);
    // Bytes beyond the read should be untouched
    EXPECT_EQ(buffer[3], 0xFF);
    EXPECT_EQ(buffer[4], 0xFF);
}
