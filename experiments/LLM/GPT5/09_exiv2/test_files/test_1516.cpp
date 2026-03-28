// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_newfujimn_1516.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Internal Exiv2 headers (available in the Exiv2 source tree build)
#include "makernote_int.hpp"

namespace {

using Exiv2::byte;

constexpr uint16_t kAnyTag = 0x1234;

static size_t FujiMnMinSize() {
  // newFujiMn returns nullptr if size < FujiMnHeader::sizeOfSignature() + 18
  return Exiv2::Internal::FujiMnHeader::sizeOfSignature() + 18u;
}

static std::vector<byte> MakeBuf(size_t n) {
  return std::vector<byte>(n, static_cast<byte>(0xAB));
}

}  // namespace

TEST(NewFujiMnTest_1516, ReturnsNullptrWhenSizeIsZero_1516) {
  const size_t size = 0;
  auto mn = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                      nullptr, size, Exiv2::bigEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST(NewFujiMnTest_1516, ReturnsNullptrWhenSizeIsBelowMinimumByOne_1516) {
  const size_t minSize = FujiMnMinSize();
  ASSERT_GT(minSize, 0u);

  const size_t size = minSize - 1;
  auto buf = MakeBuf(size);

  auto mn = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                      buf.data(), size, Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST(NewFujiMnTest_1516, ReturnsNonNullWhenSizeEqualsMinimum_1516) {
  const size_t minSize = FujiMnMinSize();
  auto buf = MakeBuf(minSize);

  auto mn = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                      buf.data(), buf.size(), Exiv2::bigEndian);
  EXPECT_NE(mn, nullptr);
}

TEST(NewFujiMnTest_1516, ReturnsNonNullWhenSizeIsAboveMinimum_1516) {
  const size_t minSize = FujiMnMinSize();
  auto buf = MakeBuf(minSize + 1);

  auto mn = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                      buf.data(), buf.size(), Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

TEST(NewFujiMnTest_1516, ReturnsDistinctInstancesOnMultipleCallsWhenSizeIsSufficient_1516) {
  const size_t minSize = FujiMnMinSize();
  auto buf = MakeBuf(minSize);

  auto mn1 = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                       buf.data(), buf.size(), Exiv2::bigEndian);
  auto mn2 = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                       buf.data(), buf.size(), Exiv2::bigEndian);

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);
  EXPECT_NE(mn1.get(), mn2.get());
}

TEST(NewFujiMnTest_1516, ReturnedUniquePtrCanBeReset_1516) {
  const size_t minSize = FujiMnMinSize();
  auto buf = MakeBuf(minSize);

  auto mn = Exiv2::Internal::newFujiMn(kAnyTag, Exiv2::ifdIdNotSet, Exiv2::ifdIdNotSet,
                                      buf.data(), buf.size(), Exiv2::bigEndian);
  ASSERT_NE(mn, nullptr);

  mn.reset();
  EXPECT_EQ(mn, nullptr);
}