// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3mnheader_baseoffset_1469.cpp

#include <gtest/gtest.h>

#include <limits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::Nikon3MnHeader;

class Nikon3MnHeaderTest_1469 : public ::testing::Test {};

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetAddsTenForZero_1469) {
  const Nikon3MnHeader hdr;
  EXPECT_EQ(hdr.baseOffset(0u), static_cast<size_t>(10u));
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetAddsTenForSmallValues_1469) {
  const Nikon3MnHeader hdr;

  EXPECT_EQ(hdr.baseOffset(1u), static_cast<size_t>(11u));
  EXPECT_EQ(hdr.baseOffset(9u), static_cast<size_t>(19u));
  EXPECT_EQ(hdr.baseOffset(10u), static_cast<size_t>(20u));
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetAddsTenForTypicalValue_1469) {
  const Nikon3MnHeader hdr;

  const size_t mnOffset = 12345u;
  EXPECT_EQ(hdr.baseOffset(mnOffset), mnOffset + static_cast<size_t>(10u));
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetHandlesNearMaxWithoutOverflow_1469) {
  const Nikon3MnHeader hdr;

  // Boundary: largest value that can be safely incremented by 10 without overflow.
  const size_t mnOffset = (std::numeric_limits<size_t>::max)() - static_cast<size_t>(10u);
  EXPECT_EQ(hdr.baseOffset(mnOffset), (std::numeric_limits<size_t>::max)());
}

}  // namespace