// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_omssystem_mnheader_1449.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::OMSystemMnHeader;

class OMSystemMnHeaderTest_1449 : public ::testing::Test {};

TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetEqualsSizeOfSignature_NonConst_1449) {
  OMSystemMnHeader h;
  const size_t expected = OMSystemMnHeader::sizeOfSignature();
  EXPECT_EQ(h.ifdOffset(), expected);
}

TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetEqualsSizeOfSignature_Const_1449) {
  OMSystemMnHeader h;
  const OMSystemMnHeader& ch = h;

  const size_t expected = OMSystemMnHeader::sizeOfSignature();
  EXPECT_EQ(ch.ifdOffset(), expected);
}

TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetIsStableAcrossCalls_1449) {
  OMSystemMnHeader h;

  const size_t first = h.ifdOffset();
  const size_t second = h.ifdOffset();
  const size_t third = h.ifdOffset();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(OMSystemMnHeaderTest_1449, IfdOffsetMatchesBetweenConstAndNonConstAccess_1449) {
  OMSystemMnHeader h;
  const OMSystemMnHeader& ch = h;

  EXPECT_EQ(h.ifdOffset(), ch.ifdOffset());
}

}  // namespace