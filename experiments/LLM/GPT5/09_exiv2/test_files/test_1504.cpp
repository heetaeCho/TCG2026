// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_casio2_mnheader_1504.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// Fixture for TEST_ID 1504
class Casio2MnHeaderTest_1504 : public ::testing::Test {};

TEST_F(Casio2MnHeaderTest_1504, SizeEqualsSizeOfSignature_1504) {
  Exiv2::Internal::Casio2MnHeader header;

  const size_t expected = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  const size_t actual = header.size();

  EXPECT_EQ(expected, actual);
}

TEST_F(Casio2MnHeaderTest_1504, SizeIsStableAcrossRepeatedCalls_1504) {
  Exiv2::Internal::Casio2MnHeader header;

  const size_t s1 = header.size();
  const size_t s2 = header.size();
  const size_t s3 = header.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(Casio2MnHeaderTest_1504, SizeWorksForConstObject_1504) {
  const Exiv2::Internal::Casio2MnHeader header;

  const size_t expected = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  const size_t actual = header.size();

  EXPECT_EQ(expected, actual);
}

TEST_F(Casio2MnHeaderTest_1504, SizeOfSignatureIsStableAcrossRepeatedCalls_1504) {
  const size_t a = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  const size_t b = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();
  const size_t c = Exiv2::Internal::Casio2MnHeader::sizeOfSignature();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

}  // namespace