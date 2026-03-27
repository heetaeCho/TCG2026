// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 1661
//
// Unit tests for Exiv2::Internal::TiffDecoder::decodeCanonAFInfo
//
// Constraints honored:
// - Black-box testing via public/visible behavior (ExifData mutations)
// - No reliance on private/internal state
// - No re-implementation of internal logic beyond constructing inputs
// - Boundary/error cases covered

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/xmp.hpp>

// Internal headers under test (project-local)
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Exifdatum;
using Exiv2::IptcData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::XmpData;

using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffEntryBase;

static std::string JoinAsValueString(const std::vector<uint16_t>& vals) {
  // decodeCanonAFInfo builds a string by appending " <number>" repeatedly.
  // Value::read tolerates leading spaces, so we mimic the same general format.
  std::ostringstream os;
  for (const auto& v : vals) {
    os << ' ' << v;
  }
  return os.str();
}

static std::vector<std::string> CollectExifKeys(const ExifData& exif) {
  std::vector<std::string> keys;
  keys.reserve(exif.count());
  for (auto it = exif.begin(); it != exif.end(); ++it) {
    keys.push_back(it->key());
  }
  return keys;
}

static bool AnyKeyContains(const std::vector<std::string>& keys, const std::string& needle) {
  return std::any_of(keys.begin(), keys.end(),
                     [&](const std::string& k) { return k.find(needle) != std::string::npos; });
}

static size_t CountKeysContaining(const std::vector<std::string>& keys, const std::string& needle) {
  return static_cast<size_t>(std::count_if(keys.begin(), keys.end(),
                                          [&](const std::string& k) { return k.find(needle) != std::string::npos; }));
}

static const Exifdatum* FindFirstDatumWithKeySubstring(const ExifData& exif, const std::string& needle) {
  for (auto it = exif.begin(); it != exif.end(); ++it) {
    if (it->key().find(needle) != std::string::npos) return &(*it);
  }
  return nullptr;
}

// Creates a TiffEntryBase with a Value of the requested type and contents.
static std::unique_ptr<TiffEntryBase> MakeEntryWithValue(TypeId type, const std::vector<uint16_t>& vals) {
  auto entry = std::make_unique<TiffEntryBase>(
      /*tag*/ static_cast<uint16_t>(0x2600),
      /*group*/ static_cast<Exiv2::IfdId>(0),
      /*tiffType*/ static_cast<Exiv2::Internal::TiffType>(0));

  auto v = Value::create(type);
  ASSERT_NE(v.get(), nullptr);

  const std::string s = JoinAsValueString(vals);
  (void)v->read(s);

  entry->setValue(std::move(v));
  return entry;
}

class TiffDecoderCanonAFInfoTest_1661 : public ::testing::Test {
 protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;

  // pRoot/findDecoderFct_ are not used directly by decodeCanonAFInfo in the provided snippet.
  // Keep them minimal and deterministic.
  TiffDecoderCanonAFInfoTest_1661()
      : decoder_(exif_, iptc_, xmp_, /*pRoot*/ nullptr,
                 /*findDecoderFct*/ Exiv2::Internal::FindDecoderFct()) {}

  TiffDecoder decoder_;
};

TEST_F(TiffDecoderCanonAFInfoTest_1661, DoesNotAddCanonAfInfoFieldsWhenCountLessThan3_1661) {
  // count < 3 triggers early return after decodeStdTiffEntry.
  // We assert that none of the Canon AFInfo-related keys appear in ExifData.
  auto entry = MakeEntryWithValue(Exiv2::unsignedShort, /*vals*/ {4, 1});  // count == 2

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);
  EXPECT_FALSE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFPointsInFocus"));
}

TEST_F(TiffDecoderCanonAFInfoTest_1661, DoesNotAddCanonAfInfoFieldsWhenTypeIsNotUnsignedShort_1661) {
  // Wrong type triggers early return.
  auto entry = MakeEntryWithValue(Exiv2::signedShort, /*vals*/ {6, 1, 1});  // count == 3 but wrong type

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);
  EXPECT_FALSE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFPointsSelected"));
}

TEST_F(TiffDecoderCanonAFInfoTest_1661, DoesNotAddCanonAfInfoFieldsWhenSizeHeaderMismatch_1661) {
  // If the first element (AFInfoSize) != count*2, the function returns early.
  // Choose count=15 but first value is wrong.
  std::vector<uint16_t> vals = {
      /*AFInfoSize*/ 0,  // mismatch (should be 30 for count 15)
      /*AFAreaMode*/ 1,
      /*AFNumPoints*/ 1,
      /*AFValidPoints*/ 1,
      /*AFCanonImageWidth*/ 100,
      /*AFCanonImageHeight*/ 200,
      /*AFImageWidth*/ 100,
      /*AFImageHeight*/ 200,
      /*AFAreaWidths[1]*/ 10,
      /*AFAreaHeights[1]*/ 10,
      /*AFXPositions[1]*/ 5,
      /*AFYPositions[1]*/ 6,
      /*AFPointsInFocus[mask1]*/ 1,
      /*AFPointsSelected[mask1]*/ 1,
      /*AFPointsUnusable[mask1]*/ 0,
  };
  auto entry = MakeEntryWithValue(Exiv2::unsignedShort, vals);

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);
  EXPECT_FALSE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFAreaWidths"));
}

