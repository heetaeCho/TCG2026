#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>

// Include necessary Exiv2 headers
#include "tiffcomposite_int.hpp"
#include "ioWrapper_int.hpp"
#include "types.hpp"
#include "value.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: A simple MemIo-based IoWrapper for testing
class TestIoWrapper {
public:
    // We'll track what's written
    std::vector<uint8_t> writtenData;
};

// We need to work with the actual IoWrapper and related infrastructure.
// Since IoWrapper wraps a BasicIo, we can use MemIo for testing.

class TiffEntryBaseDoWriteTest_366 : public ::testing::Test {
protected:
    void SetUp() override {
        memIo_ = std::make_unique<MemIo>();
    }

    std::unique_ptr<MemIo> memIo_;
};

// Since TiffEntryBase is an internal class and doWrite depends on pValue_ 
// (a member), and we can't directly instantiate TiffEntryBase easily without
// the full internal infrastructure, we test through the public composite hierarchy.
// However, given the constraints, we test what we can observe.

// We'll use TiffComponent derivatives that expose doWrite behavior.
// TiffEntry is a concrete subclass of TiffEntryBase.

class TiffEntryDoWriteTest_366 : public ::testing::Test {
protected:
    void SetUp() override {
        memIo_ = std::make_unique<MemIo>();
    }

    std::unique_ptr<MemIo> memIo_;
};

// Test that doWrite returns 0 when pValue_ is null (no value set)
TEST_F(TiffEntryDoWriteTest_366, DoWriteReturnsZeroWhenNoValue_366) {
    // Create a TiffEntry with a tag but no value set
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    // Create IoWrapper
    BasicIo::UniquePtr io(new MemIo());
    IoWrapper ioWrapper(*io, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, 0u);
}

// Test that doWrite returns 0 when pValue_ has size 0
TEST_F(TiffEntryDoWriteTest_366, DoWriteReturnsZeroWhenValueSizeIsZero_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    // Set an empty value
    Value::UniquePtr val = Value::create(unsignedByte);
    // Don't add any data - size should be 0
    entry.setValue(std::move(val));
    
    BasicIo::UniquePtr io(new MemIo());
    IoWrapper ioWrapper(*io, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, 0u);
}

// Test that doWrite writes correct number of bytes for a non-empty value
TEST_F(TiffEntryDoWriteTest_366, DoWriteWritesCorrectBytesForNonEmptyValue_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    // Set a value with actual data
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("42");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
    EXPECT_GT(result, 0u);
}

// Test with big endian byte order
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithBigEndianByteOrder_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("256");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = bigEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
}

// Test with little endian byte order
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithLittleEndianByteOrder_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("256");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
}

// Test writing multiple bytes (unsigned long value)
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithUnsignedLongValue_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedLong);
    val->read("12345678");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
    EXPECT_EQ(result, 4u); // unsignedLong is 4 bytes
}

// Test writing ASCII string value
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithAsciiStringValue_366) {
    TiffEntry entry(0x010e, IfdId::ifd0Id); // ImageDescription tag
    
    Value::UniquePtr val = Value::create(asciiString);
    val->read("Hello World");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
    EXPECT_GT(result, 0u);
}

// Test that written data matches the value (verify IoWrapper receives correct data)
TEST_F(TiffEntryDoWriteTest_366, DoWriteDataMatchesValueLittleEndian_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("258"); // 0x0102
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, 2u);
    
    // Read back from MemIo to verify
    memIo.seek(0, BasicIo::beg);
    byte buf[2];
    memIo.read(buf, 2);
    
    // Little endian: 0x0102 -> 0x02, 0x01
    EXPECT_EQ(buf[0], 0x02);
    EXPECT_EQ(buf[1], 0x01);
}

// Test that written data matches the value in big endian
TEST_F(TiffEntryDoWriteTest_366, DoWriteDataMatchesValueBigEndian_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("258"); // 0x0102
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = bigEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, 2u);
    
    // Read back from MemIo to verify
    memIo.seek(0, BasicIo::beg);
    byte buf[2];
    memIo.read(buf, 2);
    
    // Big endian: 0x0102 -> 0x01, 0x02
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// Test with unsigned byte value (single byte, byte order doesn't matter)
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithSingleByteValue_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedByte);
    val->read("255");
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, 1u);
    
    memIo.seek(0, BasicIo::beg);
    byte buf[1];
    memIo.read(buf, 1);
    EXPECT_EQ(buf[0], 0xFF);
}

// Test with multiple values in a single entry
TEST_F(TiffEntryDoWriteTest_366, DoWriteWithMultipleShortValues_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("1 2 3");
    size_t expectedSize = val->size();
    entry.setValue(std::move(val));
    
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
    
    size_t imageIdx = 0;
    ByteOrder byteOrder = littleEndian;
    
    size_t result = entry.doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);
    
    EXPECT_EQ(result, expectedSize);
    EXPECT_EQ(result, 6u); // 3 shorts * 2 bytes each
}

// Test that offset and other parameters don't affect the result size
TEST_F(TiffEntryDoWriteTest_366, DoWriteIgnoresOffsetParameters_366) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    Value::UniquePtr val = Value::create(unsignedShort);
    val->read("42");
    entry.setValue(std::move(val));
    
    MemIo memIo1;
    IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
    size_t imageIdx1 = 0;
    
    size_t result1 = entry.doWrite(ioWrapper1, littleEndian, 0, 0, 0, imageIdx1);
    
    MemIo memIo2;
    IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
    size_t imageIdx2 = 100;
    
    size_t result2 = entry.doWrite(ioWrapper2, littleEndian, 1000, 50, 200, imageIdx2);
    
    EXPECT_EQ(result1, result2);
}
