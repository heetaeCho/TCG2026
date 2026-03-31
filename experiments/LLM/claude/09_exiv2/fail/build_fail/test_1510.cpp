#include <gtest/gtest.h>
#include <memory>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "exiv2/tags.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewIfdMn2Test_1510 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns a non-null unique_ptr
TEST_F(NewIfdMn2Test_1510, ReturnsNonNullPointer_1510) {
    auto result = newIfdMn2(0x0001, IfdId::ifd0Id, IfdId::canonId);
    ASSERT_NE(result, nullptr);
}

// Test with tag value of 0
TEST_F(NewIfdMn2Test_1510, TagZero_1510) {
    auto result = newIfdMn2(0x0000, IfdId::ifd0Id, IfdId::canonId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum uint16_t tag value
TEST_F(NewIfdMn2Test_1510, MaxTagValue_1510) {
    auto result = newIfdMn2(0xFFFF, IfdId::ifd0Id, IfdId::canonId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that the tag is correctly set
TEST_F(NewIfdMn2Test_1510, TagIsCorrectlySet_1510) {
    uint16_t testTag = 0x927C; // Common MakerNote tag
    auto result = newIfdMn2(testTag, IfdId::exifId, IfdId::nikonId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with different group IDs
TEST_F(NewIfdMn2Test_1510, DifferentGroupIds_1510) {
    auto result = newIfdMn2(0x0001, IfdId::exifId, IfdId::sonyId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0001);
}

// Test with the same group and mnGroup
TEST_F(NewIfdMn2Test_1510, SameGroupAndMnGroup_1510) {
    auto result = newIfdMn2(0x0010, IfdId::canonId, IfdId::canonId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0010);
}

// Test that the returned object is a valid TiffIfdMakernote
TEST_F(NewIfdMn2Test_1510, ReturnedObjectIsValidTiffIfdMakernote_1510) {
    auto result = newIfdMn2(0x927C, IfdId::exifId, IfdId::canonId);
    ASSERT_NE(result, nullptr);
    // The mnGroup should be set properly
    EXPECT_EQ(result->mnGroup(), IfdId::canonId);
}

// Test creating multiple instances independently
TEST_F(NewIfdMn2Test_1510, MultipleInstancesAreIndependent_1510) {
    auto result1 = newIfdMn2(0x0001, IfdId::ifd0Id, IfdId::canonId);
    auto result2 = newIfdMn2(0x0002, IfdId::exifId, IfdId::nikonId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test with typical MakerNote tag value 0x927C
TEST_F(NewIfdMn2Test_1510, TypicalMakerNoteTag_1510) {
    auto result = newIfdMn2(0x927C, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927C);
}

// Test ownership transfer via unique_ptr
TEST_F(NewIfdMn2Test_1510, OwnershipTransferViaUniquePtr_1510) {
    std::unique_ptr<TiffIfdMakernote> ptr;
    {
        ptr = newIfdMn2(0x0001, IfdId::ifd0Id, IfdId::canonId);
    }
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->tag(), 0x0001);
}
