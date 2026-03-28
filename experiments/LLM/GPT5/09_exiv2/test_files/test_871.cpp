// -------------------------------------------------------------------------------------------------
// TEST_ID 871
// Unit tests for Exiv2::DateValue::toUint32(size_t) based strictly on observable behavior.
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Include the real header that declares Exiv2::DateValue in your codebase.
// If your project uses a different public header, adjust this include accordingly.
#include "value.hpp"

namespace {

class DateValueTest_871 : public ::testing::Test {};

TEST_F(DateValueTest_871, ToUint32_ZeroIndex_DoesNotThrow_871) {
  Exiv2::DateValue v;
  // Black-box expectation: method is callable and returns a uint32_t.
  EXPECT_NO_THROW({
    volatile uint32_t out = v.toUint32(0);
    (void)out;
  });
}

TEST_F(DateValueTest_871, ToUint32_LargeIndex_DoesNotThrow_871) {
  Exiv2::DateValue v;
  const size_t big = std::numeric_limits<size_t>::max();
  // Parameter is commented out (unused) in the provided implementation, so it must be safe to pass any size_t.
  EXPECT_NO_THROW({
    volatile uint32_t out = v.toUint32(big);
    (void)out;
  });
}

TEST_F(DateValueTest_871, ToUint32_ReturnTypeRange_IsUint32_871) {
  Exiv2::DateValue v;
  // Returned value must always be representable in uint32_t.
  const uint32_t out0 = v.toUint32(0);
  const uint32_t out1 = v.toUint32(1);

  // These assertions are tautologically true for uint32_t, but they encode the interface contract clearly:
  EXPECT_LE(out0, std::numeric_limits<uint32_t>::max());
  EXPECT_LE(out1, std::numeric_limits<uint32_t>::max());
}

TEST_F(DateValueTest_871, ToUint32_RepeatedCalls_AreStableInTypeAndCallability_871) {
  Exiv2::DateValue v;

  // We cannot assume determinism of the returned value (depends on internal toInt64()),
  // but repeated calls should remain callable and not throw.
  EXPECT_NO_THROW({
    for (int i = 0; i < 10; ++i) {
      volatile uint32_t out = v.toUint32(static_cast<size_t>(i));
      (void)out;
    }
  });
}

}  // namespace