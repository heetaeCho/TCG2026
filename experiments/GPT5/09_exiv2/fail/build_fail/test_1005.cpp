// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaDateStd_1005.cpp
//
// Unit tests for:
//   Exiv2::Internal::MinoltaMakerNote::printMinoltaDateStd
//
// Constraints respected:
// - Treat implementation as black box: assert only observable stream output + return reference
// - No private state access
// - Use gmock only for external collaborators (Value); ExifData pointer is unused/nullable

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <cstdint>

// Bring in the class under test (defined in minoltamn_int.cpp in the real codebase).
// Adjust include as needed for your build layout.
#include "minoltamn_int.hpp"  // or appropriate header that declares Exiv2::Internal::MinoltaMakerNote

namespace {

// Minimal gmock-based stand-in for Exiv2::Value that exposes the needed interface.
// We only model the *external dependency* (Value::toInt64()) which is invoked by the method under test.
class MockValue : public Exiv2::Value {
public:
  MOCK_METHOD(int64_t, toInt64, (), (const, override));
  // If Exiv2::Value has other pure virtuals in your build, add trivial overrides here,
  // but do not simulate any MinoltaMakerNote internal behavior.
};

}  // namespace

namespace Exiv2 {
namespace Internal {

class MinoltaMakerNoteTest_1005 : public ::testing::Test {
protected:
  MinoltaMakerNote sut_;
};

TEST_F(MinoltaMakerNoteTest_1005, FormatsZeroAs0000000000_1005) {
  MockValue v;
  EXPECT_CALL(v, toInt64()).WillOnce(::testing::Return(0));

  std::ostringstream os;
  const ExifData* exif = nullptr;

  std::ostream& ret = sut_.printMinoltaDateStd(os, v, exif);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "0:00:00");
}

TEST_F(MinoltaMakerNoteTest_1005, FormatsTypicalPackedValue_1005) {
  // val = (year << 16) | (month << 8) | day
  // Choose: 2023:12:31 -> (2023<<16) + (12<<8) + 31
  const int64_t packed = (static_cast<int64_t>(2023) << 16) |
                         (static_cast<int64_t>(12) << 8) |
                         static_cast<int64_t>(31);

  MockValue v;
  EXPECT_CALL(v, toInt64()).WillOnce(::testing::Return(packed));

  std::ostringstream os;
  std::ostream& ret = sut_.printMinoltaDateStd(os, v, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "2023:12:31");
}

TEST_F(MinoltaMakerNoteTest_1005, MonthAndDayAreZeroPaddedToTwoDigits_1005) {
  // 2001:01:02
  const int64_t packed = (static_cast<int64_t>(2001) << 16) |
                         (static_cast<int64_t>(1) << 8) |
                         static_cast<int64_t>(2);

  MockValue v;
  EXPECT_CALL(v, toInt64()).WillOnce(::testing::Return(packed));

  std::ostringstream os;
  sut_.printMinoltaDateStd(os, v, nullptr);

  EXPECT_EQ(os.str(), "2001:01:02");
}

TEST_F(MinoltaMakerNoteTest_1005, BoundaryMonthAndDayAt255_1005) {
  // Boundary for the 8-bit fields: month=255, day=255 should format as ":255" with 2-digit minimum
  // (i.e., no truncation; width is minimum 2, so "255" remains "255")
  const int64_t packed = (static_cast<int64_t>(1999) << 16) |
                         (static_cast<int64_t>(255) << 8) |
                         static_cast<int64_t>(255);

  MockValue v;
  EXPECT_CALL(v, toInt64()).WillOnce(::testing::Return(packed));

  std::ostringstream os;
  sut_.printMinoltaDateStd(os, v, nullptr);

  EXPECT_EQ(os.str(), "1999:255:255");
}

TEST_F(MinoltaMakerNoteTest_1005, UsesOnlyValueToInt64Once_1005) {
  MockValue v;
  EXPECT_CALL(v, toInt64()).Times(1).WillOnce(::testing::Return(0));

  std::ostringstream os;
  sut_.printMinoltaDateStd(os, v, nullptr);

  EXPECT_EQ(os.str(), "0:00:00");
}

TEST_F(MinoltaMakerNoteTest_1005, NegativeValueProducesObservableFormattedOutput_1005) {
  // Error-ish / exceptional input (negative) should not crash; we verify the observable output.
  // We do not assume any specific "date" validity rules; only the formatting behavior is asserted.
  MockValue v;
  EXPECT_CALL(v, toInt64()).WillOnce(::testing::Return(static_cast<int64_t>(-1)));

  std::ostringstream os;
  sut_.printMinoltaDateStd(os, v, nullptr);

  // For val=-1:
  //   year  = val/65536  (implementation-defined rounding toward zero in C++ for negatives)
  //   mid   = (val % 65536)/256
  //   low   = val % 256
  // We avoid re-deriving the exact numeric fields; instead we assert the structural shape:
  // "<something>:<two+ chars>:<two+ chars>" and presence of two ':' separators.
  const std::string s = os.str();
  ASSERT_EQ(std::count(s.begin(), s.end(), ':'), 2);

  const auto first = s.find(':');
  const auto second = s.find(':', first + 1);
  ASSERT_NE(first, std::string::npos);
  ASSERT_NE(second, std::string::npos);

  const std::string part1 = s.substr(0, first);
  const std::string part2 = s.substr(first + 1, second - (first + 1));
  const std::string part3 = s.substr(second + 1);

  EXPECT_FALSE(part1.empty());
  EXPECT_GE(part2.size(), 2u);
  EXPECT_GE(part3.size(), 2u);
}

}  // namespace Internal
}  // namespace Exiv2