// ============================================================================
// TEST_ID: 959
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x000e
// File: ./TestProjects/exiv2/src/canonmn_int.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "canonmn_int.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::CanonMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

// Helper: create a Value of given type and (optionally) initialize it using the
// public Value::read(std::string) interface. We do not assume parsing details
// beyond "it accepts a numeric string" for numeric types; tests use substring
// assertions to stay robust.
static Value::UniquePtr MakeValue(TypeId type, const std::string& init = std::string()) {
  auto v = Value::create(type);
  if (!init.empty()) {
    (void)v->read(init);
  }
  return v;
}

static std::string PrintSi0x000eToString(const Value& value, const ExifData* exif = nullptr) {
  std::ostringstream oss;
  // The provided snippet shows a non-static member; the header shows static.
  // Calling through an instance is valid in both cases (static can be called too).
  CanonMakerNote mn;
  mn.printSi0x000e(oss, value, exif);
  return oss.str();
}

}  // namespace

// Normal / boundary: value.typeId() != unsignedShort -> should stream the value as-is.
TEST(CanonMakerNoteTest_959, TypeMismatchStreamsValue_959) {
  auto v = MakeValue(Exiv2::unsignedLong, "123");
  ASSERT_NE(v, nullptr);

  const std::string out = PrintSi0x000eToString(*v, nullptr);

  // Black-box: we only assert that something representing the value is streamed.
  // For numeric values, Exiv2 typically prints the numeric textual form.
  EXPECT_NE(out.find("123"), std::string::npos);
}

// Boundary: unsignedShort but count()==0 -> should stream the value as-is and not append fixed text.
TEST(CanonMakerNoteTest_959, UnsignedShortWithZeroCountStreamsValueOnly_959) {
  auto v = MakeValue(Exiv2::unsignedShort);  // not initialized => commonly count()==0
  ASSERT_NE(v, nullptr);

  const std::string out = PrintSi0x000eToString(*v, nullptr);

  // If it took the early-return, it should not append the known fixed phrases.
  EXPECT_EQ(out.find("focus points"), std::string::npos);
  EXPECT_EQ(out.find(" used"), std::string::npos);
}

// Normal: used bits == 0 -> prints "<num> focus points; none used"
TEST(CanonMakerNoteTest_959, UsedMaskZeroPrintsNoneUsed_959) {
  // l = 0x1000 => num = 1, used = 0
  auto v = MakeValue(Exiv2::unsignedShort, "4096");
  ASSERT_NE(v, nullptr);

  const std::string out = PrintSi0x000eToString(*v, nullptr);

  EXPECT_NE(out.find("1"), std::string::npos);
  EXPECT_NE(out.find("focus points;"), std::string::npos);
  EXPECT_NE(out.find("none"), std::string::npos);
  EXPECT_NE(out.find(" used"), std::string::npos);
}

// Normal: used bits non-zero -> prints "<num> focus points; <bitmask text> used"
TEST(CanonMakerNoteTest_959, UsedMaskNonZeroPrintsBitmaskText_959) {
  // l = 0x3004 => num = 3, used = 4 ("left" in canonSiAFPointUsed)
  auto v = MakeValue(Exiv2::unsignedShort, "12292");
  ASSERT_NE(v, nullptr);

  const std::string out = PrintSi0x000eToString(*v, nullptr);

  EXPECT_NE(out.find("3"), std::string::npos);
  EXPECT_NE(out.find("focus points;"), std::string::npos);

  // Black-box + stable: based on the provided TagDetailsBitmask entries.
  EXPECT_NE(out.find("left"), std::string::npos);
  EXPECT_NE(out.find(" used"), std::string::npos);

  // And it should NOT print "none" in this case.
  EXPECT_EQ(out.find("none"), std::string::npos);
}

// Boundary: multiple used bits set (left+center+right) should include all labels.
TEST(CanonMakerNoteTest_959, UsedMaskAllBitsIncludesAllLabels_959) {
  // l = 0x0007 with num=0, used bits=7 => left+center+right
  auto v = MakeValue(Exiv2::unsignedShort, "7");
  ASSERT_NE(v, nullptr);

  const std::string out = PrintSi0x000eToString(*v, nullptr);

  EXPECT_NE(out.find("0"), std::string::npos);
  EXPECT_NE(out.find("focus points;"), std::string::npos);

  EXPECT_NE(out.find("left"), std::string::npos);
  EXPECT_NE(out.find("center"), std::string::npos);
  EXPECT_NE(out.find("right"), std::string::npos);
  EXPECT_NE(out.find(" used"), std::string::npos);
}