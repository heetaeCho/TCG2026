void encodeBinaryElement(TiffBinaryElement* object, const Exifdatum* datum);
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a TiffEncoder with minimal valid dependencies
class TiffEncoderBinaryElementTest_1681 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_ = ExifData();
    iptcData_ = IptcData();
    xmpData_ = XmpData();
  }

  ExifData exifData_;
  IptcData iptcData_;
  XmpData xmpData_;
};

// Test that encodeBinaryElement can be called with a null datum without crashing
TEST_F(TiffEncoderBinaryElementTest_1681, EncodeBinaryElementWithNullDatum_1681) {
  // Create a minimal TiffBinaryElement
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);

  // We need a valid TiffEncoder. This requires a TiffHeaderBase and root component.
  // Use TiffImage's infrastructure to create one.
  auto header = std::make_unique<TiffHeader>();
  
  // Create a root directory
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  // Call encodeBinaryElement with null datum - should handle gracefully
  EXPECT_NO_THROW(encoder.encodeBinaryElement(&element, nullptr));
}

// Test that encodeBinaryElement can be called with a valid datum
TEST_F(TiffEncoderBinaryElementTest_1681, EncodeBinaryElementWithValidDatum_1681) {
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);
  
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum.setValue("1024");
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_NO_THROW(encoder.encodeBinaryElement(&element, &datum));
}

// Test dirty flag behavior - initially should not be dirty
TEST_F(TiffEncoderBinaryElementTest_1681, InitialDirtyState_1681) {
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_FALSE(encoder.dirty());
}

// Test setDirty and dirty accessor
TEST_F(TiffEncoderBinaryElementTest_1681, SetDirtyFlag_1681) {
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  encoder.setDirty(true);
  EXPECT_TRUE(encoder.dirty());
  
  encoder.setDirty(false);
  EXPECT_FALSE(encoder.dirty());
}

// Test writeMethod returns wmNonIntrusive initially
TEST_F(TiffEncoderBinaryElementTest_1681, InitialWriteMethod_1681) {
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test byteOrder matches header's byte order
TEST_F(TiffEncoderBinaryElementTest_1681, ByteOrderMatchesHeader_1681) {
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_EQ(encoder.byteOrder(), header->byteOrder());
}

// Test TiffBinaryElement setElDef and elDef accessor
TEST_F(TiffEncoderBinaryElementTest_1681, BinaryElementDefAccessors_1681) {
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);
  
  ArrayDef def = {0, ttUnsignedByte, 1};
  element.setElDef(def);
  
  const ArrayDef* retrievedDef = element.elDef();
  ASSERT_NE(retrievedDef, nullptr);
  EXPECT_EQ(retrievedDef->type_, ttUnsignedByte);
}

// Test TiffBinaryElement byte order accessor
TEST_F(TiffEncoderBinaryElementTest_1681, BinaryElementByteOrder_1681) {
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);
  
  EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
  
  element.setElByteOrder(bigEndian);
  EXPECT_EQ(element.elByteOrder(), bigEndian);
  
  element.setElByteOrder(littleEndian);
  EXPECT_EQ(element.elByteOrder(), littleEndian);
}

// Test encoding binary element for new image
TEST_F(TiffEncoderBinaryElementTest_1681, EncodeBinaryElementNewImage_1681) {
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);
  
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum.setValue("2048");
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, true /* isNewImage */, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_NO_THROW(encoder.encodeBinaryElement(&element, &datum));
}

// Test encoding with element having specific byte order set
TEST_F(TiffEncoderBinaryElementTest_1681, EncodeBinaryElementWithByteOrder_1681) {
  TiffBinaryElement element(0x0001, IfdId::ifd0Id);
  element.setElByteOrder(littleEndian);
  
  ArrayDef def = {0, ttUnsignedShort, 1};
  element.setElDef(def);
  
  auto header = std::make_unique<TiffHeader>();
  auto rootDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
  TiffComponent* pRoot = rootDir.get();
  
  PrimaryGroups primaryGroups;
  
  ExifKey key("Exif.Image.ImageWidth");
  Exifdatum datum(key);
  datum.setValue("512");
  
  TiffEncoder encoder(
      exifData_, iptcData_, xmpData_,
      pRoot, false, std::move(primaryGroups),
      header.get(), nullptr);
  
  EXPECT_NO_THROW(encoder.encodeBinaryElement(&element, &datum));
}

}  // namespace
