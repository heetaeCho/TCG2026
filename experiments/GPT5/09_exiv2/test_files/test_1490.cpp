// File: test_samsung_mn_header_1490.cpp

#include <gtest/gtest.h>

#include <limits>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::SamsungMnHeader;
using Exiv2::Internal::MnHeader;

class SamsungMnHeaderTest_1490 : public ::testing::Test {};

TEST_F(SamsungMnHeaderTest_1490, BaseOffset_ReturnsInputForZero_1490) {
  SamsungMnHeader h;
  const size_t mnOffset = 0u;

  EXPECT_EQ(h.baseOffset(mnOffset), mnOffset);

  const SamsungMnHeader& ch = h;
  EXPECT_EQ(ch.baseOffset(mnOffset), mnOffset);
}

TEST_F(SamsungMnHeaderTest_1490, BaseOffset_ReturnsInputForTypicalValue_1490) {
  SamsungMnHeader h;
  const size_t mnOffset = 12345u;

  EXPECT_EQ(h.baseOffset(mnOffset), mnOffset);

  const SamsungMnHeader& ch = h;
  EXPECT_EQ(ch.baseOffset(mnOffset), mnOffset);
}

TEST_F(SamsungMnHeaderTest_1490, BaseOffset_ReturnsInputForMaxSizeT_1490) {
  SamsungMnHeader h;
  const size_t mnOffset = (std::numeric_limits<size_t>::max)();

  EXPECT_EQ(h.baseOffset(mnOffset), mnOffset);

  const SamsungMnHeader& ch = h;
  EXPECT_EQ(ch.baseOffset(mnOffset), mnOffset);
}

TEST_F(SamsungMnHeaderTest_1490, BaseOffset_WorksThroughBaseClassInterface_1490) {
  SamsungMnHeader h;
  MnHeader* base = &h;

  const size_t mnOffset = 777u;
  EXPECT_EQ(base->baseOffset(mnOffset), mnOffset);
}

}  // namespace