// =================================================================================================
// Unit tests for Exiv2::Internal::print0x920a
// File: ./TestProjects/exiv2/src/tags_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "tags_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

std::string CallPrint0x920a(const Exiv2::Value& v, const Exiv2::ExifData* exif = nullptr) {
  std::ostringstream os;
  Exiv2::Internal::print0x920a(os, v, exif);
  return os.str();
}

}  // namespace

// NOTE: TEST_ID is 1406

TEST(Print0x920aTest_1406, FormatsMillimetersWhenDenominatorNonZero_1406) {
  auto v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("50/1"));

  const std::string out = CallPrint0x920a(*v, nullptr);
  EXPECT_EQ(out, "50.0 mm");
}

TEST(Print0x920aTest_1406, FormatsWithOneDecimalForNonIntegerResult_1406) {
  auto v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("123/2"));  // 61.5

  const std::string out = CallPrint0x920a(*v, nullptr);
  EXPECT_EQ(out, "61.5 mm");
}

TEST(Print0x920aTest_1406, RoundsToOneDecimalPlace_1406) {
  auto v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("1/3"));  // ~0.333..., should be 0.3 with 1 decimal

  const std::string out = CallPrint0x920a(*v, nullptr);
  EXPECT_EQ(out, "0.3 mm");
}

TEST(Print0x920aTest_1406, FallsBackToParenthesizedValueWhenNotRationalConvertible_1406) {
  // Use an ASCII value that (commonly) cannot be converted to a rational, so toRational()
  // is expected to yield a zero denominator and trigger the fallback branch.
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("not-a-rational"));

  const std::string out = CallPrint0x920a(*v, nullptr);

  // Black-box assertions: must be parenthesized and include the original textual value.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  EXPECT_NE(out.find("not-a-rational"), std::string::npos);
}

TEST(Print0x920aTest_1406, ReturnsSameOstreamReference_1406) {
  auto v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("35/1"));

  Exiv2::ExifData exif;  // Non-null pointer should be accepted (even if unused).
  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::print0x920a(os, *v, &exif);

  // Verify the returned reference is the same stream object.
  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "35.0 mm");
}