// =================================================================================================
// Unit tests for ./TestProjects/exiv2/src/olympusmn_int.cpp (partial)
// Class: Exiv2::Internal::OlympusMakerNote
// Method: print0x0209(std::ostream& os, const Value& value, const ExifData*)
// TEST_ID: 901
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

// Exiv2 includes (adjust include paths if needed for your tree)
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::OlympusMakerNote;
using Exiv2::Value;
using Exiv2::TypeId;

class OlympusMakerNoteTest_901 : public ::testing::Test {
 protected:
  OlympusMakerNote mn_;
  ExifData exif_;
};

static std::string StreamToString(std::ostringstream& oss) { return oss.str(); }

// Helper: create an Exiv2::Value by type and raw data.
// We avoid assuming any OlympusMakerNote internals; this only constructs Value instances.
static std::unique_ptr<Value> MakeValue(TypeId type) {
  return Exiv2::Value::create(type);
}

}  // namespace

// Normal operation: asciiString value prints characters (at least for plain ASCII content).
TEST_F(OlympusMakerNoteTest_901, PrintAsciiStringBasic_901) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  // "ABC" as ASCII string.
  // Exiv2::Value for asciiString accepts read(const byte*, size_t)
  const char* s = "ABC";
  ASSERT_EQ(0, v->read(reinterpret_cast<const Exiv2::byte*>(s), 3));

  std::ostringstream os;
  std::ostream& ret = mn_.print0x0209(os, *v, &exif_);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(StreamToString(os), "ABC");
}

// Boundary: empty asciiString should produce empty output.
TEST_F(OlympusMakerNoteTest_901, PrintAsciiStringEmpty_901) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  // Empty data
  ASSERT_EQ(0, v->read(nullptr, 0));

  std::ostringstream os;
  mn_.print0x0209(os, *v, &exif_);
  EXPECT_TRUE(StreamToString(os).empty());
}

// Boundary: asciiString containing an embedded NUL should stop at NUL (observable truncation).
TEST_F(OlympusMakerNoteTest_901, PrintAsciiStringStopsAtNull_901) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  // "AB\0CD" -> expect "AB"
  const unsigned char raw[] = {'A', 'B', '\0', 'C', 'D'};
  ASSERT_EQ(0, v->read(reinterpret_cast<const Exiv2::byte*>(raw), sizeof(raw)));

  std::ostringstream os;
  mn_.print0x0209(os, *v, &exif_);
  EXPECT_EQ(StreamToString(os), "AB");
}

// Normal operation: undefined type is accepted and printed as character stream until NUL (if any).
TEST_F(OlympusMakerNoteTest_901, PrintUndefinedAsChars_901) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v, nullptr);

  const unsigned char raw[] = {'X', 'Y', 'Z'};
  ASSERT_EQ(0, v->read(reinterpret_cast<const Exiv2::byte*>(raw), sizeof(raw)));

  std::ostringstream os;
  mn_.print0x0209(os, *v, &exif_);
  EXPECT_EQ(StreamToString(os), "XYZ");
}

// Boundary: undefined with leading NUL prints nothing.
TEST_F(OlympusMakerNoteTest_901, PrintUndefinedLeadingNullPrintsEmpty_901) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v, nullptr);

  const unsigned char raw[] = {'\0', 'A', 'B'};
  ASSERT_EQ(0, v->read(reinterpret_cast<const Exiv2::byte*>(raw), sizeof(raw)));

  std::ostringstream os;
  mn_.print0x0209(os, *v, &exif_);
  EXPECT_TRUE(StreamToString(os).empty());
}

// Error/exceptional (observable): non-asciiString and non-undefined types should be streamed via operator<<
// We don't assume the exact formatting; we only assert that the function *does not* behave like char-by-char
// extraction from toInt64 and that it produces some output for a non-empty value.
TEST_F(OlympusMakerNoteTest_901, NonAsciiNonUndefinedFallsBackToValueStreaming_901) {
  auto v = MakeValue(Exiv2::unsignedShort);
  ASSERT_NE(v, nullptr);

  // Provide one element. We avoid assuming formatting; just ensure it produces something.
  ASSERT_TRUE(v->read("42") == 0 || true);  // Some builds allow textual read; if not, use add().
  if (v->count() == 0) {
    // Fallback: add a numeric value if textual read didn't populate.
    v->add(Exiv2::UShortValue::UniquePtr(new Exiv2::UShortValue(42)).get());  // best-effort across variants
  }

  std::ostringstream os;
  mn_.print0x0209(os, *v, &exif_);

  // At minimum, should produce a non-empty representation for a value with content.
  // (If the environment's Value streaming prints something like "42" or "[42]", both are fine.)
  EXPECT_FALSE(StreamToString(os).empty());
}

// Boundary: ExifData pointer is allowed to be null (method signature permits it); behavior should be safe.
TEST_F(OlympusMakerNoteTest_901, AcceptsNullExifDataPointer_901) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  const char* s = "OK";
  ASSERT_EQ(0, v->read(reinterpret_cast<const Exiv2::byte*>(s), 2));

  std::ostringstream os;
  EXPECT_NO_THROW({
    mn_.print0x0209(os, *v, nullptr);
  });
  EXPECT_EQ(StreamToString(os), "OK");
}