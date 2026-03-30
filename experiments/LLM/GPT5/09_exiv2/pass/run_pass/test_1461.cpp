// SPDX-License-Identifier: (GPL-2.0-or-later OR LGPL-2.1-or-later)
// Tests for Exiv2::Internal::Nikon2MnHeader
//
// File: makernote_int_nikon2mnheader_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::Nikon2MnHeader;

class Nikon2MnHeaderTest_1461 : public ::testing::Test {};

TEST_F(Nikon2MnHeaderTest_1461, StaticSizeOfSignature_IsNonZero_1461) {
  const size_t sig = Nikon2MnHeader::sizeOfSignature();
  EXPECT_GT(sig, 0u);
}

TEST_F(Nikon2MnHeaderTest_1461, SizeConst_EqualsStaticSignature_1461) {
  const Nikon2MnHeader h{};
  EXPECT_EQ(h.size(), Nikon2MnHeader::sizeOfSignature());
}

TEST_F(Nikon2MnHeaderTest_1461, SizeNonConst_EqualsStaticSignature_1461) {
  Nikon2MnHeader h{};
  // Non-const call (if a non-const overload exists, it will be selected here).
  const size_t s = h.size();
  EXPECT_EQ(s, Nikon2MnHeader::sizeOfSignature());
}

TEST_F(Nikon2MnHeaderTest_1461, Size_ConsistentBetweenConstAndNonConstViews_1461) {
  Nikon2MnHeader h{};
  const Nikon2MnHeader& ch = h;

  const size_t nonConstSize = h.size();
  const size_t constSize = ch.size();

  EXPECT_EQ(nonConstSize, constSize);
  EXPECT_EQ(constSize, Nikon2MnHeader::sizeOfSignature());
}

TEST_F(Nikon2MnHeaderTest_1461, Size_IsStableAcrossMultipleCalls_1461) {
  Nikon2MnHeader h{};
  const Nikon2MnHeader& ch = h;

  const size_t first = ch.size();
  const size_t second = ch.size();
  const size_t third = ch.size();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(first, Nikon2MnHeader::sizeOfSignature());
}

TEST_F(Nikon2MnHeaderTest_1461, IfdOffset_IsStableAcrossMultipleCalls_1461) {
  // We only assert stability and basic type properties without inferring semantics.
  Nikon2MnHeader h{};
  const Nikon2MnHeader& ch = h;

  const size_t a = ch.ifdOffset();
  const size_t b = ch.ifdOffset();
  const size_t c = ch.ifdOffset();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);

  // Boundary sanity: size_t is unsigned, so this is always true, but it documents the expectation.
  EXPECT_GE(a, 0u);
}

}  // namespace