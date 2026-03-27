// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_olympusmn_int_printCs0x0301_903.cpp
//
// Unit tests for Exiv2::Internal::OlympusMakerNote::printCs0x0301
// Based strictly on the provided interface snippet (black-box behavioral checks).

#include <gtest/gtest.h>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Exiv2 public headers (for Value / ExifData / TypeId / unsignedShort)
#include <exiv2/exiv2.hpp>

// Forward declare (the real definition lives in the library under test)
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote;
}  // namespace Internal
}  // namespace Exiv2

// Include internal header if available in your build.
// If your build exposes a different internal header, adjust accordingly.
#if __has_include("olympusmn_int.hpp")
#include "olympusmn_int.hpp"
#elif __has_include("olympusmn_int.cpp")
#include "olympusmn_int.cpp"  // fallback for some test setups (not ideal but sometimes used)
#endif

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::OlympusMakerNote;

class OlympusMakerNotePrintCs0x0301Test_903 : public ::testing::Test {
 protected:
  OlympusMakerNote mn_;
  ExifData* exifNull_ = nullptr;

  static std::string ToString(std::ostream& (*fn)(std::ostream&)) {
    std::ostringstream os;
    fn(os);
    return os.str();
  }

  static std::string CallPrint(OlympusMakerNote& mn, const Exiv2::Value& v) {
    std::ostringstream os;
    // The method signature takes (ostream&, const Value&, const ExifData*)
    mn.printCs0x0301(os, v, nullptr);
    return os.str();
  }

  static Exiv2::UShortValue MakeUShortValue(std::initializer_list<uint16_t> vals) {
    Exiv2::UShortValue v;
    for (auto x : vals) v.value_.push_back(x);  // UShortValue exposes value_ in Exiv2 API
    return v;
  }

  static Exiv2::LongValue MakeLongValue(std::initializer_list<int32_t> vals) {
    Exiv2::LongValue v;
    for (auto x : vals) v.value_.push_back(x);
    return v;
  }
};

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ReturnsParenWrappedValueWhenCountIsZero_903) {
  // Boundary: count() < 1 triggers "(<value>)" formatting regardless of type.
  Exiv2::UShortValue v;  // empty => count() == 0
  const std::string out = CallPrint(mn_, v);

  // Black-box: only verify observable wrapper pattern.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ReturnsParenWrappedValueWhenTypeIsNotUnsignedShort_903) {
  // Exceptional/error-ish: typeId != unsignedShort triggers "(<value>)"
  Exiv2::LongValue v = MakeLongValue({1});
  const std::string out = CallPrint(mn_, v);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ForSingleCountKnownModePrintsLabelThenNumericValue_903) {
  // Normal: count()==1 and unsignedShort should map certain values to a label and then append numeric v.
  // From provided table: 0 -> "Single AF" (translated macro in real build, but typically resolves to that).
  Exiv2::UShortValue v = MakeUShortValue({0});
  const std::string out = CallPrint(mn_, v);

  // Observable behavior: output contains the numeric value "0" at the end (the code appends v).
  ASSERT_FALSE(out.empty());
  EXPECT_TRUE(out.size() >= 1);
  EXPECT_EQ(out.back(), '0');

  // Also should contain some non-numeric label text before the numeric suffix in typical builds.
  // We avoid hard-coding translated strings; just require that there's more than just "0".
  EXPECT_GT(out.size(), 1u);
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ForSingleCountUnknownModePrintsOnlyNumericValue_903) {
  // Boundary: a value not present in focusModes0 should still print the numeric v (label may be absent).
  Exiv2::UShortValue v = MakeUShortValue({9});  // not in {0,1,2,3,4,10}
  const std::string out = CallPrint(mn_, v);

  // Observable: should end with "9"
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '9');

  // Likely exactly "9" (since no label printed), but keep it tolerant:
  // ensure it contains '9' and no parentheses wrapper for valid type/count.
  EXPECT_NE(out.front(), '(');
  EXPECT_NE(out.back(), ')');
  EXPECT_NE(out.find('9'), std::string::npos);
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ForMultiCountUsesSecondElementAsBitmaskAndAppendsThatNumericValue_903) {
  // Normal: count()>1 causes v to be taken from toInt64(1) (second element),
  // then prints zero or more comma-separated labels, then appends numeric v.
  //
  // Choose bitmask 0x0001 | 0x0010 = S-AF + MF; second element is 0x0011.
  Exiv2::UShortValue v = MakeUShortValue({123, static_cast<uint16_t>(0x0011)});
  const std::string out = CallPrint(mn_, v);

  // Must end with decimal representation of 0x0011 == 17.
  ASSERT_GE(out.size(), 2u);
  EXPECT_TRUE(out.rfind("17") == out.size() - 2);

  // And it should not be parenthesized for valid inputs.
  EXPECT_NE(out.front(), '(');
  EXPECT_NE(out.back(), ')');

  // Should contain a comma separator when multiple bits map to labels.
  // (From code: prints ", " between labels when more than one matches)
  EXPECT_NE(out.find(", "), std::string::npos);
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ForMultiCountWithNoKnownBitsPrintsOnlyNumericSecondValue_903) {
  // Boundary: bitmask with no matching bits results in no label text, but still appends v.
  // Use 0x0002 which doesn't match any of {0x0001,0x0004,0x0010,0x0020,0x0040,0x0100}
  Exiv2::UShortValue v = MakeUShortValue({0, static_cast<uint16_t>(0x0002)});
  const std::string out = CallPrint(mn_, v);

  // Decimal of 0x0002 is "2" at end.
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '2');

  // No comma-space expected if no labels printed.
  EXPECT_EQ(out.find(", "), std::string::npos);
}

TEST_F(OlympusMakerNotePrintCs0x0301Test_903, MultiCountIgnoresFirstElementForFinalNumericSuffix_903) {
  // Verifies observable behavior: for count()>1, the numeric suffix corresponds to the SECOND element,
  // regardless of the first element value.
  Exiv2::UShortValue v = MakeUShortValue({999, static_cast<uint16_t>(0x0100)});  // 256 decimal
  const std::string out = CallPrint(mn_, v);

  // Must end with "256"
  ASSERT_GE(out.size(), 3u);
  EXPECT_TRUE(out.rfind("256") == out.size() - 3);
}

}  // namespace