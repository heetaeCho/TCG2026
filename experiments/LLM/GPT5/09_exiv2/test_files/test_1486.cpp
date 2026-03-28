// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pentax_mn_header_test_1486.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::PentaxMnHeader;

class PentaxMnHeaderTest_1486 : public ::testing::Test {
 protected:
  PentaxMnHeader header_;
};

TEST_F(PentaxMnHeaderTest_1486, IfdOffsetEqualsSizeOfSignature_1486) {
  const size_t expected = PentaxMnHeader::sizeOfSignature();
  EXPECT_EQ(header_.ifdOffset(), expected);
}

TEST_F(PentaxMnHeaderTest_1486, IfdOffsetIsStableAcrossCalls_1486) {
  const size_t first = header_.ifdOffset();
  const size_t second = header_.ifdOffset();
  const size_t third = header_.ifdOffset();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PentaxMnHeaderTest_1486, IfdOffsetMatchesStaticSizeOfSignatureRepeatedly_1486) {
  const size_t s1 = PentaxMnHeader::sizeOfSignature();
  const size_t o1 = header_.ifdOffset();
  const size_t s2 = PentaxMnHeader::sizeOfSignature();
  const size_t o2 = header_.ifdOffset();

  EXPECT_EQ(o1, s1);
  EXPECT_EQ(o2, s2);
  EXPECT_EQ(o1, o2);
}

TEST_F(PentaxMnHeaderTest_1486, IfdOffsetDoesNotThrow_1486) {
  EXPECT_NO_THROW({
    volatile size_t v = header_.ifdOffset();
    (void)v;
  });

  EXPECT_NO_THROW({
    volatile size_t v = PentaxMnHeader::sizeOfSignature();
    (void)v;
  });
}

}  // namespace