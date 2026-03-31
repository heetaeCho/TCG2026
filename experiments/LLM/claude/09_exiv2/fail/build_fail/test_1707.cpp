#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete TiffEntryBase subclass for testing
// TiffEntry is typically available
#include "tiffimage_int.hpp"

namespace {

// Helper to write a uint16_t in little-endian
void putUShortLE(byte* buf, uint16_t val) {
    buf[0] = static_cast<byte>(val & 0xff);
    buf[1] = static_cast<byte>((val >> 8) & 0xff);
}

// Helper to write a uint32_t in little-endian
void putULongLE(byte* buf, uint32_t val) {
    buf[0] = static_cast<byte>(val & 0xff);
    buf[1] = static_cast<byte>((val >> 8) & 0xff);
    buf[2] = static_cast<byte>((val >> 16) & 0xff);
    buf[3] = static_cast<byte>((val >> 24) & 0xff);
}

// Helper to write a uint16_t in big-endian
void putUShortBE(byte* buf, uint16_t val) {
    buf[0] = static_cast<byte>((val >> 8) & 0xff);
    buf[1] = static_cast<byte>(val & 0xff);
}

// Helper to write a uint32_t in big-endian
void putULongBE(byte* buf, uint32_t val) {
    buf[0] = static_cast<byte>((val >> 24) & 0xff);
    buf[1] = static_cast<byte>((val >> 16) & 0xff);
    buf[2] = static_cast<byte>((val >> 8) & 0xff);
    buf[3] = static_cast<byte>(val & 0xff);
}

class TiffReaderTest_1707 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings to avoid noise in tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }

    // Creates a minimal valid TIFF entry in a buffer (little-endian)
    // Returns the total buffer with extra space for data
    // Entry format: tag(2) + type(2) + count(4) + offset/value(4) = 12 bytes
    std::vector<byte> createEntryBuffer(uint16_t tag, uint16_t tiffType, uint32_t count, 
                                         uint32_t offsetOrValue, 
                                         const std::vector<byte>& extraData = {},
                                         bool bigEndian = false) {
        // We need space for the entry (12 bytes) plus any extra data
        size_t totalSize = 12 + extraData.size();
        std::vector<byte> buf(totalSize, 0);

        if (bigEndian) {
            putUShortBE(&buf[0], tag);
            putUShortBE(&buf[2], tiffType);
            putULongBE(&buf[4], count);
            putULongBE(&buf[8], offsetOrValue);
        } else {
            putUShortLE(&buf[0], tag);
            putUShortLE(&buf[2], tiffType);
            putULongLE(&buf[4], count);
            putULongLE(&buf[8], offsetOrValue);
        }

        for (size_t i = 0; i < extraData.size(); i++) {
            buf[12 + i] = extraData[i];
        }
        return buf;
    }
};

// Test: Normal read of a small entry (size <= 4, data inline)
TEST_F(TiffReaderTest_1707, ReadSmallInlineEntry_1707) {
    // Create an entry: tag=0x0100, type=SHORT(3), count=1, value=42
    auto buf = createEntryBuffer(0x0100, 3, 1, 42);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // After reading, the entry should have a value
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 42);
}

// Test: Normal read of an entry with data beyond 4 bytes (offset points to data)
TEST_F(TiffReaderTest_1707, ReadLargerEntryWithOffset_1707) {
    // type=SHORT(3), count=4, size = 2*4 = 8 > 4, so offset is used
    // Offset should point within the buffer. Let's put data at offset 12.
    std::vector<byte> extraData = {1, 0, 2, 0, 3, 0, 4, 0}; // 4 shorts in LE
    auto buf = createEntryBuffer(0x0100, 3, 4, 12, extraData);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 4u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 1);
    EXPECT_EQ(entry.pValue()->toInt64(1), 2);
    EXPECT_EQ(entry.pValue()->toInt64(2), 3);
    EXPECT_EQ(entry.pValue()->toInt64(3), 4);
}

