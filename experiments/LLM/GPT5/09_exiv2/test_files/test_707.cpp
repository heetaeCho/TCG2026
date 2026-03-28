// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_panasonicmn_int_print0x000f_707.cpp
//
// Unit tests for Exiv2::Internal::PanasonicMakerNote::print0x000f
// based strictly on the public/observable interface from the snippet.
//
// Constraints honored:
// - Treat implementation as black box (no private state access)
// - Verify observable output on std::ostream
// - Cover normal, boundary, and error/fallback paths

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <sstream>
#include <vector>

// Exiv2 headers (paths may vary in your tree; adjust if needed)
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace {

// Helper: build an Exiv2 Value holding unsignedByte(s) with given bytes.
static std::unique_ptr<Exiv2::Value> MakeUByteValue(const std::vector<uint8_t>& bytes) {
  // unsignedByte in Exiv2 corresponds to Exiv2::unsignedByte and UByteValue.
  auto v = Exiv2::Value::create(Exiv2::unsignedByte);
  // Set from raw bytes; Value API supports read(const byte*, long)
  // which parses according to the type.
  if (!bytes.empty()) {
    v->read(reinterpret_cast<const Exiv2::byte*>(bytes.data()),
            static_cast<long>(bytes.size()));
  } else {
    // empty: do nothing; count() should be 0
  }
  return v;
}

// Helper: build a Value of a different type to trigger fallback branch.
static std::unique_ptr<Exiv2::Value> MakeUShortValue(const std::vector<uint16_t>& vals) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  if (!vals.empty()) {
    v->read(reinterpret_cast<const Exiv2::byte*>(vals.data()),
            static_cast<long>(vals.size() * sizeof(uint16_t)));
  }
  return v;
}

// Call helper that returns the produced string.
static std::string CallPrint0x000f(const Exiv2::Value& value) {
  // The method under test takes (std::ostream&, const Value&, const ExifData*).
  // ExifData* is unused in the provided snippet; pass nullptr.
  Exiv2::Internal::PanasonicMakerNote mn;
  std::ostringstream oss;
  mn.print0x000f(oss, value, nullptr);
  return oss.str();
}

}  // namespace

// ---------- Boundary / error-ish observable cases ----------

TEST(PanasonicMakerNotePrint0x000fTest_707, FallbackWhenCountLessThan2_707) {
  auto v = MakeUByteValue({0});  // count == 1
  const std::string out = CallPrint0x000f(*v);

  // Observable requirement: for fallback, output should match streaming the Value itself.
  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(out, expected.str());
}

TEST(PanasonicMakerNotePrint0x000fTest_707, FallbackWhenTypeIsNotUnsignedByte_707) {
  auto v = MakeUShortValue({0, 1});  // wrong type on purpose
  const std::string out = CallPrint0x000f(*v);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(out, expected.str());
}

TEST(PanasonicMakerNotePrint0x000fTest_707, FallbackWhenPairIsUnrecognized_707) {
  auto v = MakeUByteValue({2, 3});  // not listed mapping in snippet
  const std::string out = CallPrint0x000f(*v);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(out, expected.str());
}

// ---------- Normal operation (recognized mappings) ----------

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsSpotModeOnOr9AreaFor00_01_707) {
  auto v = MakeUByteValue({0, 1});
  EXPECT_EQ(CallPrint0x000f(*v), "Spot mode on or 9 area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsSpotModeOffOr3AreaHighSpeedFor00_16_707) {
  auto v = MakeUByteValue({0, 16});
  EXPECT_EQ(CallPrint0x000f(*v), "Spot mode off or 3-area (high speed)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints23AreaFor00_23_707) {
  auto v = MakeUByteValue({0, 23});
  EXPECT_EQ(CallPrint0x000f(*v), "23-area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints49AreaFor00_49_707) {
  auto v = MakeUByteValue({0, 49});
  EXPECT_EQ(CallPrint0x000f(*v), "49-area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints225AreaFor00_225_707) {
  auto v = MakeUByteValue({0, 225});
  EXPECT_EQ(CallPrint0x000f(*v), "225-area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsSpotFocusingFor01_00_707) {
  auto v = MakeUByteValue({1, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "Spot focusing");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints5AreaFor01_01_707) {
  auto v = MakeUByteValue({1, 1});
  EXPECT_EQ(CallPrint0x000f(*v), "5-area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints1AreaFor16_00_707) {
  auto v = MakeUByteValue({16, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "1-area");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints1AreaHighSpeedFor16_16_707) {
  auto v = MakeUByteValue({16, 16});
  EXPECT_EQ(CallPrint0x000f(*v), "1-area (high speed)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints3AreaAutoFor32_00_707) {
  auto v = MakeUByteValue({32, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "3-area (auto)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints3AreaLeftFor32_01_707) {
  auto v = MakeUByteValue({32, 1});
  EXPECT_EQ(CallPrint0x000f(*v), "3-area (left)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints3AreaCenterFor32_02_707) {
  auto v = MakeUByteValue({32, 2});
  EXPECT_EQ(CallPrint0x000f(*v), "3-area (center)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, Prints3AreaRightFor32_03_707) {
  auto v = MakeUByteValue({32, 3});
  EXPECT_EQ(CallPrint0x000f(*v), "3-area (right)");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsFaceDetectFor64_00_707) {
  auto v = MakeUByteValue({64, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "Face Detect");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsSpotFocusing2For128_00_707) {
  auto v = MakeUByteValue({128, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "Spot Focusing 2");
}

TEST(PanasonicMakerNotePrint0x000fTest_707, PrintsTrackingFor240_00_707) {
  auto v = MakeUByteValue({240, 0});
  EXPECT_EQ(CallPrint0x000f(*v), "Tracking");
}

// ---------- Additional boundary: extra bytes should not break mapping ----------

TEST(PanasonicMakerNotePrint0x000fTest_707, IgnoresExtraValuesBeyondFirstTwo_707) {
  // Only first two elements are used by the interface behavior we can observe.
  auto v = MakeUByteValue({0, 1, 99, 100});
  EXPECT_EQ(CallPrint0x000f(*v), "Spot mode on or 9 area");
}