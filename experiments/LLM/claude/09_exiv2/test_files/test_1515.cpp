#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

namespace Exiv2 {
namespace Internal {

// Test that newOMSystemMn2 returns a non-null pointer
TEST(NewOMSystemMn2Test_1515, ReturnsNonNullPointer_1515) {
    auto result = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
}

// Test with typical Makernote tag value
TEST(NewOMSystemMn2Test_1515, CreatesWithTypicalMakernoteTag_1515) {
    uint16_t tag = 0x927c;  // Common MakerNote tag
    auto result = newOMSystemMn2(tag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with zero tag value (boundary condition)
TEST(NewOMSystemMn2Test_1515, CreatesWithZeroTag_1515) {
    uint16_t tag = 0;
    auto result = newOMSystemMn2(tag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with maximum tag value (boundary condition)
TEST(NewOMSystemMn2Test_1515, CreatesWithMaxTag_1515) {
    uint16_t tag = 0xFFFF;
    auto result = newOMSystemMn2(tag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with different group IDs
TEST(NewOMSystemMn2Test_1515, CreatesWithDifferentGroupIds_1515) {
    auto result = newOMSystemMn2(0x927c, IfdId::exifId, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object is a unique pointer with proper ownership
TEST(NewOMSystemMn2Test_1515, ReturnsUniqueOwnership_1515) {
    auto result1 = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    auto result2 = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    // They should be different objects
    EXPECT_NE(result1.get(), result2.get());
}

// Test creating multiple instances doesn't interfere
TEST(NewOMSystemMn2Test_1515, MultipleInstancesAreIndependent_1515) {
    auto result1 = newOMSystemMn2(0x0001, IfdId::ifd0Id, IfdId::olympusId);
    auto result2 = newOMSystemMn2(0x0002, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test that the group is correctly assigned
TEST(NewOMSystemMn2Test_1515, GroupIsCorrectlyAssigned_1515) {
    auto result = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    // The mnGroup should be set as the maker note group
    // Verify through the public interface of TiffIfdMakernote
    EXPECT_EQ(result->mnGroup(), IfdId::olympusId);
}

// Test with different mnGroup
TEST(NewOMSystemMn2Test_1515, CreatesWithDifferentMnGroup_1515) {
    auto result = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
}

// Test object can be properly destroyed (no crash on destruction)
TEST(NewOMSystemMn2Test_1515, ObjectCanBeProperlyDestroyed_1515) {
    {
        auto result = newOMSystemMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
        ASSERT_NE(result, nullptr);
    }
    // If we reach here without crashing, destruction was successful
    SUCCEED();
}

}  // namespace Internal
}  // namespace Exiv2
