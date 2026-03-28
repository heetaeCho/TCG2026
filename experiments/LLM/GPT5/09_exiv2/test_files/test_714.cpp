// =================================================================================================
// Copyright ...
// Unit tests for: Exiv2::Internal::PanasonicMakerNote::printPressure
// File under test: ./TestProjects/exiv2/src/panasonicmn_int.cpp
// TEST_ID: 714
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Treat implementation as black box: include the real header that declares PanasonicMakerNote.
// If your build exposes it via a different header, adjust include accordingly.
#include "panasonicmn_int.hpp"

// Exiv2 public types used by the interface.
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

// Helper to create an Exiv2 Value holding a (U)Short / Long / etc. without relying on internals.
// We keep this minimal and only use public Exiv2::Value API.
static std::unique_ptr<Exiv2::Value> MakeUShortValue(uint16_t v) {
  // Exiv2::UShortValue is a public concrete Value type.
  auto val = std::make_unique<Exiv2::UShortValue>();
  val->read(std::to_string(v));
  return val;
}

static std::unique_ptr<Exiv2::Value> MakeLongValue(int32_t v) {
  auto val = std::make_unique<Exiv2::LongValue>();
  val->read(std::to_string(v));
  return val;
}

}  // namespace

namespace Exiv2::Internal {

class PanasonicMakerNoteTest_714 : public ::testing::Test {
 protected:
  PanasonicMakerNote uut_;
  Exiv2::ExifData exif_;  // Not used by function (by signature), but we pass a valid object when needed.
};

TEST_F(PanasonicMakerNoteTest_714, PrintsInfiniteWhenValueIs65535_714) {
  // Boundary/sentinel case: exactly 65535 should print "infinite".
  auto v = MakeUShortValue(65535);

  std::ostringstream os;
  std::ostream& ret = uut_.printPressure(os, *v, &exif_);

  EXPECT_EQ(&ret, &os) << "printPressure should return the same stream it writes to";
  EXPECT_EQ(os.str(), "infinite");
}

TEST_F(PanasonicMakerNoteTest_714, AppendsHpaSuffixForNonSentinelValue_714) {
  // Normal operation: any value != 65535 should print "<value> hPa" (with a leading space before hPa).
  auto v = MakeUShortValue(1013);

  std::ostringstream os;
  uut_.printPressure(os, *v, &exif_);

  const std::string out = os.str();
  EXPECT_NE(out.find("hPa"), std::string::npos);
  EXPECT_TRUE(out.size() >= 4);
  EXPECT_EQ(out, "1013 hPa");
}

TEST_F(PanasonicMakerNoteTest_714, WorksWithDifferentNumericValueTypes_714) {
  // Boundary-ish: ensure behavior is observable even if Value is not UShortValue.
  // (We don't infer internals; we only verify the output contract via the interface.)
  auto v = MakeLongValue(900);

  std::ostringstream os;
  uut_.printPressure(os, *v, &exif_);

  EXPECT_EQ(os.str(), "900 hPa");
}

TEST_F(PanasonicMakerNoteTest_714, AllowsNullExifDataPointer_714) {
  // Exceptional-ish input: ExifData* may be nullptr by signature.
  // Observable behavior: should still format output (no crash is the key).
  auto v = MakeUShortValue(1000);

  std::ostringstream os;
  uut_.printPressure(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1000 hPa");
}

TEST_F(PanasonicMakerNoteTest_714, SentinelComparisonUsesToInt64NotStringFormatting_714) {
  // Boundary condition around 65535: ensure 65534 is NOT treated as infinite.
  auto v = MakeUShortValue(65534);

  std::ostringstream os;
  uut_.printPressure(os, *v, &exif_);

  EXPECT_EQ(os.str(), "65534 hPa");
}

}  // namespace Exiv2::Internal