// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymnheader_1498.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::SonyMnHeader;

class SonyMnHeaderTest_1498 : public ::testing::Test {};

TEST_F(SonyMnHeaderTest_1498, SizeOfSignatureIsNonZero_1498) {
  SonyMnHeader header;
  const size_t sigSize = header.sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

TEST_F(SonyMnHeaderTest_1498, SizeOfSignatureStableAcrossRepeatedCalls_1498) {
  SonyMnHeader header;
  const size_t first = header.sizeOfSignature();
  const size_t second = header.sizeOfSignature();
  const size_t third = header.sizeOfSignature();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(SonyMnHeaderTest_1498, SizeOfSignatureSameAcrossDifferentInstances_1498) {
  SonyMnHeader a;
  SonyMnHeader b;

  EXPECT_EQ(a.sizeOfSignature(), b.sizeOfSignature());
}

}  // namespace