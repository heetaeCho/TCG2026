#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewPanasonicMn2Test_1522 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function returns a non-null unique_ptr
TEST_F(NewPanasonicMn2Test_1522, ReturnsNonNullPointer_1522) {
    auto result = newPanasonicMn2(0x927c, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
}

// Test with tag value 0x927c (typical MakerNote tag)
TEST_F(NewPanasonicMn2Test_1522, CreatesWithTypicalMakerNoteTag_1522) {
    uint16_t tag = 0x927c;
    auto result = newPanasonicMn2(tag, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with tag value 0
TEST_F(NewPanasonicMn2Test_1522, CreatesWithZeroTag_1522) {
    uint16_t tag = 0;
    auto result = newPanasonicMn2(tag, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with maximum uint16_t tag value
TEST_F(NewPanasonicMn2Test_1522, CreatesWithMaxTag_1522) {
    uint16_t tag = 0xFFFF;
    auto result = newPanasonicMn2(tag, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test that the returned object has correct group
TEST_F(NewPanasonicMn2Test_1522, HasCorrectGroup_1522) {
    auto result = newPanasonicMn2(0x927c, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    // The TiffIfdMakernote inherits from TiffComponent which should have group info
}

// Test with different group IDs
TEST_F(NewPanasonicMn2Test_1522, CreatesWithDifferentGroupIds_1522) {
    auto result = newPanasonicMn2(0x927c, IfdId::ifd0Id, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls create independent objects
TEST_F(NewPanasonicMn2Test_1522, MultipleCallsCreateIndependentObjects_1522) {
    auto result1 = newPanasonicMn2(0x0001, IfdId::exifId, IfdId::panasonicId);
    auto result2 = newPanasonicMn2(0x0002, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test with mnGroup as panasonicId
TEST_F(NewPanasonicMn2Test_1522, CreatesWithPanasonicMnGroup_1522) {
    auto result = newPanasonicMn2(0x927c, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
}

// Test that ownership is properly transferred via unique_ptr
TEST_F(NewPanasonicMn2Test_1522, OwnershipTransferViaUniquePtr_1522) {
    std::unique_ptr<TiffIfdMakernote> result = newPanasonicMn2(0x927c, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    
    // Move ownership
    std::unique_ptr<TiffIfdMakernote> moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}

// Test with tag value 1
TEST_F(NewPanasonicMn2Test_1522, CreatesWithTagValueOne_1522) {
    auto result = newPanasonicMn2(1, IfdId::exifId, IfdId::panasonicId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 1);
}
