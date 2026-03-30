// File: test_typeinfo_typeid_1113.cpp
#include <gtest/gtest.h>

#include <string>

#include "exiv2/types.hpp"

namespace {

// Keep the fixture minimal; we treat TypeInfo as a black box.
class TypeInfoTest_1113 : public ::testing::Test {
 protected:
  Exiv2::TypeInfo ti_;
};

TEST_F(TypeInfoTest_1113, ReturnsExpectedIdForKnownCoreTypeNames_1113) {
  EXPECT_EQ(ti_.typeId("Byte"), Exiv2::unsignedByte);
  EXPECT_EQ(ti_.typeId("Ascii"), Exiv2::asciiString);
  EXPECT_EQ(ti_.typeId("Short"), Exiv2::unsignedShort);
  EXPECT_EQ(ti_.typeId("Long"), Exiv2::unsignedLong);
  EXPECT_EQ(ti_.typeId("Rational"), Exiv2::unsignedRational);
}

TEST_F(TypeInfoTest_1113, ReturnsExpectedIdForKnownSignedAndTiffNumericTypeNames_1113) {
  EXPECT_EQ(ti_.typeId("SByte"), Exiv2::signedByte);
  EXPECT_EQ(ti_.typeId("SShort"), Exiv2::signedShort);
  EXPECT_EQ(ti_.typeId("SLong"), Exiv2::signedLong);
  EXPECT_EQ(ti_.typeId("SRational"), Exiv2::signedRational);
  EXPECT_EQ(ti_.typeId("Float"), Exiv2::tiffFloat);
  EXPECT_EQ(ti_.typeId("Double"), Exiv2::tiffDouble);
  EXPECT_EQ(ti_.typeId("Ifd"), Exiv2::tiffIfd);
}

TEST_F(TypeInfoTest_1113, ReturnsExpectedIdForKnownXmpAndStringFamilyTypeNames_1113) {
  EXPECT_EQ(ti_.typeId("String"), Exiv2::string);
  EXPECT_EQ(ti_.typeId("Date"), Exiv2::date);
  EXPECT_EQ(ti_.typeId("Time"), Exiv2::time);
  EXPECT_EQ(ti_.typeId("Comment"), Exiv2::comment);
  EXPECT_EQ(ti_.typeId("Directory"), Exiv2::directory);

  EXPECT_EQ(ti_.typeId("XmpText"), Exiv2::xmpText);
  EXPECT_EQ(ti_.typeId("XmpAlt"), Exiv2::xmpAlt);
  EXPECT_EQ(ti_.typeId("XmpBag"), Exiv2::xmpBag);
  EXPECT_EQ(ti_.typeId("XmpSeq"), Exiv2::xmpSeq);
  EXPECT_EQ(ti_.typeId("LangAlt"), Exiv2::langAlt);
}

TEST_F(TypeInfoTest_1113, ReturnsInvalidTypeIdForUnknownTypeName_1113) {
  EXPECT_EQ(ti_.typeId("DoesNotExist"), Exiv2::invalidTypeId);
  EXPECT_EQ(ti_.typeId("UnsignedByte"), Exiv2::invalidTypeId);  // similar-but-not-same
  EXPECT_EQ(ti_.typeId("byte"), Exiv2::invalidTypeId);          // case variation
}

TEST_F(TypeInfoTest_1113, BoundaryInputsDoNotThrowAndReturnInvalidTypeId_1113) {
  EXPECT_NO_THROW({
    EXPECT_EQ(ti_.typeId(""), Exiv2::invalidTypeId);
    EXPECT_EQ(ti_.typeId(" "), Exiv2::invalidTypeId);
    EXPECT_EQ(ti_.typeId("  Byte"), Exiv2::invalidTypeId);
    EXPECT_EQ(ti_.typeId("Byte  "), Exiv2::invalidTypeId);
    EXPECT_EQ(ti_.typeId("Byte\0Junk", 9), Exiv2::invalidTypeId);  // embedded NUL in std::string
  });
}

TEST_F(TypeInfoTest_1113, RepeatedCallsAreConsistent_1113) {
  const auto a = ti_.typeId("Byte");
  const auto b = ti_.typeId("Byte");
  const auto c = ti_.typeId("Byte");
  EXPECT_EQ(a, Exiv2::unsignedByte);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

}  // namespace