// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_pentaxmnheader_1484.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PentaxMnHeader;

class PentaxMnHeaderTest_1484 : public ::testing::Test {};

TEST_F(PentaxMnHeaderTest_1484, MemberSizeOfSignature_IsNonZero_1484) {
  PentaxMnHeader header;
  const size_t sigSize = header.sizeOfSignature();
  EXPECT_GT(sigSize, 0u);
}

TEST_F(PentaxMnHeaderTest_1484, MemberSizeOfSignature_IsStableAcrossCalls_1484) {
  PentaxMnHeader header;

  const size_t a = header.sizeOfSignature();
  const size_t b = header.sizeOfSignature();
  const size_t c = header.sizeOfSignature();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(PentaxMnHeaderTest_1484, MemberSizeOfSignature_SameAcrossInstances_1484) {
  PentaxMnHeader h1;
  PentaxMnHeader h2;

  EXPECT_EQ(h1.sizeOfSignature(), h2.sizeOfSignature());
}

TEST_F(PentaxMnHeaderTest_1484, StaticAndMemberSizeOfSignature_Agree_1484) {
  PentaxMnHeader header;

  // Verifies consistency between the static utility and the instance method.
  // This does not assume any particular signature length.
  EXPECT_EQ(PentaxMnHeader::sizeOfSignature(), header.sizeOfSignature());
}

}  // namespace