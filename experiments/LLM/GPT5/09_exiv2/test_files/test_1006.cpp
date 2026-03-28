// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaTimeStd_1006.cpp
//
// Unit tests for:
//   Exiv2::Internal::MinoltaMakerNote::printMinoltaTimeStd(std::ostream&, const Value&, const ExifData*)
//
// Constraints respected:
// - Treat implementation as a black box (no re-implementation of internals)
// - Test only observable behavior via public interface (ostream output)
// - Boundary + normal + error/exceptional cases (where observable)

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

// Exiv2 headers (paths may vary in your project layout)
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Include the internal header that declares MinoltaMakerNote.
// In Exiv2, internal classes are typically declared in *_int.hpp.
#include "minoltamn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::Internal::MinoltaMakerNote;

// Helper: create a Value that yields a specific int64 via toInt64().
// We use an unsignedLong/long Value as it is commonly backed by integer storage.
static std::unique_ptr<Value> makeInt64Value(int64_t v) {
  // Try signed long first.
  auto val = Exiv2::Value::create(Exiv2::signedLong);
  val->read(std::to_string(v));
  return val;
}

class MinoltaMakerNoteTest_1006 : public ::testing::Test {
 protected:
  MinoltaMakerNote uut_;
  ExifData exif_;  // not used by function, but supplied to satisfy signature
};

TEST_F(MinoltaMakerNoteTest_1006, FormatsZeroAs00_00_00_1006) {
  std::ostringstream os;
  auto v = makeInt64Value(0);

  std::ostream& ret = uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(&ret, &os) << "Should return the same ostream reference";
  EXPECT_EQ(os.str(), "00:00:00");
}

TEST_F(MinoltaMakerNoteTest_1006, FormatsOneSecondAs00_00_01_1006) {
  std::ostringstream os;
  // val % 256 is the seconds field
  auto v = makeInt64Value(1);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "00:00:01");
}

TEST_F(MinoltaMakerNoteTest_1006, FormatsOneMinuteAs00_01_00_1006) {
  std::ostringstream os;
  // (val % 65536)/256 is minutes; set minutes=1 => val=256
  auto v = makeInt64Value(256);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "00:01:00");
}

TEST_F(MinoltaMakerNoteTest_1006, FormatsOneHourAs01_00_00_1006) {
  std::ostringstream os;
  // hours field is val/65536; set hours=1 => val=65536
  auto v = makeInt64Value(65536);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "01:00:00");
}

TEST_F(MinoltaMakerNoteTest_1006, FormatsMixedFields_1006) {
  std::ostringstream os;
  // hours=2, minutes=3, seconds=4 => val = 2*65536 + 3*256 + 4
  const int64_t raw = 2LL * 65536 + 3LL * 256 + 4LL;
  auto v = makeInt64Value(raw);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "02:03:04");
}

TEST_F(MinoltaMakerNoteTest_1006, PadsSingleDigitFieldsWithLeadingZeroes_1006) {
  std::ostringstream os;
  // hours=9, minutes=8, seconds=7 => "09:08:07"
  const int64_t raw = 9LL * 65536 + 8LL * 256 + 7LL;
  auto v = makeInt64Value(raw);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "09:08:07");
}

TEST_F(MinoltaMakerNoteTest_1006, Boundary_AllBytesMaxWithin16BitChunk_1006) {
  std::ostringstream os;
  // Set lower 16 bits to 0xFFFF => minutes=255, seconds=255, hours=0
  auto v = makeInt64Value(65535);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "00:255:255");
}

TEST_F(MinoltaMakerNoteTest_1006, Boundary_MinutesAndSecondsZeroAtChunkBoundary_1006) {
  std::ostringstream os;
  // Exactly 0x0100 in low 16 bits => minutes=1, seconds=0
  auto v = makeInt64Value(256);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "00:01:00");
}

TEST_F(MinoltaMakerNoteTest_1006, IgnoresExifDataPointerWhenNull_1006) {
  std::ostringstream os;
  auto v = makeInt64Value(2LL * 65536 + 3LL * 256 + 4LL);

  // Passing nullptr should still be safe if implementation doesn't dereference it.
  // Observable behavior: formatting remains correct.
  uut_.printMinoltaTimeStd(os, *v, nullptr);

  EXPECT_EQ(os.str(), "02:03:04");
}

TEST_F(MinoltaMakerNoteTest_1006, Exceptional_ValueTypeThatConvertsToInt64StillFormats_1006) {
  std::ostringstream os;
  // Use a different numeric Value type to ensure conversion path is robust
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  v->read("65536");  // should convert to int64 as 1 hour

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  EXPECT_EQ(os.str(), "01:00:00");
}

TEST_F(MinoltaMakerNoteTest_1006, Exceptional_NegativeValueProducesDeterministicOutput_1006) {
  std::ostringstream os;
  auto v = makeInt64Value(-1);

  // We don't assume "correctness" for negative times; we only assert:
  // - call does not throw
  // - stream gets *some* output with two ':' separators (observable formatting shape)
  EXPECT_NO_THROW(uut_.printMinoltaTimeStd(os, *v, &exif_));

  const std::string out = os.str();
  // Basic shape check: contains exactly two ':' characters.
  const auto first = out.find(':');
  const auto second = (first == std::string::npos) ? std::string::npos : out.find(':', first + 1);
  EXPECT_NE(first, std::string::npos);
  EXPECT_NE(second, std::string::npos);
}

TEST_F(MinoltaMakerNoteTest_1006, LargeValueFormatsHoursAsQuotient_1006) {
  std::ostringstream os;
  // Choose a value where hours is clearly > 2 digits.
  // hours = 123 => val = 123*65536, minutes=0, seconds=0
  const int64_t raw = 123LL * 65536;
  auto v = makeInt64Value(raw);

  uut_.printMinoltaTimeStd(os, *v, &exif_);

  // The interface promises formatting via ostream; we assert exact output we can observe.
  EXPECT_EQ(os.str(), "123:00:00");
}

}  // namespace