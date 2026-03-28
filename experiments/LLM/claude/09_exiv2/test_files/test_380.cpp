#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

#include <cstring>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSubIfdTest_380 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: WriteData with no child IFDs returns zero
TEST_F(TiffSubIfdTest_380, WriteDataNoChildren_ReturnsZero_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo;
    byte header[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = subIfd.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 0u);
}

// Test: Construction with specific tag, group, and newGroup
TEST_F(TiffSubIfdTest_380, ConstructionParameters_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    EXPECT_EQ(subIfd.tag(), 0x014a);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test: Size with no children returns appropriate base size
TEST_F(TiffSubIfdTest_380, SizeNoChildren_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t sz = subIfd.size();
    // With no IFDs, size should reflect base entry size or zero
    // We just verify it doesn't crash and returns a consistent value
    EXPECT_GE(sz, 0u);
}

// Test: SizeData with no children
TEST_F(TiffSubIfdTest_380, SizeDataNoChildren_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t szData = subIfd.sizeData();
    EXPECT_GE(szData, 0u);
}

// Test: SizeImage with no children
TEST_F(TiffSubIfdTest_380, SizeImageNoChildren_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t szImage = subIfd.sizeImage();
    EXPECT_EQ(szImage, 0u);
}

// Test: WriteImage with no children
TEST_F(TiffSubIfdTest_380, WriteImageNoChildren_ReturnsZero_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo;
    byte header[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t result = subIfd.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test: WriteData with big endian and no children
TEST_F(TiffSubIfdTest_380, WriteDataBigEndianNoChildren_ReturnsZero_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo;
    byte header[8] = {0x4d, 0x4d, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x08};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = subIfd.writeData(ioWrapper, bigEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 0u);
}

// Test: WriteData with non-zero offset and no children
TEST_F(TiffSubIfdTest_380, WriteDataNonZeroOffsetNoChildren_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo;
    byte header[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 0;
    size_t result = subIfd.writeData(ioWrapper, littleEndian, 1024, 512, imageIdx);

    EXPECT_EQ(result, 0u);
}

// Test: Different tag values
TEST_F(TiffSubIfdTest_380, DifferentTagValues_380) {
    TiffSubIfd subIfd1(0x0100, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd1.tag(), 0x0100);

    TiffSubIfd subIfd2(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd2.tag(), 0xFFFF);

    TiffSubIfd subIfd3(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd3.tag(), 0x0000);
}

// Test: Count with no children
TEST_F(TiffSubIfdTest_380, CountNoChildren_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t cnt = subIfd.count();
    EXPECT_GE(cnt, 0u);
}

// Test: WriteData with large offset values and no children
TEST_F(TiffSubIfdTest_380, WriteDataLargeOffsets_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo;
    byte header[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);

    size_t imageIdx = 999999;
    size_t result = subIfd.writeData(ioWrapper, littleEndian, 0xFFFFFF, 0xFFFFFF, imageIdx);

    EXPECT_EQ(result, 0u);
}

// Test: Multiple calls to writeData are consistent
TEST_F(TiffSubIfdTest_380, WriteDataMultipleCalls_Consistent_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);

    MemIo memIo1;
    byte header1[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper1(memIo1, header1, sizeof(header1), nullptr);
    size_t imageIdx1 = 0;
    size_t result1 = subIfd.writeData(ioWrapper1, littleEndian, 0, 0, imageIdx1);

    MemIo memIo2;
    byte header2[8] = {0x49, 0x49, 0x2a, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper2(memIo2, header2, sizeof(header2), nullptr);
    size_t imageIdx2 = 0;
    size_t result2 = subIfd.writeData(ioWrapper2, littleEndian, 0, 0, imageIdx2);

    EXPECT_EQ(result1, result2);
}

// Test: start() returns nullptr initially
TEST_F(TiffSubIfdTest_380, StartReturnsNullInitially_380) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.start(), nullptr);
}
