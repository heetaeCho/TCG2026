// File: test_tags_int_print0x9201_1400.cpp
#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Forward declaration for the internal function under test (implemented in tags_int.cpp).
std::ostream& print0x9201(std::ostream& os, const Value& value, const ExifData*);
}  // namespace Exiv2::Internal

namespace {

class Print0x9201Test_1400 : public ::testing::Test {
 protected:
  static std::string StreamValue(const Exiv2::Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  static std::string Call(const Exiv2::Value& v) {
    std::ostringstream os;
    // ExifData* is unused by interface contract here; pass nullptr.
    Exiv2::Internal::print0x9201(os, v, nullptr);
    return os.str();
  }
};

TEST_F(Print0x9201Test_1400, FormatsValidHalfSecondRational_1400) {
  Exiv2::RationalValue v;
  ASSERT_NO_THROW(v.read("1/2"));

  const std::string out = Call(v);

  // Observable formatting properties (black-box): no parenthesized fallback for valid values,
  // and output ends with " s".
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.rfind(" s"), out.size() - 2) << out;
  EXPECT_EQ(out.find('('), std::string::npos) << out;
  EXPECT_EQ(out.find(')'), std::string::npos) << out;

  // Typical shutter-style formatting is fractional for 1/2s. If implementation changes,
  // this assertion will catch it.
  EXPECT_NE(out.find('/'), std::string::npos) << out;
}

TEST_F(Print0x9201Test_1400, FormatsValidOneSecondRational_1400) {
  Exiv2::RationalValue v;
  ASSERT_NO_THROW(v.read("1/1"));

  const std::string out = Call(v);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.rfind(" s"), out.size() - 2) << out;
  EXPECT_EQ(out.find('('), std::string::npos) << out;
  EXPECT_EQ(out.find(')'), std::string::npos) << out;

  // For whole seconds, output is commonly not a fraction.
  EXPECT_EQ(out.find('/'), std::string::npos) << out;
}

TEST_F(Print0x9201Test_1400, FallsBackToParenthesizedValueWhenDenominatorIsZero_1400) {
  Exiv2::RationalValue v;
  ASSERT_NO_THROW(v.read("1/0"));

  const std::string expected = "(" + StreamValue(v) + ")";
  const std::string out = Call(v);

  // Exact fallback formatting is observable and independent of internal shutter conversion.
  EXPECT_EQ(out, expected);
}

TEST_F(Print0x9201Test_1400, FallsBackToParenthesizedValueWhenValueIsNotOk_1400) {
  // Create a rational value and intentionally make it "not ok" by reading an invalid string.
  Exiv2::RationalValue v;
  ASSERT_NO_THROW(v.read("not_a_rational"));

  // We only assert behavior through the public interface:
  // when value.ok() is false, output is "(" << value << ")".
  const std::string expected = "(" + StreamValue(v) + ")";
  const std::string out = Call(v);

  EXPECT_EQ(out, expected);
}

TEST_F(Print0x9201Test_1400, WorksWithNegativeRationalInput_1400) {
  Exiv2::RationalValue v;
  ASSERT_NO_THROW(v.read("-1/2"));

  const std::string out = Call(v);

  // Observable formatting: should still be a duration string ending with " s",
  // and should not use fallback parentheses for valid values.
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.rfind(" s"), out.size() - 2) << out;
  EXPECT_EQ(out.find('('), std::string::npos) << out;
  EXPECT_EQ(out.find(')'), std::string::npos) << out;
}

}  // namespace