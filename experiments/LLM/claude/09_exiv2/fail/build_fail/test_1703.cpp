#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to build a minimal IFD buffer in memory
// IFD layout:
//   2 bytes: entry count (uint16)
//   N * 12 bytes: entries (each: 2 tag + 2 type + 4 count + 4 value/offset)
//   4 bytes: next IFD pointer (if hasNext)

class TiffReaderVisitDirectoryTest_1703 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings/errors by setting log level to mute
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }

    // Helper: write uint16 in little-endian
    void writeUInt16(byte* buf, uint16_t val) {
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
    }

    // Helper: write uint32 in little-endian
    void writeUInt32(byte* buf, uint32_t val) {
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        buf[2] = static_cast<byte>((val >> 16) & 0xFF);
        buf[3] = static_cast<byte>((val >> 24) & 0xFF);
    }

    // Create a TiffRwState with littleEndian byte order and base offset 0
    TiffRwState makeState(ByteOrder bo = littleEndian) {
        return TiffRwState(bo, 0);
    }
};

// Test: Buffer too small to read entry count (less than 2 bytes)
TEST_F(TiffReaderVisitDirectoryTest_1703, BufferTooSmallForEntryCount_1703) {
    byte data[1] = {0};
    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    // Should not crash; should return early
    reader.visitDirectory(&dir);
    // If we get here without crash, the test passes
    SUCCEED();
}

