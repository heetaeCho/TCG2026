// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffdecoder_visitifdmakernote_1657.cpp
//
// Unit tests for Exiv2::Internal::TiffDecoder::visitIfdMakernote
// based strictly on observable behavior through the public interface.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp.hpp>
#include <exiv2/types.hpp>

// Internal headers (used by the production code)
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"  // for MnHeader (complete type)

#include <cstdint>
#include <string>

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

class TiffDecoderIfdMakernoteTest_1657 : public ::testing::Test {
protected:
  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;

  // Construct decoder with minimal dependencies; visitIfdMakernote only touches ExifData.
  Exiv2::Internal::TiffDecoder makeDecoder() {
    Exiv2::Internal::FindDecoderFct fct{};  // default (not used by visitIfdMakernote)
    return Exiv2::Internal::TiffDecoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, fct);
  }

  // Helper to create a real TiffIfdMakernote with a valid MnHeader instance.
  // We avoid assuming anything about its internals; we only use public APIs.
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> makeMakernote() {
    // Use a concrete MnHeader implementation available in Exiv2 internals.
    // If your tree uses a different concrete header type, adjust here accordingly.
    std::unique_ptr<Exiv2::Internal::MnHeader> header(new Exiv2::Internal::MnHeader);

    // Tag/group values are not relevant to visitIfdMakernote observable behavior.
    constexpr uint16_t kTag = 0x0001;
    constexpr Exiv2::IfdId kGroup = Exiv2::ifd0Id;
    constexpr Exiv2::IfdId kMnGroup = Exiv2::makerIfdId;

    return std::unique_ptr<Exiv2::Internal::TiffIfdMakernote>(
        new Exiv2::Internal::TiffIfdMakernote(kTag, kGroup, kMnGroup, std::move(header), /*hasNext=*/false));
  }
};

TEST_F(TiffDecoderIfdMakernoteTest_1657, LittleEndianSetsOffsetAndByteOrderII_1657) {
  auto decoder = makeDecoder();
  auto mn = makeMakernote();

  mn->setByteOrder(littleEndian);

  const auto expectedOffset = static_cast<uint32_t>(mn->mnOffset());
  decoder.visitIfdMakernote(mn.get());

  EXPECT_EQ(exif_["Exif.MakerNote.Offset"].toInt64(0), static_cast<int64_t>(expectedOffset));
  EXPECT_EQ(exif_["Exif.MakerNote.ByteOrder"].toString(), std::string("II"));
}

TEST_F(TiffDecoderIfdMakernoteTest_1657, BigEndianSetsOffsetAndByteOrderMM_1657) {
  auto decoder = makeDecoder();
  auto mn = makeMakernote();

  mn->setByteOrder(bigEndian);

  const auto expectedOffset = static_cast<uint32_t>(mn->mnOffset());
  decoder.visitIfdMakernote(mn.get());

  EXPECT_EQ(exif_["Exif.MakerNote.Offset"].toInt64(0), static_cast<int64_t>(expectedOffset));
  EXPECT_EQ(exif_["Exif.MakerNote.ByteOrder"].toString(), std::string("MM"));
}

TEST_F(TiffDecoderIfdMakernoteTest_1657, InvalidByteOrderDoesNotOverwriteExistingByteOrder_1657) {
  auto decoder = makeDecoder();
  auto mn = makeMakernote();

  // Seed an existing value to verify "invalidByteOrder" case doesn't change it.
  exif_["Exif.MakerNote.ByteOrder"] = std::string("PRESET");

  mn->setByteOrder(invalidByteOrder);

  const auto expectedOffset = static_cast<uint32_t>(mn->mnOffset());
  decoder.visitIfdMakernote(mn.get());

  // Offset is always written.
  EXPECT_EQ(exif_["Exif.MakerNote.Offset"].toInt64(0), static_cast<int64_t>(expectedOffset));
  // ByteOrder should remain unchanged when invalidByteOrder is reported.
  EXPECT_EQ(exif_["Exif.MakerNote.ByteOrder"].toString(), std::string("PRESET"));
}

TEST_F(TiffDecoderIfdMakernoteTest_1657, MultipleCallsUpdateByteOrderAccordingToObject_1657) {
  auto decoder = makeDecoder();
  auto mn = makeMakernote();

  mn->setByteOrder(littleEndian);
  decoder.visitIfdMakernote(mn.get());
  EXPECT_EQ(exif_["Exif.MakerNote.ByteOrder"].toString(), std::string("II"));

  mn->setByteOrder(bigEndian);
  decoder.visitIfdMakernote(mn.get());
  EXPECT_EQ(exif_["Exif.MakerNote.ByteOrder"].toString(), std::string("MM"));
}

}  // namespace