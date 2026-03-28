// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 904
//
// Unit tests for Exiv2::Internal::OlympusMakerNote::print0x0529
// File under test: ./TestProjects/exiv2/src/olympusmn_int.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "./TestProjects/exiv2/src/olympusmn_int.hpp"

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::Internal::OlympusMakerNote;

static std::unique_ptr<Value> makeValueFromString(TypeId type, const std::string& s) {
  Value::UniquePtr v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  // Treat parsing as black-box; if read fails, we still keep the test robust by not assuming details.
  (void)v->read(s);
  return std::unique_ptr<Value>(v.release());
}

static std::string joinAsString(const std::vector<int64_t>& nums) {
  std::ostringstream oss;
  for (size_t i = 0; i < nums.size(); ++i) {
    if (i) oss << ' ';
    oss << nums[i];
  }
  return oss.str();
}

static std::unique_ptr<Value> makeUnsignedShortValue(const std::vector<int64_t>& nums) {
  return makeValueFromString(Exiv2::unsignedShort, joinAsString(nums));
}

static std::unique_ptr<Value> makeUnsignedLongValue(const std::vector<int64_t>& nums) {
  return makeValueFromString(Exiv2::unsignedLong, joinAsString(nums));
}

class OlympusMakerNotePrint0x0529Test_904 : public ::testing::Test {
 protected:
  OlympusMakerNote mn_;
  ExifData exif_;
};

TEST_F(OlympusMakerNotePrint0x0529Test_904, ReturnsSameStreamReference_904) {
  auto v = makeUnsignedShortValue({0, 0, 0, 0});
  std::ostringstream os;

  std::ostream& ret = mn_.print0x0529(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, WrongCount_WrapsValueInParentheses_904) {
  // value.count() != 4 => output should be "(" << value << ")"
  auto v = makeUnsignedShortValue({0, 0, 0});  // 3 items
  std::ostringstream os;

  mn_.print0x0529(os, *v, nullptr);
  const std::string out = os.str();

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, WrongType_WrapsValueInParentheses_904) {
  // value.typeId() != unsignedShort => output should be "(" << value << ")"
  auto v = makeUnsignedLongValue({0, 0, 0, 0});
  std::ostringstream os;

  mn_.print0x0529(os, *v, nullptr);
  const std::string out = os.str();

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, ValidUnsignedShortCount4_PrintsArtFilterName_904) {
  // v0=0 maps to "Off" in artFilters table.
  auto v = makeUnsignedShortValue({0, 0, 0, 0});
  std::ostringstream os;

  mn_.print0x0529(os, *v, nullptr);
  const std::string out = os.str();

  // Black-box friendly: check for the known label, not exact formatting.
  EXPECT_NE(out.find("Off"), std::string::npos);
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, V0Equals39_AppendsPositionUsingFourthElementPlusOne_904) {
  // For v0 == 39, it appends " (position (v3+1))"
  // Choose v3=0 => expected to contain "position 1"
  auto v = makeUnsignedShortValue({39, 0, 0, 0});
  std::ostringstream os;

  mn_.print0x0529(os, *v, nullptr);
  const std::string out = os.str();

  EXPECT_NE(out.find("Partial Color"), std::string::npos);
  EXPECT_NE(out.find("position"), std::string::npos);
  EXPECT_NE(out.find("1"), std::string::npos);
  // Should also have parentheses for the appended portion.
  EXPECT_NE(out.find('('), std::string::npos);
  EXPECT_NE(out.find(')'), std::string::npos);
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, V0Not39_DoesNotAppendPositionSuffix_904) {
  // v0 != 39 should NOT append "position ..." even if v3 is present.
  // Use v0=40 ("Partial Color II") and v3=7 to ensure there is a tempting suffix.
  auto v = makeUnsignedShortValue({40, 0, 0, 7});
  std::ostringstream os;

  mn_.print0x0529(os, *v, nullptr);
  const std::string out = os.str();

  EXPECT_NE(out.find("Partial Color II"), std::string::npos);
  EXPECT_EQ(out.find("position"), std::string::npos);
}

TEST_F(OlympusMakerNotePrint0x0529Test_904, AcceptsNonNullMetadataPointer_NoCrashAndProducesOutput_904) {
  auto v = makeUnsignedShortValue({0, 0, 0, 0});
  std::ostringstream os;

  mn_.print0x0529(os, *v, &exif_);
  const std::string out = os.str();

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Off"), std::string::npos);
}

}  // namespace