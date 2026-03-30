// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::sonyCsSelector (black-box via public signature)
//
// File under test (per prompt):
//   ./TestProjects/exiv2/src/makernote_int.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstddef>

// Forward declarations to avoid including internal headers.
// We only need pointer types for the interface.
namespace Exiv2 {
using byte = unsigned char;
namespace Internal {
struct TiffComponent;  // opaque
int sonyCsSelector(uint16_t tag, const byte* pData, size_t size, TiffComponent* pRoot);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class SonyCsSelectorTest_1538 : public ::testing::Test {};

TEST_F(SonyCsSelectorTest_1538, ReturnsMinusOneWhenRootIsNull_1538) {
  // Boundary / error case: null root pointer
  const Exiv2::byte dummy = 0x00;
  EXPECT_EQ(-1, Exiv2::Internal::sonyCsSelector(0u, &dummy, 1u, nullptr));
}

TEST_F(SonyCsSelectorTest_1538, ReturnsMinusOneWhenRootIsNullEvenIfDataNullAndSizeZero_1538) {
  // Stronger boundary: all other inputs "empty" as well.
  EXPECT_EQ(-1, Exiv2::Internal::sonyCsSelector(0u, nullptr, 0u, nullptr));
}

TEST_F(SonyCsSelectorTest_1538, ReturnsConsistentResultAcrossDifferentTagAndDataWhenRootIsNull_1538) {
  // Tag/data/size should not matter when root is null (observable outcome: -1).
  const Exiv2::byte data1[3] = {0x01, 0x02, 0x03};
  const Exiv2::byte data2[1] = {0xFF};

  EXPECT_EQ(-1, Exiv2::Internal::sonyCsSelector(0u, data1, 3u, nullptr));
  EXPECT_EQ(-1, Exiv2::Internal::sonyCsSelector(42u, data2, 1u, nullptr));
  EXPECT_EQ(-1, Exiv2::Internal::sonyCsSelector(65535u, nullptr, 0u, nullptr));
}

}  // namespace