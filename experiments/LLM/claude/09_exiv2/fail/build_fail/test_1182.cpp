#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffimage_int.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock for BasicIo to test writeOffsets
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(long, write, (const byte* data, long wcount), (override));
    MOCK_METHOD(long, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (long rcount), (override));
    MOCK_METHOD(long, read, (byte* buf, long rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(long, seek, (long offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(long, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, noexcept, override));
#ifdef EXV_UNICODE_PATH
    MOCK_METHOD(const std::wstring&, wpath, (), (const, noexcept, override));
#endif

    MockBasicIo() {
        static const std::string emptyPath;
        ON_CALL(*this, path()).WillByDefault(::testing::ReturnRef(emptyPath));
    }
};

class OffsetWriterTest_1182 : public ::testing::Test {
protected:
    OffsetWriter writer_;
};

// Test: setOrigin with a valid OffsetId and littleEndian byte order
TEST_F(OffsetWriterTest_1182, SetOriginLittleEndian_1182) {
    // Should not throw when setting origin with littleEndian
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 100, littleEndian));
}

// Test: setOrigin with bigEndian byte order
TEST_F(OffsetWriterTest_1182, SetOriginBigEndian_1182) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 200, bigEndian));
}

// Test: setOrigin with origin value of 0 (boundary)
TEST_F(OffsetWriterTest_1182, SetOriginZeroValue_1182) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 0, littleEndian));
}

// Test: setOrigin with maximum uint32_t value (boundary)
TEST_F(OffsetWriterTest_1182, SetOriginMaxUint32_1182) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, UINT32_MAX, littleEndian));
}

// Test: setOrigin called multiple times with the same id (overwrite)
TEST_F(OffsetWriterTest_1182, SetOriginOverwriteSameId_1182) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 100, littleEndian));
    EXPECT_NO_THROW(writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 200, bigEndian));
}

// Test: setTarget with a valid OffsetId
TEST_F(OffsetWriterTest_1182, SetTargetAfterOrigin_1182) {
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 100, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 500));
}

// Test: setTarget with target value of 0 (boundary)
TEST_F(OffsetWriterTest_1182, SetTargetZeroValue_1182) {
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 100, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 0));
}

// Test: setTarget with maximum uint32_t value (boundary)
TEST_F(OffsetWriterTest_1182, SetTargetMaxUint32_1182) {
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 100, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetWriter::cr2RawIfdOffset, UINT32_MAX));
}

// Test: writeOffsets on empty writer (no origins/targets set)
TEST_F(OffsetWriterTest_1182, WriteOffsetsEmpty_1182) {
    MockBasicIo mockIo;
    // With no offsets set, writeOffsets should not attempt seeks or writes
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}

// Test: writeOffsets after setting origin and target
TEST_F(OffsetWriterTest_1182, WriteOffsetsWithOriginAndTarget_1182) {
    MockBasicIo mockIo;
    
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 16, littleEndian);
    writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 1024);
    
    // Expect seek to the origin position
    EXPECT_CALL(mockIo, seek(16, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    // Expect a write of 4 bytes (uint32_t target value)
    EXPECT_CALL(mockIo, write(::testing::_, 4))
        .WillOnce(::testing::Return(4));
    
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}

// Test: writeOffsets with bigEndian byte order
TEST_F(OffsetWriterTest_1182, WriteOffsetsWithBigEndian_1182) {
    MockBasicIo mockIo;
    
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 32, bigEndian);
    writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 2048);
    
    EXPECT_CALL(mockIo, seek(32, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    EXPECT_CALL(mockIo, write(::testing::_, 4))
        .WillOnce(::testing::Return(4));
    
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}

// Test: setOrigin and setTarget with multiple different IDs
TEST_F(OffsetWriterTest_1182, MultipleOffsetIds_1182) {
    // Assuming there might be multiple OffsetId values; use cr2RawIfdOffset
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 10, littleEndian);
    writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 500);
    
    MockBasicIo mockIo;
    
    EXPECT_CALL(mockIo, seek(::testing::_, BasicIo::beg))
        .WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, write(::testing::_, 4))
        .WillRepeatedly(::testing::Return(4));
    
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}

// Test: setTarget called before setOrigin (id not yet in map)
TEST_F(OffsetWriterTest_1182, SetTargetWithoutOrigin_1182) {
    // This tests the behavior when setTarget is called for an id not yet set
    // The behavior depends on implementation - it should either handle gracefully or be a no-op
    EXPECT_NO_THROW(writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 500));
}

// Test: Overwriting target value
TEST_F(OffsetWriterTest_1182, OverwriteTarget_1182) {
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 16, littleEndian);
    writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 500);
    writer_.setTarget(OffsetWriter::cr2RawIfdOffset, 1000);
    
    MockBasicIo mockIo;
    
    EXPECT_CALL(mockIo, seek(16, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    // Should write the latest target value (1000)
    EXPECT_CALL(mockIo, write(::testing::_, 4))
        .WillOnce(::testing::Return(4));
    
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}

// Test: writeOffsets when origin is set but target is default (0)
TEST_F(OffsetWriterTest_1182, WriteOffsetsDefaultTarget_1182) {
    MockBasicIo mockIo;
    
    writer_.setOrigin(OffsetWriter::cr2RawIfdOffset, 16, littleEndian);
    // Target not explicitly set, should be default (0)
    
    EXPECT_CALL(mockIo, seek(16, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    EXPECT_CALL(mockIo, write(::testing::_, 4))
        .WillOnce(::testing::Return(4));
    
    EXPECT_NO_THROW(writer_.writeOffsets(mockIo));
}
