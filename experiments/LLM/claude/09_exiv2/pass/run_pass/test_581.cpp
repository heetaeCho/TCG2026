#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>

using namespace Exiv2;

class MemIoSeekTest_581 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test seeking from beginning with offset 0 on empty MemIo
TEST_F(MemIoSeekTest_581, SeekBegZeroOnEmpty_581) {
    MemIo memIo;
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());
}

// Test seeking from beginning with offset 0 on non-empty MemIo
TEST_F(MemIoSeekTest_581, SeekBegZeroOnNonEmpty_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());
}

// Test seeking from beginning to a valid position
TEST_F(MemIoSeekTest_581, SeekBegValidOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3u, memIo.tell());
}

// Test seeking from beginning to the end of data (exact size)
TEST_F(MemIoSeekTest_581, SeekBegToExactEnd_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(5, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(5u, memIo.tell());
}

// Test seeking from beginning past the end of data
TEST_F(MemIoSeekTest_581, SeekBegPastEnd_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(6, BasicIo::beg);
    EXPECT_EQ(1, result);
    EXPECT_TRUE(memIo.eof());
}

// Test seeking from beginning with negative offset
TEST_F(MemIoSeekTest_581, SeekBegNegativeOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_EQ(1, result);
}

// Test seeking from current position forward
TEST_F(MemIoSeekTest_581, SeekCurForward_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3u, memIo.tell());
}

// Test seeking from current position backward
TEST_F(MemIoSeekTest_581, SeekCurBackward_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(3, BasicIo::beg);
    int result = memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1u, memIo.tell());
}

// Test seeking from current position to before beginning
TEST_F(MemIoSeekTest_581, SeekCurBeforeBeginning_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(-3, BasicIo::cur);
    EXPECT_EQ(1, result);
}

// Test seeking from current position past end
TEST_F(MemIoSeekTest_581, SeekCurPastEnd_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(3, BasicIo::beg);
    int result = memIo.seek(3, BasicIo::cur);
    EXPECT_EQ(1, result);
    EXPECT_TRUE(memIo.eof());
}

// Test seeking from current with zero offset
TEST_F(MemIoSeekTest_581, SeekCurZeroOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(0, BasicIo::cur);
    EXPECT_EQ(0, result);
    EXPECT_EQ(2u, memIo.tell());
}

// Test seeking from end with offset 0
TEST_F(MemIoSeekTest_581, SeekEndZeroOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(0, result);
    EXPECT_EQ(5u, memIo.tell());
}

// Test seeking from end with negative offset (valid backward seek from end)
TEST_F(MemIoSeekTest_581, SeekEndNegativeOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-3, BasicIo::end);
    EXPECT_EQ(0, result);
    EXPECT_EQ(2u, memIo.tell());
}

// Test seeking from end to beginning
TEST_F(MemIoSeekTest_581, SeekEndToBeginning_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-5, BasicIo::end);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());
}

// Test seeking from end past beginning
TEST_F(MemIoSeekTest_581, SeekEndPastBeginning_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-6, BasicIo::end);
    EXPECT_EQ(1, result);
}

// Test seeking from end with positive offset (past end)
TEST_F(MemIoSeekTest_581, SeekEndPositiveOffset_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(1, BasicIo::end);
    EXPECT_EQ(1, result);
    EXPECT_TRUE(memIo.eof());
}

// Test that eof is cleared after a successful seek
TEST_F(MemIoSeekTest_581, EofClearedAfterSuccessfulSeek_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    // First cause eof
    memIo.seek(10, BasicIo::beg);
    EXPECT_TRUE(memIo.eof());
    // Now do a valid seek
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(memIo.eof());
}

// Test seeking on empty MemIo from end
TEST_F(MemIoSeekTest_581, SeekEndOnEmpty_581) {
    MemIo memIo;
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());
}

// Test seeking on empty MemIo from cur
TEST_F(MemIoSeekTest_581, SeekCurOnEmpty_581) {
    MemIo memIo;
    int result = memIo.seek(0, BasicIo::cur);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());
}

