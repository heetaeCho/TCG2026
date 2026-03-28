#include <gtest/gtest.h>
#include <vector>

#include "tiffimage_int.hpp"
#include "tags.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// PrimaryGroups is typically a vector of IfdId
using PrimaryGroups = std::vector<IfdId>;

class TiffHeaderTest_1181 : public ::testing::Test {
protected:
    // Helper to create TiffHeader with hasImageTags = true
    std::unique_ptr<TiffHeader> createHeaderWithImageTags(ByteOrder bo = littleEndian) {
        return std::make_unique<TiffHeader>(bo, 8, true);
    }

    // Helper to create TiffHeader with hasImageTags = false
    std::unique_ptr<TiffHeader> createHeaderWithoutImageTags(ByteOrder bo = littleEndian) {
        return std::make_unique<TiffHeader>(bo, 8, false);
    }
};

// Test: When hasImageTags_ is false, isImageTag should always return false
TEST_F(TiffHeaderTest_1181, NoImageTags_ReturnsFalse_1181) {
    auto header = createHeaderWithoutImageTags();
    PrimaryGroups pg;
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::ifd0Id, pg));
}

// Test: When hasImageTags_ is false with non-empty PrimaryGroups, still returns false
TEST_F(TiffHeaderTest_1181, NoImageTags_NonEmptyPrimaryGroups_ReturnsFalse_1181) {
    auto header = createHeaderWithoutImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd1Id};
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::ifd0Id, pg));
}

// Test: hasImageTags is true, empty PrimaryGroups - delegates to isTiffImageTag
TEST_F(TiffHeaderTest_1181, HasImageTags_EmptyPrimaryGroups_DelegatesToIsTiffImageTag_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg; // empty
    // With empty PrimaryGroups, the method skips the primary group checks
    // and goes directly to isTiffImageTag. The result depends on isTiffImageTag.
    // We just verify it doesn't crash and returns a bool.
    bool result = header->isImageTag(0x0100, IfdId::ifd0Id, pg);
    // We can't assert the exact value without knowing isTiffImageTag behavior,
    // but for common TIFF image tags like ImageWidth (0x0100) in ifd0Id, it should be true
    (void)result; // At minimum, no crash
}

// Test: Group is not in PrimaryGroups - should return false
TEST_F(TiffHeaderTest_1181, GroupNotInPrimaryGroups_ReturnsFalse_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id}; // only ifd0Id
    // Use a group that is NOT in the primary groups list
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::exifId, pg));
}

// Test: Group is in PrimaryGroups and group != ifd0Id - should return true
TEST_F(TiffHeaderTest_1181, GroupInPrimaryGroupsNotIfd0_ReturnsTrue_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd1Id};
    // ifd1Id is in PrimaryGroups and is not ifd0Id, so should return true
    EXPECT_TRUE(header->isImageTag(0x0100, IfdId::ifd1Id, pg));
}

// Test: Group is ifd0Id and is in PrimaryGroups - delegates to isTiffImageTag
TEST_F(TiffHeaderTest_1181, GroupIsIfd0InPrimaryGroups_DelegatesToIsTiffImageTag_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd1Id};
    // ifd0Id is in PrimaryGroups and equals ifd0Id, so falls through to isTiffImageTag
    // ImageWidth (0x0100) in ifd0Id is typically a TIFF image tag
    bool result = header->isImageTag(0x0100, IfdId::ifd0Id, pg);
    // Should be determined by isTiffImageTag
    (void)result;
}

// Test: SubImage group in PrimaryGroups (not ifd0Id) returns true
TEST_F(TiffHeaderTest_1181, SubImageGroupInPrimaryGroups_ReturnsTrue_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::subImage1Id};
    EXPECT_TRUE(header->isImageTag(0x0100, IfdId::subImage1Id, pg));
}

// Test: Multiple groups in PrimaryGroups, group not found
TEST_F(TiffHeaderTest_1181, MultipleGroupsNotFound_ReturnsFalse_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd1Id, IfdId::subImage1Id};
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::gpsId, pg));
}

// Test: Tag 0 with various configurations
TEST_F(TiffHeaderTest_1181, ZeroTag_NoImageTags_ReturnsFalse_1181) {
    auto header = createHeaderWithoutImageTags();
    PrimaryGroups pg;
    EXPECT_FALSE(header->isImageTag(0, IfdId::ifd0Id, pg));
}

