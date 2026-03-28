// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffdecoder_visitimageentry_1653.cpp
//
// Tests for Exiv2::Internal::TiffDecoder::visitImageEntry
// The TEST_ID is 1653

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"   // Exiv2::Internal::TiffDecoder, FindDecoderFct, etc.
#include <exiv2/exiv2.hpp>       // Exiv2::ExifData, IptcData, XmpData

namespace {

using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::FindDecoderFct;
using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffImageEntry;

class TiffDecoderVisitImageEntryTest_1653 : public ::testing::Test {
 protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;

  // In many Exiv2 call paths, the root component may be managed elsewhere; for this unit
  // test we use nullptr because visitImageEntry only takes the entry pointer.
  TiffComponent* root_ = nullptr;

  // Provide a default-constructed decoder-finder functor (no external dependencies).
  // (If FindDecoderFct is a std::function, this is an empty function object.)
  FindDecoderFct findDecoder_{};

  TiffDecoder makeDecoder() {
    return TiffDecoder(exif_, iptc_, xmp_, root_, findDecoder_);
  }
};

TEST_F(TiffDecoderVisitImageEntryTest_1653, AcceptsNullptrWithoutThrow_1653) {
  TiffDecoder decoder = makeDecoder();

  // Boundary / error-like input: nullptr image entry.
  // Observable behavior we can assert without relying on internals: does not throw.
  EXPECT_NO_THROW(decoder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
}

TEST_F(TiffDecoderVisitImageEntryTest_1653, RepeatedNullptrCallsDoNotThrow_1653) {
  TiffDecoder decoder = makeDecoder();

  // Boundary: repeated calls with the same (null) pointer should be safe.
  EXPECT_NO_THROW(decoder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
  EXPECT_NO_THROW(decoder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
  EXPECT_NO_THROW(decoder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
}

TEST_F(TiffDecoderVisitImageEntryTest_1653, WorksWithDefaultConstructedFinder_1653) {
  // Normal construction path for this unit: FindDecoderFct left empty/default.
  // Observable behavior: constructing and invoking visitImageEntry(nullptr) does not throw.
  TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, /*findDecoderFct=*/FindDecoderFct{});

  EXPECT_NO_THROW(decoder.visitImageEntry(static_cast<TiffImageEntry*>(nullptr)));
}

}  // namespace