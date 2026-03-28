#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a TiffEncoder with minimal valid state
class TiffEncoderTestFixture_1689 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
};

// We need a concrete TiffEntryBase subclass for testing
// TiffEntry is a concrete subclass of TiffEntryBase

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_NewValueFits_1689) {
  // Create a TiffEntry with some initial data that is large enough
  // to hold the new value
  TiffEntry object(0x0100, IfdId::ifd0Id);
  
  // Set initial data with a decent size
  auto storage = std::make_shared<DataBuf>(100);
  std::memset(storage->data(), 0, 100);
  object.setData(storage->data(), 100, storage);
  
  // Create an Exifdatum with a value that fits (smaller or equal size)
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum = uint32_t(1024);  // Small value, should fit in 100 bytes
  
  // Create a minimal TiffEncoder
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  
  // We need a TiffHeader and root component
  TiffHeader header;
  
  // Create a root directory
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  // The datum size (4 bytes for uint32) should be <= object.size_ (100)
  // So this should take the setValue path (not dirty)
  ASSERT_FALSE(encoder.dirty());
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Since value fits, dirty should NOT be set
  EXPECT_FALSE(encoder.dirty());
  
  // The value should have been set
  ASSERT_NE(object.pValue(), nullptr);
  EXPECT_EQ(object.pValue()->toInt64(), 1024);
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_NewValueDoesNotFit_1689) {
  // Create a TiffEntry with very small initial data
  TiffEntry object(0x0100, IfdId::ifd0Id);
  
  // Set initial data with a very small size (e.g., 1 byte)
  auto storage = std::make_shared<DataBuf>(1);
  storage->data()[0] = 0;
  object.setData(storage->data(), 1, storage);
  
  // Create an Exifdatum with a value that does NOT fit (larger than 1 byte)
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum = uint32_t(1024);  // 4 bytes, won't fit in 1 byte
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  ASSERT_FALSE(encoder.dirty());
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Since value doesn't fit, dirty should be set
  EXPECT_TRUE(encoder.dirty());
  
  // The value should still have been updated
  ASSERT_NE(object.pValue(), nullptr);
  EXPECT_EQ(object.pValue()->toInt64(), 1024);
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_ExactFit_1689) {
  // Create a TiffEntry where the new value exactly fits
  TiffEntry object(0x0100, IfdId::ifd0Id);
  
  // uint32_t is 4 bytes, so set data to exactly 4 bytes
  auto storage = std::make_shared<DataBuf>(4);
  std::memset(storage->data(), 0, 4);
  object.setData(storage->data(), 4, storage);
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum = uint32_t(2048);  // 4 bytes, exactly fits in 4 bytes
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  ASSERT_FALSE(encoder.dirty());
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Exact fit: newSize == object->size_, so should NOT be dirty
  EXPECT_FALSE(encoder.dirty());
  
  ASSERT_NE(object.pValue(), nullptr);
  EXPECT_EQ(object.pValue()->toInt64(), 2048);
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_ValueSmallerThanExisting_1689) {
  // Object has large data, datum has small value
  TiffEntry object(0x0100, IfdId::ifd0Id);
  
  auto storage = std::make_shared<DataBuf>(256);
  std::memset(storage->data(), 0, 256);
  object.setData(storage->data(), 256, storage);
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum = uint16_t(42);  // 2 bytes, fits in 256 bytes
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Value fits, so not dirty
  EXPECT_FALSE(encoder.dirty());
  ASSERT_NE(object.pValue(), nullptr);
  EXPECT_EQ(object.pValue()->toInt64(), 42);
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_ZeroSizeObject_1689) {
  // Object with zero initial size - any non-zero datum should trigger dirty
  TiffEntry object(0x0100, IfdId::ifd0Id);
  // Don't set any data, so size_ should be 0
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum = uint32_t(100);  // 4 bytes > 0
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Value doesn't fit in 0 bytes, should be dirty
  EXPECT_TRUE(encoder.dirty());
  
  ASSERT_NE(object.pValue(), nullptr);
  EXPECT_EQ(object.pValue()->toInt64(), 100);
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_StringValue_DoesNotFit_1689) {
  TiffEntry object(0x010E, IfdId::ifd0Id);  // ImageDescription - ASCII tag
  
  // Set small initial data
  auto storage = std::make_shared<DataBuf>(5);
  std::memset(storage->data(), 0, 5);
  object.setData(storage->data(), 5, storage);
  
  ExifKey key("Exif.Image.ImageDescription");
  Exifdatum datum(key);
  datum = std::string("This is a very long image description that exceeds the original size");
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Long string doesn't fit in 5 bytes, should be dirty
  EXPECT_TRUE(encoder.dirty());
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, EncodeOffsetEntry_StringValue_Fits_1689) {
  TiffEntry object(0x010E, IfdId::ifd0Id);  // ImageDescription - ASCII tag
  
  // Set large initial data
  auto storage = std::make_shared<DataBuf>(1000);
  std::memset(storage->data(), 0, 1000);
  object.setData(storage->data(), 1000, storage);
  
  ExifKey key("Exif.Image.ImageDescription");
  Exifdatum datum(key);
  datum = std::string("Short");
  
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  encoder.encodeOffsetEntry(&object, &datum);
  
  // Short string fits in 1000 bytes, should NOT be dirty
  EXPECT_FALSE(encoder.dirty());
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, SetDirty_DefaultFalse_1689) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  EXPECT_FALSE(encoder.dirty());
  
  delete pRoot;
}

TEST_F(TiffEncoderTestFixture_1689, SetDirty_ExplicitlySetTrue_1689) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  TiffHeader header;
  
  auto pRoot = new TiffDirectory(0x0000, IfdId::ifd0Id);
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData, iptcData, xmpData, pRoot,
                      false, std::move(primaryGroups), &header,
                      TiffMapping::findEncoder);
  
  encoder.setDirty(true);
  EXPECT_TRUE(encoder.dirty());
  
  encoder.setDirty(false);
  EXPECT_FALSE(encoder.dirty());
  
  delete pRoot;
}

}  // namespace
