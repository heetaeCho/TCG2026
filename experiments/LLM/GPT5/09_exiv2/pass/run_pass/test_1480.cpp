// SPDX-License-Identifier: MIT
// File: test_pentaxdng_mnheader_baseoffset_1480.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "makernote_int.hpp"

namespace {

// TEST_ID = 1480
class PentaxDngMnHeaderTest_1480 : public ::testing::Test {
 protected:
  Exiv2::Internal::PentaxDngMnHeader hdr_;
};

TEST_F(PentaxDngMnHeaderTest_1480, BaseOffset_ReturnsInputForZero_1480) {
  const size_t mnOffset = 0u;
  EXPECT_EQ(hdr_.baseOffset(mnOffset), mnOffset);
}

TEST_F(PentaxDngMnHeaderTest_1480, BaseOffset_ReturnsInputForTypicalValue_1480) {
  const size_t mnOffset = 12345u;
  EXPECT_EQ(hdr_.baseOffset(mnOffset), mnOffset);
}

TEST_F(PentaxDngMnHeaderTest_1480, BaseOffset_ReturnsInputForMaxSizeT_1480) {
  const size_t mnOffset = (std::numeric_limits<size_t>::max)();
  EXPECT_EQ(hdr_.baseOffset(mnOffset), mnOffset);
}

TEST_F(PentaxDngMnHeaderTest_1480, BaseOffset_CanBeCalledOnConstInstance_1480) {
  const Exiv2::Internal::PentaxDngMnHeader& constHdr = hdr_;
  const size_t mnOffset = 77u;
  EXPECT_EQ(constHdr.baseOffset(mnOffset), mnOffset);
}

}  // namespace