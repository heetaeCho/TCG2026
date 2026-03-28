// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonyMisc2bSelector_1541.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#include <exiv2/types.hpp>

// The function lives in Exiv2::Internal (implemented in src/makernote_int.cpp).
// It may or may not be declared in a public/internal header, so we declare it here.
namespace Exiv2 {
namespace Internal {
class TiffComponent;
int sonyMisc2bSelector(uint16_t tag, const Exiv2::byte* pData, size_t size, TiffComponent* pRoot);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class SonyMisc2bSelectorTest_1541 : public ::testing::Test {};

TEST_F(SonyMisc2bSelectorTest_1541, NullRootReturnsMinusOne_1541) {
  // Boundary / error case: no root component.
  // This test intentionally does not assume anything about internal TIFF/Exif layout.
  EXPECT_NO_THROW({
    const int rc = Exiv2::Internal::sonyMisc2bSelector(/*tag=*/0, /*pData=*/nullptr, /*size=*/0, /*pRoot=*/nullptr);
    EXPECT_EQ(-1, rc);
  });
}

TEST_F(SonyMisc2bSelectorTest_1541, NullRootIgnoresTagAndDataPointers_1541) {
  // Boundary: different tag and non-null data pointer should not matter when root is null.
  const Exiv2::byte dummy[4] = {0x00, 0x11, 0x22, 0x33};

  EXPECT_NO_THROW({
    const int rc = Exiv2::Internal::sonyMisc2bSelector(/*tag=*/0xFFFF, /*pData=*/dummy, /*size=*/sizeof(dummy),
                                                      /*pRoot=*/nullptr);
    EXPECT_EQ(-1, rc);
  });
}

TEST_F(SonyMisc2bSelectorTest_1541, NullRootWithNonZeroSizeAndNullDataDoesNotCrash_1541) {
  // Boundary: size > 0 while pData is null. We only assert the observable behavior:
  // - no exception
  // - returns an error code (-1) when root is absent
  EXPECT_NO_THROW({
    const int rc = Exiv2::Internal::sonyMisc2bSelector(/*tag=*/0x1234, /*pData=*/nullptr, /*size=*/1,
                                                      /*pRoot=*/nullptr);
    EXPECT_EQ(-1, rc);
  });
}

TEST_F(SonyMisc2bSelectorTest_1541, NullRootVariousTagsReturnMinusOne_1541) {
  // Boundary sweep: various tags should not affect the result with null root.
  for (uint16_t tag : {uint16_t{0x0000}, uint16_t{0x0001}, uint16_t{0x00FF}, uint16_t{0x9404}, uint16_t{0xFFFF}}) {
    SCOPED_TRACE(::testing::Message() << "tag=0x" << std::hex << tag);
    EXPECT_NO_THROW({
      const int rc = Exiv2::Internal::sonyMisc2bSelector(tag, /*pData=*/nullptr, /*size=*/0, /*pRoot=*/nullptr);
      EXPECT_EQ(-1, rc);
    });
  }
}

}  // namespace