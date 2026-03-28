#include <gtest/gtest.h>
#include <cstdint>

// Forward declarations and minimal type definitions needed to compile tests
// Based on the provided interface

namespace Exiv2 {

enum class IfdId {
    ifd0Id = 1,
    ifd1Id = 2,
    ifd2Id = 3,
    ifd3Id = 4,
    exifId = 5,
    gpsId = 6,
    iopId = 7,
    ifdIdNotSet = 0,
    subImage1Id = 8,
    subImage2Id = 9,
    subImage3Id = 10,
    subImage4Id = 11,
    panaRawId = 12,
};

using PrimaryGroups = std::vector<IfdId>;

// Declaration of the free function used by Cr2Header
bool isTiffImageTag(uint16_t tag, IfdId group);

namespace Internal {

class Cr2Header {
public:
    bool isImageTag(uint16_t tag, IfdId group, const PrimaryGroups& pPrimaryGroups) const {
        if (group == IfdId::ifd2Id || group == IfdId::ifd3Id)
            return true;
        return isTiffImageTag(tag, group);
    }
};

} // namespace Internal
} // namespace Exiv2

// We need to provide a definition for isTiffImageTag for linking purposes.
// Since we treat the implementation as a black box, we provide a minimal stub
// that returns a known value so we can test the routing logic of isImageTag.
// In a real test environment, this would link against the actual library.
namespace Exiv2 {
bool isTiffImageTag(uint16_t tag, IfdId group) {
    // Minimal stub: returns true for specific known TIFF image tag scenarios
    // Tag 0x0111 (StripOffsets) in ifd0Id is typically an image tag
    if (tag == 0x0111 && group == IfdId::ifd0Id)
        return true;
    // Tag 0x0117 (StripByteCounts) in ifd0Id
    if (tag == 0x0117 && group == IfdId::ifd0Id)
        return true;
    return false;
}
} // namespace Exiv2

class Cr2HeaderTest_1546 : public ::testing::Test {
protected:
    Exiv2::Internal::Cr2Header header;
    Exiv2::PrimaryGroups primaryGroups;
};

// Test that ifd2Id group always returns true regardless of tag
TEST_F(Cr2HeaderTest_1546, IsImageTag_Ifd2Group_ReturnsTrue_1546) {
    EXPECT_TRUE(header.isImageTag(0x0000, Exiv2::IfdId::ifd2Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0x0100, Exiv2::IfdId::ifd2Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0xFFFF, Exiv2::IfdId::ifd2Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0x0111, Exiv2::IfdId::ifd2Id, primaryGroups));
}

