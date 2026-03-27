// TEST_ID 1656
// File: test_tiffdecoder_visitMnEntry_1656.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

// Exiv2 public containers used by TiffDecoder ctor
#include <exiv2/exiv2.hpp>

namespace {

class TiffDecoderVisitMnEntryTest_1656 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;

  // Keep root as nullptr: visitMnEntry should be callable regardless; behavior is black-box.
  Exiv2::Internal::TiffComponent* root_ = nullptr;

  // Default / empty find-decoder function object (whatever the concrete type is).
  Exiv2::Internal::FindDecoderFct findDecoderFct_{};
};

TEST_F(TiffDecoderVisitMnEntryTest_1656, VisitMnEntryDoesNotThrowWithMinimalObject_1656) {
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, root_, findDecoderFct_);

  // Avoid relying on specific IfdId enumerators: use explicit casts.
  const uint16_t tag = 0x0001;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  Exiv2::Internal::TiffMnEntry mnEntry(tag, group, mnGroup);

  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
}

TEST_F(TiffDecoderVisitMnEntryTest_1656, VisitMnEntryHandlesBoundaryTagValuesWithoutThrow_1656) {
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, root_, findDecoderFct_);

  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  Exiv2::Internal::TiffMnEntry mnEntryMin(/*tag*/ 0x0000, group, mnGroup);
  Exiv2::Internal::TiffMnEntry mnEntryMax(/*tag*/ 0xFFFF, group, mnGroup);

  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntryMin));
  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntryMax));
}

TEST_F(TiffDecoderVisitMnEntryTest_1656, VisitMnEntryHandlesDifferentGroupsWithoutThrow_1656) {
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, root_, findDecoderFct_);

  const uint16_t tag = 0x00AA;

  // Exercise a few distinct values (treated as opaque).
  Exiv2::Internal::TiffMnEntry mnEntryA(tag, static_cast<Exiv2::IfdId>(0), static_cast<Exiv2::IfdId>(1));
  Exiv2::Internal::TiffMnEntry mnEntryB(tag, static_cast<Exiv2::IfdId>(2), static_cast<Exiv2::IfdId>(3));
  Exiv2::Internal::TiffMnEntry mnEntryC(tag, static_cast<Exiv2::IfdId>(0x7FFF), static_cast<Exiv2::IfdId>(0x7FFE));

  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntryA));
  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntryB));
  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntryC));
}

TEST_F(TiffDecoderVisitMnEntryTest_1656, VisitMnEntryIsRepeatableOnSameObject_1656) {
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, root_, findDecoderFct_);

  Exiv2::Internal::TiffMnEntry mnEntry(/*tag*/ 0x1234,
                                      static_cast<Exiv2::IfdId>(0),
                                      static_cast<Exiv2::IfdId>(0));

  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));
  EXPECT_NO_THROW(decoder.visitMnEntry(&mnEntry));  // repeated call should be safe/defined by impl
}

}  // namespace