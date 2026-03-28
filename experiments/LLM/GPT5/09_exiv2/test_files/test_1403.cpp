// ============================================================================
// tests/test_tags_int_print0x9206_1403.cpp
// Unit tests for Exiv2::Internal::print0x9206
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags_int.hpp>
#include <exiv2/value.hpp>

#include <limits>
#include <sstream>
#include <string>

namespace {

class Print0x9206Test_1403 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeRationalValue(Exiv2::TypeId typeId, const std::string& text) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(typeId);
    EXPECT_NE(v.get(), nullptr);
    if (!v) return v;

    // Value::read() returns 0 on success for Exiv2 Value implementations.
    EXPECT_EQ(0, v->read(text));
    return v;
  }

  static std::string run(const Exiv2::Value& v) {
    std::ostringstream os;
    const std::ostream* before = &os;
    std::ostream& ret = Exiv2::Internal::print0x9206(os, v, nullptr);
    EXPECT_EQ(&ret, before);  // must return the same stream
    return os.str();
  }
};

}  // namespace

TEST_F(Print0x9206Test_1403, ReturnsUnknownWhenNumeratorIsZero_1403) {
  auto v = Print0x9206Test_1403::makeRationalValue(Exiv2::signedRational, "0/1");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = Print0x9206Test_1403::run(*v);
  EXPECT_EQ("Unknown", out);
}

TEST_F(Print0x9206Test_1403, ReturnsInfinityWhenNumeratorCastsToUint32Max_1403) {
  // Casting -1 to uint32_t yields UINT32_MAX, which should print "Infinity".
  auto v = Print0x9206Test_1403::makeRationalValue(Exiv2::signedRational, "-1/1");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = Print0x9206Test_1403::run(*v);
  EXPECT_EQ("Infinity", out);
}

TEST_F(Print0x9206Test_1403, FormatsMetersWithTwoDecimalsWhenDenominatorNonZero_1403) {
  auto v = Print0x9206Test_1403::makeRationalValue(Exiv2::unsignedRational, "1/2");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = Print0x9206Test_1403::run(*v);
  EXPECT_EQ("0.50 m", out);
}

TEST_F(Print0x9206Test_1403, RoundsToTwoDecimals_1403) {
  auto v = Print0x9206Test_1403::makeRationalValue(Exiv2::unsignedRational, "1/3");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = Print0x9206Test_1403::run(*v);
  EXPECT_EQ("0.33 m", out);
}

TEST_F(Print0x9206Test_1403, FallsBackToParenthesizedValueWhenDenominatorIsZero_1403) {
  auto v = Print0x9206Test_1403::makeRationalValue(Exiv2::signedRational, "5/0");
  ASSERT_NE(v.get(), nullptr);

  // Observable behavior: output is "(" + streamed Value + ")". Using Value::toString()
  // to build an expectation avoids relying on any internal formatting details beyond the
  // public interface.
  const std::string expected = "(" + v->toString() + ")";
  const std::string out = Print0x9206Test_1403::run(*v);
  EXPECT_EQ(expected, out);
}