// TEST_ID 1112
// Unit tests for Exiv2::TypeInfo::typeName(TypeId)
//
// Constraints note:
// - Treat implementation as a black box.
// - Verify only observable behavior via the public interface.

#include <gtest/gtest.h>

#include <exiv2/types.hpp>

#include <utility>
#include <vector>

namespace {

class TypeInfoTypeNameTest_1112 : public ::testing::Test {
protected:
  Exiv2::TypeInfo ti_;
};

TEST_F(TypeInfoTypeNameTest_1112, ReturnsExpectedNames_ForKnownTypeIds_1112) {
  const std::vector<std::pair<Exiv2::TypeId, const char*>> kCases = {
      {Exiv2::invalidTypeId, "Invalid"},
      {Exiv2::unsignedByte, "Byte"},
      {Exiv2::asciiString, "Ascii"},
      {Exiv2::unsignedShort, "Short"},
      {Exiv2::unsignedLong, "Long"},
      {Exiv2::unsignedRational, "Rational"},
      {Exiv2::signedByte, "SByte"},
      {Exiv2::undefined, "Undefined"},
      {Exiv2::signedShort, "SShort"},
      {Exiv2::signedLong, "SLong"},
      {Exiv2::signedRational, "SRational"},
      {Exiv2::tiffFloat, "Float"},
      {Exiv2::tiffDouble, "Double"},
      {Exiv2::tiffIfd, "Ifd"},
      {Exiv2::string, "String"},
      {Exiv2::date, "Date"},
      {Exiv2::time, "Time"},
      {Exiv2::comment, "Comment"},
      {Exiv2::directory, "Directory"},
      {Exiv2::xmpText, "XmpText"},
      {Exiv2::xmpAlt, "XmpAlt"},
      {Exiv2::xmpBag, "XmpBag"},
      {Exiv2::xmpSeq, "XmpSeq"},
      {Exiv2::langAlt, "LangAlt"},
  };

  for (const auto& [typeId, expectedName] : kCases) {
    const char* got = ti_.typeName(typeId);  // works whether typeName is static or non-static
    ASSERT_NE(got, nullptr) << "Expected non-null for TypeId=" << static_cast<int>(typeId);
    EXPECT_STREQ(got, expectedName) << "Mismatch for TypeId=" << static_cast<int>(typeId);
  }
}

TEST_F(TypeInfoTypeNameTest_1112, ReturnsNonNull_ForInvalidTypeId_1112) {
  const char* got = ti_.typeName(Exiv2::invalidTypeId);
  ASSERT_NE(got, nullptr);
  EXPECT_STREQ(got, "Invalid");
}

TEST_F(TypeInfoTypeNameTest_1112, ReturnsNullptr_ForUnknownTypeId_1112) {
  // Use a value very unlikely to be present in the table.
  const Exiv2::TypeId unknown1 = static_cast<Exiv2::TypeId>(0x7fffffff);
  EXPECT_EQ(ti_.typeName(unknown1), nullptr);

  // Also try a small negative value (if the underlying enum allows it).
  const Exiv2::TypeId unknown2 = static_cast<Exiv2::TypeId>(-1);
  EXPECT_EQ(ti_.typeName(unknown2), nullptr);
}

TEST_F(TypeInfoTypeNameTest_1112, ReturnValueIsStableAcrossCalls_ForKnownTypeId_1112) {
  const char* first = ti_.typeName(Exiv2::unsignedLong);
  ASSERT_NE(first, nullptr);

  const char* second = ti_.typeName(Exiv2::unsignedLong);
  ASSERT_NE(second, nullptr);

  // Observable expectation: repeated calls yield the same name string.
  EXPECT_STREQ(first, "Long");
  EXPECT_STREQ(second, "Long");
}

}  // namespace