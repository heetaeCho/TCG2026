// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon2_mnheader_1460.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// TEST_ID = 1460

TEST(Nikon2MnHeaderTest_1460, SizeOfSignature_IsNonZero_1460) {
  Exiv2::Internal::Nikon2MnHeader header;
  const size_t n = header.sizeOfSignature();
  EXPECT_GT(n, static_cast<size_t>(0));
}

TEST(Nikon2MnHeaderTest_1460, SizeOfSignature_StableAcrossCalls_1460) {
  Exiv2::Internal::Nikon2MnHeader header;

  const size_t a = header.sizeOfSignature();
  const size_t b = header.sizeOfSignature();
  const size_t c = header.sizeOfSignature();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST(Nikon2MnHeaderTest_1460, SizeOfSignature_ConsistentAcrossInstances_1460) {
  Exiv2::Internal::Nikon2MnHeader h1;
  Exiv2::Internal::Nikon2MnHeader h2;

  EXPECT_EQ(h1.sizeOfSignature(), h2.sizeOfSignature());
}

TEST(Nikon2MnHeaderTest_1460, SizeOfSignature_StaticAndMemberMatch_1460) {
  Exiv2::Internal::Nikon2MnHeader header;

  const size_t memberSize = header.sizeOfSignature();
  const size_t staticSize = Exiv2::Internal::Nikon2MnHeader::sizeOfSignature();

  EXPECT_EQ(memberSize, staticSize);
}

}  // namespace