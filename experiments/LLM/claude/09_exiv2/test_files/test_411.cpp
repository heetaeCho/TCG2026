#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Type alias for convenience
using TiffType = uint16_t;

class ToTypeIdTest_411 : public ::testing::Test {
protected:
};

// Test: Normal operation - a standard TIFF type maps directly to TypeId
TEST_F(ToTypeIdTest_411, UnsignedShortMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedShort), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedShort);
}

TEST_F(ToTypeIdTest_411, UnsignedLongMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedLong), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedLong);
}

TEST_F(ToTypeIdTest_411, SignedRationalMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(signedRational), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, signedRational);
}

TEST_F(ToTypeIdTest_411, AsciiStringMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(asciiString), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, asciiString);
}

TEST_F(ToTypeIdTest_411, UnsignedRationalMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedRational), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedRational);
}

TEST_F(ToTypeIdTest_411, SignedByteMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(signedByte), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, signedByte);
}

TEST_F(ToTypeIdTest_411, SignedShortMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(signedShort), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, signedShort);
}

TEST_F(ToTypeIdTest_411, SignedLongMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(signedLong), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, signedLong);
}

TEST_F(ToTypeIdTest_411, TiffFloatMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(tiffFloat), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, tiffFloat);
}

TEST_F(ToTypeIdTest_411, TiffDoubleMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(tiffDouble), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, tiffDouble);
}

TEST_F(ToTypeIdTest_411, TiffIfdMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(tiffIfd), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, tiffIfd);
}

// Test: Special case - tag 0x0002 in nikonAFTId group with unsignedByte maps to signedByte
TEST_F(ToTypeIdTest_411, NikonAFTTag0002UnsignedByteBecomesSignedByte_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0002, IfdId::nikonAFTId);
    EXPECT_EQ(result, signedByte);
}

// Test: Special case - tag 0x0047 in pentaxId group with unsignedByte maps to signedByte
TEST_F(ToTypeIdTest_411, PentaxTag0047UnsignedByteBecomesSignedByte_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0047, IfdId::pentaxId);
    EXPECT_EQ(result, signedByte);
}

// Test: Boundary - tag 0x0002 in nikonAFTId but NOT unsignedByte should remain unchanged
TEST_F(ToTypeIdTest_411, NikonAFTTag0002NonUnsignedByteUnchanged_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedShort), 0x0002, IfdId::nikonAFTId);
    EXPECT_EQ(result, unsignedShort);
}

// Test: Boundary - tag 0x0047 in pentaxId but NOT unsignedByte should remain unchanged
TEST_F(ToTypeIdTest_411, PentaxTag0047NonUnsignedByteUnchanged_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedShort), 0x0047, IfdId::pentaxId);
    EXPECT_EQ(result, unsignedShort);
}

// Test: Boundary - tag 0x0002 but NOT in nikonAFTId group, unsignedByte stays unsignedByte
TEST_F(ToTypeIdTest_411, Tag0002InOtherGroupUnsignedByteStays_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0002, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedByte);
}

// Test: Boundary - tag 0x0047 but NOT in pentaxId group, unsignedByte stays unsignedByte
TEST_F(ToTypeIdTest_411, Tag0047InOtherGroupUnsignedByteStays_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0047, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedByte);
}

// Test: undefined type for a random tag/group that has no comment TagInfo
TEST_F(ToTypeIdTest_411, UndefinedTypeForUnknownTagStaysUndefined_411) {
    // Using a tag/group combo that likely doesn't have a comment typeId in TagInfo
    TypeId result = toTypeId(static_cast<TiffType>(undefined), 0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(result, undefined);
}

// Test: undefined type for Exif UserComment tag (0x9286 in exifId) which should become comment
TEST_F(ToTypeIdTest_411, UndefinedTypeForUserCommentBecomesComment_411) {
    // Tag 0x9286 is UserComment in exifId - its typeId_ is comment
    TypeId result = toTypeId(static_cast<TiffType>(undefined), 0x9286, IfdId::exifId);
    EXPECT_EQ(result, comment);
}

// Test: Non-undefined type for UserComment tag should NOT trigger comment lookup
TEST_F(ToTypeIdTest_411, NonUndefinedTypeForUserCommentStaysOriginal_411) {
    // Even though tag 0x9286 in exifId has comment typeId, non-undefined tiffType
    // means pTag will be nullptr, so no comment override
    TypeId result = toTypeId(static_cast<TiffType>(asciiString), 0x9286, IfdId::exifId);
    EXPECT_EQ(result, asciiString);
}

// Test: unsignedByte type for a regular tag/group that doesn't match the special cases
TEST_F(ToTypeIdTest_411, UnsignedByteRegularTagUnchanged_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedByte);
}

// Test: Tag 0x0002 in pentaxId with unsignedByte should NOT become signedByte
// (only nikonAFTId matches for tag 0x0002)
TEST_F(ToTypeIdTest_411, Tag0002InPentaxIdUnsignedByteStays_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0002, IfdId::pentaxId);
    // This should remain unsignedByte unless pentax tag 0x0002 happens to have special handling
    // Based on the code, only (0x0002, nikonAFTId) and (0x0047, pentaxId) are special
    EXPECT_EQ(result, unsignedByte);
}

// Test: Tag 0x0047 in nikonAFTId with unsignedByte should NOT become signedByte
// (only pentaxId matches for tag 0x0047)
TEST_F(ToTypeIdTest_411, Tag0047InNikonAFTIdUnsignedByteStays_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0047, IfdId::nikonAFTId);
    EXPECT_EQ(result, unsignedByte);
}

// Test: Both special case conditions checked - signedByte type for nikonAFTId tag 0x0002
// should remain signedByte (since it's not unsignedByte, the override doesn't apply)
TEST_F(ToTypeIdTest_411, NikonAFTTag0002SignedByteStaysSignedByte_411) {
    TypeId result = toTypeId(static_cast<TiffType>(signedByte), 0x0002, IfdId::nikonAFTId);
    EXPECT_EQ(result, signedByte);
}

// Test: TiffType 0 - edge case with zero value
TEST_F(ToTypeIdTest_411, TiffTypeZero_411) {
    TypeId result = toTypeId(static_cast<TiffType>(0), 0x0000, IfdId::ifdIdNotSet);
    EXPECT_EQ(result, static_cast<TypeId>(0));
}

// Test: UnsignedByte with ifdIdNotSet - no special handling should apply
TEST_F(ToTypeIdTest_411, UnsignedByteIfdIdNotSet_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedByte), 0x0002, IfdId::ifdIdNotSet);
    EXPECT_EQ(result, unsignedByte);
}

// Test: undefined type with tag 0 and ifdIdNotSet - should stay undefined
TEST_F(ToTypeIdTest_411, UndefinedTypeTag0IfdNotSet_411) {
    TypeId result = toTypeId(static_cast<TiffType>(undefined), 0x0000, IfdId::ifdIdNotSet);
    EXPECT_EQ(result, undefined);
}

// Test: UnsignedLongLong type maps correctly
TEST_F(ToTypeIdTest_411, UnsignedLongLongMapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(unsignedLongLong), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, unsignedLongLong);
}

// Test: tiffIfd8 type maps correctly
TEST_F(ToTypeIdTest_411, TiffIfd8MapsDirectly_411) {
    TypeId result = toTypeId(static_cast<TiffType>(tiffIfd8), 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(result, tiffIfd8);
}
