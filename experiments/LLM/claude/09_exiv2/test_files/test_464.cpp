#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
// Since the class is in Internal namespace, we include necessary headers
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_464 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_note_;
  std::ostringstream os_;
};

// Helper to create a URationalValue with specific rational values
static Value::UniquePtr makeRationalValue(std::vector<std::pair<int32_t, int32_t>> rationals) {
  auto value = Value::create(unsignedRational);
  for (auto& [num, den] : rationals) {
    URational r = {static_cast<uint32_t>(num), static_cast<uint32_t>(den)};
    std::ostringstream ss;
    ss << num << "/" << den;
    if (&r != &rationals.back().first) {
      // We'll build the string differently
    }
  }
  // Build string representation
  std::string str;
  for (size_t i = 0; i < rationals.size(); ++i) {
    if (i > 0) str += " ";
    str += std::to_string(rationals[i].first) + "/" + std::to_string(rationals[i].second);
  }
  value->read(str);
  return value;
}

// Test: count != 4 should output raw value in parentheses
TEST_F(Nikon3MakerNoteTest_464, CountNotFour_OutputsRawValue_464) {
  // Create a value with only 3 rationals
  auto value = makeRationalValue({{18, 1}, {55, 1}, {35, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: first rational has denominator 0
TEST_F(Nikon3MakerNoteTest_464, FirstRationalDenominatorZero_OutputsRawValue_464) {
  auto value = makeRationalValue({{18, 0}, {55, 1}, {35, 10}, {56, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: second rational has denominator 0
TEST_F(Nikon3MakerNoteTest_464, SecondRationalDenominatorZero_OutputsRawValue_464) {
  auto value = makeRationalValue({{18, 1}, {55, 0}, {35, 10}, {56, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: different focal lengths (range lens) with different apertures
TEST_F(Nikon3MakerNoteTest_464, DifferentFocalAndAperture_464) {
  // 18-55mm F3.50-5.60
  auto value = makeRationalValue({{18, 1}, {55, 1}, {35, 10}, {56, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_THAT(result, ::testing::HasSubstr("18-55mm"));
  EXPECT_THAT(result, ::testing::HasSubstr("F"));
}

// Test: same focal lengths (prime lens) with same aperture
TEST_F(Nikon3MakerNoteTest_464, SameFocalSameAperture_464) {
  // 50mm F1.80
  auto value = makeRationalValue({{50, 1}, {50, 1}, {18, 10}, {18, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_THAT(result, ::testing::HasSubstr("50mm"));
  EXPECT_THAT(result, ::testing::HasSubstr("F"));
  // Should NOT contain a dash in focal part
  EXPECT_THAT(result, ::testing::Not(::testing::HasSubstr("-")));
}

// Test: same focal lengths but different apertures
TEST_F(Nikon3MakerNoteTest_464, SameFocalDifferentAperture_464) {
  auto value = makeRationalValue({{50, 1}, {50, 1}, {28, 10}, {56, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_THAT(result, ::testing::HasSubstr("50mm"));
  EXPECT_THAT(result, ::testing::HasSubstr("F"));
  // Aperture part should contain a dash for range
  EXPECT_THAT(result, ::testing::HasSubstr("-"));
}

// Test: different focal lengths but same aperture
TEST_F(Nikon3MakerNoteTest_464, DifferentFocalSameAperture_464) {
  auto value = makeRationalValue({{24, 1}, {70, 1}, {28, 10}, {28, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_THAT(result, ::testing::HasSubstr("24-70mm"));
  EXPECT_THAT(result, ::testing::HasSubstr("F2.80"));
}

// Test: count is 0 (empty value)
TEST_F(Nikon3MakerNoteTest_464, EmptyValue_OutputsRawValue_464) {
  auto value = Value::create(unsignedRational);
  value->read("");
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: count is 5 (more than 4)
TEST_F(Nikon3MakerNoteTest_464, CountMoreThanFour_OutputsRawValue_464) {
  auto value = makeRationalValue({{18, 1}, {55, 1}, {35, 10}, {56, 10}, {100, 1}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: both denominators zero
TEST_F(Nikon3MakerNoteTest_464, BothDenominatorsZero_OutputsRawValue_464) {
  auto value = makeRationalValue({{18, 0}, {55, 0}, {35, 10}, {56, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: return value is the same stream
TEST_F(Nikon3MakerNoteTest_464, ReturnsSameStream_464) {
  auto value = makeRationalValue({{50, 1}, {50, 1}, {18, 10}, {18, 10}});
  std::ostream& returned = maker_note_.print0x0084(os_, *value, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test: valid with count=1
TEST_F(Nikon3MakerNoteTest_464, CountOne_OutputsRawValue_464) {
  auto value = makeRationalValue({{50, 1}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: large focal length values
TEST_F(Nikon3MakerNoteTest_464, LargeFocalLengthValues_464) {
  auto value = makeRationalValue({{200, 1}, {600, 1}, {56, 10}, {63, 10}});
  maker_note_.print0x0084(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_THAT(result, ::testing::HasSubstr("200-600mm"));
  EXPECT_THAT(result, ::testing::HasSubstr("F"));
}
