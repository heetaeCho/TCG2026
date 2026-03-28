// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_olympus2_mn_header_1443.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// The class lives in Exiv2::Internal.
using Exiv2::Internal::Olympus2MnHeader;

class Olympus2MnHeaderTest_1443 : public ::testing::Test {
 protected:
  Olympus2MnHeader hdr_;
};

TEST_F(Olympus2MnHeaderTest_1443, IfdOffsetEqualsSizeOfSignature_NonConstCall_1443) {
  // Observable contract from implementation: ifdOffset() == sizeOfSignature()
  const size_t sig = Olympus2MnHeader::sizeOfSignature();
  const size_t off = hdr_.ifdOffset();
  EXPECT_EQ(off, sig);
}

TEST_F(Olympus2MnHeaderTest_1443, IfdOffsetEqualsSizeOfSignature_ConstCall_1443) {
  const Olympus2MnHeader& chdr = hdr_;

  // Disambiguate overloads if both const/non-const ifdOffset exist.
  const auto ifdOffsetConst =
      static_cast<size_t (Olympus2MnHeader::*)() const>(&Olympus2MnHeader::ifdOffset);

  const size_t sig = Olympus2MnHeader::sizeOfSignature();
  const size_t off = (chdr.*ifdOffsetConst)();

  EXPECT_EQ(off, sig);
}

TEST_F(Olympus2MnHeaderTest_1443, IfdOffsetIsStableAcrossRepeatedCalls_1443) {
  const size_t first = hdr_.ifdOffset();
  const size_t second = hdr_.ifdOffset();
  EXPECT_EQ(second, first);
}

TEST_F(Olympus2MnHeaderTest_1443, IfdOffsetConsistentAcrossInstances_1443) {
  Olympus2MnHeader other;

  const size_t sig1 = Olympus2MnHeader::sizeOfSignature();
  const size_t sig2 = Olympus2MnHeader::sizeOfSignature();
  EXPECT_EQ(sig2, sig1);

  EXPECT_EQ(hdr_.ifdOffset(), sig1);
  EXPECT_EQ(other.ifdOffset(), sig1);
}

}  // namespace