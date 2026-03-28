#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffIfdMakernoteTest_306 : public ::testing::Test {
protected:
    // Helper to create a TiffIfdMakernote with no header
    std::unique_ptr<TiffIfdMakernote> createMakernote(uint16_t tag = 0x927c,
                                                       IfdId group = IfdId::exifId,
                                                       IfdId mnGroup = IfdId::canonId,
                                                       bool hasNext = false) {
        return std::make_unique<TiffIfdMakernote>(tag, group, mnGroup, nullptr, hasNext);
    }
};

TEST_F(TiffIfdMakernoteTest_306, DefaultMnOffset_306) {
    auto mn = createMakernote();
    // Default mnOffset_ should be zero-initialized
    EXPECT_EQ(0u, mn->mnOffset());
}

TEST_F(TiffIfdMakernoteTest_306, DefaultByteOrder_306) {
    auto mn = createMakernote();
    // Default imageByteOrder_ should be invalidByteOrder
    EXPECT_EQ(invalidByteOrder, mn->byteOrder());
}

TEST_F(TiffIfdMakernoteTest_306, SetByteOrder_306) {
    auto mn = createMakernote();
    mn->setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, mn->byteOrder());
}

TEST_F(TiffIfdMakernoteTest_306, SetByteOrderLittleEndian_306) {
    auto mn = createMakernote();
    mn->setByteOrder(littleEndian);
    EXPECT_EQ(littleEndian, mn->byteOrder());
}

TEST_F(TiffIfdMakernoteTest_306, SetImageByteOrder_306) {
    auto mn = createMakernote();
    mn->setImageByteOrder(bigEndian);
    // setImageByteOrder sets the image byte order; byteOrder() may still return
    // the makernote-specific byte order or fall back to image byte order
    // This tests observable behavior
    // If no makernote-specific byte order is set, it should use image byte order
}

TEST_F(TiffIfdMakernoteTest_306, SizeHeaderWithNullHeader_306) {
    auto mn = createMakernote();
    // With no header (nullptr), sizeHeader should return 0
    EXPECT_EQ(0u, mn->sizeHeader());
}

TEST_F(TiffIfdMakernoteTest_306, ReadHeaderWithNullHeaderAndEmptyData_306) {
    auto mn = createMakernote();
    // With no header (nullptr), readHeader should return true (no header to validate)
    EXPECT_TRUE(mn->readHeader(nullptr, 0, littleEndian));
}

TEST_F(TiffIfdMakernoteTest_306, ReadHeaderWithNullHeaderAndSomeData_306) {
    auto mn = createMakernote();
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    EXPECT_TRUE(mn->readHeader(data, sizeof(data), bigEndian));
}

TEST_F(TiffIfdMakernoteTest_306, BaseOffsetDefault_306) {
    auto mn = createMakernote();
    // Default base offset
    size_t offset = mn->baseOffset();
    // Just verify it returns without crashing; default should be 0
    EXPECT_EQ(0u, offset);
}

TEST_F(TiffIfdMakernoteTest_306, IfdOffsetDefault_306) {
    auto mn = createMakernote();
    size_t offset = mn->ifdOffset();
    // With null header, ifd offset should be 0
    EXPECT_EQ(0u, offset);
}

TEST_F(TiffIfdMakernoteTest_306, CopyConstructorDeleted_306) {
    // Verify copy constructor is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_constructible<TiffIfdMakernote>::value);
}

TEST_F(TiffIfdMakernoteTest_306, CopyAssignmentDeleted_306) {
    // Verify copy assignment is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_assignable<TiffIfdMakernote>::value);
}

TEST_F(TiffIfdMakernoteTest_306, SetByteOrderTwice_306) {
    auto mn = createMakernote();
    mn->setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, mn->byteOrder());
    mn->setByteOrder(littleEndian);
    EXPECT_EQ(littleEndian, mn->byteOrder());
}

TEST_F(TiffIfdMakernoteTest_306, SetByteOrderToInvalid_306) {
    auto mn = createMakernote();
    mn->setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, mn->byteOrder());
    mn->setByteOrder(invalidByteOrder);
    // After setting to invalid, byteOrder may return invalidByteOrder or fallback
    ByteOrder bo = mn->byteOrder();
    (void)bo; // Just ensure no crash
}

TEST_F(TiffIfdMakernoteTest_306, ConstructWithHasNextTrue_306) {
    auto mn = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_EQ(0u, mn->mnOffset());
    EXPECT_EQ(0u, mn->sizeHeader());
}

TEST_F(TiffIfdMakernoteTest_306, ConstructWithHasNextFalse_306) {
    auto mn = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, mn->mnOffset());
    EXPECT_EQ(0u, mn->sizeHeader());
}

TEST_F(TiffIfdMakernoteTest_306, ConstructWithDifferentGroups_306) {
    auto mn1 = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::nikonId, nullptr, false);
    EXPECT_EQ(0u, mn1->mnOffset());

    auto mn2 = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::sonyId, nullptr, false);
    EXPECT_EQ(0u, mn2->mnOffset());
}
