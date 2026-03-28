// =================================================================================================
// TestProjects/exiv2/tests/value_langaltvalue_touint32_test.cpp
// Unit tests for Exiv2::LangAltValue::toUint32()
// TEST_ID: 859
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>

// Prefer the public header if available in the codebase.
#if __has_include(<exiv2/value.hpp>)
#include <exiv2/value.hpp>
#elif __has_include("value.hpp")
#include "value.hpp"
#else
// Fallback: if the build system already provides the declaration elsewhere,
// this forward declaration will be unused. We avoid re-implementing logic.
namespace Exiv2 {
class LangAltValue {
public:
  uint32_t toUint32(size_t n) const;
};
}  // namespace Exiv2
#endif

namespace {

class LangAltValueToUint32Test_859 : public ::testing::Test {};

TEST_F(LangAltValueToUint32Test_859, ReturnsZeroForIndexZero_859) {
  const Exiv2::LangAltValue v;
  EXPECT_EQ(0u, v.toUint32(0));
}

TEST_F(LangAltValueToUint32Test_859, ReturnsZeroForTypicalSmallIndices_859) {
  const Exiv2::LangAltValue v;

  EXPECT_EQ(0u, v.toUint32(1));
  EXPECT_EQ(0u, v.toUint32(2));
  EXPECT_EQ(0u, v.toUint32(3));
  EXPECT_EQ(0u, v.toUint32(10));
}

TEST_F(LangAltValueToUint32Test_859, ReturnsZeroForLargeIndex_859) {
  const Exiv2::LangAltValue v;

  const size_t large = (std::numeric_limits<size_t>::max)();
  EXPECT_EQ(0u, v.toUint32(large));
}

TEST_F(LangAltValueToUint32Test_859, DoesNotThrowForAnyIndex_859) {
  const Exiv2::LangAltValue v;

  EXPECT_NO_THROW((void)v.toUint32(0));
  EXPECT_NO_THROW((void)v.toUint32(123));
  EXPECT_NO_THROW((void)v.toUint32((std::numeric_limits<size_t>::max)()));
}

TEST_F(LangAltValueToUint32Test_859, IsCallableThroughConstReference_859) {
  const Exiv2::LangAltValue v;
  const Exiv2::LangAltValue& cref = v;

  EXPECT_EQ(0u, cref.toUint32(0));
  EXPECT_EQ(0u, cref.toUint32(5));
}

}  // namespace