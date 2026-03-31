#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewNikon3Mn2Test_1520 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function returns a non-null pointer
TEST_F(NewNikon3Mn2Test_1520, ReturnsNonNullPointer_1520) {
    auto result = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewNikon3Mn2Test_1520, CorrectTag_1520) {
    uint16_t expectedTag = 0x927c;
    auto result = newNikon3Mn2(expectedTag, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with a different tag value
TEST_F(NewNikon3Mn2Test_1520, DifferentTagValue_1520) {
    uint16_t expectedTag = 0x0001;
    auto result = newNikon3Mn2(expectedTag, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with zero tag
TEST_F(NewNikon3Mn2Test_1520, ZeroTag_1520) {
    uint16_t expectedTag = 0x0000;
    auto result = newNikon3Mn2(expectedTag, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with maximum tag value
TEST_F(NewNikon3Mn2Test_1520, MaxTagValue_1520) {
    uint16_t expectedTag = 0xFFFF;
    auto result = newNikon3Mn2(expectedTag, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test that the returned object is of the expected type (TiffIfdMakernote)
TEST_F(NewNikon3Mn2Test_1520, ReturnTypeIsTiffIfdMakernote_1520) {
    auto result = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    // Verify it's a valid TiffIfdMakernote by calling a method on it
    TiffIfdMakernote* ptr = result.get();
    EXPECT_NE(ptr, nullptr);
}

// Test with different group parameters
TEST_F(NewNikon3Mn2Test_1520, DifferentGroupParameters_1520) {
    auto result = newNikon3Mn2(0x927c, IfdId::ifd0Id, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
}

// Test with different mnGroup parameters
TEST_F(NewNikon3Mn2Test_1520, DifferentMnGroupParameters_1520) {
    auto result = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon2Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls return distinct objects
TEST_F(NewNikon3Mn2Test_1520, MultipleCallsReturnDistinctObjects_1520) {
    auto result1 = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon3Id);
    auto result2 = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test ownership semantics - unique_ptr can be moved
TEST_F(NewNikon3Mn2Test_1520, OwnershipCanBeTransferred_1520) {
    auto result = newNikon3Mn2(0x927c, IfdId::exifId, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    EXPECT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}
