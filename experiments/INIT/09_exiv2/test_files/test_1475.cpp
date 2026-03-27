// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_panasonic_mnheader_1475.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PanasonicMnHeader;

TEST(PanasonicMnHeaderTest_1475, DefaultConstructible_1475) {
  PanasonicMnHeader h;
  (void)h;
  SUCCEED();
}

TEST(PanasonicMnHeaderTest_1475, IfdOffset_IsStableAcrossRepeatedCalls_1475) {
  PanasonicMnHeader h;

  const size_t a = h.ifdOffset();
  const size_t b = h.ifdOffset();
  const size_t c = h.ifdOffset();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(PanasonicMnHeaderTest_1475, Size_IsStableAcrossRepeatedCalls_1475) {
  PanasonicMnHeader h;

  const size_t a = h.size();
  const size_t b = h.size();
  const size_t c = h.size();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(PanasonicMnHeaderTest_1475, ConstAndNonConstIfdOffsetAgree_1475) {
  PanasonicMnHeader h;
  const PanasonicMnHeader& ch = h;

  const size_t nonConstVal = h.ifdOffset();
  const size_t constVal = ch.ifdOffset();

  EXPECT_EQ(nonConstVal, constVal);
}

TEST(PanasonicMnHeaderTest_1475, ConstAndNonConstSizeAgree_1475) {
  PanasonicMnHeader h;
  const PanasonicMnHeader& ch = h;

  const size_t nonConstVal = h.size();
  const size_t constVal = ch.size();

  EXPECT_EQ(nonConstVal, constVal);
}

TEST(PanasonicMnHeaderTest_1475, SizeOfSignature_IsStableAcrossCalls_1475) {
  const size_t a = PanasonicMnHeader::sizeOfSignature();
  const size_t b = PanasonicMnHeader::sizeOfSignature();
  const size_t c = PanasonicMnHeader::sizeOfSignature();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(PanasonicMnHeaderTest_1475, InstanceSizeOfSignature_MatchesStatic_1475) {
  PanasonicMnHeader h;

  const size_t s = PanasonicMnHeader::sizeOfSignature();
  const size_t i1 = h.sizeOfSignature();
  const size_t i2 = h.sizeOfSignature();

  EXPECT_EQ(s, i1);
  EXPECT_EQ(i1, i2);
}

TEST(PanasonicMnHeaderTest_1475, Read_WithEmptyBuffer_IsDeterministic_1475) {
  PanasonicMnHeader h;

  // Boundary: size==0 with null pointer is a safe, conventional input.
  const bool r1 = h.read(nullptr, 0u, Exiv2::littleEndian);
  const bool r2 = h.read(nullptr, 0u, Exiv2::littleEndian);

  EXPECT_EQ(r1, r2);
}

TEST(PanasonicMnHeaderTest_1475, Read_WithSameBytes_IsDeterministic_1475) {
  PanasonicMnHeader h;

  std::vector<Exiv2::byte> data(16, static_cast<Exiv2::byte>(0));
  const bool r1 = h.read(data.data(), data.size(), Exiv2::littleEndian);

  PanasonicMnHeader h2;
  const bool r2 = h2.read(data.data(), data.size(), Exiv2::littleEndian);

  EXPECT_EQ(r1, r2);
}

}  // namespace