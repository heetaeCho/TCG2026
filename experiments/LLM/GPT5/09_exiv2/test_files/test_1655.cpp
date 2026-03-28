// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffdecoder_visitSubIfd_1655.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

// Internal headers (as referenced by the prompt)
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffSubIfd;
using Exiv2::Internal::IfdId;

class TiffDecoderVisitSubIfdTest_1655 : public ::testing::Test {
 protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;

  // Keep decoder construction in one place so tests focus on observable behavior.
  TiffDecoderVisitSubIfdTest_1655()
      : decoder_(exif_, iptc_, xmp_, /*pRoot=*/nullptr,
                 /*findDecoderFct=*/Exiv2::Internal::FindDecoderFct()) {}

  TiffDecoder decoder_;
};

TEST_F(TiffDecoderVisitSubIfdTest_1655, VisitSubIfdWithNullptrDoesNotThrow_1655) {
  const auto exifSizeBefore = exif_.count();
  const auto iptcSizeBefore = iptc_.count();
  const auto xmpSizeBefore  = xmp_.count();

  EXPECT_NO_THROW(decoder_.visitSubIfd(nullptr));

  // Only verify stable, externally observable state through public APIs.
  EXPECT_EQ(exif_.count(), exifSizeBefore);
  EXPECT_EQ(iptc_.count(), iptcSizeBefore);
  EXPECT_EQ(xmp_.count(), xmpSizeBefore);
}

TEST_F(TiffDecoderVisitSubIfdTest_1655, VisitSubIfdWithValidObjectDoesNotThrow_1655) {
  // Construct a minimal TiffSubIfd using only its public constructor.
  // Use explicit casts to avoid assuming specific IfdId enumerators exist.
  TiffSubIfd subIfd(/*tag=*/0x014a, static_cast<IfdId>(0), static_cast<IfdId>(0));

  EXPECT_NO_THROW(decoder_.visitSubIfd(&subIfd));
}

TEST_F(TiffDecoderVisitSubIfdTest_1655, VisitSubIfdCalledMultipleTimesDoesNotThrow_1655) {
  TiffSubIfd subIfd(/*tag=*/0x014a, static_cast<IfdId>(0), static_cast<IfdId>(0));

  EXPECT_NO_THROW(decoder_.visitSubIfd(&subIfd));
  EXPECT_NO_THROW(decoder_.visitSubIfd(&subIfd));
  EXPECT_NO_THROW(decoder_.visitSubIfd(&subIfd));
}

TEST_F(TiffDecoderVisitSubIfdTest_1655, VisitSubIfdNullptrCalledMultipleTimesDoesNotThrow_1655) {
  EXPECT_NO_THROW(decoder_.visitSubIfd(nullptr));
  EXPECT_NO_THROW(decoder_.visitSubIfd(nullptr));
  EXPECT_NO_THROW(decoder_.visitSubIfd(nullptr));
}

}  // namespace