// File: test_nikon3mnheader_ifdoffset_1467.cpp
// TEST_ID: 1467

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

// Keep the fixture name tied to TEST_ID as requested.
class Nikon3MnHeaderTest_1467 : public ::testing::Test {};

}  // namespace

TEST_F(Nikon3MnHeaderTest_1467, IfdOffsetEqualsSizeOfSignatureAfterDefaultConstruction_1467) {
  Exiv2::Internal::Nikon3MnHeader header;

  // Observable behavior from provided implementation:
  // ifdOffset() returns internal start_, and ctor initializes start_ to sizeOfSignature().
  EXPECT_EQ(header.ifdOffset(), Exiv2::Internal::Nikon3MnHeader::sizeOfSignature());
}

TEST_F(Nikon3MnHeaderTest_1467, IfdOffsetIsStableAcrossMultipleCalls_1467) {
  Exiv2::Internal::Nikon3MnHeader header;

  const size_t first = header.ifdOffset();
  const size_t second = header.ifdOffset();
  const size_t third = header.ifdOffset();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(Nikon3MnHeaderTest_1467, IfdOffsetMatchesAfterCopyConstruction_1467) {
  Exiv2::Internal::Nikon3MnHeader original;
  const size_t expected = original.ifdOffset();

  Exiv2::Internal::Nikon3MnHeader copy = original;
  EXPECT_EQ(copy.ifdOffset(), expected);
}

TEST_F(Nikon3MnHeaderTest_1467, IfdOffsetMatchesAfterCopyAssignment_1467) {
  Exiv2::Internal::Nikon3MnHeader source;
  const size_t expected = source.ifdOffset();

  Exiv2::Internal::Nikon3MnHeader target;
  target = source;

  EXPECT_EQ(target.ifdOffset(), expected);
}