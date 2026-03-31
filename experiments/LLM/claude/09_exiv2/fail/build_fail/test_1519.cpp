#include <gtest/gtest.h>
#include <memory>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewNikon2Mn2Test_1519 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that the function returns a non-null unique_ptr
TEST_F(NewNikon2Mn2Test_1519, ReturnsNonNull_1519) {
    auto result = newNikon2Mn2(0x0001, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
}

// Test with tag value of 0
TEST_F(NewNikon2Mn2Test_1519, TagZero_1519) {
    auto result = newNikon2Mn2(0x0000, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
}

// Test with maximum uint16_t tag value (boundary)
TEST_F(NewNikon2Mn2Test_1519, MaxTagValue_1519) {
    auto result = newNikon2Mn2(0xFFFF, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has correct tag
TEST_F(NewNikon2Mn2Test_1519, CorrectTag_1519) {
    uint16_t expectedTag = 0x927C;
    auto result = newNikon2Mn2(expectedTag, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with different group parameters
TEST_F(NewNikon2Mn2Test_1519, DifferentGroupParameters_1519) {
    auto result = newNikon2Mn2(0x0001, IfdId::exifId, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls create independent objects
TEST_F(NewNikon2Mn2Test_1519, MultipleCallsCreateIndependentObjects_1519) {
    auto result1 = newNikon2Mn2(0x0001, IfdId::ifd0Id, IfdId::nikon2Id);
    auto result2 = newNikon2Mn2(0x0002, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test with different tag values produce objects with different tags
TEST_F(NewNikon2Mn2Test_1519, DifferentTagsProduceDifferentObjects_1519) {
    auto result1 = newNikon2Mn2(0x0001, IfdId::ifd0Id, IfdId::nikon2Id);
    auto result2 = newNikon2Mn2(0x0002, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test with typical Nikon makernote tag (0x927C is standard MakerNote tag)
TEST_F(NewNikon2Mn2Test_1519, TypicalMakerNoteTag_1519) {
    auto result = newNikon2Mn2(0x927C, IfdId::exifId, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927C);
}

// Test that the unique_ptr can be moved without issues
TEST_F(NewNikon2Mn2Test_1519, MoveSemantics_1519) {
    auto result = newNikon2Mn2(0x0001, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
    auto moved = std::move(result);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with tag value 1 (boundary near min)
TEST_F(NewNikon2Mn2Test_1519, TagValueOne_1519) {
    auto result = newNikon2Mn2(1, IfdId::ifd0Id, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 1);
}
