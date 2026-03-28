// SPDX-License-Identifier: GPL-2.0-or-later
// File: makernote_int_newcasiomn_test.cpp
//
// Unit tests for Exiv2::Internal::newCasioMn (black-box via public interface)

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::newCasioMn, IfdId, TiffIfdMakernote
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder (as used by Exiv2)

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::newCasioMn;

class CasioMnTest_1533 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeData(const std::initializer_list<int> vals) {
    std::vector<byte> out;
    out.reserve(vals.size());
    for (int v : vals) out.push_back(static_cast<byte>(v));
    return out;
  }
};

TEST_F(CasioMnTest_1533, ReturnsNullWhenSizeIsZero_1533) {
  const std::vector<byte> data;  // empty
  auto mn = newCasioMn(/*tag=*/0x0001, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      /*pData=*/data.data(), /*size=*/0u, /*byteOrder=*/ByteOrder::littleEndian);
  EXPECT_FALSE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNullWhenSizeLessThan14AndNoQvcHeader_1533) {
  // size = 13 (<14), and does NOT match "QVC\0\0\0" in first 6 bytes
  auto data = MakeData({'N', 'O', 'P', 0, 0, 0, 1, 2, 3, 4, 5, 6, 7});
  ASSERT_EQ(data.size(), 13u);

  auto mn = newCasioMn(/*tag=*/0x0002, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  EXPECT_FALSE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNullWhenSizeEquals6EvenIfPrefixIsQvcWithoutNulls_1533) {
  // size = 6 does NOT satisfy (size > 6), so QVC prefix alone must not trigger the header path.
  auto data = MakeData({'Q', 'V', 'C', 'X', 'Y', 'Z'});
  ASSERT_EQ(data.size(), 6u);

  auto mn = newCasioMn(/*tag=*/0x0003, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  EXPECT_FALSE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNonNullWhenQvcHeaderPresentAndSizeIs7_1533) {
  // size = 7 (>6) and first 6 bytes match "QVC\0\0\0" => should return non-null
  auto data = MakeData({'Q', 'V', 'C', 0, 0, 0, 0xAB});
  ASSERT_EQ(data.size(), 7u);

  auto mn = newCasioMn(/*tag=*/0x0004, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  ASSERT_TRUE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNonNullWhenQvcHeaderPresentAndSizeIs13_1533) {
  // size = 13 (<14) but header path should take precedence and still return non-null
  auto data = MakeData({'Q', 'V', 'C', 0, 0, 0, 1, 2, 3, 4, 5, 6, 7});
  ASSERT_EQ(data.size(), 13u);

  auto mn = newCasioMn(/*tag=*/0x0005, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  ASSERT_TRUE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNonNullWhenSizeIs14AndHeaderNotPresent_1533) {
  // size = 14 (>=14) and no QVC header => should return non-null (via the >=14 path)
  auto data = MakeData({'X', 'Y', 'Z', 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8});
  ASSERT_EQ(data.size(), 14u);

  auto mn = newCasioMn(/*tag=*/0x0006, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  ASSERT_TRUE(mn);
}

TEST_F(CasioMnTest_1533, ReturnsNullWhenSizeIs7ButHeaderDoesNotExactlyMatch_1533) {
  // size = 7 (>6) but first 6 bytes are close to QVC header yet not equal => should fall through;
  // since size < 14, it should return null.
  auto data = MakeData({'Q', 'V', 'C', 0, 0, 1, 0xCD});  // last of first 6 differs
  ASSERT_EQ(data.size(), 7u);

  auto mn = newCasioMn(/*tag=*/0x0007, /*group=*/IfdId::exifId, /*unused=*/IfdId::exifId,
                      data.data(), data.size(), ByteOrder::littleEndian);
  EXPECT_FALSE(mn);
}

}  // namespace