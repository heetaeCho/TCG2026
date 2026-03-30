// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3mnheader_1466.cpp
//
// Unit tests for Exiv2::Internal::Nikon3MnHeader
//
// Constraints honored:
// - Treat implementation as a black box (test only observable behavior via public API).
// - No private/internal state access.
// - No re-implementation of logic.

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace Exiv2::Internal {
namespace {

class Nikon3MnHeaderTest_1466 : public ::testing::Test {};

TEST_F(Nikon3MnHeaderTest_1466, DefaultConstructedSizeEqualsSizeOfSignature_1466) {
  Nikon3MnHeader header;

  const size_t s = header.size();
  const size_t sig = Nikon3MnHeader::sizeOfSignature();

  EXPECT_EQ(s, sig);
}

TEST_F(Nikon3MnHeaderTest_1466, ConstObjectSizeEqualsSizeOfSignature_1466) {
  const Nikon3MnHeader header;

  const size_t s = header.size();
  const size_t sig = Nikon3MnHeader::sizeOfSignature();

  EXPECT_EQ(s, sig);
}

TEST_F(Nikon3MnHeaderTest_1466, PolymorphicCallThroughMnHeaderReturnsSignatureSize_1466) {
  Nikon3MnHeader derived;
  MnHeader* base = &derived;

  const size_t s = base->size();
  const size_t sig = Nikon3MnHeader::sizeOfSignature();

  EXPECT_EQ(s, sig);
}

TEST_F(Nikon3MnHeaderTest_1466, SizeIsStableAcrossMultipleCalls_1466) {
  Nikon3MnHeader header;

  const size_t s1 = header.size();
  const size_t s2 = header.size();
  const size_t s3 = header.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(Nikon3MnHeaderTest_1466, SizeOfSignatureIsStableAcrossMultipleCalls_1466) {
  const size_t a = Nikon3MnHeader::sizeOfSignature();
  const size_t b = Nikon3MnHeader::sizeOfSignature();
  const size_t c = Nikon3MnHeader::sizeOfSignature();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

}  // namespace
}  // namespace Exiv2::Internal