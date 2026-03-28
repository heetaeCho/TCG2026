// =================================================================================================
// TEST_ID: 867
// File: test_datevalue_count_867.cpp
//
// Unit tests for Exiv2::DateValue focusing on the observable contract of count(),
// based strictly on the provided interface and black-box behavior.
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace {

class DateValueTest_867 : public ::testing::Test {
 protected:
  static void ExpectCountEqualsSize(const Exiv2::DateValue& v) {
    // The only behavior we can assert from the partial implementation:
    // count() must match size() (observable via public interface).
    EXPECT_EQ(v.count(), v.size());
  }
};

}  // namespace

TEST_F(DateValueTest_867, DefaultConstruction_CountEqualsSize_867) {
  const Exiv2::DateValue v;
  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, YmdConstruction_CountEqualsSize_867) {
  const Exiv2::DateValue v(2024, 2, 29);
  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, SetDate_FromAnotherInstance_CountEqualsSize_867) {
  Exiv2::DateValue a(2000, 1, 1);
  Exiv2::DateValue b(2020, 12, 31);

  // Use only public API: obtain a Date from one instance, then set it on another.
  ASSERT_NO_THROW(a.setDate(b.getDate()));
  ExpectCountEqualsSize(a);
  ExpectCountEqualsSize(b);
}

TEST_F(DateValueTest_867, ReadFromString_EmptyString_DoesNotBreakCountSizeInvariant_867) {
  Exiv2::DateValue v;

  int rc = 0;
  ASSERT_NO_THROW(rc = v.read(std::string{}));

  // We don't assume success/failure semantics; just ensure interface remains consistent.
  (void)rc;
  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, ReadFromString_GarbageString_DoesNotBreakCountSizeInvariant_867) {
  Exiv2::DateValue v(1999, 12, 31);

  int rc = 0;
  ASSERT_NO_THROW(rc = v.read(std::string("not-a-date")));
  (void)rc;

  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, ReadFromBuffer_ZeroLength_DoesNotBreakCountSizeInvariant_867) {
  Exiv2::DateValue v;

  // Pass a non-null pointer with zero length to avoid assuming null handling.
  std::vector<Exiv2::byte> buf(1, Exiv2::byte{0});

  int rc = 0;
  ASSERT_NO_THROW(rc = v.read(buf.data(), 0u, Exiv2::invalidByteOrder));
  (void)rc;

  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, Copy_DoesNotBreakCountSizeInvariant_867) {
  Exiv2::DateValue v(2010, 5, 15);

  std::vector<Exiv2::byte> out(64, Exiv2::byte{0});
  size_t written = 0;

  ASSERT_NO_THROW(written = v.copy(out.data(), Exiv2::invalidByteOrder));
  // We avoid asserting any specific encoding/size; just sanity-check return type usage.
  EXPECT_LE(written, out.size());

  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, Write_ToOstream_DoesNotBreakCountSizeInvariant_867) {
  Exiv2::DateValue v(2021, 7, 4);

  std::ostringstream os;
  ASSERT_NO_THROW(v.write(os));

  ExpectCountEqualsSize(v);
}

TEST_F(DateValueTest_867, Clone_PreservesCountSizeInvariant_867) {
  const Exiv2::DateValue v(2022, 11, 30);

  auto cloned = v.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  ExpectCountEqualsSize(v);
  ExpectCountEqualsSize(*cloned);

  // Also ensure cloning doesn't mutate the original (observable via invariant only).
  EXPECT_EQ(v.count(), v.size());
  EXPECT_EQ(cloned->count(), cloned->size());
}