// Test: Tag 0 with hasImageTags and empty PrimaryGroups
TEST_F(TiffHeaderTest_1181, ZeroTag_HasImageTags_EmptyPG_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg;
    // Depends on isTiffImageTag for tag=0, group=ifd0Id
    bool result = header->isImageTag(0, IfdId::ifd0Id, pg);
    (void)result; // No crash expected
}

// Test: Non-ifd0 group in PrimaryGroups with various tags returns true
TEST_F(TiffHeaderTest_1181, Ifd2InPrimaryGroups_ReturnsTrue_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd2Id};
    EXPECT_TRUE(header->isImageTag(0xFFFF, IfdId::ifd2Id, pg));
}

// Test: PrimaryGroups with only ifd0Id, querying ifd0Id delegates to isTiffImageTag
TEST_F(TiffHeaderTest_1181, OnlyIfd0InPG_QueryIfd0_DelegatesToIsTiffImageTag_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id};
    // Should pass the primary groups check and fall through to isTiffImageTag
    bool result = header->isImageTag(0x0100, IfdId::ifd0Id, pg);
    (void)result;
}

// Test: Boundary - max uint16_t tag value
TEST_F(TiffHeaderTest_1181, MaxTagValue_NoImageTags_1181) {
    auto header = createHeaderWithoutImageTags();
    PrimaryGroups pg;
    EXPECT_FALSE(header->isImageTag(0xFFFF, IfdId::ifd0Id, pg));
}

// Test: Boundary - ifdIdNotSet group with empty PrimaryGroups
TEST_F(TiffHeaderTest_1181, IfdIdNotSet_EmptyPG_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg;
    // With empty PG, skips PG checks, goes to isTiffImageTag
    bool result = header->isImageTag(0x0100, IfdId::ifdIdNotSet, pg);
    (void)result;
}

// Test: Non-ifd0 group in PrimaryGroups returns true regardless of tag
TEST_F(TiffHeaderTest_1181, NonIfd0InPG_AnyTag_ReturnsTrue_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::ifd0Id, IfdId::ifd3Id};
    // For group ifd3Id (which is not ifd0Id but IS in PrimaryGroups), returns true
    EXPECT_TRUE(header->isImageTag(0x0000, IfdId::ifd3Id, pg));
    EXPECT_TRUE(header->isImageTag(0x1234, IfdId::ifd3Id, pg));
    EXPECT_TRUE(header->isImageTag(0xFFFF, IfdId::ifd3Id, pg));
}

// Test: ByteOrder variations don't affect isImageTag behavior when hasImageTags is false
TEST_F(TiffHeaderTest_1181, BigEndian_NoImageTags_ReturnsFalse_1181) {
    auto header = createHeaderWithoutImageTags(bigEndian);
    PrimaryGroups pg = {IfdId::ifd0Id};
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::ifd0Id, pg));
}

// Test: ByteOrder variations with hasImageTags true
TEST_F(TiffHeaderTest_1181, BigEndian_HasImageTags_GroupNotInPG_ReturnsFalse_1181) {
    auto header = std::make_unique<TiffHeader>(bigEndian, 8, true);
    PrimaryGroups pg = {IfdId::ifd0Id};
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::exifId, pg));
}

// Test: Single non-ifd0 entry in PrimaryGroups, query that entry
TEST_F(TiffHeaderTest_1181, SingleNonIfd0InPG_QueryIt_ReturnsTrue_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::subImage2Id};
    // subImage2Id is in PG and != ifd0Id, so returns true
    EXPECT_TRUE(header->isImageTag(0x0100, IfdId::subImage2Id, pg));
}

// Test: Single non-ifd0 entry in PrimaryGroups, query ifd0
TEST_F(TiffHeaderTest_1181, SingleNonIfd0InPG_QueryIfd0_ReturnsFalse_1181) {
    auto header = createHeaderWithImageTags();
    PrimaryGroups pg = {IfdId::subImage2Id};
    // ifd0Id is NOT in PG, so returns false
    EXPECT_FALSE(header->isImageTag(0x0100, IfdId::ifd0Id, pg));
}
