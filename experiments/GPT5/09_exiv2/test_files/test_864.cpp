// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_datevalue_setdate_864.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// Exiv2
#include <exiv2/value.hpp>

namespace {

class DateValueTest_864 : public ::testing::Test {
 protected:
  using DateValue = Exiv2::DateValue;
  using Date = Exiv2::DateValue::Date;
};

TEST_F(DateValueTest_864, SetDateStoresProvidedDate_864) {
  DateValue dv;

  const Date src{2024, 2, 29};
  dv.setDate(src);

  const Date& got = dv.getDate();
  EXPECT_EQ(got.year, src.year);
  EXPECT_EQ(got.month, src.month);
  EXPECT_EQ(got.day, src.day);
}

TEST_F(DateValueTest_864, SetDateOverwritesPreviousValue_864) {
  DateValue dv;

  const Date first{2000, 1, 1};
  dv.setDate(first);

  const Date second{1999, 12, 31};
  dv.setDate(second);

  const Date& got = dv.getDate();
  EXPECT_EQ(got.year, second.year);
  EXPECT_EQ(got.month, second.month);
  EXPECT_EQ(got.day, second.day);
}

TEST_F(DateValueTest_864, ConstructorWithYMDIsObservableViaGetDate_864) {
  // Observable behavior only: whatever the ctor stores should be readable via getDate().
  DateValue dv(2021, 12, 31);

  const Date& got = dv.getDate();
  EXPECT_EQ(got.year, 2021);
  EXPECT_EQ(got.month, 12);
  EXPECT_EQ(got.day, 31);
}

TEST_F(DateValueTest_864, SetDateAcceptsBoundaryLikeValuesAndIsReadable_864) {
  DateValue dv;

  // Boundary-like but still reasonable calendar-ish values; we only assert what getDate() exposes.
  const Date src1{0, 1, 1};
  dv.setDate(src1);
  {
    const Date& got = dv.getDate();
    EXPECT_EQ(got.year, src1.year);
    EXPECT_EQ(got.month, src1.month);
    EXPECT_EQ(got.day, src1.day);
  }

  const Date src2{9999, 12, 31};
  dv.setDate(src2);
  {
    const Date& got = dv.getDate();
    EXPECT_EQ(got.year, src2.year);
    EXPECT_EQ(got.month, src2.month);
    EXPECT_EQ(got.day, src2.day);
  }
}

TEST_F(DateValueTest_864, CopyDoesNotWriteMoreThanSize_864) {
  DateValue dv;
  dv.setDate(Date{2023, 7, 8});

  const size_t sz = dv.size();
  std::vector<Exiv2::byte> buf(sz == 0 ? 1 : sz);  // avoid zero-sized data() edge cases

  const size_t copied = dv.copy(buf.data(), Exiv2::invalidByteOrder /* byteOrder is ignored per interface */);

  // Observable safety/contract style check: copied bytes should not exceed reported size().
  EXPECT_LE(copied, sz);
}

}  // namespace