// TEST_ID 869
// Unit tests for Exiv2::DateValue::write
//
// Focus: observable formatting and stream behavior only (black-box).
// - Verifies YYYY-MM-DD formatting with zero-padding for month/day.
// - Verifies 4-digit year formatting behavior for common and boundary-ish values.
// - Verifies returned stream reference enables chaining.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <exiv2/value.hpp>

namespace {

class DateValueTest_869 : public ::testing::Test {};

TEST_F(DateValueTest_869, WriteFormatsWithZeroPaddedMonthAndDay_869) {
  Exiv2::DateValue v(2024, 1, 2);

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), "2024-01-02");
}

TEST_F(DateValueTest_869, WriteFormatsTypicalDate_869) {
  Exiv2::DateValue v(1999, 12, 31);

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), "1999-12-31");
}

TEST_F(DateValueTest_869, WriteSupportsSettingDateThenWriting_869) {
  Exiv2::DateValue v(2000, 1, 1);

  Exiv2::DateValue::Date d{};
  d.year = 7;
  d.month = 3;
  d.day = 9;

  v.setDate(d);

  std::ostringstream os;
  v.write(os);

  // Observable behavior: formatted output after setDate.
  EXPECT_EQ(os.str(), "0007-03-09");
}

TEST_F(DateValueTest_869, WriteReturnsSameStreamReferenceForChaining_869) {
  Exiv2::DateValue v(2025, 10, 5);

  std::ostringstream os;
  std::ostream& returned = v.write(os);
  returned << "|tail";

  // Same underlying stream should have both the date and the chained content.
  EXPECT_EQ(os.str(), "2025-10-05|tail");

  // Also verify reference identity (observable via address).
  EXPECT_EQ(&returned, static_cast<std::ostream*>(&os));
}

}  // namespace