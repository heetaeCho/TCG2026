// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/test_tags_int_print0x8822_1397.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace Exiv2::Internal {
// Function under test (implemented in src/tags_int.cpp)
std::ostream& print0x8822(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

std::string RenderPrint0x8822(const Exiv2::Value& v, const Exiv2::ExifData* md = nullptr) {
  std::ostringstream oss;
  auto& ret = Exiv2::Internal::print0x8822(oss, v, md);
  // Observable: should return the same stream instance passed in.
  EXPECT_EQ(&ret, &oss);
  return oss.str();
}

Exiv2::Value::UniquePtr MakeUShortValueFromString(const std::string& s) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  EXPECT_NE(v.get(), nullptr);
  const int rc = v->read(s);
  // Observable: read() returns an int status; we expect success for basic numeric strings.
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(v->ok());
  return v;
}

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation: known mappings (from exifExposureProgram TagDetails table)
// -----------------------------------------------------------------------------

TEST(Print0x8822Test_1397, PrintsNotDefinedForZero_1397) {
  auto v = MakeUShortValueFromString("0");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Not defined"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsManualForOne_1397) {
  auto v = MakeUShortValueFromString("1");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Manual"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsAutoForTwo_1397) {
  auto v = MakeUShortValueFromString("2");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Auto"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsAperturePriorityForThree_1397) {
  auto v = MakeUShortValueFromString("3");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Aperture priority"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsShutterPriorityForFour_1397) {
  auto v = MakeUShortValueFromString("4");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Shutter priority"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsCreativeProgramForFive_1397) {
  auto v = MakeUShortValueFromString("5");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Creative program"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsActionProgramForSix_1397) {
  auto v = MakeUShortValueFromString("6");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Action program"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsPortraitModeForSeven_1397) {
  auto v = MakeUShortValueFromString("7");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Portrait mode"), std::string::npos);
}

TEST(Print0x8822Test_1397, PrintsLandscapeModeForEight_1397) {
  auto v = MakeUShortValueFromString("8");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Landscape mode"), std::string::npos);
}

// -----------------------------------------------------------------------------
// Boundary conditions
// -----------------------------------------------------------------------------

TEST(Print0x8822Test_1397, HandlesUpperBoundaryEightWithMetadataPointer_1397) {
  auto v = MakeUShortValueFromString("8");

  Exiv2::ExifData md;  // Should be safe to pass even if unused.
  const std::string out = RenderPrint0x8822(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Landscape mode"), std::string::npos);
}

TEST(Print0x8822Test_1397, HandlesOutOfRangeNineDoesNotCrashAndProducesSomeOutput_1397) {
  auto v = MakeUShortValueFromString("9");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  // Black-box expectation: should not throw/crash; output may be numeric or "Unknown".
  EXPECT_FALSE(out.empty());
}

TEST(Print0x8822Test_1397, HandlesVeryLargeValueDoesNotCrashAndProducesSomeOutput_1397) {
  auto v = MakeUShortValueFromString("65535");
  const std::string out = RenderPrint0x8822(*v, nullptr);

  EXPECT_FALSE(out.empty());
}

// -----------------------------------------------------------------------------
// Exceptional / error-ish cases (observable via interface)
// -----------------------------------------------------------------------------

TEST(Print0x8822Test_1397, HandlesEmptyValueGracefully_1397) {
  // Create a value but do not populate it with read(); behavior is black-box.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    auto& ret = Exiv2::Internal::print0x8822(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });

  // Output could be empty or something; we only require no crash and stream is usable.
  EXPECT_TRUE(oss.good());
}

TEST(Print0x8822Test_1397, StreamStateIsPreservedWhenStreamAlreadyBad_1397) {
  auto v = MakeUShortValueFromString("2");

  std::ostringstream oss;
  oss.setstate(std::ios::badbit);  // Pre-set error state.

  auto& ret = Exiv2::Internal::print0x8822(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);

  // Observable: should not "fix" the stream; keep badbit set.
  EXPECT_TRUE(oss.bad());
}