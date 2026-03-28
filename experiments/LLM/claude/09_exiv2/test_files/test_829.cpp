#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

namespace {

using namespace Exiv2;

// Test fixture for XmpValue static method xmpArrayType(TypeId)
class XmpValueArrayTypeTest_829 : public ::testing::Test {
protected:
};

// Test that xmpAlt TypeId maps to xaAlt
TEST_F(XmpValueArrayTypeTest_829, XmpAltTypeIdReturnsXaAlt_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(xmpAlt);
    EXPECT_EQ(XmpValue::xaAlt, result);
}

// Test that xmpBag TypeId maps to xaBag
TEST_F(XmpValueArrayTypeTest_829, XmpBagTypeIdReturnsXaBag_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(xmpBag);
    EXPECT_EQ(XmpValue::xaBag, result);
}

// Test that xmpSeq TypeId maps to xaSeq
TEST_F(XmpValueArrayTypeTest_829, XmpSeqTypeIdReturnsXaSeq_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(xmpSeq);
    EXPECT_EQ(XmpValue::xaSeq, result);
}

// Test that unsignedByte TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, UnsignedByteTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(unsignedByte);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that asciiString TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, AsciiStringTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(asciiString);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that unsignedShort TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, UnsignedShortTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(unsignedShort);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that unsignedLong TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, UnsignedLongTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(unsignedLong);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that unsignedRational TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, UnsignedRationalTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(unsignedRational);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that signedByte TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, SignedByteTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(signedByte);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that undefined TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, UndefinedTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(undefined);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that signedShort TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, SignedShortTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(signedShort);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that signedLong TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, SignedLongTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(signedLong);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that xmpText TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, XmpTextTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(xmpText);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that langAlt TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, LangAltTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(langAlt);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that string TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, StringTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(string);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that date TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, DateTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(date);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that time TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, TimeTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(time);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that comment TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, CommentTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(comment);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that directory TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, DirectoryTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(directory);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that invalidTypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, InvalidTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(invalidTypeId);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that tiffFloat TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, TiffFloatTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(tiffFloat);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that tiffDouble TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, TiffDoubleTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(tiffDouble);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that tiffIfd TypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, TiffIfdTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(tiffIfd);
    EXPECT_EQ(XmpValue::xaNone, result);
}

// Test that lastTypeId maps to xaNone (default case)
TEST_F(XmpValueArrayTypeTest_829, LastTypeIdReturnsXaNone_829) {
    XmpValue::XmpArrayType result = XmpValue::xmpArrayType(lastTypeId);
    EXPECT_EQ(XmpValue::xaNone, result);
}

}  // namespace
