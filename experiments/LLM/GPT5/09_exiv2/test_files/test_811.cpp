// TEST_ID 811
// File: test_string_value_base_toFloat_811.cpp

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "value.hpp"  // Exiv2::StringValueBase, Exiv2::TypeId, Exiv2::Value

namespace {

class StringValueBaseTest_811 : public ::testing::Test {
 protected:
  // Use a non-empty buffer so index 0 is in-range for typical implementations.
  static Exiv2::StringValueBase MakeSut() {
    return Exiv2::StringValueBase(Exiv2::asciiString, std::string("123"));
  }
};

TEST_F(StringValueBaseTest_811, ToFloatReturnsSameValueOnRepeatedCalls_811) {
  auto sut = MakeSut();

  ASSERT_GT(sut.count(), 0u);

  const float v1 = sut.toFloat(0);
  const float v2 = sut.toFloat(0);

  // Observable, implementation-agnostic: same call should be stable.
  EXPECT_EQ(v1, v2);

  // Basic sanity: value should be comparable to itself (not NaN).
  EXPECT_EQ(v1, v1);
}

TEST_F(StringValueBaseTest_811, ToFloatLastIndexDoesNotThrow_811) {
  auto sut = MakeSut();

  const size_t c = sut.count();
  ASSERT_GT(c, 0u);

  EXPECT_NO_THROW((void)sut.toFloat(c - 1));
}

TEST_F(StringValueBaseTest_811, ToFloatOutOfRangeThrows_811) {
  auto sut = MakeSut();

  const size_t c = sut.count();
  // Calling with count() is out-of-range if indexing is 0..count-1.
  EXPECT_THROW((void)sut.toFloat(c), std::out_of_range);

  // Also exercise a very large index as a boundary/error case.
  EXPECT_THROW((void)sut.toFloat(std::numeric_limits<size_t>::max()), std::out_of_range);
}

TEST_F(StringValueBaseTest_811, OkIsTrueBeforeAndAfterSuccessfulToFloat_811) {
  auto sut = MakeSut();

  // Value starts ok by default (observable via ok()).
  EXPECT_TRUE(sut.ok());

  ASSERT_GT(sut.count(), 0u);
  EXPECT_NO_THROW((void)sut.toFloat(0));

  // toFloat is expected to leave the object in an "ok" state on success.
  EXPECT_TRUE(sut.ok());
}

}  // namespace