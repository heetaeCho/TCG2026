#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "error.hpp"

namespace Exiv2 {
namespace Internal {

// Forward declaration of the function under test
TiffType toTiffType(TypeId typeId);

class ToTiffTypeTest_412 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings/errors during tests to avoid noisy output
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        // Restore default log level
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test normal TIFF types that map directly
TEST_F(ToTiffTypeTest_412, UnsignedByteMapsCorrectly_412) {
    EXPECT_EQ(ttUnsignedByte, toTiffType(unsignedByte));
}

TEST_F(ToTiffTypeTest_412, AsciiStringMapsCorrectly_412) {
    EXPECT_EQ(ttAsciiString, toTiffType(asciiString));
}

TEST_F(ToTiffTypeTest_412, UnsignedShortMapsCorrectly_412) {
    EXPECT_EQ(ttUnsignedShort, toTiffType(unsignedShort));
}

TEST_F(ToTiffTypeTest_412, UnsignedLongMapsCorrectly_412) {
    EXPECT_EQ(ttUnsignedLong, toTiffType(unsignedLong));
}

TEST_F(ToTiffTypeTest_412, UnsignedRationalMapsCorrectly_412) {
    EXPECT_EQ(ttUnsignedRational, toTiffType(unsignedRational));
}

TEST_F(ToTiffTypeTest_412, SignedByteMapsCorrectly_412) {
    EXPECT_EQ(ttSignedByte, toTiffType(signedByte));
}

TEST_F(ToTiffTypeTest_412, UndefinedMapsCorrectly_412) {
    EXPECT_EQ(ttUndefined, toTiffType(undefined));
}

TEST_F(ToTiffTypeTest_412, SignedShortMapsCorrectly_412) {
    EXPECT_EQ(ttSignedShort, toTiffType(signedShort));
}

TEST_F(ToTiffTypeTest_412, SignedLongMapsCorrectly_412) {
    EXPECT_EQ(ttSignedLong, toTiffType(signedLong));
}

TEST_F(ToTiffTypeTest_412, SignedRationalMapsCorrectly_412) {
    EXPECT_EQ(ttSignedRational, toTiffType(signedRational));
}

TEST_F(ToTiffTypeTest_412, TiffFloatMapsCorrectly_412) {
    EXPECT_EQ(ttTiffFloat, toTiffType(tiffFloat));
}

TEST_F(ToTiffTypeTest_412, TiffDoubleMapsCorrectly_412) {
    EXPECT_EQ(ttTiffDouble, toTiffType(tiffDouble));
}

TEST_F(ToTiffTypeTest_412, TiffIfdMapsCorrectly_412) {
    EXPECT_EQ(ttTiffIfd, toTiffType(tiffIfd));
}

// Test types with values > 0xffff that should return ttUndefined
TEST_F(ToTiffTypeTest_412, StringTypeReturnsUndefined_412) {
    // string = 65536 = 0x10000, which is > 0xffff
    EXPECT_EQ(ttUndefined, toTiffType(string));
}

TEST_F(ToTiffTypeTest_412, DateTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(date));
}

TEST_F(ToTiffTypeTest_412, TimeTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(time));
}

TEST_F(ToTiffTypeTest_412, CommentTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(comment));
}

TEST_F(ToTiffTypeTest_412, DirectoryTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(directory));
}

TEST_F(ToTiffTypeTest_412, XmpTextTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(xmpText));
}

TEST_F(ToTiffTypeTest_412, XmpAltTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(xmpAlt));
}

TEST_F(ToTiffTypeTest_412, XmpBagTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(xmpBag));
}

TEST_F(ToTiffTypeTest_412, XmpSeqTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(xmpSeq));
}

TEST_F(ToTiffTypeTest_412, LangAltTypeReturnsUndefined_412) {
    EXPECT_EQ(ttUndefined, toTiffType(langAlt));
}

TEST_F(ToTiffTypeTest_412, InvalidTypeIdReturnsUndefined_412) {
    // invalidTypeId = 131070 = 0x1FFFE, which is > 0xffff
    EXPECT_EQ(ttUndefined, toTiffType(invalidTypeId));
}

TEST_F(ToTiffTypeTest_412, LastTypeIdReturnsUndefined_412) {
    // lastTypeId = 131071 = 0x1FFFF, which is > 0xffff
    EXPECT_EQ(ttUndefined, toTiffType(lastTypeId));
}

// Boundary condition: types at 0xffff boundary
// unsignedLongLong = 16, signedLongLong = 17, tiffIfd8 = 18 are within 0xffff range
TEST_F(ToTiffTypeTest_412, UnsignedLongLongMapsDirectly_412) {
    TiffType result = toTiffType(unsignedLongLong);
    EXPECT_EQ(static_cast<TiffType>(16), result);
}

TEST_F(ToTiffTypeTest_412, SignedLongLongMapsDirectly_412) {
    TiffType result = toTiffType(signedLongLong);
    EXPECT_EQ(static_cast<TiffType>(17), result);
}

TEST_F(ToTiffTypeTest_412, TiffIfd8MapsDirectly_412) {
    TiffType result = toTiffType(tiffIfd8);
    EXPECT_EQ(static_cast<TiffType>(18), result);
}

// Test boundary: exactly at 0xffff should still be valid (not > 0xffff)
TEST_F(ToTiffTypeTest_412, BoundaryExactly0xFFFF_412) {
    TypeId boundaryType = static_cast<TypeId>(0xffff);
    TiffType result = toTiffType(boundaryType);
    // 0xffff is NOT > 0xffff, so it should be cast directly
    EXPECT_EQ(static_cast<TiffType>(0xffff), result);
}

// Test boundary: 0x10000 should return ttUndefined
TEST_F(ToTiffTypeTest_412, BoundaryJustAbove0xFFFF_412) {
    TypeId aboveBoundary = static_cast<TypeId>(0x10000);
    EXPECT_EQ(ttUndefined, toTiffType(aboveBoundary));
}

// Test with zero value (not a standard type but within range)
TEST_F(ToTiffTypeTest_412, ZeroValueMapsDirectly_412) {
    TypeId zeroType = static_cast<TypeId>(0);
    TiffType result = toTiffType(zeroType);
    EXPECT_EQ(static_cast<TiffType>(0), result);
}

} // namespace Internal
} // namespace Exiv2