// Test seeking on empty MemIo from beg with positive offset
TEST_F(MemIoSeekTest_581, SeekBegPositiveOnEmpty_581) {
    MemIo memIo;
    int result = memIo.seek(1, BasicIo::beg);
    EXPECT_EQ(1, result);
    EXPECT_TRUE(memIo.eof());
}

// Test seeking from end with negative offset on empty MemIo
TEST_F(MemIoSeekTest_581, SeekEndNegativeOnEmpty_581) {
    MemIo memIo;
    int result = memIo.seek(-1, BasicIo::end);
    EXPECT_EQ(1, result);
}

// Test multiple sequential seeks
TEST_F(MemIoSeekTest_581, MultipleSequentialSeeks_581) {
    const byte data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    MemIo memIo(data, sizeof(data));

    EXPECT_EQ(0, memIo.seek(5, BasicIo::beg));
    EXPECT_EQ(5u, memIo.tell());

    EXPECT_EQ(0, memIo.seek(2, BasicIo::cur));
    EXPECT_EQ(7u, memIo.tell());

    EXPECT_EQ(0, memIo.seek(-3, BasicIo::cur));
    EXPECT_EQ(4u, memIo.tell());

    EXPECT_EQ(0, memIo.seek(-2, BasicIo::end));
    EXPECT_EQ(8u, memIo.tell());
}

// Test seek to exact boundary (size) from beg
TEST_F(MemIoSeekTest_581, SeekBegExactlyAtSize_581) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3u, memIo.tell());
    EXPECT_FALSE(memIo.eof());
}

// Test seeking from cur to exactly at size boundary
TEST_F(MemIoSeekTest_581, SeekCurExactlyAtSize_581) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    memIo.seek(1, BasicIo::beg);
    int result = memIo.seek(2, BasicIo::cur);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3u, memIo.tell());
    EXPECT_FALSE(memIo.eof());
}

// Test that a failed seek (past end) sets eof
TEST_F(MemIoSeekTest_581, FailedSeekSetsEof_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(100, BasicIo::beg);
    EXPECT_EQ(1, result);
    EXPECT_TRUE(memIo.eof());
}

// Test that a failed seek (before beginning) does NOT set eof
TEST_F(MemIoSeekTest_581, FailedSeekBeforeBeginningNoEof_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    // Negative newIdx should return 1 but not set eof (based on code)
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_EQ(1, result);
    // eof should not be set for negative index case (only for past-end)
}

// Test with single byte data
TEST_F(MemIoSeekTest_581, SingleByteData_581) {
    const byte data[] = {42};
    MemIo memIo(data, sizeof(data));

    EXPECT_EQ(0, memIo.seek(0, BasicIo::beg));
    EXPECT_EQ(0u, memIo.tell());

    EXPECT_EQ(0, memIo.seek(1, BasicIo::beg));
    EXPECT_EQ(1u, memIo.tell());

    EXPECT_EQ(1, memIo.seek(2, BasicIo::beg));

    EXPECT_EQ(0, memIo.seek(-1, BasicIo::end));
    EXPECT_EQ(0u, memIo.tell());
}

// Test seek after write extends size
TEST_F(MemIoSeekTest_581, SeekAfterWrite_581) {
    MemIo memIo;
    const byte data[] = {1, 2, 3, 4, 5};
    memIo.write(data, sizeof(data));

    EXPECT_EQ(5u, memIo.size());

    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0u, memIo.tell());

    result = memIo.seek(5, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_EQ(5u, memIo.tell());
}

// Test that after a successful seek, eof is false
TEST_F(MemIoSeekTest_581, SuccessfulSeekEofFalse_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(memIo.eof());
}

// Test seeking from cur with offset 0 at various positions
TEST_F(MemIoSeekTest_581, SeekCurZeroAtVariousPositions_581) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));

    // At beginning
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0, memIo.seek(0, BasicIo::cur));
    EXPECT_EQ(0u, memIo.tell());

    // At middle
    memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(0, memIo.seek(0, BasicIo::cur));
    EXPECT_EQ(3u, memIo.tell());

    // At end
    memIo.seek(5, BasicIo::beg);
    EXPECT_EQ(0, memIo.seek(0, BasicIo::cur));
    EXPECT_EQ(5u, memIo.tell());
}
