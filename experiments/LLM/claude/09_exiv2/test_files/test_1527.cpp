#include <gtest/gtest.h>
#include <memory>
#include <cstdint>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewSamsungMn2Test_1527 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that newSamsungMn2 returns a non-null pointer
TEST_F(NewSamsungMn2Test_1527, ReturnsNonNullPointer_1527) {
    auto result = newSamsungMn2(0x0001, IfdId::ifd0Id, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
}

// Test that newSamsungMn2 creates a TiffIfdMakernote with the correct tag
TEST_F(NewSamsungMn2Test_1527, CorrectTag_1527) {
    uint16_t expectedTag = 0x927c;
    auto result = newSamsungMn2(expectedTag, IfdId::ifd0Id, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with tag value of 0
TEST_F(NewSamsungMn2Test_1527, TagZero_1527) {
    auto result = newSamsungMn2(0x0000, IfdId::ifd0Id, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewSamsungMn2Test_1527, TagMaxValue_1527) {
    auto result = newSamsungMn2(0xFFFF, IfdId::ifd0Id, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with typical MakerNote tag 0x927c
TEST_F(NewSamsungMn2Test_1527, TypicalMakerNoteTag_1527) {
    auto result = newSamsungMn2(0x927c, IfdId::exifId, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927c);
}

// Test with different group parameter
TEST_F(NewSamsungMn2Test_1527, DifferentGroupParameter_1527) {
    auto result = newSamsungMn2(0x927c, IfdId::exifId, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls create independent objects
TEST_F(NewSamsungMn2Test_1527, MultipleCallsCreateIndependentObjects_1527) {
    auto result1 = newSamsungMn2(0x0001, IfdId::ifd0Id, IfdId::samsung2Id);
    auto result2 = newSamsungMn2(0x0002, IfdId::ifd0Id, IfdId::samsung2Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test that the returned object is a valid TiffIfdMakernote
TEST_F(NewSamsungMn2Test_1527, ReturnedObjectIsValid_1527) {
    auto result = newSamsungMn2(0x927c, IfdId::exifId, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    // The object should be a valid TiffIfdMakernote and accessible
    // Verify by checking the tag is correctly stored
    EXPECT_EQ(result->tag(), 0x927c);
}

// Test with ifd1Id group
TEST_F(NewSamsungMn2Test_1527, Ifd1IdGroup_1527) {
    auto result = newSamsungMn2(0x927c, IfdId::ifd1Id, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927c);
}

// Test ownership transfer - unique_ptr should be movable
TEST_F(NewSamsungMn2Test_1527, OwnershipTransfer_1527) {
    auto result = newSamsungMn2(0x927c, IfdId::exifId, IfdId::samsung2Id);
    ASSERT_NE(result, nullptr);
    
    std::unique_ptr<TiffIfdMakernote> moved = std::move(result);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(result, nullptr);  // NOLINT - testing moved-from state
    EXPECT_EQ(moved->tag(), 0x927c);
}
