// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Bring in the real declarations (black-box testing).
#include "panasonicmn_int.hpp"

namespace {

// Minimal test-only Value implementation: only provides the observable interface used
// by PanasonicMakerNote::print0x0029 (Value::toInt64()).
//
// This is NOT re-implementing the class under test; it is just a stand-in dependency
// to supply controlled inputs via the required interface.
class FakeValue : public Exiv2::Value {
 public:
  explicit FakeValue(int64_t v) : v_(v) {}
  int64_t toInt64() const override { return v_; }

  // The rest of Exiv2::Value is not required by this unit under test; keep minimal.
  // If Exiv2::Value in your tree has a different abstract surface, adjust stubs
  // accordingly (still only to satisfy compilation).
 private:
  int64_t v_;
};

}  // namespace

namespace Exiv2::Internal {

class PanasonicMakerNoteTest_709 : public ::testing::Test {
 protected:
  PanasonicMakerNote sut_;
  const ExifData* exif_ = nullptr;  // print0x0029 does not require ExifData content
};

TEST_F(PanasonicMakerNoteTest_709, FormatsAllZeroTimeAs00_00_00_00_709) {
  FakeValue v(0);
  std::ostringstream os;

  std::ostream& ret = sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "00:00:00.00");
}

TEST_F(PanasonicMakerNoteTest_709, FormatsHundredthsOnly_709) {
  FakeValue v(7);  // 0.07
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:00:00.07");
}

TEST_F(PanasonicMakerNoteTest_709, FormatsOneSecond_709) {
  FakeValue v(100);  // 1.00s
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:00:01.00");
}

TEST_F(PanasonicMakerNoteTest_709, FormatsOneMinute_709) {
  FakeValue v(6000);  // 60.00s -> 1:00.00
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:01:00.00");
}

TEST_F(PanasonicMakerNoteTest_709, FormatsOneHour_709) {
  FakeValue v(360000);  // 3600.00s -> 1:00:00.00
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "01:00:00.00");
}

TEST_F(PanasonicMakerNoteTest_709, FormatsMixedComponents_709) {
  // 12:34:56.78
  // hours: 12 -> 12 * 360000
  // minutes: 34 -> 34 * 6000
  // seconds: 56 -> 56 * 100
  // hundredths: 78
  const int64_t t = 12 * 360000LL + 34 * 6000LL + 56 * 100LL + 78;
  FakeValue v(t);
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "12:34:56.78");
}

TEST_F(PanasonicMakerNoteTest_709, BoundaryJustBeforeNextSecond_709) {
  FakeValue v(99);  // 0.99s
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:00:00.99");
}

TEST_F(PanasonicMakerNoteTest_709, BoundaryJustBeforeNextMinute_709) {
  FakeValue v(5999);  // 59.99s
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:00:59.99");
}

TEST_F(PanasonicMakerNoteTest_709, BoundaryJustBeforeNextHour_709) {
  FakeValue v(359999);  // 59:59.99
  std::ostringstream os;

  sut_.print0x0029(os, v, exif_);

  EXPECT_EQ(os.str(), "00:59:59.99");
}

TEST_F(PanasonicMakerNoteTest_709, DoesNotThrowForLargePositiveValue_709) {
  FakeValue v(std::numeric_limits<int64_t>::max());
  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.print0x0029(os, v, exif_);
  });

  // Observable: it should produce *something* (formatting), and return the same stream.
  EXPECT_FALSE(os.str().empty());
}

TEST_F(PanasonicMakerNoteTest_709, DoesNotThrowForNegativeValue_709) {
  // Error/exceptional-ish input: negative time. Behavior is observable only as output.
  FakeValue v(-1);
  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.print0x0029(os, v, exif_);
  });

  // We don't assert exact formatting for negatives (implementation-defined),
  // but it must still return the stream and write something.
  EXPECT_FALSE(os.str().empty());
}

}  // namespace Exiv2::Internal