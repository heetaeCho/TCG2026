// File: test_tags_int_print0x9202_1401.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags_int.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

namespace {

class Print0x9202Test_1401 : public ::testing::Test {
 protected:
  static std::string WrapParensValueString(const Exiv2::Value& v) {
    std::ostringstream tmp;
    tmp << "(" << v << ")";
    return tmp.str();
  }

  static std::string CallPrint(const Exiv2::Value& v, const Exiv2::ExifData* ed = nullptr) {
    std::ostringstream os;
    Exiv2::Internal::print0x9202(os, v, ed);
    return os.str();
  }
};

TEST_F(Print0x9202Test_1401, CountZero_WrapsValueInParentheses_1401) {
  Exiv2::RationalValue v;  // default-constructed => count() is expected to be 0
  const std::string out = CallPrint(v, nullptr);

  EXPECT_EQ(out, WrapParensValueString(v));
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Print0x9202Test_1401, DenominatorZero_WrapsValueInParenthesesIfRepresentable_1401) {
  Exiv2::RationalValue v;

  // Some builds may reject "1/0" parsing; if so, skip rather than invent internal behavior.
  try {
    v.read("1/0");
  } catch (...) {
    GTEST_SKIP() << "RationalValue::read(\"1/0\") not supported in this build; cannot create denom==0 case.";
  }

  ASSERT_GT(v.count(), 0U);

  const std::string out = CallPrint(v, nullptr);
  EXPECT_EQ(out, WrapParensValueString(v));
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Print0x9202Test_1401, NormalRational_FormatsAsFNumberString_1401) {
  Exiv2::RationalValue v;
  v.read("28/10");  // 2.8

  const std::string out = CallPrint(v, nullptr);

  // For non-empty values with non-zero rational denominator, observable behavior is an "F..." formatted string.
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.front(), '(');
  EXPECT_EQ(out.front(), 'F');

  // Common expected output for 2.8 with "{:.2g}" is "2.8" => "F2.8".
  EXPECT_EQ(out, "F2.8");
}

TEST_F(Print0x9202Test_1401, NormalRational_RoundsToTwoSignificantDigits_1401) {
  Exiv2::RationalValue v;
  v.read("141/100");  // 1.41 -> "{:.2g}" => "1.4"

  const std::string out = CallPrint(v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), 'F');
  EXPECT_EQ(out, "F1.4");
}

TEST_F(Print0x9202Test_1401, ExifDataPointerNullOrNonNull_DoesNotChangeOutputForSameValue_1401) {
  Exiv2::RationalValue v;
  v.read("4/1");  // 4

  Exiv2::ExifData ed;  // empty ExifData is sufficient for pointer non-null

  const std::string out_null = CallPrint(v, nullptr);
  const std::string out_nonnull = CallPrint(v, &ed);

  EXPECT_EQ(out_null, out_nonnull);
  EXPECT_EQ(out_null, "F4");
}

}  // namespace