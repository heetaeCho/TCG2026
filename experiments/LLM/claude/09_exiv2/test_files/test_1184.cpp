#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::AtLeast;

// Mock for BasicIo
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class OffsetWriterTest_1184 : public ::testing::Test {
protected:
    OffsetWriter writer_;
    MockBasicIo mockIo_;
};

// Test: writeOffsets with no offsets set does not call seek or write
TEST_F(OffsetWriterTest_1184, WriteOffsetsEmpty_1184) {
    EXPECT_CALL(mockIo_, seek(_, _)).Times(0);
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), ::testing::A<size_t>())).Times(0);
    
    writer_.writeOffsets(mockIo_);
}

// Test: Setting origin and target for a single offset, then writing
TEST_F(OffsetWriterTest_1184, WriteOffsetsSingleEntry_1184) {
    writer_.setOrigin(OffsetId(0), 100, littleEndian);
    writer_.setTarget(OffsetId(0), 200);
    
    EXPECT_CALL(mockIo_, seek(100, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Writing with big endian byte order
TEST_F(OffsetWriterTest_1184, WriteOffsetsBigEndian_1184) {
    writer_.setOrigin(OffsetId(0), 50, bigEndian);
    writer_.setTarget(OffsetId(0), 300);
    
    EXPECT_CALL(mockIo_, seek(50, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Multiple offsets are all written
TEST_F(OffsetWriterTest_1184, WriteOffsetsMultipleEntries_1184) {
    writer_.setOrigin(OffsetId(0), 100, littleEndian);
    writer_.setTarget(OffsetId(0), 200);
    writer_.setOrigin(OffsetId(1), 300, bigEndian);
    writer_.setTarget(OffsetId(1), 400);
    
    EXPECT_CALL(mockIo_, seek(_, BasicIo::beg)).Times(2).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(2).WillRepeatedly(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Setting origin without target (target defaults to 0)
TEST_F(OffsetWriterTest_1184, WriteOffsetsOriginOnlyDefaultTarget_1184) {
    writer_.setOrigin(OffsetId(0), 64, littleEndian);
    // No setTarget called; target should default to 0
    
    EXPECT_CALL(mockIo_, seek(64, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Setting target before origin
TEST_F(OffsetWriterTest_1184, WriteOffsetsTargetBeforeOrigin_1184) {
    writer_.setTarget(OffsetId(0), 500);
    writer_.setOrigin(OffsetId(0), 80, littleEndian);
    
    EXPECT_CALL(mockIo_, seek(80, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Overwriting origin for same ID uses last value
TEST_F(OffsetWriterTest_1184, WriteOffsetsOverwriteOrigin_1184) {
    writer_.setOrigin(OffsetId(0), 100, littleEndian);
    writer_.setOrigin(OffsetId(0), 200, bigEndian);
    writer_.setTarget(OffsetId(0), 500);
    
    // Should seek to the overwritten origin (200)
    EXPECT_CALL(mockIo_, seek(200, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Overwriting target for same ID uses last value
TEST_F(OffsetWriterTest_1184, WriteOffsetsOverwriteTarget_1184) {
    writer_.setOrigin(OffsetId(0), 100, littleEndian);
    writer_.setTarget(OffsetId(0), 300);
    writer_.setTarget(OffsetId(0), 600);
    
    EXPECT_CALL(mockIo_, seek(100, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Zero origin and zero target
TEST_F(OffsetWriterTest_1184, WriteOffsetsZeroOriginAndTarget_1184) {
    writer_.setOrigin(OffsetId(0), 0, littleEndian);
    writer_.setTarget(OffsetId(0), 0);
    
    EXPECT_CALL(mockIo_, seek(0, BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Large origin and target values (boundary)
TEST_F(OffsetWriterTest_1184, WriteOffsetsLargeValues_1184) {
    uint32_t maxVal = 0xFFFFFFFF;
    writer_.setOrigin(OffsetId(0), maxVal, littleEndian);
    writer_.setTarget(OffsetId(0), maxVal);
    
    EXPECT_CALL(mockIo_, seek(static_cast<int64_t>(maxVal), BasicIo::beg)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(1).WillOnce(Return(4));
    
    writer_.writeOffsets(mockIo_);
}

// Test: Verify that the written bytes match expected little endian encoding
TEST_F(OffsetWriterTest_1184, WriteOffsetsVerifyLittleEndianBytes_1184) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    writer_.setTarget(OffsetId(0), 0x04030201);
    
    EXPECT_CALL(mockIo_, seek(10, BasicIo::beg)).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4))
        .WillOnce([](const byte* data, size_t wcount) -> size_t {
            EXPECT_EQ(wcount, 4u);
            // Little endian: 0x04030201 -> {0x01, 0x02, 0x03, 0x04}
            EXPECT_EQ(data[0], 0x01);
            EXPECT_EQ(data[1], 0x02);
            EXPECT_EQ(data[2], 0x03);
            EXPECT_EQ(data[3], 0x04);
            return 4;
        });
    
    writer_.writeOffsets(mockIo_);
}

// Test: Verify that the written bytes match expected big endian encoding
TEST_F(OffsetWriterTest_1184, WriteOffsetsVerifyBigEndianBytes_1184) {
    writer_.setOrigin(OffsetId(0), 10, bigEndian);
    writer_.setTarget(OffsetId(0), 0x04030201);
    
    EXPECT_CALL(mockIo_, seek(10, BasicIo::beg)).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4))
        .WillOnce([](const byte* data, size_t wcount) -> size_t {
            EXPECT_EQ(wcount, 4u);
            // Big endian: 0x04030201 -> {0x04, 0x03, 0x02, 0x01}
            EXPECT_EQ(data[0], 0x04);
            EXPECT_EQ(data[1], 0x03);
            EXPECT_EQ(data[2], 0x02);
            EXPECT_EQ(data[3], 0x01);
            return 4;
        });
    
    writer_.writeOffsets(mockIo_);
}

// Test: writeOffsets can be called multiple times
TEST_F(OffsetWriterTest_1184, WriteOffsetsCalledTwice_1184) {
    writer_.setOrigin(OffsetId(0), 100, littleEndian);
    writer_.setTarget(OffsetId(0), 200);
    
    EXPECT_CALL(mockIo_, seek(100, BasicIo::beg)).Times(2).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).Times(2).WillRepeatedly(Return(4));
    
    writer_.writeOffsets(mockIo_);
    writer_.writeOffsets(mockIo_);
}

// Test: Each seek is followed by a write (in sequence) for a single entry
TEST_F(OffsetWriterTest_1184, WriteOffsetsSeekThenWrite_1184) {
    writer_.setOrigin(OffsetId(0), 42, littleEndian);
    writer_.setTarget(OffsetId(0), 84);
    
    {
        InSequence seq;
        EXPECT_CALL(mockIo_, seek(42, BasicIo::beg)).WillOnce(Return(0));
        EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4)).WillOnce(Return(4));
    }
    
    writer_.writeOffsets(mockIo_);
}

// Test: Target value of 1 in little endian
TEST_F(OffsetWriterTest_1184, WriteOffsetsTargetOneLittleEndian_1184) {
    writer_.setOrigin(OffsetId(0), 0, littleEndian);
    writer_.setTarget(OffsetId(0), 1);
    
    EXPECT_CALL(mockIo_, seek(0, BasicIo::beg)).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4))
        .WillOnce([](const byte* data, size_t wcount) -> size_t {
            EXPECT_EQ(data[0], 0x01);
            EXPECT_EQ(data[1], 0x00);
            EXPECT_EQ(data[2], 0x00);
            EXPECT_EQ(data[3], 0x00);
            return 4;
        });
    
    writer_.writeOffsets(mockIo_);
}

// Test: Target value of 0 writes all zeros
TEST_F(OffsetWriterTest_1184, WriteOffsetsTargetZero_1184) {
    writer_.setOrigin(OffsetId(0), 0, littleEndian);
    writer_.setTarget(OffsetId(0), 0);
    
    EXPECT_CALL(mockIo_, seek(0, BasicIo::beg)).WillOnce(Return(0));
    EXPECT_CALL(mockIo_, write(::testing::A<const byte*>(), 4))
        .WillOnce([](const byte* data, size_t wcount) -> size_t {
            EXPECT_EQ(data[0], 0x00);
            EXPECT_EQ(data[1], 0x00);
            EXPECT_EQ(data[2], 0x00);
            EXPECT_EQ(data[3], 0x00);
            return 4;
        });
    
    writer_.writeOffsets(mockIo_);
}