// Test that ifd3Id group always returns true regardless of tag
TEST_F(Cr2HeaderTest_1546, IsImageTag_Ifd3Group_ReturnsTrue_1546) {
    EXPECT_TRUE(header.isImageTag(0x0000, Exiv2::IfdId::ifd3Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0x0100, Exiv2::IfdId::ifd3Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0xFFFF, Exiv2::IfdId::ifd3Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(0x0111, Exiv2::IfdId::ifd3Id, primaryGroups));
}

// Test that for non-ifd2/ifd3 groups, result depends on isTiffImageTag
TEST_F(Cr2HeaderTest_1546, IsImageTag_Ifd0Group_DelegatesToTiffImageTag_1546) {
    // Tag 0x0111 in ifd0Id should be recognized as image tag by isTiffImageTag stub
    EXPECT_TRUE(header.isImageTag(0x0111, Exiv2::IfdId::ifd0Id, primaryGroups));
    // Tag 0x0117 in ifd0Id should be recognized as image tag by isTiffImageTag stub
    EXPECT_TRUE(header.isImageTag(0x0117, Exiv2::IfdId::ifd0Id, primaryGroups));
}

// Test that non-image tags in non-special groups return false
TEST_F(Cr2HeaderTest_1546, IsImageTag_Ifd0Group_NonImageTag_ReturnsFalse_1546) {
    EXPECT_FALSE(header.isImageTag(0x0100, Exiv2::IfdId::ifd0Id, primaryGroups));
    EXPECT_FALSE(header.isImageTag(0x0000, Exiv2::IfdId::ifd0Id, primaryGroups));
}

// Test with ifd1Id group (not ifd2 or ifd3, so delegates to isTiffImageTag)
TEST_F(Cr2HeaderTest_1546, IsImageTag_Ifd1Group_ReturnsFalse_1546) {
    EXPECT_FALSE(header.isImageTag(0x0100, Exiv2::IfdId::ifd1Id, primaryGroups));
    EXPECT_FALSE(header.isImageTag(0x0000, Exiv2::IfdId::ifd1Id, primaryGroups));
}

// Test with exifId group
TEST_F(Cr2HeaderTest_1546, IsImageTag_ExifGroup_ReturnsFalse_1546) {
    EXPECT_FALSE(header.isImageTag(0x0100, Exiv2::IfdId::exifId, primaryGroups));
    EXPECT_FALSE(header.isImageTag(0x0111, Exiv2::IfdId::exifId, primaryGroups));
}

// Test with gpsId group
TEST_F(Cr2HeaderTest_1546, IsImageTag_GpsGroup_ReturnsFalse_1546) {
    EXPECT_FALSE(header.isImageTag(0x0100, Exiv2::IfdId::gpsId, primaryGroups));
}

// Test boundary tag values with ifd2Id
TEST_F(Cr2HeaderTest_1546, IsImageTag_BoundaryTagValues_Ifd2_1546) {
    EXPECT_TRUE(header.isImageTag(0, Exiv2::IfdId::ifd2Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(UINT16_MAX, Exiv2::IfdId::ifd2Id, primaryGroups));
}

// Test boundary tag values with ifd3Id
TEST_F(Cr2HeaderTest_1546, IsImageTag_BoundaryTagValues_Ifd3_1546) {
    EXPECT_TRUE(header.isImageTag(0, Exiv2::IfdId::ifd3Id, primaryGroups));
    EXPECT_TRUE(header.isImageTag(UINT16_MAX, Exiv2::IfdId::ifd3Id, primaryGroups));
}

// Test with non-empty PrimaryGroups (should not affect result for ifd2/ifd3)
TEST_F(Cr2HeaderTest_1546, IsImageTag_NonEmptyPrimaryGroups_Ifd2_1546) {
    Exiv2::PrimaryGroups pg = {Exiv2::IfdId::ifd0Id, Exiv2::IfdId::ifd1Id};
    EXPECT_TRUE(header.isImageTag(0x0100, Exiv2::IfdId::ifd2Id, pg));
}

// Test with non-empty PrimaryGroups for non-special group
TEST_F(Cr2HeaderTest_1546, IsImageTag_NonEmptyPrimaryGroups_Ifd0_1546) {
    Exiv2::PrimaryGroups pg = {Exiv2::IfdId::ifd0Id, Exiv2::IfdId::ifd1Id};
    // isTiffImageTag stub: 0x0111 in ifd0 returns true
    EXPECT_TRUE(header.isImageTag(0x0111, Exiv2::IfdId::ifd0Id, pg));
    // Unknown tag in ifd0 returns false
    EXPECT_FALSE(header.isImageTag(0x9999, Exiv2::IfdId::ifd0Id, pg));
}

// Test with ifdIdNotSet
TEST_F(Cr2HeaderTest_1546, IsImageTag_IfdIdNotSet_ReturnsFalse_1546) {
    EXPECT_FALSE(header.isImageTag(0x0111, Exiv2::IfdId::ifdIdNotSet, primaryGroups));
    EXPECT_FALSE(header.isImageTag(0x0000, Exiv2::IfdId::ifdIdNotSet, primaryGroups));
}

// Test multiple calls to ensure no state changes
TEST_F(Cr2HeaderTest_1546, IsImageTag_MultipleCallsConsistent_1546) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(header.isImageTag(0x0100, Exiv2::IfdId::ifd2Id, primaryGroups));
        EXPECT_TRUE(header.isImageTag(0x0100, Exiv2::IfdId::ifd3Id, primaryGroups));
        EXPECT_FALSE(header.isImageTag(0x0100, Exiv2::IfdId::ifd0Id, primaryGroups));
    }
}
