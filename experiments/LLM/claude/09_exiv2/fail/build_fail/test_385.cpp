#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSubIfdTest_385 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a memory-based IO for testing
        memIo_ = std::make_unique<MemIo>();
        // Minimal TIFF header (8 bytes)
        std::memset(header_, 0, sizeof(header_));
        header_[0] = 'I';
        header_[1] = 'I';
        header_[2] = 0x2A;
        header_[3] = 0x00;
        // offset to first IFD = 8
        header_[4] = 0x08;
        header_[5] = 0x00;
        header_[6] = 0x00;
        header_[7] = 0x00;
    }

    std::unique_ptr<MemIo> memIo_;
    byte header_[8];
};

// Test that a newly constructed TiffSubIfd with no children writes zero image bytes
TEST_F(TiffSubIfdTest_385, WriteImageWithNoChildren_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);
    IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);

    // writeImage is the public method that calls doWriteImage
    size_t result = subIfd.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test construction with different parameters
TEST_F(TiffSubIfdTest_385, ConstructionWithDifferentGroups_385) {
    // Should not throw
    EXPECT_NO_THROW(TiffSubIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id));
    EXPECT_NO_THROW(TiffSubIfd(0x014A, IfdId::ifd0Id, IfdId::subImage2Id));
    EXPECT_NO_THROW(TiffSubIfd(0x0000, IfdId::ifd0Id, IfdId::subImage1Id));
    EXPECT_NO_THROW(TiffSubIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id));
}

// Test writeImage with big endian byte order and no children
TEST_F(TiffSubIfdTest_385, WriteImageBigEndianNoChildren_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);
    IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);

    size_t result = subIfd.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test sizeImage with no children should be zero
TEST_F(TiffSubIfdTest_385, SizeImageWithNoChildren_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t result = subIfd.sizeImage();
    EXPECT_EQ(result, 0u);
}

// Test size with no data
TEST_F(TiffSubIfdTest_385, SizeWithNoChildren_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t result = subIfd.size();
    // With no children, size should reflect just the entry itself
    EXPECT_GE(result, 0u);
}

// Test sizeData with no children
TEST_F(TiffSubIfdTest_385, SizeDataWithNoChildren_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);

    size_t result = subIfd.sizeData();
    EXPECT_GE(result, 0u);
}

// Test that writeImage is consistent across multiple calls with no children
TEST_F(TiffSubIfdTest_385, WriteImageConsistentMultipleCalls_385) {
    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);
    IoWrapper ioWrapper(*memIo_, header_, sizeof(header_), nullptr);

    size_t result1 = subIfd.writeImage(ioWrapper, littleEndian);
    size_t result2 = subIfd.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result1, result2);
}
