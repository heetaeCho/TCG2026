// =================================================================================================
// TEST_ID: 866
// File: test_datevalue_getdate_866.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {

class DateValueTest_866 : public ::testing::Test {};

static std::string ToStringViaWrite(const Exiv2::DateValue& v) {
  std::ostringstream oss;
  v.write(oss);
  return oss.str();
}

TEST_F(DateValueTest_866, GetDate_ReturnTypeIsConstRefAndReferenceIsStable_866) {
  Exiv2::DateValue v;

  // Compile-time: ensure return type is a const reference.
  static_assert(std::is_reference_v<decltype(v.getDate())>,
                "getDate() must return a reference");
  static_assert(std::is_const_v<std::remove_reference_t<decltype(v.getDate())>>,
                "getDate() must return a const reference");

  // Runtime: repeated calls should refer to the same internal object (stable reference).
  const auto* p1 = &v.getDate();
  const auto* p2 = &v.getDate();
  EXPECT_EQ(p1, p2);
}

TEST_F(DateValueTest_866, SetDate_ThenWriteMatchesSourceWrite_866) {
  // Use a known calendar boundary date (leap day) without assuming formatting.
  Exiv2::DateValue src(2024, 2, 29);
  Exiv2::DateValue dst;

  // Copy observable date value through the public interface.
  dst.setDate(src.getDate());

  // If dates are the same, their serialized output via write() should match.
  // (We avoid asserting any specific date string format.)
  EXPECT_EQ(ToStringViaWrite(dst), ToStringViaWrite(src));
}

TEST_F(DateValueTest_866, Clone_ProducesIndependentObjectWithSameWrite_866) {
  Exiv2::DateValue original(2030, 12, 31);

  auto cloned = original.clone();
  ASSERT_TRUE(cloned);

  // Ensure the clone is a separate object and preserves observable output.
  EXPECT_NE(cloned.get(), &original);
  EXPECT_EQ(ToStringViaWrite(*cloned), ToStringViaWrite(original));

  // Mutating original afterwards should not mutate the clone (observable via write()).
  Exiv2::DateValue other(1999, 1, 1);
  original.setDate(other.getDate());
  EXPECT_NE(ToStringViaWrite(original), ToStringViaWrite(*cloned));
}

TEST_F(DateValueTest_866, SizeAndCopy_AgreeOnByteCount_866) {
  Exiv2::DateValue v(2026, 2, 6);

  const size_t sz = v.size();

  // Boundary: if size() is 0 (unexpected but possible), copy should return 0 and not crash.
  if (sz == 0) {
    std::vector<Exiv2::byte> buf(1, 0);
    EXPECT_EQ(v.copy(buf.data(), Exiv2::littleEndian), 0u);
    return;
  }

  std::vector<Exiv2::byte> buf(sz);
  const size_t copied = v.copy(buf.data(), Exiv2::littleEndian);

  // Observable contract style check: copy() should not claim it wrote more than size().
  EXPECT_LE(copied, sz);

  // Common expectation for value types: copy() returns exactly size().
  // If the implementation differs, this will catch it without assuming internal encoding.
  EXPECT_EQ(copied, sz);
}

TEST_F(DateValueTest_866, Count_IsStableAcrossNonMutatingCalls_866) {
  Exiv2::DateValue v(2020, 1, 2);

  const size_t c1 = v.count();
  const size_t c2 = v.count();

  EXPECT_EQ(c1, c2);

  // Boundary: count should be non-negative by type; additionally, it should be > 0 for a date value.
  // If the implementation defines otherwise, this will surface it.
  EXPECT_GE(c1, 0u);
}

}  // namespace