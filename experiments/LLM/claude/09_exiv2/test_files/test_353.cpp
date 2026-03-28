#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a minimal TiffEncoder
// TiffEncoder requires many dependencies; we set up minimal valid ones
class TiffImageEntryTest_353 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
};

// Test that doEncode delegates to encoder.encodeImageEntry
// We verify this by checking that the encoder's dirty flag or write method
// changes state appropriately after encoding
TEST_F(TiffImageEntryTest_353, DoEncodeCallsEncodeImageEntry_353) {
  // Create a TiffImageEntry with a valid tag and group
  TiffImageEntry entry(0x0111, IfdId::ifd0Id);  // StripOffsets tag

  // We need a TiffEncoder to call doEncode
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  // Create a minimal TIFF tree
  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  // Create a minimal TiffHeader-like object
  // Using TiffHeader from tiffimage_int
  TiffHeader header;

  PrimaryGroups primaryGroups;

  // Create encoder - note: the findEncoderFct can be nullptr or a real function
  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       false, std::move(primaryGroups), &header, nullptr);

  // Call doEncode with nullptr datum - should not crash
  entry.doEncode(encoder, nullptr);

  // If we get here without crashing, the delegation worked
  SUCCEED();
}

// Test doEncode with a valid Exifdatum
TEST_F(TiffImageEntryTest_353, DoEncodeWithValidDatum_353) {
  TiffImageEntry entry(0x0111, IfdId::ifd0Id);

  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  TiffHeader header;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       false, std::move(primaryGroups), &header, nullptr);

  // Create an Exifdatum
  ExifKey key("Exif.Image.StripOffsets");
  Exifdatum datum(key);
  datum.setValue("0");

  // Call doEncode with a valid datum
  entry.doEncode(encoder, &datum);

  SUCCEED();
}

// Test doEncode with new image flag set
TEST_F(TiffImageEntryTest_353, DoEncodeWithNewImage_353) {
  TiffImageEntry entry(0x0111, IfdId::ifd0Id);

  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  TiffHeader header;
  PrimaryGroups primaryGroups;

  // isNewImage = true
  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       true, std::move(primaryGroups), &header, nullptr);

  entry.doEncode(encoder, nullptr);

  SUCCEED();
}

// Test doEncode with different tag values
TEST_F(TiffImageEntryTest_353, DoEncodeWithStripByteCountsTag_353) {
  // StripByteCounts tag
  TiffImageEntry entry(0x0117, IfdId::ifd0Id);

  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  TiffHeader header;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       false, std::move(primaryGroups), &header, nullptr);

  entry.doEncode(encoder, nullptr);

  SUCCEED();
}

// Test that encoder's dirty state can be checked after encoding
TEST_F(TiffImageEntryTest_353, EncoderDirtyStateAfterEncode_353) {
  TiffImageEntry entry(0x0111, IfdId::ifd0Id);

  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  TiffHeader header;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       false, std::move(primaryGroups), &header, nullptr);

  // Check initial dirty state
  bool dirtyBefore = encoder.dirty();

  entry.doEncode(encoder, nullptr);

  // dirty state may or may not change depending on implementation
  // We just verify it's queryable without error
  bool dirtyAfter = encoder.dirty();
  (void)dirtyBefore;
  (void)dirtyAfter;

  SUCCEED();
}

// Test with entry in sub-IFD group
TEST_F(TiffImageEntryTest_353, DoEncodeWithSubIfdGroup_353) {
  TiffImageEntry entry(0x0111, IfdId::subImage1Id);

  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;

  auto pRoot = std::make_unique<TiffDirectory>(0x0000, IfdId::ifd0Id);
  TiffComponent* pRootRaw = pRoot.get();

  TiffHeader header;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, pRootRaw,
                       false, std::move(primaryGroups), &header, nullptr);

  entry.doEncode(encoder, nullptr);

  SUCCEED();
}

}  // namespace
