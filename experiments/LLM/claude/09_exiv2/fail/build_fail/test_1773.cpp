#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <vector>

#include "crwimage_int.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffComponentTest_1773 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to write a uint16_t in little-endian
    void writeUShort(byte* buf, uint16_t val, ByteOrder byteOrder) {
        if (byteOrder == littleEndian) {
            buf[0] = static_cast<byte>(val & 0xFF);
            buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        } else {
            buf[0] = static_cast<byte>((val >> 8) & 0xFF);
            buf[1] = static_cast<byte>(val & 0xFF);
        }
    }

    // Helper to write a uint32_t in little-endian
    void writeULong(byte* buf, uint32_t val, ByteOrder byteOrder) {
        if (byteOrder == littleEndian) {
            buf[0] = static_cast<byte>(val & 0xFF);
            buf[1] = static_cast<byte>((val >> 8) & 0xFF);
            buf[2] = static_cast<byte>((val >> 16) & 0xFF);
            buf[3] = static_cast<byte>((val >> 24) & 0xFF);
        } else {
            buf[0] = static_cast<byte>((val >> 24) & 0xFF);
            buf[1] = static_cast<byte>((val >> 16) & 0xFF);
            buf[2] = static_cast<byte>((val >> 8) & 0xFF);
            buf[3] = static_cast<byte>(val & 0xFF);
        }
    }

    // Build a data buffer with a directory entry at position `start`.
    // The tag field determines DataLocId behavior.
    // For valueData: tag has bit pattern where dataLocation returns valueData (tag & 0xC000 != 0x4000)
    // For directoryData: tag has bit pattern where dataLocation returns directoryData (tag & 0xC000 == 0x4000? depends on impl)
    // We'll construct entries carefully.
    
    // Creates a valid valueData entry
    // tag with dataLocation == valueData (bits 14-15 not indicating directory)
    // We'll use tag = 0x0000 which should give valueData
    std::vector<byte> createValueDataEntry(ByteOrder bo, uint16_t tag, uint32_t dataSize, 
                                            uint32_t dataOffset, uint32_t start, size_t totalSize) {
        std::vector<byte> data(totalSize, 0);
        writeUShort(data.data() + start, tag, bo);
        writeULong(data.data() + start + 2, dataSize, bo);
        writeULong(data.data() + start + 6, dataOffset, bo);
        return data;
    }
};

// Test default constructor creates component with zero values
TEST_F(CiffComponentTest_1773, DefaultConstructor_1773) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1773, ParameterizedConstructor_1773) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.tag(), 0x1234);
    EXPECT_EQ(comp.dir(), 0x5678);
}

// Test that read with size < 10 throws (kerNotACrwImage)
TEST_F(CiffComponentTest_1773, ReadSizeTooSmall_1773) {
    CiffComponent comp;
    byte data[9] = {0};
    EXPECT_THROW(comp.read(data, 9, 0, littleEndian), Error);
}

// Test that read with start > size - 10 throws
TEST_F(CiffComponentTest_1773, ReadStartTooLarge_1773) {
    CiffComponent comp;
    byte data[15] = {0};
    // size=15, start=6 => size-10=5, start(6)>5 => should throw
    EXPECT_THROW(comp.read(data, 15, 6, littleEndian), Error);
}

// Test that read with size exactly 10 and start=0 does not throw for directoryData entry
TEST_F(CiffComponentTest_1773, ReadMinimalSizeDirectoryData_1773) {
    CiffComponent comp;
    // For directoryData, we need a tag where dataLocation returns directoryData
    // According to CRW format, tags with bits 13-14 == 01 (0x4000) indicate directoryData? 
    // Let's try tag = 0x4000 which should be directoryData
    std::vector<byte> data(10, 0);
    // tag = 0x4000 for directoryData
    writeUShort(data.data(), 0x4000, littleEndian);
    // For directoryData, size=8, offset=start+2=2, pData_=pData+2
    EXPECT_NO_THROW(comp.read(data.data(), 10, 0, littleEndian));
    EXPECT_EQ(comp.size(), 8u);
    EXPECT_EQ(comp.offset(), 2u);
    EXPECT_EQ(comp.pData(), data.data() + 2);
}

// Test read with valueData - valid offset after directory entry
TEST_F(CiffComponentTest_1773, ReadValueDataValidOffsetAfterEntry_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 10;  // right after the 10-byte entry
    uint32_t dataSize = 4;
    size_t totalSize = dataOffset + dataSize; // 14

    // tag = 0x0000 should give valueData (not directoryData)
    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), dataSize);
    EXPECT_EQ(comp.offset(), dataOffset);
    EXPECT_EQ(comp.pData(), data.data() + dataOffset);
}

// Test read with valueData - offset before start (valid case: size <= start - offset)
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetBeforeStart_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 20;
    uint32_t dataOffset = 5;   // before start
    uint32_t dataSize = 10;    // 10 <= 20-5=15, OK
    size_t totalSize = start + 10; // 30

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), dataSize);
    EXPECT_EQ(comp.offset(), dataOffset);
}

// Test read valueData - offset before start, size too large -> throws
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetBeforeStartSizeTooLarge_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 20;
    uint32_t dataOffset = 5;
    uint32_t dataSize = 16;  // 16 > 20-5=15 => should throw kerOffsetOutOfRange
    size_t totalSize = start + 10;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_THROW(comp.read(data.data(), totalSize, start, bo), Error);
}

// Test read valueData - offset in forbidden zone (between start and start+10) -> throws
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetInForbiddenZone_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 10;
    uint32_t dataOffset = 15;  // >= start but < start+10=20 => should throw
    uint32_t dataSize = 4;
    size_t totalSize = 30;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_THROW(comp.read(data.data(), totalSize, start, bo), Error);
}

