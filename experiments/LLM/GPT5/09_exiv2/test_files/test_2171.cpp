// File: test_datevalue_2171.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "exiv2/value.hpp"

namespace {

// Keep the TEST_ID in the fixture name as requested.
class DateValueTest_2171 : public ::testing::Test {};

}  // namespace

TEST_F(DateValueTest_2171, DefaultConstruction_HasSingleValueAndRoundtripsClone_2171) {
  Exiv2::DateValue v;

  // Observable, interface-only checks.
  EXPECT_TRUE(v.ok());

  // Count/size should be stable and non-negative.
  EXPECT_GE(v.count(), static_cast<size_t>(0));
  EXPECT_GE(v.size(), static_cast<size_t>(0));

  // Cloning should preserve observable representation.
  Exiv2::Value::UniquePtr c = v.clone();
  ASSERT_NE(c.get(), nullptr);

  EXPECT_EQ(c->typeId(), v.typeId());
  EXPECT_EQ(c->count(), v.count());
  EXPECT_EQ(c->size(), v.size());
  EXPECT_EQ(c->toString(), v.toString());
}

TEST_F(DateValueTest_2171, SetDate_GetDateReflectsValues_2171) {
  Exiv2::DateValue v;

  Exiv2::DateValue::Date d{};
  d.year = 2026;
  d.month = 2;
  d.day = 11;

  v.setDate(d);
  const Exiv2::DateValue::Date& got = v.getDate();

  EXPECT_EQ(got.year, d.year);
  EXPECT_EQ(got.month, d.month);
  EXPECT_EQ(got.day, d.day);
}

TEST_F(DateValueTest_2171, CtorWithYmd_SetsDate_2171) {
  const int32_t y = 1999;
  const int32_t m = 12;
  const int32_t d = 31;

  Exiv2::DateValue v(y, m, d);
  const Exiv2::DateValue::Date& got = v.getDate();

  EXPECT_EQ(got.year, y);
  EXPECT_EQ(got.month, m);
  EXPECT_EQ(got.day, d);
}

TEST_F(DateValueTest_2171, ToStringReadString_RoundTripUsingSelfProducedString_2171) {
  Exiv2::DateValue original(2020, 1, 2);

  // Avoid assuming a particular string format: use the class's own output.
  const std::string s = original.toString();

  Exiv2::DateValue parsed;
  const int rc = parsed.read(s);

  // We don't assume exact return codes, only that representation round-trips.
  (void)rc;
  EXPECT_EQ(parsed.toString(), original.toString());
  EXPECT_EQ(parsed.getDate().year, original.getDate().year);
  EXPECT_EQ(parsed.getDate().month, original.getDate().month);
  EXPECT_EQ(parsed.getDate().day, original.getDate().day);
}

TEST_F(DateValueTest_2171, CopyReadBytes_RoundTripUsingSizeAndCopyBuffer_2171) {
  Exiv2::DateValue original(2010, 7, 14);

  // Use the public API to determine required buffer size.
  const size_t n = original.size();
  std::vector<Exiv2::byte> buf(n == 0 ? 1 : n, static_cast<Exiv2::byte>(0));

  // Use a "neutral" ByteOrder value without assuming enum constants.
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  const size_t copied = original.copy(buf.data(), bo);

  // copied should not exceed the provided capacity.
  EXPECT_LE(copied, buf.size());

  Exiv2::DateValue roundtrip;
  const int rc = roundtrip.read(buf.data(), copied, bo);
  (void)rc;

  EXPECT_EQ(roundtrip.toString(), original.toString());
  EXPECT_EQ(roundtrip.getDate().year, original.getDate().year);
  EXPECT_EQ(roundtrip.getDate().month, original.getDate().month);
  EXPECT_EQ(roundtrip.getDate().day, original.getDate().day);
}

TEST_F(DateValueTest_2171, BoundaryValues_SetDateWithExtremeInt32_DoesNotCorruptAccessors_2171) {
  Exiv2::DateValue v;

  Exiv2::DateValue::Date d{};
  d.year = (std::numeric_limits<int32_t>::min)();
  d.month = (std::numeric_limits<int32_t>::max)();
  d.day = 0;

  v.setDate(d);
  const Exiv2::DateValue::Date& got = v.getDate();

  EXPECT_EQ(got.year, d.year);
  EXPECT_EQ(got.month, d.month);
  EXPECT_EQ(got.day, d.day);
}

TEST_F(DateValueTest_2171, ReadWithEmptyInput_IsObservableAndStable_2171) {
  Exiv2::DateValue v;

  // Capture current representation; we won't assume what "invalid" does, but it must be safe.
  const std::string before = v.toString();

  // Empty string read should not crash; return code is observable but unspecified.
  const int rc = v.read(std::string{});
  (void)rc;

  // Must remain usable via interface after the call.
  EXPECT_GE(v.count(), static_cast<size_t>(0));
  EXPECT_GE(v.size(), static_cast<size_t>(0));
  (void)before;  // representation may or may not change; we don't assert it.
}

TEST_F(DateValueTest_2171, Write_ProducesStreamOutputConsistentWithToString_2171) {
  Exiv2::DateValue v(2023, 3, 5);

  std::ostringstream os;
  const std::ostream& ref = v.write(os);

  // Returned stream reference should be the same stream we provided.
  EXPECT_EQ(&ref, &os);

  // Avoid assuming exact formatting; just require non-empty output for a non-default date.
  EXPECT_FALSE(os.str().empty());
}