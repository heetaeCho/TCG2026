// =================================================================================================
// TEST_ID: 1438
// File: test_olympus_mnheader_ifdoffset_1438.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::OlympusMnHeader;

class OlympusMnHeaderTest_1438 : public ::testing::Test {
};

TEST_F(OlympusMnHeaderTest_1438, IfdOffsetEqualsSizeOfSignature_1438) {
  OlympusMnHeader hdr;
  EXPECT_EQ(hdr.ifdOffset(), OlympusMnHeader::sizeOfSignature());
}

TEST_F(OlympusMnHeaderTest_1438, IfdOffsetEqualsSizeOfSignatureForConstObject_1438) {
  const OlympusMnHeader hdr;
  EXPECT_EQ(hdr.ifdOffset(), OlympusMnHeader::sizeOfSignature());
}

TEST_F(OlympusMnHeaderTest_1438, IfdOffsetIsStableAcrossRepeatedCalls_1438) {
  OlympusMnHeader hdr;

  const size_t first = hdr.ifdOffset();
  const size_t second = hdr.ifdOffset();
  const size_t third = hdr.ifdOffset();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(first, OlympusMnHeader::sizeOfSignature());
}

TEST_F(OlympusMnHeaderTest_1438, IfdOffsetSameForConstAndNonConstOverloads_1438) {
  OlympusMnHeader hdr;

  const size_t nonConstCall = hdr.ifdOffset();
  const size_t constCall = static_cast<const OlympusMnHeader&>(hdr).ifdOffset();

  EXPECT_EQ(nonConstCall, constCall);
  EXPECT_EQ(constCall, OlympusMnHeader::sizeOfSignature());
}

}  // namespace