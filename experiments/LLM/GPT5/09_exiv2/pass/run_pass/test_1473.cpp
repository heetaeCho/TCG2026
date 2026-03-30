// File: test_panasonic_mnheader_1473.cpp
// Unit tests for Exiv2::Internal::PanasonicMnHeader (makernote_int.*)
//
// Constraints respected:
// - Treat implementation as black box
// - Only test observable behavior via public interface
// - No private state access

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PanasonicMnHeader;

class PanasonicMnHeaderTest_1473 : public ::testing::Test {};

TEST_F(PanasonicMnHeaderTest_1473, MemberAndStaticSizeOfSignatureMatch_1473) {
  PanasonicMnHeader h;

  const size_t member = h.sizeOfSignature();
  const size_t statik = PanasonicMnHeader::sizeOfSignature();

  // Observable invariant: both APIs represent "size of signature".
  EXPECT_EQ(member, statik);
  EXPECT_GT(member, 0u);
}

TEST_F(PanasonicMnHeaderTest_1473, SizeOfSignatureIsStableAcrossCallsAndInstances_1473) {
  PanasonicMnHeader a;
  PanasonicMnHeader b;

  const size_t a1 = a.sizeOfSignature();
  const size_t a2 = a.sizeOfSignature();
  const size_t b1 = b.sizeOfSignature();

  EXPECT_EQ(a1, a2);
  EXPECT_EQ(a1, b1);
  EXPECT_EQ(a1, PanasonicMnHeader::sizeOfSignature());
}

TEST_F(PanasonicMnHeaderTest_1473, ConstAndNonConstAccessProduceSameSizeOfSignature_1473) {
  PanasonicMnHeader h;
  const PanasonicMnHeader& ch = h;

  const size_t nonconst_value = h.sizeOfSignature();
  const size_t const_value = ch.sizeOfSignature();

  EXPECT_EQ(nonconst_value, const_value);
  EXPECT_EQ(const_value, PanasonicMnHeader::sizeOfSignature());
}

}  // namespace