// =================================================================================================
// tests_canonmn_int_printSi0x000d_958.cpp
//
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x000d
// Interface under test (from ./TestProjects/exiv2/src/canonmn_int.cpp):
//   std::ostream& printSi0x000d(std::ostream& os, const Value& value, const ExifData*)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>  // Exiv2::Value, Exiv2::ValueType, Exiv2::ExifData, Exiv2::Internal::CanonMakerNote

namespace {

class CanonMakerNoteTest_958 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote maker_;
};

// Helper: create a Value holding a signed/unsigned integer.
// We avoid assuming specific concrete Value subclasses; Exiv2 provides a factory via Value::create().
static Exiv2::Value::UniquePtr MakeSLongValue(int32_t v) {
  auto value = Exiv2::Value::create(Exiv2::signedLong);
  // Most Exiv2 Value implementations accept "read" from string; we only rely on public API.
  value->read(std::to_string(v));
  return value;
}

static Exiv2::Value::UniquePtr MakeULongValue(uint32_t v) {
  auto value = Exiv2::Value::create(Exiv2::unsignedLong);
  value->read(std::to_string(v));
  return value;
}

}  // namespace

// Normal operation: sentinel value (65535) prints "--".
TEST_F(CanonMakerNoteTest_958, PrintsDashDashForSentinel65535_958) {
  std::ostringstream os;

  auto v = MakeULongValue(65535u);
  const Exiv2::ExifData* exif = nullptr;

  std::ostream& ret = maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "--");
}

// Normal operation: non-sentinel value prints integer division by 32.
TEST_F(CanonMakerNoteTest_958, PrintsValueDividedBy32ForNonSentinel_958) {
  std::ostringstream os;

  auto v = MakeULongValue(64u);  // 64 / 32 = 2
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(os.str(), "2");
}

// Boundary: value exactly 0 prints 0.
TEST_F(CanonMakerNoteTest_958, PrintsZeroWhenValueIsZero_958) {
  std::ostringstream os;

  auto v = MakeULongValue(0u);
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(os.str(), "0");
}

// Boundary: value just below divisor prints 0 due to integer division.
TEST_F(CanonMakerNoteTest_958, PrintsZeroWhenValueIsLessThan32_958) {
  std::ostringstream os;

  auto v = MakeULongValue(31u);  // 31 / 32 = 0
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(os.str(), "0");
}

// Boundary: value exactly 32 prints 1.
TEST_F(CanonMakerNoteTest_958, PrintsOneWhenValueIs32_958) {
  std::ostringstream os;

  auto v = MakeULongValue(32u);  // 32 / 32 = 1
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(os.str(), "1");
}

// Boundary: value near sentinel but not sentinel should still be numeric.
TEST_F(CanonMakerNoteTest_958, DoesNotTreat65534AsSentinel_958) {
  std::ostringstream os;

  auto v = MakeULongValue(65534u);  // 65534 / 32 = 2047 (integer)
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  EXPECT_EQ(os.str(), "2047");
}

// Boundary/Type robustness: signed value -1 has toInt64()==-1, should not be treated as sentinel (65535).
TEST_F(CanonMakerNoteTest_958, SignedMinusOneIsNotSentinel_958) {
  std::ostringstream os;

  auto v = MakeSLongValue(-1);  // -1 / 32 = 0 in C++ integer division trunc toward 0? (C++11: toward zero)
  const Exiv2::ExifData* exif = nullptr;

  maker_.printSi0x000d(os, *v, exif);

  // We only assert it's not "--" (observable sentinel output) and is numeric-looking.
  EXPECT_NE(os.str(), "--");
  // For -1 / 32, the formatted output should be "0" with truncation toward zero.
  EXPECT_EQ(os.str(), "0");
}

// Exceptional/robustness: ExifData pointer is allowed to be null; should still print normally.
TEST_F(CanonMakerNoteTest_958, AcceptsNullExifDataPointer_958) {
  std::ostringstream os;

  auto v = MakeULongValue(96u);  // 96 / 32 = 3

  maker_.printSi0x000d(os, *v, nullptr);

  EXPECT_EQ(os.str(), "3");
}

// Stream interaction: appends to existing stream content, doesn't overwrite.
TEST_F(CanonMakerNoteTest_958, AppendsToExistingStreamContent_958) {
  std::ostringstream os;
  os << "prefix:";

  auto v = MakeULongValue(64u);  // prints "2"

  maker_.printSi0x000d(os, *v, nullptr);

  EXPECT_EQ(os.str(), "prefix:2");
}

// Stream interaction: multiple invocations append sequentially.
TEST_F(CanonMakerNoteTest_958, MultipleCallsAppendSequentially_958) {
  std::ostringstream os;

  auto v1 = MakeULongValue(32u);      // "1"
  auto v2 = MakeULongValue(65535u);   // "--"
  auto v3 = MakeULongValue(0u);       // "0"

  maker_.printSi0x000d(os, *v1, nullptr);
  os << ",";
  maker_.printSi0x000d(os, *v2, nullptr);
  os << ",";
  maker_.printSi0x000d(os, *v3, nullptr);

  EXPECT_EQ(os.str(), "1,--,0");
}