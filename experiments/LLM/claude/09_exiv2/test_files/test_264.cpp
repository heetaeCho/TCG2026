#include <gtest/gtest.h>
#include <memory>

// Include necessary Exiv2 headers
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewTiffThumbSizeTest_264 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns a non-null unique pointer
TEST_F(NewTiffThumbSizeTest_264, ReturnsNonNullPointer_264) {
    auto result = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
}

// Test that returned object has the correct tag
TEST_F(NewTiffThumbSizeTest_264, ReturnedObjectHasCorrectTag_264) {
    const uint16_t testTag = 0x0202;
    auto result = newTiffThumbSize<0x0201, IfdId::ifd1Id>(testTag, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test that returned object has the correct group
TEST_F(NewTiffThumbSizeTest_264, ReturnedObjectHasCorrectGroup_264) {
    const IfdId testGroup = IfdId::ifd1Id;
    auto result = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, testGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), testGroup);
}

// Test with different tag and group values
TEST_F(NewTiffThumbSizeTest_264, DifferentTagAndGroup_264) {
    const uint16_t testTag = 0x0103;
    const IfdId testGroup = IfdId::ifd0Id;
    auto result = newTiffThumbSize<0x0100, IfdId::ifd0Id>(testTag, testGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
    EXPECT_EQ(result->group(), testGroup);
}

// Test with zero tag value
TEST_F(NewTiffThumbSizeTest_264, ZeroTagValue_264) {
    auto result = newTiffThumbSize<0x0000, IfdId::ifd1Id>(0x0000, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum uint16_t tag value
TEST_F(NewTiffThumbSizeTest_264, MaxTagValue_264) {
    const uint16_t maxTag = 0xFFFF;
    auto result = newTiffThumbSize<0xFFFF, IfdId::ifd1Id>(maxTag, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), maxTag);
}

// Test that multiple calls return distinct objects
TEST_F(NewTiffThumbSizeTest_264, MultipleCallsReturnDistinctObjects_264) {
    auto result1 = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
    auto result2 = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test with different template parameters
TEST_F(NewTiffThumbSizeTest_264, DifferentTemplateParameters_264) {
    auto result1 = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
    auto result2 = newTiffThumbSize<0x0100, IfdId::ifd0Id>(0x0202, IfdId::ifd1Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    // Both should have the same runtime tag
    EXPECT_EQ(result1->tag(), result2->tag());
}

// Test ownership transfer - unique_ptr can be moved
TEST_F(NewTiffThumbSizeTest_264, OwnershipTransfer_264) {
    auto result = newTiffThumbSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    TiffComponent::UniquePtr moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x0202);
}
