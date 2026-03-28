// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>

// Public interface
#include "exiv2/types.hpp"

// NOTE:
// checkDataBufBounds is a TU-local (static) free function in src/types.cpp.
// To test its observable behavior (throws / no-throws) via its real implementation,
// we include the .cpp so the symbol is available in this test translation unit.
#include "types.cpp"

namespace {

using Exiv2::DataBuf;

TEST(CheckDataBufBoundsTest_1130, DoesNotThrowForEndWithinBounds_1130) {
  DataBuf buf(8);

  EXPECT_NO_THROW(Exiv2::checkDataBufBounds(buf, 0));
  EXPECT_NO_THROW(Exiv2::checkDataBufBounds(buf, 1));
  EXPECT_NO_THROW(Exiv2::checkDataBufBounds(buf, 7));
}

TEST(CheckDataBufBoundsTest_1130, DoesNotThrowForEndEqualToSize_1130) {
  DataBuf buf(8);

  EXPECT_NO_THROW(Exiv2::checkDataBufBounds(buf, buf.size()));
}

TEST(CheckDataBufBoundsTest_1130, ThrowsOutOfRangeWhenEndExceedsSize_1130) {
  DataBuf buf(8);

  EXPECT_THROW(Exiv2::checkDataBufBounds(buf, buf.size() + 1), std::out_of_range);
  EXPECT_THROW(Exiv2::checkDataBufBounds(buf, buf.size() + 100), std::out_of_range);
}

TEST(CheckDataBufBoundsTest_1130, HandlesEmptyBufferBounds_1130) {
  DataBuf empty;

  EXPECT_EQ(empty.size(), 0u);
  EXPECT_NO_THROW(Exiv2::checkDataBufBounds(empty, 0));
  EXPECT_THROW(Exiv2::checkDataBufBounds(empty, 1), std::out_of_range);
}

TEST(CheckDataBufBoundsTest_1130, ThrowsInvalidArgumentWhenEndTooLargeForLongComparison_1130) {
  DataBuf buf(8);

  // If size_t can represent (long max + 1), then passing that should trigger invalid_argument.
  constexpr size_t kLongMaxAsSizeT = static_cast<size_t>((std::numeric_limits<long>::max)());
  if constexpr (kLongMaxAsSizeT < (std::numeric_limits<size_t>::max)()) {
    const size_t endTooLarge = kLongMaxAsSizeT + 1u;
    EXPECT_THROW(Exiv2::checkDataBufBounds(buf, endTooLarge), std::invalid_argument);
  } else {
    GTEST_SKIP() << "size_t cannot represent (long max + 1) on this platform.";
  }
}

TEST(CheckDataBufBoundsTest_1130, EndAtLongMaxStillValidatedAgainstBufSize_1130) {
  // For small buffers, end == long max is still far beyond buf.size(), so out_of_range is expected
  // unless the invalid_argument check triggers earlier. This test only asserts behavior when
  // end is <= long max (so invalid_argument should NOT be thrown).
  DataBuf buf(8);

  const size_t endAtLongMax = static_cast<size_t>((std::numeric_limits<long>::max)());
  // If endAtLongMax is representable (it should be) and definitely > buf.size(),
  // the observable error should be out_of_range (not invalid_argument).
  ASSERT_GT(endAtLongMax, buf.size());
  EXPECT_THROW(Exiv2::checkDataBufBounds(buf, endAtLongMax), std::out_of_range);
}

}  // namespace