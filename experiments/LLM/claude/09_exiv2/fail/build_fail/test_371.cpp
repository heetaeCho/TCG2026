#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tiffvisitor_int.hpp"

#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffMnEntryTest_371 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<IoWrapper> createIoWrapper(BasicIo& io) {
        static const byte header[] = {0x00, 0x00};
        return std::make_unique<IoWrapper>(io, header, sizeof(header), nullptr);
    }
};

// Test that TiffMnEntry can be constructed with valid parameters
TEST_F(TiffMnEntryTest_371, Construction_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tag(), 0x927c);
    EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test write when mn_ is null (should delegate to TiffEntryBase::doWrite)
TEST_F(TiffMnEntryTest_371, WriteWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    // With no data set, TiffEntryBase::doWrite should return 0
    size_t result = entry.write(ioWrapper, bigEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test write with no data and little endian byte order
TEST_F(TiffMnEntryTest_371, WriteWithNullMnLittleEndian_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x49, 0x49};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = entry.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test size when mn_ is null and no data
TEST_F(TiffMnEntryTest_371, SizeWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.size(), 0u);
}

// Test count when mn_ is null and no data
TEST_F(TiffMnEntryTest_371, CountWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.count(), 0u);
}

// Test that tiffType is ttUndefined as set in constructor
TEST_F(TiffMnEntryTest_371, TiffTypeIsUndefined_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tiffType(), ttUndefined);
}

// Test write with different offset values when mn_ is null
TEST_F(TiffMnEntryTest_371, WriteWithVariousOffsets_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = entry.write(ioWrapper, bigEndian, 100, 200, 300, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test write with large offset values
TEST_F(TiffMnEntryTest_371, WriteWithLargeOffsets_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = entry.write(ioWrapper, bigEndian, SIZE_MAX, SIZE_MAX, SIZE_MAX, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test sizeData with null mn_
TEST_F(TiffMnEntryTest_371, SizeDataWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.sizeData(), 0u);
}

// Test sizeImage with null mn_
TEST_F(TiffMnEntryTest_371, SizeImageWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.sizeImage(), 0u);
}

// Test write with different tags
TEST_F(TiffMnEntryTest_371, WriteWithDifferentTag_371) {
    TiffMnEntry entry(0x0001, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = entry.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
    EXPECT_EQ(entry.tag(), 0x0001);
}

// Test that pData returns null when no data is set
TEST_F(TiffMnEntryTest_371, PDataNullInitially_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.pData(), nullptr);
}

// Test that pValue returns null when no value is set
TEST_F(TiffMnEntryTest_371, PValueNullInitially_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test that offset is zero initially
TEST_F(TiffMnEntryTest_371, OffsetZeroInitially_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.offset(), 0u);
}

// Test that imageIdx is not modified when nothing is written
TEST_F(TiffMnEntryTest_371, ImageIdxUnchangedOnEmptyWrite_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 42;
    entry.write(ioWrapper, bigEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(imageIdx, 42u);
}

// Test writeData when mn_ is null and no data
TEST_F(TiffMnEntryTest_371, WriteDataWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = entry.writeData(ioWrapper, bigEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0u);
}

// Test writeImage when mn_ is null
TEST_F(TiffMnEntryTest_371, WriteImageWithNullMn_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    MemIo memIo;
    const byte header[] = {0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t result = entry.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test with different IfdId groups
TEST_F(TiffMnEntryTest_371, DifferentGroups_371) {
    TiffMnEntry entry(0x927c, IfdId::ifd0Id, IfdId::nikonId);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x927c);
}

// Test start pointer is null initially
TEST_F(TiffMnEntryTest_371, StartNullInitially_371) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.start(), nullptr);
}
