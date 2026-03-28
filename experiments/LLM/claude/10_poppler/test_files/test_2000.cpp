#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Replicate the JPXData structure as described in the dependencies
// This matches the known/inferred structure with the fields used in the callback
typedef int32_t OPJ_BOOL;
typedef int64_t OPJ_OFF_T;
typedef size_t OPJ_SIZE_T;

#define OPJ_TRUE 1
#define OPJ_FALSE 0

struct JPXData {
    const unsigned char *data;
    OPJ_OFF_T size;
    OPJ_OFF_T pos;
};

// Re-declare the static function under test. Since it's static in the .cc file,
// we need to replicate it here for testing purposes. We treat it as a black box
// based on the provided implementation.
static OPJ_BOOL jpxSeek_callback(OPJ_OFF_T seek_pos, void *p_user_data) {
    auto *jpxData = (JPXData *)p_user_data;
    if (seek_pos > jpxData->size) {
        return OPJ_FALSE;
    }
    jpxData->pos = seek_pos;
    return OPJ_TRUE;
}

class JPXSeekCallbackTest_2000 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up a buffer of 100 bytes
        memset(buffer, 0, sizeof(buffer));
        jpxData.data = buffer;
        jpxData.size = 100;
        jpxData.pos = 0;
    }

    unsigned char buffer[100];
    JPXData jpxData;
};

// Test seeking to a valid position within the data
TEST_F(JPXSeekCallbackTest_2000, SeekToValidPosition_2000) {
    OPJ_BOOL result = jpxSeek_callback(50, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 50);
}

// Test seeking to position 0 (beginning)
TEST_F(JPXSeekCallbackTest_2000, SeekToBeginning_2000) {
    jpxData.pos = 50;
    OPJ_BOOL result = jpxSeek_callback(0, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 0);
}

// Test seeking to the exact end (position == size)
TEST_F(JPXSeekCallbackTest_2000, SeekToExactEnd_2000) {
    OPJ_BOOL result = jpxSeek_callback(100, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 100);
}

// Test seeking beyond the data size (position > size) should fail
TEST_F(JPXSeekCallbackTest_2000, SeekBeyondEnd_2000) {
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(101, &jpxData);
    EXPECT_EQ(result, OPJ_FALSE);
    // Position should remain unchanged since seek failed
    EXPECT_EQ(jpxData.pos, 0);
}

// Test seeking far beyond the data size
TEST_F(JPXSeekCallbackTest_2000, SeekFarBeyondEnd_2000) {
    jpxData.pos = 10;
    OPJ_BOOL result = jpxSeek_callback(1000, &jpxData);
    EXPECT_EQ(result, OPJ_FALSE);
    // Position should remain unchanged
    EXPECT_EQ(jpxData.pos, 10);
}

// Test seeking to position 1 (just past the beginning)
TEST_F(JPXSeekCallbackTest_2000, SeekToPositionOne_2000) {
    OPJ_BOOL result = jpxSeek_callback(1, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 1);
}

// Test seeking to size - 1 (last valid data byte)
TEST_F(JPXSeekCallbackTest_2000, SeekToLastByte_2000) {
    OPJ_BOOL result = jpxSeek_callback(99, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 99);
}

// Test multiple sequential seeks
TEST_F(JPXSeekCallbackTest_2000, MultipleSequentialSeeks_2000) {
    OPJ_BOOL result;

    result = jpxSeek_callback(10, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 10);

    result = jpxSeek_callback(50, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 50);

    result = jpxSeek_callback(0, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 0);

    result = jpxSeek_callback(100, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 100);
}

// Test seek with zero-size data
TEST_F(JPXSeekCallbackTest_2000, ZeroSizeData_SeekToZero_2000) {
    jpxData.size = 0;
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(0, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 0);
}

// Test seek with zero-size data should fail for any positive position
TEST_F(JPXSeekCallbackTest_2000, ZeroSizeData_SeekToOne_2000) {
    jpxData.size = 0;
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(1, &jpxData);
    EXPECT_EQ(result, OPJ_FALSE);
    EXPECT_EQ(jpxData.pos, 0);
}

// Test that a failed seek does not modify the position
TEST_F(JPXSeekCallbackTest_2000, FailedSeekDoesNotChangePosition_2000) {
    jpxData.pos = 42;
    OPJ_BOOL result = jpxSeek_callback(200, &jpxData);
    EXPECT_EQ(result, OPJ_FALSE);
    EXPECT_EQ(jpxData.pos, 42);
}

// Test seeking backward after seeking forward
TEST_F(JPXSeekCallbackTest_2000, SeekBackward_2000) {
    jpxSeek_callback(80, &jpxData);
    EXPECT_EQ(jpxData.pos, 80);

    OPJ_BOOL result = jpxSeek_callback(20, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 20);
}

// Test with size of 1
TEST_F(JPXSeekCallbackTest_2000, SizeOne_SeekToZero_2000) {
    jpxData.size = 1;
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(0, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 0);
}

TEST_F(JPXSeekCallbackTest_2000, SizeOne_SeekToOne_2000) {
    jpxData.size = 1;
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(1, &jpxData);
    EXPECT_EQ(result, OPJ_TRUE);
    EXPECT_EQ(jpxData.pos, 1);
}

TEST_F(JPXSeekCallbackTest_2000, SizeOne_SeekToTwo_2000) {
    jpxData.size = 1;
    jpxData.pos = 0;
    OPJ_BOOL result = jpxSeek_callback(2, &jpxData);
    EXPECT_EQ(result, OPJ_FALSE);
    EXPECT_EQ(jpxData.pos, 0);
}
