// File: test_print0x9204_1402.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Forward declaration (function is implemented in src/tags_int.cpp)
std::ostream& print0x9204(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
}  // namespace Exiv2::Internal

namespace {

std::unique_ptr<Exiv2::Value> MakeSignedRationalValueFromString(const std::string& s) {
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::signedRational));
  if (!v) return nullptr;
  // Using public interface only; if parsing fails in a given build, the test will surface it.
  v->read(s);
  return v;
}

std::string Print(const Exiv2::Value& v) {
  std::ostringstream os;
  Exiv2::Internal::print0x9204(os, v, nullptr);
  return os.str();
}

}  // namespace

// The TEST_ID is 1402

TEST(Print0x9204Test_1402, ZeroNumeratorPrintsZeroEV_1402) {
  auto v = MakeSignedRationalValueFromString("0/1");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "0 EV");
}

TEST(Print0x9204Test_1402, Int32MinNumeratorPrintsZeroEV_1402) {
  const auto min32 = std::numeric_limits<std::int32_t>::min();
  auto v = MakeSignedRationalValueFromString(std::to_string(min32) + "/1");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "0 EV");
}

TEST(Print0x9204Test_1402, NonPositiveDenominatorPrintsParenthesizedFraction_1402) {
  auto v = MakeSignedRationalValueFromString("1/-2");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "(1/-2)");
}

TEST(Print0x9204Test_1402, ZeroDenominatorPrintsParenthesizedFraction_1402) {
  auto v = MakeSignedRationalValueFromString("3/0");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "(3/0)");
}

TEST(Print0x9204Test_1402, PositiveRationalIsReducedAndShowsPlusSign_1402) {
  auto v = MakeSignedRationalValueFromString("2/4");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "+1/2 EV");
}

TEST(Print0x9204Test_1402, NegativeRationalIsReducedAndShowsMinusSign_1402) {
  auto v = MakeSignedRationalValueFromString("-2/4");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "-1/2 EV");
}

TEST(Print0x9204Test_1402, ReducedDenominatorOneOmitsSlashOne_1402) {
  auto v = MakeSignedRationalValueFromString("3/3");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "+1 EV");
}

TEST(Print0x9204Test_1402, AlreadyReducedKeepsDenominatorWhenNotOne_1402) {
  auto v = MakeSignedRationalValueFromString("7/9");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(Print(*v), "+7/9 EV");
}

TEST(Print0x9204Test_1402, AcceptsNullExifDataPointer_1402) {
  auto v = MakeSignedRationalValueFromString("1/2");
  ASSERT_NE(v, nullptr);

  std::ostringstream os;
  EXPECT_NO_THROW({ Exiv2::Internal::print0x9204(os, *v, nullptr); });
  EXPECT_EQ(os.str(), "+1/2 EV");
}