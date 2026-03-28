#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "exiv2/error.hpp"
#include "exiv2/tags.hpp"

#include <cstring>
#include <vector>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to write a uint32_t in the given byte order
static void writeULong(byte* buf, uint32_t val, ByteOrder bo) {
    if (bo == littleEndian) {
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

// Helper to write a uint16_t in the given byte order
static void writeUShort(byte* buf, uint16_t val, ByteOrder bo) {
    if (bo == littleEndian) {
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
    } else {
        buf[0] = static_cast<byte>((val >> 8) & 0xFF);
        buf[1] = static_cast<byte>(val & 0xFF);
    }
}

class TiffReaderVisitSubIfdTest_1704 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings to avoid noise in tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }

    // Build a minimal TIFF-like data buffer that contains:
    // - An IFD entry at a known position for the TiffSubIfd
    // - Sub-IFD data at specified offsets
    // Returns data buffer and sets up TiffReader and TiffSubIfd
    //
    // The layout:
    // [0..1]  : IFD entry count = 1
    // [2..13] : IFD entry (tag, type, count, offset/value)
    // [14..17]: Next IFD offset = 0
    // [offset]: Sub-IFD directory (minimal: count=0 + next=0 = 6 bytes)
    
    struct TestSetup {
        std::vector<byte> data;
        std::unique_ptr<TiffSubIfd> subIfd;
        std::unique_ptr<TiffComponent> root;
    };

    // Create a data buffer with an IFD entry for a SubIfd that points to sub-IFD(s)
    // entryTag: tag for the IFD entry
    // entryGroup: group for the IFD entry 
    // newGroup: the new group for sub-IFDs
    // tiffType: type of the entry (ttUnsignedLong, ttSignedLong, ttTiffIfd, etc.)
    // subIfdOffsets: offsets where sub-IFDs are located
    // totalSize: total size of the data buffer
    std::vector<byte> createDataWithSubIfd(
        ByteOrder bo,
        uint16_t entryTag,
        TiffType tiffType,
        const std::vector<uint32_t>& subIfdOffsets,
        size_t totalSize)
    {
        std::vector<byte> data(totalSize, 0);
        
        // Write IFD at offset 0:
        // Number of entries: 1
        writeUShort(data.data(), 1, bo);
        
        // IFD entry at offset 2:
        // Tag (2 bytes)
        writeUShort(data.data() + 2, entryTag, bo);
        // Type (2 bytes)
        writeUShort(data.data() + 4, static_cast<uint16_t>(tiffType), bo);
        // Count (4 bytes)
        writeULong(data.data() + 6, static_cast<uint32_t>(subIfdOffsets.size()), bo);
        
        // Value/Offset (4 bytes) - if count*4 <= 4, value is inline; otherwise offset to values
        if (subIfdOffsets.size() == 1 && subIfdOffsets.size() * 4 <= 4) {
            // Inline value
            writeULong(data.data() + 10, subIfdOffsets[0], bo);
        } else {
            // Need to store offsets somewhere; put them at offset 18 (after IFD)
            uint32_t valOffset = 18;
            writeULong(data.data() + 10, valOffset, bo);
            for (size_t i = 0; i < subIfdOffsets.size(); i++) {
                writeULong(data.data() + valOffset + i * 4, subIfdOffsets[i], bo);
            }
        }
        
        // Next IFD offset at offset 14
        writeULong(data.data() + 14, 0, bo);
        
        // For each sub-IFD offset, write a minimal empty IFD (count=0, next=0)
        for (auto off : subIfdOffsets) {
            if (off + 6 <= totalSize) {
                writeUShort(data.data() + off, 0, bo); // 0 entries
                writeULong(data.data() + off + 2, 0, bo); // next IFD = 0
            }
        }
        
        return data;
    }
};

// Test: visitSubIfd with a valid single sub-IFD pointer (UnsignedLong type)
TEST_F(TiffReaderVisitSubIfdTest_1704, ValidSingleSubIfd_UnsignedLong_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    
    // Set up the entry data by having the reader read it
    // We need to simulate what readTiffEntry does - set the start to the IFD entry
    subIfd.setStart(data.data() + 2); // Point to the IFD entry
    
    // The visitor pattern should handle this
    reader.visitSubIfd(&subIfd);
    
    // If no crash/exception, test passes - the method should process without error
    SUCCEED();
}

