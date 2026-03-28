#include <gtest/gtest.h>
#include <memory>

#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewSony1Mn2Test_1531 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that newSony1Mn2 returns a non-null pointer
TEST_F(NewSony1Mn2Test_1531, ReturnsNonNullPointer_1531) {
    auto result = newSony1Mn2(0x0001, IfdId::ifd0Id, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewSony1Mn2Test_1531, HasCorrectTag_1531) {
    const uint16_t expectedTag = 0x927c;
    auto result = newSony1Mn2(expectedTag, IfdId::ifd0Id, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with tag value of zero
TEST_F(NewSony1Mn2Test_1531, TagZero_1531) {
    auto result = newSony1Mn2(0x0000, IfdId::ifd0Id, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewSony1Mn2Test_1531, MaxTagValue_1531) {
    auto result = newSony1Mn2(0xFFFF, IfdId::ifd0Id, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with typical MakerNote tag 0x927c
TEST_F(NewSony1Mn2Test_1531, TypicalMakerNoteTag_1531) {
    auto result = newSony1Mn2(0x927c, IfdId::exifId, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927c);
}

// Test that different group parameters create valid objects
TEST_F(NewSony1Mn2Test_1531, DifferentGroupParameters_1531) {
    auto result = newSony1Mn2(0x927c, IfdId::exifId, IfdId::sony2Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls produce independent objects
TEST_F(NewSony1Mn2Test_1531, MultipleCallsProduceIndependentObjects_1531) {
    auto result1 = newSony1Mn2(0x0001, IfdId::ifd0Id, IfdId::sony1Id);
    auto result2 = newSony1Mn2(0x0002, IfdId::ifd0Id, IfdId::sony1Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test the mnGroup is properly set
TEST_F(NewSony1Mn2Test_1531, MnGroupIsSet_1531) {
    auto result = newSony1Mn2(0x927c, IfdId::exifId, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->mnGroup(), IfdId::sony1Id);
}

// Test with sony2Id as mnGroup
TEST_F(NewSony1Mn2Test_1531, Sony2MnGroup_1531) {
    auto result = newSony1Mn2(0x927c, IfdId::exifId, IfdId::sony2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->mnGroup(), IfdId::sony2Id);
}

// Test that the unique_ptr ownership works correctly (move semantics)
TEST_F(NewSony1Mn2Test_1531, OwnershipTransfer_1531) {
    auto result = newSony1Mn2(0x927c, IfdId::exifId, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}
