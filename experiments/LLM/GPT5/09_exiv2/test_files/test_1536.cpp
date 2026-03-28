// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::nikonSelector
#include "types.hpp"          // Exiv2::byte

namespace {

// NOTE: nikonSelector's 4th parameter is currently unused in the provided implementation.
// We still pass nullptr to avoid relying on any TiffComponent construction details.

class NikonSelectorTest_1536 : public ::testing::Test {};

TEST_F(NikonSelectorTest_1536, SizeZeroAndNullDataReturnsMinus1_1536) {
  const Exiv2::byte* data = nullptr;
  EXPECT_EQ(-1, Exiv2::Internal::nikonSelector(/*tag=*/0, data, /*size=*/0, /*pRoot=*/nullptr));
}

TEST_F(NikonSelectorTest_1536, SizeOneAndNullDataReturnsMinus1_1536) {
  const Exiv2::byte* data = nullptr;
  EXPECT_EQ(-1, Exiv2::Internal::nikonSelector(/*tag=*/0x1234, data, /*size=*/1, /*pRoot=*/nullptr));
}

TEST_F(NikonSelectorTest_1536, SizeThreeAndNullDataReturnsMinus1_1536) {
  const Exiv2::byte* data = nullptr;
  EXPECT_EQ(-1, Exiv2::Internal::nikonSelector(/*tag=*/0xFFFF, data, /*size=*/3, /*pRoot=*/nullptr));
}

TEST_F(NikonSelectorTest_1536, SizeExactlyFourWithValidDataDoesNotCrashAndIsDeterministic_1536) {
  const Exiv2::byte data[4] = {0x00, 0x01, 0x02, 0x03};

  const int r1 = Exiv2::Internal::nikonSelector(/*tag=*/0xFFFF, data, /*size=*/4, /*pRoot=*/nullptr);
  const int r2 = Exiv2::Internal::nikonSelector(/*tag=*/0xFFFF, data, /*size=*/4, /*pRoot=*/nullptr);

  // Observable behavior: returns an int, and for the same inputs should be stable.
  EXPECT_EQ(r1, r2);
}

TEST_F(NikonSelectorTest_1536, SizeExactlyFourWithEmbeddedNullByteDoesNotCrash_1536) {
  const Exiv2::byte data[4] = {0x41, 0x00, 0x42, 0x43};  // 'A' '\0' 'B' 'C'

  const int r = Exiv2::Internal::nikonSelector(/*tag=*/0x7FFF, data, /*size=*/4, /*pRoot=*/nullptr);

  // Should be either "not found" (-1) or some non-negative index if the key happens to exist.
  EXPECT_GE(r, -1);
}

TEST_F(NikonSelectorTest_1536, LargerSizeWithUnlikelyKeyCommonlyReturnsMinus1_1536) {
  // Choose an unlikely tag and content to avoid depending on any specific table contents.
  std::vector<Exiv2::byte> data(64, static_cast<Exiv2::byte>(0xAA));
  data[0] = 0xDE;
  data[1] = 0xAD;
  data[2] = 0xBE;
  data[3] = 0xEF;

  const int r = Exiv2::Internal::nikonSelector(/*tag=*/0xFFFE, data.data(), data.size(), /*pRoot=*/nullptr);

  // "Not found" is the only universally observable error code exposed in this interface.
  // If this ever matches in a future table update, the test will fail and should be adjusted.
  EXPECT_EQ(-1, r);
}

}  // namespace