// Test: visitSubIfd with out-of-bounds offset should not crash
TEST_F(TiffReaderVisitSubIfdTest_1704, OutOfBoundsOffset_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 64;
    uint32_t subIfdOffset = 1000; // Way beyond totalSize
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    // Should handle gracefully (return early) due to out of bounds
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with SignedLong type
TEST_F(TiffReaderVisitSubIfdTest_1704, ValidSingleSubIfd_SignedLong_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttSignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with TiffIfd type
TEST_F(TiffReaderVisitSubIfdTest_1704, ValidSingleSubIfd_TiffIfd_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttTiffIfd, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with invalid type (e.g., ttAsciiString) - should warn and not process
TEST_F(TiffReaderVisitSubIfdTest_1704, InvalidTiffType_AsciiString_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttAsciiString, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    // Should handle gracefully - invalid type branch
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with big endian byte order
TEST_F(TiffReaderVisitSubIfdTest_1704, BigEndianByteOrder_1704) {
    ByteOrder bo = bigEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: TiffSubIfd constructor sets correct tag and group
TEST_F(TiffReaderVisitSubIfdTest_1704, SubIfdConstructor_1704) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::exifId);
    EXPECT_EQ(subIfd.tag(), 0x014A);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
    // tiffType should be ttUnsignedLong by default from constructor
    EXPECT_EQ(subIfd.tiffType(), ttUnsignedLong);
}

// Test: TiffReader constructor and byteOrder
TEST_F(TiffReaderVisitSubIfdTest_1704, ReaderByteOrder_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState stateLe(littleEndian, 0);
    TiffReader readerLe(data.data(), data.size(), root.get(), stateLe);
    EXPECT_EQ(readerLe.byteOrder(), littleEndian);
    
    TiffRwState stateBe(bigEndian, 0);
    TiffReader readerBe(data.data(), data.size(), root.get(), stateBe);
    EXPECT_EQ(readerBe.byteOrder(), bigEndian);
}

// Test: TiffReader baseOffset
TEST_F(TiffReaderVisitSubIfdTest_1704, ReaderBaseOffset_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data.data(), data.size(), root.get(), state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test: visitSubIfd with ifd1Id group (maxi = 1) - only first sub-IFD should be added
TEST_F(TiffReaderVisitSubIfdTest_1704, Ifd1GroupMaxiLimit_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 512;
    
    // Multiple sub-IFD offsets
    std::vector<uint32_t> offsets = {100, 200};
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, offsets, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd1Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    // ifd1Id group means maxi = 1, so only first sub-IFD should be processed
    TiffSubIfd subIfd(tag, IfdId::ifd1Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with non-ifd1 group and multiple sub-IFDs (up to 9)
TEST_F(TiffReaderVisitSubIfdTest_1704, NonIfd1GroupMultipleSubIfds_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 1024;
    
    // Create multiple sub-IFD offsets (within the maxi=9 limit)
    std::vector<uint32_t> offsets;
    for (uint32_t i = 0; i < 5; i++) {
        offsets.push_back(200 + i * 50);
    }
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, offsets, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with more than 9 sub-IFDs should skip beyond first 9
TEST_F(TiffReaderVisitSubIfdTest_1704, ExceedMaxiLimitNonIfd1_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 2048;
    
    // Create 12 sub-IFD offsets (exceeds maxi=9)
    std::vector<uint32_t> offsets;
    for (uint32_t i = 0; i < 12; i++) {
        offsets.push_back(200 + i * 50);
    }
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, offsets, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    // Should process only first 9 and then break
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with UnsignedShort type (invalid for sub-IFD)
TEST_F(TiffReaderVisitSubIfdTest_1704, InvalidType_UnsignedShort_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedShort, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with offset at exact boundary
TEST_F(TiffReaderVisitSubIfdTest_1704, OffsetAtExactBoundary_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 106; // subIfdOffset at 100, minimal IFD = 6 bytes -> exactly fits
    uint32_t subIfdOffset = 100;
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: visitSubIfd with zero offset
TEST_F(TiffReaderVisitSubIfdTest_1704, ZeroOffset_1704) {
    ByteOrder bo = littleEndian;
    uint16_t tag = 0x014A;
    size_t totalSize = 256;
    uint32_t subIfdOffset = 0; // Offset 0 points to beginning of data
    
    auto data = createDataWithSubIfd(bo, tag, ttUnsignedLong, {subIfdOffset}, totalSize);
    
    auto root = std::make_unique<TiffDirectory>(tag, IfdId::ifd0Id);
    TiffRwState state(bo, 0);
    TiffReader reader(data.data(), totalSize, root.get(), state);
    
    TiffSubIfd subIfd(tag, IfdId::ifd0Id, IfdId::exifId);
    subIfd.setStart(data.data() + 2);
    
    reader.visitSubIfd(&subIfd);
    SUCCEED();
}

// Test: nextIdx returns incrementing indices
TEST_F(TiffReaderVisitSubIfdTest_1704, NextIdxIncrementing_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data.data(), data.size(), root.get(), state);
    
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_LT(idx1, idx2);
}

// Test: circularReference detection
TEST_F(TiffReaderVisitSubIfdTest_1704, CircularReferenceFirstCall_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data.data(), data.size(), root.get(), state);
    
    // First call should not be circular
    bool isCircular = reader.circularReference(data.data() + 10, IfdId::ifd0Id);
    EXPECT_FALSE(isCircular);
}

// Test: circularReference with same start should detect circular
TEST_F(TiffReaderVisitSubIfdTest_1704, CircularReferenceDetected_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data.data(), data.size(), root.get(), state);
    
    const byte* start = data.data() + 10;
    reader.circularReference(start, IfdId::ifd0Id);
    // Second call with same start and group should be circular
    bool isCircular = reader.circularReference(start, IfdId::ifd0Id);
    EXPECT_TRUE(isCircular);
}

// Test: setOrigState and setMnState
TEST_F(TiffReaderVisitSubIfdTest_1704, SetOrigState_1704) {
    std::vector<byte> data(64, 0);
    auto root = std::make_unique<TiffDirectory>(0, IfdId::ifd0Id);
    
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data.data(), data.size(), root.get(), state);
    
    // setOrigState should restore the original state without crash
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}
