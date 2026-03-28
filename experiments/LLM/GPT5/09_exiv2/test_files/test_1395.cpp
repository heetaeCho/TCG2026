// =================================================================================================
//  TEST_ID: 1395
//  File: test_tags_int_print0x829a_1395.cpp
//  Unit tests for Exiv2::Internal::print0x829a()
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Forward declaration (implementation is in src/tags_int.cpp)
std::ostream& print0x829a(std::ostream& os, const Value& value, const ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0x829aTest_1395 : public ::testing::Test {
protected:
  static std::string Call(const Exiv2::Value& v) {
    std::ostringstream os;
    Exiv2::Internal::print0x829a(os, v, nullptr);
    return os.str();
  }

  static std::string StreamValue(const Exiv2::Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  static std::string StreamURational(const Exiv2::URational& r) {
    std::ostringstream os;
    os << r;
    return os.str();
  }
};

TEST_F(Print0x829aTest_1395, ReturnsStreamUnchangedWhenCountIsZero_1395) {
  Exiv2::AsciiValue v;  // count() == 0 by default
  const std::string out = Call(v);
  EXPECT_TRUE(out.empty());
}

TEST_F(Print0x829aTest_1395, WrapsNonUnsignedRationalValueInParentheses_1395) {
  Exiv2::AsciiValue v;
  ASSERT_EQ(0U, v.count());
  ASSERT_EQ(0, v.read("hello"));
  ASSERT_GT(v.count(), 0U);

  const std::string expected = "(" + StreamValue(v) + ")";
  const std::string out = Call(v);
  EXPECT_EQ(expected, out);
}

TEST_F(Print0x829aTest_1395, UnsignedRationalWithZeroNumeratorPrintsParenthesizedRational_1395) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("0/10"));
  ASSERT_GT(v.count(), 0U);
  ASSERT_EQ(Exiv2::unsignedRational, v.typeId());

  const Exiv2::URational r = v.toRational();
  const std::string expected = "(" + StreamURational(r) + ")";
  const std::string out = Call(v);
  EXPECT_EQ(expected, out);
}

TEST_F(Print0x829aTest_1395, UnsignedRationalWithZeroDenominatorPrintsParenthesizedRational_1395) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("10/0"));
  ASSERT_GT(v.count(), 0U);
  ASSERT_EQ(Exiv2::unsignedRational, v.typeId());

  const Exiv2::URational r = v.toRational();
  const std::string expected = "(" + StreamURational(r) + ")";
  const std::string out = Call(v);
  EXPECT_EQ(expected, out);
}

TEST_F(Print0x829aTest_1395, UnsignedRationalWithEqualNumeratorDenominatorPrintsOneSecond_1395) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("5/5"));
  ASSERT_GT(v.count(), 0U);
  ASSERT_EQ(Exiv2::unsignedRational, v.typeId());

  const std::string out = Call(v);
  EXPECT_EQ("1 s", out);
}

TEST_F(Print0x829aTest_1395, UnsignedRationalReducibleByDenominatorMultiplePrintsReducedRationalSeconds_1395) {
  // Choose values where denominator % numerator == 0 and both are non-zero.
  // Example: 2/10 -> expected output "1/5 s" (after reduction described by the function behavior).
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("2/10"));
  ASSERT_GT(v.count(), 0U);
  ASSERT_EQ(Exiv2::unsignedRational, v.typeId());

  const std::string out = Call(v);
  EXPECT_EQ("1/5 s", out);
}

TEST_F(Print0x829aTest_1395, UnsignedRationalNonReduciblePrintsFloatSeconds_1395) {
  // Example where denominator % numerator != 0 and neither is 0.
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("3/10"));
  ASSERT_GT(v.count(), 0U);
  ASSERT_EQ(Exiv2::unsignedRational, v.typeId());

  // Build expected using the same observable formatting behavior (default stream formatting).
  const Exiv2::URational r = v.toRational();
  std::ostringstream expected;
  expected << (static_cast<float>(r.first) / r.second) << " s";

  const std::string out = Call(v);
  EXPECT_EQ(expected.str(), out);
}

}  // namespace