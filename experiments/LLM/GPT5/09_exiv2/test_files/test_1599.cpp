// =================================================================================================
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for: Exiv2::Internal::SonyMakerNote::printFocalPlaneAFPointsUsed
// File under test: ./TestProjects/exiv2/src/sonymn_int.cpp
//
// Constraints:
//  - Treat implementation as a black box: only validate observable behavior via public API.
//  - No private-state access.
//  - Include normal/boundary/error cases.
//  - Use TEST_ID suffix in every test name.
//
// TEST_ID: 1599
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Exiv2 headers (adjust include paths as needed for your build)
#include "sonymn_int.hpp"  // for Exiv2::Internal::SonyMakerNote
#include "exif.hpp"        // for Exiv2::ExifData
#include "value.hpp"       // for Exiv2::Value / Exiv2::TypeId / Exiv2::Value::create

namespace {

class SonyMnPrintFocalPlaneAFPointsUsedTest_1599 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;
  Exiv2::ExifData exif_;  // used only as a valid pointer target

  static std::string Call(const Exiv2::Internal::SonyMakerNote& mn,
                          const Exiv2::Value& value,
                          const Exiv2::ExifData* exifPtr) {
    std::ostringstream os;
    // Method is non-const in snippet; keep signature exact.
    // We call on a non-const instance in tests, so this helper isn't used for const.
    (void)mn; (void)value; (void)exifPtr;
    return os.str();
  }
};

// Helper: call method and return resulting string.
static std::string Print(Exiv2::Internal::SonyMakerNote& mn,
                         const Exiv2::Value& value,
                         const Exiv2::ExifData* exifPtr) {
  std::ostringstream os;
  mn.printFocalPlaneAFPointsUsed(os, value, exifPtr);
  return os.str();
}

static std::string Print(Exiv2::Internal::SonyMakerNote& mn,
                         const Exiv2::Value& value) {
  return Print(mn, value, nullptr);
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal / boundary / error-observable cases
// -------------------------------------------------------------------------------------------------

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, NonUnsignedByteType_EmitsParenthesizedValue_1599) {
  // If typeId != unsignedByte => output "(" << value << ")"
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::asciiString));
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("hello");

  const std::string out = Print(mn_, *v, &exif_);

  // Observable contract from interface snippet: wrapped in parentheses.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  // Should contain the streamed representation of the value.
  EXPECT_NE(out.find("hello"), std::string::npos);
}

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, UnsignedByteValueZero_PrintsNone_1599) {
  // If typeId == unsignedByte and toUint32(0) == 0 => prints _("None")
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::unsignedByte));
  ASSERT_TRUE(static_cast<bool>(v));
  // For unsignedByte, provide "0"
  v->read("0");

  const std::string out = Print(mn_, *v, &exif_);

  // Translation may vary, but commonly equals "None". We at least assert it's not parenthesized.
  // Prefer strict check because snippet literally uses _("None").
  EXPECT_EQ(out, "None");
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.front(), '(');
}

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, UnsignedByteNonZero_PrintsParenthesizedValue_1599) {
  // If unsignedByte and first element non-zero => output "(" << value << ")"
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::unsignedByte));
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("1");

  const std::string out = Print(mn_, *v, &exif_);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  // Should include "1" somewhere in the value representation.
  EXPECT_NE(out.find('1'), std::string::npos);
}

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, UnsignedByteEmptyOrOutOfRangeIndex_DoesNotThrow_1599) {
  // Boundary: if value is unsignedByte but has no elements, implementation calls toUint32(0).
  // We can't assume outcome, but the interface should be robust: verify no throw and some output.
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::unsignedByte));
  ASSERT_TRUE(static_cast<bool>(v));
  // Intentionally do not read any data -> "empty" value.

  std::ostringstream os;
  EXPECT_NO_THROW(mn_.printFocalPlaneAFPointsUsed(os, *v, &exif_));
  // Output may be empty or something; ensure stream is still usable.
  EXPECT_TRUE(os.good());
}

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, ExifDataPointerNull_BehaviorUnaffectedForNonUnsignedByte_1599) {
  // The method takes ExifData* but does not appear to use it in the snippet.
  // We validate observable equivalence for a case that doesn't depend on exif pointer.
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::asciiString));
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("abc");

  const std::string out_with = Print(mn_, *v, &exif_);
  const std::string out_null = Print(mn_, *v, nullptr);

  EXPECT_EQ(out_with, out_null);
  ASSERT_GE(out_null.size(), 2u);
  EXPECT_EQ(out_null.front(), '(');
  EXPECT_EQ(out_null.back(), ')');
}

TEST_F(SonyMnPrintFocalPlaneAFPointsUsedTest_1599, OutputIsAppendedToExistingStreamContent_1599) {
  // Normal behavior: method writes to provided stream, should append not reset.
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::unsignedByte));
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("1");

  std::ostringstream os;
  os << "prefix:";

  EXPECT_NO_THROW(mn_.printFocalPlaneAFPointsUsed(os, *v, &exif_));
  const std::string out = os.str();

  EXPECT_NE(out.find("prefix:"), std::string::npos);
  // Ensure something was appended after the prefix.
  EXPECT_GT(out.size(), std::string("prefix:").size());
}