// Test read valueData - offset > size -> throws
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetBeyondSize_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 100;  // way beyond totalSize
    uint32_t dataSize = 4;
    size_t totalSize = 20;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_THROW(comp.read(data.data(), totalSize, start, bo), Error);
}

// Test read valueData - dataSize > size - offset -> throws
TEST_F(CiffComponentTest_1773, ReadValueDataSizeExceedsRemaining_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 10;
    uint32_t dataSize = 100;  // 100 > totalSize - 10 = 10 => throws
    size_t totalSize = 20;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_THROW(comp.read(data.data(), totalSize, start, bo), Error);
}

// Test read with big endian byte order
TEST_F(CiffComponentTest_1773, ReadValueDataBigEndian_1773) {
    CiffComponent comp;
    ByteOrder bo = bigEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 10;
    uint32_t dataSize = 5;
    size_t totalSize = 20;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), dataSize);
    EXPECT_EQ(comp.offset(), dataOffset);
    EXPECT_EQ(comp.pData(), data.data() + dataOffset);
}

// Test directoryData sets size to 8 and offset to start+2
TEST_F(CiffComponentTest_1773, ReadDirectoryDataSizeAndOffset_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 10;
    size_t totalSize = 30;

    std::vector<byte> data(totalSize, 0);
    // Use tag 0x4000 for directoryData
    writeUShort(data.data() + start, 0x4000, bo);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), 8u);
    EXPECT_EQ(comp.offset(), start + 2);
    EXPECT_EQ(comp.pData(), data.data() + start + 2);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1773, EmptyOnDefault_1773) {
    CiffComponent comp;
    // Default component should be empty (no data)
    EXPECT_TRUE(comp.empty());
}

// Test tag() returns the tag from construction
TEST_F(CiffComponentTest_1773, TagReturnsConstructedValue_1773) {
    CiffComponent comp(0xABCD, 0x1234);
    EXPECT_EQ(comp.tag(), 0xABCD);
}

// Test dir() returns the dir from construction
TEST_F(CiffComponentTest_1773, DirReturnsConstructedValue_1773) {
    CiffComponent comp(0xABCD, 0x1234);
    EXPECT_EQ(comp.dir(), 0x1234);
}

// Test setDir changes the dir
TEST_F(CiffComponentTest_1773, SetDirChangesDir_1773) {
    CiffComponent comp(0xABCD, 0x1234);
    comp.setDir(0x5678);
    EXPECT_EQ(comp.dir(), 0x5678);
}

// Test read with valueData where offset equals start+10 (boundary - should be valid)
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetExactlyStartPlus10_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 10;  // exactly start + 10
    uint32_t dataSize = 0;
    size_t totalSize = 10;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
}

// Test read with valueData where offset equals size (boundary)
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetEqualsSize_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    uint32_t dataOffset = 20;  // equals totalSize
    uint32_t dataSize = 0;     // 0 <= 20-20=0, OK
    size_t totalSize = 20;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
}

// Test read with zero size data
TEST_F(CiffComponentTest_1773, ReadZeroSizeData_1773) {
    CiffComponent comp;
    byte data[1] = {0};
    EXPECT_THROW(comp.read(data, 0, 0, littleEndian), Error);
}

// Test read with valueData where dataOffset == start (forbidden, not < start and not >= start+10)
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetEqualsStart_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 10;
    uint32_t dataOffset = 10;  // equals start, >= start but < start+10=20 => throws
    uint32_t dataSize = 4;
    size_t totalSize = 30;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_THROW(comp.read(data.data(), totalSize, start, bo), Error);
}

// Test reading tag value through read
TEST_F(CiffComponentTest_1773, ReadSetsTag_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 0;
    size_t totalSize = 20;

    std::vector<byte> data(totalSize, 0);
    // Use a directoryData tag so we don't need valid offset/size fields
    writeUShort(data.data() + start, 0x4000, bo);

    comp.read(data.data(), totalSize, start, bo);
    EXPECT_EQ(comp.tag(), 0x4000);
}

// Test setValue and then check pData/size behavior
TEST_F(CiffComponentTest_1773, SetValueUpdatesStorage_1773) {
    CiffComponent comp;
    byte testData[] = {1, 2, 3, 4, 5};
    DataBuf buf(testData, 5);
    comp.setValue(std::move(buf));
    // After setValue, the component should hold the data
    // We can check this doesn't crash and pData is set
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 5u);
}

// Test valueData with offset before start, size exactly equals start-offset
TEST_F(CiffComponentTest_1773, ReadValueDataOffsetBeforeStartExactFit_1773) {
    CiffComponent comp;
    ByteOrder bo = littleEndian;
    uint32_t start = 20;
    uint32_t dataOffset = 5;
    uint32_t dataSize = 15;  // exactly start - offset = 15
    size_t totalSize = start + 10;

    auto data = createValueDataEntry(bo, 0x0000, dataSize, dataOffset, start, totalSize);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), 15u);
    EXPECT_EQ(comp.offset(), 5u);
}

// Test read with start at non-zero position, directoryData
TEST_F(CiffComponentTest_1773, ReadDirectoryDataNonZeroStart_1773) {
    CiffComponent comp;
    ByteOrder bo = bigEndian;
    uint32_t start = 5;
    size_t totalSize = 20;

    std::vector<byte> data(totalSize, 0);
    writeUShort(data.data() + start, 0x4000, bo);

    EXPECT_NO_THROW(comp.read(data.data(), totalSize, start, bo));
    EXPECT_EQ(comp.size(), 8u);
    EXPECT_EQ(comp.offset(), 7u);  // start + 2 = 7
    EXPECT_EQ(comp.pData(), data.data() + 7);
}