TEST_F(TiffDecoderCanonAFInfoTest_1661, DoesNotAddCanonAfInfoFieldsWhenRecordSizesExceedAvailableData_1661) {
  // The function computes required record sizes and returns if not enough data.
  // Set nPoints (value at index 2) large enough to make required count exceed provided count.
  // Keep vector length small so "count > ints.size()" becomes true in the preflight loop.
  //
  // NOTE: First value must still be count*2 to pass that check.
  const uint16_t providedCount = 6;
  std::vector<uint16_t> vals = {
      static_cast<uint16_t>(providedCount * 2),  // size header matches
      1,
      /*nPoints*/ 20,  // forces many records, should exceed providedCount
      1,
      100,
      200,
  };
  auto entry = MakeEntryWithValue(Exiv2::unsignedShort, vals);

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);
  EXPECT_FALSE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_FALSE(AnyKeyContains(keys, "AFPointsUnusable"));
}

TEST_F(TiffDecoderCanonAFInfoTest_1661, PopulatesExpectedCanonAfInfoFieldsForValidInput_1661) {
  // Construct a minimal valid Canon AFInfo payload with nPoints=1.
  // Total records required:
  // - 8 single-value fields (0x2600..0x2607)
  // - 4 arrays of length nPoints (0x2608..0x260b) => 4
  // - 3 masks of length nMasks where nMasks=(nPoints+15)/16 => 1 => 3
  // Total = 8 + 4 + 3 = 15
  const uint16_t count = 15;
  const uint16_t nPoints = 1;
  const uint16_t nMasks = 1;

  (void)nMasks;  // documentation-only in this test

  std::vector<uint16_t> vals = {
      /*AFInfoSize*/ static_cast<uint16_t>(count * 2),
      /*AFAreaMode*/ 1,
      /*AFNumPoints*/ nPoints,
      /*AFValidPoints*/ 1,
      /*AFCanonImageWidth*/ 100,
      /*AFCanonImageHeight*/ 200,
      /*AFImageWidth*/ 100,
      /*AFImageHeight*/ 200,
      /*AFAreaWidths[1]*/ 10,
      /*AFAreaHeights[1]*/ 11,
      /*AFXPositions[1]*/ 5,
      /*AFYPositions[1]*/ 6,
      /*AFPointsInFocus[mask1]*/ 0x0001,
      /*AFPointsSelected[mask1]*/ 0x0001,
      /*AFPointsUnusable[mask1]*/ 0x0000,
  };

  auto entry = MakeEntryWithValue(Exiv2::unsignedShort, vals);

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);

  // Verify several well-known Canon AFInfo tag names were populated.
  // We intentionally do not assert the full key prefix (groupName-dependent),
  // only that these tag-name substrings exist somewhere in ExifData keys.
  EXPECT_TRUE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFAreaWidths"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFPointsInFocus"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFPointsSelected"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFPointsUnusable"));

  // Boundary-ish verification: arrays and masks should yield exactly one datum each (not per-element datums).
  // The function writes one Exif datum per record, even when the record has multiple values.
  EXPECT_EQ(CountKeysContaining(keys, "AFAreaWidths"), 1u);
  EXPECT_EQ(CountKeysContaining(keys, "AFAreaHeights"), 1u);
  EXPECT_EQ(CountKeysContaining(keys, "AFXPositions"), 1u);
  EXPECT_EQ(CountKeysContaining(keys, "AFYPositions"), 1u);
  EXPECT_EQ(CountKeysContaining(keys, "AFPointsInFocus"), 1u);

  // Verify at least one of the produced values includes our expected numeric content.
  // (This checks observable formatting/content without assuming exact formatting details.)
  const Exifdatum* numPointsDatum = FindFirstDatumWithKeySubstring(exif_, "AFNumPoints");
  ASSERT_NE(numPointsDatum, nullptr);
  EXPECT_NE(numPointsDatum->toString().find("1"), std::string::npos);
}

TEST_F(TiffDecoderCanonAFInfoTest_1661, HandlesZeroPointsAsBoundaryCaseWithoutCrashingAndStillWritesFixedFields_1661) {
  // nPoints = 0 => nMasks = 0; record sizes become:
  // total = 8 (fixed) + 0 (4 arrays) + 0 (3 masks) = 8
  const uint16_t count = 8;
  std::vector<uint16_t> vals = {
      /*AFInfoSize*/ static_cast<uint16_t>(count * 2),
      /*AFAreaMode*/ 1,
      /*AFNumPoints*/ 0,
      /*AFValidPoints*/ 0,
      /*AFCanonImageWidth*/ 100,
      /*AFCanonImageHeight*/ 200,
      /*AFImageWidth*/ 100,
      /*AFImageHeight*/ 200,
  };

  auto entry = MakeEntryWithValue(Exiv2::unsignedShort, vals);

  decoder_.decodeCanonAFInfo(entry.get());

  const auto keys = CollectExifKeys(exif_);

  // Fixed fields should exist; point-dependent fields should also exist but with empty payload,
  // depending on whether the Canon tag table includes them. We check fixed ones robustly.
  EXPECT_TRUE(AnyKeyContains(keys, "AFInfoSize"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFNumPoints"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFImageWidth"));
  EXPECT_TRUE(AnyKeyContains(keys, "AFImageHeight"));
}

}  // namespace