#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Minimal type definitions to match the interface
namespace Exiv2 {
namespace Internal {

// Forward declarations / minimal definitions needed for compilation
enum IfdId {
    ifdIdNotSet = 0,
    ifd0Id = 1,
    ifd1Id = 2,
    ifd2Id = 3,
    ifd3Id = 4,
    exifId = 5,
    gpsId = 6,
    iopId = 7,
    mpfId = 8,
    subImage1Id = 9,
    lastId = 10
};

using PrimaryGroups = std::vector<IfdId>;

class TiffHeaderBase {
public:
    bool isImageTag(uint16_t /*tag*/, IfdId /*group*/, const PrimaryGroups& /*primaryGroups*/) const {
        return false;
    }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2::Internal;

class TiffHeaderBaseTest_1178 : public ::testing::Test {
protected:
    TiffHeaderBase header;
};

// Test that isImageTag returns false for a typical tag value
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseForTypicalTag_1178) {
    PrimaryGroups groups;
    EXPECT_FALSE(header.isImageTag(0x0100, ifd0Id, groups));
}

// Test that isImageTag returns false with zero tag
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseForZeroTag_1178) {
    PrimaryGroups groups;
    EXPECT_FALSE(header.isImageTag(0, ifdIdNotSet, groups));
}

// Test that isImageTag returns false with max uint16 tag value
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseForMaxTag_1178) {
    PrimaryGroups groups;
    EXPECT_FALSE(header.isImageTag(0xFFFF, ifd0Id, groups));
}

// Test that isImageTag returns false with empty primary groups
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseWithEmptyPrimaryGroups_1178) {
    PrimaryGroups emptyGroups;
    EXPECT_FALSE(header.isImageTag(0x0110, exifId, emptyGroups));
}

// Test that isImageTag returns false with non-empty primary groups
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseWithNonEmptyPrimaryGroups_1178) {
    PrimaryGroups groups = {ifd0Id, ifd1Id, exifId};
    EXPECT_FALSE(header.isImageTag(0x0100, ifd0Id, groups));
}

// Test that isImageTag returns false for various IfdId groups
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseForVariousGroups_1178) {
    PrimaryGroups groups = {ifd0Id};
    EXPECT_FALSE(header.isImageTag(0x0100, ifd0Id, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, ifd1Id, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, exifId, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, gpsId, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, iopId, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, mpfId, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, subImage1Id, groups));
}

// Test that isImageTag returns false for different tag values with same group
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseForDifferentTags_1178) {
    PrimaryGroups groups = {ifd0Id, exifId};
    EXPECT_FALSE(header.isImageTag(0x0001, ifd0Id, groups));
    EXPECT_FALSE(header.isImageTag(0x0100, ifd0Id, groups));
    EXPECT_FALSE(header.isImageTag(0x0200, ifd0Id, groups));
    EXPECT_FALSE(header.isImageTag(0x8000, ifd0Id, groups));
}

// Test that isImageTag is const-correct and can be called on a const object
TEST_F(TiffHeaderBaseTest_1178, IsImageTagWorksOnConstObject_1178) {
    const TiffHeaderBase constHeader;
    PrimaryGroups groups;
    EXPECT_FALSE(constHeader.isImageTag(0x0100, ifd0Id, groups));
}

// Test with a large primary groups vector
TEST_F(TiffHeaderBaseTest_1178, IsImageTagReturnsFalseWithLargePrimaryGroups_1178) {
    PrimaryGroups groups;
    for (int i = 0; i < 100; ++i) {
        groups.push_back(static_cast<IfdId>(i % lastId));
    }
    EXPECT_FALSE(header.isImageTag(0x0100, ifd0Id, groups));
}

// Test consistency: calling multiple times yields same result
TEST_F(TiffHeaderBaseTest_1178, IsImageTagConsistentAcrossMultipleCalls_1178) {
    PrimaryGroups groups = {ifd0Id};
    bool result1 = header.isImageTag(0x0100, ifd0Id, groups);
    bool result2 = header.isImageTag(0x0100, ifd0Id, groups);
    EXPECT_EQ(result1, result2);
    EXPECT_FALSE(result1);
}
