// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_panasonic_mnheader_1474.cpp
//
// Unit tests for Exiv2::Internal::PanasonicMnHeader
// Constraints:
//  - Treat implementation as a black box
//  - Test only observable behavior through public interface

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// TEST_ID is 1474
class PanasonicMnHeaderTest_1474 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMnHeader hdr_;
};

TEST_F(PanasonicMnHeaderTest_1474, SizeEqualsSizeOfSignature_1474) {
  const auto expected = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature();
  EXPECT_EQ(hdr_.size(), expected);
}

TEST_F(PanasonicMnHeaderTest_1474, ConstSizeEqualsSizeOfSignature_1474) {
  const Exiv2::Internal::PanasonicMnHeader& chdr = hdr_;
  const auto expected = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature();
  EXPECT_EQ(chdr.size(), expected);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeIsStableAcrossMultipleCalls_1474) {
  const auto s1 = hdr_.size();
  const auto s2 = hdr_.size();
  const auto s3 = hdr_.size();
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeMatchesConstAndNonConstCalls_1474) {
  const Exiv2::Internal::PanasonicMnHeader& chdr = hdr_;
  EXPECT_EQ(hdr_.size(), chdr.size());
}

TEST_F(PanasonicMnHeaderTest_1474, SizeOfSignatureIsDeterministic_1474) {
  const auto a = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature();
  const auto b = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature();
  EXPECT_EQ(a, b);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeDoesNotThrow_1474) {
  EXPECT_NO_THROW((void)hdr_.size());
  const Exiv2::Internal::PanasonicMnHeader& chdr = hdr_;
  EXPECT_NO_THROW((void)chdr.size());
}

}  // namespace