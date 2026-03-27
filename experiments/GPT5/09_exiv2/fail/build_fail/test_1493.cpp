// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::SigmaMnHeader;

class SigmaMnHeaderTest_1493 : public ::testing::Test {};

TEST_F(SigmaMnHeaderTest_1493, DefaultConstructibleAndCallable_1493) {
  SigmaMnHeader h;
  EXPECT_NO_THROW({
    const auto s = h.sizeOfSignature();
    (void)s;
  });
}

TEST_F(SigmaMnHeaderTest_1493, SizeOfSignatureIsPositive_1493) {
  SigmaMnHeader h;
  EXPECT_GT(h.sizeOfSignature(), static_cast<size_t>(0));
}

TEST_F(SigmaMnHeaderTest_1493, SizeOfSignatureIsStableAcrossCalls_1493) {
  SigmaMnHeader h;
  const auto a = h.sizeOfSignature();
  const auto b = h.sizeOfSignature();
  EXPECT_EQ(a, b);
}

TEST_F(SigmaMnHeaderTest_1493, SizeOfSignatureIsStableAcrossInstances_1493) {
  SigmaMnHeader a;
  SigmaMnHeader b;
  EXPECT_EQ(a.sizeOfSignature(), b.sizeOfSignature());
}

TEST_F(SigmaMnHeaderTest_1493, StaticAndMemberSizeOfSignatureAgree_1493) {
  SigmaMnHeader h;
  const auto member = h.sizeOfSignature();
  const auto statik = SigmaMnHeader::sizeOfSignature();
  EXPECT_EQ(member, statik);
}

}  // namespace