// Test: Entry count of zero, no hasNext
TEST_F(TiffReaderVisitDirectoryTest_1703, ZeroEntries_NoNext_1703) {
    byte data[2] = {0, 0}; // entry count = 0
    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Entry count exceeds 256 threshold (invalid directory)
TEST_F(TiffReaderVisitDirectoryTest_1703, TooManyEntries_1703) {
    byte data[2];
    writeUInt16(data, 257); // 257 > 256, should be rejected
    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Exactly 256 entries should be accepted (boundary)
TEST_F(TiffReaderVisitDirectoryTest_1703, MaxValidEntryCount256_1703) {
    // 2 bytes count + 256 * 12 bytes entries = 3074 bytes needed
    const size_t bufSize = 2 + 256 * 12;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 256);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: One entry that fits in buffer, no next pointer
TEST_F(TiffReaderVisitDirectoryTest_1703, OneEntry_NoNext_1703) {
    // 2 bytes count + 1 * 12 bytes = 14 bytes
    const size_t bufSize = 14;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 1);
    // Entry: tag=0x0100 (ImageWidth for ifd0), type=3 (SHORT), count=1, value=0
    writeUInt16(data.data() + 2, 0x0100);
    writeUInt16(data.data() + 4, 3);
    writeUInt32(data.data() + 6, 1);
    writeUInt32(data.data() + 10, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: One entry with hasNext and next pointer = 0 (no next IFD)
TEST_F(TiffReaderVisitDirectoryTest_1703, OneEntry_HasNext_NextZero_1703) {
    // 2 + 12 + 4 = 18 bytes
    const size_t bufSize = 18;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 1);
    writeUInt16(data.data() + 2, 0x0100);
    writeUInt16(data.data() + 4, 3);
    writeUInt32(data.data() + 6, 1);
    writeUInt32(data.data() + 10, 0);
    // Next pointer = 0
    writeUInt32(data.data() + 14, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: hasNext but buffer too small for next pointer
TEST_F(TiffReaderVisitDirectoryTest_1703, HasNext_BufferTooSmallForNextPointer_1703) {
    // 2 + 12 = 14 bytes; needs 18 for next pointer
    const size_t bufSize = 14;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 1);
    writeUInt16(data.data() + 2, 0x0100);
    writeUInt16(data.data() + 4, 3);
    writeUInt32(data.data() + 6, 1);
    writeUInt32(data.data() + 10, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Entry lies outside data buffer
TEST_F(TiffReaderVisitDirectoryTest_1703, EntryOutsideBuffer_1703) {
    // Claim 2 entries but only provide space for 1
    // 2 + 12 = 14 bytes; need 2 + 24 = 26
    const size_t bufSize = 14;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 2); // claims 2 entries

    writeUInt16(data.data() + 2, 0x0100);
    writeUInt16(data.data() + 4, 3);
    writeUInt32(data.data() + 6, 1);
    writeUInt32(data.data() + 10, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Next pointer out of bounds
TEST_F(TiffReaderVisitDirectoryTest_1703, NextPointerOutOfBounds_1703) {
    // 2 + 0*12 + 4 = 6 bytes; 0 entries, hasNext, next pointer very large
    const size_t bufSize = 6;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 0); // 0 entries
    writeUInt32(data.data() + 2, 0xFFFFFFFF); // next pointer way out of bounds

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Circular reference detection
TEST_F(TiffReaderVisitDirectoryTest_1703, CircularReference_1703) {
    // Create a valid small directory, visit it twice from same start
    const size_t bufSize = 6;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 0);
    writeUInt32(data.data() + 2, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    // First visit
    reader.visitDirectory(&dir);
    // Second visit with same start should trigger circular reference detection
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Big endian byte order
TEST_F(TiffReaderVisitDirectoryTest_1703, BigEndianByteOrder_1703) {
    const size_t bufSize = 6;
    std::vector<byte> data(bufSize, 0);
    // Write entry count = 0 in big endian
    data[0] = 0;
    data[1] = 0;
    // Next pointer = 0 in big endian
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;

    TiffRwState state(bigEndian, 0);
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Valid next pointer within bounds
TEST_F(TiffReaderVisitDirectoryTest_1703, ValidNextPointer_1703) {
    // 0 entries + next pointer pointing within buffer
    // We need baseOffset() + next <= size
    // baseOffset is typically 0 for default state
    const size_t bufSize = 64;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 0); // 0 entries
    writeUInt32(data.data() + 2, 8); // next pointer = 8 (within buffer)

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, true);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Empty buffer (size 0)
TEST_F(TiffReaderVisitDirectoryTest_1703, EmptyBuffer_1703) {
    byte data[1] = {0}; // need at least 1 byte for valid pointer
    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    // size = 0, so pLast_ = pData_ + 0 = pData_
    TiffReader reader(data, 0, &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Multiple entries, all within buffer
TEST_F(TiffReaderVisitDirectoryTest_1703, MultipleEntriesAllValid_1703) {
    const uint16_t numEntries = 3;
    const size_t bufSize = 2 + numEntries * 12;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), numEntries);

    // Write 3 entries with different tags
    for (uint16_t i = 0; i < numEntries; ++i) {
        byte* p = data.data() + 2 + i * 12;
        writeUInt16(p, 0x0100 + i); // tags 0x0100, 0x0101, 0x0102
        writeUInt16(p + 2, 3);      // type SHORT
        writeUInt32(p + 4, 1);      // count 1
        writeUInt32(p + 8, 0);      // value 0
    }

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: hasNext is false, no next pointer read attempted
TEST_F(TiffReaderVisitDirectoryTest_1703, NoNext_DoesNotReadNextPointer_1703) {
    // Buffer has exactly 2 bytes (count=0), no space for next
    // hasNext=false, so it shouldn't try to read next
    const size_t bufSize = 2;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false); // hasNext = false
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Entry count exactly 256 (boundary - should be accepted)
TEST_F(TiffReaderVisitDirectoryTest_1703, EntryCount256Boundary_1703) {
    // Only check that count=256 doesn't trigger the >256 rejection
    // Buffer may be too small for all entries, but count check comes first
    const size_t bufSize = 2 + 256 * 12;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 256);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    SUCCEED();
}

// Test: Entry count exactly 257 (boundary - should be rejected)
TEST_F(TiffReaderVisitDirectoryTest_1703, EntryCount257Rejected_1703) {
    const size_t bufSize = 2 + 257 * 12;
    std::vector<byte> data(bufSize, 0);
    writeUInt16(data.data(), 257);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data.data());

    TiffReader reader(data.data(), data.size(), &dir, state);
    reader.visitDirectory(&dir);
    // Should return early due to n > 256
    SUCCEED();
}

// Test: byteOrder and baseOffset accessors
TEST_F(TiffReaderVisitDirectoryTest_1703, ByteOrderAccessor_1703) {
    byte data[2] = {0, 0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

TEST_F(TiffReaderVisitDirectoryTest_1703, BaseOffsetAccessor_1703) {
    byte data[2] = {0, 0};
    TiffRwState state(littleEndian, 0);
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test: circularReference returns false on first call, true on second
TEST_F(TiffReaderVisitDirectoryTest_1703, CircularReferenceDetection_1703) {
    byte data[6] = {0};
    writeUInt16(data, 0);
    writeUInt32(data + 2, 0);

    TiffRwState state = makeState();
    TiffDirectory dir(0, IfdId::ifd0Id, false);
    dir.setStart(data);

    TiffReader reader(data, sizeof(data), &dir, state);
    
    bool first = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_FALSE(first);
    
    bool second = reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_TRUE(second);
}
