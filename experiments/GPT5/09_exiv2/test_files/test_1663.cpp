// TEST_ID 1663
// Unit tests for Exiv2::Internal::TiffDecoder::decodeStdTiffEntry
//
// File under test: ./TestProjects/exiv2/src/tiffvisitor_int.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffDecoder
#include "tiffcomposite_int.hpp" // Exiv2::Internal::TiffEntryBase
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::TiffDecoder;
using Exiv2::Internal::TiffEntryBase;

// Minimal test helper to set protected idx() on TiffEntryBase.
class TestTiffEntryBase : public TiffEntryBase {
 public:
  TestTiffEntryBase(uint16_t tag, Exiv2::IfdId group, Exiv2::Internal::TiffType tiffType)
      : TiffEntryBase(tag, group, tiffType) {}

  void setTestIdx(int idx) { setIdx(idx); }  // protected in base
};

static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  // Many Exiv2 Value types accept read(string). Keep it simple/portable.
  v->read(s);
  return v;
}

}  // namespace

class TiffDecoderTest_1663 : public ::testing::Test {
 protected:
  TiffDecoderTest_1663()
      : decoder_(exif_, iptc_, xmp_, /*pRoot=*/nullptr, /*findDecoderFct=*/Exiv2::Internal::FindDecoderFct()) {}

  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;
  TiffDecoder decoder_;
};

TEST_F(TiffDecoderTest_1663, DecodeStdTiffEntryAddsOneExifDatum_1663) {
  // Arrange: create a TIFF entry with a value.
  TestTiffEntryBase entry(/*tag=*/0x010F, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entry.setTestIdx(0);
  entry.setValue(MakeAsciiValue("UnitTestMake"));

  ASSERT_TRUE(exif_.empty());
  ASSERT_EQ(exif_.count(), 0u);

  // Act
  decoder_.decodeStdTiffEntry(&entry);

  // Assert: ExifData should now contain at least one datum.
  EXPECT_FALSE(exif_.empty());
  EXPECT_EQ(exif_.count(), 1u);

  // Additionally validate that the stored key is consistent with the created entry:
  // Reconstruct an ExifKey from the produced key string (no dependency on groupName()).
  auto it = exif_.begin();
  ASSERT_NE(it, exif_.end());
  const std::string producedKeyStr = it->key();

  ExifKey producedKey(producedKeyStr);
  EXPECT_EQ(producedKey.tag(), entry.tag());
  EXPECT_EQ(producedKey.idx(), entry.idx());
}

TEST_F(TiffDecoderTest_1663, DecodeStdTiffEntryPreservesNonZeroIdxInAddedKey_1663) {
  // Arrange
  TestTiffEntryBase entry(/*tag=*/0x0110, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entry.setTestIdx(2);
  entry.setValue(MakeAsciiValue("UnitTestModel"));

  // Act
  decoder_.decodeStdTiffEntry(&entry);

  // Assert
  ASSERT_EQ(exif_.count(), 1u);
  auto it = exif_.begin();
  ASSERT_NE(it, exif_.end());

  ExifKey producedKey(it->key());
  EXPECT_EQ(producedKey.tag(), entry.tag());
  EXPECT_EQ(producedKey.idx(), 2);
}

TEST_F(TiffDecoderTest_1663, DecodeStdTiffEntryAddsTwoDistinctEntries_1663) {
  // Arrange: two different tags (same group), both with values.
  TestTiffEntryBase entry1(/*tag=*/0x010F, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entry1.setTestIdx(0);
  entry1.setValue(MakeAsciiValue("Make1"));

  TestTiffEntryBase entry2(/*tag=*/0x0110, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entry2.setTestIdx(0);
  entry2.setValue(MakeAsciiValue("Model1"));

  // Act
  decoder_.decodeStdTiffEntry(&entry1);
  decoder_.decodeStdTiffEntry(&entry2);

  // Assert: should contain two entries (different keys).
  EXPECT_EQ(exif_.count(), 2u);

  // Verify both keys exist by scanning produced keys and matching tags.
  bool sawTag1 = false;
  bool sawTag2 = false;
  for (auto it = exif_.begin(); it != exif_.end(); ++it) {
    ExifKey k(it->key());
    if (k.tag() == entry1.tag()) sawTag1 = true;
    if (k.tag() == entry2.tag()) sawTag2 = true;
  }
  EXPECT_TRUE(sawTag1);
  EXPECT_TRUE(sawTag2);
}

TEST_F(TiffDecoderTest_1663, DecodeStdTiffEntryAllowsMultipleIdxForSameTag_1663) {
  // Boundary-ish: same tag but different idx values should yield distinct keys.
  TestTiffEntryBase entryIdx0(/*tag=*/0x010F, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entryIdx0.setTestIdx(0);
  entryIdx0.setValue(MakeAsciiValue("MakeIdx0"));

  TestTiffEntryBase entryIdx1(/*tag=*/0x010F, /*group=*/Exiv2::ifd0Id, Exiv2::Internal::ttAsciiString);
  entryIdx1.setTestIdx(1);
  entryIdx1.setValue(MakeAsciiValue("MakeIdx1"));

  decoder_.decodeStdTiffEntry(&entryIdx0);
  decoder_.decodeStdTiffEntry(&entryIdx1);

  // Expect two entries present (same tag, different idx).
  EXPECT_EQ(exif_.count(), 2u);

  bool sawIdx0 = false;
  bool sawIdx1 = false;
  for (auto it = exif_.begin(); it != exif_.end(); ++it) {
    ExifKey k(it->key());
    if (k.tag() == entryIdx0.tag() && k.idx() == 0) sawIdx0 = true;
    if (k.tag() == entryIdx1.tag() && k.idx() == 1) sawIdx1 = true;
  }
  EXPECT_TRUE(sawIdx0);
  EXPECT_TRUE(sawIdx1);
}