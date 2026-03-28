// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PentaxDngMnHeader;

class PentaxDngMnHeaderTest_1481 : public ::testing::Test {};

TEST_F(PentaxDngMnHeaderTest_1481, IfdOffsetEqualsSizeOfSignature_1481) {
  PentaxDngMnHeader header;

  const size_t expected = PentaxDngMnHeader::sizeOfSignature();
  const size_t actual = header.ifdOffset();

  EXPECT_EQ(actual, expected);
}

TEST_F(PentaxDngMnHeaderTest_1481, IfdOffsetEqualsSizeOfSignatureOnConstObject_1481) {
  const PentaxDngMnHeader header;

  const size_t expected = PentaxDngMnHeader::sizeOfSignature();
  const size_t actual = header.ifdOffset();

  EXPECT_EQ(actual, expected);
}

TEST_F(PentaxDngMnHeaderTest_1481, IfdOffsetIsStableAcrossMultipleCalls_1481) {
  PentaxDngMnHeader header;

  const size_t first = header.ifdOffset();
  const size_t second = header.ifdOffset();
  const size_t expected = PentaxDngMnHeader::sizeOfSignature();

  EXPECT_EQ(first, second);
  EXPECT_EQ(first, expected);
}

TEST_F(PentaxDngMnHeaderTest_1481, SizeOfSignatureIsStableAcrossMultipleCalls_1481) {
  const size_t first = PentaxDngMnHeader::sizeOfSignature();
  const size_t second = PentaxDngMnHeader::sizeOfSignature();

  EXPECT_EQ(first, second);
}

}  // namespace