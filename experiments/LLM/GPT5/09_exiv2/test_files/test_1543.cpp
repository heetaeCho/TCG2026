// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::Cr2Header (partial interface)
// File: test_cr2header_int_test_1543.cpp

#include <gtest/gtest.h>

#include <cstdint>

#include "cr2header_int.hpp"

namespace {

class Cr2HeaderTest_1543 : public ::testing::Test {};

TEST_F(Cr2HeaderTest_1543, Offset2Addr_ReturnsExpectedConstant_1543) {
  // Observable behavior through the public static interface.
  // We only assert what the interface exposes: the returned value.
  EXPECT_EQ(Exiv2::Internal::Cr2Header::offset2addr(), static_cast<uint32_t>(12));
}

TEST_F(Cr2HeaderTest_1543, Offset2Addr_IsStableAcrossMultipleCalls_1543) {
  // Boundary-ish: repeated calls should be consistent (no state involved in a static function).
  const uint32_t first = Exiv2::Internal::Cr2Header::offset2addr();
  const uint32_t second = Exiv2::Internal::Cr2Header::offset2addr();
  EXPECT_EQ(first, second);
}

TEST_F(Cr2HeaderTest_1543, Offset2Addr_IsNonZero_1543) {
  // Simple sanity/boundary check on the observable output.
  EXPECT_NE(Exiv2::Internal::Cr2Header::offset2addr(), static_cast<uint32_t>(0));
}

}  // namespace