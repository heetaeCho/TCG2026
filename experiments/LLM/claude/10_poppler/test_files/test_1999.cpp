#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Reproduce the JPXData structure as described in the dependencies
struct JPXData {
    const unsigned char *data;
    int size;
    int pos;
};

// We need to declare the callback with the same signature used in the implementation.
// Since it's a static function in the .cc file, we reproduce it here for testing purposes.
// This is the exact implementation from the source.
typedef int64_t OPJ_OFF_T;

static OPJ_OFF_T jpxSkip_callback(OPJ_OFF_T skip, void *p_user_data)
{
    auto *jpxData = (JPXData *)p_user_data;
    jpxData->pos += (skip > jpxData->size - jpxData->pos) ? jpxData->size - jpxData->pos : skip;
    /* Always return input value to avoid "Problem with skipping JPEG2000 box, stream error" */
    return skip;
}

class JPXSkipCallbackTest_1999 : public ::testing::Test {
protected:
    JPXData jpxData;
    unsigned char buffer[1024];

    void SetUp() override
    {
        memset(buffer, 0, sizeof(buffer));
        jpxData.data = buffer;
        jpxData.size = 1024;
        jpxData.pos = 0;
    }
};

// Test normal skip within bounds
TEST_F(JPXSkipCallbackTest_1999, NormalSkipWithinBounds_1999)
{
    jpxData.pos = 0;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(50, &jpxData);

    EXPECT_EQ(result, 50);
    EXPECT_EQ(jpxData.pos, 50);
}

// Test that skipping beyond the end clamps position to size
TEST_F(JPXSkipCallbackTest_1999, SkipBeyondEnd_1999)
{
    jpxData.pos = 90;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(50, &jpxData);

    EXPECT_EQ(result, 50); // Always returns input value
    EXPECT_EQ(jpxData.pos, 100); // Clamped to size
}

// Test skip of exactly remaining bytes
TEST_F(JPXSkipCallbackTest_1999, SkipExactlyRemaining_1999)
{
    jpxData.pos = 60;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(40, &jpxData);

    EXPECT_EQ(result, 40);
    EXPECT_EQ(jpxData.pos, 100);
}

// Test skip of zero bytes
TEST_F(JPXSkipCallbackTest_1999, SkipZeroBytes_1999)
{
    jpxData.pos = 50;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(0, &jpxData);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(jpxData.pos, 50);
}

// Test skip when already at the end
TEST_F(JPXSkipCallbackTest_1999, SkipWhenAtEnd_1999)
{
    jpxData.pos = 100;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(10, &jpxData);

    EXPECT_EQ(result, 10); // Always returns input
    EXPECT_EQ(jpxData.pos, 100); // Position stays at end
}

// Test skip of 1 byte (minimal non-zero skip)
TEST_F(JPXSkipCallbackTest_1999, SkipOneByte_1999)
{
    jpxData.pos = 0;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(1, &jpxData);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(jpxData.pos, 1);
}

// Test skip from position 0 with size 0
TEST_F(JPXSkipCallbackTest_1999, SkipWithZeroSizeStream_1999)
{
    jpxData.pos = 0;
    jpxData.size = 0;

    OPJ_OFF_T result = jpxSkip_callback(10, &jpxData);

    EXPECT_EQ(result, 10); // Always returns input
    EXPECT_EQ(jpxData.pos, 0); // Can't advance past size 0
}

// Test multiple sequential skips
TEST_F(JPXSkipCallbackTest_1999, MultipleSequentialSkips_1999)
{
    jpxData.pos = 0;
    jpxData.size = 100;

    jpxSkip_callback(20, &jpxData);
    EXPECT_EQ(jpxData.pos, 20);

    jpxSkip_callback(30, &jpxData);
    EXPECT_EQ(jpxData.pos, 50);

    jpxSkip_callback(60, &jpxData);
    EXPECT_EQ(jpxData.pos, 100); // Clamped
}

// Test return value is always the input skip value even when clamping occurs
TEST_F(JPXSkipCallbackTest_1999, ReturnValueAlwaysEqualsInput_1999)
{
    jpxData.pos = 99;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(1000, &jpxData);
    EXPECT_EQ(result, 1000);
}

// Test large skip value
TEST_F(JPXSkipCallbackTest_1999, LargeSkipValue_1999)
{
    jpxData.pos = 0;
    jpxData.size = 1024;

    OPJ_OFF_T largeSkip = 1000000;
    OPJ_OFF_T result = jpxSkip_callback(largeSkip, &jpxData);

    EXPECT_EQ(result, largeSkip);
    EXPECT_EQ(jpxData.pos, 1024); // Clamped to size
}

// Test skip with position at 1 less than size
TEST_F(JPXSkipCallbackTest_1999, SkipFromOneBeforeEnd_1999)
{
    jpxData.pos = 99;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(1, &jpxData);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(jpxData.pos, 100);
}

// Test skip exactly equal to size from position 0
TEST_F(JPXSkipCallbackTest_1999, SkipExactSize_1999)
{
    jpxData.pos = 0;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(100, &jpxData);

    EXPECT_EQ(result, 100);
    EXPECT_EQ(jpxData.pos, 100);
}

// Test skip larger than size from position 0
TEST_F(JPXSkipCallbackTest_1999, SkipLargerThanSize_1999)
{
    jpxData.pos = 0;
    jpxData.size = 100;

    OPJ_OFF_T result = jpxSkip_callback(200, &jpxData);

    EXPECT_EQ(result, 200);
    EXPECT_EQ(jpxData.pos, 100); // Clamped
}
