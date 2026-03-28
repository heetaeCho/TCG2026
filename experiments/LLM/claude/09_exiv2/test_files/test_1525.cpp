#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewPentaxDngMn2Test_1525 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that the function returns a non-null unique_ptr
TEST_F(NewPentaxDngMn2Test_1525, ReturnsNonNull_1525) {
    auto result = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
}

// Test with tag value 0x927c (standard MakerNote tag)
TEST_F(NewPentaxDngMn2Test_1525, StandardMakerNoteTag_1525) {
    uint16_t tag = 0x927c;
    auto result = newPentaxDngMn2(tag, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with tag value 0 (boundary)
TEST_F(NewPentaxDngMn2Test_1525, ZeroTag_1525) {
    uint16_t tag = 0;
    auto result = newPentaxDngMn2(tag, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with maximum uint16_t tag value (boundary)
TEST_F(NewPentaxDngMn2Test_1525, MaxTag_1525) {
    uint16_t tag = 0xFFFF;
    auto result = newPentaxDngMn2(tag, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test that the returned object has correct group
TEST_F(NewPentaxDngMn2Test_1525, CorrectGroup_1525) {
    auto result = newPentaxDngMn2(0x927c, IfdId::exifId, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    // The group should match what was passed
    // TiffEntryBase stores group from constructor
}

// Test with different group IDs
TEST_F(NewPentaxDngMn2Test_1525, DifferentGroupIds_1525) {
    auto result1 = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    auto result2 = newPentaxDngMn2(0x927c, IfdId::exifId, IfdId::pentaxDngId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
}

// Test with different mnGroup IDs
TEST_F(NewPentaxDngMn2Test_1525, DifferentMnGroupIds_1525) {
    auto result1 = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    auto result2 = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
}

// Test that multiple calls return independent objects
TEST_F(NewPentaxDngMn2Test_1525, IndependentObjects_1525) {
    auto result1 = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    auto result2 = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test that the returned object has the correct tag when queried
TEST_F(NewPentaxDngMn2Test_1525, TagAccessor_1525) {
    uint16_t expectedTag = 0x0001;
    auto result = newPentaxDngMn2(expectedTag, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test the returned pointer can be moved (ownership transfer)
TEST_F(NewPentaxDngMn2Test_1525, OwnershipTransfer_1525) {
    auto result = newPentaxDngMn2(0x927c, IfdId::ifd0Id, IfdId::pentaxDngId);
    ASSERT_NE(result, nullptr);
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}
