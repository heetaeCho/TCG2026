#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"

#include <cstring>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to build a minimal valid TIFF IFD entry in a buffer
// TIFF entry format: tag(2) + type(2) + count(4) + value/offset(4) = 12 bytes
static void writeTiffEntry(byte* buf, uint16_t tag, uint16_t type, uint32_t count, uint32_t valueOffset, ByteOrder byteOrder) {
    if (byteOrder == littleEndian) {
        buf[0] = static_cast<byte>(tag & 0xFF);
        buf[1] = static_cast<byte>((tag >> 8) & 0xFF);
        buf[2] = static_cast<byte>(type & 0xFF);
        buf[3] = static_cast<byte>((type >> 8) & 0xFF);
        buf[4] = static_cast<byte>(count & 0xFF);
        buf[5] = static_cast<byte>((count >> 8) & 0xFF);
        buf[6] = static_cast<byte>((count >> 16) & 0xFF);
        buf[7] = static_cast<byte>((count >> 24) & 0xFF);
        buf[8] = static_cast<byte>(valueOffset & 0xFF);
        buf[9] = static_cast<byte>((valueOffset >> 8) & 0xFF);
        buf[10] = static_cast<byte>((valueOffset >> 16) & 0xFF);
        buf[11] = static_cast<byte>((valueOffset >> 24) & 0xFF);
    } else {
        buf[0] = static_cast<byte>((tag >> 8) & 0xFF);
        buf[1] = static_cast<byte>(tag & 0xFF);
        buf[2] = static_cast<byte>((type >> 8) & 0xFF);
        buf[3] = static_cast<byte>(type & 0xFF);
        buf[4] = static_cast<byte>((count >> 24) & 0xFF);
        buf[5] = static_cast<byte>((count >> 16) & 0xFF);
        buf[6] = static_cast<byte>((count >> 8) & 0xFF);
        buf[7] = static_cast<byte>(count & 0xFF);
        buf[8] = static_cast<byte>((valueOffset >> 24) & 0xFF);
        buf[9] = static_cast<byte>((valueOffset >> 16) & 0xFF);
        buf[10] = static_cast<byte>((valueOffset >> 8) & 0xFF);
        buf[11] = static_cast<byte>(valueOffset & 0xFF);
    }
}

class TiffReaderReadDataEntryBaseTest_1695 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that TiffFinder can be constructed and initially returns null
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffFinderInitialResultIsNull_1695) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that TiffFinder init resets the result
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffFinderInitResetsResult_1695) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    finder.init(0x0112, IfdId::ifd1Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffDataEntryBase accessors for szTag and szGroup
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffDataEntryBaseAccessors_1695) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_EQ(entry.szTag(), 0x0117);
    EXPECT_EQ(entry.szGroup(), IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0111);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

// Test TiffEntryBase default pValue is null
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffEntryBasePValueInitiallyNull_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test TiffEntryBase pData is initially null
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffEntryBasePDataInitiallyNull_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test TiffReader byteOrder returns the order from the state
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffReaderByteOrderMatchesState_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test TiffReader baseOffset returns the offset from the state
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffReaderBaseOffsetMatchesState_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.baseOffset(), static_cast<size_t>(0));
}

// Test TiffReader with bigEndian byte order
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffReaderBigEndianByteOrder_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test circularReference returns false for first visit
TEST_F(TiffReaderReadDataEntryBaseTest_1695, CircularReferenceFirstVisitReturnsFalse_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
}

// Test circularReference returns true for second visit to same start
TEST_F(TiffReaderReadDataEntryBaseTest_1695, CircularReferenceSecondVisitReturnsTrue_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    reader.circularReference(data, IfdId::ifd0Id);
    EXPECT_TRUE(reader.circularReference(data, IfdId::ifd0Id));
}

// Test nextIdx increments for same group
TEST_F(TiffReaderReadDataEntryBaseTest_1695, NextIdxIncrementsForSameGroup_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx0 = reader.nextIdx(IfdId::ifd0Id);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx1, idx0 + 1);
}

// Test nextIdx returns 0 for first call
TEST_F(TiffReaderReadDataEntryBaseTest_1695, NextIdxReturnsZeroFirst_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 0);
}

// Test nextIdx for different groups are independent
TEST_F(TiffReaderReadDataEntryBaseTest_1695, NextIdxDifferentGroupsIndependent_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx_ifd0 = reader.nextIdx(IfdId::ifd0Id);
    int idx_ifd1 = reader.nextIdx(IfdId::ifd1Id);
    EXPECT_EQ(idx_ifd0, 0);
    EXPECT_EQ(idx_ifd1, 0);
}

// Test setOrigState and setMnState
TEST_F(TiffReaderReadDataEntryBaseTest_1695, SetOrigStateRestoresByteOrder_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState origState(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, origState);

    TiffRwState mnState(bigEndian, 8);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);

    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test TiffComponent tag and group
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffComponentTagAndGroup_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0100);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

// Test TiffEntryBase setValue
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffEntryBaseSetValue_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test TiffEntryBase setData
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffEntryBaseSetData_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    auto buf = std::make_shared<DataBuf>(4);
    std::memset(buf->data(), 0xAB, 4);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test TiffEntryBase offset setter/getter
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffEntryBaseOffsetSetGet_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), static_cast<size_t>(42));
}

// Test TiffDataEntryBase with different szTag and szGroup values
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffDataEntryBaseDifferentSzValues_1695) {
    TiffDataEntry entry(0x0202, IfdId::ifd1Id, 0x0203, IfdId::exifId);
    EXPECT_EQ(entry.szTag(), 0x0203);
    EXPECT_EQ(entry.szGroup(), IfdId::exifId);
    EXPECT_EQ(entry.tag(), 0x0202);
    EXPECT_EQ(entry.group(), IfdId::ifd1Id);
}

// Test TiffReader setMnState changes byte order
TEST_F(TiffReaderReadDataEntryBaseTest_1695, SetMnStateChangesByteOrder_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);

    TiffRwState mnState(bigEndian, 0);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test TiffReader with zero-sized data
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffReaderZeroSizeData_1695) {
    byte data[1] = {0};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, 0, &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), static_cast<size_t>(0));
}

// Test multiple nextIdx calls for same group
TEST_F(TiffReaderReadDataEntryBaseTest_1695, NextIdxMultipleCalls_1695) {
    byte data[64] = {};
    TiffEntry root(0x0000, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 0);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 1);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 2);
    EXPECT_EQ(reader.nextIdx(IfdId::ifd0Id), 3);
}

// Test TiffFinder with matching entry finds it
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffFinderFindMatchingEntry_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    entry.accept(finder);
    EXPECT_NE(finder.result(), nullptr);
    EXPECT_EQ(finder.result()->tag(), 0x0100);
    EXPECT_EQ(finder.result()->group(), IfdId::ifd0Id);
}

// Test TiffFinder with non-matching entry does not find it
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffFinderDoesNotFindNonMatchingEntry_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffFinder finder(0x0101, IfdId::ifd0Id);
    entry.accept(finder);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffFinder with wrong group does not find entry
TEST_F(TiffReaderReadDataEntryBaseTest_1695, TiffFinderWrongGroupDoesNotFind_1695) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffFinder finder(0x0100, IfdId::ifd1Id);
    entry.accept(finder);
    EXPECT_EQ(finder.result(), nullptr);
}
