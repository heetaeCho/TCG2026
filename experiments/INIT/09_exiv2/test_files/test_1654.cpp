// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1654
//
// File: test_tiffdecoder_visitSizeEntry_1654.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

#include <exiv2/exiv2.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::IfdId;
using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffSizeEntry;

static std::vector<std::string> DumpExifData(const ExifData& exif) {
  std::vector<std::string> out;
  out.reserve(exif.count());

  for (auto it = exif.begin(); it != exif.end(); ++it) {
    std::ostringstream oss;
    // Key and a stable textual representation of the value.
    oss << it->key() << "=" << it->toString();
    out.push_back(oss.str());
  }

  std::sort(out.begin(), out.end());
  return out;
}

static std::vector<std::string> DumpIptcData(const IptcData& iptc) {
  std::vector<std::string> out;
  out.reserve(iptc.count());

  for (auto it = iptc.begin(); it != iptc.end(); ++it) {
    std::ostringstream oss;
    oss << it->key() << "=" << it->toString();
    out.push_back(oss.str());
  }

  std::sort(out.begin(), out.end());
  return out;
}

static std::vector<std::string> DumpXmpData(const XmpData& xmp) {
  std::vector<std::string> out;
  out.reserve(xmp.count());

  for (auto it = xmp.begin(); it != xmp.end(); ++it) {
    std::ostringstream oss;
    oss << it->key() << "=" << it->toString();
    out.push_back(oss.str());
  }

  std::sort(out.begin(), out.end());
  return out;
}

class TiffDecoderVisitSizeEntryTest_1654 : public ::testing::Test {
 protected:
  // Helper to build a decoder with minimal collaborators.
  // We intentionally avoid making assumptions about decoding outcomes; the tests
  // only compare observable external state (Exif/Iptc/Xmp containers).
  static TiffDecoder MakeDecoder(ExifData& exif, IptcData& iptc, XmpData& xmp) {
    // pRoot is not observable through visitSizeEntry itself; keep it nullptr.
    Exiv2::Internal::TiffComponent* pRoot = nullptr;

    // FindDecoderFct is an external collaborator passed in; default construct to
    // a "no function" state (common for std::function). This avoids inferring
    // any internal behavior.
    Exiv2::Internal::FindDecoderFct findDecoderFct{};

    return TiffDecoder(exif, iptc, xmp, pRoot, findDecoderFct);
  }
};

TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryDoesNotThrowOnValidObject_1654) {
  ExifData exif;
  IptcData iptc;
  XmpData xmp;

  TiffDecoder decoder = MakeDecoder(exif, iptc, xmp);

  // Use boundary-ish values without relying on any specific enumerators.
  const uint16_t tag = 0;
  const uint16_t dtTag = 0xffff;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId dtGroup = static_cast<IfdId>(0);

  TiffSizeEntry entry(tag, group, dtTag, dtGroup);

  EXPECT_NO_THROW(decoder.visitSizeEntry(&entry));
}

TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryMatchesDecodeTiffEntryObservableEffects_1654) {
  // Decoder A: use visitSizeEntry
  ExifData exifA;
  IptcData iptcA;
  XmpData xmpA;
  TiffDecoder decoderA = MakeDecoder(exifA, iptcA, xmpA);

  // Decoder B: call decodeTiffEntry directly
  ExifData exifB;
  IptcData iptcB;
  XmpData xmpB;
  TiffDecoder decoderB = MakeDecoder(exifB, iptcB, xmpB);

  const uint16_t tag = 0x1234;
  const uint16_t dtTag = 0x5678;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId dtGroup = static_cast<IfdId>(1);

  TiffSizeEntry entry(tag, group, dtTag, dtGroup);

  // Execute
  ASSERT_NO_THROW(decoderA.visitSizeEntry(&entry));
  ASSERT_NO_THROW(decoderB.decodeTiffEntry(&entry));

  // Compare only observable public state: the external metadata containers.
  EXPECT_EQ(DumpExifData(exifA), DumpExifData(exifB));
  EXPECT_EQ(DumpIptcData(iptcA), DumpIptcData(iptcB));
  EXPECT_EQ(DumpXmpData(xmpA), DumpXmpData(xmpB));
}

TEST_F(TiffDecoderVisitSizeEntryTest_1654, VisitSizeEntryBoundaryTagsNoThrow_1654) {
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  TiffDecoder decoder = MakeDecoder(exif, iptc, xmp);

  const IfdId group0 = static_cast<IfdId>(0);
  const IfdId group1 = static_cast<IfdId>(1);

  // Lowest values
  {
    TiffSizeEntry entry(/*tag=*/0, group0, /*dtTag=*/0, group0);
    EXPECT_NO_THROW(decoder.visitSizeEntry(&entry));
  }

  // Highest uint16_t values
  {
    TiffSizeEntry entry(/*tag=*/0xffff, group1, /*dtTag=*/0xffff, group1);
    EXPECT_NO_THROW(decoder.visitSizeEntry(&entry));
  }
}

}  // namespace