// Test: Entry too short (start + 12 > pLast) - should skip
TEST_F(TiffReaderTest_1707, EntryTooShortSkipped_1707) {
    // Buffer only 10 bytes, but entry needs 12
    std::vector<byte> buf(10, 0);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // Entry should not have a value set since it was skipped
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test: Count is extremely large (>= 0x10000000) - should skip
TEST_F(TiffReaderTest_1707, InvalidCountSkipped_1707) {
    auto buf = createEntryBuffer(0x0100, 3, 0x10000000, 0);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // Should be skipped, no value
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test: Entry with count=0 should create a value with 0 items
TEST_F(TiffReaderTest_1707, ZeroCountEntry_1707) {
    auto buf = createEntryBuffer(0x0100, 3, 0, 0);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 0u);
}

// Test: Single BYTE value inline
TEST_F(TiffReaderTest_1707, ReadSingleByteInline_1707) {
    // type=BYTE(1), count=1, value=0xFF
    auto buf = createEntryBuffer(0x0100, 1, 1, 0xFF);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 0xFF);
}

// Test: 4 bytes inline (exactly 4 bytes, should use inline data)
TEST_F(TiffReaderTest_1707, ReadFourBytesInline_1707) {
    // type=BYTE(1), count=4
    auto buf = createEntryBuffer(0x0100, 1, 4, 0);
    // Set inline data bytes manually
    buf[8] = 0x01;
    buf[9] = 0x02;
    buf[10] = 0x03;
    buf[11] = 0x04;

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 4u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 1);
    EXPECT_EQ(entry.pValue()->toInt64(1), 2);
    EXPECT_EQ(entry.pValue()->toInt64(2), 3);
    EXPECT_EQ(entry.pValue()->toInt64(3), 4);
}

// Test: Offset out of bounds (offset + baseOffset >= size_) for size > 4
TEST_F(TiffReaderTest_1707, OffsetOutOfBoundsTruncated_1707) {
    // type=SHORT(3), count=4, size=8 > 4, offset=9999 (way out of bounds)
    auto buf = createEntryBuffer(0x0100, 3, 4, 9999);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // The entry should still get a value but with size truncated to 0
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 0u);
}

// Test: Big-endian byte order
TEST_F(TiffReaderTest_1707, BigEndianEntry_1707) {
    // type=SHORT(3), count=1, value=42 in big-endian
    auto buf = createEntryBuffer(0x0100, 3, 1, 42, {}, true);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(bigEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 42);
}

// Test: LONG type entry (4 bytes each, count=1, inline)
TEST_F(TiffReaderTest_1707, ReadLongInline_1707) {
    // type=LONG(4), count=1, value=100000
    auto buf = createEntryBuffer(0x0100, 4, 1, 100000);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedLong);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 100000);
}

// Test: Offset stored correctly
TEST_F(TiffReaderTest_1707, OffsetStoredCorrectly_1707) {
    // Inline entry, offset field = 42
    auto buf = createEntryBuffer(0x0100, 3, 1, 42);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    EXPECT_EQ(entry.offset(), 42u);
}

// Test: Upper boundary of data exceeds buffer for size > 4
TEST_F(TiffReaderTest_1707, DataUpperBoundaryExceedsBuffer_1707) {
    // type=SHORT(3), count=4, size=8 > 4
    // offset=8 -> data starts at byte 8 in buffer, but we make buffer just barely too small
    // Buffer: 12 entry bytes + 4 extra = 16 total. Data at offset 8 needs 8 bytes (8..15)
    // but pLast would be at buf+16, pData at buf+8, so pLast - pData = 8. That's exactly enough.
    // Let's make buffer 15 bytes so it's 1 byte short.
    std::vector<byte> buf(15, 0);
    putUShortLE(&buf[0], 0x0100);
    putUShortLE(&buf[2], 3); // SHORT
    putULongLE(&buf[4], 4);  // count=4
    putULongLE(&buf[8], 8);  // offset=8

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // Data upper boundary exceeded, size should be truncated to 0
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 0u);
}

// Test: Verify idx is set (should be sequential for same group)
TEST_F(TiffReaderTest_1707, IdxIsSet_1707) {
    auto buf = createEntryBuffer(0x0100, 3, 1, 42);

    TiffEntry entry1(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry1.setStart(buf.data());

    TiffEntry entry2(0x0101, IfdId::ifd0Id, ttUnsignedShort);
    entry2.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry1, state);

    reader.readTiffEntry(&entry1);
    reader.readTiffEntry(&entry2);

    // First and second entries should have different indices
    EXPECT_NE(entry1.idx(), entry2.idx());
}

