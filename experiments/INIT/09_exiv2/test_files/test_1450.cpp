// File: test_omsystem_mn_header_1450.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::OMSystemMnHeader;

class OMSystemMnHeaderTest_1450 : public ::testing::Test {};

TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetReturnsInputForZero_1450) {
  const OMSystemMnHeader hdr;
  const size_t mnOffset = 0;
  EXPECT_EQ(hdr.baseOffset(mnOffset), mnOffset);
}

TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetReturnsInputForTypicalValue_1450) {
  const OMSystemMnHeader hdr;
  const size_t mnOffset = 12345u;
  EXPECT_EQ(hdr.baseOffset(mnOffset), mnOffset);
}

TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetReturnsInputForMaxSizeT_1450) {
  const OMSystemMnHeader hdr;
  const size_t mnOffset = (std::numeric_limits<size_t>::max)();
  EXPECT_EQ(hdr.baseOffset(mnOffset), mnOffset);
}

TEST_F(OMSystemMnHeaderTest_1450, BaseOffsetMatchesEachInputAcrossMultipleCalls_1450) {
  const OMSystemMnHeader hdr;

  const size_t a = 1u;
  const size_t b = 999u;
  const size_t c = 0u;

  EXPECT_EQ(hdr.baseOffset(a), a);
  EXPECT_EQ(hdr.baseOffset(b), b);
  EXPECT_EQ(hdr.baseOffset(c), c);
}

}  // namespace