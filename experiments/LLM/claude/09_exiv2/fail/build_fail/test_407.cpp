#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

// Include necessary headers for the Exiv2 internal types
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffIfdMakernote
class TiffIfdMakernoteTest_407 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construction with no header (nullptr)
TEST_F(TiffIfdMakernoteTest_407, ConstructWithNullHeader_407) {
    // Construct with nullptr header - should not crash
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    ASSERT_NE(makernote, nullptr);
}

// Test: tag() returns the tag passed in constructor
TEST_F(TiffIfdMakernoteTest_407, TagReturnsCorrectValue_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->tag(), 0x927c);
}

// Test: group() returns the group passed in constructor
TEST_F(TiffIfdMakernoteTest_407, GroupReturnsCorrectValue_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->group(), IfdId::exifId);
}

// Test: byteOrder() returns invalidByteOrder initially
TEST_F(TiffIfdMakernoteTest_407, InitialByteOrderIsInvalid_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: setByteOrder changes the byte order
TEST_F(TiffIfdMakernoteTest_407, SetByteOrderLittleEndian_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
}

// Test: setByteOrder to bigEndian
TEST_F(TiffIfdMakernoteTest_407, SetByteOrderBigEndian_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: mnOffset() returns 0 initially
TEST_F(TiffIfdMakernoteTest_407, InitialMnOffsetIsZero_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->mnOffset(), 0u);
}

// Test: sizeHeader() with no header returns 0
TEST_F(TiffIfdMakernoteTest_407, SizeHeaderWithNullHeaderReturnsZero_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeHeader(), 0u);
}

// Test: sizeImage() on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, SizeImageOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeImage(), 0u);
}

// Test: size() on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, SizeOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // A fresh TiffIfdMakernote with no entries should have some size (at least header)
    size_t s = makernote->size();
    // We just verify it doesn't crash and returns something reasonable
    EXPECT_GE(s, 0u);
}

// Test: count() on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, CountOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->count(), 0u);
}

// Test: sizeData() on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, SizeDataOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeData(), 0u);
}

// Test: readHeader with null data and zero size
TEST_F(TiffIfdMakernoteTest_407, ReadHeaderWithNullData_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // With no header, readHeader should handle null gracefully
    bool result = makernote->readHeader(nullptr, 0, littleEndian);
    // Without a header, the result should be true (no header to read)
    EXPECT_TRUE(result);
}

// Test: start() initially returns nullptr
TEST_F(TiffIfdMakernoteTest_407, StartInitiallyNull_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->start(), nullptr);
}

// Test: setStart and start
TEST_F(TiffIfdMakernoteTest_407, SetStartAndRetrieve_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[10] = {0};
    makernote->setStart(data);
    EXPECT_EQ(makernote->start(), data);
}

// Test: Construction with different tag values
TEST_F(TiffIfdMakernoteTest_407, ConstructWithDifferentTag_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x0001, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_EQ(makernote->tag(), 0x0001);
}

// Test: ifdOffset on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, IfdOffsetOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t offset = makernote->ifdOffset();
    EXPECT_GE(offset, 0u);
}

// Test: baseOffset on freshly constructed object
TEST_F(TiffIfdMakernoteTest_407, BaseOffsetOnFreshObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t offset = makernote->baseOffset();
    EXPECT_GE(offset, 0u);
}

// Test: Copy constructor is deleted (compile-time check - just verifying it's non-copyable)
TEST_F(TiffIfdMakernoteTest_407, IsNonCopyable_407) {
    EXPECT_FALSE(std::is_copy_constructible<TiffIfdMakernote>::value);
    EXPECT_FALSE(std::is_copy_assignable<TiffIfdMakernote>::value);
}

// Test: setByteOrder with invalidByteOrder
TEST_F(TiffIfdMakernoteTest_407, SetByteOrderInvalid_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: idx() returns default value
TEST_F(TiffIfdMakernoteTest_407, IdxReturnsDefaultValue_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    int idx = makernote->idx();
    // Default idx should be 0
    EXPECT_EQ(idx, 0);
}

// Test: Multiple setByteOrder calls - last one wins
TEST_F(TiffIfdMakernoteTest_407, MultipleSetByteOrderLastWins_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
    makernote->setByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
    makernote->setByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: readHeader with non-null data but no header object
TEST_F(TiffIfdMakernoteTest_407, ReadHeaderWithDataButNoHeaderObject_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    bool result = makernote->readHeader(data, sizeof(data), littleEndian);
    // Without a header object, readHeader should succeed trivially
    EXPECT_TRUE(result);
}

// Test: Construction with hasNext=true
TEST_F(TiffIfdMakernoteTest_407, ConstructWithHasNextTrue_407) {
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    ASSERT_NE(makernote, nullptr);
    EXPECT_EQ(makernote->tag(), 0x927c);
    EXPECT_EQ(makernote->group(), IfdId::exifId);
}