// Test: RATIONAL type inline (8 bytes, but count=1 means size=8 > 4, so uses offset)
TEST_F(TiffReaderTest_1707, ReadRationalWithOffset_1707) {
    // type=RATIONAL(5), count=1, size=8 > 4
    // Rational = 2 longs: numerator + denominator
    // Put data at offset 12
    std::vector<byte> extraData(8, 0);
    putULongLE(&extraData[0], 1); // numerator
    putULongLE(&extraData[4], 3); // denominator

    auto buf = createEntryBuffer(0x0100, 5, 1, 12, extraData);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedRational);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
    // Rational 1/3
    Rational r = entry.pValue()->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 3);
}

// Test: Boundary - exactly 12 bytes buffer (minimum valid)
TEST_F(TiffReaderTest_1707, ExactlyMinimumBuffer_1707) {
    auto buf = createEntryBuffer(0x0100, 1, 1, 0x42); // BYTE, count=1

    // Ensure buffer is exactly 12 bytes
    ASSERT_EQ(buf.size(), 12u);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 1u);
}

// Test: Buffer of 11 bytes - entry start + 12 > pLast, should skip
TEST_F(TiffReaderTest_1707, BufferTooSmallBy1Byte_1707) {
    std::vector<byte> buf(11, 0);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test: Count just below threshold (0x0FFFFFFF) should be accepted
TEST_F(TiffReaderTest_1707, CountJustBelowThreshold_1707) {
    // type=BYTE(1), count=0x0FFFFFFF, size = 0x0FFFFFFF * 1 > 4 -> uses offset
    // But the offset will be out of bounds, so size gets truncated
    auto buf = createEntryBuffer(0x0100, 1, 0x0FFFFFFF, 9999);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedByte);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    // Should not be skipped by count check, but offset is out of bounds -> truncated
    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 0u);
}

// Test: ASCII string inline (4 chars or less)
TEST_F(TiffReaderTest_1707, ReadAsciiInline_1707) {
    // type=ASCII(2), count=4 (including null), size=4 <= 4 -> inline
    uint32_t val = 0;
    byte* vp = reinterpret_cast<byte*>(&val);
    vp[0] = 'A';
    vp[1] = 'B';
    vp[2] = 'C';
    vp[3] = '\0';

    auto buf = createEntryBuffer(0x010E, 2, 4, val);

    TiffEntry entry(0x010E, IfdId::ifd0Id, ttAsciiString);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    // ASCII values should be readable as string
    EXPECT_EQ(entry.pValue()->toString(), "ABC");
}

// Test: With base offset (non-zero)
TEST_F(TiffReaderTest_1707, NonZeroBaseOffset_1707) {
    // type=SHORT(3), count=4, size=8 > 4
    // base offset = 4, actual offset in entry = 8
    // Data location = baseOffset + offset = 4 + 8 = 12
    std::vector<byte> extraData = {10, 0, 20, 0, 30, 0, 40, 0};
    
    // Total buffer: 12 (entry) + 8 (extra) = 20 bytes
    auto buf = createEntryBuffer(0x0100, 3, 4, 8, extraData);

    TiffEntry entry(0x0100, IfdId::ifd0Id, ttUnsignedShort);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 4);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 4u);
    EXPECT_EQ(entry.pValue()->toInt64(0), 10);
    EXPECT_EQ(entry.pValue()->toInt64(1), 20);
    EXPECT_EQ(entry.pValue()->toInt64(2), 30);
    EXPECT_EQ(entry.pValue()->toInt64(3), 40);
}

// Test: UNDEFINED type with inline data
TEST_F(TiffReaderTest_1707, ReadUndefinedInline_1707) {
    // type=UNDEFINED(7), count=4, inline
    auto buf = createEntryBuffer(0x9000, 7, 4, 0);
    buf[8] = 0x30;
    buf[9] = 0x32;
    buf[10] = 0x33;
    buf[11] = 0x30;

    TiffEntry entry(0x9000, IfdId::ifd0Id, ttUndefined);
    entry.setStart(buf.data());

    TiffRwState state(littleEndian, 0);
    TiffReader reader(buf.data(), buf.size(), &entry, state);

    reader.readTiffEntry(&entry);

    ASSERT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->count(), 4u);
}

} // namespace
