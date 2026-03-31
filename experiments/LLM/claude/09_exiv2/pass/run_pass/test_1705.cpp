#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffFinder
class TiffFinderTest_1705 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that TiffFinder initialized with tag and group returns null when no match found
TEST_F(TiffFinderTest_1705, InitialResultIsNull_1705) {
    TiffFinder finder(0x010f, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffFinder init resets the finder state
TEST_F(TiffFinderTest_1705, InitResetsResult_1705) {
    TiffFinder finder(0x010f, IfdId::ifd0Id);
    finder.init(0x0110, IfdId::ifd1Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test fixture for TiffMnEntry
class TiffMnEntryTest_1705 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test TiffMnEntry construction
TEST_F(TiffMnEntryTest_1705, ConstructionSetsTagAndGroup_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.tag(), 0x927c);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test TiffMnEntry initial state - start should be null
TEST_F(TiffMnEntryTest_1705, InitialStartIsNull_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.start(), nullptr);
}

// Test TiffMnEntry pData returns null initially
TEST_F(TiffMnEntryTest_1705, InitialPDataIsNull_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test TiffMnEntry pValue returns null initially
TEST_F(TiffMnEntryTest_1705, InitialPValueIsNull_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test fixture for TiffEntryBase
class TiffEntryBaseTest_1705 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test TiffComponent setStart and start
TEST_F(TiffEntryBaseTest_1705, SetStartAndRetrieve_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    byte data[] = {0x01, 0x02, 0x03};
    entry.setStart(data);
    EXPECT_EQ(entry.start(), data);
}

// Test fixture for TiffReader
class TiffReaderTest_1705 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test TiffReader byteOrder returns the state's byte order
TEST_F(TiffReaderTest_1705, ByteOrderReturnsInitializedValue_1705) {
    // Minimal valid TIFF data - just enough to not crash
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);
}

// Test TiffReader with big endian byte order
TEST_F(TiffReaderTest_1705, ByteOrderBigEndian_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);
}

// Test TiffReader baseOffset
TEST_F(TiffReaderTest_1705, BaseOffsetReturnsInitializedValue_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test TiffReader circularReference with first call returns false
TEST_F(TiffReaderTest_1705, CircularReferenceFirstCallReturnsFalse_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
}

// Test TiffReader circularReference with same start and group returns true on second call
TEST_F(TiffReaderTest_1705, CircularReferenceSecondCallReturnsTrue_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
    EXPECT_TRUE(reader.circularReference(data, IfdId::ifd0Id));
}

// Test TiffReader circularReference with different groups returns false
TEST_F(TiffReaderTest_1705, CircularReferenceDifferentGroupReturnsFalse_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd0Id));
    EXPECT_FALSE(reader.circularReference(data, IfdId::ifd1Id));
}

// Test TiffReader nextIdx returns incrementing values for same group
TEST_F(TiffReaderTest_1705, NextIdxIncrementsForSameGroup_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx2, idx1 + 1);
}

// Test TiffReader nextIdx returns 0 for first call to a group
TEST_F(TiffReaderTest_1705, NextIdxStartsAtZero_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx, 0);
}

// Test TiffReader nextIdx for different groups are independent
TEST_F(TiffReaderTest_1705, NextIdxIndependentPerGroup_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx1_g1 = reader.nextIdx(IfdId::ifd0Id);
    int idx1_g2 = reader.nextIdx(IfdId::ifd1Id);
    EXPECT_EQ(idx1_g1, 0);
    EXPECT_EQ(idx1_g2, 0);
}

// Test TiffReader setOrigState restores original byte order
TEST_F(TiffReaderTest_1705, SetOrigStateRestoresByteOrder_1705) {
    byte data[64] = {};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), ByteOrder::bigEndian);
}

// Test TiffReader with zero-size data
TEST_F(TiffReaderTest_1705, ZeroSizeData_1705) {
    byte data[1] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(ByteOrder::littleEndian, 0);
    TiffReader reader(data, 0, &root, state);
    EXPECT_EQ(reader.byteOrder(), ByteOrder::littleEndian);
}

// Test TiffComponent tag and group accessors
class TiffComponentTest_1705 : public ::testing::Test {};

TEST_F(TiffComponentTest_1705, TagAccessor_1705) {
    TiffMnEntry entry(0x1234, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.tag(), 0x1234);
}

TEST_F(TiffComponentTest_1705, GroupAccessor_1705) {
    TiffMnEntry entry(0x1234, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test TiffEntryBase tiffType
TEST_F(TiffEntryBaseTest_1705, TiffTypeForMnEntry_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    // MnEntry is created with ttUndefined
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test TiffEntryBase offset - initially 0
TEST_F(TiffEntryBaseTest_1705, InitialOffsetIsZero_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test setOffset
TEST_F(TiffEntryBaseTest_1705, SetOffset_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    entry.setOffset(42);
    EXPECT_EQ(entry.offset(), 42u);
}

// Test TiffEntryBase setData with raw pointer
TEST_F(TiffEntryBaseTest_1705, SetDataWithRawPointer_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    auto storage = std::make_shared<DataBuf>(10);
    byte* ptr = storage->data();
    entry.setData(ptr, 10, storage);
    EXPECT_EQ(entry.pData(), ptr);
}

// Test TiffEntryBase setData with shared_ptr<DataBuf>
TEST_F(TiffEntryBaseTest_1705, SetDataWithSharedPtr_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    auto buf = std::make_shared<DataBuf>(16);
    entry.setData(buf);
    EXPECT_NE(entry.pData(), nullptr);
}

// Test setValue
TEST_F(TiffEntryBaseTest_1705, SetValueStoresValue_1705) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::mnId);
    auto value = Value::create(TypeId::asciiString);
    value->read("TestMaker");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
    EXPECT_EQ(entry.pValue()->toString(), "TestMaker");
}

// Test that findObject on TiffFinder with a matching entry sets the result
TEST_F(TiffFinderTest_1705, FindObjectSetsResult_1705) {
    TiffEntry entry(0x010f, IfdId::ifd0Id);
    TiffFinder finder(0x010f, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), &entry);
}

// Test that findObject on TiffFinder with non-matching entry doesn't set result
TEST_F(TiffFinderTest_1705, FindObjectNonMatchingDoesNotSetResult_1705) {
    TiffEntry entry(0x0110, IfdId::ifd0Id);
    TiffFinder finder(0x010f, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test findObject with matching tag but different group
TEST_F(TiffFinderTest_1705, FindObjectMatchingTagDifferentGroup_1705) {
    TiffEntry entry(0x010f, IfdId::ifd1Id);
    TiffFinder finder(0x010f, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}
