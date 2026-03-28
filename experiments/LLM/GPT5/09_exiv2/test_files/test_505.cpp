// ============================================================================
// Nikon3MakerNote print0x009a unit tests
// File: nikon3makernote_print0x009a_test.cpp
// TEST_ID: 505
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header (expected to exist in Exiv2 tree for this implementation).
// If your build uses a different path/name, adjust this include accordingly.
#include "nikonmn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::Internal::Nikon3MakerNote;

class Nikon3MakerNoteTest_505 : public ::testing::Test {
protected:
  static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    EXPECT_NE(v.get(), nullptr);
    // Rely only on public API: parse textual representation into Value.
    v->read(text);
    return v;
  }

  static std::string StreamValue(const Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }
};

TEST_F(Nikon3MakerNoteTest_505, PrintsFormattedWhenTwoUnsignedRationals_505) {
  Nikon3MakerNote mn;

  // Two unsigned rationals (typical Exiv2 textual format: "num/den num/den").
  auto v = MakeValue(Exiv2::unsignedRational, "1/1 2/1");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->count(), 2u);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedRational);

  std::ostringstream os;
  mn.print0x009a(os, *v, static_cast<const ExifData*>(nullptr));

  // Build expectation using the same public Value accessors and standard streaming.
  const float f1 = v->toFloat(0);
  const float f2 = v->toFloat(1);
  std::ostringstream expected;
  expected << f1 << " x " << f2 << " um";

  EXPECT_EQ(os.str(), expected.str());
}

TEST_F(Nikon3MakerNoteTest_505, FallsBackToValueStreamWhenCountNotTwo_505) {
  Nikon3MakerNote mn;

  // Only one component => should fall back to streaming the value itself.
  auto v = MakeValue(Exiv2::unsignedRational, "3/1");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NE(v->count(), 2u);  // boundary condition for this formatter

  std::ostringstream os;
  mn.print0x009a(os, *v, static_cast<const ExifData*>(nullptr));

  EXPECT_EQ(os.str(), StreamValue(*v));
}

TEST_F(Nikon3MakerNoteTest_505, FallsBackToValueStreamWhenTypeIsNotUnsignedRational_505) {
  Nikon3MakerNote mn;

  // Different type => should fall back to streaming the value itself.
  auto v = MakeValue(Exiv2::asciiString, "hello");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NE(v->typeId(), Exiv2::unsignedRational);

  std::ostringstream os;
  mn.print0x009a(os, *v, static_cast<const ExifData*>(nullptr));

  EXPECT_EQ(os.str(), StreamValue(*v));
}

TEST_F(Nikon3MakerNoteTest_505, FormatsFractionalRationalsUsingToFloat_505) {
  Nikon3MakerNote mn;

  // Boundary-ish values: fractional rationals.
  auto v = MakeValue(Exiv2::unsignedRational, "1/2 3/4");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->count(), 2u);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedRational);

  std::ostringstream os;
  mn.print0x009a(os, *v, static_cast<const ExifData*>(nullptr));

  const float f1 = v->toFloat(0);
  const float f2 = v->toFloat(1);
  std::ostringstream expected;
  expected << f1 << " x " << f2 << " um";

  EXPECT_EQ(os.str(), expected.str());
}

TEST_F(Nikon3MakerNoteTest_505, FormatsZeroValues_505) {
  Nikon3MakerNote mn;

  auto v = MakeValue(Exiv2::unsignedRational, "0/1 0/1");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->count(), 2u);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedRational);

  std::ostringstream os;
  mn.print0x009a(os, *v, static_cast<const ExifData*>(nullptr));

  const float f1 = v->toFloat(0);
  const float f2 = v->toFloat(1);
  std::ostringstream expected;
  expected << f1 << " x " << f2 << " um";

  EXPECT_EQ(os.str(), expected.str());
}

}  // namespace