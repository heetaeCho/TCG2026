// File: test_fuji_mn_header_1457.cpp

#include <gtest/gtest.h>

#include <limits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::FujiMnHeader;

TEST(FujiMnHeaderTest_1457, BaseOffsetReturnsInputForTypicalValue_1457) {
  const FujiMnHeader hdr;

  const size_t mnOffset = 12345u;
  EXPECT_NO_THROW({
    const size_t base = hdr.baseOffset(mnOffset);
    EXPECT_EQ(base, mnOffset);
  });
}

TEST(FujiMnHeaderTest_1457, BaseOffsetHandlesZeroOffset_1457) {
  const FujiMnHeader hdr;

  const size_t mnOffset = 0u;
  EXPECT_NO_THROW({
    const size_t base = hdr.baseOffset(mnOffset);
    EXPECT_EQ(base, 0u);
  });
}

TEST(FujiMnHeaderTest_1457, BaseOffsetHandlesMaxSizeT_1457) {
  const FujiMnHeader hdr;

  const size_t mnOffset = (std::numeric_limits<size_t>::max)();
  EXPECT_NO_THROW({
    const size_t base = hdr.baseOffset(mnOffset);
    EXPECT_EQ(base, mnOffset);
  });
}

}  // namespace